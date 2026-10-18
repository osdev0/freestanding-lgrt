//===-- atomic.c - Implement support functions for atomic operations.------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
// 2026/10/17 - Modified by Mintsuki for use inside freestanding-lgrt
//
//===----------------------------------------------------------------------===//
//
//  atomic.c defines a set of functions for performing atomic accesses on
//  arbitrary-sized memory locations.  This design uses locks that should
//  be fast in the uncontended case, for two reasons:
//
//  1) This code must work with C programs that do not link to anything
//     (including pthreads) and so it should not depend on any pthread
//     functions. If the user wishes to opt into using pthreads, they may do so.
//  2) Atomic operations, rather than explicit mutexes, are most commonly used
//     on code where contended operations are rate.
//
//  To avoid needing a per-object lock, this code allocates an array of
//  locks and hashes the object pointers to find the one that it should use.
//  For operations that must be atomic on two locations, the lower lock is
//  always acquired first, to avoid deadlock.
//
//===----------------------------------------------------------------------===//

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "assembly.h"

// Built where the compiler can do pointer-sized atomics inline, with
// instructions the CPU has, which ARM has from v6 on, except in Thumb1 code
// before ARMv8-M Baseline. GCC is not supported on 32-bit LoongArch.
//
// Workaround: GCC up to 4.9, all targets: __atomic_always_lock_free is not a
// constant expression, and up to 4.8, _Atomic is missing.
//
// Workaround: Clang up to at least 23, 80386: it reports atomics as lock-free,
// and uses cmpxchg and xadd for them, which the 80486 added.
//
// Workaround: Clang up to at least 23, ARM before v6K: it reports byte,
// halfword and doubleword atomics as lock-free, and uses the exclusives for
// them that v6K added.
//
// Workaround: GCC up to at least 13, ARM Linux targets before v6K: it turns
// byte and halfword atomics into __sync_* calls.
//
// Workaround: Clang 16 to 20, 32-bit LoongArch: it cannot compile some atomic
// operations.
#if (defined(__clang__) || defined(__GNUC__)) &&                               \
    !(!defined(__clang__) && __GNUC__ < 5) &&                                  \
    __GCC_ATOMIC_POINTER_LOCK_FREE == 2 &&                                     \
    !(defined(__i386__) && !defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_4)) &&    \
    !(defined(__arm__) &&                                                      \
      (__ARM_ARCH < 6 ||                                                       \
       (defined(__thumb__) && !defined(__thumb2__) && __ARM_ARCH < 8))) &&     \
    !(defined(__arm__) && defined(__clang__) &&                                \
      defined(__ARM_FEATURE_LDREX) && !(__ARM_FEATURE_LDREX & 1)) &&           \
    !(defined(__arm__) && !defined(__clang__) && defined(__linux__) &&         \
      !defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_1)) &&                         \
    !(defined(__loongarch__) && __loongarch_grlen == 32 &&                     \
      (!defined(__clang__) || __clang_major__ < 21))

// _Atomic and _Static_assert are C11, which pedantic C99 builds would reject.
//
// Workaround: GCC 5 up to at least 16, all targets: its -Wpedantic says that
// the expression of the static assertion below is not an integer constant
// expression.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"

// We use __builtin_mem* here to avoid dependencies on libc-provided headers.
#define memcpy __builtin_memcpy
#define memcmp __builtin_memcmp

// Clang objects if you redefine a builtin.  This little hack allows us to
// define a function with the same name as an intrinsic.
#pragma redefine_extname __atomic_load_c SYMBOL_NAME(__atomic_load)
#pragma redefine_extname __atomic_store_c SYMBOL_NAME(__atomic_store)
#pragma redefine_extname __atomic_exchange_c SYMBOL_NAME(__atomic_exchange)
#pragma redefine_extname __atomic_compare_exchange_c SYMBOL_NAME(              \
    __atomic_compare_exchange)
#pragma redefine_extname __atomic_is_lock_free_c SYMBOL_NAME(                  \
    __atomic_is_lock_free)

#ifndef __clang__
// GCC has no __c11_atomic_* builtins, but equivalent __atomic_* ones, which
// accept pointers to _Atomic types too.
#define __c11_atomic_load __atomic_load_n
#define __c11_atomic_store __atomic_store_n
#define __c11_atomic_exchange __atomic_exchange_n
#define __c11_atomic_compare_exchange_strong(p, e, d, s, f)                    \
  __atomic_compare_exchange_n(p, e, d, false, s, f)
#define __c11_atomic_compare_exchange_weak(p, e, d, s, f)                      \
  __atomic_compare_exchange_n(p, e, d, true, s, f)
#define __c11_atomic_fetch_add __atomic_fetch_add
#define __c11_atomic_fetch_sub __atomic_fetch_sub
#define __c11_atomic_fetch_and __atomic_fetch_and
#define __c11_atomic_fetch_or __atomic_fetch_or
#define __c11_atomic_fetch_xor __atomic_fetch_xor
#define __c11_atomic_fetch_nand __atomic_fetch_nand

// Workaround: GCC 5 up to at least 16, all targets: it does not apply the
// pragmas above to definitions, and it treats names such as __atomic_load_4 as
// its own builtins, so all functions here get a _c suffix, and declarations
// that give them their real names as asm labels.
#define ATOMIC_STR_(x) #x
#define ATOMIC_STR(x) ATOMIC_STR_(x)
#define ATOMIC_DECL(ret, name, params)                                         \
  ret name##_c params __asm__(ATOMIC_STR(SYMBOL_NAME(name)))
ATOMIC_DECL(bool, __atomic_is_lock_free, (size_t, void *));
ATOMIC_DECL(void, __atomic_load, (size_t, void *, void *, int));
ATOMIC_DECL(void, __atomic_store, (size_t, void *, void *, int));
ATOMIC_DECL(int, __atomic_compare_exchange,
            (size_t, void *, void *, void *, int, int));
ATOMIC_DECL(void, __atomic_exchange, (size_t, void *, void *, void *, int));
#endif

/// Number of locks.  This allocates one page on 32-bit platforms, two on
/// 64-bit.  This can be specified externally if a different trade between
/// memory usage and contention probability is required for a given platform.
#ifndef SPINLOCK_COUNT
#define SPINLOCK_COUNT (1 << 10)
#endif
static const long SPINLOCK_MASK = SPINLOCK_COUNT - 1;

////////////////////////////////////////////////////////////////////////////////
// Platform-specific lock implementation.  Falls back to spinlocks if none is
// defined.  Each platform should define the Lock type, and corresponding
// lock() and unlock() functions.
////////////////////////////////////////////////////////////////////////////////
_Static_assert(__atomic_always_lock_free(sizeof(uintptr_t), 0),
               "Implementation assumes lock-free pointer-size cmpxchg");
typedef _Atomic(uintptr_t) Lock;
/// Unlock a lock.  This is a release operation.
__inline static void unlock(Lock *l) {
  __c11_atomic_store(l, 0, __ATOMIC_RELEASE);
}
/// Locks a lock.  In the current implementation, this is potentially
/// unbounded in the contended case.
__inline static void lock(Lock *l) {
  uintptr_t old = 0;
  while (!__c11_atomic_compare_exchange_weak(l, &old, 1, __ATOMIC_ACQUIRE,
                                             __ATOMIC_RELAXED))
    old = 0;
}
/// locks for atomic operations
static Lock locks[SPINLOCK_COUNT];

/// Returns a lock to use for a given pointer.
static __inline Lock *lock_for_pointer(void *ptr) {
  intptr_t hash = (intptr_t)ptr;
  // Disregard the lowest 4 bits.  We want all values that may be part of the
  // same memory operation to hash to the same value and therefore use the same
  // lock.
  hash >>= 4;
  // Use the next bits as the basis for the hash
  intptr_t low = hash & SPINLOCK_MASK;
  // Now use the high(er) set of bits to perturb the hash, so that we don't
  // get collisions from atomic fields in a single object
  hash >>= 16;
  hash ^= low;
  // Return a pointer to the word to use
  return locks + (hash & SPINLOCK_MASK);
}

/// Macros for determining whether a size is lock free.
#define ATOMIC_ALWAYS_LOCK_FREE_OR_ALIGNED_LOCK_FREE(size, p)                  \
  (__atomic_always_lock_free(size, p) ||                                       \
   (__atomic_always_lock_free(size, 0) && ((uintptr_t)p % size) == 0))
#define IS_LOCK_FREE_1(p) ATOMIC_ALWAYS_LOCK_FREE_OR_ALIGNED_LOCK_FREE(1, p)
#define IS_LOCK_FREE_2(p) ATOMIC_ALWAYS_LOCK_FREE_OR_ALIGNED_LOCK_FREE(2, p)
#define IS_LOCK_FREE_4(p) ATOMIC_ALWAYS_LOCK_FREE_OR_ALIGNED_LOCK_FREE(4, p)
#define IS_LOCK_FREE_8(p) ATOMIC_ALWAYS_LOCK_FREE_OR_ALIGNED_LOCK_FREE(8, p)
#define IS_LOCK_FREE_16(p) ATOMIC_ALWAYS_LOCK_FREE_OR_ALIGNED_LOCK_FREE(16, p)

/// Macro that calls the compiler-generated lock-free versions of functions
/// when they exist.
#define TRY_LOCK_FREE_CASE(n, type, ptr)                                       \
  case n:                                                                      \
    if (IS_LOCK_FREE_##n(ptr)) {                                               \
      LOCK_FREE_ACTION(type);                                                  \
    }                                                                          \
    break;
#ifdef __SIZEOF_INT128__
#define TRY_LOCK_FREE_CASE_16(p) TRY_LOCK_FREE_CASE(16, __uint128_t, p)
#else
#define TRY_LOCK_FREE_CASE_16(p) /* __uint128_t not available */
#endif

#define LOCK_FREE_CASES(ptr)                                                   \
  do {                                                                         \
    switch (size) {                                                            \
      TRY_LOCK_FREE_CASE(1, uint8_t, ptr)                                      \
      TRY_LOCK_FREE_CASE(2, uint16_t, ptr)                                     \
      TRY_LOCK_FREE_CASE(4, uint32_t, ptr)                                     \
      TRY_LOCK_FREE_CASE(8, uint64_t, ptr)                                     \
      TRY_LOCK_FREE_CASE_16(ptr) /* __uint128_t may not be supported */        \
    default:                                                                   \
      break;                                                                   \
    }                                                                          \
  } while (0)

/// Whether atomic operations for the given size (and alignment) are lock-free.
bool __atomic_is_lock_free_c(size_t size, void *ptr) {
#define LOCK_FREE_ACTION(type) return true;
  LOCK_FREE_CASES(ptr);
#undef LOCK_FREE_ACTION
  return false;
}

/// An atomic load operation.  This is atomic with respect to the source
/// pointer only.
void __atomic_load_c(size_t size, void *src, void *dest, int model) {
#define LOCK_FREE_ACTION(type)                                                 \
  *((type *)dest) = __c11_atomic_load((_Atomic(type) *)src, model);            \
  return;
  LOCK_FREE_CASES(src);
#undef LOCK_FREE_ACTION
  Lock *l = lock_for_pointer(src);
  lock(l);
  memcpy(dest, src, size);
  unlock(l);
}

/// An atomic store operation.  This is atomic with respect to the destination
/// pointer only.
void __atomic_store_c(size_t size, void *dest, void *src, int model) {
#define LOCK_FREE_ACTION(type)                                                 \
  __c11_atomic_store((_Atomic(type) *)dest, *(type *)src, model);              \
  return;
  LOCK_FREE_CASES(dest);
#undef LOCK_FREE_ACTION
  Lock *l = lock_for_pointer(dest);
  lock(l);
  memcpy(dest, src, size);
  unlock(l);
}

/// Atomic compare and exchange operation.  If the value at *ptr is identical
/// to the value at *expected, then this copies value at *desired to *ptr.  If
/// they  are not, then this stores the current value from *ptr in *expected.
///
/// This function returns 1 if the exchange takes place or 0 if it fails.
int __atomic_compare_exchange_c(size_t size, void *ptr, void *expected,
                                void *desired, int success, int failure) {
#define LOCK_FREE_ACTION(type)                                                 \
  return __c11_atomic_compare_exchange_strong(                                 \
      (_Atomic(type) *)ptr, (type *)expected, *(type *)desired, success,       \
      failure)
  LOCK_FREE_CASES(ptr);
#undef LOCK_FREE_ACTION
  Lock *l = lock_for_pointer(ptr);
  lock(l);
  if (memcmp(ptr, expected, size) == 0) {
    memcpy(ptr, desired, size);
    unlock(l);
    return 1;
  }
  memcpy(expected, ptr, size);
  unlock(l);
  return 0;
}

/// Performs an atomic exchange operation between two pointers.  This is atomic
/// with respect to the target address.
void __atomic_exchange_c(size_t size, void *ptr, void *val, void *old,
                         int model) {
#define LOCK_FREE_ACTION(type)                                                 \
  *(type *)old =                                                               \
      __c11_atomic_exchange((_Atomic(type) *)ptr, *(type *)val, model);        \
  return;
  LOCK_FREE_CASES(ptr);
#undef LOCK_FREE_ACTION
  Lock *l = lock_for_pointer(ptr);
  lock(l);
  memcpy(old, ptr, size);
  memcpy(ptr, val, size);
  unlock(l);
}

////////////////////////////////////////////////////////////////////////////////
// Where the size is known at compile time, the compiler may emit calls to
// specialised versions of the above functions.
////////////////////////////////////////////////////////////////////////////////
#ifdef __SIZEOF_INT128__
#define OPTIMISED_CASES                                                        \
  OPTIMISED_CASE(1, IS_LOCK_FREE_1, uint8_t)                                   \
  OPTIMISED_CASE(2, IS_LOCK_FREE_2, uint16_t)                                  \
  OPTIMISED_CASE(4, IS_LOCK_FREE_4, uint32_t)                                  \
  OPTIMISED_CASE(8, IS_LOCK_FREE_8, uint64_t)                                  \
  OPTIMISED_CASE(16, IS_LOCK_FREE_16, __uint128_t)
#else
#define OPTIMISED_CASES                                                        \
  OPTIMISED_CASE(1, IS_LOCK_FREE_1, uint8_t)                                   \
  OPTIMISED_CASE(2, IS_LOCK_FREE_2, uint16_t)                                  \
  OPTIMISED_CASE(4, IS_LOCK_FREE_4, uint32_t)                                  \
  OPTIMISED_CASE(8, IS_LOCK_FREE_8, uint64_t)
#endif

#ifdef __clang__
#define ATOMIC_NAME(name) name
#else
// See above: GCC gets these functions with a _c suffix too.
#define ATOMIC_NAME(name) name##_c
#define OPTIMISED_CASE(n, lockfree, type)                                      \
  ATOMIC_DECL(type, __atomic_load_##n, (type *, int));                         \
  ATOMIC_DECL(void, __atomic_store_##n, (type *, type, int));                  \
  ATOMIC_DECL(type, __atomic_exchange_##n, (type *, type, int));               \
  ATOMIC_DECL(bool, __atomic_compare_exchange_##n,                             \
              (type *, type *, type, int, int));                               \
  ATOMIC_DECL(type, __atomic_fetch_add_##n, (type *, type, int));              \
  ATOMIC_DECL(type, __atomic_fetch_sub_##n, (type *, type, int));              \
  ATOMIC_DECL(type, __atomic_fetch_and_##n, (type *, type, int));              \
  ATOMIC_DECL(type, __atomic_fetch_or_##n, (type *, type, int));               \
  ATOMIC_DECL(type, __atomic_fetch_xor_##n, (type *, type, int));              \
  ATOMIC_DECL(type, __atomic_fetch_nand_##n, (type *, type, int));
OPTIMISED_CASES
#undef OPTIMISED_CASE
#endif

// clang-format off
#define OPTIMISED_CASE(n, lockfree, type)                                      \
  type ATOMIC_NAME(__atomic_load_##n)(type *src, int model) {                  \
    if (lockfree(src))                                                         \
      return __c11_atomic_load((_Atomic(type) *)src, model);                   \
    Lock *l = lock_for_pointer(src);                                           \
    lock(l);                                                                   \
    type val = *src;                                                           \
    unlock(l);                                                                 \
    return val;                                                                \
  }
OPTIMISED_CASES
#undef OPTIMISED_CASE

#define OPTIMISED_CASE(n, lockfree, type)                                      \
  void ATOMIC_NAME(__atomic_store_##n)(type *dest, type val, int model) {      \
    if (lockfree(dest)) {                                                      \
      __c11_atomic_store((_Atomic(type) *)dest, val, model);                   \
      return;                                                                  \
    }                                                                          \
    Lock *l = lock_for_pointer(dest);                                          \
    lock(l);                                                                   \
    *dest = val;                                                               \
    unlock(l);                                                                 \
    return;                                                                    \
  }
OPTIMISED_CASES
#undef OPTIMISED_CASE

#define OPTIMISED_CASE(n, lockfree, type)                                      \
  type ATOMIC_NAME(__atomic_exchange_##n)(type *dest, type val, int model) {   \
    if (lockfree(dest))                                                        \
      return __c11_atomic_exchange((_Atomic(type) *)dest, val, model);         \
    Lock *l = lock_for_pointer(dest);                                          \
    lock(l);                                                                   \
    type tmp = *dest;                                                          \
    *dest = val;                                                               \
    unlock(l);                                                                 \
    return tmp;                                                                \
  }
OPTIMISED_CASES
#undef OPTIMISED_CASE

#define OPTIMISED_CASE(n, lockfree, type)                                      \
  bool ATOMIC_NAME(__atomic_compare_exchange_##n)(type *ptr, type *expected,   \
                                                  type desired, int success,   \
                                                  int failure) {               \
    if (lockfree(ptr))                                                         \
      return __c11_atomic_compare_exchange_strong(                             \
          (_Atomic(type) *)ptr, expected, desired, success, failure);          \
    Lock *l = lock_for_pointer(ptr);                                           \
    lock(l);                                                                   \
    if (*ptr == *expected) {                                                   \
      *ptr = desired;                                                          \
      unlock(l);                                                               \
      return true;                                                             \
    }                                                                          \
    *expected = *ptr;                                                          \
    unlock(l);                                                                 \
    return false;                                                              \
  }
OPTIMISED_CASES
#undef OPTIMISED_CASE

////////////////////////////////////////////////////////////////////////////////
// Atomic read-modify-write operations for integers of various sizes.
////////////////////////////////////////////////////////////////////////////////
#define ATOMIC_RMW(n, lockfree, type, opname, op)                              \
  type ATOMIC_NAME(__atomic_fetch_##opname##_##n)(type *ptr, type val,         \
                                                  int model) {                 \
    if (lockfree(ptr))                                                         \
      return __c11_atomic_fetch_##opname((_Atomic(type) *)ptr, val, model);    \
    Lock *l = lock_for_pointer(ptr);                                           \
    lock(l);                                                                   \
    type tmp = *ptr;                                                           \
    *ptr = tmp op val;                                                         \
    unlock(l);                                                                 \
    return tmp;                                                                \
  }

#define ATOMIC_RMW_NAND(n, lockfree, type)                                     \
  type ATOMIC_NAME(__atomic_fetch_nand_##n)(type *ptr, type val, int model) {  \
    if (lockfree(ptr))                                                         \
      return __c11_atomic_fetch_nand((_Atomic(type) *)ptr, val, model);        \
    Lock *l = lock_for_pointer(ptr);                                           \
    lock(l);                                                                   \
    type tmp = *ptr;                                                           \
    *ptr = ~(tmp & val);                                                       \
    unlock(l);                                                                 \
    return tmp;                                                                \
  }
// clang-format on

#define OPTIMISED_CASE(n, lockfree, type) ATOMIC_RMW(n, lockfree, type, add, +)
OPTIMISED_CASES
#undef OPTIMISED_CASE
#define OPTIMISED_CASE(n, lockfree, type) ATOMIC_RMW(n, lockfree, type, sub, -)
OPTIMISED_CASES
#undef OPTIMISED_CASE
#define OPTIMISED_CASE(n, lockfree, type) ATOMIC_RMW(n, lockfree, type, and, &)
OPTIMISED_CASES
#undef OPTIMISED_CASE
#define OPTIMISED_CASE(n, lockfree, type) ATOMIC_RMW(n, lockfree, type, or, |)
OPTIMISED_CASES
#undef OPTIMISED_CASE
#define OPTIMISED_CASE(n, lockfree, type) ATOMIC_RMW(n, lockfree, type, xor, ^)
OPTIMISED_CASES
#undef OPTIMISED_CASE
// Allow build with clang without __c11_atomic_fetch_nand builtin (pre-14)
// and with GCC, which has it.
#ifdef __clang__
#define HAS_ATOMIC_FETCH_NAND __has_builtin(__c11_atomic_fetch_nand)
#else
#define HAS_ATOMIC_FETCH_NAND 1
#endif
#if HAS_ATOMIC_FETCH_NAND
#define OPTIMISED_CASE(n, lockfree, type) ATOMIC_RMW_NAND(n, lockfree, type)
OPTIMISED_CASES
#undef OPTIMISED_CASE
#endif

#undef memcpy
#undef memcmp
#undef SPINLOCK_COUNT
#undef ATOMIC_ALWAYS_LOCK_FREE_OR_ALIGNED_LOCK_FREE
#undef IS_LOCK_FREE_1
#undef IS_LOCK_FREE_2
#undef IS_LOCK_FREE_4
#undef IS_LOCK_FREE_8
#undef IS_LOCK_FREE_16
#undef TRY_LOCK_FREE_CASE
#undef TRY_LOCK_FREE_CASE_16
#undef LOCK_FREE_CASES
#undef OPTIMISED_CASES
#undef ATOMIC_RMW
#undef ATOMIC_RMW_NAND
#undef ATOMIC_NAME
#undef HAS_ATOMIC_FETCH_NAND
#ifndef __clang__
#undef __c11_atomic_load
#undef __c11_atomic_store
#undef __c11_atomic_exchange
#undef __c11_atomic_compare_exchange_strong
#undef __c11_atomic_compare_exchange_weak
#undef __c11_atomic_fetch_add
#undef __c11_atomic_fetch_sub
#undef __c11_atomic_fetch_and
#undef __c11_atomic_fetch_or
#undef __c11_atomic_fetch_xor
#undef __c11_atomic_fetch_nand
#undef ATOMIC_STR_
#undef ATOMIC_STR
#undef ATOMIC_DECL
#endif

#pragma GCC diagnostic pop

#endif

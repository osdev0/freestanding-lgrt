//===-- atomic_thread_fence.c ---------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
// 2026/10/17 - Modified by Mintsuki for use inside cc-runtime
//
//===----------------------------------------------------------------------===//
//
// This file implements atomic_thread_fence from C11's stdatomic.h.
//
//===----------------------------------------------------------------------===//

#ifndef __has_include
#define __has_include(inc) 0
#endif

// Built as C11 or later, where atomic.c is, except with GCC on ARM before v6K.
//
// Workaround: GCC 6 up to at least 14, ARM before v6K: up to 13, it makes a
// byte test-and-set a plain load and store, which is not atomic, and from 14
// on, a call to a library function.
#if __has_include(<stdatomic.h>) && defined(__STDC_VERSION__) &&               \
    __STDC_VERSION__ >= 201112L &&                                             \
    (defined(__clang__) || defined(__GNUC__)) &&                               \
    !(!defined(__clang__) && __GNUC__ < 5) &&                                  \
    __GCC_ATOMIC_POINTER_LOCK_FREE == 2 &&                                     \
    !(defined(__i386__) && !defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_4)) &&    \
    !(defined(__arm__) &&                                                      \
      (__ARM_ARCH < 6 ||                                                       \
       (defined(__thumb__) && !defined(__thumb2__) && __ARM_ARCH < 8))) &&     \
    !(defined(__arm__) && defined(__clang__) &&                                \
      defined(__ARM_FEATURE_LDREX) && !(__ARM_FEATURE_LDREX & 1)) &&           \
    !(defined(__arm__) && !defined(__clang__) &&                               \
      !defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_1)) &&                         \
    !(defined(__loongarch__) && __loongarch_grlen == 32 &&                     \
      (!defined(__clang__) || __clang_major__ < 21))

#include <stdatomic.h>
#undef atomic_thread_fence
void atomic_thread_fence(memory_order order) { __atomic_thread_fence(order); }

#endif

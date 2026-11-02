/* SPDX-License-Identifier: 0BSD */

/* Copyright (C) 2026 Mintsuki and contributors.
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
 * OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#if defined(__cplusplus)
#   error "Please do not compile freestanding-lgrt as C++ code! Compile it as C99 or newer."
#elif !defined(__STDC_VERSION__) || __STDC_VERSION__ < 199901L
#   error "Compile freestanding-lgrt as C99 or newer."
#elif !defined(__GNUC__) && !defined(__clang__)
#   error "Compile freestanding-lgrt with GCC or Clang."
#elif (defined(__clang__) && __clang_major__ < 6) \
   || (!defined(__clang__) && (__GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ < 8)))
#   error "Compile freestanding-lgrt with GCC 4.8 or later, or Clang 6 or later."
#endif

// Options, to define when building this file:
//
// FREESTANDING_LGRT_ENABLE_FLOAT adds all that has to do with floating point,
// as far as the flags of the build allow it: the routines of binary and
// decimal formats and of complex values, conversions of integers, fixed point,
// and _BitInt to and from those, __atomic_feraiseexcept, and the routines that
// save floating-point registers. Without it, what there is uses no
// floating-point type or instruction of its own, though the compiler may still
// choose such registers where its flags allow it.
//
// FREESTANDING_LGRT_ENABLE_SIMD adds what is written with SIMD instructions:
// PowerPC's routines that save the registers of AltiVec. Without it, the
// compiler may still choose such registers where its flags allow it, and
// values of floating-point types arrive in them where the ABI has them there.
//
// What needs what these add fails to link without them.
//
// FREESTANDING_LGRT_DISABLE_LIBC_FUNCS leaves out the functions of the C
// library: those of <stdatomic.h> and <stdbit.h>.
//
// The other macros are internal: they follow from these, the compiler, and the
// target, and are not for defining.

// Known issues of compilers, and what to do about them when building this:
//
// Clang 12 at -Oz miscompiles code that its machine outliner factors out for
// ARM M-profile targets: build with -mno-outline there.
//
// On MIPS64, and on SPARC64 with Clang before 21, GCC and Clang pass __int128
// arguments differently: build this with the same compiler as the code that
// calls its 16-byte atomic routines.

// Workaround: GCC 12, SuperH: it miscompiles conditional branches when
// optimising, so the file is built without optimisation there.
#if !defined(__clang__) && defined(__sh__) && __GNUC__ == 12
#   pragma GCC optimize("O0")
#endif

// Nothing declares the routines, as only compilers call them, by name, nor the
// variables, which compilers and programs reach likewise.
#pragma GCC diagnostic ignored "-Wmissing-prototypes"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#if defined(__clang__) || __GNUC__ >= 14
#   pragma GCC diagnostic ignored "-Wmissing-variable-declarations"
#endif

#include <float.h>
#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// For what only assembly calls, which compilers cannot see.
#define ASM_CALLED __attribute__((__used__)) static

#if defined(__ARM_EABI__)
#   define AAPCS __attribute__((__pcs__("aapcs")))
#else
#   define AAPCS
#endif

#if defined(__SIZEOF_INT128__)
#define HAS_INT128 1
__extension__ typedef __int128 i128;
__extension__ typedef unsigned __int128 u128;
#else
#define HAS_INT128 0
#endif

#define STR(x) #x
#define XSTR(x) STR(x)

// AVR and MSP430 have no instruction that traps, and GCC calls abort there, so
// these spin.
//
// Workaround: Clang before 10, RISC-V; Clang before 9, Hexagon; GCC, SuperH,
// OpenRISC, MicroBlaze, Xtensa, and ARC; GCC 4.8, AArch64 and ARM:
// __builtin_trap() becomes a call to abort or an instruction that does not
// trap, so these execute one that traps instead, and spin in case it does not.
#if defined(__AVR__) || defined(__MSP430__)
#   define TRAP() do { \
        for (;;) {} \
    } while (0)
#elif defined(__clang__)
#   if defined(__riscv) && __clang_major__ < 10
#       define TRAP() do { \
            __asm__ volatile ("unimp"); \
            for (;;) {} \
        } while (0)
#   elif defined(__hexagon__) && __clang_major__ < 9
// A misaligned load from an unmapped address, the address kept in memory as
// Clang 8 rejects a misaligned constant one.
#       define TRAP() do { \
            volatile uint64_t *volatile TRAP_address = (volatile uint64_t *)0xbadc0fee; \
            \
            (void)*TRAP_address; \
            for (;;) {} \
        } while (0)
#   endif
#elif defined(__sh__)
#   define TRAP() do { \
        __asm__ volatile (".word 0xfffd"); \
        for (;;) {} \
    } while (0)
#elif defined(__or1k__)
// The bit of SR it names is the one that is always set, as the instruction
// tests that bit in the older versions of the architecture.
#   define TRAP() do { \
        __asm__ volatile ("l.trap 15"); \
        for (;;) {} \
    } while (0)
#elif defined(__MICROBLAZE__)
// A load from an unmapped address, as the illegal instruction exception is an
// option of the cores.
#   define TRAP() do { \
        (void)*(volatile uint32_t *)0xffffefee; \
        for (;;) {} \
    } while (0)
#elif defined(__XTENSA__)
#   define TRAP() do { \
        __asm__ volatile ("ill"); \
        for (;;) {} \
    } while (0)
#elif defined(__ARC600__) || defined(__ARC601__)
#   define TRAP() do { \
        __asm__ volatile ("swi"); \
        for (;;) {} \
    } while (0)
#elif defined(__arc__)
#   define TRAP() do { \
        __asm__ volatile ("trap_s 5"); \
        for (;;) {} \
    } while (0)
#elif __GNUC__ == 4 && __GNUC_MINOR__ == 8
#   if defined(__aarch64__)
#       define TRAP() do { \
            __asm__ volatile ("brk #1000"); \
            for (;;) {} \
        } while (0)
#   elif defined(__arm__)
// The udf instruction, encoded by hand, as old assemblers lack the mnemonic.
#       if defined(__thumb__)
#           define TRAP() do { \
                __asm__ volatile (".inst.n 0xdeff"); \
                for (;;) {} \
            } while (0)
#       else
#           define TRAP() do { \
                __asm__ volatile (".inst 0xe7f000f0"); \
                for (;;) {} \
            } while (0)
#       endif
#   endif
#endif // defined(__AVR__) || defined(__MSP430__)

#if !defined(TRAP)
#   define TRAP() do { \
        __builtin_trap(); \
    } while (0)
#endif

// The compiler's bit-counting and byte-swapping builtins can compile into
// calls to the routines below, so these must never use them.

static inline uint32_t clz32(uint32_t x) {
    uint32_t n = 0;
    uint32_t s;

    s = (uint32_t)(x < 0x00010000) << 4;
    x <<= s;
    n += s;
    s = (uint32_t)(x < 0x01000000) << 3;
    x <<= s;
    n += s;
    s = (uint32_t)(x < 0x10000000) << 2;
    x <<= s;
    n += s;
    s = (uint32_t)(x < 0x40000000) << 1;
    x <<= s;
    n += s;
    // At this point, the leading one, if any, is in one of the top two bits.
    return n + (uint32_t)(x < (uint32_t)0x80000000) + (uint32_t)(x == 0);
}

static inline uint32_t clz64(uint64_t x) {
    uint32_t hi = (uint32_t)(x >> 32);
    uint32_t lo = (uint32_t)x;
    uint32_t z = (uint32_t)(hi == 0);

    // Search lo if hi is zero, else hi.
    return (z << 5) + clz32(hi | (lo & ((uint32_t)0 - z)));
}

// Those of AVR with special conventions are assembly, further on.
#if !defined(__AVR__)
int __clzsi2(int32_t a) {
    return (int)clz32((uint32_t)a);
}
#endif

int __clzdi2(int64_t a) {
    return (int)clz64((uint64_t)a);
}

#if HAS_INT128
static inline uint32_t clz128(u128 x) {
    uint64_t hi = (uint64_t)(x >> 64);
    uint64_t lo = (uint64_t)x;
    uint64_t z = (uint64_t)(hi == 0);

    return ((uint32_t)z << 6) + clz64(hi | (lo & ((uint64_t)0 - z)));
}

int __clzti2(i128 a) {
    return (int)clz128((u128)a);
}
#endif

static inline uint32_t ctz32(uint32_t x) {
    uint32_t n = 0;
    uint32_t s;

    s = (uint32_t)((x & 0x0000ffff) == 0) << 4;
    x >>= s;
    n += s;
    s = (uint32_t)((x & 0x000000ff) == 0) << 3;
    x >>= s;
    n += s;
    s = (uint32_t)((x & 0x0000000f) == 0) << 2;
    x >>= s;
    n += s;
    s = (uint32_t)((x & 0x00000003) == 0) << 1;
    x >>= s;
    n += s;
    // At this point, the lowest one, if any, is in one of the bottom two bits.
    return n + (uint32_t)((x & 1) == 0) + (uint32_t)(x == 0);
}

static inline uint32_t ctz64(uint64_t x) {
    uint32_t lo = (uint32_t)x;
    uint32_t hi = (uint32_t)(x >> 32);
    uint32_t z = (uint32_t)(lo == 0);

    // Search hi if lo is zero, else lo.
    return (z << 5) + ctz32(lo | (hi & ((uint32_t)0 - z)));
}

#if !defined(__AVR__)
int __ctzsi2(int32_t a) {
    return (int)ctz32((uint32_t)a);
}
#endif

int __ctzdi2(int64_t a) {
    return (int)ctz64((uint64_t)a);
}

#if HAS_INT128
static inline uint32_t ctz128(u128 x) {
    uint64_t lo = (uint64_t)x;
    uint64_t hi = (uint64_t)(x >> 64);
    uint64_t z = (uint64_t)(lo == 0);

    return (uint32_t)(z << 6) + ctz64(lo | (hi & ((uint64_t)0 - z)));
}

int __ctzti2(i128 a) {
    return (int)ctz128((u128)a);
}
#endif

#if !defined(__AVR__)
int __ffssi2(int32_t a) {
    uint32_t x = (uint32_t)a;

    if (x == 0) {
        return 0;
    }
    return (int)(ctz32(x) + 1);
}
#endif

int __ffsdi2(int64_t a) {
    uint64_t x = (uint64_t)a;

    if (x == 0) {
        return 0;
    }
    return (int)(ctz64(x) + 1);
}

#if HAS_INT128
int __ffsti2(i128 a) {
    u128 x = (u128)a;

    if (x == 0) {
        return 0;
    }
    return (int)(ctz128(x) + 1);
}
#endif

// The redundant sign bits are the leading zeros, but for the sign bit itself,
// of the value with its complement for a negative one.

int __clrsbsi2(int32_t a) {
    uint32_t x = (uint32_t)a;

    return (int)(clz32(x ^ ((uint32_t)0 - (x >> 31))) - 1);
}

int __clrsbdi2(int64_t a) {
    uint64_t x = (uint64_t)a;

    return (int)(clz64(x ^ ((uint64_t)0 - (x >> 63))) - 1);
}

#if HAS_INT128
int __clrsbti2(i128 a) {
    u128 x = (u128)a;
    u128 y = x ^ ((u128)0 - (x >> 127));
    uint64_t hi = (uint64_t)(y >> 64);
    uint64_t lo = (uint64_t)y;
    uint64_t z = (uint64_t)(hi == 0);

    return (int)((z << 6) + clz64(hi | (lo & ((uint64_t)0 - z))) - 1);
}
#endif

// No multiplications: they are library calls on targets without a multiplier.
// Wider counts add up the per-nibble counts of their parts, which still fit.

static inline uint32_t nibble_popcounts32(uint32_t x) {
    x -= (x >> 1) & 0x55555555;
    return (x & 0x33333333) + ((x >> 2) & 0x33333333);
}

// Each nibble of x must be at most 8.
static inline uint32_t sum_nibbles32(uint32_t x) {
    x = (x & 0x0f0f0f0f) + ((x >> 4) & 0x0f0f0f0f);
    x += x >> 8;
    x += x >> 16;
    return x & 0xff;
}

#if !defined(__AVR__)
int __popcountsi2(int32_t a) {
    return (int)sum_nibbles32(nibble_popcounts32((uint32_t)a));
}
#endif

#if HAS_INT128

// Targets with 128-bit integers have 64-bit registers: count 64 bits at a
// time.

static inline uint64_t nibble_popcounts64(uint64_t x) {
    x -= (x >> 1) & 0x5555555555555555;
    return (x & 0x3333333333333333) + ((x >> 2) & 0x3333333333333333);
}

// Each nibble of x must be at most 8.
static inline uint32_t sum_nibbles64(uint64_t x) {
    x = (x & 0x0f0f0f0f0f0f0f0f) + ((x >> 4) & 0x0f0f0f0f0f0f0f0f);
    x += x >> 8;
    x += x >> 16;
    x += x >> 32;
    return (uint32_t)x & 0xff;
}

int __popcountdi2(int64_t a) {
    return (int)sum_nibbles64(nibble_popcounts64((uint64_t)a));
}

int __popcountti2(i128 a) {
    u128 x = (u128)a;
    uint64_t lo = nibble_popcounts64((uint64_t)x);
    uint64_t hi = nibble_popcounts64((uint64_t)(x >> 64));

    return (int)sum_nibbles64(lo + hi);
}

#else // HAS_INT128

int __popcountdi2(int64_t a) {
    uint64_t x = (uint64_t)a;
    uint32_t lo = nibble_popcounts32((uint32_t)x);
    uint32_t hi = nibble_popcounts32((uint32_t)(x >> 32));

    return (int)sum_nibbles32(lo + hi);
}

#endif // HAS_INT128

static inline uint32_t parity32(uint32_t x) {
    x ^= x >> 16;
    x ^= x >> 8;
    x ^= x >> 4;
    x ^= x >> 2;
    x ^= x >> 1;
    return x & 1;
}

#if !defined(__AVR__)
int __paritysi2(int32_t a) {
    return (int)parity32((uint32_t)a);
}
#endif

int __paritydi2(int64_t a) {
    uint64_t x = (uint64_t)a;

    return (int)parity32((uint32_t)x ^ (uint32_t)(x >> 32));
}

#if HAS_INT128
int __parityti2(i128 a) {
    u128 x = (u128)a;
    uint64_t y = (uint64_t)x ^ (uint64_t)(x >> 64);

    return (int)parity32((uint32_t)y ^ (uint32_t)(y >> 32));
}
#endif

#if !defined(__AVR__) || defined(__AVR_TINY__)

static inline uint32_t bswap32(uint32_t x) {
#if !defined(__clang__) && defined(__XTENSA__) && __GNUC__ >= 13
    // Workaround: GCC 13 to 16, Xtensa: optimising for size, it recognises the
    // swap and calls __bswapsi2 for it, which this is part of, so the swap
    // takes its bytes from two copies of the value, which it cannot tell are
    // equal.
    volatile uint32_t y = x;
#else
    uint32_t y = x;
#endif

    x = ((x >> 8) & 0x00ff00ff) | ((y & 0x00ff00ff) << 8);
    return (x >> 16) | (x << 16);
}

#if !defined(__AVR__)
uint32_t __bswapsi2(uint32_t a) {
    return bswap32(a);
}
#endif

uint64_t __bswapdi2(uint64_t a) {
    uint64_t lo = bswap32((uint32_t)a);
    uint64_t hi = bswap32((uint32_t)(a >> 32));

    return (lo << 32) | hi;
}
#endif // !defined(__AVR__) || defined(__AVR_TINY__)

// Compilers may implement double-word comparisons by calling these routines,
// so they compare single-word halves.

#if !defined(__AVR__) || defined(__AVR_TINY__)
int __cmpdi2(int64_t a, int64_t b) {
    int32_t ah = (int32_t)(a >> 32);
    int32_t bh = (int32_t)(b >> 32);
    uint32_t al = (uint32_t)a;
    uint32_t bl = (uint32_t)b;

    if (ah != bh) {
        return ah < bh ? 0 : 2;
    }
    if (al != bl) {
        return al < bl ? 0 : 2;
    }
    return 1;
}
#endif

#if HAS_INT128
int __cmpti2(i128 a, i128 b) {
    int64_t ah = (int64_t)(a >> 64);
    int64_t bh = (int64_t)(b >> 64);
    uint64_t al = (uint64_t)a;
    uint64_t bl = (uint64_t)b;

    if (ah != bh) {
        return ah < bh ? 0 : 2;
    }
    if (al != bl) {
        return al < bl ? 0 : 2;
    }
    return 1;
}
#endif

int __ucmpdi2(uint64_t a, uint64_t b) {
    uint32_t ah = (uint32_t)(a >> 32);
    uint32_t bh = (uint32_t)(b >> 32);
    uint32_t al = (uint32_t)a;
    uint32_t bl = (uint32_t)b;

    if (ah != bh) {
        return ah < bh ? 0 : 2;
    }
    if (al != bl) {
        return al < bl ? 0 : 2;
    }
    return 1;
}

#if HAS_INT128
int __ucmpti2(u128 a, u128 b) {
    uint64_t ah = (uint64_t)(a >> 64);
    uint64_t bh = (uint64_t)(b >> 64);
    uint64_t al = (uint64_t)a;
    uint64_t bl = (uint64_t)b;

    if (ah != bh) {
        return ah < bh ? 0 : 2;
    }
    if (al != bl) {
        return al < bl ? 0 : 2;
    }
    return 1;
}
#endif

// Negate as unsigned, as -a overflows for the most negative value.

#if !defined(__AVR__) || defined(__AVR_TINY__)
int64_t __negdi2(int64_t a) {
    return (int64_t)((uint64_t)0 - (uint64_t)a);
}
#endif

#if HAS_INT128
i128 __negti2(i128 a) {
    return (i128)((u128)0 - (u128)a);
}
#endif

// Variable double-word shifts can compile into calls to these routines, so
// they shift single-word halves. No shift may reach the width of its operand:
// the count is masked, and bits crossing between the halves move in two steps,
// as the masked count may be zero. Signed right shifts are arithmetic with GCC
// and Clang. The count is a byte on AVR, where what follows it is undefined.

#if defined(__AVR__)
typedef uint8_t shift_count;
#else
typedef int shift_count;
#endif

// AVR has a convention of its own for these, but for its reduced cores, for
// which the routines further on call these under other names. MSP430 has names
// and a convention of its own too, which further on call these as they are.
#if defined(__AVR__) && !defined(__AVR_TINY__)
#   define SHIFT_NAME(name) avr##name
#   define SHIFT_ATTRIBUTE ASM_CALLED
#else
#   define SHIFT_NAME(name) name
#   define SHIFT_ATTRIBUTE
#endif

// The reduced AVR cores, and GCC 4.9 for MSP430, call these for shifts by 32
// too, so they split and join their values in memory there. The other AVR
// cores do it too, where a shift would be a call.
#if defined(__AVR__) || defined(__MSP430__)
union words_64 {
    uint64_t whole;
    uint32_t words[2];
};

#define HIGH_32(x) (((union words_64){ .whole = (x) }).words[1])
#define JOIN_32(hi, lo) (((union words_64){ .words = { (lo), (hi) } }).whole)
#else
#define HIGH_32(x) ((uint32_t)((x) >> 32))
#define JOIN_32(hi, lo) (((uint64_t)(hi) << 32) | (lo))
#endif

SHIFT_ATTRIBUTE int64_t SHIFT_NAME(__ashldi3)(int64_t a, shift_count b) {
    uint64_t x = (uint64_t)a;
    uint32_t lo = (uint32_t)x;
    uint32_t hi = HIGH_32(x);
    uint32_t n = (uint32_t)b;
    uint32_t s = n & 31;

    if ((n & 32) != 0) {
        hi = lo << s;
        lo = 0;
    } else {
        hi = (hi << s) | ((lo >> 1) >> (31 - s));
        lo <<= s;
    }
    return (int64_t)JOIN_32(hi, lo);
}

#if HAS_INT128
i128 __ashlti3(i128 a, int b) {
    u128 x = (u128)a;
    uint64_t lo = (uint64_t)x;
    uint64_t hi = (uint64_t)(x >> 64);
    uint32_t n = (uint32_t)b;
    uint32_t s = n & 63;

    if ((n & 64) != 0) {
        hi = lo << s;
        lo = 0;
    } else {
        hi = (hi << s) | ((lo >> 1) >> (63 - s));
        lo <<= s;
    }
    return (i128)(((u128)hi << 64) | lo);
}
#endif

SHIFT_ATTRIBUTE int64_t SHIFT_NAME(__ashrdi3)(int64_t a, shift_count b) {
    uint64_t x = (uint64_t)a;
    uint32_t lo = (uint32_t)x;
    uint32_t hi = HIGH_32(x);
    uint32_t n = (uint32_t)b;
    uint32_t s = n & 31;

    if ((n & 32) != 0) {
        lo = (uint32_t)((int32_t)hi >> s);
        hi = (uint32_t)((int32_t)hi >> 31);
    } else {
        lo = (lo >> s) | ((hi << 1) << (31 - s));
        hi = (uint32_t)((int32_t)hi >> s);
    }
    return (int64_t)JOIN_32(hi, lo);
}

#if HAS_INT128
i128 __ashrti3(i128 a, int b) {
    u128 x = (u128)a;
    uint64_t lo = (uint64_t)x;
    uint64_t hi = (uint64_t)(x >> 64);
    uint32_t n = (uint32_t)b;
    uint32_t s = n & 63;

    if ((n & 64) != 0) {
        lo = (uint64_t)((int64_t)hi >> s);
        hi = (uint64_t)((int64_t)hi >> 63);
    } else {
        lo = (lo >> s) | ((hi << 1) << (63 - s));
        hi = (uint64_t)((int64_t)hi >> s);
    }
    return (i128)(((u128)hi << 64) | lo);
}
#endif

SHIFT_ATTRIBUTE int64_t SHIFT_NAME(__lshrdi3)(int64_t a, shift_count b) {
    uint64_t x = (uint64_t)a;
    uint32_t lo = (uint32_t)x;
    uint32_t hi = HIGH_32(x);
    uint32_t n = (uint32_t)b;
    uint32_t s = n & 31;

    if ((n & 32) != 0) {
        lo = hi >> s;
        hi = 0;
    } else {
        lo = (lo >> s) | ((hi << 1) << (31 - s));
        hi >>= s;
    }
    return (int64_t)JOIN_32(hi, lo);
}

#if HAS_INT128
i128 __lshrti3(i128 a, int b) {
    u128 x = (u128)a;
    uint64_t lo = (uint64_t)x;
    uint64_t hi = (uint64_t)(x >> 64);
    uint32_t n = (uint32_t)b;
    uint32_t s = n & 63;

    if ((n & 64) != 0) {
        lo = hi >> s;
        hi = 0;
    } else {
        lo = (lo >> s) | ((hi << 1) << (63 - s));
        hi >>= s;
    }
    return (i128)(((u128)hi << 64) | lo);
}
#endif

#if __SIZEOF_POINTER__ == 8 || __SIZEOF_LONG__ == 8
#   define LGRT_64BIT 1
#else
#   define LGRT_64BIT 0
#endif

// Compilers call these where there is no multiply instruction, so they shift
// and add, with the smaller operand as the multiplier to end the loop sooner.
// On 64-bit targets, compilers call __muldi3 even for 32-bit multiplications.
//
// Workaround: GCC 14 to 16, ARC EM and HS without a multiplier, optimising for
// size: it makes a multiplication by the bit out of its mask, and calls the
// function that this is part of, for ever, so it is not told that the mask is
// of one bit.

#define HIDE_BIT(bit) __asm__ ("" : "+r"(bit))

// What startup code runs on, with the data of a stack guard not yet there.
#if defined(__clang__)
#   if __clang_major__ >= 7
#       define NO_STACK_PROTECTOR __attribute__((__no_stack_protector__))
#   else
#       define NO_STACK_PROTECTOR
#   endif
#elif __GNUC__ >= 11
#   define NO_STACK_PROTECTOR __attribute__((__no_stack_protector__))
#else
#   define NO_STACK_PROTECTOR __attribute__((__optimize__("no-stack-protector")))
#endif

#if !defined(__AVR__) || defined(__AVR_TINY__) || !defined(__AVR_HAVE_MUL__)
static inline uint32_t shift_add_mul32(uint32_t a, uint32_t b) {
    uint32_t small = a < b ? a : b;
    uint32_t big = a < b ? b : a;
    uint32_t r = 0;

    while (small != 0) {
        uint8_t bit = (uint8_t)(small & 1);

        HIDE_BIT(bit);
        r += big & ((uint32_t)0 - (uint32_t)bit);
        big <<= 1;
        small >>= 1;
    }
    return r;
}
#endif

#if !defined(__AVR__) || defined(__AVR_TINY__)

int32_t __mulsi3(int32_t a, int32_t b) {
    return (int32_t)shift_add_mul32((uint32_t)a, (uint32_t)b);
}

#endif

#if LGRT_64BIT

static inline uint64_t shift_add_mul64(uint64_t a, uint64_t b) {
    uint64_t small = a < b ? a : b;
    uint64_t big = a < b ? b : a;
    uint64_t r = 0;

    while (small != 0) {
        uint8_t bit = (uint8_t)(small & 1);

        HIDE_BIT(bit);
        r += big & ((uint64_t)0 - (uint64_t)bit);
        big <<= 1;
        small >>= 1;
    }
    return r;
}

int64_t __muldi3(int64_t a, int64_t b) {
    return (int64_t)shift_add_mul64((uint64_t)a, (uint64_t)b);
}

#else // LGRT_64BIT

// A widening multiplication could compile into a call to __muldi3, so the
// product comes from 16-bit pieces. Neither middle sum can overflow, as (2^16
// - 1)^2 + 2^16 - 1 < 2^32.
static inline uint64_t wide_mul32(uint32_t a, uint32_t b) {
    uint32_t a0 = a & 0xffff;
    uint32_t a1 = a >> 16;
    uint32_t b0 = b & 0xffff;
    uint32_t b1 = b >> 16;
    uint32_t p00 = a0 * b0;
    uint32_t m1 = a1 * b0 + (p00 >> 16);
    uint32_t m2 = a0 * b1 + (m1 & 0xffff);
    uint32_t hi = a1 * b1 + (m1 >> 16) + (m2 >> 16);
    uint32_t lo = (m2 << 16) | (p00 & 0xffff);

    return ((uint64_t)hi << 32) | lo;
}

int64_t __muldi3(int64_t a, int64_t b) {
    uint64_t x = (uint64_t)a;
    uint64_t y = (uint64_t)b;
    uint32_t xl = (uint32_t)x;
    uint32_t yl = (uint32_t)y;
    uint32_t cross = (uint32_t)(x >> 32) * yl + xl * (uint32_t)(y >> 32);

    // The cross terms only reach the high half.
    return (int64_t)(wide_mul32(xl, yl) + ((uint64_t)cross << 32));
}

#if defined(__XTENSA__)
// GCC for Xtensa calls this for the 64-bit products of 32-bit operands where
// the core has no instruction for their high half.
uint64_t __umulsidi3(uint32_t a, uint32_t b) {
    return wide_mul32(a, b);
}
#endif

#endif // LGRT_64BIT

#if HAS_INT128

// A 64 by 64 to 128-bit multiplication could compile into a call to __multi3,
// so the product comes from 32-bit pieces. Neither middle sum can overflow, as
// (2^32 - 1)^2 + 2^32 - 1 < 2^64.
static inline u128 wide_mul64(uint64_t a, uint64_t b) {
    uint64_t a0 = a & 0xffffffff;
    uint64_t a1 = a >> 32;
    uint64_t b0 = b & 0xffffffff;
    uint64_t b1 = b >> 32;
    uint64_t p00 = a0 * b0;
    uint64_t m1 = a1 * b0 + (p00 >> 32);
    uint64_t m2 = a0 * b1 + (m1 & 0xffffffff);
    uint64_t hi = a1 * b1 + (m1 >> 32) + (m2 >> 32);
    uint64_t lo = (m2 << 32) | (p00 & 0xffffffff);

    return ((u128)hi << 64) | lo;
}

i128 __multi3(i128 a, i128 b) {
    u128 x = (u128)a;
    u128 y = (u128)b;
    uint64_t xl = (uint64_t)x;
    uint64_t yl = (uint64_t)y;
    uint64_t cross = (uint64_t)(x >> 64) * yl + xl * (uint64_t)(y >> 64);

    // The cross terms only reach the high half.
    return (i128)(wide_mul64(xl, yl) + ((u128)cross << 64));
}

#endif // HAS_INT128

// With -ftrapv, signed arithmetic can compile into calls to the routines
// below, so they, and everything they call, compute on unsigned values.
//
// Products of magnitudes overflow if both have a nonzero high half. Otherwise,
// the smaller magnitude times each half of the larger one gives two partial
// products, whose sum is exact unless the high one exceeds a half word or the
// sum carries out. A negative product may have a magnitude one larger than a
// positive one.

#if LGRT_64BIT

// On 64-bit targets, the product of the sign-extended operands is exact.
static inline uint32_t mulo32(int32_t a, int32_t b, bool *overflow) {
    uint64_t p = (uint64_t)a * (uint64_t)b;

    *overflow = ((p + (uint64_t)0x80000000) >> 32) != 0;
    return (uint32_t)p;
}

#else // LGRT_64BIT

static inline uint32_t mulo32(int32_t a, int32_t b, bool *overflow) {
    uint32_t x = (uint32_t)a;
    uint32_t y = (uint32_t)b;
    uint32_t xs = (uint32_t)0 - (x >> 31);
    uint32_t ys = (uint32_t)0 - (y >> 31);
    uint32_t xm = (x ^ xs) - xs;
    uint32_t ym = (y ^ ys) - ys;
    uint32_t neg = (x ^ y) >> 31;
    uint32_t small;
    uint32_t big;
    uint32_t mid;
    uint32_t low;
    uint32_t p;

    if (xm <= 0xffff) {
        small = xm;
        big = ym;
    } else if (ym <= 0xffff) {
        small = ym;
        big = xm;
    } else {
        *overflow = true;
        return x * y;
    }
    mid = small * (big >> 16);
    low = small * (big & 0xffff);
    p = (mid << 16) + low;
    *overflow = mid > 0xffff || p < low || p > (uint32_t)0x7fffffff + neg;
    return (p ^ ((uint32_t)0 - neg)) + neg;
}

#endif // LGRT_64BIT

int32_t __mulosi4(int32_t a, int32_t b, int *overflow) {
    bool overflowed;
    uint32_t p = mulo32(a, b, &overflowed);

    *overflow = overflowed;
    return (int32_t)p;
}

static inline uint64_t mulo64(int64_t a, int64_t b, bool *overflow) {
    uint64_t x = (uint64_t)a;
    uint64_t y = (uint64_t)b;
    uint64_t xs = (uint64_t)0 - (x >> 63);
    uint64_t ys = (uint64_t)0 - (y >> 63);
    uint64_t xm = (x ^ xs) - xs;
    uint64_t ym = (y ^ ys) - ys;
    uint64_t neg = (x ^ y) >> 63;
    uint32_t small;
    uint64_t big;
    uint64_t mid;
    uint64_t low;
    uint64_t p;

    if ((xm >> 32) == 0) {
        small = (uint32_t)xm;
        big = ym;
    } else if ((ym >> 32) == 0) {
        small = (uint32_t)ym;
        big = xm;
    } else {
        *overflow = true;
        return x * y;
    }
    mid = (uint64_t)small * (uint32_t)(big >> 32);
    low = (uint64_t)small * (uint32_t)big;
    p = (mid << 32) + low;
    *overflow = (mid >> 32) != 0 || p < low || p > (uint64_t)0x7fffffffffffffff + neg;
    return (p ^ ((uint64_t)0 - neg)) + neg;
}

int64_t __mulodi4(int64_t a, int64_t b, int *overflow) {
    bool overflowed;
    uint64_t p = mulo64(a, b, &overflowed);

    *overflow = overflowed;
    return (int64_t)p;
}

#if HAS_INT128

static inline u128 mulo128(i128 a, i128 b, bool *overflow) {
    u128 x = (u128)a;
    u128 y = (u128)b;
    u128 xs = (u128)0 - (x >> 127);
    u128 ys = (u128)0 - (y >> 127);
    u128 xm = (x ^ xs) - xs;
    u128 ym = (y ^ ys) - ys;
    u128 neg = (x ^ y) >> 127;
    uint64_t small;
    u128 big;
    u128 mid;
    u128 low;
    u128 p;

    if ((xm >> 64) == 0) {
        small = (uint64_t)xm;
        big = ym;
    } else if ((ym >> 64) == 0) {
        small = (uint64_t)ym;
        big = xm;
    } else {
        *overflow = true;
        return x * y;
    }
    mid = (u128)small * (uint64_t)(big >> 64);
    low = (u128)small * (uint64_t)big;
    p = (mid << 64) + low;
    // Workaround: GCC 4.8, AArch64: it needs SIMD registers to load 128-bit
    // constants, so this uses none.
    *overflow = (mid >> 64) != 0 || p < low || ((p >> 127) != 0 && (neg == 0 || (p << 1) != 0));
    return (p ^ ((u128)0 - neg)) + neg;
}

i128 __muloti4(i128 a, i128 b, int *overflow) {
    bool overflowed;
    u128 p = mulo128(a, b, &overflowed);

    *overflow = overflowed;
    return (i128)p;
}

#endif // HAS_INT128

int32_t __mulvsi3(int32_t a, int32_t b) {
    bool overflow;
    uint32_t p = mulo32(a, b, &overflow);

    if (overflow) {
        TRAP();
    }
    return (int32_t)p;
}

int64_t __mulvdi3(int64_t a, int64_t b) {
    bool overflow;
    uint64_t p = mulo64(a, b, &overflow);

    if (overflow) {
        TRAP();
    }
    return (int64_t)p;
}

#if HAS_INT128
i128 __mulvti3(i128 a, i128 b) {
    bool overflow;
    u128 p = mulo128(a, b, &overflow);

    if (overflow) {
        TRAP();
    }
    return (i128)p;
}
#endif

// a + b overflows exactly when the sum's sign differs from those of a and b.

int32_t __addvsi3(int32_t a, int32_t b) {
    uint32_t x = (uint32_t)a;
    uint32_t y = (uint32_t)b;
    uint32_t s = x + y;

    if ((((s ^ x) & (s ^ y)) >> 31) != 0) {
        TRAP();
    }
    return (int32_t)s;
}

int64_t __addvdi3(int64_t a, int64_t b) {
    uint64_t x = (uint64_t)a;
    uint64_t y = (uint64_t)b;
    uint64_t s = x + y;

    if ((((s ^ x) & (s ^ y)) >> 63) != 0) {
        TRAP();
    }
    return (int64_t)s;
}

#if HAS_INT128
i128 __addvti3(i128 a, i128 b) {
    u128 x = (u128)a;
    u128 y = (u128)b;
    u128 s = x + y;

    if ((((s ^ x) & (s ^ y)) >> 127) != 0) {
        TRAP();
    }
    return (i128)s;
}
#endif

// a - b overflows exactly when a and b differ in sign and the difference's
// sign differs from that of a.

int32_t __subvsi3(int32_t a, int32_t b) {
    uint32_t x = (uint32_t)a;
    uint32_t y = (uint32_t)b;
    uint32_t d = x - y;

    if ((((x ^ y) & (x ^ d)) >> 31) != 0) {
        TRAP();
    }
    return (int32_t)d;
}

int64_t __subvdi3(int64_t a, int64_t b) {
    uint64_t x = (uint64_t)a;
    uint64_t y = (uint64_t)b;
    uint64_t d = x - y;

    if ((((x ^ y) & (x ^ d)) >> 63) != 0) {
        TRAP();
    }
    return (int64_t)d;
}

#if HAS_INT128
i128 __subvti3(i128 a, i128 b) {
    u128 x = (u128)a;
    u128 y = (u128)b;
    u128 d = x - y;

    if ((((x ^ y) & (x ^ d)) >> 127) != 0) {
        TRAP();
    }
    return (i128)d;
}
#endif

// Without a divide instruction, compilers turn divisions into calls to the
// routines below, at the operands' width but at least 64 bits on 64-bit
// targets, or into calls to target-specific helpers that this file does not
// define. So the routines below use / and % only on narrower operands, and
// only where the target has a divide instruction for those, calling their own
// long division elsewhere. The 32-bit routines never use them, as narrower
// operands are promoted to int, and neither do the 64-bit ones on 64-bit
// targets.
//
// HW_DIV32 tells whether the target has a divide instruction for 32-bit
// operands, and HW_DIV64 whether it has one for 64-bit operands held in single
// registers.

#if defined(__i386__) || defined(__x86_64__) || defined(__aarch64__) \
 || (defined(__arm__) && defined(__ARM_FEATURE_IDIV)) || defined(__mips__) \
 || defined(__powerpc__) || defined(__s390__) || defined(__loongarch__) \
 || (defined(__riscv) && defined(__riscv_div)) || defined(__sparc_v8__) || defined(__sparcv8) \
 || defined(__sparc_v9__) || defined(__sparcv9) || defined(__mc68020__) || defined(__mc68030__) \
 || defined(__mc68040__) || defined(__mc68060__) || defined(__mcfhwdiv__) \
 || defined(__ARC_DIVREM__)
#   define HW_DIV32 1
#else
#   define HW_DIV32 0
#endif

#if defined(__x86_64__) || defined(__aarch64__) || (defined(__mips64) && LGRT_64BIT) \
 || defined(__powerpc64__) || defined(__s390x__) || defined(__loongarch64) \
 || (defined(__riscv) && defined(__riscv_div) && __riscv_xlen == 64) \
 || (defined(__sparc__) && defined(__arch64__))
#   define HW_DIV64 1
#else
#   define HW_DIV64 0
#endif

// Unlike the bit-counting routines, the division routines can use the clz
// builtins. x | 1 has the leading zeros of x, except for zero, for which the
// builtins are undefined.

static inline uint32_t div_clz32(uint32_t x) {
#if __SIZEOF_INT__ < 4
    return (uint32_t)__builtin_clzl((unsigned long)(x | 1));
#else
    return (uint32_t)__builtin_clz((unsigned int)(x | 1));
#endif
}

static inline uint32_t div_clz64(uint64_t x) {
    return (uint32_t)__builtin_clzll((unsigned long long)(x | 1));
}

// Binary long division over the bit positions where the quotient can have set
// bits. Aligning the divisor's top bit with the dividend's keeps the remainder
// below twice the divisor, so each step subtracts at most once.
static inline uint32_t udivmod32(uint32_t a, uint32_t b, uint32_t *rem) {
    uint32_t q = 0;
    uint32_t n;
    uint32_t d;

    if (b > a) {
        *rem = a;
        return 0;
    }
    n = div_clz32(b) - div_clz32(a);
    d = b << n;
    do {
        uint32_t c = (uint32_t)(a >= d);

        a -= d & ((uint32_t)0 - c);
        q = (q << 1) | c;
        d >>= 1;
    } while (n-- != 0);
    *rem = a;
    return q;
}

#if !defined(__AVR__)
uint32_t __udivmodsi4(uint32_t a, uint32_t b, uint32_t *rem) {
    uint32_t r;
    uint32_t q = udivmod32(a, b, &r);

    if (rem != NULL) {
        *rem = r;
    }
    return q;
}
#endif

#if !LGRT_64BIT
static inline uint32_t hw_udivmod32(uint32_t a, uint32_t b, uint32_t *rem) {
#if HW_DIV32
    *rem = a % b;
    return a / b;
#else
    return udivmod32(a, b, rem);
#endif
}
#endif

static inline uint64_t udivmod64(uint64_t a, uint64_t b, uint64_t *rem) {
    uint64_t q = 0;
    uint64_t d;
    uint32_t n;

    if (b > a) {
        *rem = a;
        return 0;
    }
#if !LGRT_64BIT
    if ((a >> 32) == 0) {
        uint32_t r;
        uint32_t q32 = hw_udivmod32((uint32_t)a, (uint32_t)b, &r);

        *rem = r;
        return q32;
    }
#endif
    n = div_clz64(b) - div_clz64(a);
    d = b << n;
    do {
        uint64_t c = (uint64_t)(a >= d);

        a -= d & ((uint64_t)0 - c);
        q = (q << 1) | c;
        d >>= 1;
    } while (n-- != 0);
    *rem = a;
    return q;
}

uint64_t __udivmoddi4(uint64_t a, uint64_t b, uint64_t *rem) {
    uint64_t r;
    uint64_t q = udivmod64(a, b, &r);

    if (rem != NULL) {
        *rem = r;
    }
    return q;
}

#if HAS_INT128

static inline uint64_t hw_udivmod64(uint64_t a, uint64_t b, uint64_t *rem) {
#if HW_DIV64
    *rem = a % b;
    return a / b;
#else
    return udivmod64(a, b, rem);
#endif
}

#if defined(__x86_64__)

// Divides hi:lo by v. As hi < v, the quotient fits in 64 bits, so divq cannot
// fault.
static inline uint64_t udiv128by64(uint64_t hi, uint64_t lo, uint64_t v, uint64_t *rem) {
    uint64_t q;
    uint64_t r;

    __asm__ ("{divq %4|div %4}" : "=a"(q), "=d"(r) : "0"(lo), "1"(hi), "r"(v) : "cc");
    *rem = r;
    return q;
}

#else // defined(__x86_64__)

// A step of Knuth's Algorithm D with 32-bit digits: divides u:next by v, where
// v has its top bit set and u < v, so that the quotient is a single digit. Its
// estimate exceeds it by at most two, and as v has two digits, comparing with
// the low one tells exactly whether the estimate is too large.
static inline uint32_t udiv96by64(uint64_t u, uint32_t next, uint64_t v, uint64_t *rem) {
    uint64_t vh = v >> 32;
    uint64_t vl = v & 0xffffffff;
    uint64_t r;
    uint64_t q = hw_udivmod64(u, vh, &r);

    if ((q >> 32) != 0 || q * vl > ((r << 32) | next)) {
        q--;
        r += vh;
        if ((r >> 32) == 0 && ((q >> 32) != 0 || q * vl > ((r << 32) | next))) {
            q--;
        }
    }
    *rem = (u << 32) + next - q * v;
    return (uint32_t)q;
}

// Divides hi:lo by v, where hi < v, so that the quotient fits in 64 bits.
static inline uint64_t udiv128by64(uint64_t hi, uint64_t lo, uint64_t v, uint64_t *rem) {
    uint32_t s = div_clz64(v);
    uint64_t r;
    uint32_t q1;
    uint32_t q0;

    // Normalise v. s may be zero, so bits move from lo to hi in two shifts.
    v <<= s;
    hi = (hi << s) | ((lo >> 1) >> (63 - s));
    lo <<= s;
    q1 = udiv96by64(hi, (uint32_t)(lo >> 32), v, &r);
    q0 = udiv96by64(r, (uint32_t)lo, v, &r);
    *rem = r >> s;
    return ((uint64_t)q1 << 32) | q0;
}

#endif // defined(__x86_64__)

static inline u128 udivmod128(u128 a, u128 b, u128 *rem) {
    uint64_t ah = (uint64_t)(a >> 64);
    uint64_t al = (uint64_t)a;
    uint64_t bh = (uint64_t)(b >> 64);
    uint64_t bl = (uint64_t)b;
    uint64_t qh = 0;
    uint64_t q;
    uint64_t r;
    u128 d;
    uint32_t n;

    if (b > a) {
        *rem = a;
        return 0;
    }
    if (ah == 0) {
        q = hw_udivmod64(al, bl, &r);
        *rem = r;
        return q;
    }
    if (bh == 0) {
        if (ah >= bl) {
            qh = hw_udivmod64(ah, bl, &ah);
        }
        q = udiv128by64(ah, al, bl, &r);
        *rem = r;
        return ((u128)qh << 64) | q;
    }
    // As b does not fit in 64 bits, the quotient does.
    n = div_clz64(bh) - div_clz64(ah);
    d = b << n;
    q = 0;
    do {
        uint64_t c = (uint64_t)(a >= d);

        a -= d & ((u128)0 - c);
        q = (q << 1) | c;
        d >>= 1;
    } while (n-- != 0);
    *rem = a;
    return q;
}

u128 __udivmodti4(u128 a, u128 b, u128 *rem) {
    u128 r;
    u128 q = udivmod128(a, b, &r);

    if (rem != NULL) {
        *rem = r;
    }
    return q;
}

#endif // HAS_INT128

// SuperH's __udivsi3 is assembly with a special convention, defined further
// on.
#if !defined(__sh__)
uint32_t __udivsi3(uint32_t a, uint32_t b) {
    uint32_t r;

    return udivmod32(a, b, &r);
}
#endif

uint64_t __udivdi3(uint64_t a, uint64_t b) {
    uint64_t r;

    return udivmod64(a, b, &r);
}

#if HAS_INT128
u128 __udivti3(u128 a, u128 b) {
    u128 r;

    return udivmod128(a, b, &r);
}
#endif

uint32_t __umodsi3(uint32_t a, uint32_t b) {
    uint32_t r;

    udivmod32(a, b, &r);
    return r;
}

uint64_t __umoddi3(uint64_t a, uint64_t b) {
    uint64_t r;

    udivmod64(a, b, &r);
    return r;
}

#if HAS_INT128
u128 __umodti3(u128 a, u128 b) {
    u128 r;

    udivmod128(a, b, &r);
    return r;
}
#endif

// Signed division divides the magnitudes as unsigned values, then negates the
// quotient if the signs differ, and the remainder if a is negative. Unsigned
// arithmetic lets the most negative value divided by -1 wrap, and cannot trap
// with -ftrapv.

static inline uint32_t divmod32(int32_t a, int32_t b, uint32_t *rem) {
    uint32_t x = (uint32_t)a;
    uint32_t y = (uint32_t)b;
    uint32_t xs = (uint32_t)0 - (x >> 31);
    uint32_t ys = (uint32_t)0 - (y >> 31);
    uint32_t qs = xs ^ ys;
    uint32_t r;
    uint32_t q = udivmod32((x ^ xs) - xs, (y ^ ys) - ys, &r);

    *rem = (r ^ xs) - xs;
    return (q ^ qs) - qs;
}

int32_t __divsi3(int32_t a, int32_t b) {
    uint32_t r;

    return (int32_t)divmod32(a, b, &r);
}

static inline uint64_t divmod64(int64_t a, int64_t b, uint64_t *rem) {
    uint64_t x = (uint64_t)a;
    uint64_t y = (uint64_t)b;
    uint64_t xs = (uint64_t)0 - (x >> 63);
    uint64_t ys = (uint64_t)0 - (y >> 63);
    uint64_t qs = xs ^ ys;
    uint64_t r;
    uint64_t q = udivmod64((x ^ xs) - xs, (y ^ ys) - ys, &r);

    *rem = (r ^ xs) - xs;
    return (q ^ qs) - qs;
}

int64_t __divdi3(int64_t a, int64_t b) {
    uint64_t r;

    return (int64_t)divmod64(a, b, &r);
}

#if HAS_INT128

static inline u128 divmod128(i128 a, i128 b, u128 *rem) {
    u128 x = (u128)a;
    u128 y = (u128)b;
    u128 xs = (u128)0 - (x >> 127);
    u128 ys = (u128)0 - (y >> 127);
    u128 qs = xs ^ ys;
    u128 r;
    u128 q = udivmod128((x ^ xs) - xs, (y ^ ys) - ys, &r);

    *rem = (r ^ xs) - xs;
    return (q ^ qs) - qs;
}

i128 __divti3(i128 a, i128 b) {
    u128 r;

    return (i128)divmod128(a, b, &r);
}

#endif // HAS_INT128

int32_t __modsi3(int32_t a, int32_t b) {
    uint32_t r;

    divmod32(a, b, &r);
    return (int32_t)r;
}

int64_t __moddi3(int64_t a, int64_t b) {
    uint64_t r;

    divmod64(a, b, &r);
    return (int64_t)r;
}

#if HAS_INT128
i128 __modti3(i128 a, i128 b) {
    u128 r;

    divmod128(a, b, &r);
    return (i128)r;
}
#endif

#if !defined(__AVR__)
int32_t __divmodsi4(int32_t a, int32_t b, int32_t *rem) {
    uint32_t r;
    uint32_t q = divmod32(a, b, &r);

    if (rem != NULL) {
        *rem = (int32_t)r;
    }
    return (int32_t)q;
}
#endif

int64_t __divmoddi4(int64_t a, int64_t b, int64_t *rem) {
    uint64_t r;
    uint64_t q = divmod64(a, b, &r);

    if (rem != NULL) {
        *rem = (int64_t)r;
    }
    return (int64_t)q;
}

#if HAS_INT128
i128 __divmodti4(i128 a, i128 b, i128 *rem) {
    u128 r;
    u128 q = divmod128(a, b, &r);

    if (rem != NULL) {
        *rem = (i128)r;
    }
    return (i128)q;
}
#endif

// With -ftrapv, signed arithmetic compiles into calls to overflow-checking
// routines such as these, so they compute on unsigned values.

int32_t __negvsi2(int32_t a) {
    uint32_t x = (uint32_t)a;

    if (x == (uint32_t)0x80000000) {
        TRAP();
    }
    return (int32_t)((uint32_t)0 - x);
}

int64_t __negvdi2(int64_t a) {
    uint64_t x = (uint64_t)a;

    if (x == (uint64_t)0x8000000000000000) {
        TRAP();
    }
    return (int64_t)((uint64_t)0 - x);
}

#if HAS_INT128
i128 __negvti2(i128 a) {
    u128 x = (u128)a;

    // Workaround: GCC 4.8, AArch64: it needs SIMD registers to load 128-bit
    // constants, so this uses none.
    if ((x >> 127) != 0 && (x << 1) == 0) {
        TRAP();
    }
    return (i128)((u128)0 - x);
}
#endif

// Only the most negative value has a magnitude with the top bit set.

int32_t __absvsi2(int32_t a) {
    uint32_t x = (uint32_t)a;
    uint32_t s = (uint32_t)0 - (x >> 31);
    uint32_t m = (x ^ s) - s;

    if ((m >> 31) != 0) {
        TRAP();
    }
    return (int32_t)m;
}

int64_t __absvdi2(int64_t a) {
    uint64_t x = (uint64_t)a;
    uint64_t s = (uint64_t)0 - (x >> 63);
    uint64_t m = (x ^ s) - s;

    if ((m >> 63) != 0) {
        TRAP();
    }
    return (int64_t)m;
}

#if HAS_INT128
i128 __absvti2(i128 a) {
    u128 x = (u128)a;
    u128 s = (u128)0 - (x >> 127);
    u128 m = (x ^ s) - s;

    if ((m >> 127) != 0) {
        TRAP();
    }
    return (i128)m;
}
#endif

#if __SIZEOF_INT__ == 2

// On targets whose int has 16 bits, -ftrapv checks int arithmetic with these,
// so they compute on 16-bit unsigned values, or on 32-bit ones for products,
// which fit.

int16_t __addvhi3(int16_t a, int16_t b) {
    uint16_t x = (uint16_t)a;
    uint16_t y = (uint16_t)b;
    uint16_t s = x + y;

    if ((((s ^ x) & (s ^ y)) >> 15) != 0) {
        TRAP();
    }
    return (int16_t)s;
}

int16_t __subvhi3(int16_t a, int16_t b) {
    uint16_t x = (uint16_t)a;
    uint16_t y = (uint16_t)b;
    uint16_t d = x - y;

    if ((((x ^ y) & (x ^ d)) >> 15) != 0) {
        TRAP();
    }
    return (int16_t)d;
}

int16_t __mulvhi3(int16_t a, int16_t b) {
    bool overflow;
    uint32_t p = mulo32(a, b, &overflow);

    if (((p + (uint32_t)0x8000) >> 16) != 0) {
        TRAP();
    }
    return (int16_t)p;
}

int16_t __negvhi2(int16_t a) {
    uint16_t x = (uint16_t)a;

    if (x == (uint16_t)0x8000) {
        TRAP();
    }
    return (int16_t)((uint16_t)0 - x);
}

int16_t __absvhi2(int16_t a) {
    uint16_t x = (uint16_t)a;
    uint16_t s = (uint16_t)0 - (x >> 15);
    uint16_t m = (x ^ s) - s;

    if ((m >> 15) != 0) {
        TRAP();
    }
    return (int16_t)m;
}

int __clrsbhi2(int16_t a) {
    uint16_t x = (uint16_t)a;
    uint16_t y = x ^ ((uint16_t)0 - (x >> 15));

    return (int)(clz32(y) - 17);
}

// Those of AVR have special conventions, and are assembly, further on.
#if !defined(__AVR__)

// GCC 4.9 for MSP430 calls these for switches.
int __cmpsi2(int32_t a, int32_t b) {
    return a < b ? 0 : (a > b ? 2 : 1);
}

int __ucmpsi2(uint32_t a, uint32_t b) {
    return a < b ? 0 : (a > b ? 2 : 1);
}

int __clzhi2(uint16_t a) {
    return (int)(clz32(a) - 16);
}

// Bit 16 stops the count at the width for zero.
int __ctzhi2(uint16_t a) {
    return (int)ctz32((uint32_t)a | 0x10000);
}

int __ffshi2(uint16_t a) {
    return a == 0 ? 0 : (int)(ctz32(a) + 1);
}

int __popcounthi2(uint16_t a) {
    return (int)sum_nibbles32(nibble_popcounts32(a));
}

int __parityhi2(uint16_t a) {
    return (int)parity32(a);
}

int16_t __mulhi3(int16_t a, int16_t b) {
    uint16_t x = (uint16_t)a;
    uint16_t y = (uint16_t)b;
    uint16_t r = 0;

    while (y != 0) {
        r += x & ((uint16_t)0 - (y & 1));
        x = (uint16_t)(x + x);
        y >>= 1;
    }
    return (int16_t)r;
}

// The bit that shifting the remainder loses makes it exceed the divisor.
static inline uint16_t udivmod16(uint16_t a, uint16_t b, uint16_t *rem) {
    uint16_t r = 0;
    size_t i;

    for (i = 0; i < 16; i++) {
        bool over = (r >> 15) != 0;

        r = (uint16_t)(r + r) | (a >> 15);
        a = (uint16_t)(a + a);
        if (over || r >= b) {
            r -= b;
            a |= 1;
        }
    }
    *rem = r;
    return a;
}

static inline uint16_t divmod16(int16_t a, int16_t b, uint16_t *rem) {
    uint16_t x = (uint16_t)a;
    uint16_t y = (uint16_t)b;
    uint16_t xs = (uint16_t)0 - (x >> 15);
    uint16_t ys = (uint16_t)0 - (y >> 15);
    uint16_t qs = xs ^ ys;
    uint16_t r;
    uint16_t q = udivmod16((x ^ xs) - xs, (y ^ ys) - ys, &r);

    *rem = (r ^ xs) - xs;
    return (q ^ qs) - qs;
}

uint16_t __udivhi3(uint16_t a, uint16_t b) {
    uint16_t r;

    return udivmod16(a, b, &r);
}

uint16_t __umodhi3(uint16_t a, uint16_t b) {
    uint16_t r;

    udivmod16(a, b, &r);
    return r;
}

int16_t __divhi3(int16_t a, int16_t b) {
    uint16_t r;

    return (int16_t)divmod16(a, b, &r);
}

int16_t __modhi3(int16_t a, int16_t b) {
    uint16_t r;

    divmod16(a, b, &r);
    return (int16_t)r;
}

#endif // !defined(__AVR__)

#endif // __SIZEOF_INT__ == 2

#if defined(__ARM_EABI__)

__attribute__((__alias__("__udivsi3"))) uint32_t __aeabi_uidiv(uint32_t a, uint32_t b);

__attribute__((__alias__("__divsi3"))) int32_t __aeabi_idiv(int32_t a, int32_t b);

// These return the quotient in r0 and the remainder in r1, which hold the low
// and high halves of a 64-bit integer on little-endian targets, and the high
// and low halves on big-endian ones.

static inline uint64_t aeabi_pair(uint32_t r0, uint32_t r1) {
#if defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
    return ((uint64_t)r0 << 32) | r1;
#else
    return ((uint64_t)r1 << 32) | r0;
#endif
}

uint64_t __aeabi_uidivmod(unsigned int a, unsigned int b) {
    uint32_t r;
    uint32_t q = udivmod32(a, b, &r);

    return aeabi_pair(q, r);
}

uint64_t __aeabi_idivmod(int a, int b) {
    uint32_t r;
    uint32_t q = divmod32(a, b, &r);

    return aeabi_pair(q, r);
}

#endif // defined(__ARM_EABI__)

#if defined(__ARM_EABI__)

// The assembly routines below are naked functions, so that the compiler emits
// their symbols. GCC assembles inline assembly in divided syntax and, in older
// versions, its own ARM and Thumb-1 code too, so the assembly switches to
// unified syntax and, with GCC outside Thumb-2, back.

#if defined(__clang__) || defined(__thumb2__)
#   define ASM_END ""
#else
#   define ASM_END ".syntax divided\n\t"
#endif

#if defined(__ARM_FEATURE_BTI_DEFAULT)
#   define ASM_BTI "bti\n\t"
#else
#   define ASM_BTI ""
#endif

// On ARMv4T, popping into pc does not switch between ARM and Thumb state.
#if defined(__ARM_ARCH_4T__) || (defined(__ARM_ARCH) && __ARM_ARCH < 5)
#   define ARM_V4T 1
#else
#   define ARM_V4T 0
#endif

#if defined(__thumb__) && !defined(__thumb2__)
#   define THUMB1 1
#else
#   define THUMB1 0
#endif

// These return the quotient in r0 and r1 and the remainder in r2 and r3, where
// the base procedure call standard returns a vector of 16 bytes, its words in
// the order of memory, which is how a register pair holds a 64-bit value on
// either endianness.
typedef uint32_t aeabi_divmod_vector __attribute__((__vector_size__(16)));

union aeabi_divmod {
    uint64_t parts[2];
    aeabi_divmod_vector vector;
};

AAPCS aeabi_divmod_vector __aeabi_uldivmod(uint64_t a, uint64_t b) {
    union aeabi_divmod result;

    result.parts[0] = __udivmoddi4(a, b, &result.parts[1]);
    return result.vector;
}

AAPCS aeabi_divmod_vector __aeabi_ldivmod(int64_t a, int64_t b) {
    union aeabi_divmod result;

    result.parts[0] = (uint64_t)__divmoddi4(a, b, (int64_t *)&result.parts[1]);
    return result.vector;
}

// The run-time ABI's division by zero handlers, which programs may replace.

__attribute__((__weak__, __visibility__("hidden"))) int __aeabi_idiv0(int return_value) {
    return return_value;
}

__attribute__((__weak__, __visibility__("hidden"))) int64_t __aeabi_ldiv0(int64_t return_value) {
    return return_value;
}

// __cmpdi2 and __ucmpdi2 return one more than these.

int __aeabi_lcmp(int64_t a, int64_t b) {
    return (int)((unsigned int)__cmpdi2(a, b) - 1);
}

int __aeabi_ulcmp(uint64_t a, uint64_t b) {
    return (int)((unsigned int)__ucmpdi2(a, b) - 1);
}

__attribute__((__alias__("__muldi3"))) int64_t __aeabi_lmul(int64_t a, int64_t b);

__attribute__((__alias__("__ashldi3"))) int64_t __aeabi_llsl(int64_t a, int b);

__attribute__((__alias__("__lshrdi3"))) int64_t __aeabi_llsr(int64_t a, int b);

__attribute__((__alias__("__ashrdi3"))) int64_t __aeabi_lasr(int64_t a, int b);

// Compilers can compile calls to memcpy and friends into calls to these, so
// these call them through pointers that are hidden from the compilers.

void *memcpy(void *dest, const void *src, size_t n);
void *memmove(void *dest, const void *src, size_t n);
void *memset(void *dest, int c, size_t n);
int memcmp(const void *a, const void *b, size_t n);

void __aeabi_memcpy(void *dest, const void *src, size_t n) {
    void *(*f)(void *, const void *, size_t) = memcpy;

    HIDE_BIT(f);
    f(dest, src, n);
}

__attribute__((__alias__("__aeabi_memcpy"))) void __aeabi_memcpy4(
    void *dest,
    const void *src,
    size_t n
);

__attribute__((__alias__("__aeabi_memcpy"))) void __aeabi_memcpy8(
    void *dest,
    const void *src,
    size_t n
);

void __aeabi_memmove(void *dest, const void *src, size_t n) {
    void *(*f)(void *, const void *, size_t) = memmove;

    HIDE_BIT(f);
    f(dest, src, n);
}

__attribute__((__alias__("__aeabi_memmove"))) void __aeabi_memmove4(
    void *dest,
    const void *src,
    size_t n
);

__attribute__((__alias__("__aeabi_memmove"))) void __aeabi_memmove8(
    void *dest,
    const void *src,
    size_t n
);

void __aeabi_memset(void *dest, size_t n, int c) {
    void *(*f)(void *, int, size_t) = memset;

    HIDE_BIT(f);
    f(dest, c, n);
}

__attribute__((__alias__("__aeabi_memset"))) void __aeabi_memset4(void *dest, size_t n, int c);

__attribute__((__alias__("__aeabi_memset"))) void __aeabi_memset8(void *dest, size_t n, int c);

void __aeabi_memclr(void *dest, size_t n) {
    void *(*f)(void *, int, size_t) = memset;

    HIDE_BIT(f);
    f(dest, 0, n);
}

__attribute__((__alias__("__aeabi_memclr"))) void __aeabi_memclr4(void *dest, size_t n);

__attribute__((__alias__("__aeabi_memclr"))) void __aeabi_memclr8(void *dest, size_t n);

int __aeabi_memcmp(const void *a, const void *b, size_t n) {
    int (*f)(const void *, const void *, size_t) = memcmp;

    HIDE_BIT(f);
    return f(a, b, n);
}

__attribute__((__alias__("__aeabi_memcmp"))) int __aeabi_memcmp4(
    const void *a,
    const void *b,
    size_t n
);

__attribute__((__alias__("__aeabi_memcmp"))) int __aeabi_memcmp8(
    const void *a,
    const void *b,
    size_t n
);

// These go byte by byte, through volatile accesses that compilers cannot merge
// into the misaligned ones that would call these.

static inline void aeabi_read_bytes(void *value, const void *address, size_t n) {
    unsigned char *d = value;
    const volatile unsigned char *s = address;

    for (size_t i = 0; i < n; i++) {
        d[i] = s[i];
    }
}

static inline void aeabi_write_bytes(void *address, const void *value, size_t n) {
    volatile unsigned char *d = address;
    const unsigned char *s = value;

    for (size_t i = 0; i < n; i++) {
        d[i] = s[i];
    }
}

int32_t __aeabi_uread4(void *address) {
    int32_t value;

    aeabi_read_bytes(&value, address, sizeof(int32_t));
    return value;
}

int64_t __aeabi_uread8(void *address) {
    int64_t value;

    aeabi_read_bytes(&value, address, sizeof(int64_t));
    return value;
}

int32_t __aeabi_uwrite4(int32_t value, void *address) {
    aeabi_write_bytes(address, &value, sizeof(int32_t));
    return value;
}

int64_t __aeabi_uwrite8(int64_t value, void *address) {
    aeabi_write_bytes(address, &value, sizeof(int64_t));
    return value;
}

#endif // defined(__ARM_EABI__)

// AArch64 without its floating-point registers: GCC tells of that with
// __ARM_FP, or __FP_FAST_FMAF before 5, and Clang before 17 only by leaving
// out __ARM_NEON, as it does for no SIMD alone, where nothing calls these
// either.
#if defined(__aarch64__) \
 && ((defined(__clang__) && !defined(__ARM_NEON)) \
  || (!defined(__clang__) && !defined(__ARM_FP) && !defined(__FP_FAST_FMAF)))
#   define AARCH64_NO_FP 1
#else
#   define AARCH64_NO_FP 0
#endif

// A function taking float cannot be declared on x86-64 without SSE, nothing
// telling that Clang can do it with x87 off too, or on AArch64 without its
// floating-point registers.
//
// Workaround: GCC, Alpha: with -mno-fp-regs, it cannot compile a function that
// returns float, and all that tells of that option is __GCC_IEC_559 being 0,
// which GCC 4.8 does not define.
//
// Workaround: GCC before 11, PA-RISC: with -mdisable-fpregs, it cannot compile
// a function that takes or returns float, and nothing tells of that option. So
// these exist there only with -msoft-float, which __GCC_IEC_559 tells of, as
// long as finite maths does not make it say the same.
#if !defined(FREESTANDING_LGRT_ENABLE_FLOAT) || (defined(__x86_64__) && !defined(__SSE__)) \
 || AARCH64_NO_FP || (defined(__alpha__) && (!defined(__GCC_IEC_559) || __GCC_IEC_559 == 0)) \
 || (defined(__hppa__) && __GNUC__ < 11 \
  && (!defined(__GCC_IEC_559) || __GCC_IEC_559 != 0 || __FINITE_MATH_ONLY__ != 0))
#   define LGRT_SOFT_FLOAT 0
#else
#   define LGRT_SOFT_FLOAT 1
#endif

// The format of the x87, which x86-64 has without SSE too, and that of 96 bits
// of m68k, on all but ColdFire, whose long double is 64-bit.
#if defined(FREESTANDING_LGRT_ENABLE_FLOAT) \
 && (defined(__i386__) || defined(__x86_64__) || (defined(__m68k__) && LDBL_MANT_DIG == 64))
#   define SOFT_XF 1
#else
#   define SOFT_XF 0
#endif

// The routines of long double on Alpha pass it in ways that C has no part in,
// and so go on without float and double.
#if defined(FREESTANDING_LGRT_ENABLE_FLOAT) && defined(__alpha__) && LDBL_MANT_DIG == 113
#   define ALPHA_QUAD 1
#else
#   define ALPHA_QUAD 0
#endif

#if LGRT_SOFT_FLOAT || SOFT_XF || ALPHA_QUAD

// The soft-float routines work on bits alone, in the default rounding mode,
// track no exceptions, and handle subnormal numbers in full. The macros below
// generate them for a binary format, from:
//
// fmt, the name of the format in the routines' names; C, the type that passes
// a value of it; T, an unsigned type, no narrower than unsigned int, of W
// bits, that holds its bits and has at least F + 5 bits; E, the width of its
// exponent field, and F, that of its fraction field.
//
// In T, a value has its fraction at the bottom, then its exponent, then its
// sign. A significand being worked on has its integer bit at bit F + 3, above
// a guard bit, a round bit, and a sticky bit, the last of which keeps whether
// any bit below it was lost: enough to round correctly at the end. Products
// come from fp_wide_mulW, and bit counts of integers from clzN.
//
// FMT_to_bits and FMT_from_bits copy the bits between C and T. Compilers could
// recognise what the routines do to bits passed in the open as floating-point
// operations, and call the same routines for those, or load constant results
// with conversions, so the bits are hidden from them. Only a signalling NaN
// returned in an x87 or m68k register changes on the way.
//
// The base procedure call standard of 32-bit ARM, which compilers call these
// with, passes float as it does uint32_t, and double as it does uint64_t, and
// so do AVR and MSP430, by the sizes of arguments. There C is one of those.
// That also lets ARM compile them with -mgeneral-regs-only, where GCC rejects
// floating-point types with nothing to tell of it, and keeps them off the
// floating-point registers. It makes them smaller on the others, and needs no
// copies of bits.

#if defined(__arm__) || defined(__AVR__) || defined(__MSP430__)
#   define FP_PASSED_AS_INT 1
#else
#   define FP_PASSED_AS_INT 0
#endif

// MIPS16 code has no access to the floating-point registers that pass these
// values, and would need helpers for that, so these are not MIPS16 code.
#if defined(__mips16) && defined(__mips_hard_float)
#   define FP_ABI __attribute__((__nomips16__))
#else
#   define FP_ABI AAPCS
#endif

// AVR and MSP430 keep helpers apart, for size, at any optimisation level.
#if defined(__AVR__) || defined(__MSP430__)
#   define FP_HELPER __attribute__((__noinline__)) static
#else
#   define FP_HELPER static inline
#endif

// Another name for a routine, for targets with names of their own.
//
// Workaround: Clang 6, ARM: it rejects an alias attribute that comes before
// that of the calling convention, as if the declaration were a definition.
#define FP_ALIAS(R, name, target, params) FP_ABI __attribute__((__alias__(target))) R name params;

#define FP_SIGN(T, E, F) ((T)1 << ((E) + (F)))
#define FP_INT_BIT(T, F) ((T)1 << (F))
#define FP_INF(T, E, F) ((((T)1 << (E)) - 1) << (F))
#define FP_EXP_MAX(E) ((1 << (E)) - 1)
#define FP_BIAS(E) ((1 << ((E) - 1)) - 1)

// The quiet bit is the other way round on MIPS before NaN 2008, on PA-RISC,
// and on SuperH.
#if (defined(__mips__) && !defined(__mips_nan2008)) || defined(__hppa__) || defined(__sh__)
#   define FP_NAN(T, E, F) (FP_INF(T, E, F) | (((T)1 << ((F) - 1)) - 1))
#   define WIDE_QUIET(bit) wide_sub(bit, wide_make(0, 1))
#else
#   define FP_NAN(T, E, F) (FP_INF(T, E, F) | ((T)1 << ((F) - 1)))
// In the 96-bit format of m68k, the FPU and compilers set all the bits.
#   if defined(__m68k__)
#       define WIDE_QUIET(bit) wide_or(bit, wide_sub(bit, wide_make(0, 1)))
#   else
#       define WIDE_QUIET(bit) (bit)
#   endif
#endif

// Workaround: GCC 13, Xtensa, optimising for size: it crashes on "+g" here.
#if !defined(__clang__) && defined(__XTENSA__) && __GNUC__ == 13
#   define FP_HIDDEN "+r"
#else
#   define FP_HIDDEN "+g"
#endif

#if FP_PASSED_AS_INT
#   define FP_BITS(fmt, C, T) \
        static inline T fmt##_to_bits(T bits) { \
            return bits; \
        } \
        \
        static inline T fmt##_from_bits(T bits) { \
            return bits; \
        }
#else // FP_PASSED_AS_INT
#   define FP_BITS(fmt, C, T) \
        FP_ABI static inline T fmt##_to_bits(C value) { \
            T bits; \
            \
            __builtin_memcpy(&bits, &value, sizeof(T)); \
            __asm__ ("" : FP_HIDDEN(bits)); \
            return bits; \
        } \
        \
        FP_ABI static inline C fmt##_from_bits(T bits) { \
            C value; \
            \
            __asm__ ("" : FP_HIDDEN(bits)); \
            __builtin_memcpy(&value, &bits, sizeof(T)); \
            return value; \
        }
#endif // FP_PASSED_AS_INT

// A shift right that keeps in the low bit whether any bit was lost. A count
// past F + 4 leaves no bit of a significand, which never reaches bit F + 5.
#define FP_STICKY_SHIFT(fmt, T, F) \
    FP_HELPER T fmt##_sticky_shift(T sig, unsigned int n) { \
        T kept; \
        \
        if (n > (F) + 4) { \
            return (T)(sig != 0); \
        } \
        kept = sig >> n; \
        return kept | (T)((kept << n) != sig); \
    }

// Packs a result of biased exponent e, with sig below bit F + 4. Exponents are
// unsigned for -ftrapv, and e may have wrapped below zero. The rounded
// significand is added to the exponent field less one: the integer bit of a
// normal result makes up for that, a subnormal result has none, and rounding
// up into the next exponent, or into infinity, carries by itself.
#define FP_ROUND_PACK(fmt, T, E, F) \
    FP_HELPER T fmt##_round_pack(T sign, unsigned int e, T sig) { \
        T bits; \
        unsigned int low; \
        \
        if ((int)e >= FP_EXP_MAX(E)) { \
            return sign | FP_INF(T, E, F); \
        } \
        if ((int)e <= 0) { \
            sig = fmt##_sticky_shift(sig, 1 - e); \
            e = 1; \
        } \
        low = (unsigned int)sig & 7; \
        bits = ((T)(e - 1) << (F)) + (sig >> 3); \
        if (low > 4 || (low == 4 && (bits & 1) != 0)) { \
            bits += 1; \
        } \
        return sign | bits; \
    }

// With the larger magnitude first, a NaN or an infinity is first too, and the
// subtraction of the significands cannot go below zero. An exact cancellation
// gives +0 in the default rounding mode. Only a subtraction of nearly equal
// values shifts by more than one bit, and those lose no bits to the sticky
// bit.
#define FP_ADD(fmt, T, E, F) \
    FP_HELPER T fmt##_add(T a, T b) { \
        T sign = FP_SIGN(T, E, F); \
        T inf = FP_INF(T, E, F); \
        T int_bit = FP_INT_BIT(T, F); \
        bool swapped = (a & (sign - 1)) < (b & (sign - 1)); \
        T big = swapped ? b : a; \
        T magnitude = big & (sign - 1); \
        T other_magnitude = (swapped ? a : b) & (sign - 1); \
        T sig = magnitude & (int_bit - 1); \
        T other_sig = other_magnitude & (int_bit - 1); \
        unsigned int e = (unsigned int)(magnitude >> (F)); \
        unsigned int other_e = (unsigned int)(other_magnitude >> (F)); \
        \
        if (magnitude >= inf) { \
            if (magnitude > inf || (other_magnitude == inf && ((a ^ b) & sign) != 0)) { \
                return FP_NAN(T, E, F); \
            } \
            return big; \
        } \
        if (e != 0) { \
            sig |= int_bit; \
        } else { \
            e = 1; \
        } \
        if (other_e != 0) { \
            other_sig |= int_bit; \
        } else { \
            other_e = 1; \
        } \
        sig <<= 3; \
        other_sig = fmt##_sticky_shift(other_sig << 3, e - other_e); \
        if (((a ^ b) & sign) == 0) { \
            sig += other_sig; \
            if (sig >= int_bit << 4) { \
                sig = (sig >> 1) | (sig & 1); \
                e += 1; \
            } \
        } else { \
            sig -= other_sig; \
            if (sig == 0) { \
                return 0; \
            } \
            while (sig < int_bit << 3 && e > 1) { \
                sig += sig; \
                e -= 1; \
            } \
        } \
        return fmt##_round_pack(big & sign, e, sig); \
    }

#define FP_ZERO 0
#define FP_FINITE 1
#define FP_INFINITE 2
#define FP_NOT_A_NUMBER 3

// The special cases of multiplication and division go by the kinds of their
// operands, which keeps them to one comparison of each with infinity.
#define FP_KIND(fmt, T, E, F) \
    FP_HELPER int fmt##_kind(T magnitude) { \
        if (magnitude > FP_INF(T, E, F)) { \
            return FP_NOT_A_NUMBER; \
        } \
        if (magnitude == FP_INF(T, E, F)) { \
            return FP_INFINITE; \
        } \
        return magnitude != 0 ? FP_FINITE : FP_ZERO; \
    }

// The significand of a finite nonzero value, its integer bit set.
#define FP_NORMALISE(fmt, T, F) \
    FP_HELPER T fmt##_normalise(T magnitude, unsigned int *e) { \
        T int_bit = FP_INT_BIT(T, F); \
        T sig = magnitude & (int_bit - 1); \
        unsigned int exponent = (unsigned int)(magnitude >> (F)); \
        \
        if (exponent != 0) { \
            sig |= int_bit; \
        } else { \
            exponent = 1; \
            while (sig < int_bit) { \
                sig += sig; \
                exponent -= 1; \
            } \
        } \
        *e = exponent; \
        return sig; \
    }

#if LGRT_SOFT_FLOAT
// These give the two halves of the product of two values of W bits.
static inline void fp_wide_mul32(uint32_t a, uint32_t b, uint32_t *hi, uint32_t *lo) {
    uint64_t product = (uint64_t)a * b;

    *hi = HIGH_32(product);
    *lo = (uint32_t)product;
}
#endif

// The product of the significands has 2F + 1 or 2F + 2 bits, so a shift by F -
// 3 lines it up with the significand worked on, or one bit above that.
#define FP_MUL(fmt, T, W, E, F) \
    static inline T fmt##_mul(T a, T b) { \
        T sign_bit = FP_SIGN(T, E, F); \
        T sign = (a ^ b) & sign_bit; \
        T magnitude_a = a & (sign_bit - 1); \
        T magnitude_b = b & (sign_bit - 1); \
        int kind_a = fmt##_kind(magnitude_a); \
        int kind_b = fmt##_kind(magnitude_b); \
        T sig_a; \
        T sig_b; \
        T hi; \
        T lo; \
        T sig; \
        unsigned int e_a; \
        unsigned int e_b; \
        unsigned int e; \
        \
        if (kind_a == FP_NOT_A_NUMBER || kind_b == FP_NOT_A_NUMBER) { \
            return FP_NAN(T, E, F); \
        } \
        if (kind_a == FP_INFINITE || kind_b == FP_INFINITE) { \
            if (kind_a == FP_ZERO || kind_b == FP_ZERO) { \
                return FP_NAN(T, E, F); \
            } \
            return sign | FP_INF(T, E, F); \
        } \
        if (kind_a == FP_ZERO || kind_b == FP_ZERO) { \
            return sign; \
        } \
        sig_a = fmt##_normalise(magnitude_a, &e_a); \
        sig_b = fmt##_normalise(magnitude_b, &e_b); \
        e = e_a + e_b - FP_BIAS(E); \
        fp_wide_mul##W(sig_a, sig_b, &hi, &lo); \
        sig = (hi << ((W) - (F) + 3)) | (lo >> ((F) - 3)) \
            | (T)((lo & (((T)1 << ((F) - 3)) - 1)) != 0); \
        if (sig >= FP_INT_BIT(T, F) << 4) { \
            sig = (sig >> 1) | (sig & 1); \
            e += 1; \
        } \
        return fmt##_round_pack(sign, e, sig); \
    }

// With the remainder made no smaller than the divisor and less than twice it,
// long division gives the integer bit first, and F + 3 bits after that.
#define FP_DIV(fmt, T, E, F) \
    static inline T fmt##_div(T a, T b) { \
        T sign_bit = FP_SIGN(T, E, F); \
        T sign = (a ^ b) & sign_bit; \
        T magnitude_a = a & (sign_bit - 1); \
        T magnitude_b = b & (sign_bit - 1); \
        int kind_a = fmt##_kind(magnitude_a); \
        int kind_b = fmt##_kind(magnitude_b); \
        T quotient = 0; \
        T rem; \
        T divisor; \
        unsigned int e_a; \
        unsigned int e_b; \
        unsigned int e; \
        \
        if (kind_a == FP_NOT_A_NUMBER || kind_b == FP_NOT_A_NUMBER \
         || (kind_a == kind_b && kind_a != FP_FINITE)) { \
            return FP_NAN(T, E, F); \
        } \
        if (kind_a == FP_INFINITE || kind_b == FP_ZERO) { \
            return sign | FP_INF(T, E, F); \
        } \
        if (kind_b == FP_INFINITE || kind_a == FP_ZERO) { \
            return sign; \
        } \
        rem = fmt##_normalise(magnitude_a, &e_a); \
        divisor = fmt##_normalise(magnitude_b, &e_b); \
        e = e_a - e_b + FP_BIAS(E); \
        if (rem < divisor) { \
            rem += rem; \
            e -= 1; \
        } \
        for (size_t i = 0; i < (F) + 4; i++) { \
            quotient += quotient; \
            if (rem >= divisor) { \
                rem -= divisor; \
                quotient |= 1; \
            } \
            rem += rem; \
        } \
        quotient |= (T)(rem != 0); \
        return fmt##_round_pack(sign, e, quotient); \
    }

#define FP_ARITHMETIC_ROUTINES(fmt, C, T, E, F) \
    FP_ABI C __add##fmt##3(C a, C b) { \
        T x = fmt##_to_bits(a); \
        T y = fmt##_to_bits(b); \
        \
        return fmt##_from_bits(fmt##_add(x, y)); \
    } \
    \
    FP_ABI C __sub##fmt##3(C a, C b) { \
        T x = fmt##_to_bits(a); \
        T y = fmt##_to_bits(b) ^ FP_SIGN(T, E, F); \
        \
        return fmt##_from_bits(fmt##_add(x, y)); \
    } \
    \
    FP_ABI C __mul##fmt##3(C a, C b) { \
        T x = fmt##_to_bits(a); \
        T y = fmt##_to_bits(b); \
        \
        return fmt##_from_bits(fmt##_mul(x, y)); \
    } \
    \
    FP_ABI C __div##fmt##3(C a, C b) { \
        T x = fmt##_to_bits(a); \
        T y = fmt##_to_bits(b); \
        \
        return fmt##_from_bits(fmt##_div(x, y)); \
    } \
    \
    FP_ABI C __neg##fmt##2(C a) { \
        T x = fmt##_to_bits(a) ^ FP_SIGN(T, E, F); \
        \
        return fmt##_from_bits(x); \
    }

// Compilers read the result of a comparison as all of the register that
// returns it on some targets, and as its low part on others, down to the low
// byte on AVR, so it is extended to all of that register. Its value is -1, 0,
// or 1, or unordered if either operand is a NaN.
#if LGRT_64BIT || defined(__x86_64__) || defined(__mips64)
typedef int64_t fp_cmp;
#else
typedef int fp_cmp;
#endif

#define FP_COMPARE(fmt, T, E, F) \
    FP_HELPER int fmt##_compare(T a, T b, int unordered) { \
        T sign = FP_SIGN(T, E, F); \
        T inf = FP_INF(T, E, F); \
        T magnitude_a = a & (sign - 1); \
        T magnitude_b = b & (sign - 1); \
        bool negative = (a & sign) != 0; \
        \
        if (magnitude_a > inf || magnitude_b > inf) { \
            return unordered; \
        } \
        if (a == b || (magnitude_a | magnitude_b) == 0) { \
            return 0; \
        } \
        if (((a ^ b) & sign) != 0) { \
            return negative ? -1 : 1; \
        } \
        return (magnitude_a < magnitude_b) != negative ? -1 : 1; \
    }

#define FP_COMPARE_ROUTINE(fmt, C, T, name, unordered) \
    FP_ABI fp_cmp name(C a, C b) { \
        T x = fmt##_to_bits(a); \
        T y = fmt##_to_bits(b); \
        \
        return fmt##_compare(x, y, unordered); \
    }

// Comparisons with the same value for unordered operands are one routine under
// several names.
//
// Workaround: Clang, AVR: it writes an alias in a form that its own assembler
// alone takes, so they stay apart there. Clang 6 on ARM: the alias attribute
// comes second, as in FP_ALIAS.
#if defined(__clang__) && defined(__AVR__)
#   define FP_COMPARE_ALIAS(fmt, C, T, name, target, unordered) \
        FP_COMPARE_ROUTINE(fmt, C, T, name, unordered)
#else
#   define FP_COMPARE_ALIAS(fmt, C, T, name, target, unordered) \
        FP_ABI __attribute__((__alias__(target))) fp_cmp name(C a, C b);
#endif

#define FP_RELATION_NAMES(fmt, C, T) \
    FP_COMPARE_ROUTINE(fmt, C, T, __lt##fmt##2, 1) \
    FP_COMPARE_ALIAS(fmt, C, T, __le##fmt##2, "__lt" #fmt "2", 1) \
    FP_COMPARE_ALIAS(fmt, C, T, __eq##fmt##2, "__lt" #fmt "2", 1) \
    FP_COMPARE_ALIAS(fmt, C, T, __ne##fmt##2, "__lt" #fmt "2", 1) \
    FP_COMPARE_ROUTINE(fmt, C, T, __gt##fmt##2, -1) \
    FP_COMPARE_ALIAS(fmt, C, T, __ge##fmt##2, "__gt" #fmt "2", -1)

#define FP_COMPARE_NAMES(fmt, C, T) \
    FP_RELATION_NAMES(fmt, C, T) \
    FP_COMPARE_ALIAS(fmt, C, T, __cmp##fmt##2, "__lt" #fmt "2", 1)

#define FP_UNORD_ROUTINE(fmt, C, T, E, F) \
    FP_ABI fp_cmp __unord##fmt##2(C a, C b) { \
        T mask = FP_SIGN(T, E, F) - 1; \
        T x = fmt##_to_bits(a) & mask; \
        T y = fmt##_to_bits(b) & mask; \
        \
        return x > FP_INF(T, E, F) || y > FP_INF(T, E, F); \
    }

#define FP_COMPARE_ROUTINES(fmt, C, T, E, F) \
    FP_COMPARE_NAMES(fmt, C, T) \
    FP_UNORD_ROUTINE(fmt, C, T, E, F)

#define FP_CORE(fmt, C, T, W, E, F) \
    FP_STICKY_SHIFT(fmt, T, F) \
    FP_ROUND_PACK(fmt, T, E, F) \
    FP_ADD(fmt, T, E, F) \
    FP_KIND(fmt, T, E, F) \
    FP_NORMALISE(fmt, T, F) \
    FP_MUL(fmt, T, W, E, F) \
    FP_DIV(fmt, T, E, F) \
    FP_COMPARE(fmt, T, E, F) \
    FP_ARITHMETIC_ROUTINES(fmt, C, T, E, F)

// Conversions to an integer type of iw bits, with I and U its signed and
// unsigned forms, and mode its name in the routines' names, truncate. A value
// out of range gives the nearest integer of the type, and a NaN gives zero.
#define FP_TO_INT(fmt, C, T, E, F, mode, I, U, iw) \
    FP_HELPER U fmt##_fix_##mode(T a, U limit) { \
        T magnitude = a & (FP_SIGN(T, E, F) - 1); \
        T int_bit = FP_INT_BIT(T, F); \
        T sig = (magnitude & (int_bit - 1)) | int_bit; \
        unsigned int e = (unsigned int)(magnitude >> (F)); \
        U value; \
        \
        if (magnitude > FP_INF(T, E, F) || e < FP_BIAS(E)) { \
            return 0; \
        } \
        e -= FP_BIAS(E); \
        if (magnitude == FP_INF(T, E, F) || e >= (iw)) { \
            return limit; \
        } \
        if ((iw) > (F) && e >= (F)) { \
            value = (U)sig << (e - (F)); \
        } else { \
            value = (U)(sig >> ((F) - e)); \
        } \
        return value > limit ? limit : value; \
    } \
    \
    FP_ABI I __fix##fmt##mode(C a) { \
        T x = fmt##_to_bits(a); \
        U top = (U)1 << ((iw) - 1); \
        \
        if ((x & FP_SIGN(T, E, F)) != 0) { \
            return (I)((U)0 - fmt##_fix_##mode(x, top)); \
        } \
        return (I)fmt##_fix_##mode(x, top - 1); \
    } \
    \
    FP_ABI U __fixuns##fmt##mode(C a) { \
        T x = fmt##_to_bits(a); \
        \
        if ((x & FP_SIGN(T, E, F)) != 0) { \
            return 0; \
        } \
        return fmt##_fix_##mode(x, (U)0 - 1); \
    }

// The types that conversions from unsigned integers take them in, by mode.
//
// Workaround: GCC, 64-bit PowerPC after 4.9, s390x, and SPARC64: for those of
// unsigned int, its library calls sign-extend the argument, where the ABI has
// it zero-extended and code compiled for that type relies on that. So they
// take all of the register there, and narrow it to the low half.
//
// Workaround: Clang before 12, 64-bit RISC-V: its library calls zero-extend it
// where the ABI has it sign-extended, and take the same way.
#if LGRT_64BIT \
 && (defined(__powerpc__) || defined(__s390__) || defined(__sparc__) \
  || (defined(__clang__) && __clang_major__ < 12 && defined(__riscv)))
typedef uint64_t fp_unsigned_si;
#else
typedef uint32_t fp_unsigned_si;
#endif
typedef uint64_t fp_unsigned_di;
#if HAS_INT128
typedef u128 fp_unsigned_ti;
#endif

#define FP_FROM_INT(fmt, C, T, E, F, mode, I, U, iw) \
    FP_HELPER T fmt##_float_##mode(T sign, U value) { \
        unsigned int top; \
        T sig; \
        \
        if (value == 0) { \
            return 0; \
        } \
        top = (iw) - 1 - clz##iw(value); \
        if ((iw) <= (F) + 4 || top <= (F) + 3) { \
            sig = (T)value << ((F) + 3 - top); \
        } else { \
            unsigned int lost = top - ((F) + 3); \
            U kept = value >> lost; \
            \
            sig = (T)kept | (T)((kept << lost) != value); \
        } \
        return fmt##_round_pack(sign, FP_BIAS(E) + top, sig); \
    } \
    \
    FP_ABI C __float##mode##fmt(I i) { \
        T sign = i < 0 ? FP_SIGN(T, E, F) : 0; \
        U value = i < 0 ? (U)0 - (U)i : (U)i; \
        \
        return fmt##_from_bits(fmt##_float_##mode(sign, value)); \
    } \
    \
    FP_ABI C __floatun##mode##fmt(fp_unsigned_##mode i) { \
        return fmt##_from_bits(fmt##_float_##mode(0, (U)i)); \
    }

// Conversions between a format and a wider one, from the parameters above with
// _a for the former and _b for the latter. A value that is subnormal in the
// former is normal in the latter, where the integer bit of its significand
// adds to the exponent field, and so does a carry from rounding the other way.
#define FP_EXTEND_BITS(fmt_a, t_a, e_a, f_a, fmt_b, t_b, e_b, f_b) \
    static inline t_b fmt_b##_from_##fmt_a(t_a x) { \
        t_a magnitude = x & (FP_SIGN(t_a, e_a, f_a) - 1); \
        t_b bits = (x & FP_SIGN(t_a, e_a, f_a)) != 0 ? FP_SIGN(t_b, e_b, f_b) : 0; \
        t_a sig; \
        unsigned int e; \
        \
        if (magnitude > FP_INF(t_a, e_a, f_a)) { \
            bits = FP_NAN(t_b, e_b, f_b); \
        } else if (magnitude == FP_INF(t_a, e_a, f_a)) { \
            bits |= FP_INF(t_b, e_b, f_b); \
        } else if (magnitude != 0) { \
            sig = fmt_a##_normalise(magnitude, &e); \
            e = e + FP_BIAS(e_b) - FP_BIAS(e_a) - 1; \
            bits |= ((t_b)e << (f_b)) + ((t_b)sig << ((f_b) - (f_a))); \
        } \
        return bits; \
    }

#define FP_EXTEND(fmt_a, c_a, t_a, e_a, f_a, fmt_b, c_b, t_b, e_b, f_b) \
    FP_EXTEND_BITS(fmt_a, t_a, e_a, f_a, fmt_b, t_b, e_b, f_b) \
    \
    FP_ABI c_b __extend##fmt_a##fmt_b##2(c_a a) { \
        return fmt_b##_from_bits(fmt_b##_from_##fmt_a(fmt_a##_to_bits(a))); \
    }

#define FP_TRUNC_BITS(fmt_a, t_a, e_a, f_a, fmt_b, t_b, e_b, f_b) \
    static inline t_a fmt_b##_to_##fmt_a(t_b x) { \
        t_b magnitude = x & (FP_SIGN(t_b, e_b, f_b) - 1); \
        t_a sign = (x & FP_SIGN(t_b, e_b, f_b)) != 0 ? FP_SIGN(t_a, e_a, f_a) : 0; \
        t_b sig = magnitude & (FP_INT_BIT(t_b, f_b) - 1); \
        t_b kept; \
        unsigned int e = (unsigned int)(magnitude >> (f_b)); \
        \
        if (magnitude > FP_INF(t_b, e_b, f_b)) { \
            return FP_NAN(t_a, e_a, f_a); \
        } \
        if (magnitude == FP_INF(t_b, e_b, f_b)) { \
            return sign | FP_INF(t_a, e_a, f_a); \
        } \
        if (e != 0) { \
            sig |= FP_INT_BIT(t_b, f_b); \
        } else { \
            e = 1; \
        } \
        kept = sig >> ((f_b) - (f_a) - 3); \
        return fmt_a##_round_pack( \
            sign, e + FP_BIAS(e_a) - FP_BIAS(e_b), \
            (t_a)kept | (t_a)((kept << ((f_b) - (f_a) - 3)) != sig) \
        ); \
    }

#define FP_TRUNC(fmt_a, c_a, t_a, e_a, f_a, fmt_b, c_b, t_b, e_b, f_b) \
    FP_TRUNC_BITS(fmt_a, t_a, e_a, f_a, fmt_b, t_b, e_b, f_b) \
    \
    FP_ABI c_a __trunc##fmt_b##fmt_a##2(c_b a) { \
        return fmt_a##_from_bits(fmt_b##_to_##fmt_a(fmt_b##_to_bits(a))); \
    }

#if LGRT_SOFT_FLOAT

#if FP_PASSED_AS_INT
typedef uint32_t sf_value;
#else
typedef float sf_value;
#endif

FP_BITS(sf, sf_value, uint32_t)
FP_CORE(sf, sf_value, uint32_t, 32, 8, 23)
FP_COMPARE_ROUTINES(sf, sf_value, uint32_t, 8, 23)
FP_TO_INT(sf, sf_value, uint32_t, 8, 23, si, int32_t, uint32_t, 32)
FP_TO_INT(sf, sf_value, uint32_t, 8, 23, di, int64_t, uint64_t, 64)
FP_FROM_INT(sf, sf_value, uint32_t, 8, 23, si, int32_t, uint32_t, 32)
FP_FROM_INT(sf, sf_value, uint32_t, 8, 23, di, int64_t, uint64_t, 64)

#if HAS_INT128
FP_TO_INT(sf, sf_value, uint32_t, 8, 23, ti, i128, u128, 128)
FP_FROM_INT(sf, sf_value, uint32_t, 8, 23, ti, i128, u128, 128)
#endif

#endif // LGRT_SOFT_FLOAT

// The 64-bit format is double, or long double where double is narrower, as on
// AVR from GCC 10 by default and SuperH with -m4-single-only. AVR has neither
// before that, or with Clang by default. Clang on x86-64 without SSE2 cannot
// compile functions that take or return double.
#if !LGRT_SOFT_FLOAT || (__SIZEOF_DOUBLE__ != 8 && __SIZEOF_LONG_DOUBLE__ != 8) \
 || (defined(__x86_64__) && defined(__clang__) && !defined(__SSE2__))
#   define SOFT_DOUBLE 0
#else
#   define SOFT_DOUBLE 1
#endif

// IEEE quad is long double where that has its 113 bits, and __float128 where a
// compiler offers that next to a narrower long double. SPARC and Alpha have
// routines of other names for it, further down, and of these names for 128-bit
// integers and complex values, and on SPARC with -msoft-float. PowerPC has
// names of its own, for __float128 and with VSX, and for long double without
// VSX.
#if ALPHA_QUAD
#define QUAD_OWN_NAMES 1
typedef long double quad_value;
#elif !LGRT_SOFT_FLOAT
// Workaround: GCC 9 to 16, 64-bit MIPS, -msingle-float: it moves long double
// with instructions that the assembler rejects, so nothing can use the type.
#elif defined(__mips_single_float) && LDBL_MANT_DIG == 113 && !defined(__clang__) && __GNUC__ >= 9
#elif defined(__powerpc__)
#if defined(__FLOAT128__)
#define SOFT_QUAD 1
__extension__ typedef __float128 quad_value;
#elif defined(__LONG_DOUBLE_IEEE128__)
#define SOFT_QUAD 1
typedef long double quad_value;
#endif
#elif LDBL_MANT_DIG == 113
typedef long double quad_value;
#if defined(__sparc__)
#   define QUAD_OWN_NAMES 1
#else
#   define SOFT_QUAD 1
#endif
// Workaround: GCC before 5, x86: it has __float128 without this macro.
#elif defined(__SIZEOF_FLOAT128__) \
   || (!defined(__clang__) && __GNUC__ < 5 && (defined(__i386__) || defined(__x86_64__)))
#define SOFT_QUAD 1
__extension__ typedef __float128 quad_value;
#endif // ALPHA_QUAD

#if !defined(SOFT_QUAD)
#   define SOFT_QUAD 0
#endif

#if !defined(QUAD_OWN_NAMES)
#   define QUAD_OWN_NAMES 0
#endif

// The double-double format of IBM long double holds a value as the sum of two
// doubles, the larger first in memory on either endianness, and only the first
// when that is an infinity or a NaN. It comes as long double, or as __ibm128
// next to a long double of IEEE quad.
#if !SOFT_DOUBLE || !defined(__powerpc__)
#define HAS_IBM_128 0
#elif LDBL_MANT_DIG == 106
#define HAS_IBM_128 1
typedef long double ibm_value;
#elif defined(__LONG_DOUBLE_IEEE128__) \
   && (defined(__FLOAT128__) || defined(__VSX__) || defined(__clang__)) \
   && !(defined(__clang__) && __clang_major__ < 13)
#define HAS_IBM_128 1
__extension__ typedef __ibm128 ibm_value;
#else
#define HAS_IBM_128 0
#endif

#define SOFT_WIDE (SOFT_QUAD || QUAD_OWN_NAMES || SOFT_XF)

#if SOFT_DOUBLE || SOFT_WIDE

// In 32-bit pieces, as 32-bit targets have no 128-bit type, and so that 64-bit
// ones do not involve the routines for that type. Neither middle sum can
// overflow, as (2^32 - 1)^2 + 2^32 - 1 < 2^64.
static inline void fp_wide_mul64(uint64_t a, uint64_t b, uint64_t *hi, uint64_t *lo) {
    uint32_t a0 = (uint32_t)a;
    uint32_t a1 = HIGH_32(a);
    uint32_t b0 = (uint32_t)b;
    uint32_t b1 = HIGH_32(b);
    uint64_t p00 = (uint64_t)a0 * b0;
    uint64_t m1 = (uint64_t)a1 * b0 + HIGH_32(p00);
    uint64_t m2 = (uint64_t)a0 * b1 + (uint32_t)m1;

    *hi = (uint64_t)a1 * b1 + HIGH_32(m1) + HIGH_32(m2);
    *lo = JOIN_32((uint32_t)m2, (uint32_t)p00);
}

#endif

#if SOFT_DOUBLE

#if FP_PASSED_AS_INT
typedef uint64_t df_value;
#elif __SIZEOF_DOUBLE__ == 8
typedef double df_value;
#else
typedef long double df_value;
#endif

FP_BITS(df, df_value, uint64_t)
FP_CORE(df, df_value, uint64_t, 64, 11, 52)

// GCC on AVR takes these results for this format as truth values, nonzero
// where the relation holds, as __WITH_DOUBLE_COMPARISON__ being 2 tells. Clang
// goes by their sign here, as GCC does for float.
#if defined(__AVR__) && defined(__WITH_DOUBLE_COMPARISON__) && __WITH_DOUBLE_COMPARISON__ == 2

#define DF_TRUTH_ROUTINE(name, unordered, op) \
    FP_ABI fp_cmp name(df_value a, df_value b) { \
        uint64_t x = df_to_bits(a); \
        uint64_t y = df_to_bits(b); \
        \
        return df_compare(x, y, unordered) op 0; \
    }

DF_TRUTH_ROUTINE(__eqdf2, 1, ==)
DF_TRUTH_ROUTINE(__nedf2, 1, !=)
DF_TRUTH_ROUTINE(__ltdf2, 1, <)
DF_TRUTH_ROUTINE(__ledf2, 1, <=)
DF_TRUTH_ROUTINE(__gtdf2, -1, >)
DF_TRUTH_ROUTINE(__gedf2, -1, >=)
FP_COMPARE_ROUTINE(df, df_value, uint64_t, __cmpdf2, 1)
FP_UNORD_ROUTINE(df, df_value, uint64_t, 11, 52)

#else // defined(__AVR__) && defined(__WITH_DOUBLE_COMPARISON__) && __WITH_DOUBLE_COMPARISON__ == 2
FP_COMPARE_ROUTINES(df, df_value, uint64_t, 11, 52)
#endif // defined(__AVR__) && defined(__WITH_DOUBLE_COMPARISON__) && __WITH_DOUBLE_COMPARISON__ == 2

FP_TO_INT(df, df_value, uint64_t, 11, 52, si, int32_t, uint32_t, 32)
FP_TO_INT(df, df_value, uint64_t, 11, 52, di, int64_t, uint64_t, 64)
FP_FROM_INT(df, df_value, uint64_t, 11, 52, si, int32_t, uint32_t, 32)
FP_FROM_INT(df, df_value, uint64_t, 11, 52, di, int64_t, uint64_t, 64)
FP_EXTEND(sf, sf_value, uint32_t, 8, 23, df, df_value, uint64_t, 11, 52)
FP_TRUNC(sf, sf_value, uint32_t, 8, 23, df, df_value, uint64_t, 11, 52)

#if HAS_INT128
FP_TO_INT(df, df_value, uint64_t, 11, 52, ti, i128, u128, 128)
FP_FROM_INT(df, df_value, uint64_t, 11, 52, ti, i128, u128, 128)
#endif

#endif // SOFT_DOUBLE

#if SOFT_WIDE

// Formats of more than 64 bits have a core of their own, over two 64-bit words
// on every target, as 32-bit ones have no 128-bit type, and the others then
// need none of the routines for one either. It goes step by step as the core
// above does, with helpers for what that does with operators. It takes:
//
// M, the largest value of the exponent field, which infinities and NaNs have,
// with a bias of M / 2; F, the width of the fraction field, at least 63.
//
// A value has its fraction at the bottom, then its exponent, and its sign in
// the top bit of the high word. A significand being worked on has F + 5 bits.

// Not all that follows is used on every target.
#define WIDE_HELPER __attribute__((__unused__)) static inline

// The words in the order that they have in a value in memory.
struct wide {
#if defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
    uint64_t high;
    uint64_t low;
#else
    uint64_t low;
    uint64_t high;
#endif
};

WIDE_HELPER struct wide wide_make(uint64_t high, uint64_t low) {
    struct wide a;

    a.high = high;
    a.low = low;
    return a;
}

// A count of 128 or more leaves nothing.
WIDE_HELPER struct wide wide_shl(struct wide a, unsigned int n) {
    if (n == 0) {
        return a;
    }
    if (n >= 128) {
        return wide_make(0, 0);
    }
    if (n >= 64) {
        return wide_make(a.low << (n - 64), 0);
    }
    return wide_make((a.high << n) | (a.low >> (64 - n)), a.low << n);
}

WIDE_HELPER struct wide wide_shr(struct wide a, unsigned int n) {
    if (n == 0) {
        return a;
    }
    if (n >= 128) {
        return wide_make(0, 0);
    }
    if (n >= 64) {
        return wide_make(0, a.high >> (n - 64));
    }
    return wide_make(a.high >> n, (a.low >> n) | (a.high << (64 - n)));
}

WIDE_HELPER struct wide wide_add(struct wide a, struct wide b) {
    uint64_t low = a.low + b.low;

    return wide_make(a.high + b.high + (uint64_t)(low < a.low), low);
}

WIDE_HELPER struct wide wide_sub(struct wide a, struct wide b) {
    return wide_make(a.high - b.high - (uint64_t)(a.low < b.low), a.low - b.low);
}

WIDE_HELPER struct wide wide_or(struct wide a, struct wide b) {
    return wide_make(a.high | b.high, a.low | b.low);
}

WIDE_HELPER bool wide_eq(struct wide a, struct wide b) {
    return ((a.high ^ b.high) | (a.low ^ b.low)) == 0;
}

WIDE_HELPER bool wide_lt(struct wide a, struct wide b) {
    return a.high < b.high || (a.high == b.high && a.low < b.low);
}

// The n lowest bits.
WIDE_HELPER struct wide wide_low_bits(struct wide a, unsigned int n) {
    if (n >= 64) {
        return wide_make(a.high & (((uint64_t)1 << (n - 64)) - 1), a.low);
    }
    return wide_make(0, a.low & (((uint64_t)1 << n) - 1));
}

// The exponent field of a value without its sign.
WIDE_HELPER unsigned int wide_exponent(struct wide magnitude, unsigned int f) {
    return (unsigned int)wide_shr(magnitude, f).low;
}

// A shift right that keeps in the low bit whether any bit was lost.
WIDE_HELPER struct wide wide_sticky_shift(struct wide sig, unsigned int n) {
    struct wide kept = wide_shr(sig, n);

    kept.low |= (uint64_t)!wide_eq(wide_shl(kept, n), sig);
    return kept;
}

// The two halves of a product, from those of the words.
WIDE_HELPER void wide_mul(struct wide a, struct wide b, struct wide *hi, struct wide *lo) {
    struct wide low_low;
    struct wide low_high;
    struct wide high_low;
    struct wide high_high;
    struct wide sum;

    fp_wide_mul64(a.low, b.low, &low_low.high, &low_low.low);
    fp_wide_mul64(a.low, b.high, &low_high.high, &low_high.low);
    fp_wide_mul64(a.high, b.low, &high_low.high, &high_low.low);
    fp_wide_mul64(a.high, b.high, &high_high.high, &high_high.low);
    sum = wide_add(wide_make(0, low_low.high), wide_make(0, low_high.low));
    sum = wide_add(sum, wide_make(0, high_low.low));
    *lo = wide_make(sum.low, low_low.low);
    sum = wide_add(wide_make(0, sum.high), wide_make(0, low_high.high));
    sum = wide_add(sum, wide_make(0, high_low.high));
    sum = wide_add(sum, wide_make(0, high_high.low));
    *hi = wide_make(high_high.high + sum.high, sum.low);
}

#define WIDE_SIGN ((uint64_t)1 << 63)
#define WIDE_MAGNITUDE(a) wide_make((a).high & (WIDE_SIGN - 1), (a).low)
#define WIDE_INT_BIT(F) wide_shl(wide_make(0, 1), (F))
#define WIDE_BIAS(M) ((M) / 2)
#define WIDE_INF(M, F) wide_shl(wide_make(0, (M)), (F))
#define WIDE_NAN(M, F) wide_or(WIDE_INF(M, F), WIDE_QUIET(WIDE_INT_BIT((F) - 1)))

#define WIDE_BITS(fmt, C) \
    FP_ABI static inline struct wide fmt##_to_bits(C value) { \
        struct wide bits; \
        \
        __builtin_memcpy(&bits, &value, sizeof(struct wide)); \
        __asm__ ("" : "+g"(bits.high), "+g"(bits.low)); \
        return bits; \
    } \
    \
    FP_ABI static inline C fmt##_from_bits(struct wide bits) { \
        C value; \
        \
        __asm__ ("" : "+g"(bits.high), "+g"(bits.low)); \
        __builtin_memcpy(&value, &bits, sizeof(struct wide)); \
        return value; \
    }

#define WIDE_ROUND_PACK(fmt, M, F) \
    WIDE_HELPER struct wide fmt##_round_pack(uint64_t sign, unsigned int e, struct wide sig) { \
        struct wide bits; \
        unsigned int low; \
        \
        if ((int)e >= (M)) { \
            bits = WIDE_INF(M, F); \
            bits.high |= sign; \
            return bits; \
        } \
        if ((int)e <= 0) { \
            sig = wide_sticky_shift(sig, 1 - e); \
            e = 1; \
        } \
        low = (unsigned int)sig.low & 7; \
        bits = wide_add(wide_shl(wide_make(0, e - 1), (F)), wide_shr(sig, 3)); \
        if (low > 4 || (low == 4 && (bits.low & 1) != 0)) { \
            bits = wide_add(bits, wide_make(0, 1)); \
        } \
        bits.high |= sign; \
        return bits; \
    }

#define WIDE_ADD(fmt, M, F) \
    WIDE_HELPER struct wide fmt##_add(struct wide a, struct wide b) { \
        uint64_t sign = WIDE_SIGN; \
        struct wide inf = WIDE_INF(M, F); \
        struct wide int_bit = WIDE_INT_BIT(F); \
        struct wide magnitude_a = WIDE_MAGNITUDE(a); \
        struct wide magnitude_b = WIDE_MAGNITUDE(b); \
        bool swapped = wide_lt(magnitude_a, magnitude_b); \
        struct wide big = swapped ? b : a; \
        struct wide magnitude = swapped ? magnitude_b : magnitude_a; \
        struct wide other = swapped ? magnitude_a : magnitude_b; \
        struct wide sig = wide_low_bits(magnitude, (F)); \
        struct wide other_sig = wide_low_bits(other, (F)); \
        unsigned int e = wide_exponent(magnitude, (F)); \
        unsigned int other_e = wide_exponent(other, (F)); \
        bool subtract = ((a.high ^ b.high) & sign) != 0; \
        \
        if (!wide_lt(magnitude, inf)) { \
            if (wide_lt(inf, magnitude) || (wide_eq(other, inf) && subtract)) { \
                return WIDE_NAN(M, F); \
            } \
            return big; \
        } \
        if (e != 0) { \
            sig = wide_or(sig, int_bit); \
        } else { \
            e = 1; \
        } \
        if (other_e != 0) { \
            other_sig = wide_or(other_sig, int_bit); \
        } else { \
            other_e = 1; \
        } \
        sig = wide_shl(sig, 3); \
        other_sig = wide_sticky_shift(wide_shl(other_sig, 3), e - other_e); \
        if (!subtract) { \
            sig = wide_add(sig, other_sig); \
            if (!wide_lt(sig, wide_shl(int_bit, 4))) { \
                sig = wide_sticky_shift(sig, 1); \
                e += 1; \
            } \
        } else { \
            sig = wide_sub(sig, other_sig); \
            if (wide_eq(sig, wide_make(0, 0))) { \
                return sig; \
            } \
            while (wide_lt(sig, wide_shl(int_bit, 3)) && e > 1) { \
                sig = wide_shl(sig, 1); \
                e -= 1; \
            } \
        } \
        return fmt##_round_pack(big.high & sign, e, sig); \
    }

#define WIDE_KIND(fmt, M, F) \
    WIDE_HELPER int fmt##_kind(struct wide magnitude) { \
        struct wide inf = WIDE_INF(M, F); \
        \
        if (wide_lt(inf, magnitude)) { \
            return FP_NOT_A_NUMBER; \
        } \
        if (wide_eq(magnitude, inf)) { \
            return FP_INFINITE; \
        } \
        return wide_eq(magnitude, wide_make(0, 0)) ? FP_ZERO : FP_FINITE; \
    }

#define WIDE_NORMALISE(fmt, F) \
    WIDE_HELPER struct wide fmt##_normalise(struct wide magnitude, unsigned int *e) { \
        struct wide int_bit = WIDE_INT_BIT(F); \
        struct wide sig = wide_low_bits(magnitude, (F)); \
        unsigned int exponent = wide_exponent(magnitude, (F)); \
        \
        if (exponent != 0) { \
            sig = wide_or(sig, int_bit); \
        } else { \
            exponent = 1; \
            while (wide_lt(sig, int_bit)) { \
                sig = wide_shl(sig, 1); \
                exponent -= 1; \
            } \
        } \
        *e = exponent; \
        return sig; \
    }

#define WIDE_MUL(fmt, M, F) \
    WIDE_HELPER struct wide fmt##_mul(struct wide a, struct wide b) { \
        uint64_t sign = (a.high ^ b.high) & WIDE_SIGN; \
        struct wide magnitude_a = WIDE_MAGNITUDE(a); \
        struct wide magnitude_b = WIDE_MAGNITUDE(b); \
        int kind_a = fmt##_kind(magnitude_a); \
        int kind_b = fmt##_kind(magnitude_b); \
        struct wide bits = wide_make(sign, 0); \
        struct wide sig_a; \
        struct wide sig_b; \
        struct wide hi; \
        struct wide lo; \
        struct wide sig; \
        unsigned int e_a; \
        unsigned int e_b; \
        unsigned int e; \
        \
        if (kind_a == FP_NOT_A_NUMBER || kind_b == FP_NOT_A_NUMBER) { \
            return WIDE_NAN(M, F); \
        } \
        if (kind_a == FP_INFINITE || kind_b == FP_INFINITE) { \
            if (kind_a == FP_ZERO || kind_b == FP_ZERO) { \
                return WIDE_NAN(M, F); \
            } \
            return wide_or(bits, WIDE_INF(M, F)); \
        } \
        if (kind_a == FP_ZERO || kind_b == FP_ZERO) { \
            return bits; \
        } \
        sig_a = fmt##_normalise(magnitude_a, &e_a); \
        sig_b = fmt##_normalise(magnitude_b, &e_b); \
        e = e_a + e_b - WIDE_BIAS(M); \
        wide_mul(sig_a, sig_b, &hi, &lo); \
        sig = wide_or(wide_shl(hi, 128 - (F) + 3), wide_shr(lo, (F) - 3)); \
        lo = wide_low_bits(lo, (F) - 3); \
        sig.low |= (uint64_t)!wide_eq(lo, wide_make(0, 0)); \
        if (!wide_lt(sig, wide_shl(WIDE_INT_BIT(F), 4))) { \
            sig = wide_sticky_shift(sig, 1); \
            e += 1; \
        } \
        return fmt##_round_pack(sign, e, sig); \
    }

#define WIDE_DIV(fmt, M, F) \
    WIDE_HELPER struct wide fmt##_div(struct wide a, struct wide b) { \
        uint64_t sign = (a.high ^ b.high) & WIDE_SIGN; \
        struct wide magnitude_a = WIDE_MAGNITUDE(a); \
        struct wide magnitude_b = WIDE_MAGNITUDE(b); \
        int kind_a = fmt##_kind(magnitude_a); \
        int kind_b = fmt##_kind(magnitude_b); \
        struct wide bits = wide_make(sign, 0); \
        struct wide quotient = wide_make(0, 0); \
        struct wide rem; \
        struct wide divisor; \
        unsigned int e_a; \
        unsigned int e_b; \
        unsigned int e; \
        \
        if (kind_a == FP_NOT_A_NUMBER || kind_b == FP_NOT_A_NUMBER \
         || (kind_a == kind_b && kind_a != FP_FINITE)) { \
            return WIDE_NAN(M, F); \
        } \
        if (kind_a == FP_INFINITE || kind_b == FP_ZERO) { \
            return wide_or(bits, WIDE_INF(M, F)); \
        } \
        if (kind_b == FP_INFINITE || kind_a == FP_ZERO) { \
            return bits; \
        } \
        rem = fmt##_normalise(magnitude_a, &e_a); \
        divisor = fmt##_normalise(magnitude_b, &e_b); \
        e = e_a - e_b + WIDE_BIAS(M); \
        if (wide_lt(rem, divisor)) { \
            rem = wide_shl(rem, 1); \
            e -= 1; \
        } \
        for (size_t i = 0; i < (F) + 4; i++) { \
            quotient = wide_shl(quotient, 1); \
            if (!wide_lt(rem, divisor)) { \
                rem = wide_sub(rem, divisor); \
                quotient.low |= 1; \
            } \
            rem = wide_shl(rem, 1); \
        } \
        quotient.low |= (uint64_t)!wide_eq(rem, wide_make(0, 0)); \
        return fmt##_round_pack(sign, e, quotient); \
    }

#define WIDE_COMPARE(fmt, M, F) \
    static inline int fmt##_compare(struct wide a, struct wide b, int unordered) { \
        uint64_t sign = WIDE_SIGN; \
        struct wide inf = WIDE_INF(M, F); \
        struct wide magnitude_a = WIDE_MAGNITUDE(a); \
        struct wide magnitude_b = WIDE_MAGNITUDE(b); \
        struct wide either = wide_or(magnitude_a, magnitude_b); \
        bool negative = (a.high & sign) != 0; \
        \
        if (wide_lt(inf, magnitude_a) || wide_lt(inf, magnitude_b)) { \
            return unordered; \
        } \
        if (wide_eq(a, b) || (either.high | either.low) == 0) { \
            return 0; \
        } \
        if (((a.high ^ b.high) & sign) != 0) { \
            return negative ? -1 : 1; \
        } \
        return wide_lt(magnitude_a, magnitude_b) != negative ? -1 : 1; \
    }

// C returns a value and P passes one in, where those cannot be one type.
#define WIDE_ARITHMETIC_ROUTINES(fmt, C, P, M, F) \
    FP_ABI C __add##fmt##3(P a, P b) { \
        struct wide x = fmt##_to_bits(a); \
        struct wide y = fmt##_to_bits(b); \
        \
        return fmt##_from_bits(fmt##_add(x, y)); \
    } \
    \
    FP_ABI C __sub##fmt##3(P a, P b) { \
        struct wide x = fmt##_to_bits(a); \
        struct wide y = fmt##_to_bits(b); \
        \
        y.high ^= WIDE_SIGN; \
        return fmt##_from_bits(fmt##_add(x, y)); \
    } \
    \
    FP_ABI C __mul##fmt##3(P a, P b) { \
        struct wide x = fmt##_to_bits(a); \
        struct wide y = fmt##_to_bits(b); \
        \
        return fmt##_from_bits(fmt##_mul(x, y)); \
    } \
    \
    FP_ABI C __div##fmt##3(P a, P b) { \
        struct wide x = fmt##_to_bits(a); \
        struct wide y = fmt##_to_bits(b); \
        \
        return fmt##_from_bits(fmt##_div(x, y)); \
    } \
    \
    FP_ABI C __neg##fmt##2(P a) { \
        struct wide x = fmt##_to_bits(a); \
        \
        x.high ^= WIDE_SIGN; \
        return fmt##_from_bits(x); \
    }

#define WIDE_COMPARE_ROUTINES(fmt, C, M, F) \
    FP_COMPARE_NAMES(fmt, C, struct wide) \
    \
    FP_ABI fp_cmp __unord##fmt##2(C a, C b) { \
        struct wide x = fmt##_to_bits(a); \
        struct wide y = fmt##_to_bits(b); \
        struct wide inf = WIDE_INF(M, F); \
        \
        return wide_lt(inf, WIDE_MAGNITUDE(x)) || wide_lt(inf, WIDE_MAGNITUDE(y)); \
    }

#define WIDE_CORE(fmt, M, F) \
    WIDE_ROUND_PACK(fmt, M, F) \
    WIDE_ADD(fmt, M, F) \
    WIDE_KIND(fmt, M, F) \
    WIDE_NORMALISE(fmt, F) \
    WIDE_MUL(fmt, M, F) \
    WIDE_DIV(fmt, M, F)

#define WIDE_ARITHMETIC(fmt, C, P, M, F) \
    WIDE_CORE(fmt, M, F) \
    WIDE_ARITHMETIC_ROUTINES(fmt, C, P, M, F)

#define WIDE_COMPARISONS(fmt, C, M, F) \
    WIDE_COMPARE(fmt, M, F) \
    WIDE_COMPARE_ROUTINES(fmt, C, M, F)

// These truncate, out of range and for a NaN as FP_TO_INT does. In
// FMT_wrap_MODE, a negative value goes as in the signed conversion, and its
// integer is cast to the unsigned type.
#define WIDE_TO_INT_BITS(fmt, M, F, mode, I, U, iw) \
    WIDE_HELPER U fmt##_fix_##mode(struct wide a, U limit) { \
        struct wide magnitude = WIDE_MAGNITUDE(a); \
        struct wide sig = wide_or(wide_low_bits(magnitude, (F)), WIDE_INT_BIT(F)); \
        unsigned int e = wide_exponent(magnitude, (F)); \
        U value; \
        \
        if (wide_lt(WIDE_INF(M, F), magnitude) || e < WIDE_BIAS(M)) { \
            return 0; \
        } \
        e -= WIDE_BIAS(M); \
        if (e >= (iw)) { \
            return limit; \
        } \
        value = (U)wide_shr(sig, (F) - e).low; \
        return value > limit ? limit : value; \
    } \
    \
    WIDE_HELPER I fmt##_to_##mode(struct wide x) { \
        U top = (U)1 << ((iw) - 1); \
        \
        if ((x.high & WIDE_SIGN) != 0) { \
            return (I)((U)0 - fmt##_fix_##mode(x, top)); \
        } \
        return (I)fmt##_fix_##mode(x, top - 1); \
    } \
    \
    WIDE_HELPER U fmt##_to_uns##mode(struct wide x) { \
        if ((x.high & WIDE_SIGN) != 0) { \
            return 0; \
        } \
        return fmt##_fix_##mode(x, (U)0 - 1); \
    } \
    \
    WIDE_HELPER U fmt##_wrap_##mode(struct wide x) { \
        if ((x.high & WIDE_SIGN) != 0) { \
            return (U)0 - fmt##_fix_##mode(x, (U)1 << ((iw) - 1)); \
        } \
        return fmt##_fix_##mode(x, (U)0 - 1); \
    }

#define WIDE_TO_INT(fmt, C, M, F, mode, I, U, iw) \
    WIDE_TO_INT_BITS(fmt, M, F, mode, I, U, iw) \
    \
    FP_ABI I __fix##fmt##mode(C a) { \
        return fmt##_to_##mode(fmt##_to_bits(a)); \
    } \
    \
    FP_ABI U __fixuns##fmt##mode(C a) { \
        return fmt##_to_uns##mode(fmt##_to_bits(a)); \
    }

// The significands have room for the integers, so nothing rounds.
#define WIDE_FROM_INT_BITS(fmt, M, F, mode, I, U, iw) \
    WIDE_HELPER struct wide fmt##_float_##mode(uint64_t sign, U value) { \
        unsigned int top; \
        \
        if (value == 0) { \
            return wide_make(0, 0); \
        } \
        top = (iw) - 1 - clz##iw(value); \
        return fmt##_round_pack( \
            sign, WIDE_BIAS(M) + top, wide_shl(wide_make(0, value), (F) + 3 - top) \
        ); \
    } \
    \
    WIDE_HELPER struct wide fmt##_from_##mode(I i) { \
        uint64_t sign = i < 0 ? WIDE_SIGN : 0; \
        U value = i < 0 ? (U)0 - (U)i : (U)i; \
        \
        return fmt##_float_##mode(sign, value); \
    }

#define WIDE_FROM_INT(fmt, C, M, F, mode, I, U, iw) \
    WIDE_FROM_INT_BITS(fmt, M, F, mode, I, U, iw) \
    \
    FP_ABI C __float##mode##fmt(I i) { \
        return fmt##_from_bits(fmt##_from_##mode(i)); \
    } \
    \
    FP_ABI C __floatun##mode##fmt(fp_unsigned_##mode i) { \
        return fmt##_from_bits(fmt##_float_##mode(0, (U)i)); \
    }

#if HAS_INT128

static inline struct wide wide_from_u128(u128 a) {
    return wide_make((uint64_t)(a >> 64), (uint64_t)a);
}

static inline u128 wide_to_u128(struct wide a) {
    return ((u128)a.high << 64) | a.low;
}

// Conversions with 128-bit integers, which can be wider than a significand on
// top of what the macros above do, on two words rather than on the type.
#define WIDE_TO_TI_BITS(fmt, M, F) \
    static inline struct wide fmt##_fix_ti(struct wide a, struct wide limit) { \
        struct wide magnitude = WIDE_MAGNITUDE(a); \
        struct wide sig = wide_or(wide_low_bits(magnitude, (F)), WIDE_INT_BIT(F)); \
        unsigned int e = wide_exponent(magnitude, (F)); \
        struct wide value; \
        \
        if (wide_lt(WIDE_INF(M, F), magnitude) || e < WIDE_BIAS(M)) { \
            return wide_make(0, 0); \
        } \
        e -= WIDE_BIAS(M); \
        if (e >= 128) { \
            return limit; \
        } \
        value = e > (F) ? wide_shl(sig, e - (F)) : wide_shr(sig, (F) - e); \
        return wide_lt(limit, value) ? limit : value; \
    } \
    \
    static inline struct wide fmt##_to_ti(struct wide x) { \
        struct wide top = wide_make(WIDE_SIGN, 0); \
        \
        if ((x.high & WIDE_SIGN) != 0) { \
            return wide_sub(wide_make(0, 0), fmt##_fix_ti(x, top)); \
        } \
        return fmt##_fix_ti(x, wide_sub(top, wide_make(0, 1))); \
    } \
    \
    static inline struct wide fmt##_to_unsti(struct wide x) { \
        if ((x.high & WIDE_SIGN) != 0) { \
            return wide_make(0, 0); \
        } \
        return fmt##_fix_ti(x, wide_make((uint64_t)0 - 1, (uint64_t)0 - 1)); \
    }

#define WIDE_TO_TI(fmt, C, M, F) \
    WIDE_TO_TI_BITS(fmt, M, F) \
    \
    FP_ABI i128 __fix##fmt##ti(C a) { \
        return (i128)wide_to_u128(fmt##_to_ti(fmt##_to_bits(a))); \
    } \
    \
    FP_ABI u128 __fixuns##fmt##ti(C a) { \
        return wide_to_u128(fmt##_to_unsti(fmt##_to_bits(a))); \
    }

#define WIDE_FROM_TI_BITS(fmt, M, F) \
    static inline struct wide fmt##_float_ti(uint64_t sign, struct wide value) { \
        unsigned int top; \
        struct wide sig; \
        \
        if (wide_eq(value, wide_make(0, 0))) { \
            return value; \
        } \
        top = value.high != 0 ? 127 - clz64(value.high) : 63 - clz64(value.low); \
        sig = top <= (F) + 3 \
            ? wide_shl(value, (F) + 3 - top) \
            : wide_sticky_shift(value, top - ((F) + 3)); \
        return fmt##_round_pack(sign, WIDE_BIAS(M) + top, sig); \
    } \
    \
    static inline struct wide fmt##_from_ti(i128 i) { \
        u128 value = i < 0 ? (u128)0 - (u128)i : (u128)i; \
        \
        return fmt##_float_ti(i < 0 ? WIDE_SIGN : 0, wide_from_u128(value)); \
    }

#define WIDE_FROM_TI(fmt, C, M, F) \
    WIDE_FROM_TI_BITS(fmt, M, F) \
    \
    FP_ABI C __floatti##fmt(i128 i) { \
        return fmt##_from_bits(fmt##_from_ti(i)); \
    } \
    \
    FP_ABI C __floatunti##fmt(u128 i) { \
        return fmt##_from_bits(fmt##_float_ti(0, wide_from_u128(i))); \
    }

// Workaround: Clang before 22, hard-float MIPS64: it has the 128-bit integer
// of these in the floating-point registers of the format, going in and coming
// back, where the C ABI has it in integer registers.
#if defined(__clang__) && __clang_major__ < 22 && defined(__mips64) && !defined(__mips_soft_float)
#   define QUAD_TI_ROUTINES(fmt) \
        WIDE_TO_TI_BITS(fmt, 32767, 112) \
        WIDE_FROM_TI_BITS(fmt, 32767, 112) \
        \
        FP_ABI quad_value __fix##fmt##ti(quad_value a) { \
            return fmt##_from_bits(fmt##_to_ti(fmt##_to_bits(a))); \
        } \
        \
        FP_ABI quad_value __fixuns##fmt##ti(quad_value a) { \
            return fmt##_from_bits(fmt##_to_unsti(fmt##_to_bits(a))); \
        } \
        \
        FP_ABI quad_value __floatti##fmt(quad_value i) { \
            return fmt##_from_bits(fmt##_from_ti((i128)wide_to_u128(fmt##_to_bits(i)))); \
        } \
        \
        FP_ABI quad_value __floatunti##fmt(quad_value i) { \
            return fmt##_from_bits(fmt##_float_ti(0, fmt##_to_bits(i))); \
        }
#else // defined(__clang__) && __clang_major__ < 22 && defined(__mips64) && !defined(__mips_soft_float)
#   define QUAD_TI_ROUTINES(fmt) \
        WIDE_TO_TI(fmt, quad_value, 32767, 112) \
        WIDE_FROM_TI(fmt, quad_value, 32767, 112)
#endif // defined(__clang__) && __clang_major__ < 22 && defined(__mips64) && !defined(__mips_soft_float)

#else // HAS_INT128
#define QUAD_TI_ROUTINES(fmt)
#endif // HAS_INT128

// Conversions between a format of the core above, with the _a parameters, and
// one of this core, with the _b ones, as FP_EXTEND does them.
#define WIDE_EXTEND_BITS(fmt_a, t_a, e_a, f_a, fmt_b, m_b, f_b) \
    static inline struct wide fmt_b##_from_##fmt_a(t_a x) { \
        t_a magnitude = x & (FP_SIGN(t_a, e_a, f_a) - 1); \
        struct wide bits = wide_make(0, 0); \
        t_a sig; \
        unsigned int e; \
        \
        if (magnitude > FP_INF(t_a, e_a, f_a)) { \
            return WIDE_NAN(m_b, f_b); \
        } \
        if (magnitude == FP_INF(t_a, e_a, f_a)) { \
            bits = WIDE_INF(m_b, f_b); \
        } else if (magnitude != 0) { \
            sig = fmt_a##_normalise(magnitude, &e); \
            e = e + WIDE_BIAS(m_b) - FP_BIAS(e_a) - 1; \
            bits = wide_add( \
                wide_shl(wide_make(0, e), (f_b)), wide_shl(wide_make(0, sig), (f_b) - (f_a)) \
            ); \
        } \
        if ((x & FP_SIGN(t_a, e_a, f_a)) != 0) { \
            bits.high |= WIDE_SIGN; \
        } \
        return bits; \
    }

#define WIDE_EXTEND(fmt_a, c_a, t_a, e_a, f_a, fmt_b, c_b, m_b, f_b) \
    WIDE_EXTEND_BITS(fmt_a, t_a, e_a, f_a, fmt_b, m_b, f_b) \
    \
    FP_ABI c_b __extend##fmt_a##fmt_b##2(c_a a) { \
        return fmt_b##_from_bits(fmt_b##_from_##fmt_a(fmt_a##_to_bits(a))); \
    }

#define WIDE_TRUNC_BITS(fmt_a, t_a, e_a, f_a, fmt_b, m_b, f_b) \
    static inline t_a fmt_b##_to_##fmt_a(struct wide x) { \
        struct wide magnitude = WIDE_MAGNITUDE(x); \
        struct wide inf = WIDE_INF(m_b, f_b); \
        t_a sign = (x.high & WIDE_SIGN) != 0 ? FP_SIGN(t_a, e_a, f_a) : 0; \
        struct wide sig = wide_low_bits(magnitude, (f_b)); \
        struct wide kept; \
        unsigned int e = wide_exponent(magnitude, (f_b)); \
        \
        if (wide_lt(inf, magnitude)) { \
            return FP_NAN(t_a, e_a, f_a); \
        } \
        if (wide_eq(magnitude, inf)) { \
            return sign | FP_INF(t_a, e_a, f_a); \
        } \
        if (e != 0) { \
            sig = wide_or(sig, WIDE_INT_BIT(f_b)); \
        } else { \
            e = 1; \
        } \
        kept = wide_sticky_shift(sig, (f_b) - (f_a) - 3); \
        return fmt_a##_round_pack(sign, e + FP_BIAS(e_a) - WIDE_BIAS(m_b), (t_a)kept.low); \
    }

#define WIDE_TRUNC(fmt_a, c_a, t_a, e_a, f_a, fmt_b, c_b, m_b, f_b) \
    WIDE_TRUNC_BITS(fmt_a, t_a, e_a, f_a, fmt_b, m_b, f_b) \
    \
    FP_ABI c_a __trunc##fmt_b##fmt_a##2(c_b a) { \
        return fmt_a##_from_bits(fmt_b##_to_##fmt_a(fmt_b##_to_bits(a))); \
    }

#if SOFT_DOUBLE
#   define QUAD_DOUBLE_ROUTINES(fmt) \
        WIDE_EXTEND(df, df_value, uint64_t, 11, 52, fmt, quad_value, 32767, 112) \
        WIDE_TRUNC(df, df_value, uint64_t, 11, 52, fmt, quad_value, 32767, 112)
#else
#   define QUAD_DOUBLE_ROUTINES(fmt)
#endif

#define QUAD_ROUTINES(fmt) \
    WIDE_BITS(fmt, quad_value) \
    WIDE_ARITHMETIC(fmt, quad_value, quad_value, 32767, 112) \
    WIDE_COMPARISONS(fmt, quad_value, 32767, 112) \
    WIDE_TO_INT(fmt, quad_value, 32767, 112, si, int32_t, uint32_t, 32) \
    WIDE_TO_INT(fmt, quad_value, 32767, 112, di, int64_t, uint64_t, 64) \
    WIDE_FROM_INT(fmt, quad_value, 32767, 112, si, int32_t, uint32_t, 32) \
    WIDE_FROM_INT(fmt, quad_value, 32767, 112, di, int64_t, uint64_t, 64) \
    WIDE_EXTEND(sf, sf_value, uint32_t, 8, 23, fmt, quad_value, 32767, 112) \
    WIDE_TRUNC(sf, sf_value, uint32_t, 8, 23, fmt, quad_value, 32767, 112) \
    QUAD_DOUBLE_ROUTINES(fmt) \
    QUAD_TI_ROUTINES(fmt)

#if SOFT_QUAD

// PowerPC has names of its own for these, but for GCC with long double without
// VSX, which calls them by the usual ones or by those further down.
#if defined(__powerpc__) && (defined(__FLOAT128__) || defined(__VSX__) || defined(__clang__))

QUAD_ROUTINES(kf)

#if HAS_INT128
// GCC calls these conversions by the names of its software forms.
FP_ALIAS(i128, __fixkfti_sw, "__fixkfti", (quad_value a))
FP_ALIAS(u128, __fixunskfti_sw, "__fixunskfti", (quad_value a))
FP_ALIAS(quad_value, __floattikf_sw, "__floattikf", (i128 a))
FP_ALIAS(quad_value, __floatuntikf_sw, "__floatuntikf", (u128 a))
#endif

// The difference between a value in quad and the nearest double is exact in
// the format of IBM long double, and so are both doubles in quad.
#if HAS_IBM_128

ibm_value __extendkftf2(quad_value a) {
    struct wide x = kf_to_bits(a);
    uint64_t parts[2] = { kf_to_df(x), 0 };
    uint64_t mask = FP_SIGN(uint64_t, 11, 52) - 1;
    ibm_value value;

    if ((parts[0] & mask) < FP_INF(uint64_t, 11, 52)) {
        struct wide high = kf_from_df(parts[0]);

        high.high ^= WIDE_SIGN;
        parts[1] = kf_to_df(kf_add(x, high));
    }
    __builtin_memcpy(&value, parts, sizeof(parts));
    return value;
}

quad_value __trunctfkf2(ibm_value a) {
    uint64_t parts[2];
    uint64_t mask = FP_SIGN(uint64_t, 11, 52) - 1;
    struct wide high;

    __builtin_memcpy(parts, &a, sizeof(parts));
    high = kf_from_df(parts[0]);
    if ((parts[0] & mask) < FP_INF(uint64_t, 11, 52) && (parts[1] & mask) != 0) {
        high = kf_add(high, kf_from_df(parts[1]));
    }
    return kf_from_bits(high);
}

#endif // HAS_IBM_128

#else // defined(__powerpc__) && (defined(__FLOAT128__) || defined(__VSX__) || defined(__clang__))

QUAD_ROUTINES(tf)

#if defined(__powerpc__)

// The comparisons have the same results under these names.

#define QUAD_COMPARE_ALIAS(name, target) \
    FP_ALIAS(fp_cmp, name, target, (quad_value a, quad_value b))

#define QUAD_BINARY_ALIAS(name, target) \
    FP_ALIAS(quad_value, name, target, (quad_value a, quad_value b))

QUAD_BINARY_ALIAS(_q_add, "__addtf3")
QUAD_BINARY_ALIAS(_q_sub, "__subtf3")
QUAD_BINARY_ALIAS(_q_mul, "__multf3")
QUAD_BINARY_ALIAS(_q_div, "__divtf3")
QUAD_COMPARE_ALIAS(_q_feq, "__lttf2")
QUAD_COMPARE_ALIAS(_q_fne, "__lttf2")
QUAD_COMPARE_ALIAS(_q_flt, "__lttf2")
QUAD_COMPARE_ALIAS(_q_fle, "__lttf2")
QUAD_COMPARE_ALIAS(_q_fgt, "__gttf2")
QUAD_COMPARE_ALIAS(_q_fge, "__gttf2")
FP_ALIAS(quad_value, _q_neg, "__negtf2", (quad_value a))
FP_ALIAS(int32_t, _q_qtoi, "__fixtfsi", (quad_value a))
FP_ALIAS(uint32_t, _q_qtou, "__fixunstfsi", (quad_value a))
FP_ALIAS(quad_value, _q_itoq, "__floatsitf", (int32_t a))
FP_ALIAS(quad_value, _q_utoq, "__floatunsitf", (fp_unsigned_si a))
FP_ALIAS(sf_value, _q_qtos, "__trunctfsf2", (quad_value a))
FP_ALIAS(df_value, _q_qtod, "__trunctfdf2", (quad_value a))
FP_ALIAS(quad_value, _q_stoq, "__extendsftf2", (sf_value a))
FP_ALIAS(quad_value, _q_dtoq, "__extenddftf2", (df_value a))

#endif // defined(__powerpc__)

#endif // defined(__powerpc__) && (defined(__FLOAT128__) || defined(__VSX__) || defined(__clang__))

#elif QUAD_OWN_NAMES

#if !SOFT_DOUBLE
FP_STICKY_SHIFT(df, uint64_t, 52)
FP_ROUND_PACK(df, uint64_t, 11, 52)
FP_NORMALISE(df, uint64_t, 52)
#endif

WIDE_BITS(tf, quad_value)
WIDE_CORE(tf, 32767, 112)
QUAD_TI_ROUTINES(tf)
WIDE_COMPARE(tf, 32767, 112)
WIDE_TO_INT_BITS(tf, 32767, 112, si, int32_t, uint32_t, 32)
WIDE_TO_INT_BITS(tf, 32767, 112, di, int64_t, uint64_t, 64)
WIDE_FROM_INT_BITS(tf, 32767, 112, si, int32_t, uint32_t, 32)
WIDE_FROM_INT_BITS(tf, 32767, 112, di, int64_t, uint64_t, 64)
WIDE_EXTEND_BITS(df, uint64_t, 11, 52, tf, 32767, 112)
WIDE_TRUNC_BITS(df, uint64_t, 11, 52, tf, 32767, 112)

WIDE_HELPER struct wide tf_sub(struct wide a, struct wide b) {
    b.high ^= WIDE_SIGN;
    return tf_add(a, b);
}

#if defined(__sparc__)

WIDE_EXTEND_BITS(sf, uint32_t, 8, 23, tf, 32767, 112)
WIDE_TRUNC_BITS(sf, uint32_t, 8, 23, tf, 32767, 112)

// What compilers call for long double on SPARC, and how it passes values:
//
// 32-bit, _Q_*: as C passes that type, by pointer, with the caller's memory
// for a result.
//
// 64-bit, _Qp_*: pointers to the operands, after one to the result where that
// is a long double. C would use floating-point registers for those.
//
// 64-bit with -msoft-float, the usual names: as C passes that type, in integer
// registers.
//
// 32-bit with -msoft-float, Clang, the usual names, and _Q_lltoq, and
// _Q_ulltoq: each operand as two uint64_t, and a result in the four registers
// that a complex value of those comes back in. Only _Q_qtoll and _Q_qtoull
// stay as C passes that type, by pointer.
//
// TF_BINARY and the others write a routine in the form at hand, from an
// expression over x and y, the bits of its operands, or i, its operand of
// another type. The comparisons with an f in their names give truth values.
#if !LGRT_64BIT && defined(__clang__) && defined(SOFT_FLOAT)
#   define TF_IN_REGISTERS 1
#else
#   define TF_IN_REGISTERS 0
#endif

#if TF_IN_REGISTERS

__extension__ typedef _Complex unsigned long long tf_registers;

static inline tf_registers tf_to_registers(struct wide bits) {
    tf_registers value;

    __builtin_memcpy(&value, &bits, sizeof(struct wide));
    return value;
}

#define TF_BINARY(name, value) \
    tf_registers name(uint64_t a_high, uint64_t a_low, uint64_t b_high, uint64_t b_low) { \
        struct wide x = wide_make(a_high, a_low); \
        struct wide y = wide_make(b_high, b_low); \
        \
        return tf_to_registers(value); \
    }

#define TF_RELATION(name, value) \
    fp_cmp name(uint64_t a_high, uint64_t a_low, uint64_t b_high, uint64_t b_low) { \
        struct wide x = wide_make(a_high, a_low); \
        struct wide y = wide_make(b_high, b_low); \
        \
        return (value); \
    }

#define TF_FROM(name, P, value) \
    tf_registers name(P i) { \
        return tf_to_registers(value); \
    }

#define TF_TO(name, R, value) \
    R name(uint64_t high, uint64_t low) { \
        struct wide x = wide_make(high, low); \
        \
        return (value); \
    }

#define TF_TO_AS_C(name, R, value) \
    R name(quad_value a) { \
        struct wide x = tf_to_bits(a); \
        \
        return (value); \
    }

#elif LGRT_64BIT && !defined(_SOFT_FLOAT) && !defined(SOFT_FLOAT)

// Workaround: Clang 6 to 23, SPARC64: the temporaries that it passes to these
// routines are aligned to 8, where long double has 16.
typedef quad_value quad_place __attribute__((__aligned__(8)));

#define TF_BINARY(name, value) \
    void name(quad_place *r, const quad_place *a, const quad_place *b) { \
        struct wide x = tf_to_bits(*a); \
        struct wide y = tf_to_bits(*b); \
        \
        *r = tf_from_bits(value); \
    }

#define TF_RELATION(name, value) \
    fp_cmp name(const quad_place *a, const quad_place *b) { \
        struct wide x = tf_to_bits(*a); \
        struct wide y = tf_to_bits(*b); \
        \
        return (value); \
    }

#define TF_FROM(name, P, value) \
    void name(quad_place *r, P i) { \
        *r = tf_from_bits(value); \
    }

#define TF_TO(name, R, value) \
    R name(const quad_place *a) { \
        struct wide x = tf_to_bits(*a); \
        \
        return (value); \
    }

#else // TF_IN_REGISTERS

#define TF_BINARY(name, value) \
    quad_value name(quad_value a, quad_value b) { \
        struct wide x = tf_to_bits(a); \
        struct wide y = tf_to_bits(b); \
        \
        return tf_from_bits(value); \
    }

#define TF_RELATION(name, value) \
    fp_cmp name(quad_value a, quad_value b) { \
        struct wide x = tf_to_bits(a); \
        struct wide y = tf_to_bits(b); \
        \
        return (value); \
    }

#define TF_FROM(name, P, value) \
    quad_value name(P i) { \
        return tf_from_bits(value); \
    }

#define TF_TO(name, R, value) \
    R name(quad_value a) { \
        struct wide x = tf_to_bits(a); \
        \
        return (value); \
    }

#endif // TF_IN_REGISTERS

#define TF_EQUAL (tf_compare(x, y, 1) == 0)
#define TF_NOT_EQUAL (tf_compare(x, y, 1) != 0)
#define TF_LESS (tf_compare(x, y, 1) < 0)
#define TF_LESS_EQUAL (tf_compare(x, y, 1) <= 0)
#define TF_GREATER (tf_compare(x, y, -1) > 0)
#define TF_GREATER_EQUAL (tf_compare(x, y, -1) >= 0)
#define TF_UNORDERED (tf_compare(x, y, 2) == 2)
#define TF_FROM_SF tf_from_sf(sf_to_bits(i))
#define TF_FROM_DF tf_from_df(df_to_bits(i))
#define TF_TO_SF sf_from_bits(tf_to_sf(x))
#define TF_TO_DF df_from_bits(tf_to_df(x))

// The value of _Q_cmp and _Qp_cmp: 0 for equal, 1 for less, 2 for greater, and
// 3 for unordered.
WIDE_HELPER int tf_order(struct wide a, struct wide b) {
    int order = tf_compare(a, b, 2);

    return order < 0 ? 1 : order == 0 ? 0 : order + 1;
}

// One bit of the root at a time, for a value of m * 2^e with e even, keeping m
// - q * q = r * 2^-j for the root q after j bits and its remainder r. Both
// have 114 bits below the point, and r at most 4 above it. The sticky bit
// comes from r, so the result is correctly rounded.
WIDE_HELPER struct wide tf_sqrt(struct wide a) {
    struct wide magnitude = WIDE_MAGNITUDE(a);
    int kind = tf_kind(magnitude);
    struct wide root = WIDE_INT_BIT(114);
    struct wide rem;
    struct wide sig;
    unsigned int e;

    if (kind == FP_ZERO) {
        return a;
    }
    if (kind == FP_NOT_A_NUMBER || (a.high & WIDE_SIGN) != 0) {
        return WIDE_NAN(32767, 112);
    }
    if (kind == FP_INFINITE) {
        return a;
    }
    sig = tf_normalise(magnitude, &e);
    e -= WIDE_BIAS(32767);
    rem = wide_sub(wide_shl(sig, 2 + (e & 1)), root);
    e -= e & 1;
    for (size_t i = 114; i-- > 0; ) {
        struct wide unit = WIDE_INT_BIT((unsigned int)i);
        struct wide trial = wide_add(wide_shl(root, 1), unit);

        rem = wide_shl(rem, 1);
        if (!wide_lt(rem, trial)) {
            rem = wide_sub(rem, trial);
            root = wide_add(root, unit);
        }
    }
    sig = wide_shl(root, 1);
    sig.low |= (uint64_t)!wide_eq(rem, wide_make(0, 0));
    e = ((e + 0x10000) >> 1) - 0x8000;
    return tf_round_pack(0, e + WIDE_BIAS(32767), sig);
}

#if TF_IN_REGISTERS

TF_BINARY(__addtf3, tf_add(x, y))
TF_BINARY(__subtf3, tf_sub(x, y))
TF_BINARY(__multf3, tf_mul(x, y))
TF_BINARY(__divtf3, tf_div(x, y))
TF_RELATION(__eqtf2, tf_compare(x, y, 1))
TF_RELATION(__netf2, tf_compare(x, y, 1))
TF_RELATION(__lttf2, tf_compare(x, y, 1))
TF_RELATION(__letf2, tf_compare(x, y, 1))
TF_RELATION(__gttf2, tf_compare(x, y, -1))
TF_RELATION(__getf2, tf_compare(x, y, -1))
TF_RELATION(__unordtf2, TF_UNORDERED)
TF_FROM(__extendsftf2, sf_value, TF_FROM_SF)
TF_FROM(__extenddftf2, df_value, TF_FROM_DF)
TF_FROM(__floatsitf, int32_t, tf_from_si(i))
TF_FROM(__floatunsitf, uint32_t, tf_float_si(0, i))
TF_FROM(_Q_lltoq, int64_t, tf_from_di(i))
TF_FROM(_Q_ulltoq, uint64_t, tf_float_di(0, i))
TF_TO(__trunctfsf2, sf_value, TF_TO_SF)
TF_TO(__trunctfdf2, df_value, TF_TO_DF)
TF_TO(__fixtfsi, int32_t, tf_to_si(x))
TF_TO(__fixunstfsi, uint32_t, tf_to_unssi(x))
TF_TO_AS_C(_Q_qtoll, int64_t, tf_to_di(x))
TF_TO_AS_C(_Q_qtoull, uint64_t, tf_wrap_di(x))

#elif !LGRT_64BIT

TF_BINARY(_Q_add, tf_add(x, y))
TF_BINARY(_Q_sub, tf_sub(x, y))
TF_BINARY(_Q_mul, tf_mul(x, y))
TF_BINARY(_Q_div, tf_div(x, y))
TF_RELATION(_Q_cmp, tf_order(x, y))
TF_RELATION(_Q_feq, TF_EQUAL)
TF_RELATION(_Q_fne, TF_NOT_EQUAL)
TF_RELATION(_Q_flt, TF_LESS)
TF_RELATION(_Q_fle, TF_LESS_EQUAL)
TF_RELATION(_Q_fgt, TF_GREATER)
TF_RELATION(_Q_fge, TF_GREATER_EQUAL)
TF_FROM(_Q_stoq, sf_value, TF_FROM_SF)
TF_FROM(_Q_dtoq, df_value, TF_FROM_DF)
TF_FROM(_Q_itoq, int32_t, tf_from_si(i))
TF_FROM(_Q_utoq, uint32_t, tf_float_si(0, i))
TF_FROM(_Q_lltoq, int64_t, tf_from_di(i))
TF_FROM(_Q_ulltoq, uint64_t, tf_float_di(0, i))
TF_TO(_Q_qtos, sf_value, TF_TO_SF)
TF_TO(_Q_qtod, df_value, TF_TO_DF)
TF_TO(_Q_qtoi, int32_t, tf_to_si(x))
// The SPARC Compliance Definition has a negative value of _Q_qtou go through
// the signed integer, and the others like it do so here too.
TF_TO(_Q_qtou, uint32_t, tf_wrap_si(x))
TF_TO(_Q_qtoll, int64_t, tf_to_di(x))
TF_TO(_Q_qtoull, uint64_t, tf_wrap_di(x))

quad_value _Q_sqrt(quad_value a) {
    return tf_from_bits(tf_sqrt(tf_to_bits(a)));
}

// GCC calls this one by its usual name, with and only with -msoft-float.
#if defined(_SOFT_FLOAT)
TF_RELATION(__unordtf2, TF_UNORDERED)
#endif

#elif !defined(_SOFT_FLOAT) && !defined(SOFT_FLOAT)

TF_BINARY(_Qp_add, tf_add(x, y))
TF_BINARY(_Qp_sub, tf_sub(x, y))
TF_BINARY(_Qp_mul, tf_mul(x, y))
TF_BINARY(_Qp_div, tf_div(x, y))
TF_RELATION(_Qp_cmp, tf_order(x, y))
TF_RELATION(_Qp_feq, TF_EQUAL)
TF_RELATION(_Qp_fne, TF_NOT_EQUAL)
TF_RELATION(_Qp_flt, TF_LESS)
TF_RELATION(_Qp_fle, TF_LESS_EQUAL)
TF_RELATION(_Qp_fgt, TF_GREATER)
TF_RELATION(_Qp_fge, TF_GREATER_EQUAL)
TF_FROM(_Qp_stoq, sf_value, TF_FROM_SF)
TF_FROM(_Qp_dtoq, df_value, TF_FROM_DF)
// GCC extends a 32-bit integer to all of its register, and Clang leaves what
// is there, so these two take the low half of that register.
TF_FROM(_Qp_itoq, uint64_t, tf_from_si((int32_t)(uint32_t)i))
TF_FROM(_Qp_uitoq, uint64_t, tf_float_si(0, (uint32_t)i))
TF_FROM(_Qp_xtoq, int64_t, tf_from_di(i))
TF_FROM(_Qp_uxtoq, uint64_t, tf_float_di(0, i))
TF_TO(_Qp_qtos, sf_value, TF_TO_SF)
TF_TO(_Qp_qtod, df_value, TF_TO_DF)
TF_TO(_Qp_qtoi, int32_t, tf_to_si(x))
TF_TO(_Qp_qtoui, uint32_t, tf_wrap_si(x))
TF_TO(_Qp_qtox, int64_t, tf_to_di(x))
TF_TO(_Qp_qtoux, uint64_t, tf_wrap_di(x))

void _Qp_sqrt(quad_place *r, const quad_place *a) {
    *r = tf_from_bits(tf_sqrt(tf_to_bits(*a)));
}

#else // TF_IN_REGISTERS

TF_BINARY(__addtf3, tf_add(x, y))
TF_BINARY(__subtf3, tf_sub(x, y))
TF_BINARY(__multf3, tf_mul(x, y))
TF_BINARY(__divtf3, tf_div(x, y))

// GCC takes these results as truth values, nonzero where the relation holds,
// and Clang goes by their sign.
#if defined(__clang__)
TF_RELATION(__eqtf2, tf_compare(x, y, 1))
TF_RELATION(__netf2, tf_compare(x, y, 1))
TF_RELATION(__lttf2, tf_compare(x, y, 1))
TF_RELATION(__letf2, tf_compare(x, y, 1))
TF_RELATION(__gttf2, tf_compare(x, y, -1))
TF_RELATION(__getf2, tf_compare(x, y, -1))
#else
TF_RELATION(__eqtf2, TF_EQUAL)
TF_RELATION(__netf2, TF_NOT_EQUAL)
TF_RELATION(__lttf2, TF_LESS)
TF_RELATION(__letf2, TF_LESS_EQUAL)
TF_RELATION(__gttf2, TF_GREATER)
TF_RELATION(__getf2, TF_GREATER_EQUAL)
#endif

TF_RELATION(__unordtf2, TF_UNORDERED)
TF_FROM(__extendsftf2, sf_value, TF_FROM_SF)
TF_FROM(__extenddftf2, df_value, TF_FROM_DF)
// These two take the low half of the register, as _Qp_itoq does.
TF_FROM(__floatsitf, uint64_t, tf_from_si((int32_t)(uint32_t)i))
TF_FROM(__floatunsitf, uint64_t, tf_float_si(0, (uint32_t)i))
TF_FROM(__floatditf, int64_t, tf_from_di(i))
TF_FROM(__floatunditf, uint64_t, tf_float_di(0, i))
TF_TO(__trunctfsf2, sf_value, TF_TO_SF)
TF_TO(__trunctfdf2, df_value, TF_TO_DF)
TF_TO(__fixtfsi, int32_t, tf_to_si(x))
TF_TO(__fixunstfsi, uint32_t, tf_to_unssi(x))
TF_TO(__fixtfdi, int64_t, tf_to_di(x))
TF_TO(__fixunstfdi, uint64_t, tf_to_unsdi(x))

#endif // TF_IN_REGISTERS

#elif defined(__alpha__)

// GCC passes long double to these in two integer registers, the low word
// first, $16 and $17 and then $18 and $19, and otherwise calls them as it does
// any other function. Those that give a long double give it in $16 and $17,
// which C cannot do, so these leave it in those registers on their way out,
// which epilogues do not touch.
//
// The argument after the operands of some of these is a rounding mode, set by
// -mfp-rounding-mode: 2 by default for to nearest, and 1, 0, or 4 for towards
// minus infinity, towards zero, or dynamic. Nothing reads it, and all of these
// round to nearest.
#define OTS_RETURN_QUAD(value) do { \
    __typeof__(value) OTS_RETURN_QUAD_value = (value); \
    register uint64_t OTS_RETURN_QUAD_low __asm__ ("$16") = OTS_RETURN_QUAD_value.low; \
    register uint64_t OTS_RETURN_QUAD_high __asm__ ("$17") = OTS_RETURN_QUAD_value.high; \
    \
    __asm__ volatile ("" :: "r"(OTS_RETURN_QUAD_low), "r"(OTS_RETURN_QUAD_high)); \
} while (0)

#define OTS_ARITHMETIC(name, value) \
    void name(uint64_t a_low, uint64_t a_high, uint64_t b_low, uint64_t b_high) { \
        struct wide x = wide_make(a_high, a_low); \
        struct wide y = wide_make(b_high, b_low); \
        \
        OTS_RETURN_QUAD(value); \
    }

OTS_ARITHMETIC(_OtsAddX, tf_add(x, y))
OTS_ARITHMETIC(_OtsSubX, tf_sub(x, y))
OTS_ARITHMETIC(_OtsMulX, tf_mul(x, y))
OTS_ARITHMETIC(_OtsDivX, tf_div(x, y))

void _OtsCvtQX(int64_t i) {
    OTS_RETURN_QUAD(tf_from_di(i));
}

void _OtsCvtQUX(uint64_t i) {
    OTS_RETURN_QUAD(tf_float_di(0, i));
}

// The double comes in $f16, and floating-point types stay out of these, for
// -mno-fp-regs. Nothing has changed that register yet where this reads it.
void _OtsConvertFloatTX(void) {
    uint64_t bits;

    __asm__ volatile ("stt $f16, %0" : "=m"(bits));
    OTS_RETURN_QUAD(tf_from_df(bits));
}

// The double goes back in $f0, or in $0 with -mno-fp-regs, which no macro
// tells from -msoft-float, so it goes in both.
uint64_t _OtsConvertFloatXT(uint64_t low, uint64_t high) {
    uint64_t bits = tf_to_df(wide_make(high, low));

    __asm__ volatile ("ldt $f0, %0" :: "m"(bits));
    return bits;
}

// With -msoft-float or -mno-fp-regs, GCC calls this for float, with long
// double as C passes it, by pointer, and the result as above, in the form that
// loading it from memory gives.
#if !LGRT_SOFT_FLOAT

FP_STICKY_SHIFT(sf, uint32_t, 23)
FP_ROUND_PACK(sf, uint32_t, 8, 23)
WIDE_TRUNC_BITS(sf, uint32_t, 8, 23, tf, 32767, 112)

int32_t __trunctfsf2(const quad_value *a) {
    int32_t bits = (int32_t)tf_to_sf(tf_to_bits(*a));

    __asm__ volatile ("lds $f0, %0" :: "m"(bits));
    return bits;
}

#endif

// GCC calls this for conversions to unsigned types too, so values up to 2^64
// give what those need, and negative ones what signed types do.
int64_t _OtsCvtXQ(uint64_t low, uint64_t high) {
    return (int64_t)tf_wrap_di(wide_make(high, low));
}

// These give 1 where the relation holds, and 0 where it does not. GCC takes a
// negative value from _OtsEqlX as unordered operands, and -1 is what these
// give for those: false for what reads a positive value as true, and true for
// _OtsNeqX, which reads any other than 0 as true.
#define OTS_RELATION(name, op) \
    fp_cmp name(uint64_t a_low, uint64_t a_high, uint64_t b_low, uint64_t b_high) { \
        struct wide x = wide_make(a_high, a_low); \
        struct wide y = wide_make(b_high, b_low); \
        int order = tf_compare(x, y, 2); \
        \
        return order == 2 ? -1 : order op 0; \
    }

OTS_RELATION(_OtsEqlX, ==)
OTS_RELATION(_OtsNeqX, !=)
OTS_RELATION(_OtsLssX, <)
OTS_RELATION(_OtsLeqX, <=)
OTS_RELATION(_OtsGtrX, >)
OTS_RELATION(_OtsGeqX, >=)

#endif // defined(__sparc__)

#endif // SOFT_QUAD

#if SOFT_XF

#define XF_INT_BIT ((uint64_t)1 << 63)

// The core treats the integer bit of these formats as it does any other: it
// sees it only here, where values come and go.
#if defined(__m68k__)

// A value of 96 bits has its sign and exponent field at the top of its first
// word, then 16 bits that are ignored and written as zero, then its
// significand. The exponent field means what it says down to 0, where a set
// integer bit makes a normal number and a clear one a denormal one of the same
// exponent, a binade below where IEEE formats stop. The core has this as a
// format with a field one higher, so that denormal numbers have 0 there.
//
// All encodings have a meaning. An unnormal number, of a clear integer bit
// under a higher field, gets normalised as it is used, its significand and
// field making up its value, and is a zero if its significand is. The integer
// bit means nothing for infinities and NaNs.
#define XF_EXP_MAX 32768
#define XF_RETURNED 1

typedef long double xf_value;

// Values are passed on the stack, where this structure goes too. As long
// double, compilers can load them into a floating-point register on the way,
// which changes some of them.
struct xf_words {
    uint32_t words[3];
};

#define XF_PARAMETER struct xf_words

static inline struct wide xf_to_bits(struct xf_words value) {
    uint32_t top = value.words[0];
    uint64_t sig = JOIN_32(value.words[1], value.words[2]);
    uint64_t field = (top >> 16) & 0x7fff;

    if (field == 0x7fff) {
        field = XF_EXP_MAX;
    } else {
        if (sig == 0) {
            field = 0;
        }
        while (sig < XF_INT_BIT && field != 0) {
            sig += sig;
            field -= 1;
        }
        field = sig < XF_INT_BIT ? 0 : field + 1;
    }
    return wide_make(
        ((uint64_t)(top >> 31) << 63) | (field >> 1), (field << 63) | (sig & (XF_INT_BIT - 1))
    );
}

// An infinity has a clear integer bit, as compilers and the FPU write it.
static inline xf_value xf_from_bits(struct wide bits) {
    uint64_t field = ((bits.high << 1) | (bits.low >> 63)) & 0xffff;
    uint64_t sig = bits.low & (XF_INT_BIT - 1);
    uint32_t words[3];
    xf_value value;

    if (field != 0) {
        if (field != XF_EXP_MAX || sig != 0) {
            sig |= XF_INT_BIT;
        }
        field -= 1;
    }
    words[0] = ((uint32_t)(bits.high >> 63) << 31) | ((uint32_t)field << 16);
    words[1] = HIGH_32(sig);
    words[2] = (uint32_t)sig;
    __asm__ ("" : "+g"(words[0]), "+g"(words[1]), "+g"(words[2]));
    __builtin_memcpy(&value, words, sizeof(words));
    return value;
}

#else // defined(__m68k__)

// A value has its significand first, then its sign and exponent field, in 16
// bits, then padding up to the size of the type. The 387 and later read a
// pseudo-denormal number, of a set integer bit under a zero field, as having a
// field of 1, and raise invalid for any other encoding that IEEE 754 does not
// have: unnormal numbers, pseudo-infinities, and pseudo-NaNs, of a clear
// integer bit under a nonzero field. Those are NaNs here for that reason.
#define XF_EXP_MAX 32767

// Clang rejects long double in a definition with x87 off, with nothing telling
// of that, so the routines it may call take that type's place below. x86-64
// passes long double where unsigned __int128 goes once the six registers for
// integers are taken, and IA-32 where a structure of its size goes, and both
// return it on top of the x87 stack.
#if !defined(__clang__)
__extension__ typedef __float80 xf_value;
typedef xf_value xf_argument;
#define XF_PARAMETER xf_argument
#elif defined(__x86_64__)
typedef u128 xf_argument;
#define XF_IGNORED __attribute__((__unused__))
#define XF_PARAMETER \
    uint64_t rdi XF_IGNORED, uint64_t rsi XF_IGNORED, \
    uint64_t rdx XF_IGNORED, uint64_t rcx XF_IGNORED, \
    uint64_t r8 XF_IGNORED, uint64_t r9 XF_IGNORED, \
    xf_argument
#else
typedef struct { uint32_t words[3]; } xf_argument;
#define XF_PARAMETER xf_argument
#endif

static inline struct wide xf_to_bits(xf_argument value) {
    struct wide raw = wide_make(0, 0);
    uint64_t field;

    __builtin_memcpy(&raw, &value, sizeof(xf_argument));
    __asm__ ("" : "+g"(raw.high), "+g"(raw.low));
    field = raw.high & 0x7fff;
    if (field == 0 && raw.low >= XF_INT_BIT) {
        field = 1;
    } else if (field != 0 && raw.low < XF_INT_BIT) {
        return WIDE_NAN(XF_EXP_MAX, 63);
    }
    return wide_make(
        ((raw.high & 0x8000) << 48) | (field >> 1), (field << 63) | (raw.low & (XF_INT_BIT - 1))
    );
}

// The bits in memory, with the padding clear.
static inline struct wide xf_encode(struct wide bits) {
    uint64_t field = ((bits.high << 1) | (bits.low >> 63)) & 0x7fff;

    return wide_make(
        ((bits.high >> 48) & 0x8000) | field,
        (bits.low & (XF_INT_BIT - 1)) | (field != 0 ? XF_INT_BIT : 0)
    );
}

#if defined(__clang__)

static inline void xf_return(struct wide bits) {
    struct wide raw = xf_encode(bits);

    __asm__ ("fldt %0" :: "m"(raw));
}

// x86-64 cannot return long double with x87 off. Passing it still works, in
// memory, so the routines that only take one are still called there.
//
// Workaround: GCC before 5, x86-64: nothing tells of -mno-80387, so none of
// them return it, which nothing calls with x87 on.
#elif !defined(__x86_64__) || (__GNUC__ >= 5 && !defined(_SOFT_FLOAT))

static inline xf_value xf_from_bits(struct wide bits) {
    struct wide raw = xf_encode(bits);
    xf_value value;

    __asm__ ("" : "+g"(raw.high), "+g"(raw.low));
    __builtin_memcpy(&value, &raw, sizeof(xf_value));
    return value;
}

#define XF_RETURNED 1

#endif // defined(__clang__)

#endif // defined(__m68k__)

#if !defined(XF_RETURNED)
#   define XF_RETURNED 0
#endif

#if XF_RETURNED

WIDE_ARITHMETIC(xf, xf_value, XF_PARAMETER, XF_EXP_MAX, 63)
WIDE_FROM_INT(xf, xf_value, XF_EXP_MAX, 63, si, int32_t, uint32_t, 32)
WIDE_FROM_INT(xf, xf_value, XF_EXP_MAX, 63, di, int64_t, uint64_t, 64)
#if LGRT_SOFT_FLOAT
WIDE_EXTEND(sf, sf_value, uint32_t, 8, 23, xf, xf_value, XF_EXP_MAX, 63)
#endif
#if SOFT_DOUBLE
WIDE_EXTEND(df, df_value, uint64_t, 11, 52, xf, xf_value, XF_EXP_MAX, 63)
#endif
#if HAS_INT128
WIDE_FROM_TI(xf, xf_value, XF_EXP_MAX, 63)
#endif

#elif defined(__clang__)

WIDE_CORE(xf, XF_EXP_MAX, 63)

#if HAS_INT128

WIDE_FROM_TI_BITS(xf, XF_EXP_MAX, 63)

void __floattixf(i128 i) {
    xf_return(xf_from_ti(i));
}

void __floatuntixf(u128 i) {
    xf_return(xf_float_ti(0, wide_from_u128(i)));
}

#endif

#endif // XF_RETURNED

#if !defined(__clang__) || defined(__m68k__)

WIDE_COMPARISONS(xf, XF_PARAMETER, XF_EXP_MAX, 63)
WIDE_TO_INT(xf, XF_PARAMETER, XF_EXP_MAX, 63, si, int32_t, uint32_t, 32)
WIDE_TO_INT(xf, XF_PARAMETER, XF_EXP_MAX, 63, di, int64_t, uint64_t, 64)
#if LGRT_SOFT_FLOAT
WIDE_TRUNC(sf, sf_value, uint32_t, 8, 23, xf, XF_PARAMETER, XF_EXP_MAX, 63)
#endif
#if SOFT_DOUBLE
WIDE_TRUNC(df, df_value, uint64_t, 11, 52, xf, XF_PARAMETER, XF_EXP_MAX, 63)
#endif

#endif

#if HAS_INT128
WIDE_TO_TI(xf, XF_PARAMETER, XF_EXP_MAX, 63)
#endif

// Quad has the same exponents as the x87, and a longer significand.
#if SOFT_QUAD && (defined(__i386__) || defined(__x86_64__))

quad_value __extendxftf2(XF_PARAMETER a) {
    struct wide x = xf_to_bits(a);
    struct wide magnitude = WIDE_MAGNITUDE(x);

    if (wide_lt(WIDE_INF(XF_EXP_MAX, 63), magnitude)) {
        return tf_from_bits(WIDE_NAN(32767, 112));
    }
    magnitude = wide_shl(magnitude, 112 - 63);
    magnitude.high |= x.high & WIDE_SIGN;
    return tf_from_bits(magnitude);
}

#if XF_RETURNED || defined(__clang__)

static inline struct wide xf_from_tf(struct wide x) {
    struct wide magnitude = WIDE_MAGNITUDE(x);
    struct wide sig = wide_low_bits(magnitude, 112);
    struct wide bits = WIDE_INF(XF_EXP_MAX, 63);
    unsigned int e = wide_exponent(magnitude, 112);

    if (wide_lt(WIDE_INF(32767, 112), magnitude)) {
        return WIDE_NAN(XF_EXP_MAX, 63);
    }
    if (wide_eq(magnitude, WIDE_INF(32767, 112))) {
        bits.high |= x.high & WIDE_SIGN;
        return bits;
    }
    if (e != 0) {
        sig = wide_or(sig, WIDE_INT_BIT(112));
    } else {
        e = 1;
    }
    return xf_round_pack(x.high & WIDE_SIGN, e, wide_sticky_shift(sig, 112 - 63 - 3));
}

#if defined(__clang__)
void __trunctfxf2(quad_value a) {
    xf_return(xf_from_tf(tf_to_bits(a)));
}
#else
xf_value __trunctfxf2(quad_value a) {
    return xf_from_bits(xf_from_tf(tf_to_bits(a)));
}
#endif

#endif // XF_RETURNED || defined(__clang__)

#endif // SOFT_QUAD && (defined(__i386__) || defined(__x86_64__))

#endif // SOFT_XF

#endif // SOFT_WIDE

#if defined(__ARM_EABI__)

// The names of the run-time ABI, and what the generic routines leave out.

#define AEABI_COMPARE(fmt, C, name, unordered, op) \
    AAPCS int name(C a, C b) { \
        return fmt##_compare(a, b, unordered) op 0; \
    }

#if defined(__ARM_FEATURE_PAC_DEFAULT)
// r12 holds the authentication code of lr, so it is saved with lr.
#   if defined(__ARM_FEATURE_BTI_DEFAULT)
#       define AEABI_FLAGS_ENTRY \
            "pacbti r12, lr, sp\n\t" \
            "push {r12, lr}\n\t"
#   else
#       define AEABI_FLAGS_ENTRY \
            "pac r12, lr, sp\n\t" \
            "push {r12, lr}\n\t"
#   endif
#   define AEABI_FLAGS_EXIT \
        "pop {r2, r3, r12, lr}\n\t" \
        "aut r12, lr, sp\n\t" \
        "bx lr\n\t"
#else // defined(__ARM_FEATURE_PAC_DEFAULT)
#   define AEABI_FLAGS_ENTRY \
        ASM_BTI \
        "push {r4, lr}\n\t"
#   if THUMB1 && ARM_V4T
// Thumb-1 cannot pop into lr, and r0 to r3 hold the results.
#       define AEABI_FLAGS_EXIT \
            "ldr r2, [sp, #12]\n\t" \
            "mov lr, r2\n\t" \
            "pop {r2, r3, r4}\n\t" \
            "add sp, sp, #4\n\t" \
            "bx lr\n\t"
#   elif ARM_V4T
#       define AEABI_FLAGS_EXIT \
            "pop {r2, r3, r4, lr}\n\t" \
            "bx lr\n\t"
#   else
#       define AEABI_FLAGS_EXIT "pop {r2, r3, r4, pc}\n\t"
#   endif
#endif // defined(__ARM_FEATURE_PAC_DEFAULT)

// These return in the flags and keep every register but ip and lr, so they
// save the argument registers around the comparison, with its -1, 0, or 1. One
// more than that, compared with 1, clears C only for less, and sets Z only for
// equal. Loading the saved registers changes no flags.
#define AEABI_FLAGS_ASM(f, swap) \
    ".syntax unified\n\t" \
    AEABI_FLAGS_ENTRY \
    "push {r0, r1, r2, r3}\n\t" \
    swap \
    "bl " f "\n\t" \
    "adds r0, r0, #1\n\t" \
    "cmp r0, #1\n\t" \
    "pop {r0, r1}\n\t" \
    AEABI_FLAGS_EXIT \
    ASM_END

#define AEABI_ROUTINES(x, fmt, C, E, F, swap) \
    FP_ALIAS(C, __aeabi_##x##add, "__add" #fmt "3", (C a, C b)) \
    FP_ALIAS(C, __aeabi_##x##sub, "__sub" #fmt "3", (C a, C b)) \
    FP_ALIAS(C, __aeabi_##x##mul, "__mul" #fmt "3", (C a, C b)) \
    FP_ALIAS(C, __aeabi_##x##div, "__div" #fmt "3", (C a, C b)) \
    FP_ALIAS(C, __aeabi_##x##neg, "__neg" #fmt "2", (C a)) \
    FP_ALIAS(int, __aeabi_##x##cmpun, "__unord" #fmt "2", (C a, C b)) \
    FP_ALIAS(int32_t, __aeabi_##x##2iz, "__fix" #fmt "si", (C a)) \
    FP_ALIAS(uint32_t, __aeabi_##x##2uiz, "__fixuns" #fmt "si", (C a)) \
    FP_ALIAS(int64_t, __aeabi_##x##2lz, "__fix" #fmt "di", (C a)) \
    FP_ALIAS(uint64_t, __aeabi_##x##2ulz, "__fixuns" #fmt "di", (C a)) \
    FP_ALIAS(C, __aeabi_i2##x, "__floatsi" #fmt, (int32_t a)) \
    FP_ALIAS(C, __aeabi_ui2##x, "__floatunsi" #fmt, (uint32_t a)) \
    FP_ALIAS(C, __aeabi_l2##x, "__floatdi" #fmt, (int64_t a)) \
    FP_ALIAS(C, __aeabi_ul2##x, "__floatundi" #fmt, (uint64_t a)) \
    \
    AAPCS C __aeabi_##x##rsub(C a, C b) { \
        return fmt##_add(b, a ^ FP_SIGN(C, E, F)); \
    } \
    \
    AEABI_COMPARE(fmt, C, __aeabi_##x##cmpeq, 1, ==) \
    AEABI_COMPARE(fmt, C, __aeabi_##x##cmplt, 1, <) \
    AEABI_COMPARE(fmt, C, __aeabi_##x##cmple, 1, <=) \
    AEABI_COMPARE(fmt, C, __aeabi_##x##cmpge, -1, >=) \
    AEABI_COMPARE(fmt, C, __aeabi_##x##cmpgt, -1, >) \
    \
    AAPCS __attribute__((__naked__)) void __aeabi_c##x##cmple(C a, C b) { \
        __asm__ volatile ( \
            AEABI_FLAGS_ASM("__lt" #fmt "2", "") \
        ); \
    } \
    \
    FP_ALIAS(void, __aeabi_c##x##cmpeq, "__aeabi_c" #x "cmple", (C a, C b)) \
    \
    AAPCS __attribute__((__naked__)) void __aeabi_c##x##rcmple(C a, C b) { \
        __asm__ volatile ( \
            AEABI_FLAGS_ASM("__lt" #fmt "2", swap) \
        ); \
    }

// Workaround: GCC, ARM: it warns that the parameters of naked functions are
// unused.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

AEABI_ROUTINES(
    f, sf, uint32_t, 8, 23,
    "ldr r0, [sp, #4]\n\t"
    "ldr r1, [sp]\n\t"
)
AEABI_ROUTINES(
    d, df, uint64_t, 11, 52,
    "ldr r0, [sp, #8]\n\t"
    "ldr r1, [sp, #12]\n\t"
    "ldr r2, [sp]\n\t"
    "ldr r3, [sp, #4]\n\t"
)

#pragma GCC diagnostic pop

FP_ALIAS(uint64_t, __aeabi_f2d, "__extendsfdf2", (uint32_t a))
FP_ALIAS(uint32_t, __aeabi_d2f, "__truncdfsf2", (uint64_t a))

#endif // defined(__ARM_EABI__)

#if defined(__hexagon__)

// A square root bit by bit, from the top. The value to take the root of lies
// in [1, 4), for an even exponent, and q is the root found so far, with rem
// the value less the square of q, doubled for each bit of q. All of them have
// F + 3 bits after the point. The bias is odd, so an even exponent has an odd
// biased one, and half the former, biased, is half the sum of that and the
// bias.
#define FP_SQRT(fmt, T, E, F) \
    static inline T fmt##_sqrt(T a) { \
        T sign = FP_SIGN(T, E, F); \
        T magnitude = a & (sign - 1); \
        T q = FP_INT_BIT(T, F) << 3; \
        T sig; \
        T rem; \
        unsigned int e; \
        \
        if (magnitude == 0 || a == FP_INF(T, E, F)) { \
            return a; \
        } \
        if (a >= FP_INF(T, E, F)) { \
            return FP_NAN(T, E, F); \
        } \
        sig = fmt##_normalise(magnitude, &e); \
        if ((e & 1) == 0) { \
            sig += sig; \
            e -= 1; \
        } \
        rem = (sig << 3) - q; \
        for (T bit = q >> 1; bit != 0; bit >>= 1) { \
            T trial = q + q + bit; \
            \
            rem += rem; \
            if (rem >= trial) { \
                rem -= trial; \
                q += bit; \
            } \
        } \
        q |= (T)(rem != 0); \
        return fmt##_round_pack(0, (e + FP_BIAS(E)) >> 1, q); \
    }

FP_SQRT(sf, uint32_t, 8, 23)
FP_SQRT(df, uint64_t, 11, 52)

float __hexagon_sqrtf(float a) {
    return sf_from_bits(sf_sqrt(sf_to_bits(a)));
}

double __hexagon_fast2_sqrtdf2(double a) {
    return df_from_bits(df_sqrt(df_to_bits(a)));
}

FP_ALIAS(double, __hexagon_adddf3, "__adddf3", (double a, double b))
FP_ALIAS(double, __hexagon_subdf3, "__subdf3", (double a, double b))
FP_ALIAS(double, __hexagon_muldf3, "__muldf3", (double a, double b))
FP_ALIAS(double, __hexagon_divdf3, "__divdf3", (double a, double b))
FP_ALIAS(float, __hexagon_divsf3, "__divsf3", (float a, float b))

// What -ffast-math calls is free to be more exact than it needs to be.
FP_ALIAS(double, __hexagon_fast_adddf3, "__adddf3", (double a, double b))
FP_ALIAS(double, __hexagon_fast_subdf3, "__subdf3", (double a, double b))
FP_ALIAS(double, __hexagon_fast_muldf3, "__muldf3", (double a, double b))
FP_ALIAS(double, __hexagon_fast_divdf3, "__divdf3", (double a, double b))
FP_ALIAS(float, __hexagon_fast_divsf3, "__divsf3", (float a, float b))
FP_ALIAS(float, __hexagon_fast2_sqrtf, "__hexagon_sqrtf", (float a))

#endif // defined(__hexagon__)

#if defined(__mips__) && defined(__mips_hard_float) && defined(_ABIO32) && _MIPS_SIM == _ABIO32 \
 && !defined(__mips_micromips) && !(defined(__mips_isa_rev) && __mips_isa_rev >= 6)

// What hard-float MIPS16 code calls, as it has no access to the floating-point
// registers. Operands and results stay in the general registers, in the order
// of integers of their sizes, and floating-point instructions do the work in
// 32-bit code. Comparisons need no such instructions, so they work on the bits
// in code of any kind.

#define MIPS16_BINARY(fmt, T, name, op) \
    FP_ABI T name(T a, T b) { \
        return fmt##_to_bits(fmt##_from_bits(a) op fmt##_from_bits(b)); \
    }

#define MIPS16_COMPARE_ALIAS(T, name, target) \
    __attribute__((__alias__(target))) fp_cmp name(T a, T b);

#define MIPS16_ROUTINES(fmt, C, T, E, F) \
    MIPS16_BINARY(fmt, T, __mips16_add##fmt##3, +) \
    MIPS16_BINARY(fmt, T, __mips16_sub##fmt##3, -) \
    MIPS16_BINARY(fmt, T, __mips16_mul##fmt##3, *) \
    MIPS16_BINARY(fmt, T, __mips16_div##fmt##3, /) \
    \
    fp_cmp __mips16_lt##fmt##2(T a, T b) { \
        return fmt##_compare(a, b, 1); \
    } \
    \
    MIPS16_COMPARE_ALIAS(T, __mips16_le##fmt##2, "__mips16_lt" #fmt "2") \
    MIPS16_COMPARE_ALIAS(T, __mips16_eq##fmt##2, "__mips16_lt" #fmt "2") \
    MIPS16_COMPARE_ALIAS(T, __mips16_ne##fmt##2, "__mips16_lt" #fmt "2") \
    \
    fp_cmp __mips16_gt##fmt##2(T a, T b) { \
        return fmt##_compare(a, b, -1); \
    } \
    \
    MIPS16_COMPARE_ALIAS(T, __mips16_ge##fmt##2, "__mips16_gt" #fmt "2") \
    \
    fp_cmp __mips16_unord##fmt##2(T a, T b) { \
        T mask = FP_SIGN(T, E, F) - 1; \
        \
        return (a & mask) > FP_INF(T, E, F) || (b & mask) > FP_INF(T, E, F); \
    } \
    \
    FP_ABI int32_t __mips16_fix_trunc##fmt##si(T a) { \
        return (int32_t)fmt##_from_bits(a); \
    } \
    \
    FP_ABI T __mips16_floatsi##fmt(int32_t a) { \
        return fmt##_to_bits((C)a); \
    } \
    \
    FP_ABI T __mips16_floatunsi##fmt(uint32_t a) { \
        return fmt##_to_bits((C)a); \
    }

MIPS16_ROUTINES(sf, sf_value, uint32_t, 8, 23)

// These have conventions of their own, so each is assembly in a section of its
// own. Moves of doubles go through memory, in the order of the two registers
// that hold them, whatever the byte order and the width of the floating-point
// registers. The frame is their own, as their callers may have none to spare.
#define MIPS16_STUB(name, body) \
    __asm__ ( \
        ".pushsection .text." name ",\"ax\",@progbits\n\t" \
        ".set push\n\t" \
        ".set nomips16\n\t" \
        ".set reorder\n\t" \
        ".set macro\n\t" \
        ".p2align 2\n\t" \
        ".globl " name "\n\t" \
        ".hidden " name "\n\t" \
        ".type " name ", @function\n\t" \
        name ":\n\t" \
        body \
        ".size " name ", . - " name "\n\t" \
        ".set pop\n\t" \
        ".popsection" \
    );

#define MIPS16_TO_FPR(first, second, fpr) \
    "addiu $sp, $sp, -8\n\t" \
    "sw " first ", 0($sp)\n\t" \
    "sw " second ", 4($sp)\n\t" \
    "l.d " fpr ", 0($sp)\n\t" \
    "addiu $sp, $sp, 8\n\t"

#define MIPS16_FROM_FPR(fpr, first, second) \
    "addiu $sp, $sp, -8\n\t" \
    "s.d " fpr ", 0($sp)\n\t" \
    "lw " first ", 0($sp)\n\t" \
    "lw " second ", 4($sp)\n\t" \
    "addiu $sp, $sp, 8\n\t"

// A function returning a floating-point value that MIPS16 code calls needs it
// in the floating-point registers, should its caller not be MIPS16 code. The
// general registers stay as they are.
MIPS16_STUB(
    "__mips16_ret_sf",
    "mtc1 $2, $f0\n\t"
    "jr $31\n\t"
)

MIPS16_STUB(
    "__mips16_ret_sc",
    "mtc1 $2, $f0\n\t"
    "mtc1 $3, $f2\n\t"
    "jr $31\n\t"
)

// MIPS16 code calls through pointers with these, the address in $2 and the
// arguments in the general registers. The number in each name tells which of
// the first two arguments go in floating-point registers, with two bits for
// each, the first in the lowest: 1 for float, and 2 for double. Without a
// floating-point result, a stub jumps to the function. Otherwise, $18 keeps
// the return address over the call, and the result comes back to the general
// registers.
#define MIPS16_CALL(n, args) \
    MIPS16_STUB( \
        "__mips16_call_stub_" #n, \
        args \
        "move $25, $2\n\t" \
        "jr $25\n\t" \
    )

#define MIPS16_CALL_RETURN(kind, n, args, result) \
    MIPS16_STUB( \
        "__mips16_call_stub_" kind "_" #n, \
        "move $18, $31\n\t" \
        args \
        "move $25, $2\n\t" \
        "jalr $25\n\t" \
        result \
        "jr $18\n\t" \
    )

#define MIPS16_ARGS_1 "mtc1 $4, $f12\n\t"
#define MIPS16_ARGS_5 \
    "mtc1 $4, $f12\n\t" \
    "mtc1 $5, $f14\n\t"

#define MIPS16_RETURN_SF "mfc1 $2, $f0\n\t"
#define MIPS16_RETURN_SC \
    "mfc1 $2, $f0\n\t" \
    "mfc1 $3, $f2\n\t"

MIPS16_CALL(1, MIPS16_ARGS_1)
MIPS16_CALL(5, MIPS16_ARGS_5)

#define MIPS16_CALLS_OF_FLOATS(kind, result) \
    MIPS16_CALL_RETURN(kind, 0, "", result) \
    MIPS16_CALL_RETURN(kind, 1, MIPS16_ARGS_1, result) \
    MIPS16_CALL_RETURN(kind, 5, MIPS16_ARGS_5, result)

MIPS16_CALLS_OF_FLOATS("sf", MIPS16_RETURN_SF)
MIPS16_CALLS_OF_FLOATS("sc", MIPS16_RETURN_SC)

#if !defined(__mips_single_float)

MIPS16_ROUTINES(df, df_value, uint64_t, 11, 52)

FP_ABI uint64_t __mips16_extendsfdf2(uint32_t a) {
    return df_to_bits((df_value)sf_from_bits(a));
}

FP_ABI uint32_t __mips16_truncdfsf2(uint64_t a) {
    return sf_to_bits((sf_value)df_from_bits(a));
}

MIPS16_STUB(
    "__mips16_ret_df",
    MIPS16_TO_FPR("$2", "$3", "$f0")
    "jr $31\n\t"
)

MIPS16_STUB(
    "__mips16_ret_dc",
    MIPS16_TO_FPR("$2", "$3", "$f0")
    MIPS16_TO_FPR("$4", "$5", "$f2")
    "jr $31\n\t"
)

#define MIPS16_ARGS_2 MIPS16_TO_FPR("$4", "$5", "$f12")
#define MIPS16_ARGS_6 \
    MIPS16_TO_FPR("$4", "$5", "$f12") \
    "mtc1 $6, $f14\n\t"
#define MIPS16_ARGS_9 \
    "mtc1 $4, $f12\n\t" \
    MIPS16_TO_FPR("$6", "$7", "$f14")
#define MIPS16_ARGS_10 \
    MIPS16_TO_FPR("$4", "$5", "$f12") \
    MIPS16_TO_FPR("$6", "$7", "$f14")

#define MIPS16_RETURN_DF MIPS16_FROM_FPR("$f0", "$2", "$3")
#define MIPS16_RETURN_DC \
    MIPS16_FROM_FPR("$f0", "$2", "$3") \
    MIPS16_FROM_FPR("$f2", "$4", "$5")

MIPS16_CALL(2, MIPS16_ARGS_2)
MIPS16_CALL(6, MIPS16_ARGS_6)
MIPS16_CALL(9, MIPS16_ARGS_9)
MIPS16_CALL(10, MIPS16_ARGS_10)

#define MIPS16_CALLS_OF_DOUBLES(kind, result) \
    MIPS16_CALL_RETURN(kind, 2, MIPS16_ARGS_2, result) \
    MIPS16_CALL_RETURN(kind, 6, MIPS16_ARGS_6, result) \
    MIPS16_CALL_RETURN(kind, 9, MIPS16_ARGS_9, result) \
    MIPS16_CALL_RETURN(kind, 10, MIPS16_ARGS_10, result)

MIPS16_CALLS_OF_FLOATS("df", MIPS16_RETURN_DF)
MIPS16_CALLS_OF_FLOATS("dc", MIPS16_RETURN_DC)
MIPS16_CALLS_OF_DOUBLES("sf", MIPS16_RETURN_SF)
MIPS16_CALLS_OF_DOUBLES("sc", MIPS16_RETURN_SC)
MIPS16_CALLS_OF_DOUBLES("df", MIPS16_RETURN_DF)
MIPS16_CALLS_OF_DOUBLES("dc", MIPS16_RETURN_DC)

#endif // !defined(__mips_single_float)

#endif // defined(__mips__) && defined(__mips_hard_float) && defined(_ABIO32) && _MIPS_SIM == _ABIO32 && !defined(__mips_micromips) && !(defined(__mips_isa_rev) && __mips_isa_rev >= 6)

#if LGRT_SOFT_FLOAT

// The 16-bit formats, half precision with E of 5 and F of 10, and bfloat16
// with 8 and 7, go through the core above on 32 bits. Compilers pass both as
// they pass _Float16, where they have that type, which GCC can only use on x86
// with SSE2. Clang has __fp16 on every target besides, and passes that as an
// integer where it has no _Float16. ARM has names of its own, further down.
//
// Workaround: Clang before 9, every target: it defines __FLT16_MANT_DIG__ for
// a type that 8 rejects on some targets, and 6 and 7 cannot compile on others,
// and it passes half as an integer to its library calls in any case.
//
// Workaround: Clang before 17, RISC-V with a hard-float ABI, without Zfh, and
// without Zfhmin from 16: it passes _Float16 in floating-point registers in C
// and to __mulhc3 and __divhc3, but half in integer registers to the library
// calls for its conversions.
#if defined(__clang__) && __clang_major__ < 17 && defined(__riscv) \
 && !defined(__riscv_float_abi_soft) && !defined(__riscv_zfh) \
 && (!defined(__riscv_zfhmin) || __clang_major__ < 16)
#   define HF_CONVERSIONS_AS_INT 1
#else
#   define HF_CONVERSIONS_AS_INT 0
#endif

// Half in an integer register. On RISC-V, what is above it there may be what
// was above it in a floating-point register, so that is taken and dropped.
#if defined(__riscv)
typedef uint32_t hf_register;
#else
typedef uint16_t hf_register;
#endif

// Workaround: Clang 17 to 19, RISC-V with a hard-float ABI, without Zfh and
// Zfhmin: it still takes half back in an integer register from the calls that
// convert a format which the ABI does not have in floating-point registers.
#if defined(__clang__) && __clang_major__ >= 17 && __clang_major__ < 20 && defined(__riscv) \
 && !defined(__riscv_float_abi_soft) && !defined(__riscv_zfh) && !defined(__riscv_zfhmin)
#   define HF_SOFT_RESULT_AS_INT 1
#else
#   define HF_SOFT_RESULT_AS_INT 0
#endif

#if defined(__FLT16_MANT_DIG__) && (!defined(__arm__) || defined(__clang__)) \
 && (defined(__SSE2__) || (!defined(__i386__) && !defined(__x86_64__))) \
 && (!defined(__clang__) || __clang_major__ >= 9) && !HF_CONVERSIONS_AS_INT
#define SOFT_HF 1
#define HF_PASSED_AS_INT 0
__extension__ typedef _Float16 hf_value;
#elif defined(__clang__)
#define SOFT_HF 1
#define HF_PASSED_AS_INT 1
typedef hf_register hf_value;
#else
#define SOFT_HF 0
#define HF_PASSED_AS_INT 0
#endif

#if !HF_PASSED_AS_INT
#   define FP16_HELPER __attribute__((__unused__)) FP_ABI static inline
#   define FP16_BITS(fmt, C) \
        FP16_HELPER uint32_t fmt##_to_bits(C value) { \
            uint16_t bits; \
            \
            __builtin_memcpy(&bits, &value, sizeof(uint16_t)); \
            __asm__ ("" : "+g"(bits)); \
            return bits; \
        } \
        \
        FP16_HELPER C fmt##_from_bits(uint32_t bits) { \
            uint16_t narrow = (uint16_t)bits; \
            C value; \
            \
            __asm__ ("" : "+g"(narrow)); \
            __builtin_memcpy(&value, &narrow, sizeof(uint16_t)); \
            return value; \
        }
#else // !HF_PASSED_AS_INT
#   define FP16_HELPER __attribute__((__unused__)) static inline
#   define FP16_BITS(fmt, C) \
        FP16_HELPER uint32_t fmt##_to_bits(C value) { \
            return (uint16_t)value; \
        } \
        \
        FP16_HELPER C fmt##_from_bits(uint32_t bits) { \
            return (C)bits; \
        }
#endif // !HF_PASSED_AS_INT

#if defined(__arm__) || SOFT_HF
FP_STICKY_SHIFT(hf, uint32_t, 10)
FP_ROUND_PACK(hf, uint32_t, 5, 10)
FP_NORMALISE(hf, uint32_t, 10)
#endif

#if defined(__arm__)

// These pass a half value in the low half of an integer register, on every
// procedure call standard, as they do float and double.
FP_EXTEND_BITS(hf, uint32_t, 5, 10, sf, uint32_t, 8, 23)
FP_TRUNC_BITS(hf, uint32_t, 5, 10, sf, uint32_t, 8, 23)
FP_TRUNC_BITS(hf, uint32_t, 5, 10, df, uint64_t, 11, 52)

// The run-time ABI has a NaN keep its sign and all of its fraction that the
// other format holds, with zeros below it in a wider one. Where a narrower one
// holds none of it, the NaN was a signalling one, and its lowest bit keeps it
// a signalling NaN.
#define HF_IEEE_TRUNC(fmt, T, E, F) \
    static inline uint32_t fmt##_to_hf_ieee(T x) { \
        uint32_t sign = (x & FP_SIGN(T, E, F)) != 0 ? 0x8000 : 0; \
        uint32_t kept = (uint32_t)((x & (FP_INT_BIT(T, F) - 1)) >> ((F) - 10)); \
        \
        if ((x & (FP_SIGN(T, E, F) - 1)) <= FP_INF(T, E, F)) { \
            return fmt##_to_hf(x); \
        } \
        return sign | FP_INF(uint32_t, 5, 10) | (kept != 0 ? kept : 1); \
    }

HF_IEEE_TRUNC(sf, uint32_t, 8, 23)
HF_IEEE_TRUNC(df, uint64_t, 11, 52)

uint32_t __gnu_h2f_ieee(uint32_t a) {
    uint32_t x = (uint16_t)a;

    if ((x & 0x7fff) > FP_INF(uint32_t, 5, 10)) {
        return ((x & 0x8000) << 16) | FP_INF(uint32_t, 8, 23) | ((x & 0x3ff) << 13);
    }
    return sf_from_hf(x);
}

int16_t __gnu_f2h_ieee(uint32_t a) {
    return (int16_t)sf_to_hf_ieee(a);
}

int16_t __gnu_d2h_ieee(uint64_t a) {
    return (int16_t)df_to_hf_ieee(a);
}

// The alternative format has no infinities or NaNs, and a field of 31 holds
// numbers too. The run-time ABI has what is too large for it, infinities
// included, give the largest number with its sign, and NaNs a zero with
// theirs.
static inline uint32_t hf_alt_round_pack(uint32_t sign, unsigned int e, uint32_t sig) {
    uint32_t bits;
    unsigned int low;

    if ((int)e > 31) {
        return sign | 0x7fff;
    }
    if ((int)e <= 0) {
        sig = hf_sticky_shift(sig, 1 - e);
        e = 1;
    }
    low = (unsigned int)sig & 7;
    bits = ((uint32_t)(e - 1) << 10) + (sig >> 3);
    if (low > 4 || (low == 4 && (bits & 1) != 0)) {
        bits += 1;
    }
    return sign | (bits > 0x7fff ? 0x7fff : bits);
}

#define HF_ALT_TRUNC(fmt, T, E, F) \
    static inline uint32_t fmt##_to_hf_alt(T x) { \
        T magnitude = x & (FP_SIGN(T, E, F) - 1); \
        uint32_t sign = (x & FP_SIGN(T, E, F)) != 0 ? 0x8000 : 0; \
        T sig = magnitude & (FP_INT_BIT(T, F) - 1); \
        T kept; \
        unsigned int e = (unsigned int)(magnitude >> (F)); \
        \
        if (magnitude > FP_INF(T, E, F)) { \
            return sign; \
        } \
        if (e != 0) { \
            sig |= FP_INT_BIT(T, F); \
        } else { \
            e = 1; \
        } \
        kept = sig >> ((F) - 13); \
        return hf_alt_round_pack( \
            sign, e + FP_BIAS(5) - FP_BIAS(E), \
            (uint32_t)kept | (uint32_t)((kept << ((F) - 13)) != sig) \
        ); \
    }

HF_ALT_TRUNC(sf, uint32_t, 8, 23)
HF_ALT_TRUNC(df, uint64_t, 11, 52)

uint32_t __gnu_h2f_alternative(uint32_t a) {
    uint32_t magnitude = a & 0x7fff;
    uint32_t bits = (a & 0x8000) << 16;

    if (magnitude != 0) {
        unsigned int e;
        uint32_t sig = hf_normalise(magnitude, &e);

        e = e + FP_BIAS(8) - FP_BIAS(5) - 1;
        bits |= ((uint32_t)e << 23) + (sig << 13);
    }
    return bits;
}

int16_t __gnu_f2h_alternative(uint32_t a) {
    return (int16_t)sf_to_hf_alt(a);
}

int16_t __gnu_d2h_alternative(uint64_t a) {
    return (int16_t)df_to_hf_alt(a);
}

#if defined(__ARM_EABI__)
FP_ALIAS(uint32_t, __aeabi_h2f, "__gnu_h2f_ieee", (uint32_t a))
FP_ALIAS(int16_t, __aeabi_f2h, "__gnu_f2h_ieee", (uint32_t a))
FP_ALIAS(int16_t, __aeabi_d2h, "__gnu_d2h_ieee", (uint64_t a))
FP_ALIAS(uint32_t, __aeabi_h2f_alt, "__gnu_h2f_alternative", (uint32_t a))
FP_ALIAS(int16_t, __aeabi_f2h_alt, "__gnu_f2h_alternative", (uint32_t a))
FP_ALIAS(int16_t, __aeabi_d2h_alt, "__gnu_d2h_alternative", (uint64_t a))
#endif

#if defined(__clang__)

#if !defined(__ARM_EABI__)
FP_ALIAS(int16_t, __truncdfhf2, "__gnu_d2h_ieee", (uint64_t a))
#endif

// What only Clang calls goes by the procedure call standard in use, with
// floating-point registers where that has them. That is all there is from here
// to the end of the section.
#undef FP_ABI
#define FP_ABI

FP16_BITS(hf, hf_value)
FP16_BITS(bf, hf_value)
FP_STICKY_SHIFT(bf, uint32_t, 7)
FP_ROUND_PACK(bf, uint32_t, 8, 7)
FP_TRUNC_BITS(bf, uint32_t, 8, 7, sf, uint32_t, 8, 23)
FP_TRUNC_BITS(bf, uint32_t, 8, 7, df, uint64_t, 11, 52)

hf_value __truncsfbf2(float a) {
    uint32_t bits;

    __builtin_memcpy(&bits, &a, sizeof(uint32_t));
    __asm__ ("" : "+g"(bits));
    return bf_from_bits(sf_to_bf(bits));
}

hf_value __truncdfbf2(double a) {
    uint64_t bits;

    __builtin_memcpy(&bits, &a, sizeof(uint64_t));
    __asm__ ("" : "+g"(bits));
    return bf_from_bits(df_to_bf(bits));
}

FP_TO_INT(hf, hf_value, uint32_t, 5, 10, di, int64_t, uint64_t, 64)
FP_FROM_INT(hf, hf_value, uint32_t, 5, 10, di, int64_t, uint64_t, 64)

#endif // defined(__clang__)

#elif SOFT_HF

FP16_BITS(hf, hf_value)
FP_EXTEND(hf, hf_value, uint32_t, 5, 10, sf, sf_value, uint32_t, 8, 23)
FP_TRUNC(hf, hf_value, uint32_t, 5, 10, sf, sf_value, uint32_t, 8, 23)

// Older releases of Clang call these for __fp16, with half in an integer
// register, however they pass _Float16.
#if defined(__clang__)
FP_ABI sf_value __gnu_h2f_ieee(hf_register a) {
    return sf_from_bits(sf_from_hf((uint16_t)a));
}

FP_ABI uint16_t __gnu_f2h_ieee(sf_value a) {
    return (uint16_t)sf_to_hf(sf_to_bits(a));
}
#endif

#if SOFT_DOUBLE
FP_EXTEND(hf, hf_value, uint32_t, 5, 10, df, df_value, uint64_t, 11, 52)
#if HF_SOFT_RESULT_AS_INT && defined(__riscv_float_abi_single)
FP_TRUNC_BITS(hf, uint32_t, 5, 10, df, uint64_t, 11, 52)

uint16_t __truncdfhf2(df_value a) {
    return (uint16_t)df_to_hf(df_to_bits(a));
}
#else
FP_TRUNC(hf, hf_value, uint32_t, 5, 10, df, df_value, uint64_t, 11, 52)
#endif
#endif

#if (SOFT_QUAD || (QUAD_OWN_NAMES && HAS_INT128)) && !defined(__powerpc__)
#define FP16_QUAD 1
WIDE_EXTEND(hf, hf_value, uint32_t, 5, 10, tf, quad_value, 32767, 112)

// Workaround: Clang before 22, hard-float MIPS64: it calls this with the two
// words of the value in the integer registers that come first, in their order
// in memory, where the C ABI has them in floating-point registers.
#if defined(__clang__) && __clang_major__ < 22 && defined(__mips64) && !defined(__mips_soft_float)

WIDE_TRUNC_BITS(hf, uint32_t, 5, 10, tf, 32767, 112)

hf_value __trunctfhf2(uint64_t first, uint64_t second) {
    uint64_t words[2] = { first, second };
    struct wide x;

    __builtin_memcpy(&x, words, sizeof(words));
    return hf_from_bits(tf_to_hf(x));
}

#elif HF_SOFT_RESULT_AS_INT

WIDE_TRUNC_BITS(hf, uint32_t, 5, 10, tf, 32767, 112)

uint16_t __trunctfhf2(quad_value a) {
    return (uint16_t)tf_to_hf(tf_to_bits(a));
}

#else // defined(__clang__) && __clang_major__ < 22 && defined(__mips64) && !defined(__mips_soft_float)
WIDE_TRUNC(hf, hf_value, uint32_t, 5, 10, tf, quad_value, 32767, 112)
#endif // defined(__clang__) && __clang_major__ < 22 && defined(__mips64) && !defined(__mips_soft_float)

#else // (SOFT_QUAD || (QUAD_OWN_NAMES && HAS_INT128)) && !defined(__powerpc__)

#define FP16_QUAD 0

// 32-bit SPARC, as it passes its other routines of long double.
#if QUAD_OWN_NAMES && TF_IN_REGISTERS
WIDE_TRUNC_BITS(hf, uint32_t, 5, 10, tf, 32767, 112)
TF_TO(__trunctfhf2, hf_value, hf_from_bits(tf_to_hf(x)))
#elif QUAD_OWN_NAMES
WIDE_TRUNC(hf, hf_value, uint32_t, 5, 10, tf, quad_value, 32767, 112)
#endif

#endif // (SOFT_QUAD || (QUAD_OWN_NAMES && HAS_INT128)) && !defined(__powerpc__)

#if defined(__i386__) || defined(__x86_64__)

WIDE_TRUNC(hf, hf_value, uint32_t, 5, 10, xf, XF_PARAMETER, XF_EXP_MAX, 63)

#if defined(__clang__)
WIDE_EXTEND_BITS(hf, uint32_t, 5, 10, xf, XF_EXP_MAX, 63)

void __extendhfxf2(hf_value a) {
    xf_return(xf_from_hf(hf_to_bits(a)));
}
#elif XF_RETURNED
WIDE_EXTEND(hf, hf_value, uint32_t, 5, 10, xf, xf_value, XF_EXP_MAX, 63)
#endif

#endif

#if !HF_PASSED_AS_INT

// Arithmetic always goes through float, but for these.
FP_COMPARE(hf, uint32_t, 5, 10)
FP_RELATION_NAMES(hf, hf_value, uint32_t)
FP_UNORD_ROUTINE(hf, hf_value, uint32_t, 5, 10)
FP_TO_INT(hf, hf_value, uint32_t, 5, 10, si, int32_t, uint32_t, 32)
FP_TO_INT(hf, hf_value, uint32_t, 5, 10, di, int64_t, uint64_t, 64)
FP_FROM_INT(hf, hf_value, uint32_t, 5, 10, si, int32_t, uint32_t, 32)
FP_FROM_INT(hf, hf_value, uint32_t, 5, 10, di, int64_t, uint64_t, 64)
#if HAS_INT128
FP_TO_INT(hf, hf_value, uint32_t, 5, 10, ti, i128, u128, 128)
FP_FROM_INT(hf, hf_value, uint32_t, 5, 10, ti, i128, u128, 128)
#endif

// No macro tells of __bf16 on Clang.
#if defined(__BFLT16_MANT_DIG__) \
 || (defined(__clang__) \
  && (defined(__i386__) || defined(__x86_64__) || defined(__aarch64__) || defined(__riscv) \
   || defined(__loongarch__)))

// bfloat16 travels as half does.
//
// Workaround: Clang 17 and 18, IA-32: __bf16 comes back on the x87 stack, as a
// float whose image holds its bits, so these are written with that type there.
#if defined(__clang__) && defined(__i386__) && (__clang_major__ == 17 || __clang_major__ == 18)
typedef __bf16 bf_value;
#else
typedef hf_value bf_value;
#endif

#define SOFT_BF 1

FP16_BITS(bf, bf_value)
FP_STICKY_SHIFT(bf, uint32_t, 7)
FP_ROUND_PACK(bf, uint32_t, 8, 7)
FP_COMPARE(bf, uint32_t, 8, 7)
FP_RELATION_NAMES(bf, bf_value, uint32_t)
FP_UNORD_ROUTINE(bf, bf_value, uint32_t, 8, 7)
FP_FROM_INT(bf, bf_value, uint32_t, 8, 7, si, int32_t, uint32_t, 32)
FP_FROM_INT(bf, bf_value, uint32_t, 8, 7, di, int64_t, uint64_t, 64)
#if HAS_INT128
FP_FROM_INT(bf, bf_value, uint32_t, 8, 7, ti, i128, u128, 128)
#endif
FP_TRUNC(bf, bf_value, uint32_t, 8, 7, sf, sf_value, uint32_t, 8, 23)
#if SOFT_DOUBLE
FP_TRUNC(bf, bf_value, uint32_t, 8, 7, df, df_value, uint64_t, 11, 52)
#endif
#if FP16_QUAD
WIDE_TRUNC(bf, bf_value, uint32_t, 8, 7, tf, quad_value, 32767, 112)
#endif
#if defined(__i386__) || defined(__x86_64__)
WIDE_TRUNC(bf, bf_value, uint32_t, 8, 7, xf, XF_PARAMETER, XF_EXP_MAX, 63)
#endif

// bfloat16 is the top half of float.
FP_ABI sf_value __extendbfsf2(bf_value a) {
    uint32_t x = bf_to_bits(a);
    uint32_t magnitude = x & (FP_SIGN(uint32_t, 8, 7) - 1);

    if (magnitude > FP_INF(uint32_t, 8, 7)) {
        return sf_from_bits(FP_NAN(uint32_t, 8, 23));
    }
    return sf_from_bits(x << 16);
}

// With its integer bit at bit 10, the significand of a half value is lined up
// with what the core works on for bfloat16, and all of its value is in there.
FP_ABI bf_value __trunchfbf2(hf_value a) {
    uint32_t x = hf_to_bits(a);
    uint32_t sign = x & FP_SIGN(uint32_t, 5, 10);
    uint32_t magnitude = x & (FP_SIGN(uint32_t, 5, 10) - 1);
    uint32_t bits = sign;
    unsigned int e;

    if (magnitude > FP_INF(uint32_t, 5, 10)) {
        bits = FP_NAN(uint32_t, 8, 7);
    } else if (magnitude == FP_INF(uint32_t, 5, 10)) {
        bits |= FP_INF(uint32_t, 8, 7);
    } else if (magnitude != 0) {
        uint32_t sig = hf_normalise(magnitude, &e);

        bits = bf_round_pack(sign, e + FP_BIAS(8) - FP_BIAS(5), sig);
    }
    return bf_from_bits(bits);
}

#endif // defined(__BFLT16_MANT_DIG__) || (defined(__clang__) && (defined(__i386__) || defined(__x86_64__) || defined(__aarch64__) || defined(__riscv) || defined(__loongarch__)))

#endif // !HF_PASSED_AS_INT

#endif // defined(__arm__)

#endif // LGRT_SOFT_FLOAT

// Complex multiplication and division, and powers to an int. Their arithmetic
// goes through FMT_cx_add, _sub, _mul, and _div, over a type V: the type of
// the format, whose operators reach the FPU where the target has one and the
// routines above where it does not, or T where C cannot use that type.
//
// With a floating-point V, each operation stores its result in a volatile
// object and reads it back. Whatever their flags, that leaves compilers
// nothing to contract into a fused operation, to reassociate, to replace with
// the reciprocal of a divisor, or to gather into a power, which would be a
// call to these routines. It also takes off any excess precision, as on the
// x87, so that the bits of a result are what the next operation gets.
// Classifying a value, giving it a sign, and making an infinity or a NaN go on
// the bits in T, which no flag about floating-point values reaches.

// Below the sum of the exponents of any two nonzero values of a format.
#define CX_ZERO_EXPONENT(M) ((unsigned int)0 - ((unsigned int)(M) + 1) * 4)

// Exponents are as in the core: unsigned for -ftrapv, wrapping below zero.
__attribute__((__unused__)) static inline unsigned int cx_larger(unsigned int a, unsigned int b) {
    return (int)(a - b) < 0 ? b : a;
}

// The bits of a format. FMT_cx_split gives a finite value with its exponent
// taken out, in [1, 2). FMT_cx_scale adds k to the exponent of a finite value,
// rounding a subnormal result and giving an infinity for one too large.
// FMT_cx_down takes n off the exponent of a value below 4, which stays normal,
// or gives a zero of its sign where the value would be too small to change
// what it gets added to, which is at least 1.
#define CX_BITS(fmt, T, E, F) \
    static inline bool fmt##_cx_negative(T x) { \
        return (x & FP_SIGN(T, E, F)) != 0; \
    } \
    \
    static inline T fmt##_cx_magnitude(T x) { \
        return x & (FP_SIGN(T, E, F) - 1); \
    } \
    \
    static inline T fmt##_cx_signed(bool negative, T magnitude) { \
        return (negative ? FP_SIGN(T, E, F) : 0) | magnitude; \
    } \
    \
    static inline bool fmt##_cx_less(T a, T b) { \
        return a < b; \
    } \
    \
    FP_HELPER T fmt##_cx_split(T x, unsigned int *e) { \
        T sign = x & FP_SIGN(T, E, F); \
        T magnitude = x - sign; \
        T sig; \
        unsigned int field; \
        \
        if (magnitude == 0) { \
            *e = CX_ZERO_EXPONENT(FP_EXP_MAX(E)); \
            return x; \
        } \
        sig = fmt##_normalise(magnitude, &field); \
        *e = field - FP_BIAS(E); \
        return sign + ((T)(FP_BIAS(E) - 1) << (F)) + sig; \
    } \
    \
    FP_HELPER T fmt##_cx_down(T x, unsigned int n) { \
        if (n > (F) + 6 || (x & (FP_SIGN(T, E, F) - 1)) == 0) { \
            return x & FP_SIGN(T, E, F); \
        } \
        return x - ((T)n << (F)); \
    } \
    \
    FP_HELPER T fmt##_cx_scale(T x, unsigned int k) { \
        T sign = x & FP_SIGN(T, E, F); \
        T magnitude = x - sign; \
        T sig; \
        unsigned int field; \
        \
        if (magnitude == 0) { \
            return x; \
        } \
        sig = fmt##_normalise(magnitude, &field); \
        return fmt##_round_pack(sign, field + k, sig << 3); \
    }

#define CX_WIDE_BITS(fmt, M, F) \
    static inline bool fmt##_cx_negative(struct wide x) { \
        return (x.high & WIDE_SIGN) != 0; \
    } \
    \
    static inline struct wide fmt##_cx_magnitude(struct wide x) { \
        return WIDE_MAGNITUDE(x); \
    } \
    \
    static inline struct wide fmt##_cx_signed(bool negative, struct wide magnitude) { \
        magnitude.high |= negative ? WIDE_SIGN : 0; \
        return magnitude; \
    } \
    \
    static inline bool fmt##_cx_less(struct wide a, struct wide b) { \
        return wide_lt(a, b); \
    } \
    \
    static inline struct wide fmt##_cx_split(struct wide x, unsigned int *e) { \
        struct wide sig; \
        unsigned int field; \
        \
        if (fmt##_kind(WIDE_MAGNITUDE(x)) == FP_ZERO) { \
            *e = CX_ZERO_EXPONENT(M); \
            return x; \
        } \
        sig = fmt##_normalise(WIDE_MAGNITUDE(x), &field); \
        *e = field - WIDE_BIAS(M); \
        sig = wide_add(wide_shl(wide_make(0, WIDE_BIAS(M) - 1), (F)), sig); \
        sig.high |= x.high & WIDE_SIGN; \
        return sig; \
    } \
    \
    static inline struct wide fmt##_cx_down(struct wide x, unsigned int n) { \
        if (n > (F) + 6 || fmt##_kind(WIDE_MAGNITUDE(x)) == FP_ZERO) { \
            return wide_make(x.high & WIDE_SIGN, 0); \
        } \
        return wide_sub(x, wide_shl(wide_make(0, n), (F))); \
    } \
    \
    static inline struct wide fmt##_cx_scale(struct wide x, unsigned int k) { \
        struct wide sig; \
        unsigned int field; \
        \
        if (fmt##_kind(WIDE_MAGNITUDE(x)) == FP_ZERO) { \
            return x; \
        } \
        sig = fmt##_normalise(WIDE_MAGNITUDE(x), &field); \
        return fmt##_round_pack(x.high & WIDE_SIGN, field + k, wide_shl(sig, 3)); \
    }

// The operations over a floating-point type, and the bits of its values.
#define CX_FP_LINEAR_OPERATIONS(fmt, V, T, to_bits, from_bits) \
    FP_ABI static inline T fmt##_cx_bits(V x) { \
        return to_bits(x); \
    } \
    \
    FP_ABI static inline V fmt##_cx_value(T x) { \
        return from_bits(x); \
    } \
    \
    FP_ABI static inline V fmt##_cx_add(V x, V y) { \
        volatile V result = x + y; \
        \
        return result; \
    } \
    \
    FP_ABI static inline V fmt##_cx_sub(V x, V y) { \
        volatile V result = x - y; \
        \
        return result; \
    } \
    \
    FP_ABI static inline V fmt##_cx_div(V x, V y) { \
        volatile V divisor = y; \
        volatile V result = x / divisor; \
        \
        return result; \
    }

#define CX_FP_OPERATIONS(fmt, V, T, to_bits, from_bits) \
    CX_FP_LINEAR_OPERATIONS(fmt, V, T, to_bits, from_bits) \
    \
    FP_ABI static inline V fmt##_cx_mul(V x, V y) { \
        volatile V result = x * y; \
        \
        return result; \
    }

// With V and T the same, the bits are the value.
#define CX_NO_CONVERSIONS(fmt, T) \
    static inline T fmt##_cx_bits(T x) { \
        return x; \
    } \
    \
    static inline T fmt##_cx_value(T x) { \
        return x; \
    }

// What the examples in Annex G of the C standard do where a part is not
// finite, on the bits. Their boxes are units of the smallest magnitude there
// is, or zeros. FMT_cx_term stands for a product: it has its sign, is zero if
// the product is, and otherwise has the magnitude of its larger factor. With a
// box for a factor, that is the magnitude of the product. Without one, each
// sum of two has a zero among its factors in place of a NaN, so at most one of
// them is not zero.
#define CX_SPECIAL_VALUES(fmt, T, zero, unit, inf, quiet) \
    FP_HELPER bool fmt##_cx_is(T x, int kind) { \
        return fmt##_kind(fmt##_cx_magnitude(x)) == kind; \
    } \
    \
    /* A box: a unit of the sign of x where x is of that kind, or a zero. */ \
    FP_HELPER T fmt##_cx_box(T x, int kind) { \
        return fmt##_cx_signed(fmt##_cx_negative(x), fmt##_cx_is(x, kind) ? (unit) : (zero)); \
    } \
    \
    FP_HELPER T fmt##_cx_no_nan(T x) { \
        if (fmt##_cx_is(x, FP_NOT_A_NUMBER)) { \
            return fmt##_cx_signed(fmt##_cx_negative(x), zero); \
        } \
        return x; \
    } \
    \
    FP_HELPER T fmt##_cx_negated(T x) { \
        return fmt##_cx_signed(!fmt##_cx_negative(x), fmt##_cx_magnitude(x)); \
    } \
    \
    FP_HELPER T fmt##_cx_term(T p, T q) { \
        T magnitude_p = fmt##_cx_magnitude(p); \
        T magnitude_q = fmt##_cx_magnitude(q); \
        bool negative = fmt##_cx_negative(p) != fmt##_cx_negative(q); \
        \
        if (fmt##_cx_is(p, FP_ZERO) || fmt##_cx_is(q, FP_ZERO)) { \
            return fmt##_cx_signed(negative, zero); \
        } \
        return fmt##_cx_signed( \
            negative, \
            fmt##_cx_less(magnitude_p, magnitude_q) ? magnitude_q : magnitude_p \
        ); \
    } \
    \
    /* An infinity times the sum of two products, or a zero times it. */ \
    FP_HELPER T fmt##_cx_infinity_times(T s, T t) { \
        T magnitude_s = fmt##_cx_magnitude(s); \
        T magnitude_t = fmt##_cx_magnitude(t); \
        bool below = fmt##_cx_less(magnitude_s, magnitude_t); \
        \
        if (!below && !fmt##_cx_less(magnitude_t, magnitude_s) \
         && (fmt##_cx_is(s, FP_ZERO) || fmt##_cx_negative(s) != fmt##_cx_negative(t))) { \
            return (quiet); \
        } \
        return fmt##_cx_signed(fmt##_cx_negative(below ? t : s), inf); \
    } \
    \
    FP_HELPER T fmt##_cx_zero_times(T s, T t) { \
        T magnitude_s = fmt##_cx_magnitude(s); \
        T magnitude_t = fmt##_cx_magnitude(t); \
        \
        if (fmt##_cx_less(magnitude_s, magnitude_t)) { \
            return fmt##_cx_signed(fmt##_cx_negative(t), zero); \
        } \
        if (fmt##_cx_less(magnitude_t, magnitude_s)) { \
            return fmt##_cx_signed(fmt##_cx_negative(s), zero); \
        } \
        return fmt##_cx_signed(fmt##_cx_negative(s) && fmt##_cx_negative(t), zero); \
    }

// Workaround: GCC 5, IA-32 with PIC and x87 off: it runs out of registers in
// the complex routines of double, unless these helpers stay out of line and
// are built as at -O1.
#if !defined(__clang__) && __GNUC__ == 5 && defined(__i386__) && defined(__PIC__) \
 && defined(_SOFT_FLOAT)
#   define CX_HELPER __attribute__((__noinline__, __optimize__("O1"))) static
#else
#   define CX_HELPER FP_HELPER
#endif

// Multiplication as in Annex G. Finite factors alone never give NaNs in both
// parts, as the signs of the products that would have to overflow for that
// disagree, so a NaN is among the factors if none is infinite.
#define CX_MULTIPLY(fmt, V, T) \
    FP_ABI static inline bool fmt##_cx_infinite(V x) { \
        return fmt##_cx_is(fmt##_cx_bits(x), FP_INFINITE); \
    } \
    \
    FP_HELPER void fmt##_cx_recover(T a, T b, T c, T d, bool overflowed, T *x, T *y) { \
        bool z_infinite = fmt##_cx_is(a, FP_INFINITE) || fmt##_cx_is(b, FP_INFINITE); \
        bool w_infinite = fmt##_cx_is(c, FP_INFINITE) || fmt##_cx_is(d, FP_INFINITE); \
        \
        if (!z_infinite && !w_infinite && !overflowed) { \
            return; \
        } \
        a = z_infinite ? fmt##_cx_box(a, FP_INFINITE) : fmt##_cx_no_nan(a); \
        b = z_infinite ? fmt##_cx_box(b, FP_INFINITE) : fmt##_cx_no_nan(b); \
        c = w_infinite ? fmt##_cx_box(c, FP_INFINITE) : fmt##_cx_no_nan(c); \
        d = w_infinite ? fmt##_cx_box(d, FP_INFINITE) : fmt##_cx_no_nan(d); \
        *x = fmt##_cx_infinity_times(fmt##_cx_term(a, c), fmt##_cx_negated(fmt##_cx_term(b, d))); \
        *y = fmt##_cx_infinity_times(fmt##_cx_term(a, d), fmt##_cx_term(b, c)); \
    } \
    \
    CX_HELPER FP_ABI void fmt##_cx_multiply(V a, V b, V c, V d, V *parts) { \
        V ac = fmt##_cx_mul(a, c); \
        V bd = fmt##_cx_mul(b, d); \
        V ad = fmt##_cx_mul(a, d); \
        V bc = fmt##_cx_mul(b, c); \
        T x = fmt##_cx_bits(fmt##_cx_sub(ac, bd)); \
        T y = fmt##_cx_bits(fmt##_cx_add(ad, bc)); \
        \
        if (fmt##_cx_is(x, FP_NOT_A_NUMBER) && fmt##_cx_is(y, FP_NOT_A_NUMBER)) { \
            fmt##_cx_recover( \
                fmt##_cx_bits(a), fmt##_cx_bits(b), fmt##_cx_bits(c), fmt##_cx_bits(d), \
                fmt##_cx_infinite(ac) || fmt##_cx_infinite(bd) || fmt##_cx_infinite(ad) \
             || fmt##_cx_infinite(bc), &x, &y \
            ); \
        } \
        parts[0] = fmt##_cx_value(x); \
        parts[1] = fmt##_cx_value(y); \
    }

// Division. Scaling the denominator alone, as in the example in Annex G,
// leaves the numerator open to overflow and underflow, and scaling both by one
// factor still fails where the parts of one of them are far apart. So each
// part keeps an exponent of its own, as an integer without limits to reach,
// and the usual formula works on values in [1, 2). Two products meet in a sum
// once the smaller has its exponent lined up, and the exponents left over go
// back on the quotient at the end, the one place where a value can overflow or
// underflow, and then only if the result itself does.
//
// A value that is not finite, or a zero denominator, gives what the example
// does, but for sums of finite values that overflow there on the way to a
// zero, which Annex G requires, or to the infinite part of a result.
#define CX_DIVIDE(fmt, V, T, quiet, zero) \
    FP_HELPER FP_ABI T fmt##_cx_part( \
        V p, V q, unsigned int e_pq, V r, V s, unsigned int e_rs, bool subtract, V denominator, \
        unsigned int e_w \
    ) { \
        unsigned int top = cx_larger(e_pq, e_rs); \
        V pq = fmt##_cx_value(fmt##_cx_down(fmt##_cx_bits(fmt##_cx_mul(p, q)), top - e_pq)); \
        V rs = fmt##_cx_value(fmt##_cx_down(fmt##_cx_bits(fmt##_cx_mul(r, s)), top - e_rs)); \
        V sum = subtract ? fmt##_cx_sub(pq, rs) : fmt##_cx_add(pq, rs); \
        \
        if (fmt##_cx_is(fmt##_cx_bits(sum), FP_ZERO)) { \
            return fmt##_cx_bits(sum); \
        } \
        return fmt##_cx_scale(fmt##_cx_bits(fmt##_cx_div(sum, denominator)), top - e_w - e_w); \
    } \
    \
    FP_HELPER FP_ABI void fmt##_cx_quotient(T a, T b, T c, T d, T *x, T *y) { \
        unsigned int e_a; \
        unsigned int e_b; \
        unsigned int e_c; \
        unsigned int e_d; \
        V m_a = fmt##_cx_value(fmt##_cx_split(a, &e_a)); \
        V m_b = fmt##_cx_value(fmt##_cx_split(b, &e_b)); \
        T s_c = fmt##_cx_split(c, &e_c); \
        T s_d = fmt##_cx_split(d, &e_d); \
        V m_c = fmt##_cx_value(s_c); \
        V m_d = fmt##_cx_value(s_d); \
        unsigned int e_w = cx_larger(e_c, e_d); \
        V w_c = fmt##_cx_value(fmt##_cx_down(s_c, e_w - e_c)); \
        V w_d = fmt##_cx_value(fmt##_cx_down(s_d, e_w - e_d)); \
        V denominator = fmt##_cx_add(fmt##_cx_mul(w_c, w_c), fmt##_cx_mul(w_d, w_d)); \
        \
        *x = fmt##_cx_part(m_a, m_c, e_a + e_c, m_b, m_d, e_b + e_d, false, denominator, e_w); \
        *y = fmt##_cx_part(m_b, m_c, e_b + e_c, m_a, m_d, e_a + e_d, true, denominator, e_w); \
    } \
    \
    CX_HELPER FP_ABI void fmt##_cx_divide(T a, T b, T c, T d, V *parts) { \
        bool a_finite = !fmt##_cx_is(a, FP_INFINITE) && !fmt##_cx_is(a, FP_NOT_A_NUMBER); \
        bool b_finite = !fmt##_cx_is(b, FP_INFINITE) && !fmt##_cx_is(b, FP_NOT_A_NUMBER); \
        T x = (quiet); \
        T y = (quiet); \
        \
        if (fmt##_cx_is(c, FP_INFINITE) || fmt##_cx_is(d, FP_INFINITE)) { \
            if (a_finite && b_finite) { \
                T box_c = fmt##_cx_box(c, FP_INFINITE); \
                T box_d = fmt##_cx_box(d, FP_INFINITE); \
                \
                x = fmt##_cx_zero_times(fmt##_cx_term(a, box_c), fmt##_cx_term(b, box_d)); \
                y = fmt##_cx_zero_times( \
                    fmt##_cx_term(b, box_c), fmt##_cx_negated(fmt##_cx_term(a, box_d)) \
                ); \
            } \
        } else if (fmt##_cx_is(c, FP_NOT_A_NUMBER) || fmt##_cx_is(d, FP_NOT_A_NUMBER)) { \
            /* Nothing recovers from these. */ \
        } else if (fmt##_cx_is(c, FP_ZERO) && fmt##_cx_is(d, FP_ZERO)) { \
            T box_c = fmt##_cx_box(c, FP_ZERO); \
            \
            x = fmt##_cx_infinity_times(fmt##_cx_term(box_c, fmt##_cx_no_nan(a)), zero); \
            y = fmt##_cx_infinity_times(fmt##_cx_term(box_c, fmt##_cx_no_nan(b)), zero); \
        } else if (fmt##_cx_is(a, FP_INFINITE) || fmt##_cx_is(b, FP_INFINITE)) { \
            T box_a = fmt##_cx_box(a, FP_INFINITE); \
            T box_b = fmt##_cx_box(b, FP_INFINITE); \
            T box_c = fmt##_cx_box(c, FP_FINITE); \
            T box_d = fmt##_cx_box(d, FP_FINITE); \
            \
            x = fmt##_cx_infinity_times( \
                fmt##_cx_term(box_a, box_c), fmt##_cx_term(box_b, box_d) \
            ); \
            y = fmt##_cx_infinity_times( \
                fmt##_cx_term(box_b, box_c), fmt##_cx_negated(fmt##_cx_term(box_a, box_d)) \
            ); \
        } else if (a_finite && b_finite) { \
            fmt##_cx_quotient(a, b, c, d, &x, &y); \
        } \
        parts[0] = fmt##_cx_value(x); \
        parts[1] = fmt##_cx_value(y); \
    }

// A power by repeated squaring, of the magnitude of n, which unsigned int
// holds for the most negative int too, whatever the width of int. Nothing
// squares x past what the result needs. A negative n takes the reciprocal of
// the power, by parts as division does, as with -ffast-math compilers can make
// any division an estimate that gets zeros, infinities, and the limits of the
// range wrong. Where the divisor is in [1, 2), that is only less exact. For
// the same reason, division above does not divide a zero.
#define CX_POWER(fmt, V, T, zero, inf, one) \
    FP_HELPER FP_ABI V fmt##_cx_reciprocal(V x) { \
        T bits = fmt##_cx_bits(x); \
        bool negative = fmt##_cx_negative(bits); \
        unsigned int e; \
        V m; \
        \
        if (fmt##_cx_is(bits, FP_NOT_A_NUMBER)) { \
            return x; \
        } \
        if (fmt##_cx_is(bits, FP_INFINITE)) { \
            return fmt##_cx_value(fmt##_cx_signed(negative, zero)); \
        } \
        if (fmt##_cx_is(bits, FP_ZERO)) { \
            return fmt##_cx_value(fmt##_cx_signed(negative, inf)); \
        } \
        m = fmt##_cx_value(fmt##_cx_split(bits, &e)); \
        return fmt##_cx_value( \
            fmt##_cx_scale( \
                fmt##_cx_bits(fmt##_cx_div(fmt##_cx_value(one), m)), (unsigned int)0 - e \
            ) \
        ); \
    } \
    \
    FP_HELPER FP_ABI V fmt##_cx_power(V x, int n) { \
        unsigned int m = n < 0 ? (unsigned int)0 - (unsigned int)n : (unsigned int)n; \
        V result = fmt##_cx_value(one); \
        \
        for (;;) { \
            if ((m & 1) != 0) { \
                result = fmt##_cx_mul(result, x); \
            } \
            m >>= 1; \
            if (m == 0) { \
                break; \
            } \
            x = fmt##_cx_mul(x, x); \
        } \
        return n < 0 ? fmt##_cx_reciprocal(result) : result; \
    }

#define CX_NARROW(fmt, V, T, E, F) \
    CX_BITS(fmt, T, E, F) \
    CX_SPECIAL_VALUES(fmt, T, (T)0, (T)1, FP_INF(T, E, F), FP_NAN(T, E, F)) \
    CX_MULTIPLY(fmt, V, T) \
    CX_DIVIDE(fmt, V, T, FP_NAN(T, E, F), (T)0) \
    CX_POWER(fmt, V, T, (T)0, FP_INF(T, E, F), (T)FP_BIAS(E) << (F))

#define CX_WIDE(fmt, V, M, F) \
    CX_WIDE_BITS(fmt, M, F) \
    CX_SPECIAL_VALUES( \
        fmt, struct wide, wide_make(0, 0), wide_make(0, 1), WIDE_INF(M, F), WIDE_NAN(M, F) \
    ) \
    CX_MULTIPLY(fmt, V, struct wide) \
    CX_DIVIDE(fmt, V, struct wide, WIDE_NAN(M, F), wide_make(0, 0)) \
    CX_POWER( \
        fmt, V, struct wide, wide_make(0, 0), WIDE_INF(M, F), \
        wide_shl(wide_make(0, WIDE_BIAS(M)), (F)) \
    )

// The type that powers take their exponent in.
//
// Workaround: Clang before 12, 64-bit RISC-V: it zero-extends the exponent for
// these calls, where the ABI has it sign-extended and code compiled for int
// relies on that. So they take all of the register there, and narrow it.
#if defined(__clang__) && __clang_major__ < 12 && defined(__riscv) && __riscv_xlen == 64
typedef long powi_exponent;
#else
typedef int powi_exponent;
#endif

// The routines, with V for the parts of a value and Z for the whole of one,
// which goes by the rules of the target for complex values.
//
// Workaround: GCC 5, 6, and 8, m68k without an FPU: it crashes on a copy into
// the whole of one with __builtin_memcpy, hence the unions.
#define CX_NAMED_ROUTINES(fmt, V, Z, mul_name, div_name, powi_name) \
    FP_ABI Z mul_name(V a, V b, V c, V d) { \
        union { \
            V parts[2]; \
            Z whole; \
        } z; \
        \
        fmt##_cx_multiply(a, b, c, d, z.parts); \
        return z.whole; \
    } \
    \
    FP_ABI Z div_name(V a, V b, V c, V d) { \
        union { \
            V parts[2]; \
            Z whole; \
        } z; \
        \
        fmt##_cx_divide( \
            fmt##_cx_bits(a), fmt##_cx_bits(b), fmt##_cx_bits(c), fmt##_cx_bits(d), z.parts \
        ); \
        return z.whole; \
    } \
    \
    FP_ABI V powi_name(V x, powi_exponent n) { \
        return fmt##_cx_power(x, (int)n); \
    }

#define CX_ROUTINES(fmt, cfmt, V, Z) \
    CX_NAMED_ROUTINES(fmt, V, Z, __mul##cfmt##3, __div##cfmt##3, __powi##fmt##2)

// GCC declares the complex routines itself, with the complex types, as
// ordinary code of the target, so those that differ from that have other names
// in C.
#define CX_LABELLED_ROUTINES(fmt, cfmt, V, Z) \
    FP_ABI Z mul##cfmt##3(V a, V b, V c, V d) \
        __asm__ ("__mul" #cfmt "3"); \
    FP_ABI Z div##cfmt##3(V a, V b, V c, V d) \
        __asm__ ("__div" #cfmt "3"); \
    FP_ABI V powi##fmt##2(V x, powi_exponent n) \
        __asm__ ("__powi" #fmt "2"); \
    CX_NAMED_ROUTINES(fmt, V, Z, mul##cfmt##3, div##cfmt##3, powi##fmt##2)

// The operations on the bits, from the core of the format.
#define CX_WIDE_OPERATIONS(fmt) \
    CX_NO_CONVERSIONS(fmt, struct wide) \
    \
    static inline struct wide fmt##_cx_add(struct wide x, struct wide y) { \
        return fmt##_add(x, y); \
    } \
    \
    static inline struct wide fmt##_cx_sub(struct wide x, struct wide y) { \
        y.high ^= WIDE_SIGN; \
        return fmt##_add(x, y); \
    } \
    \
    static inline struct wide fmt##_cx_mul(struct wide x, struct wide y) { \
        return fmt##_mul(x, y); \
    } \
    \
    static inline struct wide fmt##_cx_div(struct wide x, struct wide y) { \
        return fmt##_div(x, y); \
    }

#if LGRT_SOFT_FLOAT

#if FP_PASSED_AS_INT

// These targets pass values as integers here too, and take their arithmetic
// from the routines above. GCC allows floating-point types on 32-bit ARM with
// an FPU only without -mgeneral-regs-only, with nothing to tell of that, so
// assembly, which that option leaves alone, reaches the FPU there. The
// registers it names need not be saved across calls.
#define CX_CALL(fmt, T, name) \
    static inline T fmt##_cx_##name(T x, T y) { \
        return __##name##fmt##3(x, y); \
    }

#define CX_VFP_SINGLE(name, instruction) \
    static inline uint32_t sf_cx_##name(uint32_t x, uint32_t y) { \
        uint32_t result; \
        \
        __asm__ ( \
            "vmov s14, %1\n\t" \
            "vmov s15, %2\n\t" \
            instruction " s14, s14, s15\n\t" \
            "vmov %0, s14" \
            : "=r"(result) \
            : "r"(x), "r"(y) \
            : "s14", "s15" \
        ); \
        return result; \
    }

#define CX_VFP_DOUBLE(name, instruction) \
    static inline uint64_t df_cx_##name(uint64_t x, uint64_t y) { \
        uint64_t result; \
        \
        __asm__ ( \
            "vmov d6, %Q1, %R1\n\t" \
            "vmov d7, %Q2, %R2\n\t" \
            instruction " d6, d6, d7\n\t" \
            "vmov %Q0, %R0, d6" \
            : "=r"(result) \
            : "r"(x), "r"(y) \
            : "d6", "d7" \
        ); \
        return result; \
    }

#if defined(__arm__) && !defined(__SOFTFP__) && defined(__ARM_FP) && (__ARM_FP & 4) != 0
CX_VFP_SINGLE(add, "vadd.f32")
CX_VFP_SINGLE(sub, "vsub.f32")
CX_VFP_SINGLE(mul, "vmul.f32")
CX_VFP_SINGLE(div, "vdiv.f32")
#else
CX_CALL(sf, uint32_t, add)
CX_CALL(sf, uint32_t, sub)
CX_CALL(sf, uint32_t, mul)
CX_CALL(sf, uint32_t, div)
#endif

CX_NO_CONVERSIONS(sf, uint32_t)
CX_NARROW(sf, uint32_t, uint32_t, 8, 23)

#if SOFT_DOUBLE
#if defined(__arm__) && !defined(__SOFTFP__) && defined(__ARM_FP) && (__ARM_FP & 8) != 0
CX_VFP_DOUBLE(add, "vadd.f64")
CX_VFP_DOUBLE(sub, "vsub.f64")
CX_VFP_DOUBLE(mul, "vmul.f64")
CX_VFP_DOUBLE(div, "vdiv.f64")
#else
CX_CALL(df, uint64_t, add)
CX_CALL(df, uint64_t, sub)
CX_CALL(df, uint64_t, mul)
CX_CALL(df, uint64_t, div)
#endif

CX_NO_CONVERSIONS(df, uint64_t)
CX_NARROW(df, uint64_t, uint64_t, 11, 52)
#endif

#if defined(__ARM_PCS_VFP)

// Where floating-point registers pass values, C cannot have the types that use
// them, as above, so assembly moves them to memory for C to work on, and takes
// the results from there.
#define CX_VFP_ENTRY(name, symbol, frame, store, helper, load) \
    void name(void) __asm__ (symbol); \
    __attribute__((__naked__)) void name(void) { \
        __asm__ volatile ( \
            ".syntax unified\n\t" \
            ASM_BTI \
            "push {r4, lr}\n\t" \
            "sub sp, sp, #" frame "\n\t" \
            store \
            "bl " helper "\n\t" \
            load \
            "add sp, sp, #" frame "\n\t" \
            "pop {r4, pc}\n\t" \
            ASM_END \
        ); \
    }

#define CX_VFP_HELPER ASM_CALLED

#define CX_VFP_ROUTINES(fmt, cfmt, T, frame, first, second, last) \
    CX_VFP_HELPER void mul##cfmt##3_parts(T *parts) { \
        fmt##_cx_multiply(parts[0], parts[1], parts[2], parts[3], parts); \
    } \
    \
    CX_VFP_ENTRY( \
        mul##cfmt##3, "__mul" #cfmt "3", frame, \
        "vstmia sp, {" first "-" last "}\n\t" \
        "mov r0, sp\n\t", \
        "mul" #cfmt "3_parts", \
        "vldmia sp, {" first "-" second "}\n\t" \
    ) \
    \
    CX_VFP_HELPER void div##cfmt##3_parts(T *parts) { \
        fmt##_cx_divide(parts[0], parts[1], parts[2], parts[3], parts); \
    } \
    \
    CX_VFP_ENTRY( \
        div##cfmt##3, "__div" #cfmt "3", frame, \
        "vstmia sp, {" first "-" last "}\n\t" \
        "mov r0, sp\n\t", \
        "div" #cfmt "3_parts", \
        "vldmia sp, {" first "-" second "}\n\t" \
    ) \
    \
    CX_VFP_HELPER void powi##fmt##2_value(T *value, int n) { \
        *value = fmt##_cx_power(*value, n); \
    } \
    \
    CX_VFP_ENTRY( \
        powi##fmt##2, "__powi" #fmt "2", "8", \
        "vstr " first ", [sp]\n\t" \
        "mov r1, r0\n\t" \
        "mov r0, sp\n\t", \
        "powi" #fmt "2_value", \
        "vldr " first ", [sp]\n\t" \
    )

CX_VFP_ROUTINES(sf, sc, uint32_t, "16", "s0", "s1", "s3")
#if SOFT_DOUBLE
CX_VFP_ROUTINES(df, dc, uint64_t, "32", "d0", "d1", "d3")
#endif

#else // defined(__ARM_PCS_VFP)

// The procedure call standards of ARM return complex values in memory, as they
// do structures of those sizes, and so do AVR and MSP430 for 16 bytes. 8 bytes
// go where uint64_t does on the latter two, the real part low. ARM without
// those standards returns them in registers, and only has soft floating point
// to care about, where GCC accepts the types.
#if defined(__ARM_EABI__) || !defined(__arm__)
struct dc_value {
    uint64_t parts[2];
};
#if defined(__arm__)
struct sc_value {
    uint32_t parts[2];
};
#define SC_RETURN struct sc_value
#else
#define SC_RETURN uint64_t
#endif
#define DC_RETURN struct dc_value
#else
__extension__ typedef _Complex float sc_value;
__extension__ typedef _Complex double dc_value;
#define SC_RETURN sc_value
#define DC_RETURN dc_value
#endif

CX_LABELLED_ROUTINES(sf, sc, uint32_t, SC_RETURN)
#if SOFT_DOUBLE
CX_LABELLED_ROUTINES(df, dc, uint64_t, DC_RETURN)
#endif

#endif // defined(__ARM_PCS_VFP)

// Half complex goes through float, as on other targets. Compilers call these
// only with arithmetic of that format. Each operand comes in a register of its
// own, and the result goes in r0, as a structure of its size does.
#if defined(__arm__) && defined(__ARM_FEATURE_FP16_SCALAR_ARITHMETIC)

static inline uint32_t hc_packed(uint32_t *parts) {
    uint32_t x = sf_to_hf(parts[0]);
    uint32_t y = sf_to_hf(parts[1]);

#if defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
    return (x << 16) | y;
#else
    return (y << 16) | x;
#endif
}

#define HC_FUNCTION(name, attributes, operation) \
    attributes uint32_t name(uint32_t a, uint32_t b, uint32_t c, uint32_t d) { \
        uint32_t parts[2]; \
        \
        operation( \
            sf_from_hf((uint16_t)a), sf_from_hf((uint16_t)b), sf_from_hf((uint16_t)c), \
            sf_from_hf((uint16_t)d), parts \
        ); \
        return hc_packed(parts); \
    }

#if defined(__ARM_PCS_VFP)

#   define HC_ROUTINE(name, operation) \
        HC_FUNCTION(name##_packed, CX_VFP_HELPER, operation) \
        \
        void name(void) __asm__ ("__" #name); \
        __attribute__((__naked__)) void name(void) { \
            __asm__ volatile ( \
                ".syntax unified\n\t" \
                ASM_BTI \
                "vmov r0, s0\n\t" \
                "vmov r1, s1\n\t" \
                "vmov r2, s2\n\t" \
                "vmov r3, s3\n\t" \
                "b " #name "_packed\n\t" \
                ASM_END \
            ); \
        }

#else // defined(__ARM_PCS_VFP)

#   define HC_ROUTINE(name, operation) \
        uint32_t name(uint32_t a, uint32_t b, uint32_t c, uint32_t d) __asm__ ("__" #name); \
        HC_FUNCTION(name, , operation)

#endif // defined(__ARM_PCS_VFP)

HC_ROUTINE(mulhc3, sf_cx_multiply)
HC_ROUTINE(divhc3, sf_cx_divide)

#endif // defined(__arm__) && defined(__ARM_FEATURE_FP16_SCALAR_ARITHMETIC)

#else // FP_PASSED_AS_INT

#if defined(__mips16) && defined(__mips_hard_float)
#   define CX_NATIVE_ROUTINES CX_LABELLED_ROUTINES
#else
#   define CX_NATIVE_ROUTINES CX_ROUTINES
#endif

CX_FP_OPERATIONS(sf, sf_value, uint32_t, sf_to_bits, sf_from_bits)
CX_NARROW(sf, sf_value, uint32_t, 8, 23)

__extension__ typedef _Complex float sc_value;

CX_NATIVE_ROUTINES(sf, sc, sf_value, sc_value)

#if SOFT_DOUBLE
// Workaround: Clang, Hexagon V67 and later: with -Ofast or
// -funsafe-math-optimizations, it leaves out of a product of doubles the steps
// that subnormal operands need, and no macro tells of both flags. So the core
// makes that product there.
#if defined(__hexagon__)
CX_FP_LINEAR_OPERATIONS(df, df_value, uint64_t, df_to_bits, df_from_bits)

static inline df_value df_cx_mul(df_value x, df_value y) {
    return df_from_bits(df_mul(df_to_bits(x), df_to_bits(y)));
}
#else
CX_FP_OPERATIONS(df, df_value, uint64_t, df_to_bits, df_from_bits)
#endif
CX_NARROW(df, df_value, uint64_t, 11, 52)

#if __SIZEOF_DOUBLE__ == 8
__extension__ typedef _Complex double dc_value;
#else
__extension__ typedef _Complex long double dc_value;
#endif

CX_NATIVE_ROUTINES(df, dc, df_value, dc_value)
#endif // SOFT_DOUBLE

// Half complex goes through float, which holds the products of its parts
// exactly and has the range for all that follows from them. Only the
// conversions back to half can overflow. Compilers go through float themselves
// on LoongArch, and nothing calls these there.
//
// Workaround: Clang before 14, every target with _Float16: it rejects _Complex
// _Float16, so it gets no such routines.
#if SOFT_HF && (!HF_PASSED_AS_INT || HF_CONVERSIONS_AS_INT) && !defined(__loongarch__) \
 && (!defined(__clang__) || __clang_major__ >= 14)

__extension__ typedef _Float16 hc_part;
__extension__ typedef _Complex _Float16 hc_value;

#define HC_ROUTINE(name, operation) \
    FP_ABI hc_value name(hc_part a, hc_part b, hc_part c, hc_part d) { \
        sf_value parts[2]; \
        hc_part results[2]; \
        hc_value z; \
        \
        operation; \
        results[0] = (hc_part)parts[0]; \
        results[1] = (hc_part)parts[1]; \
        __builtin_memcpy(&z, results, sizeof(results)); \
        return z; \
    }

HC_ROUTINE(__mulhc3, sf_cx_multiply((sf_value)a, (sf_value)b, (sf_value)c, (sf_value)d, parts))
HC_ROUTINE(
    __divhc3,
    sf_cx_divide(
        sf_cx_bits((sf_value)a), sf_cx_bits((sf_value)b), sf_cx_bits((sf_value)c),
        sf_cx_bits((sf_value)d), parts
    )
)

#endif // SOFT_HF && (!HF_PASSED_AS_INT || HF_CONVERSIONS_AS_INT) && !defined(__loongarch__) && (!defined(__clang__) || __clang_major__ >= 14)

#endif // FP_PASSED_AS_INT

#endif // LGRT_SOFT_FLOAT

#if HAS_IBM_128

// IBM long double, in C's own operators on double, each with its volatile
// store as above, so that the steps that recover what rounding lost stay as
// they are written whatever the flags. Infinities, NaNs, zeros, and exponents
// go on the bits.
//
// Multiplication and division first move both values to about 1, which keeps
// all between them away from overflow and underflow, and the exponents go back
// on at the end. There a result too large for the format is an infinity, and
// one in the subnormal range of double has no more than double has: it is
// rounded once, to nearest, into the first double.
//
// By the published analyses of these sums and products, a sum of normalised
// values is within about 3 * 2^-106 of the exact one, in proportion to it, and
// a product within about 7 * 2^-106. A quotient has three rounds of long
// division on exact remainders, for about the same, however inexact a division
// of two doubles is under -ffast-math. A result has its first double as the
// sum of both, rounded to nearest.
//
// Infinities and NaNs have a zero for the second double, and a NaN that comes
// out is the default one.

// Workaround: GCC 7, SPE: at -O0, a parameter of this type comes out wrong.
#if defined(__SPE__) && __GNUC__ == 7 && !defined(__OPTIMIZE__)
#   pragma GCC optimize("O1")
#endif

#define IBM_HELPER __attribute__((__unused__)) static inline
#define IBM_SIGN FP_SIGN(uint64_t, 11, 52)
#define IBM_INF FP_INF(uint64_t, 11, 52)
#define IBM_NAN FP_NAN(uint64_t, 11, 52)
#define IBM_ONE ((uint64_t)FP_BIAS(11) << 52)

struct ibm_bits {
    uint64_t high;
    uint64_t low;
};

IBM_HELPER struct ibm_bits ibm_make(uint64_t high, uint64_t low) {
    struct ibm_bits x;

    x.high = high;
    x.low = low;
    return x;
}

IBM_HELPER struct ibm_bits ibm_to_bits(ibm_value value) {
    struct ibm_bits bits;

#if defined(__SPE__) && __GNUC__ == 7
    // Workaround: GCC 7, SPE: crashes on the halves of a register value.
    __asm__ ("" : "+m"(value));
#endif
    __builtin_memcpy(&bits, &value, sizeof(struct ibm_bits));
    __asm__ ("" : "+g"(bits.high), "+g"(bits.low));
    return bits;
}

IBM_HELPER ibm_value ibm_from_bits(struct ibm_bits bits) {
    ibm_value value;

    __asm__ ("" : "+g"(bits.high), "+g"(bits.low));
    __builtin_memcpy(&value, &bits, sizeof(struct ibm_bits));
    return value;
}

// The bits of two doubles, with nothing beside an infinity or a NaN.
IBM_HELPER struct ibm_bits ibm_pair(df_value high, df_value low) {
    uint64_t first = df_to_bits(high);

    if ((first & (IBM_SIGN - 1)) >= IBM_INF) {
        return ibm_make(first, 0);
    }
    return ibm_make(first, df_to_bits(low));
}

// s + e is exactly a + b, with s that sum rounded.
IBM_HELPER void ibm_two_sum(df_value a, df_value b, df_value *s, df_value *e) {
    df_value sum = df_cx_add(a, b);
    df_value b_part = df_cx_sub(sum, a);
    df_value a_part = df_cx_sub(sum, b_part);

    *e = df_cx_add(df_cx_sub(a, a_part), df_cx_sub(b, b_part));
    *s = sum;
}

// The same, for a of no smaller a magnitude than b, or a zero.
IBM_HELPER void ibm_quick_sum(df_value a, df_value b, df_value *s, df_value *e) {
    df_value sum = df_cx_add(a, b);

    *e = df_cx_sub(b, df_cx_sub(sum, a));
    *s = sum;
}

// a as two doubles of 26 bits at most, for a value that can take 2^27 + 1.
IBM_HELPER void ibm_split(df_value a, df_value *high, df_value *low) {
    df_value factor = df_from_bits((uint64_t)0x41a0000002000000);
    df_value scaled = df_cx_mul(a, factor);

    *high = df_cx_sub(scaled, df_cx_sub(scaled, a));
    *low = df_cx_sub(a, *high);
}

// p + e is exactly a * b, with p that product rounded.
IBM_HELPER void ibm_two_product(df_value a, df_value b, df_value *p, df_value *e) {
    df_value product = df_cx_mul(a, b);
    df_value a_high;
    df_value a_low;
    df_value b_high;
    df_value b_low;
    df_value rest;

    ibm_split(a, &a_high, &a_low);
    ibm_split(b, &b_high, &b_low);
    rest = df_cx_sub(df_cx_mul(a_high, b_high), product);
    rest = df_cx_add(rest, df_cx_mul(a_high, b_low));
    rest = df_cx_add(rest, df_cx_mul(a_low, b_high));
    *e = df_cx_add(rest, df_cx_mul(a_low, b_low));
    *p = product;
}

// The sum of two pairs.
IBM_HELPER void ibm_sum(
    df_value a,
    df_value b,
    df_value c,
    df_value d,
    df_value *high,
    df_value *low
) {
    df_value s;
    df_value e;
    df_value t;
    df_value f;

    ibm_two_sum(a, c, &s, &e);
    ibm_two_sum(b, d, &t, &f);
    ibm_quick_sum(s, df_cx_add(e, t), &s, &e);
    ibm_quick_sum(s, df_cx_add(e, f), high, low);
}

// A value whose second double overlaps the first, moved to where it goes.
IBM_HELPER struct ibm_bits ibm_tidy(struct ibm_bits x) {
    uint64_t magnitude = x.high & (IBM_SIGN - 1);
    uint64_t magnitude_low = x.low & (IBM_SIGN - 1);
    df_value high;
    df_value low;

    if (magnitude >= IBM_INF) {
        return ibm_make(x.high, 0);
    }
    if (magnitude_low == 0 || (magnitude_low >> 52) + 52 < magnitude >> 52) {
        return x;
    }
    ibm_two_sum(df_from_bits(x.high), df_from_bits(x.low), &high, &low);
    return ibm_pair(high, low);
}

// The first double of a value, with its last bit set where the second double
// is not zero, on the side of the value: a double of the value that rounds to
// any narrower format as the value does.
IBM_HELPER uint64_t ibm_sticky(struct ibm_bits x) {
    if ((x.low & (IBM_SIGN - 1)) == 0) {
        return x.high;
    }
    if (((x.high ^ x.low) & IBM_SIGN) != 0) {
        return (x.high - 1) | 1;
    }
    return x.high | 1;
}

IBM_HELPER bool ibm_cx_negative(struct ibm_bits x) {
    return (x.high & IBM_SIGN) != 0;
}

// The value negated is both doubles negated.
IBM_HELPER struct ibm_bits ibm_opposite(struct ibm_bits x) {
    return ibm_make(x.high ^ IBM_SIGN, x.low ^ IBM_SIGN);
}

IBM_HELPER struct ibm_bits ibm_cx_magnitude(struct ibm_bits x) {
    return ibm_cx_negative(x) ? ibm_opposite(x) : x;
}

IBM_HELPER struct ibm_bits ibm_cx_signed(bool negative, struct ibm_bits magnitude) {
    return negative ? ibm_opposite(magnitude) : magnitude;
}

// Of a value without its sign.
IBM_HELPER int ibm_kind(struct ibm_bits magnitude) {
    if (magnitude.high == 0 && (magnitude.low & (IBM_SIGN - 1)) != 0) {
        return FP_FINITE;
    }
    return df_kind(magnitude.high);
}

// As FMT_compare: -1, 0, or 1, or unordered if either value is a NaN.
IBM_HELPER int ibm_compare(struct ibm_bits a, struct ibm_bits b, int unordered) {
    struct ibm_bits x = ibm_tidy(a);
    struct ibm_bits y = ibm_tidy(b);
    int order = df_compare(x.high, y.high, 2);

    if (order == 0) {
        order = df_compare(x.low, y.low, 2);
    }
    return order == 2 ? unordered : order;
}

IBM_HELPER bool ibm_cx_less(struct ibm_bits a, struct ibm_bits b) {
    return ibm_compare(a, b, 0) < 0;
}

// Adds k to the exponent of a finite value. One that reaches the subnormal
// range of double rounds once, into the first double: the second stands for a
// bit below all of those of the first, on its own side of it. What that leaves
// is at most half of the least double, which rounds to zero.
IBM_HELPER struct ibm_bits ibm_cx_scale(struct ibm_bits x, unsigned int k) {
    uint64_t sign = x.high & IBM_SIGN;
    uint64_t magnitude = x.high - sign;
    unsigned int field = (unsigned int)(magnitude >> 52);
    uint64_t high;

    if ((int)(field + k) <= 0) {
        bool opposite = ((x.high ^ x.low) & IBM_SIGN) != 0;
        uint64_t sig;

        if ((x.low & (IBM_SIGN - 1)) == 0) {
            return ibm_make(df_cx_scale(x.high, k), 0);
        }
        if (magnitude == 0) {
            return ibm_make(df_cx_scale(x.low, k), 0);
        }
        sig = df_normalise(magnitude, &field) << 3;
        sig = opposite ? sig - 1 : sig + 1;
        return ibm_make(df_round_pack(sign, field + k, sig), 0);
    }
    high = df_cx_scale(x.high, k);
    if ((high & (IBM_SIGN - 1)) == IBM_INF) {
        return ibm_make(high, 0);
    }
    return ibm_make(high, df_cx_scale(x.low, k));
}

// The value over the exponent of its first double, which goes in [1, 2).
IBM_HELPER struct ibm_bits ibm_cx_split(struct ibm_bits x, unsigned int *e) {
    uint64_t high;

    if (ibm_kind(ibm_cx_magnitude(x)) == FP_ZERO) {
        *e = CX_ZERO_EXPONENT(FP_EXP_MAX(11));
        return x;
    }
    high = df_cx_split(x.high, e);
    return ibm_make(high, df_cx_scale(x.low, (unsigned int)0 - *e));
}

// As FMT_cx_down above, for this format's 106 bits.
IBM_HELPER struct ibm_bits ibm_cx_down(struct ibm_bits x, unsigned int n) {
    if (n > 106 + 6 || ibm_kind(ibm_cx_magnitude(x)) == FP_ZERO) {
        return ibm_make(x.high & IBM_SIGN, 0);
    }
    return ibm_cx_scale(x, (unsigned int)0 - n);
}

IBM_HELPER struct ibm_bits ibm_finite_sum(struct ibm_bits x, struct ibm_bits y) {
    df_value high;
    df_value low;

    ibm_sum(
        df_from_bits(x.high), df_from_bits(x.low), df_from_bits(y.high), df_from_bits(y.low),
        &high, &low
    );
    return ibm_pair(high, low);
}

// A sum can overflow on the way where a value reaches 2^1023, so both are
// halved there, which loses nothing that the sum can show.
IBM_HELPER struct ibm_bits ibm_add(struct ibm_bits x, struct ibm_bits y) {
    uint64_t top = (uint64_t)(FP_EXP_MAX(11) - 1) << 52;
    int kind_x = ibm_kind(ibm_cx_magnitude(x));
    int kind_y = ibm_kind(ibm_cx_magnitude(y));

    if (kind_x == FP_NOT_A_NUMBER || kind_y == FP_NOT_A_NUMBER
     || (kind_x == FP_INFINITE && kind_y == FP_INFINITE
      && ibm_cx_negative(x) != ibm_cx_negative(y))) {
        return ibm_make(IBM_NAN, 0);
    }
    if (kind_x == FP_INFINITE) {
        return ibm_make(x.high, 0);
    }
    if (kind_y == FP_INFINITE) {
        return ibm_make(y.high, 0);
    }
    if (kind_x == FP_ZERO && kind_y == FP_ZERO) {
        return ibm_make(x.high & y.high & IBM_SIGN, 0);
    }
    if ((x.high & (IBM_SIGN - 1)) >= top || (y.high & (IBM_SIGN - 1)) >= top) {
        return ibm_cx_scale(
            ibm_finite_sum(
                ibm_cx_scale(x, (unsigned int)0 - 1), ibm_cx_scale(y, (unsigned int)0 - 1)
            ), 1
        );
    }
    return ibm_finite_sum(x, y);
}

IBM_HELPER struct ibm_bits ibm_sub(struct ibm_bits x, struct ibm_bits y) {
    return ibm_add(x, ibm_opposite(y));
}

IBM_HELPER struct ibm_bits ibm_mul(struct ibm_bits a, struct ibm_bits b) {
    struct ibm_bits x = ibm_tidy(a);
    struct ibm_bits y = ibm_tidy(b);
    uint64_t sign = (x.high ^ y.high) & IBM_SIGN;
    int kind_x = ibm_kind(ibm_cx_magnitude(x));
    int kind_y = ibm_kind(ibm_cx_magnitude(y));
    unsigned int e_x;
    unsigned int e_y;
    df_value x_high;
    df_value x_low;
    df_value y_high;
    df_value y_low;
    df_value product;
    df_value rest;
    df_value high;
    df_value low;

    if (kind_x == FP_NOT_A_NUMBER || kind_y == FP_NOT_A_NUMBER) {
        return ibm_make(IBM_NAN, 0);
    }
    if (kind_x == FP_INFINITE || kind_y == FP_INFINITE) {
        if (kind_x == FP_ZERO || kind_y == FP_ZERO) {
            return ibm_make(IBM_NAN, 0);
        }
        return ibm_make(sign | IBM_INF, 0);
    }
    if (kind_x == FP_ZERO || kind_y == FP_ZERO) {
        return ibm_make(sign, 0);
    }
    x = ibm_cx_split(x, &e_x);
    y = ibm_cx_split(y, &e_y);
    x_high = df_from_bits(x.high);
    x_low = df_from_bits(x.low);
    y_high = df_from_bits(y.high);
    y_low = df_from_bits(y.low);
    ibm_two_product(x_high, y_high, &product, &rest);
    rest = df_cx_add(rest, df_cx_add(df_cx_mul(x_high, y_low), df_cx_mul(x_low, y_high)));
    ibm_quick_sum(product, rest, &high, &low);
    return ibm_cx_scale(ibm_pair(high, low), e_x + e_y);
}

// The remainder (*r_high, *r_low) less q times the divisor, for the next q.
IBM_HELPER void ibm_remainder(
    df_value q,
    df_value c,
    df_value d,
    df_value *r_high,
    df_value *r_low
) {
    df_value p;
    df_value e;
    uint64_t sign = IBM_SIGN;

    ibm_two_product(q, c, &p, &e);
    e = df_cx_add(e, df_cx_mul(q, d));
    ibm_quick_sum(p, e, &p, &e);
    ibm_sum(
        *r_high, *r_low, df_from_bits(df_to_bits(p) ^ sign), df_from_bits(df_to_bits(e) ^ sign),
        r_high, r_low
    );
}

IBM_HELPER struct ibm_bits ibm_div(struct ibm_bits a, struct ibm_bits b) {
    struct ibm_bits x = ibm_tidy(a);
    struct ibm_bits y = ibm_tidy(b);
    uint64_t sign = (x.high ^ y.high) & IBM_SIGN;
    int kind_x = ibm_kind(ibm_cx_magnitude(x));
    int kind_y = ibm_kind(ibm_cx_magnitude(y));
    unsigned int e_x;
    unsigned int e_y;
    df_value c;
    df_value d;
    df_value r_high;
    df_value r_low;
    df_value q0;
    df_value q1;
    df_value q2;
    df_value high;
    df_value low;

    if (kind_x == FP_NOT_A_NUMBER || kind_y == FP_NOT_A_NUMBER
     || (kind_x == kind_y && kind_x != FP_FINITE)) {
        return ibm_make(IBM_NAN, 0);
    }
    if (kind_x == FP_INFINITE || kind_y == FP_ZERO) {
        return ibm_make(sign | IBM_INF, 0);
    }
    if (kind_y == FP_INFINITE || kind_x == FP_ZERO) {
        return ibm_make(sign, 0);
    }
    x = ibm_cx_split(x, &e_x);
    y = ibm_cx_split(y, &e_y);
    c = df_from_bits(y.high);
    d = df_from_bits(y.low);
    r_high = df_from_bits(x.high);
    r_low = df_from_bits(x.low);
    q0 = df_cx_div(r_high, c);
    ibm_remainder(q0, c, d, &r_high, &r_low);
    q1 = df_cx_div(r_high, c);
    ibm_remainder(q1, c, d, &r_high, &r_low);
    q2 = df_cx_div(r_high, c);
    ibm_quick_sum(q0, q1, &high, &low);
    ibm_sum(high, low, q2, df_from_bits((uint64_t)0), &high, &low);
    return ibm_cx_scale(ibm_pair(high, low), e_x - e_y);
}

#define IBM_BINARY(name, operation) \
    ibm_value name(df_value a, df_value b, df_value c, df_value d) { \
        return ibm_from_bits( \
            operation( \
                ibm_make(df_to_bits(a), df_to_bits(b)), ibm_make(df_to_bits(c), df_to_bits(d)) \
            ) \
        ); \
    }

IBM_BINARY(__gcc_qadd, ibm_add)
IBM_BINARY(__gcc_qsub, ibm_sub)
IBM_BINARY(__gcc_qmul, ibm_mul)
IBM_BINARY(__gcc_qdiv, ibm_div)

// GCC calls these by those other names with -mxl-compat.
#define IBM_BINARY_ALIAS(name, target) \
    FP_ALIAS(ibm_value, name, target, (df_value a, df_value b, df_value c, df_value d))

IBM_BINARY_ALIAS(_xlqadd, "__gcc_qadd")
IBM_BINARY_ALIAS(_xlqsub, "__gcc_qsub")
IBM_BINARY_ALIAS(_xlqmul, "__gcc_qmul")
IBM_BINARY_ALIAS(_xlqdiv, "__gcc_qdiv")

// The integer part of a double without its sign, modulo 2^iw, and whether
// there is more to it.
IBM_HELPER bool ibm_has_fraction(uint64_t magnitude) {
    unsigned int field = (unsigned int)(magnitude >> 52);

    if (field < FP_BIAS(11)) {
        return magnitude != 0;
    }
    field -= FP_BIAS(11);
    return field < 52 && (magnitude & (((uint64_t)1 << (52 - field)) - 1)) != 0;
}

#define IBM_INTEGER(mode, U, iw) \
    IBM_HELPER U ibm_integer_##mode(uint64_t magnitude) { \
        uint64_t int_bit = FP_INT_BIT(uint64_t, 52); \
        uint64_t sig = (magnitude & (int_bit - 1)) | int_bit; \
        unsigned int field = (unsigned int)(magnitude >> 52); \
        \
        if (field < FP_BIAS(11)) { \
            return 0; \
        } \
        field -= FP_BIAS(11); \
        if (field >= (iw) + 52) { \
            return 0; \
        } \
        if (field >= 52) { \
            return (U)sig << (field - 52); \
        } \
        return (U)(sig >> (52 - field)); \
    }

// Conversions to integers truncate the sum of both doubles. A second double
// opposite to the first takes off its integer part, and 1 more if that leaves
// a fraction, which it can only do where the first has none. These give the
// nearest integer of the type out of range, and zero for a NaN. In
// ibm_wrap_MODE, a negative value goes as in the signed conversion, and its
// integer is cast to the unsigned type. A first double of 2^iw has an integer
// part of 0 modulo that, from which a second double takes the rest.
#define IBM_TO_INT(mode, I, U, iw) \
    IBM_INTEGER(mode, U, iw) \
    \
    IBM_HELPER U ibm_fix_##mode(struct ibm_bits x, U limit) { \
        uint64_t mask = IBM_SIGN - 1; \
        uint64_t high = x.high & mask; \
        uint64_t low = x.low & mask; \
        uint64_t edge = (uint64_t)(FP_BIAS(11) + (iw)) << 52; \
        bool below = ((x.high ^ x.low) & IBM_SIGN) != 0 && low != 0; \
        U value = ibm_integer_##mode(high); \
        \
        if (high > IBM_INF) { \
            return 0; \
        } \
        if (high > edge || (high == edge && !below)) { \
            return limit; \
        } \
        if (below) { \
            value -= ibm_integer_##mode(low); \
            if (!ibm_has_fraction(high) && ibm_has_fraction(low)) { \
                value -= 1; \
            } \
        } else { \
            value += ibm_integer_##mode(low); \
        } \
        return value > limit ? limit : value; \
    } \
    \
    IBM_HELPER I ibm_to_##mode(struct ibm_bits x) { \
        U top = (U)1 << ((iw) - 1); \
        \
        if (ibm_cx_negative(x)) { \
            return (I)((U)0 - ibm_fix_##mode(x, top)); \
        } \
        return (I)ibm_fix_##mode(x, top - 1); \
    } \
    \
    IBM_HELPER U ibm_to_uns##mode(struct ibm_bits x) { \
        if (ibm_cx_negative(x)) { \
            return 0; \
        } \
        return ibm_fix_##mode(x, (U)0 - 1); \
    } \
    \
    IBM_HELPER U ibm_wrap_##mode(struct ibm_bits x) { \
        if (ibm_cx_negative(x)) { \
            return (U)0 - ibm_fix_##mode(x, (U)1 << ((iw) - 1)); \
        } \
        return ibm_fix_##mode(x, (U)0 - 1); \
    }

// Conversions from integers. The first double is the integer rounded, which
// may take it to 2^iw, so the second double is the difference modulo that, as
// a signed value, rounded in turn.
#define IBM_FROM_INT(mode, I, U, iw) \
    IBM_HELPER struct ibm_bits ibm_float_##mode(bool negative, U value) { \
        uint64_t high = df_float_##mode(0, value); \
        U rest = value - ibm_integer_##mode(high); \
        bool below = (rest >> ((iw) - 1)) != 0; \
        struct ibm_bits x = ibm_make(high, df_float_##mode(0, below ? (U)0 - rest : rest)); \
        \
        if (below) { \
            x.low ^= IBM_SIGN; \
        } \
        if (negative) { \
            x.high ^= IBM_SIGN; \
            if (rest != 0) { \
                x.low ^= IBM_SIGN; \
            } \
        } \
        return x; \
    } \
    \
    IBM_HELPER struct ibm_bits ibm_from_##mode(I i) { \
        return ibm_float_##mode(i < 0, i < 0 ? (U)0 - (U)i : (U)i); \
    }

IBM_TO_INT(si, int32_t, uint32_t, 32)
IBM_TO_INT(di, int64_t, uint64_t, 64)
IBM_FROM_INT(si, int32_t, uint32_t, 32)
IBM_FROM_INT(di, int64_t, uint64_t, 64)

#define IBM_TO_NAMED(R, name, value) \
    R name(ibm_value a) { \
        struct ibm_bits x = ibm_tidy(ibm_to_bits(a)); \
        \
        return (value); \
    }

#define IBM_FROM_NAMED(P, name, value) \
    ibm_value name(P i) { \
        return ibm_from_bits(value); \
    }

IBM_TO_NAMED(int64_t, __fixtfdi, ibm_to_di(x))
IBM_TO_NAMED(uint64_t, __fixunstfdi, ibm_to_unsdi(x))
IBM_FROM_NAMED(int64_t, __floatditf, ibm_from_di(i))
IBM_FROM_NAMED(uint64_t, __floatunditf, ibm_float_di(false, i))

#if HAS_INT128
IBM_TO_INT(ti, i128, u128, 128)
IBM_FROM_INT(ti, i128, u128, 128)
IBM_TO_NAMED(i128, __fixtfti, ibm_to_ti(x))
IBM_TO_NAMED(u128, __fixunstfti, ibm_to_unsti(x))
IBM_FROM_NAMED(i128, __floattitf, ibm_from_ti(i))
IBM_FROM_NAMED(u128, __floatuntitf, ibm_float_ti(false, i))
#endif

// Hard float does the rest inline. Without floating-point registers, these
// come as the arithmetic does, with each long double as two doubles, and their
// values are as the usual comparisons have them. Clang calls __gcc_qtou for
// signed int too, and GCC for unsigned int, so it takes the range of both.
#if defined(__NO_FPRS__)

#define IBM_COMPARE(name, unordered) \
    fp_cmp name(df_value a, df_value b, df_value c, df_value d) { \
        return ibm_compare( \
            ibm_make(df_to_bits(a), df_to_bits(b)), ibm_make(df_to_bits(c), df_to_bits(d)), \
            unordered \
        ); \
    }

#define IBM_COMPARE_ALIAS(name, target) \
    FP_ALIAS(fp_cmp, name, target, (df_value a, df_value b, df_value c, df_value d))

IBM_COMPARE(__gcc_qlt, 1)
IBM_COMPARE_ALIAS(__gcc_qle, "__gcc_qlt")
IBM_COMPARE_ALIAS(__gcc_qeq, "__gcc_qlt")
IBM_COMPARE_ALIAS(__gcc_qne, "__gcc_qlt")
IBM_COMPARE(__gcc_qgt, -1)
IBM_COMPARE_ALIAS(__gcc_qge, "__gcc_qgt")

fp_cmp __gcc_qunord(df_value a, df_value b, df_value c, df_value d) {
    int order = ibm_compare(
        ibm_make(df_to_bits(a), df_to_bits(b)), ibm_make(df_to_bits(c), df_to_bits(d)), 2
    );

    return order == 2;
}

ibm_value __gcc_qneg(df_value a, df_value b) {
    return ibm_from_bits(ibm_opposite(ibm_make(df_to_bits(a), df_to_bits(b))));
}

IBM_FROM_NAMED(sf_value, __gcc_stoq, ibm_make(df_from_sf(sf_to_bits(i)), 0))
IBM_FROM_NAMED(df_value, __gcc_dtoq, ibm_make(df_to_bits(i), 0))
IBM_FROM_NAMED(int32_t, __gcc_itoq, ibm_from_si(i))
IBM_FROM_NAMED(fp_unsigned_si, __gcc_utoq, ibm_float_si(false, (uint32_t)i))

sf_value __gcc_qtos(df_value a, df_value b) {
    struct ibm_bits x = ibm_tidy(ibm_make(df_to_bits(a), df_to_bits(b)));

    return sf_from_bits(df_to_sf(ibm_sticky(x)));
}

df_value __gcc_qtod(df_value a, df_value b) {
    if ((df_to_bits(a) & (IBM_SIGN - 1)) >= IBM_INF) {
        return a;
    }
    return df_cx_add(a, b);
}

#define IBM_TO_DOUBLES(R, name, value) \
    R name(df_value a, df_value b) { \
        struct ibm_bits x = ibm_tidy(ibm_make(df_to_bits(a), df_to_bits(b))); \
        \
        return (value); \
    }

IBM_TO_DOUBLES(int32_t, __gcc_qtoi, ibm_to_si(x))
IBM_TO_DOUBLES(uint32_t, __gcc_qtou, ibm_wrap_si(x))
IBM_TO_NAMED(uint32_t, __fixunstfsi, ibm_to_unssi(x))

#endif // defined(__NO_FPRS__)

// Complex values and powers, for long double alone. Clang also calls the first
// two by these names for complex __float128, which cannot be told from here.
#if LDBL_MANT_DIG == 106

__extension__ typedef _Complex long double ibm_complex;

IBM_HELPER struct ibm_bits ibm_tidy_bits(ibm_value value) {
    return ibm_tidy(ibm_to_bits(value));
}

CX_FP_OPERATIONS(ibm, ibm_value, struct ibm_bits, ibm_tidy_bits, ibm_from_bits)
CX_SPECIAL_VALUES(
    ibm, struct ibm_bits, ibm_make(0, 0), ibm_make(1, 0), ibm_make(IBM_INF, 0),
    ibm_make(IBM_NAN, 0)
)
CX_MULTIPLY(ibm, ibm_value, struct ibm_bits)
CX_DIVIDE(ibm, ibm_value, struct ibm_bits, ibm_make(IBM_NAN, 0), ibm_make(0, 0))
CX_POWER(
    ibm, ibm_value, struct ibm_bits, ibm_make(0, 0), ibm_make(IBM_INF, 0), ibm_make(IBM_ONE, 0)
)
CX_NAMED_ROUTINES(ibm, ibm_value, ibm_complex, __multc3, __divtc3, __powitf2)

#endif

#endif // HAS_IBM_128

#if SOFT_QUAD

#if defined(__powerpc__) && defined(__FLOAT128__)
__extension__ typedef _Complex float quad_complex __attribute__((__mode__(__KC__)));
#elif LDBL_MANT_DIG == 113
__extension__ typedef _Complex long double quad_complex;
#else
__extension__ typedef _Complex float quad_complex __attribute__((__mode__(__TC__)));
#endif

#define QUAD_COMPLEX_ROUTINES(fmt, cfmt) \
    CX_FP_OPERATIONS(fmt, quad_value, struct wide, fmt##_to_bits, fmt##_from_bits) \
    CX_WIDE(fmt, quad_value, 32767, 112) \
    CX_ROUTINES(fmt, cfmt, quad_value, quad_complex)

// The same choice of names as the routines of the format.
#if defined(__powerpc__) && (defined(__FLOAT128__) || defined(__VSX__) || defined(__clang__))

QUAD_COMPLEX_ROUTINES(kf, kc)

// Clang calls these by the usual names for IEEE long double.
#if defined(__clang__) && defined(__LONG_DOUBLE_IEEE128__)
#define KC_ALIAS(name, target) \
    FP_ALIAS(quad_complex, name, target, (quad_value a, quad_value b, quad_value c, quad_value d))

KC_ALIAS(__multc3, "__mulkc3")
KC_ALIAS(__divtc3, "__divkc3")
#endif

#else

QUAD_COMPLEX_ROUTINES(tf, tc)

#endif

#elif QUAD_OWN_NAMES

// SPARC and Alpha call routines of other names for quad arithmetic, so these
// go on the bits, and long double only passes through them.
CX_WIDE_OPERATIONS(tf)
CX_WIDE(tf, struct wide, 32767, 112)

__extension__ typedef _Complex long double tc_value;

#define TC_ROUTINE(name, operation) \
    tc_value name(quad_value a, quad_value b, quad_value c, quad_value d) { \
        struct wide parts[2]; \
        quad_value results[2]; \
        tc_value z; \
        \
        operation(tf_to_bits(a), tf_to_bits(b), tf_to_bits(c), tf_to_bits(d), parts); \
        results[0] = tf_from_bits(parts[0]); \
        results[1] = tf_from_bits(parts[1]); \
        __builtin_memcpy(&z, results, sizeof(results)); \
        return z; \
    }

TC_ROUTINE(__multc3, tf_cx_multiply)
TC_ROUTINE(__divtc3, tf_cx_divide)

#if defined(__sparc__) && TF_IN_REGISTERS

tf_registers __powitf2(uint64_t high, uint64_t low, int n) {
    return tf_to_registers(tf_cx_power(wide_make(high, low), n));
}

#else

quad_value __powitf2(quad_value x, powi_exponent n) {
    return tf_from_bits(tf_cx_power(tf_to_bits(x), (int)n));
}

#endif

#endif // SOFT_QUAD

// C has no name for a complex value of the x87 format where it is not that of
// long double, so there is nothing to call these for there.
#if !SOFT_XF || LDBL_MANT_DIG != 64
#elif XF_RETURNED

__extension__ typedef _Complex long double xc_value;

#if defined(__m68k__)

static inline struct wide xf_value_bits(xf_value value) {
    struct xf_words words;

    __builtin_memcpy(&words, &value, sizeof(struct xf_words));
    return xf_to_bits(words);
}

CX_FP_OPERATIONS(xf, xf_value, struct wide, xf_value_bits, xf_from_bits)

#else

CX_FP_OPERATIONS(xf, xf_value, struct wide, xf_to_bits, xf_from_bits)

#endif

CX_WIDE(xf, xf_value, XF_EXP_MAX, 63)
CX_ROUTINES(xf, xc, xf_value, xc_value)

#elif defined(__clang__)

// Clang has no long double to write these with, as the conversions above say,
// so they go on the bits. x86-64 returns a complex one on the x87 stack, its
// real part on top, and IA-32 in memory, as it does a structure of its size.
CX_WIDE_OPERATIONS(xf)
CX_WIDE(xf, struct wide, XF_EXP_MAX, 63)

#if defined(__x86_64__)

#define XC_ROUTINE(name, operation) \
    void name(XF_PARAMETER a, xf_argument b, xf_argument c, xf_argument d) { \
        struct wide parts[2]; \
        struct wide real_part; \
        struct wide imaginary_part; \
        \
        operation(xf_to_bits(a), xf_to_bits(b), xf_to_bits(c), xf_to_bits(d), parts); \
        real_part = xf_encode(parts[0]); \
        imaginary_part = xf_encode(parts[1]); \
        __asm__ ( \
            "fldt %0\n\t" \
            "fldt %1" \
            : \
            : "m"(imaginary_part), "m"(real_part) \
        ); \
    }

// Its int goes in the first of the registers that the other routines skip.
void __powixf2(
    int n,
    uint64_t rsi,
    uint64_t rdx,
    uint64_t rcx,
    uint64_t r8,
    uint64_t r9,
    xf_argument x
) {
    (void)rsi;
    (void)rdx;
    (void)rcx;
    (void)r8;
    (void)r9;
    xf_return(xf_cx_power(xf_to_bits(x), n));
}

#else // defined(__x86_64__)

struct xc_value {
    xf_argument parts[2];
};

#define XC_ROUTINE(name, operation) \
    struct xc_value name(xf_argument a, xf_argument b, xf_argument c, xf_argument d) { \
        struct wide parts[2]; \
        struct wide raw; \
        struct xc_value z; \
        \
        operation(xf_to_bits(a), xf_to_bits(b), xf_to_bits(c), xf_to_bits(d), parts); \
        raw = xf_encode(parts[0]); \
        __builtin_memcpy(&z.parts[0], &raw, sizeof(xf_argument)); \
        raw = xf_encode(parts[1]); \
        __builtin_memcpy(&z.parts[1], &raw, sizeof(xf_argument)); \
        return z; \
    }

void __powixf2(xf_argument x, int n) {
    xf_return(xf_cx_power(xf_to_bits(x), n));
}

#endif // defined(__x86_64__)

XC_ROUTINE(__mulxc3, xf_cx_multiply)
XC_ROUTINE(__divxc3, xf_cx_divide)

#endif // !SOFT_XF || LDBL_MANT_DIG != 64

#endif // LGRT_SOFT_FLOAT || SOFT_XF || ALPHA_QUAD

// The routines of _BitInt work on arrays of limbs, whose width and order go by
// the target. A pointer comes with a precision, positive for an unsigned value
// of that many bits and negative for a signed one. The array has as many limbs
// as hold them. Bits above them in the top limb are not read, and are written
// as the extension of the value, for ABIs that want that. Compilers lower the
// precision of an operand where its value allows it, so operands and results
// differ in width. A result never overlaps an operand, while operands may
// overlap each other.
#if defined(__x86_64__) || defined(__i386__) || defined(__riscv) || defined(__s390x__) \
 || defined(__loongarch64) || (defined(__aarch64__) && !defined(__AARCH64EB__)) \
 || (defined(__arm__) && !defined(__ARMEB__))
#   define BITINT_GCC 1
#else
#   define BITINT_GCC 0
#endif

// Clang has the type on more targets, with routines of other names.
#if BITINT_GCC || defined(__aarch64__) || defined(__arm__) || defined(__mips__) \
 || defined(__powerpc__) || defined(__sparc__) || defined(__hexagon__) || defined(__loongarch__)
#   define BITINT 1
#else
#   define BITINT 0
#endif

#if BITINT

// Not all that follows is used on every target.
#define BITINT_HELPER __attribute__((__unused__)) static

#if defined(__x86_64__) || defined(__aarch64__) || (LGRT_64BIT && HAS_INT128)
#define LIMB_BITS 64
typedef uint64_t lgrt_limb __attribute__((__may_alias__));
__extension__ typedef unsigned __int128 double_limb;
#else
#define LIMB_BITS 32
typedef uint32_t lgrt_limb __attribute__((__may_alias__));
typedef uint64_t double_limb;
#endif

// The operands are objects of _BitInt types, which the limbs alias. Where limb
// i of an array of n limbs is, limb 0 being the lowest.
#if defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#   define LIMB_AT(n, i) ((n) - 1 - (i))
#else
#   define LIMB_AT(n, i) ((void)(n), (i))
#endif

// A shift of hi:lo left by s, from 0 to one less than a limb, keeping hi.
#define LIMB_SHIFT(hi, lo, s) (((hi) << (s)) | (((lo) >> 1) >> (LIMB_BITS - 1 - (s))))

static inline uint32_t bitint_bits(int32_t prec) {
    return prec < 0 ? (uint32_t)0 - (uint32_t)prec : (uint32_t)prec;
}

static inline size_t bitint_limbs(int32_t prec) {
    return ((size_t)bitint_bits(prec) + LIMB_BITS - 1) / LIMB_BITS;
}

// The top limb of a value, with the bits above its precision extended.
static inline lgrt_limb bitint_extend(lgrt_limb limb, int32_t prec, bool is_signed) {
    unsigned int used = bitint_bits(prec) % LIMB_BITS;
    lgrt_limb above;

    if (used == 0) {
        return limb;
    }
    above = ~(lgrt_limb)0 << used;
    if (is_signed && ((limb >> (used - 1)) & 1) != 0) {
        return limb | above;
    }
    return limb & ~above;
}

// An operand, to be read as a sign and a magnitude. A signed value's magnitude
// has as many limbs as it does, however negative it is. The limbs of the
// magnitude are had one at a time, in any order, with nothing written: a
// negated limb at the lowest one that is not zero, and inverted ones above it.
// count is how many limbs it has without its leading zeros, 0 if it is zero.
struct bitint {
    const lgrt_limb *limbs;
    size_t stored;
    size_t count;
    size_t lowest;
    lgrt_limb top;
    bool negative;
};

static inline lgrt_limb bitint_stored(const struct bitint *x, size_t i) {
    if (i + 1 == x->stored) {
        return x->top;
    }
    return x->limbs[LIMB_AT(x->stored, i)];
}

static inline lgrt_limb bitint_magnitude(const struct bitint *x, size_t i) {
    lgrt_limb limb = bitint_stored(x, i);

    if (x->negative && i >= x->lowest) {
        return i == x->lowest ? (lgrt_limb)0 - limb : ~limb;
    }
    return limb;
}

static void bitint_load(struct bitint *x, const lgrt_limb *limbs, int32_t prec) {
    lgrt_limb leading;

    x->limbs = limbs;
    x->stored = bitint_limbs(prec);
    x->count = 0;
    x->lowest = 0;
    x->top = 0;
    x->negative = false;
    if (x->stored == 0) {
        return;
    }
    x->top = bitint_extend(limbs[LIMB_AT(x->stored, x->stored - 1)], prec, prec < 0);
    x->negative = prec < 0 && (x->top >> (LIMB_BITS - 1)) != 0;
    while (x->lowest < x->stored && bitint_stored(x, x->lowest) == 0) {
        x->lowest += 1;
    }
    if (x->lowest == x->stored) {
        return;
    }
    leading = x->negative ? ~(lgrt_limb)0 : 0;
    x->count = x->stored;
    while (x->count - 1 > x->lowest && bitint_stored(x, x->count - 1) == leading) {
        x->count -= 1;
    }
}

static void bitint_negate(lgrt_limb *r, size_t rn) {
    lgrt_limb carry = 1;

    for (size_t i = 0; i < rn; i++) {
        lgrt_limb limb = ~r[LIMB_AT(rn, i)] + carry;

        r[LIMB_AT(rn, i)] = limb;
        carry = (lgrt_limb)(carry != 0 && limb == 0);
    }
}

// The last step of a result of multiplication or division, whose precision has
// no sign: it can only be negative if an operand's precision was negative.
static void bitint_finish(lgrt_limb *r, int32_t rprec, bool negate, bool any_signed) {
    size_t rn = bitint_limbs(rprec);

    if (rn == 0) {
        return;
    }
    if (negate) {
        bitint_negate(r, rn);
    }
    r[LIMB_AT(rn, rn - 1)] = bitint_extend(r[LIMB_AT(rn, rn - 1)], rprec, any_signed);
}

BITINT_HELPER void bitint_mul(
    lgrt_limb *ret,
    int32_t retprec,
    const lgrt_limb *u,
    int32_t uprec,
    const lgrt_limb *v,
    int32_t vprec
) {
    size_t rn = bitint_limbs(retprec);
    struct bitint a;
    struct bitint b;

    bitint_load(&a, u, uprec);
    bitint_load(&b, v, vprec);
    for (size_t i = 0; i < rn; i++) {
        ret[LIMB_AT(rn, i)] = 0;
    }
    for (size_t i = 0; i < a.count && i < rn; i++) {
        lgrt_limb x = bitint_magnitude(&a, i);
        lgrt_limb carry = 0;
        size_t j;

        for (j = 0; j < b.count && i + j < rn; j++) {
            lgrt_limb *to = &ret[LIMB_AT(rn, i + j)];
            double_limb t = (double_limb)x * bitint_magnitude(&b, j) + *to + carry;

            *to = (lgrt_limb)t;
            carry = (lgrt_limb)(t >> LIMB_BITS);
        }
        if (i + j < rn) {
            ret[LIMB_AT(rn, i + j)] = carry;
        }
    }
    bitint_finish(ret, retprec, a.negative != b.negative, uprec < 0 || vprec < 0);
}

// The quotient of hi:lo by d, where hi < d, so that it fits in a limb.
static inline lgrt_limb limb_divide(lgrt_limb hi, lgrt_limb lo, lgrt_limb d, lgrt_limb *rem) {
#if LIMB_BITS == 64
    uint64_t r;
    uint64_t q = udiv128by64(hi, lo, d, &r);

    *rem = r;
    return q;
#else
    uint64_t r;
    uint64_t q = udivmod64(((uint64_t)hi << 32) | lo, d, &r);

    *rem = (lgrt_limb)r;
    return (lgrt_limb)q;
#endif
}

static inline unsigned int limb_clz(lgrt_limb x) {
#if LIMB_BITS == 64
    return clz64(x);
#else
    return clz32(x);
#endif
}

// Knuth's Algorithm D, for operands of at least two limbs, with neither of
// them written. The divisor stays as it is: only its top two limbs, and the
// top three of what is being divided, are shifted, to make the estimate of a
// quotient digit that normalised operands would give, and the subtraction of
// that digit times the divisor gives the same result either way.
//
// w has room for all the limbs of u. What is being divided sits at w[k] to w[k
// + m], with the limbs of u still to come below it, read as they are needed,
// and the digit of the quotient found at k goes to w[k + m], which the
// subtraction has cleared. This leaves the remainder at the bottom, the digits
// above it, and the highest digit, which has no room, in *top_digit.
static void bitint_long_divide(
    lgrt_limb *w,
    size_t wn,
    const struct bitint *u,
    const struct bitint *v,
    lgrt_limb *top_digit
) {
    size_t n = u->count;
    size_t m = v->count;
    lgrt_limb v_top = bitint_magnitude(v, m - 1);
    lgrt_limb v_next = bitint_magnitude(v, m - 2);
    lgrt_limb v_rest = m > 2 ? bitint_magnitude(v, m - 3) : 0;
    unsigned int s = limb_clz(v_top);
    lgrt_limb d1 = LIMB_SHIFT(v_top, v_next, s);
    lgrt_limb d2 = LIMB_SHIFT(v_next, v_rest, s);

    for (size_t i = n - m; i < n; i++) {
        w[LIMB_AT(wn, i)] = bitint_magnitude(u, i);
    }
    for (size_t k = n - m + 1; k-- > 0; ) {
        lgrt_limb top = k == n - m ? 0 : w[LIMB_AT(wn, k + m)];
        lgrt_limb r1;
        lgrt_limb r2;
        lgrt_limb r3;
        lgrt_limb n0;
        lgrt_limb n1;
        lgrt_limb n2;
        lgrt_limb digit;
        lgrt_limb rem;
        lgrt_limb borrow = 0;
        bool estimate_checks;

        if (k != n - m) {
            w[LIMB_AT(wn, k)] = bitint_magnitude(u, k);
        }
        r1 = w[LIMB_AT(wn, k + m - 1)];
        r2 = w[LIMB_AT(wn, k + m - 2)];
        r3 = m > 2 ? w[LIMB_AT(wn, k + m - 3)] : 0;
        n0 = LIMB_SHIFT(top, r1, s);
        n1 = LIMB_SHIFT(r1, r2, s);
        n2 = LIMB_SHIFT(r2, r3, s);
        if (n0 >= d1) {
            digit = ~(lgrt_limb)0;
            rem = n1 + d1;
            estimate_checks = rem >= d1;
        } else {
            digit = limb_divide(n0, n1, d1, &rem);
            estimate_checks = true;
        }
        while (estimate_checks
            && (double_limb)digit * d2 > (((double_limb)rem << LIMB_BITS) | n2)) {
            digit -= 1;
            rem += d1;
            estimate_checks = rem >= d1;
        }
        for (size_t j = 0; j < m; j++) {
            lgrt_limb *to = &w[LIMB_AT(wn, k + j)];
            lgrt_limb limb = *to;
            double_limb product = (double_limb)digit * bitint_magnitude(v, j) + borrow;
            lgrt_limb low = (lgrt_limb)product;

            *to = limb - low;
            borrow = (lgrt_limb)(product >> LIMB_BITS) + (lgrt_limb)(limb < low);
        }
        if (top < borrow) {
            lgrt_limb carry = 0;

            digit -= 1;
            for (size_t j = 0; j < m; j++) {
                lgrt_limb *to = &w[LIMB_AT(wn, k + j)];
                double_limb sum = (double_limb)*to + bitint_magnitude(v, j) + carry;

                *to = (lgrt_limb)sum;
                carry = (lgrt_limb)(sum >> LIMB_BITS);
            }
        }
        if (k == n - m) {
            *top_digit = digit;
        } else {
            w[LIMB_AT(wn, k + m)] = digit;
        }
    }
}

// The remainder at the bottom of w, into a result that w may be.
static void bitint_move_remainder(
    lgrt_limb *r,
    size_t rn,
    const lgrt_limb *w,
    size_t wn,
    size_t m
) {
    for (size_t i = 0; i < rn; i++) {
        r[LIMB_AT(rn, i)] = i < m ? w[LIMB_AT(wn, i)] : 0;
    }
}

// The digits above the remainder, into a result that w may be.
static void bitint_move_quotient(
    lgrt_limb *q,
    size_t qn,
    const lgrt_limb *w,
    size_t wn,
    size_t digits,
    size_t m,
    lgrt_limb top_digit
) {
    for (size_t i = 0; i < qn; i++) {
        lgrt_limb digit = 0;

        if (i < digits) {
            digit = w[LIMB_AT(wn, i + m)];
        } else if (i == digits) {
            digit = top_digit;
        }
        q[LIMB_AT(qn, i)] = digit;
    }
}

// A result at least as wide as the dividend has room for all that the long
// division needs, and compilers always give one. Without one, there is only
// the stack for it, for that call alone.
BITINT_HELPER void bitint_divmod(
    lgrt_limb *q,
    int32_t qprec,
    lgrt_limb *r,
    int32_t rprec,
    const lgrt_limb *u,
    int32_t uprec,
    const lgrt_limb *v,
    int32_t vprec
) {
    size_t qn = bitint_limbs(qprec);
    size_t rn = bitint_limbs(rprec);
    bool any_signed = uprec < 0 || vprec < 0;
    struct bitint a;
    struct bitint b;

    bitint_load(&a, u, uprec);
    bitint_load(&b, v, vprec);
    if (b.count == 0) {
        TRAP();
    }
    if (a.count < b.count) {
        for (size_t i = 0; i < qn; i++) {
            q[LIMB_AT(qn, i)] = 0;
        }
        for (size_t i = 0; i < rn; i++) {
            r[LIMB_AT(rn, i)] = i < a.count ? bitint_magnitude(&a, i) : 0;
        }
    } else if (b.count == 1) {
        lgrt_limb d = bitint_magnitude(&b, 0);
        lgrt_limb rem = 0;

        for (size_t i = 0; i < qn; i++) {
            q[LIMB_AT(qn, i)] = 0;
        }
        for (size_t i = a.count; i-- > 0; ) {
            lgrt_limb digit = limb_divide(rem, bitint_magnitude(&a, i), d, &rem);

            if (i < qn) {
                q[LIMB_AT(qn, i)] = digit;
            }
        }
        for (size_t i = 0; i < rn; i++) {
            r[LIMB_AT(rn, i)] = i == 0 ? rem : 0;
        }
    } else {
        lgrt_limb *w = q;
        size_t wn = qn;
        lgrt_limb top_digit = 0;

        if (qn < a.count) {
            w = r;
            wn = rn;
            if (rn < a.count) {
                wn = a.count;
                w = __builtin_alloca(wn * sizeof(lgrt_limb));
            }
        }
        bitint_long_divide(w, wn, &a, &b, &top_digit);
        if (w == q) {
            bitint_move_remainder(r, rn, w, wn, b.count);
        }
        bitint_move_quotient(q, qn, w, wn, a.count - b.count, b.count, top_digit);
        if (w != q) {
            bitint_move_remainder(r, rn, w, wn, b.count);
        }
    }
    bitint_finish(q, qprec, a.negative != b.negative, any_signed);
    bitint_finish(r, rprec, a.negative, any_signed);
}

#if BITINT_GCC

void __mulbitint3(
    lgrt_limb *ret,
    int32_t retprec,
    const lgrt_limb *u,
    int32_t uprec,
    const lgrt_limb *v,
    int32_t vprec
) {
    bitint_mul(ret, retprec, u, uprec, v, vprec);
}

void __divmodbitint4(
    lgrt_limb *q,
    int32_t qprec,
    lgrt_limb *r,
    int32_t rprec,
    const lgrt_limb *u,
    int32_t uprec,
    const lgrt_limb *v,
    int32_t vprec
) {
    bitint_divmod(q, qprec, r, rprec, u, uprec, v, vprec);
}

#endif // BITINT_GCC

// Clang 15 calls these for what is wider than 128 bits, given an option to
// have such a width. The operands and the result are all as wide as bits says,
// a multiple of 64, and the operands are extended to that.
#if !defined(__loongarch__)

#define BITINT_EI4(name, is_signed, is_remainder) \
    void name(lgrt_limb *out, const lgrt_limb *a, const lgrt_limb *b, unsigned int bits) { \
        int32_t result = (int32_t)bits; \
        int32_t operand = (is_signed) ? (int32_t)((uint32_t)0 - bits) : result; \
        \
        if (is_remainder) { \
            bitint_divmod(NULL, 0, out, result, a, operand, b, operand); \
        } else { \
            bitint_divmod(out, result, NULL, 0, a, operand, b, operand); \
        } \
    }

BITINT_EI4(__divei4, true, false)
BITINT_EI4(__udivei4, false, false)
BITINT_EI4(__modei4, true, true)
BITINT_EI4(__umodei4, false, true)

#endif

#if LGRT_SOFT_FLOAT || SOFT_XF

BITINT_HELPER size_t bitint_length(const struct bitint *x) {
    return x->count * LIMB_BITS - limb_clz(bitint_magnitude(x, x->count - 1));
}

// Up to 64 bits of a magnitude from bit pos up, zeros beyond its limbs.
BITINT_HELPER uint64_t bitint_extract(const struct bitint *x, size_t pos) {
    size_t i = pos / LIMB_BITS;
    unsigned int s = pos % LIMB_BITS;
    unsigned int got = 0;
    uint64_t value = 0;

    while (got < 64 && i < x->count) {
        value |= (uint64_t)(bitint_magnitude(x, i) >> s) << got;
        got += LIMB_BITS - s;
        s = 0;
        i += 1;
    }
    return value;
}

// Whether a magnitude has any of its n lowest bits set, n below its length.
BITINT_HELPER bool bitint_any_below(const struct bitint *x, size_t n) {
    size_t i = n / LIMB_BITS;
    unsigned int s = n % LIMB_BITS;

    if (x->lowest != i) {
        return x->lowest < i;
    }
    return s != 0 && (bitint_magnitude(x, i) << (LIMB_BITS - s)) != 0;
}

// Rounding comes from the core of the format, as for other integers, given the
// top bits of the magnitude and whether any other bit is set.
#define BITINT_TO_FP(fmt, T, E, F) \
    BITINT_HELPER T fmt##_from_bitint(const lgrt_limb *i, int32_t iprec) { \
        struct bitint x; \
        T sign; \
        T sig; \
        size_t length; \
        \
        bitint_load(&x, i, iprec); \
        if (x.count == 0) { \
            return 0; \
        } \
        sign = x.negative ? FP_SIGN(T, E, F) : 0; \
        length = bitint_length(&x); \
        if (length - 1 >= (size_t)(FP_EXP_MAX(E) - FP_BIAS(E))) { \
            return sign | FP_INF(T, E, F); \
        } \
        if (length <= (F) + 4) { \
            sig = (T)bitint_extract(&x, 0) << ((F) + 4 - length); \
        } else { \
            size_t lost = length - ((F) + 4); \
            \
            sig = (T)bitint_extract(&x, lost) | (T)bitint_any_below(&x, lost); \
        } \
        return fmt##_round_pack(sign, FP_BIAS(E) + (unsigned int)length - 1, sig); \
    }

BITINT_HELPER void bitint_clear(lgrt_limb *r, int32_t rprec) {
    size_t rn = bitint_limbs(rprec);

    for (size_t i = 0; i < rn; i++) {
        r[LIMB_AT(rn, i)] = 0;
    }
}

// The nearest value that the result can hold, for one out of its range.
BITINT_HELPER void bitint_saturate(lgrt_limb *r, int32_t rprec, bool negative) {
    size_t rn = bitint_limbs(rprec);
    unsigned int used = bitint_bits(rprec) % LIMB_BITS;
    lgrt_limb sign_bit;

    if (rn == 0) {
        return;
    }
    for (size_t i = 0; i < rn; i++) {
        r[LIMB_AT(rn, i)] = negative ? 0 : ~(lgrt_limb)0;
    }
    sign_bit = (lgrt_limb)1 << ((used != 0 ? used : LIMB_BITS) - 1);
    if (rprec > 0) {
        r[LIMB_AT(rn, rn - 1)] = bitint_extend(~(lgrt_limb)0, rprec, false);
    } else {
        r[LIMB_AT(rn, rn - 1)] = negative ? (lgrt_limb)0 - sign_bit : sign_bit - 1;
    }
}

// Sets bits of a result from bit pos up, as far as it has them.
BITINT_HELPER void bitint_set_bits(lgrt_limb *r, size_t rn, size_t pos, uint64_t value) {
    size_t i = pos / LIMB_BITS;
    unsigned int s = pos % LIMB_BITS;

    while (value != 0 && i < rn) {
        unsigned int taken = LIMB_BITS - s;

        r[LIMB_AT(rn, i)] |= (lgrt_limb)value << s;
        value = taken < 64 ? value >> taken : 0;
        s = 0;
        i += 1;
    }
}

// A finite value of a magnitude of at least 1, negative only for a signed
// result, from its exponent without the bias, and high:low, its significand
// with the integer bit at bit f. It truncates. The most negative value of a
// signed result comes out of saturating too.
BITINT_HELPER void bitint_fix(
    lgrt_limb *r,
    int32_t rprec,
    bool negative,
    uint32_t e,
    uint64_t high,
    uint64_t low,
    unsigned int f
) {
    uint32_t bits = bitint_bits(rprec);
    size_t rn = bitint_limbs(rprec);
    size_t pos = 0;

    if (e >= bits || (rprec < 0 && e == bits - 1)) {
        bitint_saturate(r, rprec, negative);
        return;
    }
    bitint_clear(r, rprec);
    if (e >= f) {
        pos = e - f;
    } else {
        unsigned int n = f - e;

        if (n >= 64) {
            low = high >> (n - 64);
            high = 0;
        } else {
            low = (low >> n) | ((high << 1) << (63 - n));
            high >>= n;
        }
    }
    bitint_set_bits(r, rn, pos, low);
    bitint_set_bits(r, rn, pos + 64, high);
    if (negative) {
        bitint_negate(r, rn);
    }
    r[LIMB_AT(rn, rn - 1)] = bitint_extend(r[LIMB_AT(rn, rn - 1)], rprec, rprec < 0);
}

// A NaN gives zero, and so does a negative value to an unsigned result.
#define BITINT_FROM_FP(fmt, T, E, F) \
    BITINT_HELPER void fmt##_to_bitint(lgrt_limb *r, int32_t rprec, T x) { \
        T magnitude = x & (FP_SIGN(T, E, F) - 1); \
        T int_bit = FP_INT_BIT(T, F); \
        bool negative = (x & FP_SIGN(T, E, F)) != 0; \
        unsigned int e = (unsigned int)(magnitude >> (F)); \
        \
        if (magnitude > FP_INF(T, E, F) || e < FP_BIAS(E) || (negative && rprec > 0)) { \
            bitint_clear(r, rprec); \
        } else if (magnitude == FP_INF(T, E, F)) { \
            bitint_saturate(r, rprec, negative); \
        } else { \
            bitint_fix( \
                r, rprec, negative, e - FP_BIAS(E), 0, (magnitude & (int_bit - 1)) | int_bit, (F) \
            ); \
        } \
    }

#define BITINT_FLOAT_ROUTINE(fmt, C, out) \
    C __floatbitint##fmt(const lgrt_limb *i, int32_t iprec) { \
        return out(fmt##_from_bitint(i, iprec)); \
    }

#define BITINT_FIX_ROUTINE(fmt, C, in) \
    void __fix##fmt##bitint(lgrt_limb *r, int32_t rprec, C a) { \
        fmt##_to_bitint(r, rprec, in(a)); \
    }

// GCC rejects floating-point types with -mgeneral-regs-only on ARM, with
// nothing to tell of it, so where the procedure call standard has them in
// floating-point registers, C has their bits in core registers, and assembly
// moves them. A branch does for an argument, which needs nothing afterwards.
#if defined(__ARM_PCS_VFP)

#   define BITINT_VFP_MOVE(name, symbol, moves, helper) \
        void name(void) __asm__ (symbol); \
        __attribute__((__naked__)) void name(void) { \
            __asm__ volatile ( \
                ".syntax unified\n\t" \
                ASM_BTI \
                moves \
                "b " helper "\n\t" \
                ASM_END \
            ); \
        }

#   define BITINT_VFP_FLOAT(fmt, T, load) \
        CX_VFP_HELPER T floatbitint##fmt##_bits(const lgrt_limb *i, int32_t iprec) { \
            return fmt##_from_bitint(i, iprec); \
        } \
        \
        CX_VFP_ENTRY( \
            floatbitint##fmt, "__floatbitint" #fmt, "8", "", "floatbitint" #fmt "_bits", load \
        )

#   define BITINT_VFP_FIX(fmt, T, moves) \
        CX_VFP_HELPER void fix##fmt##bitint_bits(lgrt_limb *r, int32_t rprec, T a) { \
            fmt##_to_bitint(r, rprec, a); \
        } \
        \
        BITINT_VFP_MOVE(fix##fmt##bitint, "__fix" #fmt "bitint", moves, "fix" #fmt "bitint_bits")

#endif // defined(__ARM_PCS_VFP)

#if LGRT_SOFT_FLOAT

BITINT_TO_FP(sf, uint32_t, 8, 23)
BITINT_FROM_FP(sf, uint32_t, 8, 23)

#if BITINT_GCC
#if defined(__ARM_PCS_VFP)
BITINT_VFP_FLOAT(sf, uint32_t, "vmov s0, r0\n\t")
BITINT_VFP_FIX(sf, uint32_t, "vmov r2, s0\n\t")
#else
BITINT_FLOAT_ROUTINE(sf, sf_value, sf_from_bits)
BITINT_FIX_ROUTINE(sf, sf_value, sf_to_bits)
#endif
#endif

#if SOFT_DOUBLE

BITINT_TO_FP(df, uint64_t, 11, 52)
BITINT_FROM_FP(df, uint64_t, 11, 52)

#if BITINT_GCC
#if defined(__ARM_PCS_VFP)
BITINT_VFP_FLOAT(df, uint64_t, "vmov d0, r0, r1\n\t")
BITINT_VFP_FIX(df, uint64_t, "vmov r2, r3, d0\n\t")
#else
BITINT_FLOAT_ROUTINE(df, df_value, df_from_bits)
BITINT_FIX_ROUTINE(df, df_value, df_to_bits)
#endif
#endif

#endif

#if defined(__arm__) || SOFT_HF
BITINT_TO_FP(hf, uint32_t, 5, 10)
BITINT_FROM_FP(hf, uint32_t, 5, 10)
#endif

// ARM's half comes back where float does, in the low half of that. Compilers
// have no half to convert on LoongArch.
#if BITINT_GCC
#if defined(__ARM_PCS_VFP)
BITINT_VFP_FLOAT(hf, uint32_t, "vmov s0, r0\n\t")
#elif defined(__arm__)
BITINT_FLOAT_ROUTINE(hf, uint32_t, sf_from_bits)
#elif SOFT_HF && !HF_PASSED_AS_INT && !defined(__loongarch__)
BITINT_FLOAT_ROUTINE(hf, hf_value, hf_from_bits)
#if defined(SOFT_BF)
BITINT_TO_FP(bf, uint32_t, 8, 7)
BITINT_FLOAT_ROUTINE(bf, bf_value, bf_from_bits)
#endif
#endif
#endif

#endif // LGRT_SOFT_FLOAT

#if SOFT_WIDE

// These too are in their own core, over two words, whose significands reach
// beyond 64 bits in part or in all.
#define BITINT_WIDE_FROM_BITS(fmt, M, F) \
    BITINT_HELPER struct wide fmt##_from_bitint(const lgrt_limb *i, int32_t iprec) { \
        struct bitint x; \
        struct wide sig; \
        uint64_t sign; \
        size_t length; \
        \
        bitint_load(&x, i, iprec); \
        if (x.count == 0) { \
            return wide_make(0, 0); \
        } \
        sign = x.negative ? WIDE_SIGN : 0; \
        length = bitint_length(&x); \
        if (length - 1 >= (size_t)((M) - WIDE_BIAS(M))) { \
            return fmt##_round_pack(sign, (M), wide_make(0, 0)); \
        } \
        if (length <= (F) + 4) { \
            sig = wide_shl( \
                wide_make(bitint_extract(&x, 64), bitint_extract(&x, 0)), \
                (F) + 4 - (unsigned int)length \
            ); \
        } else { \
            size_t lost = length - ((F) + 4); \
            \
            sig = wide_make(bitint_extract(&x, lost + 64), bitint_extract(&x, lost)); \
            sig.low |= (uint64_t)bitint_any_below(&x, lost); \
        } \
        return fmt##_round_pack(sign, WIDE_BIAS(M) + (unsigned int)length - 1, sig); \
    }

#define BITINT_WIDE_TO_BITS(fmt, M, F) \
    BITINT_HELPER void fmt##_to_bitint(lgrt_limb *r, int32_t rprec, struct wide x) { \
        struct wide magnitude = WIDE_MAGNITUDE(x); \
        struct wide inf = WIDE_INF(M, F); \
        struct wide sig = wide_or(wide_low_bits(magnitude, (F)), WIDE_INT_BIT(F)); \
        bool negative = (x.high & WIDE_SIGN) != 0; \
        unsigned int e = wide_exponent(magnitude, (F)); \
        \
        if (wide_lt(inf, magnitude) || e < WIDE_BIAS(M) || (negative && rprec > 0)) { \
            bitint_clear(r, rprec); \
        } else if (wide_eq(magnitude, inf)) { \
            bitint_saturate(r, rprec, negative); \
        } else { \
            bitint_fix(r, rprec, negative, e - WIDE_BIAS(M), sig.high, sig.low, (F)); \
        } \
    }

// PowerPC has this format under another name, and no routines here for it.
#if (SOFT_QUAD || QUAD_OWN_NAMES) && !defined(__powerpc__)
BITINT_WIDE_FROM_BITS(tf, 32767, 112)
BITINT_WIDE_TO_BITS(tf, 32767, 112)
#endif

#if BITINT_GCC && SOFT_QUAD
BITINT_FLOAT_ROUTINE(tf, quad_value, tf_from_bits)
BITINT_FIX_ROUTINE(tf, quad_value, tf_to_bits)
#endif

#if defined(__i386__) || defined(__x86_64__)

BITINT_WIDE_TO_BITS(xf, XF_EXP_MAX, 63)

#if defined(__clang__) || XF_RETURNED
BITINT_WIDE_FROM_BITS(xf, XF_EXP_MAX, 63)
#endif

#if defined(__clang__) && defined(__x86_64__)
void __fixxfbitint(
    lgrt_limb *r,
    int32_t rprec,
    uint64_t rdx,
    uint64_t rcx,
    uint64_t r8,
    uint64_t r9,
    xf_argument a
) {
    (void)rdx;
    (void)rcx;
    (void)r8;
    (void)r9;
    xf_to_bitint(r, rprec, xf_to_bits(a));
}
#else
void __fixxfbitint(lgrt_limb *r, int32_t rprec, xf_argument a) {
    xf_to_bitint(r, rprec, xf_to_bits(a));
}
#endif

#if defined(__clang__)
void __floatbitintxf(const lgrt_limb *i, int32_t iprec) {
    xf_return(xf_from_bitint(i, iprec));
}
#elif XF_RETURNED
BITINT_FLOAT_ROUTINE(xf, xf_value, xf_from_bits)
#endif

#endif // defined(__i386__) || defined(__x86_64__)

#endif // SOFT_WIDE

#endif // LGRT_SOFT_FLOAT || SOFT_XF

// Clang takes _BitInt of up to 128 bits on targets where C has no integer of
// that width, and calls the routines of that width for what it does not do
// itself, each release for its own share of them. It passes such an integer in
// words in their order in memory, as far as the registers for arguments go: in
// four of them, or by reference, or on the stack. It comes back in four
// registers, or in memory by a hidden pointer.
#if !HAS_INT128 && (!defined(__arm__) || defined(__ARM_EABI__))

struct ti {
    lgrt_limb words[4];
};

// Two 64-bit integers go where one of these goes, but for a structure.
#if defined(__mips__) || defined(__powerpc__) || defined(__sparc__) || defined(__hexagon__)

#define TI_PARAMETER(a) uint64_t a##_first, uint64_t a##_second
#define TI_VALUE(a) ti_from_pair(a##_first, a##_second)

// Where neither the routines that return these nor those of floating point are
// there, as for Clang on PowerPC with AltiVec in a plain build, nothing uses
// this, which Clang warns of.
__attribute__((__unused__)) static inline struct ti ti_from_pair(uint64_t first, uint64_t second) {
    uint64_t pair[2] = { first, second };
    struct ti x;

    __builtin_memcpy(&x, pair, sizeof(pair));
    return x;
}

#else // defined(__mips__) || defined(__powerpc__) || defined(__sparc__) || defined(__hexagon__)

#define TI_PARAMETER(a) struct ti a
#define TI_VALUE(a) (a)

#endif // defined(__mips__) || defined(__powerpc__) || defined(__sparc__) || defined(__hexagon__)

// What a compiler returns in the same place. It is a vector on ARM, where only
// the base procedure call standard has it in core registers, and for Clang on
// PowerPC, where only a vector goes in registers, which AltiVec would make its
// own.
#if defined(__arm__) || (defined(__powerpc__) && defined(__clang__))
typedef uint32_t ti_return __attribute__((__vector_size__(16)));
#elif defined(__mips__) || defined(__powerpc__) || defined(__sparc__)
__extension__ typedef _Complex unsigned long long ti_return;
#else
typedef struct ti ti_return;
#endif

// MIPS16 code has no access to the floating-point registers that pass values,
// so these are not MIPS16 code, as with other routines of floating point.
#if defined(__mips16) && defined(__mips_hard_float)
#   define TI_FP_ABI __attribute__((__nomips16__))
#else
#   define TI_FP_ABI
#endif

#if defined(__arm__)
#   define TI_ABI AAPCS
#else
#   define TI_ABI TI_FP_ABI
#endif

#if defined(__powerpc__) && defined(__clang__) && defined(__ALTIVEC__)
#   define TI_RETURNED 0
#else
#   define TI_RETURNED 1
#endif

// The result of a routine, from limbs of the target's width, 32 bits on all of
// these, in the same order as in memory.
#if TI_RETURNED

TI_ABI static inline ti_return ti_out(struct ti x) {
    ti_return z;

    __builtin_memcpy(&z, &x, sizeof(struct ti));
    return z;
}

#define TI_DIVMOD(name, is_signed, is_remainder) \
    TI_ABI ti_return name(TI_PARAMETER(a), TI_PARAMETER(b)) { \
        struct ti x = TI_VALUE(a); \
        struct ti y = TI_VALUE(b); \
        struct ti result; \
        int32_t prec = (is_signed) ? -128 : 128; \
        \
        if (is_remainder) { \
            bitint_divmod(NULL, 0, result.words, 128, x.words, prec, y.words, prec); \
        } else { \
            bitint_divmod(result.words, 128, NULL, 0, x.words, prec, y.words, prec); \
        } \
        return ti_out(result); \
    }

TI_DIVMOD(__divti3, true, false)
TI_DIVMOD(__udivti3, false, false)
TI_DIVMOD(__modti3, true, true)
TI_DIVMOD(__umodti3, false, true)

// A signed product, whose overflow shows in the half above it not being the
// extension of what is below that. Clang has this inline on SPARC.
#if !defined(__sparc__)
TI_ABI ti_return __muloti4(TI_PARAMETER(a), TI_PARAMETER(b), int *overflow) {
    struct ti x = TI_VALUE(a);
    struct ti y = TI_VALUE(b);
    struct ti result;
    lgrt_limb wide[8];
    lgrt_limb fill;
    bool overflowed = false;

    bitint_mul(wide, 256, x.words, -128, y.words, -128);
    for (size_t i = 0; i < 4; i++) {
        result.words[LIMB_AT(4, i)] = wide[LIMB_AT(8, i)];
    }
    fill = (wide[LIMB_AT(8, 3)] >> (LIMB_BITS - 1)) != 0 ? ~(lgrt_limb)0 : 0;
    for (size_t i = 4; i < 8; i++) {
        overflowed = overflowed || wide[LIMB_AT(8, i)] != fill;
    }
    *overflow = overflowed;
    return ti_out(result);
}
#endif

// The other targets have only inline multiplication of this width.
#if !defined(__i386__) && !defined(__hexagon__) && !defined(__loongarch__)
TI_ABI ti_return __multi3(TI_PARAMETER(a), TI_PARAMETER(b)) {
    struct ti x = TI_VALUE(a);
    struct ti y = TI_VALUE(b);
    struct ti result;

    bitint_mul(result.words, 128, x.words, 128, y.words, 128);
    return ti_out(result);
}
#endif

// Clang before 14 calls these on RISC-V, where it has them nowhere else.
#if defined(__riscv)

static inline struct ti ti_shift_right(struct ti x, unsigned int n, lgrt_limb fill) {
    struct ti result;
    size_t skip = n / LIMB_BITS;
    unsigned int s = n % LIMB_BITS;

    for (size_t i = 0; i < 4; i++) {
        lgrt_limb lo = i + skip < 4 ? x.words[LIMB_AT(4, i + skip)] : fill;
        lgrt_limb hi = i + skip + 1 < 4 ? x.words[LIMB_AT(4, i + skip + 1)] : fill;

        result.words[LIMB_AT(4, i)] = (lo >> s) | ((hi << 1) << (LIMB_BITS - 1 - s));
    }
    return result;
}

ti_return __ashlti3(struct ti a, int b) {
    struct ti result;
    size_t skip = (unsigned int)b / LIMB_BITS;
    unsigned int s = (unsigned int)b % LIMB_BITS;

    for (size_t i = 0; i < 4; i++) {
        lgrt_limb hi = i >= skip ? a.words[LIMB_AT(4, i - skip)] : 0;
        lgrt_limb lo = i >= skip + 1 ? a.words[LIMB_AT(4, i - skip - 1)] : 0;

        result.words[LIMB_AT(4, i)] = LIMB_SHIFT(hi, lo, s);
    }
    return result;
}

ti_return __lshrti3(struct ti a, int b) {
    return ti_shift_right(a, (unsigned int)b, 0);
}

ti_return __ashrti3(struct ti a, int b) {
    lgrt_limb top = a.words[LIMB_AT(4, 3)];

    return ti_shift_right(a, (unsigned int)b, (top >> (LIMB_BITS - 1)) != 0 ? ~(lgrt_limb)0 : 0);
}

#endif // defined(__riscv)

#endif // TI_RETURNED

#if LGRT_SOFT_FLOAT

// Conversions, by the same helpers as _BitInt, for all but the integer in the
// forms above. With the integer coming back in core registers on ARM, the base
// standard goes for all of the routine under the other one too, and assembly
// moves a floating-point value.
#define TI_FROM_INT(fmt, C, out, signed_name, unsigned_name) \
    TI_FP_ABI C signed_name(TI_PARAMETER(a)) { \
        struct ti x = TI_VALUE(a); \
        \
        return out(fmt##_from_bitint(x.words, -128)); \
    } \
    \
    TI_FP_ABI C unsigned_name(TI_PARAMETER(a)) { \
        struct ti x = TI_VALUE(a); \
        \
        return out(fmt##_from_bitint(x.words, 128)); \
    }

#define TI_TO_INT_NAMED(fmt, C, in, name, prec) \
    TI_ABI ti_return name(C a) { \
        struct ti result; \
        \
        fmt##_to_bitint(result.words, (prec), in(a)); \
        return ti_out(result); \
    }

#if defined(__ARM_PCS_VFP)

#define TI_VFP_TO_INT(fmt, T, name, prec, moves) \
    CX_VFP_HELPER AAPCS ti_return name##_bits(T a) { \
        struct ti result; \
        \
        fmt##_to_bitint(result.words, (prec), a); \
        return ti_out(result); \
    } \
    \
    BITINT_VFP_MOVE(name, "__" #name, moves, #name "_bits")

#define TI_VFP_FROM_INT(fmt, T, name, prec, load) \
    CX_VFP_HELPER T name##_bits(struct ti a) { \
        return fmt##_from_bitint(a.words, (prec)); \
    } \
    \
    CX_VFP_ENTRY(name, "__" #name, "8", "", #name "_bits", load)

#if defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#   define TI_VFP_DF_IN "vmov r1, r0, d0\n\t"
#   define TI_VFP_DF_OUT "vmov d0, r1, r0\n\t"
#else
#   define TI_VFP_DF_IN "vmov r0, r1, d0\n\t"
#   define TI_VFP_DF_OUT "vmov d0, r0, r1\n\t"
#endif

TI_VFP_TO_INT(sf, uint32_t, fixsfti, -128, "vmov r0, s0\n\t")
TI_VFP_TO_INT(sf, uint32_t, fixunssfti, 128, "vmov r0, s0\n\t")
TI_VFP_TO_INT(df, uint64_t, fixdfti, -128, TI_VFP_DF_IN)
TI_VFP_TO_INT(df, uint64_t, fixunsdfti, 128, TI_VFP_DF_IN)
TI_VFP_FROM_INT(sf, uint32_t, floattisf, -128, "vmov s0, r0\n\t")
TI_VFP_FROM_INT(sf, uint32_t, floatuntisf, 128, "vmov s0, r0\n\t")
TI_VFP_FROM_INT(df, uint64_t, floattidf, -128, TI_VFP_DF_OUT)
TI_VFP_FROM_INT(df, uint64_t, floatuntidf, 128, TI_VFP_DF_OUT)

#else // defined(__ARM_PCS_VFP)

#if TI_RETURNED
TI_TO_INT_NAMED(sf, sf_value, sf_to_bits, __fixsfti, -128)
TI_TO_INT_NAMED(sf, sf_value, sf_to_bits, __fixunssfti, 128)
#if SOFT_DOUBLE
TI_TO_INT_NAMED(df, df_value, df_to_bits, __fixdfti, -128)
TI_TO_INT_NAMED(df, df_value, df_to_bits, __fixunsdfti, 128)
#endif
#endif

TI_FROM_INT(sf, sf_value, sf_from_bits, __floattisf, __floatuntisf)
#if SOFT_DOUBLE
TI_FROM_INT(df, df_value, df_from_bits, __floattidf, __floatuntidf)
#endif

#endif // defined(__ARM_PCS_VFP)

// Clang calls these for half where the instruction set has it.
#if defined(__arm__) && defined(__clang__) && defined(__ARM_FEATURE_FP16_SCALAR_ARITHMETIC)
#if defined(__ARM_PCS_VFP)
TI_VFP_TO_INT(hf, uint32_t, fixhfti, -128, "vmov r0, s0\n\t")
TI_VFP_TO_INT(hf, uint32_t, fixunshfti, 128, "vmov r0, s0\n\t")
TI_VFP_FROM_INT(hf, uint32_t, floattihf, -128, "vmov s0, r0\n\t")
TI_VFP_FROM_INT(hf, uint32_t, floatuntihf, 128, "vmov s0, r0\n\t")
#else
TI_TO_INT_NAMED(hf, hf_value, hf_to_bits, __fixhfti, -128)
TI_TO_INT_NAMED(hf, hf_value, hf_to_bits, __fixunshfti, 128)
TI_FROM_INT(hf, hf_value, hf_from_bits, __floattihf, __floatuntihf)
#endif
#endif

// Hexagon has names of its own for these, from releases before 20.
#if defined(__hexagon__)
FP_ALIAS(ti_return, __hexagon_fixsfti, "__fixsfti", (sf_value a))
FP_ALIAS(ti_return, __hexagon_fixunssfti, "__fixunssfti", (sf_value a))
FP_ALIAS(ti_return, __hexagon_fixdfti, "__fixdfti", (df_value a))
FP_ALIAS(ti_return, __hexagon_fixunsdfti, "__fixunsdfti", (df_value a))
FP_ALIAS(sf_value, __hexagon_floattisf, "__floattisf", (uint64_t a_first, uint64_t a_second))
FP_ALIAS(df_value, __hexagon_floattidf, "__floattidf", (uint64_t a_first, uint64_t a_second))
#endif

// On IA-32, the integer goes on the stack where this format goes, which moved
// in Clang 21, along with the alignment of 16 that both have from then on.
#if SOFT_QUAD && !defined(__powerpc__)
#if defined(__i386__)
#define TI_TF_FROM_INT(name, prec) \
    quad_value name(quad_value a) { \
        struct ti x; \
        \
        __builtin_memcpy(&x, &a, sizeof(struct ti)); \
        return tf_from_bits(tf_from_bitint(x.words, (prec))); \
    }

TI_TF_FROM_INT(__floattitf, -128)
TI_TF_FROM_INT(__floatuntitf, 128)
#else
TI_FROM_INT(tf, quad_value, tf_from_bits, __floattitf, __floatuntitf)
#endif
#if TI_RETURNED
TI_TO_INT_NAMED(tf, quad_value, tf_to_bits, __fixtfti, -128)
TI_TO_INT_NAMED(tf, quad_value, tf_to_bits, __fixunstfti, 128)
#endif
#endif

// SPARC passes long double in the forms of its routines of other names.
#if defined(__sparc__) && QUAD_OWN_NAMES

static inline ti_return tf_fix_ti(struct wide x, int32_t prec) {
    struct ti result;

    tf_to_bitint(result.words, prec, x);
    return ti_out(result);
}

#if TF_IN_REGISTERS
TI_FROM_INT(tf, tf_registers, tf_to_registers, __floattitf, __floatuntitf)
#else
TI_FROM_INT(tf, quad_value, tf_from_bits, __floattitf, __floatuntitf)
#endif
TF_TO(__fixtfti, ti_return, tf_fix_ti(x, -128))
TF_TO(__fixunstfti, ti_return, tf_fix_ti(x, 128))

#endif

#if defined(__i386__)

#if SOFT_HF && !HF_PASSED_AS_INT
TI_FROM_INT(hf, hf_value, hf_from_bits, __floattihf, __floatuntihf)
TI_TO_INT_NAMED(hf, hf_value, hf_to_bits, __fixhfti, -128)
TI_TO_INT_NAMED(hf, hf_value, hf_to_bits, __fixunshfti, 128)
#endif

TI_TO_INT_NAMED(xf, xf_argument, xf_to_bits, __fixxfti, -128)
TI_TO_INT_NAMED(xf, xf_argument, xf_to_bits, __fixunsxfti, 128)

#if defined(__clang__)
void __floattixf(struct ti a) {
    xf_return(xf_from_bitint(a.words, -128));
}

void __floatuntixf(struct ti a) {
    xf_return(xf_from_bitint(a.words, 128));
}
#elif XF_RETURNED
TI_FROM_INT(xf, xf_value, xf_from_bits, __floattixf, __floatuntixf)
#endif

#endif // defined(__i386__)

// IBM long double. Its first double can be as large as 2^128, or more, with a
// second that takes it back into range, so the sums go on limbs with room for
// that. Clang goes through __floattitf for unsigned integers too.
#if defined(__powerpc__) && HAS_IBM_128

#define IBM_TI_LIMBS 6
#define IBM_TI_PREC 192

static inline void ibm_ti_sum(
    lgrt_limb *r,
    const lgrt_limb *a,
    const lgrt_limb *b,
    bool subtract,
    bool one_less
) {
    lgrt_limb carry = subtract && !one_less ? 1 : 0;

    for (size_t i = 0; i < IBM_TI_LIMBS; i++) {
        size_t at = LIMB_AT(IBM_TI_LIMBS, i);
        double_limb sum = (double_limb)a[at] + (subtract ? ~b[at] : b[at]) + carry;

        r[at] = (lgrt_limb)sum;
        carry = (lgrt_limb)(sum >> LIMB_BITS);
    }
}

#if TI_RETURNED

// As other conversions of this format do: a second double opposite to the
// first takes off its integer part, and 1 more if that leaves a fraction,
// which it can only do where the first has none.
static inline ti_return ibm_fix_ti(struct ibm_bits x, int32_t prec) {
    uint64_t mask = IBM_SIGN - 1;
    uint64_t high = x.high & mask;
    uint64_t low = x.low & mask;
    bool negative = ibm_cx_negative(x);
    bool below = ((x.high ^ x.low) & IBM_SIGN) != 0 && low != 0;
    lgrt_limb first[IBM_TI_LIMBS];
    lgrt_limb second[IBM_TI_LIMBS];
    lgrt_limb sum[IBM_TI_LIMBS];
    struct ti result;

    if (high > IBM_INF || (negative && prec > 0)) {
        bitint_clear(result.words, prec);
        return ti_out(result);
    }
    df_to_bitint(first, IBM_TI_PREC, high);
    df_to_bitint(second, IBM_TI_PREC, low);
    ibm_ti_sum(
        sum, first, second, below, below && !ibm_has_fraction(high) && ibm_has_fraction(low)
    );
    if (sum[LIMB_AT(IBM_TI_LIMBS, 4)] != 0 || sum[LIMB_AT(IBM_TI_LIMBS, 5)] != 0
     || (prec < 0 && (sum[LIMB_AT(IBM_TI_LIMBS, 3)] >> (LIMB_BITS - 1)) != 0)) {
        bitint_saturate(result.words, prec, negative);
        return ti_out(result);
    }
    for (size_t i = 0; i < 4; i++) {
        result.words[LIMB_AT(4, i)] = sum[LIMB_AT(IBM_TI_LIMBS, i)];
    }
    if (negative) {
        bitint_negate(result.words, 4);
    }
    return ti_out(result);
}

IBM_TO_NAMED(ti_return, __fixtfti, ibm_fix_ti(x, -128))
IBM_TO_NAMED(ti_return, __fixunstfti, ibm_fix_ti(x, 128))

#endif // TI_RETURNED

// The first double is the integer rounded, and the second what that leaves, as
// a signed value, rounded in turn.
ibm_value __floattitf(TI_PARAMETER(a)) {
    struct ti x = TI_VALUE(a);
    struct bitint value;
    lgrt_limb magnitude[IBM_TI_LIMBS];
    lgrt_limb first[IBM_TI_LIMBS];
    lgrt_limb rest[IBM_TI_LIMBS];
    uint64_t high;
    uint64_t low;

    bitint_load(&value, x.words, -128);
    for (size_t i = 0; i < IBM_TI_LIMBS; i++) {
        magnitude[LIMB_AT(IBM_TI_LIMBS, i)] = i < value.count ? bitint_magnitude(&value, i) : 0;
    }
    high = df_from_bitint(magnitude, IBM_TI_PREC);
    df_to_bitint(first, IBM_TI_PREC, high);
    ibm_ti_sum(rest, magnitude, first, true, false);
    low = df_from_bitint(rest, -IBM_TI_PREC);
    if (value.negative) {
        high ^= IBM_SIGN;
        if (low != 0) {
            low ^= IBM_SIGN;
        }
    }
    return ibm_from_bits(ibm_make(high, low));
}

#endif // defined(__powerpc__) && HAS_IBM_128

#endif // LGRT_SOFT_FLOAT

#endif // !HAS_INT128 && (!defined(__arm__) || defined(__ARM_EABI__))

#endif // BITINT

// Fixed-point arithmetic, of ISO/IEC TR 18037, where GCC has its types. Clang
// has them only with -ffixed-point, and then calls none of these. Each routine
// works on the bits of its operands, zero-extended into a word of type L, of N
// bits, at least as wide as int so as not to promote. w is the width of the
// type and f the number of its fractional bits, as the compiler defines them.
//
// Where TR 18037 leaves it open: products round to the nearest value, with
// ties up, and quotients towards zero; overflow without saturation wraps; a
// shift count that is negative, or no less than w, shifts out every bit; and a
// zero divisor gives the limit of the type with the sign of the dividend.
#if !defined(__clang__) && defined(__QQ_FBIT__)

// Workaround: GCC 15, 64-bit MIPS, -O1: its if-conversion crashes, in
// mips_load_store_insns, on some 128-bit arithmetic of the conversions.
#if defined(__mips64) && __GNUC__ == 15
#   pragma GCC push_options
#   pragma GCC optimize("no-if-conversion")
#endif

#if defined(__ARM_EABI__)
#   define FX_NAME(name) __gnu_##name
#else
#   define FX_NAME(name) __##name
#endif

// Strict modes have no _Fract or _Accum, but do have constants of those.
__extension__ typedef __typeof__(0.5r) fract;
__extension__ typedef __typeof__(0.5ur) ufract;
__extension__ typedef __typeof__(0.5k) accum;
__extension__ typedef __typeof__(0.5uk) uaccum;

// Constant operands make a conversion a few instructions, when optimising.
#if defined(__OPTIMIZE__)
#   define FX_INLINE __attribute__((__always_inline__)) static inline
#else
#   define FX_INLINE static inline
#endif

// The number of the highest bit set in a value that is not zero.
#if defined(__AVR__)

#define FX_TOP_OF(N, L) \
    static inline unsigned int fx_top##N(L x) { \
        unsigned int top = 0; \
        \
        while ((x >>= 1) != 0) { \
            top++; \
        } \
        return top; \
    }

FX_TOP_OF(16, uint16_t)
FX_TOP_OF(32, uint32_t)
FX_TOP_OF(64, uint64_t)

#define FX_TOP(N, x) fx_top##N(x)

#else
#define FX_TOP(N, x) ((N) - 1 - clz##N(x))
#endif

// fx_umulN gives the high w bits of the product of two w-bit values, and its
// low w bits in *low. Without a type for that product, it comes from pieces of
// half a word each, whose products do fit, for a w that is N, the one w there
// is for an N above 32. Neither middle sum can overflow, as (2^(N/2) - 1)^2 +
// 2^(N/2) - 1 < 2^N.
static inline uint32_t fx_umul32(uint32_t a, uint32_t b, unsigned int w, uint32_t *low) {
    uint32_t mask = ~(uint32_t)0 >> (32 - w);
    uint64_t product;

    if (w <= 16) {
        uint32_t narrow = a * b;

        *low = narrow & mask;
        return narrow >> w;
    }
    product = (uint64_t)a * b;
    *low = (uint32_t)product & mask;
    return (uint32_t)(product >> w);
}

#define FX_UMUL_PIECES(N, L) \
    static inline L fx_umul##N(L a, L b, unsigned int w, L *low) { \
        L half = ~(L)0 >> ((N) / 2); \
        L a0 = a & half; \
        L a1 = a >> ((N) / 2); \
        L b0 = b & half; \
        L b1 = b >> ((N) / 2); \
        L p00 = a0 * b0; \
        L m1 = a1 * b0 + (p00 >> ((N) / 2)); \
        L m2 = a0 * b1 + (m1 & half); \
        \
        (void)w; \
        *low = (m2 << ((N) / 2)) | (p00 & half); \
        return a1 * b1 + (m1 >> ((N) / 2)) + (m2 >> ((N) / 2)); \
    }

#if HAS_INT128
static inline uint64_t fx_umul64(uint64_t a, uint64_t b, unsigned int w, uint64_t *low) {
    u128 product = (u128)a * b;

    (void)w;
    *low = (uint64_t)product;
    return (uint64_t)(product >> 64);
}

FX_UMUL_PIECES(128, u128)
#else
FX_UMUL_PIECES(64, uint64_t)
#endif

// fx_udivN gives the low w bits of n * 2^f / d, rounded down, for a d that is
// not zero, and tells in *overflow whether the quotient has more bits than
// that. Without a type for that dividend, the bits below the integer part of
// the quotient come one at a time, from a remainder always below d, which goes
// above N bits only to go back by subtracting d.
#if defined(__AVR__)

// Without room to spare, bit by bit, for size: the dividend leaves q at the
// top as the bits of the quotient enter at the bottom, for w steps, and then f
// zeros follow it, while q overflows. The remainder stays below d, but on its
// way there.
#define FX_UDIV_SERIAL(N, L) \
    static inline L fx_udiv##N(L n, L d, unsigned int w, unsigned int f, bool *overflow) { \
        L mask = ~(L)0 >> ((N) - w); \
        L q = n << ((N) - w); \
        L r = 0; \
        bool lost = false; \
        \
        for (unsigned int i = w + f; i != 0; i--) { \
            bool top = (q >> ((N) - 1)) != 0; \
            bool carry = (r >> ((N) - 1)) != 0; \
            \
            q <<= 1; \
            r <<= 1; \
            if (i <= f) { \
                lost = lost || top; \
            } else if (top) { \
                r |= 1; \
            } \
            if (carry || r >= d) { \
                r -= d; \
                q |= 1; \
            } \
        } \
        *overflow = lost || (q & ~mask) != 0; \
        return q & mask; \
    }

FX_UDIV_SERIAL(16, uint16_t)
FX_UDIV_SERIAL(32, uint32_t)
FX_UDIV_SERIAL(64, uint64_t)

#else // defined(__AVR__)

static inline uint32_t fx_udiv32(
    uint32_t n,
    uint32_t d,
    unsigned int w,
    unsigned int f,
    bool *overflow
) {
    uint32_t mask = ~(uint32_t)0 >> (32 - w);
    uint64_t q;

    if (w + f <= 32) {
        uint32_t narrow = (n << f) / d;

        *overflow = (narrow >> w) != 0;
        return narrow & mask;
    }
    q = ((uint64_t)n << f) / d;
    *overflow = (q >> w) != 0;
    return (uint32_t)q & mask;
}

#define FX_UDIV_BITS(N, L) \
    static inline L fx_udiv##N(L n, L d, unsigned int w, unsigned int f, bool *overflow) { \
        L q = n / d; \
        L r = n - q * d; \
        \
        (void)w; \
        *overflow = false; \
        for (size_t i = 0; i < f; i++) { \
            bool carry = (r >> ((N) - 1)) != 0; \
            \
            *overflow = *overflow || (q >> ((N) - 1)) != 0; \
            q <<= 1; \
            r <<= 1; \
            if (carry || r >= d) { \
                r -= d; \
                q |= 1; \
            } \
        } \
        return q; \
    }

#if HAS_INT128
static inline uint64_t fx_udiv64(
    uint64_t n,
    uint64_t d,
    unsigned int w,
    unsigned int f,
    bool *overflow
) {
    u128 q = ((u128)n << f) / d;

    (void)w;
    *overflow = (uint64_t)(q >> 64) != 0;
    return (uint64_t)q;
}

FX_UDIV_BITS(128, u128)
#else
FX_UDIV_BITS(64, uint64_t)
#endif

#endif // defined(__AVR__)

#define FX_BASICS(N, L) \
    static inline L fx_mask##N(unsigned int w) { \
        return ~(L)0 >> ((N) - w); \
    } \
    \
    static inline bool fx_sign##N(L x, unsigned int w) { \
        return (x >> (w - 1)) != 0; \
    } \
    \
    /* The bits of the most negative value, or of the most positive one. */ \
    static inline L fx_limit##N(bool negative, unsigned int w) { \
        return (fx_mask##N(w) >> 1) + (L)negative; \
    } \
    \
    /* With the sign bits inverted, unsigned order is the signed order. */ \
    static inline int fx_cmp##N(L a, L b, unsigned int w, bool is_signed) { \
        L flip = is_signed ? fx_limit##N(true, w) : 0; \
        L x = a ^ flip; \
        L y = b ^ flip; \
        \
        return x < y ? 0 : x > y ? 2 : 1; \
    }

#define FX_ADDITION(N, L) \
    static inline L fx_add##N(L a, L b, unsigned int w) { \
        return (a + b) & fx_mask##N(w); \
    } \
    \
    /* A sum that overflows has the sign that neither operand has. */ \
    static inline L fx_ssadd##N(L a, L b, unsigned int w) { \
        L r = fx_add##N(a, b, w); \
        \
        if (fx_sign##N((a ^ r) & (b ^ r), w)) { \
            return fx_limit##N(fx_sign##N(a, w), w); \
        } \
        return r; \
    } \
    \
    static inline L fx_usadd##N(L a, L b, unsigned int w) { \
        L r = fx_add##N(a, b, w); \
        \
        return r < a ? fx_mask##N(w) : r; \
    } \
    \
    static inline L fx_sub##N(L a, L b, unsigned int w) { \
        return (a - b) & fx_mask##N(w); \
    } \
    \
    /* A difference that overflows comes from opposite signs, and has b's. */ \
    static inline L fx_sssub##N(L a, L b, unsigned int w) { \
        L r = fx_sub##N(a, b, w); \
        \
        if (fx_sign##N((a ^ b) & (a ^ r), w)) { \
            return fx_limit##N(fx_sign##N(a, w), w); \
        } \
        return r; \
    } \
    \
    static inline L fx_ussub##N(L a, L b) { \
        return a < b ? 0 : a - b; \
    } \
    \
    static inline L fx_neg##N(L a, unsigned int w) { \
        return ((L)0 - a) & fx_mask##N(w); \
    } \
    \
    static inline L fx_ssneg##N(L a, unsigned int w) { \
        if (a == fx_limit##N(true, w)) { \
            return fx_limit##N(false, w); \
        } \
        return fx_neg##N(a, w); \
    } \
    \
    /* The negation of an unsigned value is never above zero. */ \
    static inline L fx_usneg##N(L a) { \
        (void)a; \
        return 0; \
    }

// A count as uint32_t puts a negative one out of range. A saturating shift has
// overflowed where shifting back does not give the operand.
#define FX_SHIFTS(N, L) \
    static inline L fx_ashl##N(L a, uint32_t count, unsigned int w) { \
        return count >= w ? 0 : (a << count) & fx_mask##N(w); \
    } \
    \
    static inline L fx_lshr##N(L a, uint32_t count, unsigned int w) { \
        return count >= w ? 0 : a >> count; \
    } \
    \
    static inline L fx_ashr##N(L a, uint32_t count, unsigned int w) { \
        L mask = fx_mask##N(w); \
        L fill = fx_sign##N(a, w) ? mask : 0; \
        \
        return count >= w ? fill : (a >> count) | (fill & ~(mask >> count)); \
    } \
    \
    static inline L fx_ssashl##N(L a, uint32_t count, unsigned int w) { \
        L r = fx_ashl##N(a, count, w); \
        \
        if (fx_ashr##N(r, count, w) != a) { \
            return fx_limit##N(fx_sign##N(a, w), w); \
        } \
        return r; \
    } \
    \
    static inline L fx_usashl##N(L a, uint32_t count, unsigned int w) { \
        L r = fx_ashl##N(a, count, w); \
        \
        return fx_lshr##N(r, count, w) != a ? fx_mask##N(w) : r; \
    }

// The high half of a signed product is that of the unsigned one, less each
// operand whose counterpart is negative. Adding half of the last place of the
// result rounds to the nearest value, with ties up. The carry out of the low
// half goes into the high one, and none comes out of that, as (2^w - 1)^2 +
// 2^(w - 1) < 2^(2w). A signed sum stays below 2^(2w - 1), so that its top bit
// is its sign. The result is the w bits from bit f up. A signed one has
// overflowed unless all above it, and its own top bit, are copies of that
// sign.
#define FX_MULTIPLICATION(N, L) \
    static inline L fx_mul##N( \
        L a, L b, unsigned int w, unsigned int f, bool is_signed, bool saturating \
    ) { \
        L mask = fx_mask##N(w); \
        L half = (L)1 << (f - 1); \
        L low; \
        L high = fx_umul##N(a, b, w, &low); \
        L r; \
        L above; \
        bool negative; \
        \
        if (is_signed) { \
            if (fx_sign##N(a, w)) { \
                high -= b; \
            } \
            if (fx_sign##N(b, w)) { \
                high -= a; \
            } \
        } \
        low = (low + half) & mask; \
        high = (high + (L)(low < half)) & mask; \
        r = f == w ? high : ((high << (w - f)) | (low >> f)) & mask; \
        if (!saturating) { \
            return r; \
        } \
        above = f == w ? 0 : high >> f; \
        if (!is_signed) { \
            return above != 0 ? mask : r; \
        } \
        negative = fx_sign##N(high, w); \
        if (above != (negative ? mask >> f : 0) || fx_sign##N(r, w) != negative) { \
            return fx_limit##N(negative, w); \
        } \
        return r; \
    }

// On magnitudes, which all fit in w bits, so that a quotient rounds towards
// zero. The bits of the most negative value are its magnitude too, so that the
// limit of either sign compares with the magnitude of a quotient.
#if defined(__AVR__)
#   define FX_DIVISION_INLINE FX_INLINE
#else
#   define FX_DIVISION_INLINE static inline
#endif

#define FX_DIVISION(N, L) \
    FX_DIVISION_INLINE L fx_div##N( \
        L a, L b, unsigned int w, unsigned int f, bool is_signed, bool saturating \
    ) { \
        bool negative_a = is_signed && fx_sign##N(a, w); \
        bool negative_b = is_signed && fx_sign##N(b, w); \
        bool negative = negative_a != negative_b; \
        L n = negative_a ? fx_neg##N(a, w) : a; \
        L d = negative_b ? fx_neg##N(b, w) : b; \
        L limit; \
        L q; \
        bool overflow; \
        \
        if (d == 0) { \
            return is_signed ? fx_limit##N(negative_a, w) : fx_mask##N(w); \
        } \
        q = fx_udiv##N(n, d, w, f, &overflow); \
        if (!is_signed) { \
            return saturating && overflow ? fx_mask##N(w) : q; \
        } \
        limit = fx_limit##N(negative, w); \
        if (saturating && (overflow || q > limit)) { \
            return limit; \
        } \
        return negative ? fx_neg##N(q, w) : q; \
    }

#define FX_CORE(N, L) \
    FX_BASICS(N, L) \
    FX_ADDITION(N, L) \
    FX_SHIFTS(N, L) \
    FX_MULTIPLICATION(N, L) \
    FX_DIVISION(N, L)

#if defined(__AVR__)

// On AVR, words of 16 and 32 bits have a type for their products, which goes
// by magnitudes, for size. The lower half of the last place of the result goes
// to the nearest value, with ties up, on the magnitude of a negative value too
// but for the tie itself. The product and that half fit in the wider type, as
// (2^w - 1)^2 + 2^(w - 1) < 2^(2w).
#define FX_DOUBLE_WORD_PRODUCTS(N, L, D) \
    FX_INLINE L fx_mul##N( \
        L a, L b, unsigned int w, unsigned int f, bool is_signed, bool saturating \
    ) { \
        bool negative_a = is_signed && fx_sign##N(a, w); \
        bool negative_b = is_signed && fx_sign##N(b, w); \
        bool negative = negative_a != negative_b; \
        L x = negative_a ? fx_neg##N(a, w) : a; \
        L y = negative_b ? fx_neg##N(b, w) : b; \
        L mask = fx_mask##N(w); \
        L limit = is_signed ? fx_limit##N(negative, w) : mask; \
        D r = (D)x * y + ((D)1 << (f - 1)) - (D)negative; \
        \
        r >>= f; \
        if (saturating && r > limit) { \
            return limit; \
        } \
        return (negative ? (L)0 - (L)r : (L)r) & mask; \
    }

#define FX_SMALL_CORE(N, L, D) \
    FX_BASICS(N, L) \
    FX_ADDITION(N, L) \
    FX_SHIFTS(N, L) \
    FX_DOUBLE_WORD_PRODUCTS(N, L, D) \
    FX_DIVISION(N, L)

FX_SMALL_CORE(16, uint16_t, uint32_t)
FX_SMALL_CORE(32, uint32_t, uint64_t)
#else // defined(__AVR__)
FX_CORE(32, uint32_t)
#endif // defined(__AVR__)
FX_CORE(64, uint64_t)
#if HAS_INT128
FX_CORE(128, u128)
#endif

// The modes name the types, as not all of them have a name in C.
#define FX_TYPE(m, M, base, U, N, L, W) \
    typedef base fx_##m __attribute__((__mode__(__##M##__))); \
    \
    static inline L fx_bits_##m(fx_##m x) { \
        union { \
            fx_##m value; \
            U bits; \
        } pun; \
        \
        pun.value = x; \
        return pun.bits & fx_mask##N(W); \
    } \
    \
    static inline fx_##m fx_value_##m(L x) { \
        union { \
            fx_##m value; \
            U bits; \
        } pun; \
        \
        pun.bits = (U)x; \
        return pun.value; \
    }

// The expression of each is over x and y, or count, for the operands.
#define FX_BINARY(op, m, L, expression) \
    fx_##m FX_NAME(op##m##3)(fx_##m a, fx_##m b) { \
        L x = fx_bits_##m(a); \
        L y = fx_bits_##m(b); \
        \
        return fx_value_##m(expression); \
    }

#define FX_UNARY(op, m, L, expression) \
    fx_##m FX_NAME(op##m##2)(fx_##m a) { \
        L x = fx_bits_##m(a); \
        \
        return fx_value_##m(expression); \
    }

// AVR's count is the byte that the word mode there makes it.
#if defined(__AVR__)
#   define FX_COUNT uint8_t
#else
#   define FX_COUNT int
#endif

#define FX_SHIFT(op, m, L, expression) \
    fx_##m FX_NAME(op##m##3)(fx_##m a, FX_COUNT b) { \
        L x = fx_bits_##m(a); \
        uint32_t count = (uint32_t)b; \
        \
        return fx_value_##m(expression); \
    }

// 0 if a is below b, 2 if above, and 1 if they are equal.
#define FX_COMPARE(m, N, L, W, is_signed) \
    int FX_NAME(cmp##m##2)(fx_##m a, fx_##m b) { \
        L x = fx_bits_##m(a); \
        L y = fx_bits_##m(b); \
        \
        return fx_cmp##N(x, y, W, is_signed); \
    }

#define FX_COMMON(m, N, L, W, F, is_signed) \
    FX_BINARY(add, m, L, fx_add##N(x, y, W)) \
    FX_BINARY(sub, m, L, fx_sub##N(x, y, W)) \
    FX_UNARY(neg, m, L, fx_neg##N(x, W)) \
    FX_BINARY(mul, m, L, fx_mul##N(x, y, W, F, is_signed, false)) \
    FX_SHIFT(ashl, m, L, fx_ashl##N(x, count, W)) \
    FX_COMPARE(m, N, L, W, is_signed)

#define FX_SIGNED_ROUTINES(m, N, L, W, F) \
    FX_COMMON(m, N, L, W, F, true) \
    FX_BINARY(ssadd, m, L, fx_ssadd##N(x, y, W)) \
    FX_BINARY(sssub, m, L, fx_sssub##N(x, y, W)) \
    FX_UNARY(ssneg, m, L, fx_ssneg##N(x, W)) \
    FX_BINARY(ssmul, m, L, fx_mul##N(x, y, W, F, true, true)) \
    FX_BINARY(div, m, L, fx_div##N(x, y, W, F, true, false)) \
    FX_BINARY(ssdiv, m, L, fx_div##N(x, y, W, F, true, true)) \
    FX_SHIFT(ashr, m, L, fx_ashr##N(x, count, W)) \
    FX_SHIFT(ssashl, m, L, fx_ssashl##N(x, count, W))

#define FX_UNSIGNED_ROUTINES(m, N, L, W, F) \
    FX_COMMON(m, N, L, W, F, false) \
    FX_BINARY(usadd, m, L, fx_usadd##N(x, y, W)) \
    FX_BINARY(ussub, m, L, fx_ussub##N(x, y)) \
    FX_UNARY(usneg, m, L, fx_usneg##N(x)) \
    FX_BINARY(usmul, m, L, fx_mul##N(x, y, W, F, false, true)) \
    FX_BINARY(udiv, m, L, fx_div##N(x, y, W, F, false, false)) \
    FX_BINARY(usdiv, m, L, fx_div##N(x, y, W, F, false, true)) \
    FX_SHIFT(lshr, m, L, fx_lshr##N(x, count, W)) \
    FX_SHIFT(usashl, m, L, fx_usashl##N(x, count, W))

#define FX_SIGNED(m, M, base, U, N, L) \
    FX_TYPE(m, M, base, U, N, L, (__##M##_IBIT__ + __##M##_FBIT__ + 1)) \
    FX_SIGNED_ROUTINES(m, N, L, (__##M##_IBIT__ + __##M##_FBIT__ + 1), __##M##_FBIT__)

#define FX_UNSIGNED(m, M, base, U, N, L) \
    FX_TYPE(m, M, base, U, N, L, (__##M##_IBIT__ + __##M##_FBIT__)) \
    FX_UNSIGNED_ROUTINES(m, N, L, (__##M##_IBIT__ + __##M##_FBIT__), __##M##_FBIT__)

#if defined(__AVR__)

// AVR passes these types as it does integers of their sizes, and has compilers
// call only some of their routines, with registers of their own for some. So
// its types are those integers, and all that tells them apart is packed in a
// word that takes one register pair, for routines to share their cores: the
// width, which leaves the low bit for signed, the fractional bits above that,
// and the top bit for saturating.
#define FX_PACK(W, F, is_signed, saturating) \
    ((uint16_t)((W) + (uint16_t)(is_signed) + ((uint16_t)(F) << 8) \
              + ((uint16_t)(saturating) << 15)))
#define FX_PACKED_W(p) ((unsigned int)(p) & 0xfe)
#define FX_PACKED_F(p) (((unsigned int)(p) >> 8) & 0x7f)
#define FX_PACKED_SIGNED(p) (((p) & 1) != 0)
#define FX_PACKED_SATURATING(p) (((p) >> 15) != 0)

#define FX_SHARED __attribute__((__noinline__, __unused__)) static

// Types of W bits, in the word of N bits, share these.
#define FX_SHARED_CORE(W, N, L) \
    FX_SHARED L fx_shared_mul##W(L a, L b, uint16_t p) { \
        return fx_mul##N(a, b, W, FX_PACKED_F(p), FX_PACKED_SIGNED(p), FX_PACKED_SATURATING(p)); \
    } \
    \
    FX_SHARED L fx_shared_div##W(L a, L b, uint16_t p) { \
        return fx_div##N(a, b, W, FX_PACKED_F(p), FX_PACKED_SIGNED(p), FX_PACKED_SATURATING(p)); \
    } \
    \
    FX_SHARED L fx_shared_ssashl##W(L a, uint8_t n) { \
        return fx_ssashl##N(a, n, W); \
    } \
    \
    FX_SHARED L fx_shared_usashl##W(L a, uint8_t n) { \
        return fx_usashl##N(a, n, W); \
    }

FX_SHARED_CORE(8, 16, uint16_t)
FX_SHARED_CORE(16, 16, uint16_t)
FX_SHARED_CORE(32, 32, uint32_t)
FX_SHARED_CORE(64, 64, uint64_t)

#define FX_TYPE_OF(m, U, L) \
    typedef U fx_##m; \
    \
    static inline L fx_bits_##m(U x) { \
        return x; \
    } \
    \
    static inline U fx_value_##m(L x) { \
        return (U)x; \
    }

// The product or quotient of two values, by the width W of their type.
#define FX_PACKED_BINARY(op, core, m, L, W, F, is_signed, saturating) \
    FX_BINARY(op, m, L, fx_shared_##core##W(x, y, FX_PACK(W, F, is_signed, saturating)))

#define FX_SIGNED_OF(m, M, U, W, L) \
    FX_TYPE_OF(m, U, L) \
    FX_PACKED_BINARY(ssmul, mul, m, L, W, __##M##_FBIT__, true, true) \
    FX_PACKED_BINARY(ssdiv, div, m, L, W, __##M##_FBIT__, true, true) \
    FX_SHIFT(ssashl, m, L, fx_shared_ssashl##W(x, (uint8_t)count))

#define FX_UNSIGNED_OF(m, M, U, W, L) \
    FX_TYPE_OF(m, U, L) \
    FX_PACKED_BINARY(usmul, mul, m, L, W, __##M##_FBIT__, false, true) \
    FX_PACKED_BINARY(usdiv, div, m, L, W, __##M##_FBIT__, false, true) \
    FX_SHIFT(usashl, m, L, fx_shared_usashl##W(x, (uint8_t)count))

FX_SIGNED_OF(qq, QQ, uint8_t, 8, uint16_t)
FX_SIGNED_OF(hq, HQ, uint16_t, 16, uint16_t)
FX_SIGNED_OF(sq, SQ, uint32_t, 32, uint32_t)
FX_SIGNED_OF(dq, DQ, uint64_t, 64, uint64_t)
FX_UNSIGNED_OF(uqq, UQQ, uint8_t, 8, uint16_t)
FX_UNSIGNED_OF(uhq, UHQ, uint16_t, 16, uint16_t)
FX_UNSIGNED_OF(usq, USQ, uint32_t, 32, uint32_t)
FX_UNSIGNED_OF(udq, UDQ, uint64_t, 64, uint64_t)
FX_SIGNED_OF(ha, HA, uint16_t, 16, uint16_t)
FX_SIGNED_OF(sa, SA, uint32_t, 32, uint32_t)
FX_SIGNED_OF(da, DA, uint64_t, 64, uint64_t)
FX_SIGNED_OF(ta, TA, uint64_t, 64, uint64_t)
FX_UNSIGNED_OF(uha, UHA, uint16_t, 16, uint16_t)
FX_UNSIGNED_OF(usa, USA, uint32_t, 32, uint32_t)
FX_UNSIGNED_OF(uda, UDA, uint64_t, 64, uint64_t)
FX_UNSIGNED_OF(uta, UTA, uint64_t, 64, uint64_t)

// The rest of the products and quotients that have the convention of C.
#define FX_PLAIN_MUL(m, M, W, L, is_signed) \
    FX_PACKED_BINARY(mul, mul, m, L, W, __##M##_FBIT__, is_signed, false)

#define FX_PLAIN_DIV(op, m, M, W, L, is_signed) \
    FX_PACKED_BINARY(op, div, m, L, W, __##M##_FBIT__, is_signed, false)

#define FX_PLAIN_MUL_DIV(op, m, M, W, L, is_signed) \
    FX_PLAIN_MUL(m, M, W, L, is_signed) \
    FX_PLAIN_DIV(op, m, M, W, L, is_signed)

FX_PLAIN_MUL_DIV(div, sq, SQ, 32, uint32_t, true)
FX_PLAIN_MUL_DIV(div, dq, DQ, 64, uint64_t, true)
FX_PLAIN_MUL_DIV(div, da, DA, 64, uint64_t, true)
FX_PLAIN_MUL_DIV(div, ta, TA, 64, uint64_t, true)
FX_PLAIN_MUL_DIV(udiv, usq, USQ, 32, uint32_t, false)
FX_PLAIN_MUL_DIV(udiv, udq, UDQ, 64, uint64_t, false)
FX_PLAIN_MUL_DIV(udiv, uda, UDA, 64, uint64_t, false)
FX_PLAIN_MUL_DIV(udiv, uta, UTA, 64, uint64_t, false)

#if !defined(__AVR_HAVE_MUL__)
FX_PLAIN_MUL(hq, HQ, 16, uint16_t, true)
FX_PLAIN_MUL(ha, HA, 16, uint16_t, true)
FX_PLAIN_MUL(sa, SA, 32, uint32_t, true)
FX_PLAIN_MUL(uhq, UHQ, 16, uint16_t, false)
FX_PLAIN_MUL(uha, UHA, 16, uint16_t, false)
FX_PLAIN_MUL(usa, USA, 32, uint32_t, false)
#endif

// What stdfix.h asks of the compiler. A count at or above the fractional bits
// leaves all of them, and a negative one that leaves no bit of value gives 0.
// Adding half of the last place left rounds to the nearest value, with ties
// up, and only overflows upwards, to the limit of the type, whose fractional
// bits stay. Otherwise the bits below that place go.
#define FX_ROUNDING(N, L) \
    FX_INLINE L fx_round##N(L x, int n, unsigned int w, unsigned int f, bool is_signed) { \
        unsigned int count = f - (unsigned int)n; \
        L half; \
        L r; \
        \
        if (n >= (int)f) { \
            return x; \
        } \
        if (n < 0 && count >= w - (unsigned int)is_signed) { \
            return 0; \
        } \
        half = (L)1 << (count - 1); \
        r = fx_add##N(x, half, w); \
        if (is_signed ? fx_sign##N(r & ~x, w) : r < x) { \
            return is_signed ? fx_limit##N(false, w) : fx_mask##N(w); \
        } \
        return r & ~(half + (half - 1)); \
    }

FX_ROUNDING(16, uint16_t)
FX_ROUNDING(32, uint32_t)
FX_ROUNDING(64, uint64_t)

#define FX_SHARED_ROUND(W, N, L) \
    FX_SHARED L fx_shared_round##W(L x, int n, uint16_t p) { \
        return fx_round##N(x, n, W, FX_PACKED_F(p), FX_PACKED_SIGNED(p)); \
    }

FX_SHARED_ROUND(8, 16, uint16_t)
FX_SHARED_ROUND(16, 16, uint16_t)
FX_SHARED_ROUND(32, 32, uint32_t)
FX_SHARED_ROUND(64, 64, uint64_t)

#define FX_ROUND_ROUTINE(m, M, is_signed) \
    fx_##m __round##m##3(fx_##m a, int n) { \
        return fx_shared_round64(a, n, FX_PACK(64, __##M##_FBIT__, is_signed, false)); \
    }

FX_ROUND_ROUTINE(dq, DQ, true)
FX_ROUND_ROUTINE(da, DA, true)
FX_ROUND_ROUTINE(ta, TA, true)
FX_ROUND_ROUTINE(udq, UDQ, false)
FX_ROUND_ROUTINE(uda, UDA, false)
FX_ROUND_ROUTINE(uta, UTA, false)

// Copies of the sign, past the first, count what a value can shift left by,
// and leading zeros in an unsigned value. Zero has all its bits of value.
#define FX_COUNTING(W, N, L) \
    FX_SHARED int fx_shared_countls##W(L x, bool is_signed) { \
        unsigned int n = (W); \
        \
        if (is_signed && fx_sign##N(x, W)) { \
            x = ~x & fx_mask##N(W); \
        } \
        if (x != 0) { \
            n -= fx_top##N(x) + 1; \
        } \
        return (int)(n - (unsigned int)is_signed); \
    }

FX_COUNTING(8, 16, uint16_t)
FX_COUNTING(16, 16, uint16_t)
FX_COUNTING(32, 32, uint32_t)
FX_COUNTING(64, 64, uint64_t)

#define FX_COUNT_ROUTINES(mode, U, W) \
    int __countls##mode##2(U x) { \
        return fx_shared_countls##W(x, true); \
    } \
    \
    int __countlsu##mode##2(U x) { \
        return fx_shared_countls##W(x, false); \
    }

FX_COUNT_ROUTINES(qi, uint8_t, 8)
FX_COUNT_ROUTINES(hi, uint16_t, 16)
FX_COUNT_ROUTINES(si, uint32_t, 32)
FX_COUNT_ROUTINES(di, uint64_t, 64)

// Values of 8 bytes, whose operations are alike in all their types.
#define FX_8_BYTES_SIGNED(m) \
    FX_UNARY(ssneg, m, uint64_t, fx_ssneg64(x, 64)) \
    fx_##m __ssabs##m##2(fx_##m a) { \
        return fx_sign64(a, 64) ? fx_ssneg64(a, 64) : a; \
    }

#define FX_8_BYTES_UNSIGNED(m) FX_UNARY(usneg, m, uint64_t, fx_usneg64(x))

FX_8_BYTES_SIGNED(dq)
FX_8_BYTES_SIGNED(da)
FX_8_BYTES_SIGNED(ta)
FX_8_BYTES_UNSIGNED(udq)
FX_8_BYTES_UNSIGNED(uda)
FX_8_BYTES_UNSIGNED(uta)

// Reduced cores pass these in memory, and have calls with the convention of C
// for what the others have inline, or in registers of its own.
#if defined(__AVR_TINY__)

#define FX_8_BYTES_COMMON(m) \
    FX_BINARY(add, m, uint64_t, fx_add64(x, y, 64)) \
    FX_BINARY(sub, m, uint64_t, fx_sub64(x, y, 64)) \
    FX_UNARY(neg, m, uint64_t, fx_neg64(x, 64)) \
    FX_SHIFT(ashl, m, uint64_t, fx_ashl64(x, count, 64))

#define FX_TINY_SIGNED(m) \
    FX_8_BYTES_COMMON(m) \
    FX_COMPARE(m, 64, uint64_t, 64, true) \
    FX_BINARY(ssadd, m, uint64_t, fx_ssadd64(x, y, 64)) \
    FX_BINARY(sssub, m, uint64_t, fx_sssub64(x, y, 64)) \
    FX_SHIFT(ashr, m, uint64_t, fx_ashr64(x, count, 64))

#define FX_TINY_UNSIGNED(m) \
    FX_8_BYTES_COMMON(m) \
    FX_COMPARE(m, 64, uint64_t, 64, false) \
    FX_BINARY(usadd, m, uint64_t, fx_usadd64(x, y, 64)) \
    FX_BINARY(ussub, m, uint64_t, fx_ussub64(x, y)) \
    FX_SHIFT(lshr, m, uint64_t, fx_lshr64(x, count, 64))

FX_TINY_SIGNED(dq)
FX_TINY_SIGNED(da)
FX_TINY_SIGNED(ta)
FX_TINY_UNSIGNED(udq)
FX_TINY_UNSIGNED(uda)
FX_TINY_UNSIGNED(uta)

#endif // defined(__AVR_TINY__)

#else // defined(__AVR__)

FX_SIGNED(qq, QQ, fract, uint8_t, 32, uint32_t)
FX_SIGNED(hq, HQ, fract, uint16_t, 32, uint32_t)
FX_SIGNED(sq, SQ, fract, uint32_t, 32, uint32_t)
FX_SIGNED(dq, DQ, fract, uint64_t, 64, uint64_t)
FX_UNSIGNED(uqq, UQQ, ufract, uint8_t, 32, uint32_t)
FX_UNSIGNED(uhq, UHQ, ufract, uint16_t, 32, uint32_t)
FX_UNSIGNED(usq, USQ, ufract, uint32_t, 32, uint32_t)
FX_UNSIGNED(udq, UDQ, ufract, uint64_t, 64, uint64_t)
FX_SIGNED(ha, HA, accum, uint16_t, 32, uint32_t)
FX_SIGNED(sa, SA, accum, uint32_t, 32, uint32_t)
FX_SIGNED(da, DA, accum, uint64_t, 64, uint64_t)
FX_UNSIGNED(uha, UHA, uaccum, uint16_t, 32, uint32_t)
FX_UNSIGNED(usa, USA, uaccum, uint32_t, 32, uint32_t)
FX_UNSIGNED(uda, UDA, uaccum, uint64_t, 64, uint64_t)
#if HAS_INT128
FX_SIGNED(tq, TQ, fract, u128, 128, u128)
FX_SIGNED(ta, TA, accum, u128, 128, u128)
FX_UNSIGNED(utq, UTQ, ufract, u128, 128, u128)
FX_UNSIGNED(uta, UTA, uaccum, u128, 128, u128)
#endif

#endif // defined(__AVR__)

// A conversion works on the magnitude of the operand, of width ws with fs
// fractional bits, in a word that holds both types. Only integers have no
// fractional bits, and those round towards zero, as TR 18037 requires. The
// rest round down, so that a negative magnitude rounds up. The bits of a limit
// are also its magnitude, and shifted right they are the most a magnitude can
// be before the shift left. Without saturation, the result wraps.
#define FX_CONVERSION(N, L) \
    static inline L fx_right##N(L x, unsigned int count) { \
        return count >= (N) ? 0 : x >> count; \
    } \
    \
    FX_INLINE L fx_convert##N( \
        L x, unsigned int ws, unsigned int fs, bool from_signed, unsigned int wd, \
        unsigned int fd, bool to_signed, bool saturating \
    ) { \
        L bits = x & fx_mask##N(ws); \
        L mask = fx_mask##N(wd); \
        bool negative = from_signed && fx_sign##N(bits, ws); \
        L magnitude = negative ? fx_neg##N(bits, ws) : bits; \
        L limit = negative ? 0 : mask; \
        unsigned int right = fs > fd ? fs - fd : 0; \
        unsigned int left = fd > fs ? fd - fs : 0; \
        \
        if (to_signed) { \
            limit = fx_limit##N(negative, wd); \
        } \
        if (negative && fd != 0) { \
            magnitude = fx_right##N(magnitude - 1, right) + 1; \
        } else { \
            magnitude = fx_right##N(magnitude, right); \
        } \
        if (saturating && magnitude > fx_right##N(limit, left)) { \
            return limit; \
        } \
        magnitude = left >= (N) ? 0 : magnitude << left; \
        return (negative ? (L)0 - magnitude : magnitude) & mask; \
    }

#if defined(__AVR__)
FX_CONVERSION(16, uint16_t)
#endif
FX_CONVERSION(32, uint32_t)
FX_CONVERSION(64, uint64_t)
#if HAS_INT128
FX_CONVERSION(128, u128)
#endif

#define FX_WIDER_16_16 16
#define FX_WIDER_16_32 32
#define FX_WIDER_16_64 64
#define FX_WIDER_32_16 32
#define FX_WIDER_64_16 64
#define FX_WIDER_32_32 32
#define FX_WIDER_32_64 64
#define FX_WIDER_32_128 128
#define FX_WIDER_64_32 64
#define FX_WIDER_64_64 64
#define FX_WIDER_64_128 128
#define FX_WIDER_128_32 128
#define FX_WIDER_128_64 128
#define FX_WIDER_128_128 128

// Between types of the same class, the names end in a 2.
#define FX_SUFFIX_fract_fract 2
#define FX_SUFFIX_fract_accum
#define FX_SUFFIX_fract_ufract
#define FX_SUFFIX_fract_uaccum
#define FX_SUFFIX_accum_fract
#define FX_SUFFIX_accum_accum 2
#define FX_SUFFIX_accum_ufract
#define FX_SUFFIX_accum_uaccum
#define FX_SUFFIX_ufract_fract
#define FX_SUFFIX_ufract_accum
#define FX_SUFFIX_ufract_ufract 2
#define FX_SUFFIX_ufract_uaccum
#define FX_SUFFIX_uaccum_fract
#define FX_SUFFIX_uaccum_accum
#define FX_SUFFIX_uaccum_ufract
#define FX_SUFFIX_uaccum_uaccum 2

#define FX_PASTE4(a, b, c, d) a##b##c##d
#define FX_NAME_OF(name) FX_NAME(name)
#if defined(__AVR__)

#define FX_SHARED_CONVERT(N, L) \
    FX_SHARED L fx_shared_convert##N(L x, uint16_t a, uint16_t b) { \
        return fx_convert##N( \
            x, FX_PACKED_W(a), FX_PACKED_F(a), FX_PACKED_SIGNED(a), FX_PACKED_W(b), \
            FX_PACKED_F(b), FX_PACKED_SIGNED(b), FX_PACKED_SATURATING(b) \
        ); \
    }

FX_SHARED_CONVERT(16, uint16_t)
FX_SHARED_CONVERT(32, uint32_t)
FX_SHARED_CONVERT(64, uint64_t)

#define FX_PACKED_CONVERT_16(x, wa, fa, sa, wb, fb, sb, saturating) \
    fx_shared_convert16(x, FX_PACK(wa, fa, sa, false), FX_PACK(wb, fb, sb, saturating))
#define FX_PACKED_CONVERT_32(x, wa, fa, sa, wb, fb, sb, saturating) \
    fx_shared_convert32(x, FX_PACK(wa, fa, sa, false), FX_PACK(wb, fb, sb, saturating))
#define FX_PACKED_CONVERT_64(x, wa, fa, sa, wb, fb, sb, saturating) \
    fx_shared_convert64(x, FX_PACK(wa, fa, sa, false), FX_PACK(wb, fb, sb, saturating))
#define FX_CONVERT_AT_EXPANDED(N) FX_PACKED_CONVERT_##N

#else // defined(__AVR__)
#define FX_CONVERT_AT_EXPANDED(N) fx_convert##N
#endif // defined(__AVR__)
#define FX_CONVERT_AT(N) FX_CONVERT_AT_EXPANDED(N)

#define FX_FIXED_ROUTINE(name, a, wa, fa, sa, b, wb, fb, sb, N, saturating) \
    fx_##b FX_NAME_OF(name)(fx_##a x) { \
        return fx_value_##b( \
            FX_CONVERT_AT(N)(fx_bits_##a(x), wa, fa, sa, wb, fb, sb, saturating) \
        ); \
    }

// AVR's compilers have these inline, but for the saturating forms.
#if defined(__AVR__)
#   define FX_FIXED_ROUTINES(a, wa, fa, sa, b, wb, fb, sb, N, suffix) \
        FX_FIXED_ROUTINE(FX_PASTE4(satfract, a, b, suffix), a, wa, fa, sa, b, wb, fb, sb, N, true)
#else
#   define FX_FIXED_ROUTINES(a, wa, fa, sa, b, wb, fb, sb, N, suffix) \
        FX_FIXED_ROUTINE(FX_PASTE4(fract, a, b, suffix), a, wa, fa, sa, b, wb, fb, sb, N, false) \
        FX_FIXED_ROUTINE(FX_PASTE4(satfract, a, b, suffix), a, wa, fa, sa, b, wb, fb, sb, N, true)
#endif

#define FX_FIXED_PAIR(a, na, ca, wa, fa, sa, b, nb, cb, wb, fb, sb) \
    FX_FIXED_ROUTINES(a, wa, fa, sa, b, wb, fb, sb, FX_WIDER_##na##_##nb, FX_SUFFIX_##ca##_##cb)

// Callers extend an integer narrower than a register to all of it, and a
// 32-bit unsigned one with zeros even where code for that type would expect a
// sign: so these take the register as it comes, and read its low bits. Results
// have their own types, which callers extend as they need.
#define FX_FROM_INTEGER(name, R, wi, is_signed, m, wm, fm, sm, N, saturating) \
    fx_##m FX_NAME_OF(name)(R x) { \
        return fx_value_##m(FX_CONVERT_AT(N)(x, wi, 0, is_signed, wm, fm, sm, saturating)); \
    }

#define FX_TO_INTEGER(name, I, m, wm, fm, sm, wi, N) \
    I FX_NAME_OF(name)(fx_##m x) { \
        return (I)FX_CONVERT_AT(N)(fx_bits_##m(x), wm, fm, sm, wi, 0, false, false); \
    }

#if defined(__AVR__)
#   define FX_INTEGER_ROUTINES(m, wm, fm, sm, i, wi, R, I, U, N) \
        FX_FROM_INTEGER(satfract##i##m, R, wi, true, m, wm, fm, sm, N, true) \
        FX_FROM_INTEGER(satfractuns##i##m, R, wi, false, m, wm, fm, sm, N, true)
#else
#   define FX_INTEGER_ROUTINES(m, wm, fm, sm, i, wi, R, I, U, N) \
        FX_FROM_INTEGER(fract##i##m, R, wi, true, m, wm, fm, sm, N, false) \
        FX_FROM_INTEGER(fractuns##i##m, R, wi, false, m, wm, fm, sm, N, false) \
        FX_FROM_INTEGER(satfract##i##m, R, wi, true, m, wm, fm, sm, N, true) \
        FX_FROM_INTEGER(satfractuns##i##m, R, wi, false, m, wm, fm, sm, N, true) \
        FX_TO_INTEGER(fract##m##i, I, m, wm, fm, sm, wi, N) \
        FX_TO_INTEGER(fractuns##m##i, U, m, wm, fm, sm, wi, N)
#endif

#define FX_INTEGER_PAIR(m, nm, cm, wm, fm, sm, i, ni, wi, R, I, U) \
    FX_INTEGER_ROUTINES(m, wm, fm, sm, i, wi, R, I, U, FX_WIDER_##ni##_##nm)

// Word, class, width, fractional bits, and signedness.
#define FX_SIGNED_INFO(M) (__##M##_IBIT__ + __##M##_FBIT__ + 1), __##M##_FBIT__, true
#define FX_UNSIGNED_INFO(M) (__##M##_IBIT__ + __##M##_FBIT__), __##M##_FBIT__, false

// The types of AVR that are not 32 bits wide take smaller or other words.
#if defined(__AVR__)
#   define FX_WORD_OF_8 16
#   define FX_WORD_OF_16 16
#   define FX_WORD_OF_TA 64
#else
#   define FX_WORD_OF_8 32
#   define FX_WORD_OF_16 32
#   define FX_WORD_OF_TA 128
#endif

#define FX_INFO_qq FX_WORD_OF_8, fract, FX_SIGNED_INFO(QQ)
#define FX_INFO_hq FX_WORD_OF_16, fract, FX_SIGNED_INFO(HQ)
#define FX_INFO_sq 32, fract, FX_SIGNED_INFO(SQ)
#define FX_INFO_dq 64, fract, FX_SIGNED_INFO(DQ)
#define FX_INFO_tq 128, fract, FX_SIGNED_INFO(TQ)
#define FX_INFO_ha FX_WORD_OF_16, accum, FX_SIGNED_INFO(HA)
#define FX_INFO_sa 32, accum, FX_SIGNED_INFO(SA)
#define FX_INFO_da 64, accum, FX_SIGNED_INFO(DA)
#define FX_INFO_ta FX_WORD_OF_TA, accum, FX_SIGNED_INFO(TA)
#define FX_INFO_uqq FX_WORD_OF_8, ufract, FX_UNSIGNED_INFO(UQQ)
#define FX_INFO_uhq FX_WORD_OF_16, ufract, FX_UNSIGNED_INFO(UHQ)
#define FX_INFO_usq 32, ufract, FX_UNSIGNED_INFO(USQ)
#define FX_INFO_udq 64, ufract, FX_UNSIGNED_INFO(UDQ)
#define FX_INFO_utq 128, ufract, FX_UNSIGNED_INFO(UTQ)
#define FX_INFO_uha FX_WORD_OF_16, uaccum, FX_UNSIGNED_INFO(UHA)
#define FX_INFO_usa 32, uaccum, FX_UNSIGNED_INFO(USA)
#define FX_INFO_uda 64, uaccum, FX_UNSIGNED_INFO(UDA)
#define FX_INFO_uta FX_WORD_OF_TA, uaccum, FX_UNSIGNED_INFO(UTA)

// Word, width, the type of an operand, and of a signed or unsigned result.
typedef unsigned int fx_register __attribute__((__mode__(__word__)));

#if defined(__AVR__)
#   define FX_INFO_qi 16, 8, uint8_t, int8_t, uint8_t
#   define FX_INFO_hi 16, 16, uint16_t, int16_t, uint16_t
#   define FX_INFO_si 32, 32, uint32_t, int32_t, uint32_t
#else
#   define FX_INFO_qi 32, 8, fx_register, int8_t, uint8_t
#   define FX_INFO_hi 32, 16, fx_register, int16_t, uint16_t
#   define FX_INFO_si 32, 32, fx_register, int32_t, uint32_t
#endif
#define FX_INFO_di 64, 64, uint64_t, int64_t, uint64_t
#define FX_INFO_ti 128, 128, u128, i128, u128

#define FX_PAIR_EXPANDED(X, ...) X(__VA_ARGS__)
#define FX_PAIR(X, a, b) FX_PAIR_EXPANDED(X, a, FX_INFO_##a, b, FX_INFO_##b)

#define FX_BOTH_WAYS(a, b) \
    FX_PAIR(FX_FIXED_PAIR, a, b) \
    FX_PAIR(FX_FIXED_PAIR, b, a)

// Each type with the types after it, so that no type goes with itself.
#define FX_AFTER_qq(m) FX_BOTH_WAYS(m, hq) FX_AFTER_hq(m)
#define FX_AFTER_hq(m) FX_BOTH_WAYS(m, sq) FX_AFTER_sq(m)
#define FX_AFTER_sq(m) FX_BOTH_WAYS(m, dq) FX_AFTER_dq(m)
#define FX_AFTER_dq(m) FX_BOTH_WAYS(m, uqq) FX_AFTER_uqq(m)
#define FX_AFTER_uqq(m) FX_BOTH_WAYS(m, uhq) FX_AFTER_uhq(m)
#define FX_AFTER_uhq(m) FX_BOTH_WAYS(m, usq) FX_AFTER_usq(m)
#define FX_AFTER_usq(m) FX_BOTH_WAYS(m, udq) FX_AFTER_udq(m)
#define FX_AFTER_udq(m) FX_BOTH_WAYS(m, ha) FX_AFTER_ha(m)
#define FX_AFTER_ha(m) FX_BOTH_WAYS(m, sa) FX_AFTER_sa(m)
#define FX_AFTER_sa(m) FX_BOTH_WAYS(m, da) FX_AFTER_da(m)
#define FX_AFTER_da(m) FX_BOTH_WAYS(m, uha) FX_AFTER_uha(m)
#define FX_AFTER_uha(m) FX_BOTH_WAYS(m, usa) FX_AFTER_usa(m)
#define FX_AFTER_usa(m) FX_BOTH_WAYS(m, uda) FX_AFTER_uda(m)
#if HAS_INT128
#   define FX_AFTER_uda(m) FX_BOTH_WAYS(m, tq) FX_AFTER_tq(m)
#   define FX_AFTER_tq(m) FX_BOTH_WAYS(m, ta) FX_AFTER_ta(m)
#   define FX_AFTER_ta(m) FX_BOTH_WAYS(m, utq) FX_AFTER_utq(m)
#   define FX_AFTER_utq(m) FX_BOTH_WAYS(m, uta)
#   define FX_AFTER_uta(m)
#elif defined(__AVR__)
#   define FX_AFTER_uda(m) FX_BOTH_WAYS(m, ta) FX_AFTER_ta(m)
#   define FX_AFTER_ta(m) FX_BOTH_WAYS(m, uta)
#   define FX_AFTER_uta(m)
#else
#   define FX_AFTER_uda(m)
#endif

#if HAS_INT128
#   define FX_WITH_128_BITS(m) FX_PAIR(FX_INTEGER_PAIR, m, ti)
#else
#   define FX_WITH_128_BITS(m)
#endif

#if LGRT_SOFT_FLOAT

// MIPS16 code has no access to the registers of hard-float values.
#if defined(__mips16) && defined(__mips_hard_float)
#   define FX_FP_ABI __attribute__((__nomips16__))
#else
#   define FX_FP_ABI
#endif

// The routines of a type differ in a few constants, so that they share what
// follows, for size, on AVR through wrappers of its own. To a format with F
// fractional bits, a magnitude becomes a significand as the soft-float core
// has them, its lost bits in the sticky bit, so that it rounds once, subnormal
// results too.
#if defined(__AVR__)
#   define FX_FP_SHARED FX_INLINE
#else
#   define FX_FP_SHARED __attribute__((__noinline__)) static
#endif

#define FX_TO_FP(N, L, fmt, T, E, F) \
    FX_FP_SHARED T fx_to_##fmt##N(L x, unsigned int w, unsigned int f, bool is_signed) { \
        bool negative = is_signed && fx_sign##N(x, w); \
        L magnitude = negative ? fx_neg##N(x, w) : x; \
        unsigned int top; \
        T sig; \
        \
        if (magnitude == 0) { \
            return 0; \
        } \
        top = FX_TOP(N, magnitude); \
        if (top <= (F) + 3) { \
            sig = (T)magnitude << ((F) + 3 - top); \
        } else { \
            unsigned int lost = top - ((F) + 3); \
            L kept = magnitude >> lost; \
            \
            sig = (T)kept | (T)((kept << lost) != magnitude); \
        } \
        return fmt##_round_pack(negative ? FP_SIGN(T, E, F) : 0, FP_BIAS(E) + top - f, sig); \
    }

// From a format, in a word that holds both, the significand counts in units of
// the last place of the result at the biased exponent called point here. Above
// that it shifts left, and bits past the word are past the result too; below
// that it shifts right, which truncates its magnitude. The bits of a limit are
// also its magnitude, and that of a negative value in an unsigned type is 0.
// Without saturation, the result wraps. A NaN gives 0, and an infinity the
// limit of the type, with or without saturation.
#define FX_FROM_FP(N, L, fmt, T, E, F) \
    FX_FP_SHARED L fx_from_##fmt##N( \
        T x, unsigned int w, unsigned int f, bool to_signed, bool saturating \
    ) { \
        T magnitude = x & (FP_SIGN(T, E, F) - 1); \
        T sig = magnitude & (FP_INT_BIT(T, F) - 1); \
        unsigned int e = (unsigned int)(magnitude >> (F)); \
        unsigned int point = FP_BIAS(E) + (F) - f; \
        bool negative = (x & FP_SIGN(T, E, F)) != 0; \
        L mask = fx_mask##N(w); \
        L limit = negative ? 0 : mask; \
        L value; \
        \
        if (to_signed) { \
            limit = fx_limit##N(negative, w); \
        } \
        if (magnitude >= FP_INF(T, E, F)) { \
            return magnitude == FP_INF(T, E, F) ? limit : 0; \
        } \
        if (e != 0) { \
            sig |= FP_INT_BIT(T, F); \
        } else { \
            e = 1; \
        } \
        if (e < point) { \
            value = fx_right##N((L)sig, point - e); \
            if (saturating && value > limit) { \
                return limit; \
            } \
        } else { \
            if (saturating && (L)sig > fx_right##N(limit, e - point)) { \
                return limit; \
            } \
            value = e - point >= (N) ? 0 : (L)sig << (e - point); \
        } \
        return (negative ? (L)0 - value : value) & mask; \
    }

#define FX_FP_CORE(N, L, fmt, T, E, F) \
    FX_TO_FP(N, L, fmt, T, E, F) \
    FX_FROM_FP(N, L, fmt, T, E, F)

#if defined(__AVR__)
FX_TO_FP(16, uint16_t, sf, uint32_t, 8, 23)
#endif
FX_FP_CORE(32, uint32_t, sf, uint32_t, 8, 23)
FX_FP_CORE(64, uint64_t, sf, uint32_t, 8, 23)
#if HAS_INT128
FX_FP_CORE(128, u128, sf, uint32_t, 8, 23)
#endif

#if SOFT_DOUBLE
#if defined(__AVR__)
FX_TO_FP(16, uint16_t, df, uint64_t, 11, 52)
#endif
FX_TO_FP(32, uint32_t, df, uint64_t, 11, 52)
FX_FP_CORE(64, uint64_t, df, uint64_t, 11, 52)
#if HAS_INT128
FX_FP_CORE(128, u128, df, uint64_t, 11, 52)
#endif
#endif

#define FX_FROM_FP_AT_EXPANDED(fmt, N) fx_from_##fmt##N
#define FX_FROM_FP_AT(fmt, N) FX_FROM_FP_AT_EXPANDED(fmt, N)

#if defined(__AVR__)

#define FX_SHARED_TO_FP(N, L, fmt, T) \
    FX_SHARED T fx_shared_to_##fmt##N(L x, uint16_t p) { \
        return fx_to_##fmt##N(x, FX_PACKED_W(p), FX_PACKED_F(p), FX_PACKED_SIGNED(p)); \
    }

#define FX_SHARED_FROM_FP(N, L, fmt, T) \
    FX_SHARED L fx_shared_from_##fmt##N(T x, uint16_t p) { \
        return fx_from_##fmt##N( \
            x, FX_PACKED_W(p), FX_PACKED_F(p), FX_PACKED_SIGNED(p), FX_PACKED_SATURATING(p) \
        ); \
    }

FX_SHARED_TO_FP(16, uint16_t, sf, uint32_t)
FX_SHARED_TO_FP(32, uint32_t, sf, uint32_t)
FX_SHARED_TO_FP(64, uint64_t, sf, uint32_t)
FX_SHARED_FROM_FP(32, uint32_t, sf, uint32_t)
FX_SHARED_FROM_FP(64, uint64_t, sf, uint32_t)

#if SOFT_DOUBLE
FX_SHARED_TO_FP(16, uint16_t, df, uint64_t)
FX_SHARED_TO_FP(32, uint32_t, df, uint64_t)
FX_SHARED_TO_FP(64, uint64_t, df, uint64_t)
FX_SHARED_FROM_FP(64, uint64_t, df, uint64_t)
#endif

#define FX_SHARED_FROM_FP_AT_EXPANDED(fmt, N) fx_shared_from_##fmt##N
#define FX_SHARED_FROM_FP_AT(fmt, N) FX_SHARED_FROM_FP_AT_EXPANDED(fmt, N)

#endif // defined(__AVR__)

// Compilers call these with floating-point values where the procedure call
// standard has them, and where that is in floating-point registers, C has
// their bits in core registers and assembly moves them, as for _BitInt. A
// 64-bit value in two core registers has its high half first if big-endian.
#if defined(__ARM_PCS_VFP)

#   define FX_VFP_TO_CORE_sf "vmov r0, s0\n\t"
#   define FX_VFP_FROM_CORE_sf "vmov s0, r0\n\t"
#   if defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#       define FX_VFP_TO_CORE_df "vmov r1, r0, d0\n\t"
#       define FX_VFP_FROM_CORE_df "vmov d0, r1, r0\n\t"
#   else
#       define FX_VFP_TO_CORE_df "vmov r0, r1, d0\n\t"
#       define FX_VFP_FROM_CORE_df "vmov d0, r0, r1\n\t"
#   endif

#   define FX_TO_FP_ROUTINE(m, nm, wm, fm, sm, fmt, C, T) \
        CX_VFP_HELPER T fx_fract##m##fmt##_bits(fx_##m x) { \
            return fx_to_##fmt##nm(fx_bits_##m(x), wm, fm, sm); \
        } \
        \
        CX_VFP_ENTRY( \
            fx_fract##m##fmt, "__gnu_fract" #m #fmt, "8", "", "fx_fract" #m #fmt "_bits", \
            FX_VFP_FROM_CORE_##fmt \
        )

#   define FX_FROM_FP_ROUTINE(op, m, wm, fm, sm, fmt, C, T, N, saturating) \
        CX_VFP_HELPER fx_##m fx_##op##fmt##m##_bits(T a) { \
            return fx_value_##m(FX_FROM_FP_AT(fmt, N)(a, wm, fm, sm, saturating)); \
        } \
        \
        BITINT_VFP_MOVE( \
            fx_##op##fmt##m, "__gnu_" #op #fmt #m, FX_VFP_TO_CORE_##fmt, \
            "fx_" #op #fmt #m "_bits" \
        )

#elif defined(__AVR__)

#   define FX_TO_FP_ROUTINE(m, nm, wm, fm, sm, fmt, C, T) \
        C FX_NAME(fract##m##fmt)(fx_##m x) { \
            return fx_shared_to_##fmt##nm(fx_bits_##m(x), FX_PACK(wm, fm, sm, false)); \
        }

// Without saturation, a signed type of up to 16 bits is the top of a result of
// 32 bits, which rounds down from there, what that truncates being finer.
#   define FX_BELOW_TOP(W) ((W) <= 16 ? 32 - (W) : 0)

#   define FX_FROM_FP_ROUTINE(op, m, wm, fm, sm, fmt, C, T, N, saturating) \
        fx_##m FX_NAME(op##fmt##m)(C a) { \
            if ((sm) && !(saturating) && (wm) <= 16) { \
                uint32_t top = (uint32_t)FX_SHARED_FROM_FP_AT(fmt, N)( \
                    a, FX_PACK(32, (fm) + FX_BELOW_TOP(wm), true, false) \
                ); \
                \
                return fx_value_##m(top >> FX_BELOW_TOP(wm)); \
            } \
            return fx_value_##m( \
                FX_SHARED_FROM_FP_AT(fmt, N)(a, FX_PACK(wm, fm, sm, saturating)) \
            ); \
        }

#else // defined(__ARM_PCS_VFP)

#   define FX_TO_FP_ROUTINE(m, nm, wm, fm, sm, fmt, C, T) \
        FX_FP_ABI C FX_NAME(fract##m##fmt)(fx_##m x) { \
            return fmt##_from_bits(fx_to_##fmt##nm(fx_bits_##m(x), wm, fm, sm)); \
        }

#   define FX_FROM_FP_ROUTINE(op, m, wm, fm, sm, fmt, C, T, N, saturating) \
        FX_FP_ABI fx_##m FX_NAME(op##fmt##m)(C a) { \
            return fx_value_##m(FX_FROM_FP_AT(fmt, N)(fmt##_to_bits(a), wm, fm, sm, saturating)); \
        }

#endif // defined(__ARM_PCS_VFP)

#define FX_FP_PAIR(m, nm, cm, wm, fm, sm, fmt, nf, C, T) \
    FX_TO_FP_ROUTINE(m, nm, wm, fm, sm, fmt, C, T) \
    FX_FROM_FP_ROUTINE(fract, m, wm, fm, sm, fmt, C, T, FX_WIDER_##nm##_##nf, false) \
    FX_FROM_FP_ROUTINE(satfract, m, wm, fm, sm, fmt, C, T, FX_WIDER_##nm##_##nf, true)

// Word, the type that passes a value, and the type of its bits.
#define FX_INFO_sf 32, sf_value, uint32_t
#define FX_INFO_df 64, df_value, uint64_t

#endif // LGRT_SOFT_FLOAT

#if SOFT_DOUBLE
#   define FX_WITH_FP(m) \
        FX_PAIR(FX_FP_PAIR, m, sf) \
        FX_PAIR(FX_FP_PAIR, m, df)
#elif LGRT_SOFT_FLOAT
#   define FX_WITH_FP(m) FX_PAIR(FX_FP_PAIR, m, sf)
#else
#   define FX_WITH_FP(m)
#endif

#define FX_CONVERSIONS(m) \
    FX_AFTER_##m(m) \
    FX_PAIR(FX_INTEGER_PAIR, m, qi) \
    FX_PAIR(FX_INTEGER_PAIR, m, hi) \
    FX_PAIR(FX_INTEGER_PAIR, m, si) \
    FX_PAIR(FX_INTEGER_PAIR, m, di) \
    FX_WITH_128_BITS(m) \
    FX_WITH_FP(m)

FX_CONVERSIONS(qq)
FX_CONVERSIONS(hq)
FX_CONVERSIONS(sq)
FX_CONVERSIONS(dq)
FX_CONVERSIONS(uqq)
FX_CONVERSIONS(uhq)
FX_CONVERSIONS(usq)
FX_CONVERSIONS(udq)
FX_CONVERSIONS(ha)
FX_CONVERSIONS(sa)
FX_CONVERSIONS(da)
FX_CONVERSIONS(uha)
FX_CONVERSIONS(usa)
FX_CONVERSIONS(uda)
#if HAS_INT128
FX_CONVERSIONS(tq)
FX_CONVERSIONS(ta)
FX_CONVERSIONS(utq)
FX_CONVERSIONS(uta)
#elif defined(__AVR__)
FX_CONVERSIONS(ta)
FX_CONVERSIONS(uta)
#endif

#if defined(__mips64) && __GNUC__ == 15
#   pragma GCC pop_options
#endif

#endif // !defined(__clang__) && defined(__QQ_FBIT__)

// Decimal floating point, which only GCC has. It stores significands as binary
// integers on x86 and AArch64, telling of it with __DECIMAL_BID_FORMAT__, and
// as densely packed decimal on PowerPC and s390. Before GCC 10, it defines
// __DEC32_MANT_DIG__ on all targets, whether they have these types or not.
// These values travel in the registers of float, so their routines go by the
// same condition. They round to nearest, with ties to even, and raise nothing.
#if defined(__DECIMAL_BID_FORMAT__)
#   define DEC_NAME(name) __bid_##name
#elif defined(__DEC32_MANT_DIG__) && (__GNUC__ >= 10 || defined(__powerpc__) || defined(__s390__))
#   define DEC_NAME(name) __dpd_##name
#endif

#if defined(DEC_NAME) && LGRT_SOFT_FLOAT

// In strict modes, GCC before 10 has no keywords for these.
typedef float sd_value __attribute__((__mode__(__SD__)));
typedef float dd_value __attribute__((__mode__(__DD__)));
typedef float td_value __attribute__((__mode__(__TD__)));

// All arithmetic stays within 32 bits with limbs of 4 digits.
#define DEC_BASE ((uint32_t)10000)
#define DEC_LIMBS 9
#define DEC_WIDE_LIMBS 18

#define DEC_FINITE 0
#define DEC_INFINITE 1
#define DEC_QUIET 2
#define DEC_SIGNALLING 3

// A finite number is (-1)^negative * coefficient * 10^exponent, with the limbs
// of the coefficient little end first. A NaN's coefficient is its payload.
struct dec {
    int kind;
    int32_t exponent;
    uint32_t coefficient[DEC_LIMBS];
    bool negative;
};

// A format is known by how many words of 32 bits it has: 1, 2, or 4.
static size_t dec_precision(size_t words) {
    return 9 * words - 2;
}

static size_t dec_limbs(size_t words) {
    return (dec_precision(words) + 3) >> 2;
}

// Limbs that hold all that an operation works on before it rounds: twice the
// precision and 2 digits, with 1 digit more for a carry.
static size_t dec_wide_limbs(size_t words) {
    return (2 * dec_precision(words) + 6) >> 2;
}

// The bits of the exponent continuation.
static size_t dec_continuation(size_t words) {
    return words == 4 ? 12 : 4 + 2 * words;
}

// The bias, which is also minus the lowest exponent.
static int32_t dec_bias(size_t words) {
    int32_t emax = (int32_t)3 << (dec_continuation(words) - 1);

    return emax + (int32_t)dec_precision(words) - 2;
}

static int32_t dec_highest_exponent(size_t words) {
    int32_t limit = (int32_t)3 << dec_continuation(words);

    return limit - 1 - dec_bias(words);
}

static uint32_t dec_power(size_t count) {
    return count == 0 ? 1 : count == 1 ? 10 : count == 2 ? 100 : 1000;
}

static size_t dec_digits(const uint32_t *c, size_t n) {
    for (size_t i = n; i-- > 0; ) {
        if (c[i] != 0) {
            return 4 * i + (c[i] >= 1000 ? 4 : c[i] >= 100 ? 3 : c[i] >= 10 ? 2 : 1);
        }
    }
    return 0;
}

// Multiplies by 10^count a number that stays within n limbs.
static void dec_scale_up(uint32_t *c, size_t n, size_t count) {
    size_t whole = count >> 2;
    uint32_t factor = dec_power(count & 3);
    uint32_t split = DEC_BASE / factor;

    if (count == 0) {
        return;
    }
    for (size_t i = n; i-- > 0; ) {
        uint32_t high = i >= whole ? c[i - whole] % split * factor : 0;
        uint32_t low = i > whole ? c[i - whole - 1] / split : 0;

        c[i] = high + low;
    }
}

// Divides by 10^count, leaving out the remainder.
static void dec_scale_down(uint32_t *c, size_t n, size_t count) {
    size_t whole = count >> 2;
    uint32_t factor = dec_power(count & 3);
    uint32_t split = DEC_BASE / factor;

    if (count == 0) {
        return;
    }
    for (size_t i = 0; i < n; i++) {
        uint32_t low = i + whole < n ? c[i + whole] / factor : 0;
        uint32_t high = i + whole + 1 < n ? c[i + whole + 1] % factor * split : 0;

        c[i] = low + high;
    }
}

static void dec_widen(uint32_t *c, const struct dec *x, size_t n) {
    for (size_t i = 0; i < n; i++) {
        c[i] = i < DEC_LIMBS ? x->coefficient[i] : 0;
    }
}

static void dec_set_infinite(struct dec *r, bool negative) {
    for (size_t i = 0; i < DEC_LIMBS; i++) {
        r->coefficient[i] = 0;
    }
    r->kind = DEC_INFINITE;
    r->negative = negative;
    r->exponent = 0;
}

// The result of an invalid operation, which has neither sign nor payload.
static void dec_set_invalid(struct dec *r) {
    dec_set_infinite(r, false);
    r->kind = DEC_QUIET;
}

// The first signalling NaN, else the first NaN, becomes the result, quiet, as
// it is.
static bool dec_propagate(struct dec *r, const struct dec *a, const struct dec *b) {
    const struct dec *source;

    if (a->kind == DEC_SIGNALLING) {
        source = a;
    } else if (b->kind == DEC_SIGNALLING) {
        source = b;
    } else if (a->kind == DEC_QUIET) {
        source = a;
    } else if (b->kind == DEC_QUIET) {
        source = b;
    } else {
        return false;
    }
    *r = *source;
    r->kind = DEC_QUIET;
    return true;
}

// Whether a number rounds away from zero when it loses its last count digits,
// with sticky telling of a further remainder below them: to nearest, with ties
// to even.
static bool dec_rounds_up(const uint32_t *c, size_t n, size_t count, bool sticky) {
    size_t limb = (count - 1) >> 2;
    uint32_t unit = dec_power((count - 1) & 3);
    uint32_t digit = limb < n ? c[limb] / unit % 10 : 0;
    size_t next = count >> 2;

    if (digit != 5) {
        return digit > 5;
    }
    if (sticky || c[limb] % unit != 0) {
        return true;
    }
    for (size_t i = 0; i < limb; i++) {
        if (c[i] != 0) {
            return true;
        }
    }
    return next < n && (c[next] / dec_power(count & 3) & 1) != 0;
}

static void dec_increment(uint32_t *c, size_t n) {
    for (size_t i = 0; i < n; i++) {
        c[i] += 1;
        if (c[i] < DEC_BASE) {
            return;
        }
        c[i] = 0;
    }
}

// Makes the finite number c * 10^exponent the result, with its sign already in
// r, c having n limbs, at least those of the format, and sticky telling of a
// remainder below its last digit. All operations round here, once.
static void dec_round(
    struct dec *r,
    uint32_t *c,
    size_t n,
    int32_t exponent,
    bool sticky,
    size_t words
) {
    size_t precision = dec_precision(words);
    int32_t lowest = -dec_bias(words);
    int32_t highest = dec_highest_exponent(words);
    size_t digits = dec_digits(c, n);
    int32_t drop = digits > precision ? (int32_t)(digits - precision) : 0;

    if (exponent + drop < lowest) {
        drop = lowest - exponent;
    }
    if (drop > 0) {
        bool up = dec_rounds_up(c, n, (size_t)drop, sticky);

        dec_scale_down(c, n, (size_t)drop);
        exponent += drop;
        if (up) {
            dec_increment(c, n);
        }
        digits = dec_digits(c, n);
        if (digits > precision) {
            dec_scale_down(c, n, 1);
            exponent += 1;
            digits -= 1;
        }
    }
    if (digits == 0) {
        if (exponent > highest) {
            exponent = highest;
        }
    } else if (exponent + (int32_t)digits > highest + (int32_t)precision) {
        dec_set_infinite(r, r->negative);
        return;
    } else if (exponent > highest) {
        dec_scale_up(c, n, (size_t)(exponent - highest));
        exponent = highest;
    }
    r->kind = DEC_FINITE;
    r->exponent = exponent;
    for (size_t i = 0; i < DEC_LIMBS; i++) {
        r->coefficient[i] = i < n ? c[i] : 0;
    }
}

// The order of two numbers: -1, 0, or 1.
static int dec_order(const uint32_t *x, const uint32_t *y, size_t n) {
    for (size_t i = n; i-- > 0; ) {
        if (x[i] != y[i]) {
            return x[i] < y[i] ? -1 : 1;
        }
    }
    return 0;
}

// Adds y to x, and returns the carry out of the last limb.
static uint32_t dec_add_limbs(uint32_t *x, const uint32_t *y, size_t n) {
    uint32_t carry = 0;

    for (size_t i = 0; i < n; i++) {
        uint32_t sum = x[i] + y[i] + carry;

        carry = sum >= DEC_BASE ? 1 : 0;
        x[i] = carry != 0 ? sum - DEC_BASE : sum;
    }
    return carry;
}

// Subtracts from x a y that is not above it.
static void dec_subtract_limbs(uint32_t *x, const uint32_t *y, size_t n) {
    uint32_t borrow = 0;

    for (size_t i = 0; i < n; i++) {
        uint32_t difference = x[i] + DEC_BASE - y[i] - borrow;

        borrow = difference < DEC_BASE ? 1 : 0;
        x[i] = borrow != 0 ? difference : difference - DEC_BASE;
    }
}

static void dec_add(
    struct dec *r,
    const struct dec *a,
    const struct dec *b,
    bool subtract,
    size_t words
) {
    bool b_negative = b->negative != subtract;
    bool swap = a->exponent < b->exponent;
    const struct dec *high = swap ? b : a;
    const struct dec *low = swap ? a : b;
    bool high_negative = swap ? b_negative : a->negative;
    bool low_negative = swap ? a->negative : b_negative;
    size_t n = dec_wide_limbs(words);
    size_t room = 2 * dec_precision(words) + 2;
    uint32_t x[DEC_WIDE_LIMBS];
    uint32_t y[DEC_WIDE_LIMBS];
    size_t digits;
    size_t gap;
    int32_t exponent = low->exponent;
    int order;

    if (dec_propagate(r, a, b)) {
        return;
    }
    if (a->kind == DEC_INFINITE || b->kind == DEC_INFINITE) {
        if (a->kind != DEC_INFINITE) {
            dec_set_infinite(r, b_negative);
        } else if (b->kind == DEC_INFINITE && a->negative != b_negative) {
            dec_set_invalid(r);
        } else {
            dec_set_infinite(r, a->negative);
        }
        return;
    }
    dec_widen(x, high, n);
    dec_widen(y, low, n);
    digits = dec_digits(x, n);
    gap = digits == 0 ? 0 : (size_t)(high->exponent - low->exponent);
    if (digits + gap > room) {
        // All of the lower number lies so far below where the sum rounds that
        // a single unit gives the same rounding.
        bool nonzero = dec_digits(y, n) != 0;

        gap = room - digits;
        exponent = high->exponent - (int32_t)gap;
        for (size_t i = 0; i < n; i++) {
            y[i] = 0;
        }
        y[0] = nonzero ? 1 : 0;
    }
    dec_scale_up(x, n, gap);
    if (high_negative == low_negative) {
        dec_add_limbs(x, y, n);
        r->negative = high_negative;
        dec_round(r, x, n, exponent, false, words);
        return;
    }
    order = dec_order(x, y, n);
    if (order < 0) {
        dec_subtract_limbs(y, x, n);
        r->negative = low_negative;
        dec_round(r, y, n, exponent, false, words);
        return;
    }
    dec_subtract_limbs(x, y, n);
    r->negative = order > 0 && high_negative;
    dec_round(r, x, n, exponent, false, words);
}

static void dec_multiply(struct dec *r, const struct dec *a, const struct dec *b, size_t words) {
    size_t limbs = dec_limbs(words);
    size_t n = dec_wide_limbs(words);
    uint32_t c[DEC_WIDE_LIMBS];
    uint32_t carry = 0;

    if (dec_propagate(r, a, b)) {
        return;
    }
    r->negative = a->negative != b->negative;
    if (a->kind == DEC_INFINITE || b->kind == DEC_INFINITE) {
        const struct dec *other = a->kind == DEC_INFINITE ? b : a;

        if (other->kind == DEC_FINITE && dec_digits(other->coefficient, limbs) == 0) {
            dec_set_invalid(r);
        } else {
            dec_set_infinite(r, r->negative);
        }
        return;
    }
    for (size_t k = 0; k < n; k++) {
        uint32_t sum = carry;

        for (size_t i = k < limbs ? 0 : k - limbs + 1; i <= k && i < limbs; i++) {
            sum += a->coefficient[i] * b->coefficient[k - i];
        }
        c[k] = sum % DEC_BASE;
        carry = sum / DEC_BASE;
    }
    dec_round(r, c, n, a->exponent + b->exponent, false, words);
}

static void dec_multiply_small(uint32_t *c, size_t n, uint32_t factor) {
    uint32_t carry = 0;

    for (size_t i = 0; i < n; i++) {
        uint32_t value = c[i] * factor + carry;

        c[i] = value % DEC_BASE;
        carry = value / DEC_BASE;
    }
}

// Long division in the base of the limbs, as Knuth's Algorithm D has it, of u,
// of un limbs and room for one more, by v, of vn limbs, the top one not zero.
// Gives the limbs of the quotient in q, and whether a remainder is left.
static bool dec_long_divide(uint32_t *q, uint32_t *u, size_t un, uint32_t *v, size_t vn) {
    uint32_t factor = DEC_BASE / (v[vn - 1] + 1);

    u[un] = 0;
    dec_multiply_small(u, un + 1, factor);
    dec_multiply_small(v, vn, factor);
    for (size_t j = un - vn + 1; j-- > 0; ) {
        uint32_t top = u[j + vn] * DEC_BASE + u[j + vn - 1];
        uint32_t qhat = top / v[vn - 1];
        uint32_t rhat = top % v[vn - 1];
        uint32_t carry = 0;
        uint32_t borrow = 0;

        while (qhat >= DEC_BASE
            || (vn > 1 && qhat * v[vn - 2] > rhat * DEC_BASE + u[j + vn - 2])) {
            qhat -= 1;
            rhat += v[vn - 1];
            if (rhat >= DEC_BASE) {
                break;
            }
        }
        for (size_t i = 0; i <= vn; i++) {
            uint32_t product = (i < vn ? qhat * v[i] : 0) + carry;
            uint32_t difference = u[i + j] + DEC_BASE - product % DEC_BASE - borrow;

            carry = product / DEC_BASE;
            borrow = difference < DEC_BASE ? 1 : 0;
            u[i + j] = borrow != 0 ? difference : difference - DEC_BASE;
        }
        if (borrow != 0) {
            carry = dec_add_limbs(u + j, v, vn);
            u[j + vn] = (u[j + vn] + carry) % DEC_BASE;
            qhat -= 1;
        }
        q[j] = qhat;
    }
    for (size_t i = 0; i <= un; i++) {
        if (u[i] != 0) {
            return true;
        }
    }
    return false;
}

static size_t dec_trailing_zeros(const uint32_t *c, size_t n) {
    size_t count = 0;

    for (size_t i = 0; i < n; i++) {
        uint32_t limb = c[i];

        if (limb != 0) {
            while (limb % 10 == 0) {
                limb /= 10;
                count += 1;
            }
            break;
        }
        count += 4;
    }
    return count;
}

static void dec_divide(struct dec *r, const struct dec *a, const struct dec *b, size_t words) {
    size_t limbs = dec_limbs(words);
    size_t n = dec_wide_limbs(words);
    size_t a_digits = dec_digits(a->coefficient, limbs);
    size_t b_digits = dec_digits(b->coefficient, limbs);
    int32_t exponent = a->exponent - b->exponent;
    uint32_t q[DEC_WIDE_LIMBS];
    bool sticky = false;

    if (dec_propagate(r, a, b)) {
        return;
    }
    r->negative = a->negative != b->negative;
    if (a->kind == DEC_INFINITE) {
        if (b->kind == DEC_INFINITE) {
            dec_set_invalid(r);
        } else {
            dec_set_infinite(r, r->negative);
        }
        return;
    }
    if (b_digits == 0 && b->kind == DEC_FINITE) {
        if (a_digits == 0) {
            dec_set_invalid(r);
        } else {
            dec_set_infinite(r, r->negative);
        }
        return;
    }
    for (size_t i = 0; i < n; i++) {
        q[i] = 0;
    }
    if (b->kind == DEC_INFINITE) {
        // The exponent of the divisor counts as above all others.
        exponent = -dec_bias(words);
    } else if (a_digits != 0) {
        // A quotient of at least one digit beyond the precision, for what
        // rounding needs. If it comes out exact, it goes back towards the
        // exponent wanted, which is that of the unscaled quotient.
        size_t scale = dec_precision(words) + 1 + b_digits - a_digits;
        size_t un = (dec_precision(words) + 1 + b_digits + 3) >> 2;
        uint32_t u[DEC_WIDE_LIMBS + 1];
        uint32_t v[DEC_LIMBS];

        dec_widen(u, a, n);
        dec_scale_up(u, n, scale);
        for (size_t i = 0; i < limbs; i++) {
            v[i] = b->coefficient[i];
        }
        exponent -= (int32_t)scale;
        sticky = dec_long_divide(q, u, un, v, (b_digits + 3) >> 2);
        if (!sticky) {
            size_t zeros = dec_trailing_zeros(q, n);

            zeros = zeros < scale ? zeros : scale;
            dec_scale_down(q, n, zeros);
            exponent += (int32_t)zeros;
        }
    }
    dec_round(r, q, n, exponent, sticky, words);
}

static int dec_sign(const struct dec *x, size_t digits) {
    if (x->kind == DEC_FINITE && digits == 0) {
        return 0;
    }
    return x->negative ? -1 : 1;
}

// Below, equal, or above as -1, 0, or 1; unordered if either is a NaN.
static fp_cmp dec_compare(struct dec *a, struct dec *b, fp_cmp unordered, size_t words) {
    size_t limbs = dec_limbs(words);
    size_t a_digits = dec_digits(a->coefficient, limbs);
    size_t b_digits = dec_digits(b->coefficient, limbs);
    int a_sign = dec_sign(a, a_digits);
    int b_sign = dec_sign(b, b_digits);
    int32_t a_top = a->exponent + (int32_t)a_digits;
    int32_t b_top = b->exponent + (int32_t)b_digits;
    int order;

    if (a->kind >= DEC_QUIET || b->kind >= DEC_QUIET) {
        return unordered;
    }
    if (a_sign != b_sign) {
        return a_sign < b_sign ? -1 : 1;
    }
    if (a_sign == 0) {
        return 0;
    }
    if (a->kind == DEC_INFINITE || b->kind == DEC_INFINITE) {
        order = a->kind == b->kind ? 0 : a->kind == DEC_INFINITE ? 1 : -1;
    } else if (a_top != b_top) {
        order = a_top < b_top ? -1 : 1;
    } else {
        if (a_digits < b_digits) {
            dec_scale_up(a->coefficient, limbs, b_digits - a_digits);
        } else {
            dec_scale_up(b->coefficient, limbs, a_digits - b_digits);
        }
        order = dec_order(a->coefficient, b->coefficient, limbs);
    }
    return a_sign < 0 ? -order : order;
}

// Words of a format little end first, whatever its order in memory.
#if defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#   define DEC_WORD(i, words) ((words) - 1 - (i))
#else
#   define DEC_WORD(i, words) (i)
#endif

static void dec_load(uint32_t *w, const void *value, size_t words) {
    uint32_t raw[4];

    __builtin_memcpy(raw, value, words * sizeof(uint32_t));
    for (size_t i = 0; i < words; i++) {
        w[i] = raw[DEC_WORD(i, words)];
    }
}

static void dec_store(void *value, const uint32_t *w, size_t words) {
    uint32_t raw[4];

    for (size_t i = 0; i < words; i++) {
        raw[DEC_WORD(i, words)] = w[i];
    }
    __builtin_memcpy(value, raw, words * sizeof(uint32_t));
}

static uint32_t dec_mask(size_t bits) {
    return ((uint32_t)1 << bits) - 1;
}

// Binary integers, in pieces of 16 bits, little end first, which keep the
// steps to and from limbs within 32 bits. Gives the pieces of a number that
// fits them.
static void dec_limbs_to_chunks(uint32_t *chunks, size_t n, const uint32_t *c, size_t limbs) {
    for (size_t i = 0; i < n; i++) {
        chunks[i] = 0;
    }
    for (size_t limb = limbs; limb-- > 0; ) {
        uint32_t carry = c[limb];

        for (size_t i = 0; i < n; i++) {
            uint32_t value = chunks[i] * DEC_BASE + carry;

            chunks[i] = value & 0xffff;
            carry = value >> 16;
        }
    }
}

// Gives the limbs of a number that fits them, using up its pieces.
static void dec_chunks_to_limbs(uint32_t *c, size_t limbs, uint32_t *chunks, size_t n) {
    for (size_t limb = 0; limb < limbs; limb++) {
        uint32_t remainder = 0;

        // Workaround: GCC 5 to 7, IA-32, at -O3: a loop counting down here
        // gets a false -Warray-bounds.
        for (size_t i = 0; i < n; i++) {
            uint32_t value = remainder << 16 | chunks[n - 1 - i];

            chunks[n - 1 - i] = value / DEC_BASE;
            remainder = value % DEC_BASE;
        }
        while (n > 0 && chunks[n - 1] == 0) {
            n -= 1;
        }
        c[limb] = remainder;
    }
}

#if defined(__DECIMAL_BID_FORMAT__)

// The binary integer form: after the sign, an exponent of the continuation's
// bits and 2 more, then the coefficient. Where the first 2 bits of that
// exponent are both set, the exponent comes after them, and the coefficient
// has 2 bits less, with 100 in front of them.
static size_t dec_coefficient_shift(size_t words) {
    return 25 - 2 * words;
}

// Gives the coefficient that the low words of w and the top word high make, by
// pieces of 16 bits, as zero if it has more digits than the format holds.
static void dec_from_bits(
    struct dec *r,
    const uint32_t *w,
    uint32_t high,
    size_t digits,
    size_t words
) {
    uint32_t chunks[8];
    size_t n = 2 * words;

    for (size_t i = 0; i < words; i++) {
        uint32_t word = i == words - 1 ? high : w[i];

        chunks[2 * i] = word & 0xffff;
        chunks[2 * i + 1] = word >> 16;
    }
    dec_chunks_to_limbs(r->coefficient, DEC_LIMBS, chunks, n);
    if (dec_digits(r->coefficient, DEC_LIMBS) > digits) {
        for (size_t i = 0; i < DEC_LIMBS; i++) {
            r->coefficient[i] = 0;
        }
    }
}

static void dec_unpack_finite(struct dec *r, const uint32_t *w, size_t words) {
    uint32_t top = w[words - 1];
    size_t shift = dec_coefficient_shift(words);
    uint32_t mask = dec_mask(dec_continuation(words) + 2);
    uint32_t biased = (top >> shift) & mask;
    uint32_t high = top & dec_mask(shift);

    if (((top >> 29) & 3) == 3) {
        biased = (top >> (shift - 2)) & mask;
        high = (top & dec_mask(shift - 2)) | (uint32_t)1 << shift;
    }
    r->exponent = (int32_t)biased - dec_bias(words);
    dec_from_bits(r, w, high, dec_precision(words), words);
}

static void dec_unpack_payload(struct dec *r, const uint32_t *w, size_t words) {
    uint32_t high = w[words - 1] & dec_mask(26 - dec_continuation(words));

    dec_from_bits(r, w, high, dec_precision(words) - 1, words);
}

static void dec_pack_number(uint32_t *w, const struct dec *x, size_t words) {
    uint32_t chunks[8];

    dec_limbs_to_chunks(chunks, 2 * words, x->coefficient, dec_limbs(words));
    for (size_t i = 0; i < words; i++) {
        w[i] = chunks[2 * i] | chunks[2 * i + 1] << 16;
    }
    if (x->kind == DEC_FINITE) {
        uint32_t top = w[words - 1];
        size_t shift = dec_coefficient_shift(words);
        uint32_t biased = (uint32_t)(x->exponent + dec_bias(words));

        if (top >> shift != 0) {
            top = (uint32_t)3 << 29 | biased << (shift - 2) | (top & dec_mask(shift - 2));
        } else {
            top |= biased << shift;
        }
        w[words - 1] = top;
    }
}

#else // defined(__DECIMAL_BID_FORMAT__)

// The densely packed form, as the Power ISA's appendix on it has the tables:
// bits, from the top, pqr stu v wxy, for digits of bits abcd efgh ijkm.
static uint32_t dec_declet_to_value(uint32_t declet) {
    uint32_t pqr = (declet >> 7) & 7;
    uint32_t pq = (declet >> 8) & 3;
    uint32_t r = (declet >> 7) & 1;
    uint32_t stu = (declet >> 4) & 7;
    uint32_t st = (declet >> 5) & 3;
    uint32_t u = (declet >> 4) & 1;
    uint32_t y = declet & 1;
    uint32_t first = pqr;
    uint32_t second = stu;
    uint32_t third = declet & 7;

    if ((declet & 8) != 0) {
        switch ((declet >> 1) & 3) {
            case 0: {
                third = 8 | y;
                break;
            }
            case 1: {
                second = 8 | u;
                third = st << 1 | y;
                break;
            }
            case 2: {
                first = 8 | r;
                third = pq << 1 | y;
                break;
            }
            default: {
                first = st == 2 ? pqr : 8 | r;
                second = st == 1 ? pq << 1 | u : 8 | u;
                third = st == 0 ? pq << 1 | y : 8 | y;
                break;
            }
        }
    }
    return first * 100 + second * 10 + third;
}

static uint32_t dec_value_to_declet(uint32_t value) {
    uint32_t first = value / 100;
    uint32_t second = value / 10 % 10;
    uint32_t third = value % 10;
    uint32_t bcd = first & 7;
    uint32_t d = first & 1;
    uint32_t fgh = second & 7;
    uint32_t fg = (second >> 1) & 3;
    uint32_t h = second & 1;
    uint32_t jkm = third & 7;
    uint32_t jk = (third >> 1) & 3;
    uint32_t m = third & 1;

    switch ((first >> 3) << 2 | (second >> 3) << 1 | third >> 3) {
        case 0: {
            return bcd << 7 | fgh << 4 | jkm;
        }
        case 1: {
            return bcd << 7 | fgh << 4 | 8 | m;
        }
        case 2: {
            return bcd << 7 | jk << 5 | h << 4 | 10 | m;
        }
        case 3: {
            return bcd << 7 | 2 << 5 | h << 4 | 14 | m;
        }
        case 4: {
            return jk << 8 | d << 7 | fgh << 4 | 12 | m;
        }
        case 5: {
            return fg << 8 | d << 7 | 1 << 5 | h << 4 | 14 | m;
        }
        case 6: {
            return jk << 8 | d << 7 | h << 4 | 14 | m;
        }
        default: {
            return d << 7 | 3 << 5 | h << 4 | 14 | m;
        }
    }
}

// The coefficient has its last digits in w, 10 bits for every 3, and the digit
// above them apart: 4 such groups make 3 limbs.
static void dec_from_declets(struct dec *r, const uint32_t *w, uint32_t top_digit, size_t words) {
    size_t count = 3 * words - 1;
    uint32_t values[12];

    for (size_t i = 0; i < 12; i++) {
        size_t word = (10 * i) >> 5;
        size_t shift = (10 * i) & 31;
        uint32_t bits = 0;

        if (i < count) {
            bits = w[word] >> shift;
            if (shift > 22) {
                bits |= w[word + 1] << (32 - shift);
            }
            bits = dec_declet_to_value(bits & 0x3ff);
        }
        values[i] = i == count ? top_digit : bits;
    }
    for (size_t i = 0; i < 3; i++) {
        uint32_t *c = r->coefficient + 3 * i;
        const uint32_t *d = values + 4 * i;

        c[0] = d[0] + d[1] % 10 * 1000;
        c[1] = d[1] / 10 + d[2] % 100 * 100;
        c[2] = d[2] / 100 + d[3] * 10;
    }
}

static void dec_unpack_finite(struct dec *r, const uint32_t *w, size_t words) {
    uint32_t top = w[words - 1];
    uint32_t combination = (top >> 26) & 31;
    size_t continuation = dec_continuation(words);
    uint32_t biased = (top >> (26 - continuation)) & dec_mask(continuation);
    uint32_t high = combination >> 3;
    uint32_t top_digit = combination & 7;

    if (high == 3) {
        high = (combination >> 1) & 3;
        top_digit = 8 | (combination & 1);
    }
    biased |= high << continuation;
    r->exponent = (int32_t)biased - dec_bias(words);
    dec_from_declets(r, w, top_digit, words);
}

static void dec_unpack_payload(struct dec *r, const uint32_t *w, size_t words) {
    dec_from_declets(r, w, 0, words);
}

static void dec_pack_number(uint32_t *w, const struct dec *x, size_t words) {
    size_t count = 3 * words - 1;
    uint32_t values[12];

    for (size_t i = 0; i < words; i++) {
        w[i] = 0;
    }
    for (size_t i = 0; i < 3; i++) {
        const uint32_t *c = x->coefficient + 3 * i;
        uint32_t *d = values + 4 * i;

        d[0] = c[0] % 1000;
        d[1] = c[0] / 1000 + c[1] % 100 * 10;
        d[2] = c[1] / 100 + c[2] % 10 * 100;
        d[3] = c[2] / 10;
    }
    for (size_t i = 0; i < count; i++) {
        size_t word = (10 * i) >> 5;
        size_t shift = (10 * i) & 31;
        uint32_t bits = dec_value_to_declet(values[i]);

        w[word] |= bits << shift;
        if (shift > 22) {
            w[word + 1] |= bits >> (32 - shift);
        }
    }
    if (x->kind == DEC_FINITE) {
        size_t continuation = dec_continuation(words);
        uint32_t biased = (uint32_t)(x->exponent + dec_bias(words));
        uint32_t high = biased >> continuation;
        uint32_t combination = values[count] >= 8
                             ? 24 | high << 1 | (values[count] & 1)
                             : high << 3 | values[count];

        w[words - 1] |= combination << 26
                      | (biased & dec_mask(continuation)) << (26 - continuation);
    }
}

#endif // defined(__DECIMAL_BID_FORMAT__)

static void dec_unpack(struct dec *r, const void *value, size_t words) {
    uint32_t w[4];
    uint32_t combination;

    dec_load(w, value, words);
    combination = (w[words - 1] >> 26) & 31;
    r->negative = w[words - 1] >> 31 != 0;
    r->exponent = 0;
    if (combination == 30) {
        dec_set_infinite(r, r->negative);
        return;
    }
    if (combination == 31) {
        r->kind = ((w[words - 1] >> 25) & 1) != 0 ? DEC_SIGNALLING : DEC_QUIET;
        dec_unpack_payload(r, w, words);
        return;
    }
    r->kind = DEC_FINITE;
    dec_unpack_finite(r, w, words);
}

static void dec_pack(void *value, const struct dec *x, size_t words) {
    uint32_t w[4];

    dec_pack_number(w, x, words);
    if (x->kind == DEC_INFINITE) {
        w[words - 1] = (uint32_t)30 << 26;
    } else if (x->kind != DEC_FINITE) {
        w[words - 1] |= (uint32_t)31 << 26;
    }
    if (x->negative) {
        w[words - 1] |= (uint32_t)1 << 31;
    }
    dec_store(value, w, words);
}

// Workaround: GCC before 5, PowerPC: with the vector instructions of POWER8
// and -mno-hard-dfp, which nothing tells of, it fails to load a _Decimal32
// into the register that returns it, unless hardware decimal is on for the
// routine, which has no decimal arithmetic for that to take part in.
#if __GNUC__ < 5 && defined(__POWER8_VECTOR__) && !defined(_SOFT_FLOAT)
#   define DEC_RETURN __attribute__((__target__("hard-dfp")))
#else
#   define DEC_RETURN
#endif

#define DEC_OPERATION(name, T, words, call) \
    DEC_RETURN T DEC_NAME(name)(T a, T b) { \
        struct dec x; \
        struct dec y; \
        struct dec r; \
        \
        dec_unpack(&x, &a, words); \
        dec_unpack(&y, &b, words); \
        call; \
        dec_pack(&a, &r, words); \
        return a; \
    }

#define DEC_RELATION(name, T, words, unordered) \
    fp_cmp DEC_NAME(name)(T a, T b) { \
        struct dec x; \
        struct dec y; \
        \
        dec_unpack(&x, &a, words); \
        dec_unpack(&y, &b, words); \
        return dec_compare(&x, &y, unordered, words); \
    }

#define DEC_FORMAT(fmt, T, words) \
    DEC_OPERATION(add##fmt##3, T, words, dec_add(&r, &x, &y, false, words)) \
    DEC_OPERATION(sub##fmt##3, T, words, dec_add(&r, &x, &y, true, words)) \
    DEC_OPERATION(mul##fmt##3, T, words, dec_multiply(&r, &x, &y, words)) \
    DEC_OPERATION(div##fmt##3, T, words, dec_divide(&r, &x, &y, words)) \
    DEC_RELATION(eq##fmt##2, T, words, 1) \
    DEC_RELATION(ne##fmt##2, T, words, 1) \
    DEC_RELATION(ge##fmt##2, T, words, -1) \
    DEC_RELATION(lt##fmt##2, T, words, 1) \
    DEC_RELATION(le##fmt##2, T, words, 1) \
    DEC_RELATION(gt##fmt##2, T, words, -1) \
    \
    fp_cmp DEC_NAME(unord##fmt##2)(T a, T b) { \
        uint32_t x[4]; \
        uint32_t y[4]; \
        \
        dec_load(x, &a, words); \
        dec_load(y, &b, words); \
        return ((x[(words) - 1] >> 26) & 31) == 31 || ((y[(words) - 1] >> 26) & 31) == 31; \
    }

DEC_FORMAT(sd, sd_value, 1)
DEC_FORMAT(dd, dd_value, 2)
DEC_FORMAT(td, td_value, 4)

// What the wider format holds exactly, packed with a NaN made quiet.
#define DEC_EXTEND(name, S, source, T, words) \
    DEC_RETURN T DEC_NAME(name)(S a) { \
        struct dec x; \
        T r; \
        \
        dec_unpack(&x, &a, source); \
        dec_pack(&r, &x, words); \
        return r; \
    }

DEC_EXTEND(extendsddd2, sd_value, 1, dd_value, 2)
DEC_EXTEND(extendsdtd2, sd_value, 1, td_value, 4)
DEC_EXTEND(extendddtd2, dd_value, 2, td_value, 4)

// A NaN keeps the last digits of its payload that the format holds.
static void dec_narrow(struct dec *r, const struct dec *x, size_t words) {
    size_t digits = dec_precision(words) - 1;
    size_t whole = digits >> 2;
    uint32_t c[DEC_LIMBS];

    if (x->kind != DEC_FINITE) {
        *r = *x;
        r->coefficient[whole] %= dec_power(digits & 3);
        for (size_t i = whole + 1; i < DEC_LIMBS; i++) {
            r->coefficient[i] = 0;
        }
        return;
    }
    dec_widen(c, x, DEC_LIMBS);
    r->negative = x->negative;
    dec_round(r, c, DEC_LIMBS, x->exponent, false, words);
}

#define DEC_TRUNCATE(name, S, source, T, words) \
    DEC_RETURN T DEC_NAME(name)(S a) { \
        struct dec x; \
        struct dec y; \
        T r; \
        \
        dec_unpack(&x, &a, source); \
        dec_narrow(&y, &x, words); \
        dec_pack(&r, &y, words); \
        return r; \
    }

DEC_TRUNCATE(truncddsd2, dd_value, 2, sd_value, 1)
DEC_TRUNCATE(trunctdsd2, td_value, 4, sd_value, 1)
DEC_TRUNCATE(trunctddd2, td_value, 4, dd_value, 2)

// Limbs that hold any integer of 128 bits.
#define DEC_INTEGER_LIMBS 10

// The words of a coefficient as a binary integer, little end first.
static void dec_coefficient_bits(uint32_t *w, const struct dec *x) {
    uint32_t chunks[8];

    dec_limbs_to_chunks(chunks, 8, x->coefficient, DEC_LIMBS);
    for (size_t i = 0; i < 4; i++) {
        w[i] = chunks[2 * i] | chunks[2 * i + 1] << 16;
    }
}

// Truncates a number towards zero into the words of an integer type, little
// end first. What does not fit it saturates by its sign, a NaN gives 0, and so
// does a negative value in an unsigned type.
static void dec_to_integer(
    uint32_t *w,
    const void *value,
    size_t count,
    bool is_signed,
    size_t words
) {
    struct dec x;
    uint32_t c[DEC_INTEGER_LIMBS];
    uint32_t chunks[9];
    size_t limit = count == 4 ? 39 : 10 * count;
    size_t digits;
    int32_t top;
    bool over;

    dec_unpack(&x, value, words);
    digits = dec_digits(x.coefficient, DEC_LIMBS);
    top = x.exponent + (int32_t)digits;
    for (size_t i = 0; i < count; i++) {
        w[i] = 0;
    }
    if (x.kind >= DEC_QUIET || (x.negative && !is_signed)
     || (x.kind == DEC_FINITE && (digits == 0 || top <= 0))) {
        return;
    }
    over = x.kind == DEC_INFINITE || top > (int32_t)limit;
    if (!over) {
        dec_widen(c, &x, DEC_INTEGER_LIMBS);
        if (x.exponent < 0) {
            dec_scale_down(c, DEC_INTEGER_LIMBS, (size_t)-x.exponent);
        } else {
            dec_scale_up(c, DEC_INTEGER_LIMBS, (size_t)x.exponent);
        }
        dec_limbs_to_chunks(chunks, 2 * count + 1, c, (limit + 3) >> 2);
        for (size_t i = 0; i < count; i++) {
            w[i] = chunks[2 * i] | chunks[2 * i + 1] << 16;
        }
        over = chunks[2 * count] != 0 || (is_signed && (w[count - 1] >> 31) != 0);
    }
    if (over) {
        for (size_t i = 0; i < count; i++) {
            w[i] = x.negative ? 0 : ~(uint32_t)0;
        }
        if (is_signed) {
            w[count - 1] ^= (uint32_t)1 << 31;
        }
    } else if (x.negative) {
        uint32_t carry = 1;

        for (size_t i = 0; i < count; i++) {
            w[i] = ~w[i] + carry;
            carry = carry != 0 && w[i] == 0 ? 1 : 0;
        }
    }
}

static void dec_from_integer(
    void *value,
    const uint32_t *w,
    size_t count,
    bool negative,
    size_t words
) {
    struct dec r;
    uint32_t c[DEC_INTEGER_LIMBS];
    uint32_t chunks[8];

    for (size_t i = 0; i < count; i++) {
        chunks[2 * i] = w[i] & 0xffff;
        chunks[2 * i + 1] = w[i] >> 16;
    }
    dec_chunks_to_limbs(c, DEC_INTEGER_LIMBS, chunks, 2 * count);
    r.negative = negative;
    dec_round(&r, c, DEC_INTEGER_LIMBS, 0, false, words);
    dec_pack(value, &r, words);
}

static uint32_t dec_to_u32(const void *value, bool is_signed, size_t words) {
    uint32_t w[1];

    dec_to_integer(w, value, 1, is_signed, words);
    return w[0];
}

static uint64_t dec_to_u64(const void *value, bool is_signed, size_t words) {
    uint32_t w[2];

    dec_to_integer(w, value, 2, is_signed, words);
    return (uint64_t)w[1] << 32 | w[0];
}

static void dec_from_u32(void *value, uint32_t i, bool negative, size_t words) {
    uint32_t w[1] = { i };

    dec_from_integer(value, w, 1, negative, words);
}

static void dec_from_u64(void *value, uint64_t i, bool negative, size_t words) {
    uint32_t w[2] = { (uint32_t)i, (uint32_t)(i >> 32) };

    dec_from_integer(value, w, 2, negative, words);
}

#if HAS_INT128
static u128 dec_to_u128(const void *value, bool is_signed, size_t words) {
    uint32_t w[4];

    dec_to_integer(w, value, 4, is_signed, words);
    return (u128)((uint64_t)w[3] << 32 | w[2]) << 64 | ((uint64_t)w[1] << 32 | w[0]);
}

static void dec_from_u128(void *value, u128 i, bool negative, size_t words) {
    uint64_t low = (uint64_t)i;
    uint64_t high = (uint64_t)(i >> 64);
    uint32_t w[4] = {
        (uint32_t)low, (uint32_t)(low >> 32),
        (uint32_t)high, (uint32_t)(high >> 32)
    };

    dec_from_integer(value, w, 4, negative, words);
}
#endif

#define DEC_WITH_MODE(mode, I, U, bits, fmt, T, words) \
    I DEC_NAME(fix##fmt##mode)(T a) { \
        return (I)dec_to_u##bits(&a, true, words); \
    } \
    \
    U DEC_NAME(fixuns##fmt##mode)(T a) { \
        return dec_to_u##bits(&a, false, words); \
    } \
    \
    DEC_RETURN T DEC_NAME(float##mode##fmt)(I i) { \
        U magnitude = i < 0 ? (U)0 - (U)i : (U)i; \
        T r; \
        \
        dec_from_u##bits(&r, magnitude, i < 0, words); \
        return r; \
    } \
    \
    DEC_RETURN T DEC_NAME(floatuns##mode##fmt)(fp_unsigned_##mode i) { \
        T r; \
        \
        dec_from_u##bits(&r, (U)i, false, words); \
        return r; \
    }

#define DEC_MODE(mode, I, U, bits) \
    DEC_WITH_MODE(mode, I, U, bits, sd, sd_value, 1) \
    DEC_WITH_MODE(mode, I, U, bits, dd, dd_value, 2) \
    DEC_WITH_MODE(mode, I, U, bits, td, td_value, 4)

DEC_MODE(si, int32_t, uint32_t, 32)
DEC_MODE(di, int64_t, uint64_t, 64)
#if HAS_INT128
DEC_MODE(ti, i128, u128, 128)
#endif

// What follows takes exact values between binary and decimal, which reach far,
// so it has binary numbers of many limbs of 32 bits, little end first, in a
// work area of the routine, whose size goes by the formats at hand: a product
// in all of it, or a power of 5 and a remainder in a half of it each. A cut on
// the exponents first leaves out the values that overflow or round to zero.
#define DEC_MAX(a, b) ((a) > (b) ? (a) : (b))
#define DEC_MIN(a, b) ((a) < (b) ? (a) : (b))

// The largest power of 5 that a value of a binary format of bits from 2^lo up
// to below 2^hi needs in the format of this many words.
#define DEC_POWER(hi, lo, words) \
    DEC_MIN( \
        DEC_MAX((hi) * 302 / 1000 + 2, (1 - (lo)) * 302 / 1000 + 9 * (words) + 1), \
        ((words) == 1 ? 101 : (words) == 2 ? 398 : 6176) + 9 * (words) + 3 \
    )

// log2(5) is below 7 / 3.
#define DEC_HALF_BITS(bits, hi, lo, words) \
    (DEC_MAX((bits), (words) == 4 ? 113 : 27 * (words)) + DEC_POWER(hi, lo, words) * 7 / 3)
#define DEC_HALF(bits, hi, lo, words) (DEC_HALF_BITS(bits, hi, lo, words) / 32 + 3)

// Multiplies by 5^count, and returns the limbs that the product has.
static size_t dec_big_times_5(uint32_t *x, size_t n, size_t count) {
    while (count != 0) {
        size_t step = count < 13 ? count : 13;
        uint32_t factor = 1;
        uint32_t carry = 0;

        for (size_t i = 0; i < step; i++) {
            factor *= 5;
        }
        for (size_t i = 0; i < n; i++) {
            uint64_t value = (uint64_t)x[i] * factor + carry;

            x[i] = (uint32_t)value;
            carry = (uint32_t)(value >> 32);
        }
        if (carry != 0) {
            x[n] = carry;
            n += 1;
        }
        count -= step;
    }
    return n;
}

static size_t dec_big_length(const uint32_t *x, size_t n) {
    for (size_t i = n; i-- > 0; ) {
        if (x[i] != 0) {
            return 32 * i + 32 - clz32(x[i]);
        }
    }
    return 0;
}

// The 32 bits from bit pos up, with zeros below bit 0 and above the limbs.
static uint32_t dec_big_word_at(const uint32_t *x, size_t n, int32_t pos) {
    size_t limb = (size_t)pos >> 5;
    unsigned int shift = (unsigned int)pos & 31;
    uint32_t bits;

    if (pos < 0) {
        return pos > -32 && n != 0 ? x[0] << -pos : 0;
    }
    bits = limb < n ? x[limb] >> shift : 0;
    if (shift != 0 && limb + 1 < n) {
        bits |= x[limb + 1] << (32 - shift);
    }
    return bits;
}

static bool dec_big_any_below(const uint32_t *x, size_t n, size_t count) {
    size_t whole = count >> 5;
    unsigned int rest = (unsigned int)count & 31;

    for (size_t i = 0; i < whole && i < n; i++) {
        if (x[i] != 0) {
            return true;
        }
    }
    return whole < n && rest != 0 && x[whole] << (32 - rest) != 0;
}

// Gives x shifted right by shift, or left where that is negative, which fits
// y, and whether that lost any bits.
static bool dec_big_take(uint32_t *y, size_t yn, const uint32_t *x, size_t n, int32_t shift) {
    for (size_t i = 0; i < yn; i++) {
        y[i] = dec_big_word_at(x, n, shift + 32 * (int32_t)i);
    }
    return shift > 0 && dec_big_any_below(x, n, (size_t)shift);
}

// Subtracts from x, of n limbs, a y not above it, of as many limbs or less.
static void dec_big_subtract(uint32_t *x, size_t n, const uint32_t *y, size_t yn) {
    uint32_t borrow = 0;

    for (size_t i = 0; i < n; i++) {
        uint64_t difference = (uint64_t)x[i] - (i < yn ? y[i] : 0) - borrow;

        x[i] = (uint32_t)difference;
        borrow = (uint32_t)(difference >> 32) & 1;
    }
}

// Gives the quotient of x * 2^shift, rounded down, by den, which fits y, and
// whether anything is left. It goes one bit at a time, from all the bits that
// the remainder can start with, so that the work is that of the bits of the
// quotient. rem has room for a limb more than den.
static bool dec_big_divide(
    uint32_t *y,
    size_t yn,
    const uint32_t *x,
    size_t n,
    int32_t shift,
    const uint32_t *den,
    size_t dn,
    uint32_t *rem
) {
    int32_t length = (int32_t)dec_big_length(x, n);
    int32_t total = length + shift;
    int32_t first = (int32_t)dec_big_length(den, dn) - 1;
    bool left = shift < 0 && dec_big_any_below(x, n, (size_t)-shift);

    first = first < total ? first : total;
    dec_big_take(rem, dn + 1, x, n, length - first);
    for (size_t i = 0; i < yn; i++) {
        y[i] = 0;
    }
    for (int32_t i = total - first; i-- > 0; ) {
        uint32_t carry = 0;
        uint32_t bit = i - shift < 0 ? 0 : dec_big_word_at(x, n, i - shift) & 1;

        for (size_t j = 0; j <= dn; j++) {
            uint32_t next = rem[j] >> 31;

            rem[j] = rem[j] << 1 | (j == 0 ? bit : carry);
            carry = next;
        }
        carry = rem[dn] != 0 || dec_order(rem, den, dn) >= 0 ? 1 : 0;
        if (carry != 0) {
            dec_big_subtract(rem, dn + 1, den, dn);
        }
        for (size_t j = 0; j < yn; j++) {
            uint32_t next = y[j] >> 31;

            y[j] = y[j] << 1 | carry;
            carry = next;
        }
    }
    return left || dec_big_length(rem, dn + 1) != 0;
}

static void dec_special(void *value, int kind, bool negative, size_t words) {
    struct dec r;

    dec_set_infinite(&r, negative);
    r.kind = kind;
    dec_pack(value, &r, words);
}

// The value m * 2^e in the format of this many words. 10^l is at most the
// value, so that its product with 10^t, rounded down, has 2 or 3 digits more
// than the precision, for rounding to work on, and fits 4 limbs. Where that
// product is exact, it goes back towards exponent 0.
static void dec_from_binary(
    void *value,
    const uint32_t *m,
    size_t mn,
    int32_t e,
    bool negative,
    size_t words,
    uint32_t *work,
    size_t half
) {
    struct dec r;
    uint32_t y[4];
    uint32_t chunks[8];
    uint32_t c[DEC_INTEGER_LIMBS];
    int32_t precision = (int32_t)dec_precision(words);
    int32_t lowest = -dec_bias(words);
    size_t length = dec_big_length(m, mn);
    int32_t b = (int32_t)length + e;
    int32_t l = b > 0 ? (b - 1) * 30102 / 100000 : -((1 - b) * 30103 / 100000) - 1;
    int32_t t = precision + 1 - l;
    int32_t exponent = -t;
    bool sticky;

    r.negative = negative;
    if (length != 0 && l >= dec_highest_exponent(words) + precision) {
        dec_special(value, DEC_INFINITE, negative, words);
        return;
    }
    for (size_t i = 0; i < DEC_INTEGER_LIMBS; i++) {
        c[i] = 0;
    }
    if (length == 0 || (b <= 0 && -b * 30102 / 100000 >= 1 - lowest)) {
        dec_round(&r, c, DEC_INTEGER_LIMBS, length == 0 ? 0 : lowest, false, words);
        dec_pack(value, &r, words);
        return;
    }
    if (t >= 0) {
        size_t n = (length + 31) >> 5;

        for (size_t i = 0; i < n; i++) {
            work[i] = m[i];
        }
        n = dec_big_times_5(work, n, (size_t)t);
        sticky = dec_big_take(y, 4, work, n, -e - t);
    } else {
        size_t dn;

        work[0] = 1;
        dn = dec_big_times_5(work, 1, (size_t)-t);
        sticky = dec_big_divide(y, 4, m, mn, e + t, work, dn, work + half);
    }
    for (size_t i = 0; i < 4; i++) {
        chunks[2 * i] = y[i] & 0xffff;
        chunks[2 * i + 1] = y[i] >> 16;
    }
    dec_chunks_to_limbs(c, DEC_INTEGER_LIMBS, chunks, 8);
    if (!sticky && t > 0) {
        size_t zeros = dec_trailing_zeros(c, DEC_INTEGER_LIMBS);

        zeros = zeros < (size_t)t ? zeros : (size_t)t;
        dec_scale_down(c, DEC_INTEGER_LIMBS, zeros);
        exponent += (int32_t)zeros;
    }
    dec_round(&r, c, DEC_INTEGER_LIMBS, exponent, sticky, words);
    dec_pack(value, &r, words);
}

// Gives x / 5^power, for a power of 0 too, as y * 2^exponent, the shape that
// the rounding of a binary format takes: y has want bits, the top one set and
// the last one telling of any left below them too.
static int32_t dec_big_top_bits(
    uint32_t *y,
    size_t want,
    const uint32_t *x,
    size_t n,
    size_t power,
    uint32_t *work,
    size_t half
) {
    int32_t length = (int32_t)dec_big_length(x, n);
    int32_t shift = length - (int32_t)want;
    bool sticky;

    if (power == 0) {
        sticky = dec_big_take(y, 4, x, n, shift);
    } else {
        uint32_t q[4];
        size_t dn;
        int32_t extra;

        work[0] = 1;
        dn = dec_big_times_5(work, 1, power);
        shift = (int32_t)want + 1 + (int32_t)dec_big_length(work, dn) - length;
        sticky = dec_big_divide(q, 4, x, n, shift, work, dn, work + half);
        extra = (int32_t)dec_big_length(q, 4) - (int32_t)want;
        sticky = dec_big_take(y, 4, q, 4, extra) || sticky;
        shift = extra - shift;
    }
    if (sticky) {
        y[0] |= 1;
    }
    return shift;
}

// A kind of number for a binary format, beside those of a decimal one.
#define DEC_ZERO 4

// Reads a number for a binary format whose values go from 2^lo up to below
// 2^hi: a finite one as dec_big_top_bits gives it. Returns what kind of number
// it is, or DEC_ZERO for zero and for what rounds to it.
static int dec_to_binary(
    uint32_t *y,
    size_t want,
    int32_t *exponent,
    bool *negative,
    const void *value,
    size_t words,
    int32_t hi,
    int32_t lo,
    uint32_t *work,
    size_t half
) {
    struct dec x;
    uint32_t m[4];
    size_t digits;
    int32_t top;

    dec_unpack(&x, value, words);
    *negative = x.negative;
    if (x.kind == DEC_SIGNALLING) {
        return DEC_QUIET;
    }
    if (x.kind != DEC_FINITE) {
        return x.kind;
    }
    digits = dec_digits(x.coefficient, DEC_LIMBS);
    top = x.exponent + (int32_t)digits;
    if (digits == 0 || (top <= 0 && -top * 3321 / 1000 >= 1 - lo)) {
        return DEC_ZERO;
    }
    if (top > 1 && (top - 1) * 3321 / 1000 >= hi) {
        return DEC_INFINITE;
    }
    dec_coefficient_bits(m, &x);
    if (x.exponent >= 0) {
        size_t n = (dec_big_length(m, 4) + 31) >> 5;

        for (size_t i = 0; i < n; i++) {
            work[i] = m[i];
        }
        n = dec_big_times_5(work, n, (size_t)x.exponent);
        *exponent = x.exponent + dec_big_top_bits(y, want, work, n, 0, work, half);
    } else {
        *exponent = x.exponent + dec_big_top_bits(y, want, m, 4, (size_t)-x.exponent, work, half);
    }
    return DEC_FINITE;
}

#define DEC_FROM_NARROW(fmt, C, T, E, F) \
    static void dec_from_##fmt(void *value, C a, size_t words, uint32_t *work, size_t half) { \
        T bits = fmt##_to_bits(a); \
        T sig = bits & (FP_INT_BIT(T, F) - 1); \
        int32_t field = (int32_t)(bits >> (F)) & FP_EXP_MAX(E); \
        bool negative = (bits & FP_SIGN(T, E, F)) != 0; \
        uint32_t m[2]; \
        \
        if (field == FP_EXP_MAX(E)) { \
            dec_special(value, sig == 0 ? DEC_INFINITE : DEC_QUIET, negative, words); \
            return; \
        } \
        if (field != 0) { \
            sig |= FP_INT_BIT(T, F); \
        } else { \
            field = 1; \
        } \
        m[0] = (uint32_t)sig; \
        m[1] = (uint32_t)((uint64_t)sig >> 32); \
        dec_from_binary(value, m, 2, field - FP_BIAS(E) - (F), negative, words, work, half); \
    }

#define DEC_TO_NARROW(fmt, C, T, E, F, hi, lo) \
    static C dec_to_##fmt(const void *value, size_t words, uint32_t *work, size_t half) { \
        uint32_t y[4]; \
        int32_t e = 0; \
        bool negative; \
        int kind = dec_to_binary( \
            y, (F) + 4, &e, &negative, value, words, (hi), (lo), work, half \
        ); \
        T bits = negative ? FP_SIGN(T, E, F) : 0; \
        \
        if (kind == DEC_INFINITE) { \
            bits |= FP_INF(T, E, F); \
        } else if (kind == DEC_QUIET) { \
            bits |= FP_NAN(T, E, F); \
        } else if (kind == DEC_FINITE) { \
            bits = fmt##_round_pack( \
                bits, (unsigned int)(e + FP_BIAS(E) + (F) + 3), (T)((uint64_t)y[1] << 32 | y[0]) \
            ); \
        } \
        return fmt##_from_bits(bits); \
    }

#define DEC_FROM_WIDE(fmt, C, M, F) \
    static void dec_from_##fmt(void *value, C a, size_t words, uint32_t *work, size_t half) { \
        struct wide x = fmt##_to_bits(a); \
        struct wide magnitude = WIDE_MAGNITUDE(x); \
        struct wide sig = wide_low_bits(magnitude, (F)); \
        int32_t field = (int32_t)wide_exponent(magnitude, (F)); \
        bool negative = (x.high & WIDE_SIGN) != 0; \
        uint32_t m[4]; \
        \
        if (field == (M)) { \
            dec_special( \
                value, sig.high == 0 && sig.low == 0 ? DEC_INFINITE : DEC_QUIET, negative, words \
            ); \
            return; \
        } \
        if (field != 0) { \
            sig = wide_or(sig, WIDE_INT_BIT(F)); \
        } else { \
            field = 1; \
        } \
        m[0] = (uint32_t)sig.low; \
        m[1] = (uint32_t)(sig.low >> 32); \
        m[2] = (uint32_t)sig.high; \
        m[3] = (uint32_t)(sig.high >> 32); \
        dec_from_binary(value, m, 4, field - WIDE_BIAS(M) - (F), negative, words, work, half); \
    }

#define DEC_TO_WIDE(fmt, C, M, F, hi, lo) \
    static C dec_to_##fmt(const void *value, size_t words, uint32_t *work, size_t half) { \
        uint32_t y[4]; \
        int32_t e = 0; \
        bool negative; \
        int kind = dec_to_binary( \
            y, (F) + 4, &e, &negative, value, words, (hi), (lo), work, half \
        ); \
        uint64_t sign = negative ? WIDE_SIGN : 0; \
        struct wide bits = wide_make(sign, 0); \
        \
        if (kind == DEC_INFINITE) { \
            bits = wide_or(bits, WIDE_INF(M, F)); \
        } else if (kind == DEC_QUIET) { \
            bits = wide_or(bits, WIDE_NAN(M, F)); \
        } else if (kind == DEC_FINITE) { \
            bits = fmt##_round_pack( \
                sign, (unsigned int)(e + WIDE_BIAS(M) + (F) + 3), \
                wide_make((uint64_t)y[3] << 32 | y[2], (uint64_t)y[1] << 32 | y[0]) \
            ); \
        } \
        return fmt##_from_bits(bits); \
    }

// Routines of one binary type and one decimal one, by direction.
#define DEC_FROM_TYPE(name, fmt, C, bits, hi, lo, T, words) \
    DEC_RETURN T DEC_NAME(name)(C a) { \
        uint32_t work[2 * DEC_HALF(bits, hi, lo, words)]; \
        T r; \
        \
        dec_from_##fmt(&r, a, words, work, DEC_HALF(bits, hi, lo, words)); \
        return r; \
    }

#define DEC_TO_TYPE(name, fmt, C, bits, hi, lo, T, words) \
    C DEC_NAME(name)(T a) { \
        uint32_t work[2 * DEC_HALF(bits, hi, lo, words)]; \
        \
        return dec_to_##fmt(&a, words, work, DEC_HALF(bits, hi, lo, words)); \
    }

// The three from a binary type, given their names, whose bits and range are
// the rest of the arguments.
#define DEC_FROM_ALL(sd, dd, td, fmt, C, bits, hi, lo) \
    DEC_FROM_TYPE(sd, fmt, C, bits, hi, lo, sd_value, 1) \
    DEC_FROM_TYPE(dd, fmt, C, bits, hi, lo, dd_value, 2) \
    DEC_FROM_TYPE(td, fmt, C, bits, hi, lo, td_value, 4)

#define DEC_TO_ALL(sd, dd, td, fmt, C, bits, hi, lo) \
    DEC_TO_TYPE(sd, fmt, C, bits, hi, lo, sd_value, 1) \
    DEC_TO_TYPE(dd, fmt, C, bits, hi, lo, dd_value, 2) \
    DEC_TO_TYPE(td, fmt, C, bits, hi, lo, td_value, 4)

DEC_FROM_NARROW(sf, sf_value, uint32_t, 8, 23)
DEC_TO_NARROW(sf, sf_value, uint32_t, 8, 23, 128, -149)
DEC_FROM_ALL(extendsfsd, extendsfdd, extendsftd, sf, sf_value, 24, 128, -149)
DEC_TO_ALL(truncsdsf, truncddsf, trunctdsf, sf, sf_value, 24, 128, -149)

#if SOFT_DOUBLE
DEC_FROM_NARROW(df, df_value, uint64_t, 11, 52)
DEC_TO_NARROW(df, df_value, uint64_t, 11, 52, 1024, -1074)
DEC_FROM_ALL(truncdfsd, extenddfdd, extenddftd, df, df_value, 53, 1024, -1074)
DEC_TO_ALL(extendsddf, truncdddf, trunctddf, df, df_value, 53, 1024, -1074)
#endif

#if SOFT_HF && !HF_PASSED_AS_INT
DEC_FROM_NARROW(hf, hf_value, uint32_t, 5, 10)
DEC_TO_NARROW(hf, hf_value, uint32_t, 5, 10, 16, -24)
DEC_FROM_ALL(extendhfsd, extendhfdd, extendhftd, hf, hf_value, 11, 16, -24)
DEC_TO_ALL(truncsdhf, truncddhf, trunctdhf, hf, hf_value, 11, 16, -24)
#endif

// Compilers take bfloat16 to the wider two through float.
#if defined(SOFT_BF)
DEC_FROM_NARROW(bf, bf_value, uint32_t, 8, 7)
DEC_TO_NARROW(bf, bf_value, uint32_t, 8, 7, 128, -133)
DEC_FROM_TYPE(extendbfsd, bf, bf_value, 8, 128, -133, sd_value, 1)
DEC_TO_ALL(truncsdbf, truncddbf, trunctdbf, bf, bf_value, 8, 128, -133)
#endif

// x86-64 cannot return long double with x87 off, as XF_RETURNED tells.
#if defined(__i386__) || defined(__x86_64__)
DEC_FROM_WIDE(xf, xf_argument, XF_EXP_MAX, 63)
DEC_FROM_ALL(truncxfsd, truncxfdd, extendxftd, xf, xf_argument, 64, 16384, -16445)
#if XF_RETURNED
DEC_TO_WIDE(xf, xf_value, XF_EXP_MAX, 63, 16384, -16445)
DEC_TO_ALL(extendsdxf, extendddxf, trunctdxf, xf, xf_value, 64, 16384, -16445)
#endif
#endif

// PowerPC has IEEE quad under the name kf where the file does too.
#if SOFT_QUAD && defined(__powerpc__) && (defined(__FLOAT128__) || defined(__VSX__))
DEC_FROM_WIDE(kf, quad_value, 32767, 112)
DEC_TO_WIDE(kf, quad_value, 32767, 112, 16384, -16494)
DEC_FROM_ALL(trunckfsd, trunckfdd, extendkftd, kf, quad_value, 113, 16384, -16494)
DEC_TO_ALL(extendsdkf, extendddkf, trunctdkf, kf, quad_value, 113, 16384, -16494)
#elif SOFT_QUAD
DEC_FROM_WIDE(tf, quad_value, 32767, 112)
DEC_TO_WIDE(tf, quad_value, 32767, 112, 16384, -16494)
DEC_FROM_ALL(trunctfsd, trunctfdd, extendtftd, tf, quad_value, 113, 16384, -16494)
DEC_TO_ALL(extendsdtf, extendddtf, trunctdtf, tf, quad_value, 113, 16384, -16494)
#endif

#if HAS_IBM_128

// An exact sum of two doubles, of bits from 2^1023 down to 2^-1074.
#define DEC_IBM_SUM_LIMBS 68
#define DEC_IBM_SUM_BITS 2100

// What the rest of a value takes beside the first double, at most.
#define DEC_IBM_REST_LIMBS 40

// Puts a value in n limbs, at a bit that leaves it room there.
static void dec_big_set(uint32_t *x, size_t n, uint64_t value, size_t pos) {
    size_t limb = pos >> 5;
    unsigned int shift = (unsigned int)pos & 31;

    for (size_t i = 0; i < n; i++) {
        x[i] = 0;
    }
    x[limb] = (uint32_t)value << shift;
    x[limb + 1] = (uint32_t)(value >> (32 - shift));
    if (shift != 0) {
        x[limb + 2] = (uint32_t)((value >> 32) >> (32 - shift));
    }
}

// The significand of a finite double, and the exponent of its last bit.
static uint64_t dec_double_sig(uint64_t bits, int32_t *e) {
    uint64_t sig = bits & (FP_INT_BIT(uint64_t, 52) - 1);
    int32_t field = (int32_t)(bits >> 52) & FP_EXP_MAX(11);

    if (field != 0) {
        sig |= FP_INT_BIT(uint64_t, 52);
    } else {
        field = 1;
    }
    *e = field - FP_BIAS(11) - 52;
    return sig;
}

// The value of a pair is the exact sum of its doubles, or its first double
// where that is an infinity or a NaN, as the format has it, or else its second
// where that is one. An exact cancellation gives +0, and two zeros the sign of
// the first.
static void dec_from_ibm_bits(
    void *value,
    struct ibm_bits bits,
    size_t words,
    uint32_t *work,
    size_t half
) {
    uint64_t mask = IBM_SIGN - 1;
    uint64_t special = (bits.high & mask) >= IBM_INF ? bits.high : bits.low;
    bool first_negative = (bits.high & IBM_SIGN) != 0;
    bool second_negative = (bits.low & IBM_SIGN) != 0;
    bool negative = first_negative;
    uint32_t x[DEC_IBM_SUM_LIMBS];
    uint32_t y[DEC_IBM_SUM_LIMBS];
    const uint32_t *sum = x;
    uint64_t sig_x;
    uint64_t sig_y;
    int32_t e_x;
    int32_t e_y;
    int32_t base;

    if ((special & mask) >= IBM_INF) {
        dec_special(
            value, (special & mask) == IBM_INF ? DEC_INFINITE : DEC_QUIET,
            (special & IBM_SIGN) != 0, words
        );
        return;
    }
    sig_x = dec_double_sig(bits.high, &e_x);
    sig_y = dec_double_sig(bits.low, &e_y);
    base = sig_y == 0 || (sig_x != 0 && e_x < e_y) ? e_x : e_y;
    dec_big_set(x, DEC_IBM_SUM_LIMBS, sig_x, sig_x == 0 ? 0 : (size_t)(e_x - base));
    dec_big_set(y, DEC_IBM_SUM_LIMBS, sig_y, sig_y == 0 ? 0 : (size_t)(e_y - base));
    if (first_negative == second_negative) {
        uint32_t carry = 0;

        for (size_t i = 0; i < DEC_IBM_SUM_LIMBS; i++) {
            uint64_t total = (uint64_t)x[i] + y[i] + carry;

            x[i] = (uint32_t)total;
            carry = (uint32_t)(total >> 32);
        }
    } else {
        int order = dec_order(x, y, DEC_IBM_SUM_LIMBS);

        if (order < 0) {
            dec_big_subtract(y, DEC_IBM_SUM_LIMBS, x, DEC_IBM_SUM_LIMBS);
            sum = y;
            negative = second_negative;
        } else if (order > 0) {
            dec_big_subtract(x, DEC_IBM_SUM_LIMBS, y, DEC_IBM_SUM_LIMBS);
        } else {
            for (size_t i = 0; i < DEC_IBM_SUM_LIMBS; i++) {
                x[i] = 0;
            }
            negative = sig_x == 0 && first_negative;
        }
    }
    dec_from_binary(value, sum, DEC_IBM_SUM_LIMBS, base, negative, words, work, half);
}

// Workaround: GCC 7, SPE: at -O2 and -O3, a value of this type passed on to a
// function that is not inlined can lose a word of its second double.
__attribute__((__always_inline__)) static inline void dec_from_ibm(
    void *value,
    ibm_value a,
    size_t words,
    uint32_t *work,
    size_t half
) {
    dec_from_ibm_bits(value, ibm_to_bits(a), words, work, half);
}

// What is left of a finite number c * 10^q beside a first double h * 2^g,
// rounded to a double. Over 5^-q where q is negative, the difference of two
// integers is that of c and h, each with its power of 5 and of 2, down to 2^w.
static uint64_t dec_ibm_rest(
    uint64_t first,
    const void *value,
    size_t words,
    uint32_t *work,
    size_t half
) {
    struct dec d;
    uint32_t x[DEC_IBM_REST_LIMBS];
    uint32_t y[DEC_IBM_REST_LIMBS];
    uint32_t t[DEC_IBM_REST_LIMBS];
    uint32_t bits[4];
    const uint32_t *rest = x;
    uint64_t sign = first & IBM_SIGN;
    int32_t g;
    uint64_t h = dec_double_sig(first, &g);
    int32_t q;
    int32_t w;
    size_t power;
    size_t n;
    int order;

    dec_unpack(&d, value, words);
    dec_coefficient_bits(bits, &d);
    q = d.exponent;
    w = q < g ? q : g;
    power = q < 0 ? (size_t)-q : 0;
    for (size_t i = 0; i < 4; i++) {
        t[i] = bits[i];
    }
    n = dec_big_times_5(t, 4, q < 0 ? 0 : (size_t)q);
    dec_big_take(x, DEC_IBM_REST_LIMBS, t, n, w - q);
    t[0] = (uint32_t)h;
    t[1] = (uint32_t)(h >> 32);
    n = dec_big_times_5(t, 2, power);
    dec_big_take(y, DEC_IBM_REST_LIMBS, t, n, w - g);
    order = dec_order(x, y, DEC_IBM_REST_LIMBS);
    if (order == 0) {
        return 0;
    }
    if (order < 0) {
        dec_big_subtract(y, DEC_IBM_REST_LIMBS, x, DEC_IBM_REST_LIMBS);
        rest = y;
        sign ^= IBM_SIGN;
    } else {
        dec_big_subtract(x, DEC_IBM_REST_LIMBS, y, DEC_IBM_REST_LIMBS);
    }
    w += dec_big_top_bits(bits, 56, rest, DEC_IBM_REST_LIMBS, power, work, half);
    return df_round_pack(
        sign, (unsigned int)(w + FP_BIAS(11) + 52 + 3), (uint64_t)bits[1] << 32 | bits[0]
    );
}

static ibm_value dec_to_ibm(const void *value, size_t words, uint32_t *work, size_t half) {
    uint32_t y[4];
    int32_t e = 0;
    bool negative;
    int kind = dec_to_binary(y, 56, &e, &negative, value, words, 1024, -1074, work, half);
    uint64_t first = negative ? IBM_SIGN : 0;
    uint64_t second = 0;

    if (kind == DEC_INFINITE) {
        first |= IBM_INF;
    } else if (kind == DEC_QUIET) {
        first |= IBM_NAN;
    } else if (kind == DEC_FINITE) {
        uint64_t mask = IBM_SIGN - 1;

        first = df_round_pack(
            first, (unsigned int)(e + FP_BIAS(11) + 52 + 3), (uint64_t)y[1] << 32 | y[0]
        );
        if ((first & mask) != 0 && (first & mask) < IBM_INF) {
            second = dec_ibm_rest(first, value, words, work, half);
        }
    }
    return ibm_from_bits(ibm_make(first, second));
}

DEC_FROM_ALL(trunctfsd, trunctfdd, extendtftd, ibm, ibm_value, DEC_IBM_SUM_BITS, 1024, -1074)
DEC_TO_ALL(extendsdtf, extendddtf, trunctdtf, ibm, ibm_value, 128, 1024, -1074)

#endif // HAS_IBM_128

#if BITINT_GCC

// The integer part of a number into a result of the file's other conversions
// to _BitInt: a NaN, what is below 1, and a negative value in an unsigned type
// give 0, and what does not fit saturates.
static void dec_to_bitint(
    lgrt_limb *r,
    int32_t rprec,
    const void *value,
    size_t words,
    uint32_t *work
) {
    struct dec x;
    int32_t bits = (int32_t)bitint_bits(rprec);
    size_t rn = bitint_limbs(rprec);
    int32_t digits;
    int32_t top;
    int32_t length;
    size_t n;

    dec_unpack(&x, value, words);
    digits = (int32_t)dec_digits(x.coefficient, DEC_LIMBS);
    top = x.exponent + digits;
    if (x.kind >= DEC_QUIET || (x.negative && rprec > 0)
     || (x.kind == DEC_FINITE && (digits == 0 || top <= 0))) {
        bitint_clear(r, rprec);
        return;
    }
    if (x.kind == DEC_INFINITE || (top - 1) * 3321 / 1000 >= bits) {
        bitint_saturate(r, rprec, x.negative);
        return;
    }
    if (x.exponent < 0) {
        dec_scale_down(x.coefficient, DEC_LIMBS, (size_t)-x.exponent);
        x.exponent = 0;
    }
    dec_coefficient_bits(work, &x);
    n = dec_big_times_5(work, 4, (size_t)x.exponent);
    length = (int32_t)dec_big_length(work, n) + x.exponent;
    if (length > bits || (rprec < 0 && length == bits)) {
        bitint_saturate(r, rprec, x.negative);
        return;
    }
    bitint_clear(r, rprec);
    for (size_t i = 0; i < n; i++) {
        bitint_set_bits(r, rn, (size_t)x.exponent + 32 * i, work[i]);
    }
    if (x.negative) {
        bitint_negate(r, rn);
    }
    r[LIMB_AT(rn, rn - 1)] = bitint_extend(r[LIMB_AT(rn, rn - 1)], rprec, rprec < 0);
}

// An operand of more limbs than m, given by the largest value that does not
// overflow, overflows.
static void dec_from_bitint(
    void *value,
    const lgrt_limb *i,
    int32_t iprec,
    size_t words,
    uint32_t *m,
    size_t capacity,
    uint32_t *work,
    size_t half
) {
    struct bitint x;
    size_t n = 0;

    bitint_load(&x, i, iprec);
    if (x.count != 0 && bitint_length(&x) > 32 * capacity) {
        dec_special(value, DEC_INFINITE, x.negative, words);
        return;
    }
    for (size_t limb = 0; limb < x.count; limb++) {
        lgrt_limb magnitude = bitint_magnitude(&x, limb);

        for (size_t j = 0; j < LIMB_BITS / 32 && n < capacity; j++) {
            m[n] = (uint32_t)(magnitude >> (32 * j));
            n += 1;
        }
    }
    dec_from_binary(value, m, n, 0, x.negative, words, work, half);
}

#define DEC_BITINT_LIMBS(emax) (((emax) + 1) * 3322 / 1000 / 32 + 2)

#define DEC_BITINT(fmt, T, words, emax) \
    void DEC_NAME(fix##fmt##bitint)(lgrt_limb *r, int32_t rprec, T a) { \
        uint32_t work[DEC_HALF(0, 20416, 0, words)]; \
        \
        dec_to_bitint(r, rprec, &a, words, work); \
    } \
    \
    DEC_RETURN T DEC_NAME(floatbitint##fmt)(const lgrt_limb *i, int32_t iprec) { \
        uint32_t m[DEC_BITINT_LIMBS(emax)]; \
        uint32_t work[2 * DEC_HALF(128, 20416, 0, words)]; \
        T r; \
        \
        dec_from_bitint( \
            &r, i, iprec, words, m, DEC_BITINT_LIMBS(emax), work, DEC_HALF(128, 20416, 0, words) \
        ); \
        return r; \
    }

DEC_BITINT(sd, sd_value, 1, 96)
DEC_BITINT(dd, dd_value, 2, 384)
DEC_BITINT(td, td_value, 4, 6144)

#endif // BITINT_GCC

#endif // defined(DEC_NAME) && LGRT_SOFT_FLOAT

// The atomic routines need the atomic instructions of the target, and nothing
// but them: neither the help of an operating system, nor masked interrupts. So
// they exist only where the compiler implements pointer-sized atomics inline
// with such instructions. Where it gets those wrong, WORD_CAS stands in for
// them: a compare-exchange of aligned words, on which the accesses of up to 4
// bytes are lock-free, so that they are atomic with respect to the loads and
// stores that the compilers inline.
#if defined(__i386__) && !defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_4)
// No compare-exchange on the 80386, where Clang uses it all the same.
#   define NO_ATOMICS 1
#elif defined(__arm__) \
   && (!defined(__ARM_ARCH) || __ARM_ARCH < 6 \
    || (defined(__thumb__) && !defined(__thumb2__) && __ARM_ARCH < 8))
// No exclusive loads and stores before ARMv6, or in Thumb-1 before ARMv8-M
// Baseline.
#   define NO_ATOMICS 1
#elif defined(__arm__) \
   && ((defined(__clang__) && defined(__ARM_FEATURE_LDREX) && (__ARM_FEATURE_LDREX & 1) == 0) \
    || (!defined(__clang__) && defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_4) \
     && !defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_1)))
// Workaround: ARMv6 without K: Clang uses the byte, halfword, and doubleword
// exclusives that ARMv6K added, and GCC may turn byte and halfword atomics
// into calls to the __sync routines, which are built on them.
#   define WORD_CAS 1
#elif defined(__sparc__) && !defined(__arch64__) && !defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_4)
// No compare-exchange before SPARC V9.
#   define NO_ATOMICS 1
#elif defined(__hppa__)
// No compare-exchange on PA-RISC, where GCC implements even the __atomic
// builtins with calls to __sync routines.
#   define NO_ATOMICS 1
#elif defined(__sh__) && !defined(__SH_ATOMIC_MODEL_HARD_LLCS__)
// Only the movli.l and movco.l of SH4A are such instructions: the other atomic
// models of GCC rely on the kernel, or on masked interrupts.
#   define NO_ATOMICS 1
#elif defined(__mips) && __mips == 1
// No ll and sc on MIPS I, which GCC uses all the same, for kernels to fake.
#   define NO_ATOMICS 1
#elif defined(__loongarch__) && defined(__loongarch_grlen) && __loongarch_grlen == 32 \
   && !(defined(__clang__) && __clang_major__ >= 21)
// Workaround: GCC, and Clang before 21, 32-bit LoongArch: they get atomics
// wrong.
#   define WORD_CAS 1
#elif !defined(__clang__) && defined(__MICROBLAZE__)
// Workaround: GCC (16 at least), MicroBlaze: its 4-byte compare-exchange takes
// two words that differ in their top bit alone for equal where the one it
// finds has that bit set, as the cmp it compares them with puts the signed
// comparison in that bit. Before 14.4, and in 15.1 and 15.2, it also gives
// back the comparison it makes, which is 0 where it succeeds, for its result.
// So the exchanges, the other read-modify-write operations, and test-and-set
// it builds on it, and those of 1 and 2 bytes, get wrong values.
#   define WORD_CAS 1
#elif !defined(__clang__) && !defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_4)
// What GCC claims to be lock-free without that, it calls __sync routines for.
#   define NO_ATOMICS 1
#elif defined(__mips16)
// No ll and sc in MIPS16 code, where GCC calls __sync routines for its atomics
// all the same.
#   define NO_ATOMICS 1
#elif !defined(__GCC_ATOMIC_POINTER_LOCK_FREE) || __GCC_ATOMIC_POINTER_LOCK_FREE != 2
#   define NO_ATOMICS 1
#endif // defined(__i386__) && !defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_4)

#if !defined(WORD_CAS)
#   define WORD_CAS 0
#endif

#if defined(NO_ATOMICS)
#   define HAS_ATOMICS 0
#else
#   define HAS_ATOMICS 1
#endif

#if HAS_ATOMICS

// Compilers reserve the names of the atomic routines for their builtins, so
// the routines have other names in C and get theirs from asm labels.
#define ASM_LABEL(name) __asm__ (XSTR(__USER_LABEL_PREFIX__) #name)

// Clang turns atomic builtins on types aligned below their size, such as
// 64-bit integers on IA-32, into calls to the routines below, so the builtins
// operate on these types instead. The objects are of any type, which these may
// alias.
#define ATOMIC_TYPE(n) __attribute__((__aligned__(n), __may_alias__))

typedef uint16_t atomic_u16 ATOMIC_TYPE(2);
typedef uint32_t atomic_u32 ATOMIC_TYPE(4);
typedef uint64_t atomic_u64 ATOMIC_TYPE(8);
#if HAS_INT128
typedef u128 atomic_u128 ATOMIC_TYPE(16);
#endif
typedef uintptr_t lock_word __attribute__((__aligned__(sizeof(uintptr_t))));

// Objects that are not lock-free are accessed under a lock chosen by hashing
// their address: the lowest bits rarely tell objects apart, so they are
// dropped, and higher ones are folded in.
#define LOCK_BITS 9
#define LOCK_COUNT ((size_t)1 << LOCK_BITS)

static lock_word locks[LOCK_COUNT];

static inline lock_word *lock_of(const volatile void *ptr) {
    uintptr_t h = (uintptr_t)ptr >> 3;

    h ^= h >> LOCK_BITS;
    h ^= h >> (2 * LOCK_BITS);
    return &locks[h & (LOCK_COUNT - 1)];
}

#if WORD_CAS

static inline void fence(void) {
    __atomic_thread_fence(__ATOMIC_SEQ_CST);
}

// The compare-exchange of an aligned word, which gives back what it found.
#if defined(__arm__)

static inline uint32_t word_cas(volatile atomic_u32 *word, uint32_t expected, uint32_t desired) {
    __atomic_compare_exchange_n(
        word, &expected, desired, false, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST
    );
    return expected;
}

#elif defined(__loongarch__)

static inline uint32_t word_cas(volatile atomic_u32 *word, uint32_t expected, uint32_t desired) {
    uint32_t found;
    uint32_t stored;

    __asm__ volatile (
        "1:\n\t"
        "ll.w %0, %2, 0\n\t"
        "bne %0, %3, 2f\n\t"
        "move %1, %4\n\t"
        "sc.w %1, %2, 0\n\t"
        "beqz %1, 1b\n\t"
        "2:\n\t"
        "dbar 0"
        : "=&r"(found), "=&r"(stored)
        : "r"(word), "r"(expected), "r"(desired)
        : "memory"
    );
    return found;
}

#elif defined(__MICROBLAZE__)

static inline uint32_t word_cas(volatile atomic_u32 *word, uint32_t expected, uint32_t desired) {
    uint32_t found;
    uint32_t c;

    __asm__ volatile (
        "addc r0, r0, r0\n\t"
        "1:\n\t"
        "lwx %0, %2, r0\n\t"
        "addic %1, r0, 0\n\t"
        "bnei %1, 1b\n\t"
        "xor %1, %0, %3\n\t"
        "bnei %1, 2f\n\t"
        "swx %4, %2, r0\n\t"
        "addic %1, r0, 0\n\t"
        "bnei %1, 1b\n\t"
        "2:"
        : "=&r"(found), "=&r"(c)
        : "r"(word), "r"(expected), "r"(desired)
        : "cc", "memory"
    );
    return found;
}

#endif // defined(__arm__)

#endif // WORD_CAS

static inline void lgrt_lock(lock_word *lock) {
#if WORD_CAS
    while (word_cas((volatile atomic_u32 *)lock, 0, 1) != 0) {
        while (*(volatile lock_word *)lock != 0) {}
    }
#else
    while (__atomic_exchange_n(lock, 1, __ATOMIC_ACQUIRE) != 0) {
        while (__atomic_load_n(lock, __ATOMIC_RELAXED) != 0) {}
    }
#endif
}

static inline void unlock(lock_word *lock) {
#if WORD_CAS
    fence();
    *(volatile lock_word *)lock = 0;
#else
    __atomic_store_n(lock, 0, __ATOMIC_RELEASE);
#endif
}

// An object of n bytes, for n of 1, 2, 4, 8, and 16, is accessed lock-free
// when LOCK_FREE(n) holds and the object is aligned to n. Every builtin on n
// bytes sits under a plain if on that constant, so that it vanishes where the
// constant is false instead of compiling into a call to the routine containing
// it. On words, those of up to 4 bytes are the only ones that need no lock.
//
// Workaround: GCC 5 and 6, 32-bit ARM without doubleword exclusives; Clang
// before 9, 80486: they claim that 8-byte objects are always lock-free where
// they are not, GCC calling __sync routines for them and Clang using the
// cmpxchg8b that the Pentium added, so LOCK_FREE(8) is false there.
#if WORD_CAS
#   define LOCK_FREE(n) ((n) <= 4)
#elif (defined(__arm__) && !(defined(__ARM_FEATURE_LDREX) && (__ARM_FEATURE_LDREX & 8) != 0)) \
   || (defined(__i386__) && !defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_8))
#   define LOCK_FREE(n) ((n) != 8 && __atomic_always_lock_free(n, 0))
#else
#   define LOCK_FREE(n) (__atomic_always_lock_free(n, 0))
#endif

static inline bool aligned(const volatile void *ptr, size_t n) {
    return ((uintptr_t)ptr & (n - 1)) == 0;
}

// Buffers other than the objects are not shared, but may be misaligned, so
// they are copied with copy. When optimising for size, Clang turns misaligned
// word accesses into calls to __aeabi_uread4 and friends on ARM without
// unaligned accesses, so there copy copies bytes, through volatile loads that
// it cannot merge into words.
#if defined(__clang__) && defined(__arm__) && !defined(__ARM_FEATURE_UNALIGNED)
static inline void copy(void *dest, const void *src, size_t n) {
    unsigned char *d = dest;
    const volatile unsigned char *s = src;
    size_t i;

    for (i = 0; i < n; i++) {
        d[i] = s[i];
    }
}
#else
static inline void copy(void *dest, const void *src, size_t n) {
    __builtin_memcpy(dest, src, n);
}
#endif

// An object under its lock may be volatile, which only a volatile access may
// touch, so these go by bytes. The objects are of any type, which bytes alias.
static inline void load_bytes(void *dest, const volatile void *object, size_t n) {
    unsigned char *d = dest;
    const volatile unsigned char *o = object;
    size_t i;

    for (i = 0; i < n; i++) {
        d[i] = o[i];
    }
}

static inline void store_bytes(volatile void *object, const void *src, size_t n) {
    volatile unsigned char *o = object;
    const unsigned char *s = src;
    size_t i;

    for (i = 0; i < n; i++) {
        o[i] = s[i];
    }
}

static inline bool same_bytes(const volatile void *object, const void *buffer, size_t n) {
    const volatile unsigned char *o = object;
    const unsigned char *b = buffer;
    size_t i;

    for (i = 0; i < n; i++) {
        if (o[i] != b[i]) {
            return false;
        }
    }
    return true;
}

#if !defined(__clang__) && defined(__sparc__) && !defined(__arch64__)
// GCC for 32-bit SPARC has the 8-byte loads and stores inline, as one
// instruction each, without the lock, so those under the lock are one
// instruction too, for the others not to see a value partly written.
#define COPY_WHOLE_8 1
static inline void load_object(void *dest, const volatile void *object, size_t n) {
    if (n == 8 && aligned(object, 8)) {
        uint64_t v = *(const volatile atomic_u64 *)object;

        copy(dest, &v, 8);
        return;
    }
    load_bytes(dest, object, n);
}

static inline void store_object(volatile void *object, const void *src, size_t n) {
    if (n == 8 && aligned(object, 8)) {
        uint64_t v;

        copy(&v, src, 8);
        *(volatile atomic_u64 *)object = v;
        return;
    }
    store_bytes(object, src, n);
}
#else // !defined(__clang__) && defined(__sparc__) && !defined(__arch64__)
static inline void load_object(void *dest, const volatile void *object, size_t n) {
    load_bytes(dest, object, n);
}

static inline void store_object(volatile void *object, const void *src, size_t n) {
    store_bytes(object, src, n);
}
#endif // !defined(__clang__) && defined(__sparc__) && !defined(__arch64__)

#if WORD_CAS
// The compare-exchange of the n bytes at ptr, of up to 4, on the aligned word
// they are in, which writes what it found to expected where it fails.
static inline bool word_compare_exchange(
    volatile void *ptr,
    size_t n,
    void *expected,
    const void *desired
) {
    uintptr_t at = (uintptr_t)ptr & 3;
    volatile atomic_u32 *word = (volatile atomic_u32 *)((uintptr_t)ptr - at);
    uint32_t found = *word;

    for (;;) {
        uint32_t want = found;
        uint32_t next = found;
        uint32_t seen;

        copy((unsigned char *)&want + at, expected, n);
        if (want != found) {
            copy(expected, (unsigned char *)&found + at, n);
            return false;
        }
        copy((unsigned char *)&next + at, desired, n);
        seen = word_cas(word, found, next);
        if (seen == found) {
            return true;
        }
        found = seen;
    }
}

// The exchange of the n bytes at ptr, of up to 4, which writes what it found
// to old.
static inline void word_exchange(volatile void *ptr, size_t n, const void *val, void *old) {
    load_bytes(old, ptr, n);
    while (!word_compare_exchange(ptr, n, old, val)) {}
}

// Aligned loads and stores of up to 4 bytes are atomic by themselves. The load
// that gives fenced its argument comes before the call, so before the fence.
static inline uint32_t fenced(uint32_t value) {
    fence();
    return value;
}

#define ATOMIC_LOAD(T, p, model) ((void)(model), (T)fenced(*(const volatile T *)(p)))
#define ATOMIC_STORE(p, val, model) do { \
    __typeof__(p) ATOMIC_STORE_p = (p); \
    __typeof__(val) ATOMIC_STORE_val = (val); \
    __typeof__(model) ATOMIC_STORE_model = (model); \
    \
    (void)ATOMIC_STORE_model; \
    fence(); \
    *ATOMIC_STORE_p = ATOMIC_STORE_val; \
    fence(); \
} while (0)
#else // WORD_CAS
#define ATOMIC_LOAD(T, p, model) __atomic_load_n((const volatile T *)(p), model)
#define ATOMIC_STORE(p, val, model) __atomic_store_n(p, val, model)
#endif // WORD_CAS

static inline void locked_load(size_t size, const volatile void *src, void *dest) {
    lock_word *lock = lock_of(src);

    lgrt_lock(lock);
    load_object(dest, src, size);
    unlock(lock);
}

static inline void locked_store(size_t size, volatile void *dest, const void *src) {
    lock_word *lock = lock_of(dest);

    lgrt_lock(lock);
    store_object(dest, src, size);
    unlock(lock);
}

static inline void locked_exchange(size_t size, volatile void *ptr, const void *val, void *old) {
    lock_word *lock = lock_of(ptr);

    lgrt_lock(lock);
    // Callers may pass one buffer as both val and old, whose bytes are then
    // swapped.
    if (val != old) {
        load_object(old, ptr, size);
        store_object(ptr, val, size);
#if defined(COPY_WHOLE_8)
    } else if (size == 8) {
        uint64_t t;

        load_object(&t, ptr, 8);
        store_object(ptr, val, 8);
        copy(old, &t, 8);
#endif
    } else {
        volatile unsigned char *p = ptr;
        unsigned char *o = old;
        size_t i;

        for (i = 0; i < size; i++) {
            unsigned char t = p[i];

            p[i] = o[i];
            o[i] = t;
        }
    }
    unlock(lock);
}

static inline bool locked_compare_exchange(
    size_t size,
    volatile void *ptr,
    void *expected,
    const void *desired
) {
    lock_word *lock = lock_of(ptr);
    bool equal;

    lgrt_lock(lock);
    equal = same_bytes(ptr, expected, size);
    if (equal) {
        store_object(ptr, desired, size);
    } else {
        load_object(expected, ptr, size);
    }
    unlock(lock);
    return equal;
}

#if HAS_INT128 && defined(__s390x__) && !defined(__clang__)

// Workaround: GCC, s390x: it compiles 16-byte atomic builtins into library
// calls, that is, into calls to the routines below, so the 16-byte helpers
// further down use these instead. lpq, stpq, and cdsg access aligned quadwords
// atomically, through the even/odd register pairs in which GCC holds 128-bit
// values. Only loads may pass earlier stores on s390x, which the serialisation
// after sequentially consistent stores prevents, and cdsg serialises, so no
// memory order needs more.
#define S390X_ASM_16 1

static inline u128 s390x_load_16(const volatile void *ptr, int model) {
    const volatile atomic_u128 *p = ptr;
    u128 v;

    (void)model;
    __asm__ volatile ("lpq %0,%1" : "=d"(v) : "Q"(*p) : "memory");
    return v;
}

static inline void s390x_store_16(volatile void *ptr, u128 val, int model) {
    volatile atomic_u128 *p = ptr;

    if (model == __ATOMIC_SEQ_CST) {
        __asm__ volatile (
            "stpq %1,%0\n\t"
            "bcr 15,0"
            : "=Q"(*p)
            : "d"(val)
            : "memory"
        );
    } else {
        __asm__ volatile ("stpq %1,%0" : "=Q"(*p) : "d"(val) : "memory");
    }
}

// The cdsg instruction sets condition code 0 when it stores desired, and
// otherwise loads the quadword into the pair that held expected.
static inline bool s390x_compare_exchange_16(
    volatile void *ptr,
    u128 *expected,
    u128 desired,
    int success,
    int failure
) {
    volatile atomic_u128 *p = ptr;
    u128 e = *expected;
    int cc;

    (void)success;
    (void)failure;
    __asm__ volatile (
        "cdsg %0,%3,%1\n\t"
        "ipm %2\n\t"
        "srl %2,28"
        : "+d"(e), "+Q"(*p), "=d"(cc)
        : "d"(desired)
        : "cc", "memory"
    );
    *expected = e;
    return cc == 0;
}

#else // HAS_INT128 && defined(__s390x__) && !defined(__clang__)
#define S390X_ASM_16 0
#endif // HAS_INT128 && defined(__s390x__) && !defined(__clang__)

#if HAS_INT128 && defined(__aarch64__) && defined(__clang__) \
 && (__clang_major__ < 8 || (__clang_major__ < 23 && defined(__AARCH64EB__)))

// Workaround: Clang before 8, AArch64 with LSE; Clang before 23, big-endian
// AArch64: in 16-byte atomics, the first uses casp on odd registers or gets
// its success flag wrong, without defining a macro that tells whether LSE is
// enabled, and the second swaps the halves of the values it stores. There, the
// 16-byte helpers below use this file's own compare-and-swap routines, defined
// further on, picking the one whose ordering covers both memory orders: an
// order acquires unless it is relaxed or release, and releases unless it is
// relaxed, consume, or acquire.
#define AARCH64_CAS_16 1

u128 __aarch64_cas16_relax(u128 expected, u128 desired, volatile void *ptr);
u128 __aarch64_cas16_acq(u128 expected, u128 desired, volatile void *ptr);
u128 __aarch64_cas16_rel(u128 expected, u128 desired, volatile void *ptr);
u128 __aarch64_cas16_acq_rel(u128 expected, u128 desired, volatile void *ptr);

// Returns the value read, which equals expected exactly when desired was
// stored.
static inline u128 aarch64_cas_16(
    volatile void *ptr,
    u128 expected,
    u128 desired,
    int success,
    int failure
) {
    bool acquire = (success != __ATOMIC_RELAXED && success != __ATOMIC_RELEASE)
                || (failure != __ATOMIC_RELAXED && failure != __ATOMIC_RELEASE);
    bool release = success != __ATOMIC_RELAXED && success != __ATOMIC_CONSUME
                && success != __ATOMIC_ACQUIRE;

    if (acquire && release) {
        return __aarch64_cas16_acq_rel(expected, desired, ptr);
    }
    if (acquire) {
        return __aarch64_cas16_acq(expected, desired, ptr);
    }
    if (release) {
        return __aarch64_cas16_rel(expected, desired, ptr);
    }
    return __aarch64_cas16_relax(expected, desired, ptr);
}

#else // HAS_INT128 && defined(__aarch64__) && defined(__clang__) && (__clang_major__ < 8 || (__clang_major__ < 23 && defined(__AARCH64EB__)))
#define AARCH64_CAS_16 0
#endif // HAS_INT128 && defined(__aarch64__) && defined(__clang__) && (__clang_major__ < 8 || (__clang_major__ < 23 && defined(__AARCH64EB__)))

// Where ATOMIC_HELPERS_16 is 1, the 16-byte atomic builtins cannot be used,
// and lock-free 16-byte objects are accessed with these helpers instead. They
// take the builtins' memory orders, and compare_exchange_16 stores the value
// it read in expected when it fails. On AArch64, a load is a compare-exchange
// of 0 with 0, which returns the value and, if it is 0, writes it back
// unchanged.
#if S390X_ASM_16 || AARCH64_CAS_16
#define ATOMIC_HELPERS_16 1

static inline u128 load_16(const volatile void *ptr, int model) {
#if S390X_ASM_16
    return s390x_load_16(ptr, model);
#else
    return aarch64_cas_16((volatile void *)ptr, 0, 0, model, model);
#endif
}

static inline bool compare_exchange_16(
    volatile void *ptr,
    u128 *expected,
    u128 desired,
    int success,
    int failure
) {
#if S390X_ASM_16
    return s390x_compare_exchange_16(ptr, expected, desired, success, failure);
#else
    u128 e = *expected;

    *expected = aarch64_cas_16(ptr, e, desired, success, failure);
    return *expected == e;
#endif
}

static inline u128 exchange_16(volatile void *ptr, u128 val, int model) {
    u128 old = load_16(ptr, __ATOMIC_RELAXED);
    bool done;

    do {
        done = compare_exchange_16(ptr, &old, val, model, __ATOMIC_RELAXED);
    } while (!done);
    return old;
}

static inline void store_16(volatile void *ptr, u128 val, int model) {
#if S390X_ASM_16
    s390x_store_16(ptr, val, model);
#else
    exchange_16(ptr, val, model);
#endif
}

#else // S390X_ASM_16 || AARCH64_CAS_16
#define ATOMIC_HELPERS_16 0
#endif // S390X_ASM_16 || AARCH64_CAS_16

bool atomic_is_lock_free(size_t size, void *ptr) ASM_LABEL(__atomic_is_lock_free);
bool atomic_is_lock_free(size_t size, void *ptr) {
    if (LOCK_FREE(1)) {
        if (size == 1) {
            return true;
        }
    }
    if (LOCK_FREE(2)) {
        if (size == 2) {
            return aligned(ptr, 2);
        }
    }
    if (LOCK_FREE(4)) {
        if (size == 4) {
            return aligned(ptr, 4);
        }
    }
    if (LOCK_FREE(8)) {
        if (size == 8) {
            return aligned(ptr, 8);
        }
    }
#if HAS_INT128
    if (LOCK_FREE(16)) {
        if (size == 16) {
            return aligned(ptr, 16);
        }
    }
#endif
    return false;
}

// The generic routines leave lock-free objects to the sized routines, declared
// here and defined after them.
//
// Workaround: GCC before 8, SuperH: at -O3, it cannot allocate registers for
// the atomic sequences of several sizes in one function, so the sized routines
// are not inlined there.
#if !defined(__clang__) && defined(__sh__) && __GNUC__ < 8
#   define SIZED_NOINLINE __attribute__((__noinline__))
#else
#   define SIZED_NOINLINE
#endif

uint8_t atomic_load_1(
    const volatile void *ptr,
    int model
) ASM_LABEL(__atomic_load_1) SIZED_NOINLINE;
uint16_t atomic_load_2(
    const volatile void *ptr,
    int model
) ASM_LABEL(__atomic_load_2) SIZED_NOINLINE;
uint32_t atomic_load_4(
    const volatile void *ptr,
    int model
) ASM_LABEL(__atomic_load_4) SIZED_NOINLINE;
uint64_t atomic_load_8(
    const volatile void *ptr,
    int model
) ASM_LABEL(__atomic_load_8) SIZED_NOINLINE;
#if HAS_INT128
u128 atomic_load_16(
    const volatile void *ptr,
    int model
) ASM_LABEL(__atomic_load_16) SIZED_NOINLINE;
#endif

void atomic_store_1(
    volatile void *ptr,
    uint8_t val,
    int model
) ASM_LABEL(__atomic_store_1) SIZED_NOINLINE;
void atomic_store_2(
    volatile void *ptr,
    uint16_t val,
    int model
) ASM_LABEL(__atomic_store_2) SIZED_NOINLINE;
void atomic_store_4(
    volatile void *ptr,
    uint32_t val,
    int model
) ASM_LABEL(__atomic_store_4) SIZED_NOINLINE;
void atomic_store_8(
    volatile void *ptr,
    uint64_t val,
    int model
) ASM_LABEL(__atomic_store_8) SIZED_NOINLINE;
#if HAS_INT128
void atomic_store_16(
    volatile void *ptr,
    u128 val,
    int model
) ASM_LABEL(__atomic_store_16) SIZED_NOINLINE;
#endif

uint8_t atomic_exchange_1(
    volatile void *ptr,
    uint8_t val,
    int model
) ASM_LABEL(__atomic_exchange_1) SIZED_NOINLINE;
uint16_t atomic_exchange_2(
    volatile void *ptr,
    uint16_t val,
    int model
) ASM_LABEL(__atomic_exchange_2) SIZED_NOINLINE;
uint32_t atomic_exchange_4(
    volatile void *ptr,
    uint32_t val,
    int model
) ASM_LABEL(__atomic_exchange_4) SIZED_NOINLINE;
uint64_t atomic_exchange_8(
    volatile void *ptr,
    uint64_t val,
    int model
) ASM_LABEL(__atomic_exchange_8) SIZED_NOINLINE;
#if HAS_INT128
u128 atomic_exchange_16(
    volatile void *ptr,
    u128 val,
    int model
) ASM_LABEL(__atomic_exchange_16) SIZED_NOINLINE;
#endif

bool atomic_compare_exchange_1(
    volatile void *ptr,
    void *expected,
    uint8_t desired,
    int success,
    int failure
) ASM_LABEL(__atomic_compare_exchange_1) SIZED_NOINLINE;
bool atomic_compare_exchange_2(
    volatile void *ptr,
    void *expected,
    uint16_t desired,
    int success,
    int failure
) ASM_LABEL(__atomic_compare_exchange_2) SIZED_NOINLINE;
bool atomic_compare_exchange_4(
    volatile void *ptr,
    void *expected,
    uint32_t desired,
    int success,
    int failure
) ASM_LABEL(__atomic_compare_exchange_4) SIZED_NOINLINE;
bool atomic_compare_exchange_8(
    volatile void *ptr,
    void *expected,
    uint64_t desired,
    int success,
    int failure
) ASM_LABEL(__atomic_compare_exchange_8) SIZED_NOINLINE;
#if HAS_INT128
bool atomic_compare_exchange_16(
    volatile void *ptr,
    void *expected,
    u128 desired,
    int success,
    int failure
) ASM_LABEL(__atomic_compare_exchange_16) SIZED_NOINLINE;
#endif

void atomic_load(size_t size, void *src, void *dest, int model) ASM_LABEL(__atomic_load);
void atomic_load(size_t size, void *src, void *dest, int model) {
    if (LOCK_FREE(1)) {
        if (size == 1) {
            uint8_t v = atomic_load_1(src, model);

            copy(dest, &v, 1);
            return;
        }
    }
    if (LOCK_FREE(2)) {
        if (size == 2 && aligned(src, 2)) {
            uint16_t v = atomic_load_2(src, model);

            copy(dest, &v, 2);
            return;
        }
    }
    if (LOCK_FREE(4)) {
        if (size == 4 && aligned(src, 4)) {
            uint32_t v = atomic_load_4(src, model);

            copy(dest, &v, 4);
            return;
        }
    }
    if (LOCK_FREE(8)) {
        if (size == 8 && aligned(src, 8)) {
            uint64_t v = atomic_load_8(src, model);

            copy(dest, &v, 8);
            return;
        }
    }
#if HAS_INT128
    if (LOCK_FREE(16)) {
        if (size == 16 && aligned(src, 16)) {
            u128 v = atomic_load_16(src, model);

            copy(dest, &v, 16);
            return;
        }
    }
#endif
    locked_load(size, src, dest);
}

void atomic_store(size_t size, void *dest, void *src, int model) ASM_LABEL(__atomic_store);
void atomic_store(size_t size, void *dest, void *src, int model) {
    if (LOCK_FREE(1)) {
        if (size == 1) {
            uint8_t v;

            copy(&v, src, 1);
            atomic_store_1(dest, v, model);
            return;
        }
    }
    if (LOCK_FREE(2)) {
        if (size == 2 && aligned(dest, 2)) {
            uint16_t v;

            copy(&v, src, 2);
            atomic_store_2(dest, v, model);
            return;
        }
    }
    if (LOCK_FREE(4)) {
        if (size == 4 && aligned(dest, 4)) {
            uint32_t v;

            copy(&v, src, 4);
            atomic_store_4(dest, v, model);
            return;
        }
    }
    if (LOCK_FREE(8)) {
        if (size == 8 && aligned(dest, 8)) {
            uint64_t v;

            copy(&v, src, 8);
            atomic_store_8(dest, v, model);
            return;
        }
    }
#if HAS_INT128
    if (LOCK_FREE(16)) {
        if (size == 16 && aligned(dest, 16)) {
            u128 v;

            copy(&v, src, 16);
            atomic_store_16(dest, v, model);
            return;
        }
    }
#endif
    locked_store(size, dest, src);
}

void atomic_exchange(
    size_t size,
    void *ptr,
    void *val,
    void *old,
    int model
) ASM_LABEL(__atomic_exchange);
void atomic_exchange(size_t size, void *ptr, void *val, void *old, int model) {
    if (LOCK_FREE(1)) {
        if (size == 1) {
            uint8_t x;

            copy(&x, val, 1);
            x = atomic_exchange_1(ptr, x, model);
            copy(old, &x, 1);
            return;
        }
    }
    if (LOCK_FREE(2)) {
        if (size == 2 && aligned(ptr, 2)) {
            uint16_t x;

            copy(&x, val, 2);
            x = atomic_exchange_2(ptr, x, model);
            copy(old, &x, 2);
            return;
        }
    }
    if (LOCK_FREE(4)) {
        if (size == 4 && aligned(ptr, 4)) {
            uint32_t x;

            copy(&x, val, 4);
            x = atomic_exchange_4(ptr, x, model);
            copy(old, &x, 4);
            return;
        }
    }
    if (LOCK_FREE(8)) {
        if (size == 8 && aligned(ptr, 8)) {
            uint64_t x;

            copy(&x, val, 8);
            x = atomic_exchange_8(ptr, x, model);
            copy(old, &x, 8);
            return;
        }
    }
#if HAS_INT128
    if (LOCK_FREE(16)) {
        if (size == 16 && aligned(ptr, 16)) {
            u128 x;

            copy(&x, val, 16);
            x = atomic_exchange_16(ptr, x, model);
            copy(old, &x, 16);
            return;
        }
    }
#endif
    locked_exchange(size, ptr, val, old);
}

// Compilers drop the weak flag when they call these routines, so they are
// strong.
bool atomic_compare_exchange(
    size_t size,
    void *ptr,
    void *expected,
    void *desired,
    int success,
    int failure
) ASM_LABEL(__atomic_compare_exchange);
bool atomic_compare_exchange(
    size_t size,
    void *ptr,
    void *expected,
    void *desired,
    int success,
    int failure
) {
    if (LOCK_FREE(1)) {
        if (size == 1) {
            uint8_t d;

            copy(&d, desired, 1);
            return atomic_compare_exchange_1(ptr, expected, d, success, failure);
        }
    }
    if (LOCK_FREE(2)) {
        if (size == 2 && aligned(ptr, 2)) {
            uint16_t d;

            copy(&d, desired, 2);
            return atomic_compare_exchange_2(ptr, expected, d, success, failure);
        }
    }
    if (LOCK_FREE(4)) {
        if (size == 4 && aligned(ptr, 4)) {
            uint32_t d;

            copy(&d, desired, 4);
            return atomic_compare_exchange_4(ptr, expected, d, success, failure);
        }
    }
    if (LOCK_FREE(8)) {
        if (size == 8 && aligned(ptr, 8)) {
            uint64_t d;

            copy(&d, desired, 8);
            return atomic_compare_exchange_8(ptr, expected, d, success, failure);
        }
    }
#if HAS_INT128
    if (LOCK_FREE(16)) {
        if (size == 16 && aligned(ptr, 16)) {
            u128 d;

            copy(&d, desired, 16);
            return atomic_compare_exchange_16(ptr, expected, d, success, failure);
        }
    }
#endif
    return locked_compare_exchange(size, ptr, expected, desired);
}

uint8_t atomic_load_1(const volatile void *ptr, int model) {
    uint8_t v;

    if (LOCK_FREE(1)) {
        return ATOMIC_LOAD(uint8_t, ptr, model);
    }
    locked_load(1, ptr, &v);
    return v;
}

uint16_t atomic_load_2(const volatile void *ptr, int model) {
    uint16_t v;

    if (LOCK_FREE(2)) {
        if (aligned(ptr, 2)) {
            return ATOMIC_LOAD(atomic_u16, ptr, model);
        }
    }
    locked_load(2, ptr, &v);
    return v;
}

uint32_t atomic_load_4(const volatile void *ptr, int model) {
    uint32_t v;

    if (LOCK_FREE(4)) {
        if (aligned(ptr, 4)) {
            return ATOMIC_LOAD(atomic_u32, ptr, model);
        }
    }
    locked_load(4, ptr, &v);
    return v;
}

#if defined(__clang__) && __clang_major__ < 9 && defined(__i386__) && !defined(_SOFT_FLOAT) \
 && defined(FREESTANDING_LGRT_ENABLE_FLOAT)
// Workaround: Clang before 9, IA-32: it loads 8 bytes with cmpxchg8b, which
// writes, and so faults where the object is read-only, so there 8 bytes are
// loaded through the x87 instead, whose 8-byte loads are atomic, and exact for
// integers.
#define X87_LOAD_8 1

static inline uint64_t x87_load_8(const volatile void *ptr) {
    uint64_t v;

    __asm__ volatile (
        "fildll %1\n\t"
        "fistpll %0"
        : "=m"(v)
        : "m"(*(const volatile atomic_u64 *)ptr)
        : "memory"
    );
    return v;
}
#else // defined(__clang__) && __clang_major__ < 9 && defined(__i386__) && !defined(_SOFT_FLOAT) && defined(FREESTANDING_LGRT_ENABLE_FLOAT)
#define X87_LOAD_8 0
#endif // defined(__clang__) && __clang_major__ < 9 && defined(__i386__) && !defined(_SOFT_FLOAT) && defined(FREESTANDING_LGRT_ENABLE_FLOAT)

uint64_t atomic_load_8(const volatile void *ptr, int model) {
    uint64_t v;

    if (LOCK_FREE(8)) {
        if (aligned(ptr, 8)) {
#if X87_LOAD_8
            (void)model;
            return x87_load_8(ptr);
#else
            return __atomic_load_n((const volatile atomic_u64 *)ptr, model);
#endif
        }
    }
    locked_load(8, ptr, &v);
    return v;
}

#if HAS_INT128
u128 atomic_load_16(const volatile void *ptr, int model) {
    u128 v;

    if (LOCK_FREE(16)) {
        if (aligned(ptr, 16)) {
#if ATOMIC_HELPERS_16
            return load_16(ptr, model);
#else
            return __atomic_load_n((const volatile atomic_u128 *)ptr, model);
#endif
        }
    }
    locked_load(16, ptr, &v);
    return v;
}
#endif

void atomic_store_1(volatile void *ptr, uint8_t val, int model) {
    if (LOCK_FREE(1)) {
        ATOMIC_STORE((volatile uint8_t *)ptr, val, model);
        return;
    }
    locked_store(1, ptr, &val);
}

void atomic_store_2(volatile void *ptr, uint16_t val, int model) {
    if (LOCK_FREE(2)) {
        if (aligned(ptr, 2)) {
            ATOMIC_STORE((volatile atomic_u16 *)ptr, val, model);
            return;
        }
    }
    locked_store(2, ptr, &val);
}

void atomic_store_4(volatile void *ptr, uint32_t val, int model) {
    if (LOCK_FREE(4)) {
        if (aligned(ptr, 4)) {
            ATOMIC_STORE((volatile atomic_u32 *)ptr, val, model);
            return;
        }
    }
    locked_store(4, ptr, &val);
}

void atomic_store_8(volatile void *ptr, uint64_t val, int model) {
    if (LOCK_FREE(8)) {
        if (aligned(ptr, 8)) {
            __atomic_store_n((volatile atomic_u64 *)ptr, val, model);
            return;
        }
    }
    locked_store(8, ptr, &val);
}

#if HAS_INT128
void atomic_store_16(volatile void *ptr, u128 val, int model) {
    if (LOCK_FREE(16)) {
        if (aligned(ptr, 16)) {
#if ATOMIC_HELPERS_16
            store_16(ptr, val, model);
#else
            __atomic_store_n((volatile atomic_u128 *)ptr, val, model);
#endif
            return;
        }
    }
    locked_store(16, ptr, &val);
}
#endif

uint8_t atomic_exchange_1(volatile void *ptr, uint8_t val, int model) {
    uint8_t old;

    if (LOCK_FREE(1)) {
#if WORD_CAS
        (void)model;
        word_exchange(ptr, 1, &val, &old);
        return old;
#else
        return __atomic_exchange_n((volatile uint8_t *)ptr, val, model);
#endif
    }
    locked_exchange(1, ptr, &val, &old);
    return old;
}

uint16_t atomic_exchange_2(volatile void *ptr, uint16_t val, int model) {
    uint16_t old;

    if (LOCK_FREE(2)) {
        if (aligned(ptr, 2)) {
#if WORD_CAS
            (void)model;
            word_exchange(ptr, 2, &val, &old);
            return old;
#else
            return __atomic_exchange_n((volatile atomic_u16 *)ptr, val, model);
#endif
        }
    }
    locked_exchange(2, ptr, &val, &old);
    return old;
}

uint32_t atomic_exchange_4(volatile void *ptr, uint32_t val, int model) {
    uint32_t old;

    if (LOCK_FREE(4)) {
        if (aligned(ptr, 4)) {
#if WORD_CAS
            (void)model;
            word_exchange(ptr, 4, &val, &old);
            return old;
#else
            return __atomic_exchange_n((volatile atomic_u32 *)ptr, val, model);
#endif
        }
    }
    locked_exchange(4, ptr, &val, &old);
    return old;
}

uint64_t atomic_exchange_8(volatile void *ptr, uint64_t val, int model) {
    uint64_t old;

    if (LOCK_FREE(8)) {
        if (aligned(ptr, 8)) {
            return __atomic_exchange_n((volatile atomic_u64 *)ptr, val, model);
        }
    }
    locked_exchange(8, ptr, &val, &old);
    return old;
}

#if HAS_INT128
u128 atomic_exchange_16(volatile void *ptr, u128 val, int model) {
    u128 old;

    if (LOCK_FREE(16)) {
        if (aligned(ptr, 16)) {
#if ATOMIC_HELPERS_16
            return exchange_16(ptr, val, model);
#else
            return __atomic_exchange_n((volatile atomic_u128 *)ptr, val, model);
#endif
        }
    }
    locked_exchange(16, ptr, &val, &old);
    return old;
}
#endif

bool atomic_compare_exchange_1(
    volatile void *ptr,
    void *expected,
    uint8_t desired,
    int success,
    int failure
) {
    if (LOCK_FREE(1)) {
#if WORD_CAS
        (void)success;
        (void)failure;
        return word_compare_exchange(ptr, 1, expected, &desired);
#else
        volatile uint8_t *p = ptr;
        uint8_t e;
        bool ok;

        copy(&e, expected, 1);
        ok = __atomic_compare_exchange_n(p, &e, desired, false, success, failure);
        if (ok) {
            return true;
        }
        copy(expected, &e, 1);
        return false;
#endif
    }
    return locked_compare_exchange(1, ptr, expected, &desired);
}

bool atomic_compare_exchange_2(
    volatile void *ptr,
    void *expected,
    uint16_t desired,
    int success,
    int failure
) {
    if (LOCK_FREE(2)) {
        if (aligned(ptr, 2)) {
#if WORD_CAS
            (void)success;
            (void)failure;
            return word_compare_exchange(ptr, 2, expected, &desired);
#else
            volatile atomic_u16 *p = ptr;
            atomic_u16 e;
            bool ok;

            copy(&e, expected, 2);
            ok = __atomic_compare_exchange_n(p, &e, desired, false, success, failure);
            if (ok) {
                return true;
            }
            copy(expected, &e, 2);
            return false;
#endif
        }
    }
    return locked_compare_exchange(2, ptr, expected, &desired);
}

// Workaround: Clang before 10.0.1, 64-bit RISC-V: its 4-byte compare-exchanges
// compare the word they load, which is sign-extended, with the expected one as
// it comes, which may be zero-extended, and then report that they stored the
// value that they did not.
#if defined(__clang__) && defined(__riscv) && __riscv_xlen == 64 && defined(__riscv_atomic) \
 && (__clang_major__ < 10 || (__clang_major__ == 10 && __clang_patchlevel__ < 1))
#define RISCV64_CAS_4 1

// So this compares itself, on the aligned 8 bytes that hold the word, which
// are little-endian, and go through the compare-exchange that these get right.
static inline bool riscv64_compare_exchange_4(
    volatile void *ptr,
    void *expected,
    uint32_t desired
) {
    uintptr_t address = (uintptr_t)ptr;
    volatile atomic_u64 *whole = (volatile atomic_u64 *)(address & ~(uintptr_t)7);
    uint32_t shift = (uint32_t)(address & 4) * 8;
    uint64_t others = ~((uint64_t)UINT32_MAX << shift);
    uint64_t old = __atomic_load_n(whole, __ATOMIC_SEQ_CST);
    uint32_t e;

    copy(&e, expected, 4);
    for (;;) {
        uint32_t found = (uint32_t)(old >> shift);

        if (found != e) {
            copy(expected, &found, 4);
            return false;
        }
        bool exchanged = __atomic_compare_exchange_n(
            whole, &old, (old & others) | ((uint64_t)desired << shift), true, __ATOMIC_SEQ_CST,
            __ATOMIC_SEQ_CST
        );
        if (exchanged) {
            return true;
        }
    }
}
#else // defined(__clang__) && defined(__riscv) && __riscv_xlen == 64 && defined(__riscv_atomic) && (__clang_major__ < 10 || (__clang_major__ == 10 && __clang_patchlevel__ < 1))
#define RISCV64_CAS_4 0
#endif // defined(__clang__) && defined(__riscv) && __riscv_xlen == 64 && defined(__riscv_atomic) && (__clang_major__ < 10 || (__clang_major__ == 10 && __clang_patchlevel__ < 1))

bool atomic_compare_exchange_4(
    volatile void *ptr,
    void *expected,
    uint32_t desired,
    int success,
    int failure
) {
    if (LOCK_FREE(4)) {
        if (aligned(ptr, 4)) {
#if RISCV64_CAS_4
            (void)success;
            (void)failure;
            return riscv64_compare_exchange_4(ptr, expected, desired);
#elif WORD_CAS
            (void)success;
            (void)failure;
            return word_compare_exchange(ptr, 4, expected, &desired);
#else
            volatile atomic_u32 *p = ptr;
            atomic_u32 e;
            bool ok;

            copy(&e, expected, 4);
            ok = __atomic_compare_exchange_n(p, &e, desired, false, success, failure);
            if (ok) {
                return true;
            }
            copy(expected, &e, 4);
            return false;
#endif
        }
    }
    return locked_compare_exchange(4, ptr, expected, &desired);
}

bool atomic_compare_exchange_8(
    volatile void *ptr,
    void *expected,
    uint64_t desired,
    int success,
    int failure
) {
    if (LOCK_FREE(8)) {
        if (aligned(ptr, 8)) {
            volatile atomic_u64 *p = ptr;
            atomic_u64 e;
            bool ok;

            copy(&e, expected, 8);
            ok = __atomic_compare_exchange_n(p, &e, desired, false, success, failure);
            if (ok) {
                return true;
            }
            copy(expected, &e, 8);
            return false;
        }
    }
    return locked_compare_exchange(8, ptr, expected, &desired);
}

#if HAS_INT128
bool atomic_compare_exchange_16(
    volatile void *ptr,
    void *expected,
    u128 desired,
    int success,
    int failure
) {
    if (LOCK_FREE(16)) {
        if (aligned(ptr, 16)) {
            atomic_u128 e;
            bool ok;

            copy(&e, expected, 16);
#if ATOMIC_HELPERS_16
            ok = compare_exchange_16(ptr, (u128 *)&e, desired, success, failure);
#else
            ok = __atomic_compare_exchange_n(
                (volatile atomic_u128 *)ptr, &e, desired, false, success, failure
            );
#endif
            if (!ok) {
                copy(expected, &e, 16);
            }
            return ok;
        }
    }
    return locked_compare_exchange(16, ptr, expected, &desired);
}
#endif // HAS_INT128

#endif // HAS_ATOMICS

#if HAS_ATOMICS

// These define __atomic_fetch_OP_N for each OP and N. Under the lock, values
// narrower than int are operated on as unsigned int, as they would otherwise
// promote to int, whose arithmetic can compile into overflow-checking calls
// with -ftrapv.

#define OP_ADD(x, v) ((x) + (v))
#define OP_SUB(x, v) ((x) - (v))
#define OP_AND(x, v) ((x) & (v))
#define OP_OR(x, v) ((x) | (v))
#define OP_XOR(x, v) ((x) ^ (v))
#define OP_NAND(x, v) (~((x) & (v)))

// fetch(op, n) names the builtin, or the function, that the lock-free path
// calls.
#define FETCH_OP(op, apply, n, type, atomic_type, arith_type, fetch) \
    type atomic_fetch_##op##_##n( \
        volatile void *ptr, type val, int model \
    ) ASM_LABEL(__atomic_fetch_##op##_##n); \
    type atomic_fetch_##op##_##n(volatile void *ptr, type val, int model) { \
        lock_word *lock; \
        type x; \
        type y; \
        \
        if (LOCK_FREE(n)) { \
            if (aligned(ptr, n)) { \
                return fetch(op, n)((volatile atomic_type *)ptr, val, model); \
            } \
        } \
        lock = lock_of(ptr); \
        lgrt_lock(lock); \
        load_object(&x, ptr, n); \
        y = (type)apply((arith_type)x, (arith_type)val); \
        store_object(ptr, &y, n); \
        unlock(lock); \
        return x; \
    }

#define FETCH_BUILTIN(op, n) __atomic_fetch_##op

#if WORD_CAS
// The lock-free paths of the routines of up to 4 bytes loop on
// word_compare_exchange instead.
#   define FETCH_WORD(op, n) word_fetch_##op##_##n
#   define FETCH_OP_WORD(op, apply, n, type, atomic_type) \
        static inline type word_fetch_##op##_##n(volatile atomic_type *p, type val, int model) { \
            type x; \
            type y; \
            \
            (void)model; \
            load_bytes(&x, p, n); \
            do { \
                y = (type)apply((uint32_t)x, (uint32_t)val); \
            } while (!word_compare_exchange(p, n, &x, &y)); \
            return x; \
        } \
        FETCH_OP(op, apply, n, type, atomic_type, uint32_t, FETCH_WORD)
#   define FETCH_OP_NARROW(op, apply, n, type, atomic_type) \
        FETCH_OP_WORD(op, apply, n, type, atomic_type)
#   define FETCH_OP_4(op, apply) FETCH_OP_WORD(op, apply, 4, uint32_t, atomic_u32)
#elif !defined(__clang__) && __GNUC__ == 16 && __GNUC_MINOR__ == 1 && defined(__mips__)
// Workaround: GCC 16.1, MIPS: when optimising, it compiles byte and halfword
// fetch-and-add, -and, -or, and -xor into fetch-nand, so there the lock-free
// paths of the 1- and 2-byte routines loop on compare-exchanges instead.
#   define FETCH_CAS(op, n) cas_fetch_##op##_##n
#   define FETCH_OP_NARROW(op, apply, n, type, atomic_type) \
        static inline type cas_fetch_##op##_##n(volatile atomic_type *p, type val, int model) { \
            atomic_type x = __atomic_load_n(p, __ATOMIC_RELAXED); \
            type y; \
            bool done; \
            \
            do { \
                y = (type)apply((unsigned int)x, (unsigned int)val); \
                done = __atomic_compare_exchange_n(p, &x, y, false, model, __ATOMIC_RELAXED); \
            } while (!done); \
            return x; \
        } \
        FETCH_OP(op, apply, n, type, atomic_type, unsigned int, FETCH_CAS)
#else // WORD_CAS
#   define FETCH_OP_NARROW(op, apply, n, type, atomic_type) \
        FETCH_OP(op, apply, n, type, atomic_type, unsigned int, FETCH_BUILTIN)
#endif // WORD_CAS

#if !defined(FETCH_OP_4)
#   define FETCH_OP_4(op, apply) \
        FETCH_OP(op, apply, 4, uint32_t, atomic_u32, uint32_t, FETCH_BUILTIN)
#endif

#if ATOMIC_HELPERS_16
// Where the 16-byte builtins cannot be used, the lock-free paths of the
// 16-byte routines loop on compare_exchange_16 instead.
#   define FETCH_HELPER(op, n) fetch_##op##_##n
#   define FETCH_OP_16(op, apply) \
        static inline u128 fetch_##op##_16(volatile void *ptr, u128 val, int model) { \
            u128 x = load_16(ptr, __ATOMIC_RELAXED); \
            bool done; \
            \
            do { \
                done = compare_exchange_16(ptr, &x, apply(x, val), model, __ATOMIC_RELAXED); \
            } while (!done); \
            return x; \
        } \
        FETCH_OP(op, apply, 16, u128, atomic_u128, u128, FETCH_HELPER)
#elif HAS_INT128
#   define FETCH_OP_16(op, apply) FETCH_OP(op, apply, 16, u128, atomic_u128, u128, FETCH_BUILTIN)
#else
#   define FETCH_OP_16(op, apply)
#endif

#define FETCH_OPS(op, apply) \
    FETCH_OP_NARROW(op, apply, 1, uint8_t, uint8_t) \
    FETCH_OP_NARROW(op, apply, 2, uint16_t, atomic_u16) \
    FETCH_OP_4(op, apply) \
    FETCH_OP(op, apply, 8, uint64_t, atomic_u64, uint64_t, FETCH_BUILTIN) \
    FETCH_OP_16(op, apply)

FETCH_OPS(add, OP_ADD)
FETCH_OPS(sub, OP_SUB)
FETCH_OPS(and, OP_AND)
FETCH_OPS(or, OP_OR)
FETCH_OPS(xor, OP_XOR)
FETCH_OPS(nand, OP_NAND)

#if !defined(FREESTANDING_LGRT_DISABLE_LIBC_FUNCS) && __STDC_VERSION__ >= 201112L \
 && defined(__has_include)
#if __has_include(<stdatomic.h>)

#include <stdatomic.h>

// <stdatomic.h> defines these as macros, but programs may also call them as
// functions. Where WORD_CAS stands in, they use the routines, as GCC may make
// a byte test-and-set a plain load and store, or a library call.

#undef atomic_flag_test_and_set
bool atomic_flag_test_and_set(volatile atomic_flag *object) {
#if WORD_CAS
    uint8_t old = atomic_exchange_1(
        (volatile void *)object, __GCC_ATOMIC_TEST_AND_SET_TRUEVAL, __ATOMIC_SEQ_CST
    );

    return old != 0;
#else
    return __atomic_test_and_set((volatile void *)object, __ATOMIC_SEQ_CST);
#endif
}

#undef atomic_flag_test_and_set_explicit
bool atomic_flag_test_and_set_explicit(volatile atomic_flag *object, memory_order order) {
#if WORD_CAS
    uint8_t old = atomic_exchange_1(
        (volatile void *)object, __GCC_ATOMIC_TEST_AND_SET_TRUEVAL, order
    );

    return old != 0;
#else
    return __atomic_test_and_set((volatile void *)object, order);
#endif
}

#undef atomic_flag_clear
void atomic_flag_clear(volatile atomic_flag *object) {
#if WORD_CAS
    atomic_store_1((volatile void *)object, 0, __ATOMIC_SEQ_CST);
#else
    __atomic_clear((volatile void *)object, __ATOMIC_SEQ_CST);
#endif
}

#undef atomic_flag_clear_explicit
void atomic_flag_clear_explicit(volatile atomic_flag *object, memory_order order) {
#if WORD_CAS
    atomic_store_1((volatile void *)object, 0, order);
#else
    __atomic_clear((volatile void *)object, order);
#endif
}

#undef atomic_thread_fence
void atomic_thread_fence(memory_order order) {
    __atomic_thread_fence(order);
}

#undef atomic_signal_fence
void atomic_signal_fence(memory_order order) {
    __atomic_signal_fence(order);
}

#endif // __has_include(<stdatomic.h>)
#endif // !defined(FREESTANDING_LGRT_DISABLE_LIBC_FUNCS) && __STDC_VERSION__ >= 201112L && defined(__has_include)

// Compilers call these for the __sync builtins, on the sizes they have no
// inline code for, and on some targets for the __atomic builtins too.

#define SYNC_FETCH(op, apply, n, type) \
    type sync_fetch_and_##op##_##n( \
        volatile void *ptr, type val \
    ) ASM_LABEL(__sync_fetch_and_##op##_##n); \
    type sync_fetch_and_##op##_##n(volatile void *ptr, type val) { \
        return atomic_fetch_##op##_##n(ptr, val, __ATOMIC_SEQ_CST); \
    } \
    \
    type sync_##op##_and_fetch_##n( \
        volatile void *ptr, type val \
    ) ASM_LABEL(__sync_##op##_and_fetch_##n); \
    type sync_##op##_and_fetch_##n(volatile void *ptr, type val) { \
        type x = atomic_fetch_##op##_##n(ptr, val, __ATOMIC_SEQ_CST); \
        \
        return (type)apply((sync_wide_##n)x, (sync_wide_##n)val); \
    }

#define SYNC_SIZE(n, type) \
    SYNC_FETCH(add, OP_ADD, n, type) \
    SYNC_FETCH(sub, OP_SUB, n, type) \
    SYNC_FETCH(and, OP_AND, n, type) \
    SYNC_FETCH(or, OP_OR, n, type) \
    SYNC_FETCH(xor, OP_XOR, n, type) \
    SYNC_FETCH(nand, OP_NAND, n, type) \
    \
    type sync_val_compare_and_swap_##n( \
        volatile void *ptr, type expected, type desired \
    ) ASM_LABEL(__sync_val_compare_and_swap_##n); \
    type sync_val_compare_and_swap_##n(volatile void *ptr, type expected, type desired) { \
        atomic_compare_exchange_##n(ptr, &expected, desired, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST); \
        return expected; \
    } \
    \
    bool sync_bool_compare_and_swap_##n( \
        volatile void *ptr, type expected, type desired \
    ) ASM_LABEL(__sync_bool_compare_and_swap_##n); \
    bool sync_bool_compare_and_swap_##n(volatile void *ptr, type expected, type desired) { \
        return atomic_compare_exchange_##n( \
            ptr, &expected, desired, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST \
        ); \
    } \
    \
    type sync_lock_test_and_set_##n( \
        volatile void *ptr, type val \
    ) ASM_LABEL(__sync_lock_test_and_set_##n); \
    type sync_lock_test_and_set_##n(volatile void *ptr, type val) { \
        return atomic_exchange_##n(ptr, val, __ATOMIC_ACQUIRE); \
    } \
    \
    void sync_lock_release_##n(volatile void *ptr) ASM_LABEL(__sync_lock_release_##n); \
    void sync_lock_release_##n(volatile void *ptr) { \
        atomic_store_##n(ptr, 0, __ATOMIC_RELEASE); \
    }

// Values narrower than int are operated on as unsigned int, for the reason of
// the routines above.
typedef unsigned int sync_wide_1;
typedef unsigned int sync_wide_2;
typedef uint32_t sync_wide_4;
typedef uint64_t sync_wide_8;

SYNC_SIZE(1, uint8_t)
SYNC_SIZE(2, uint16_t)
SYNC_SIZE(4, uint32_t)
SYNC_SIZE(8, uint64_t)

#if HAS_INT128
typedef u128 sync_wide_16;

SYNC_SIZE(16, u128)
#endif

#if WORD_CAS
void sync_synchronize(void) ASM_LABEL(__sync_synchronize);
void sync_synchronize(void) {
    fence();
}
#endif

#endif // HAS_ATOMICS

// GCC calls this at the end of a compound assignment to an _Atomic
// floating-point object, with the environment as it was before that, and with
// the status register as it was after it, of which only the flags that GCC
// cleared for the operation count. Nothing calls it on the other targets,
// which have no FPU, or do this inline, as RISC-V and PowerPC do, and Clang
// calls it nowhere.
#if defined(__mips16)
#   define FE_ABI __attribute__((__nomips16__))
#else
#   define FE_ABI
#endif

FE_ABI void atomic_feraiseexcept(int excepts) __asm__ (
    XSTR(__USER_LABEL_PREFIX__) "__atomic_feraiseexcept"
);

#if !defined(FREESTANDING_LGRT_ENABLE_FLOAT)
// Nothing to raise.
#elif (defined(__i386__) || defined(__x86_64__)) \
   && (defined(__SSE__) \
    || (!defined(__clang__) && !defined(_SOFT_FLOAT) && (!defined(__x86_64__) || __GNUC__ >= 5)))
#   define FE_ALL ((uint32_t)0x3f)
#   define FE_INVALID ((uint32_t)0x01)
#   define FE_DENORMAL ((uint32_t)0x02)
#   define FE_DIVBYZERO ((uint32_t)0x04)
#   define FE_OVERFLOW ((uint32_t)0x08)
#   define FE_UNDERFLOW ((uint32_t)0x10)
#   define FE_INEXACT ((uint32_t)0x20)
#elif defined(__alpha__)
#   define FE_ALL ((uint32_t)0x7e0000)
#   define FE_INVALID ((uint32_t)0x020000)
#   define FE_DIVBYZERO ((uint32_t)0x040000)
#   define FE_OVERFLOW ((uint32_t)0x080000)
#   define FE_UNDERFLOW ((uint32_t)0x100000)
#   define FE_INEXACT ((uint32_t)0x200000)
#   define FE_DENORMAL ((uint32_t)0x400000)
#elif (defined(__aarch64__) && !AARCH64_NO_FP) \
   || (defined(__arm__) && defined(__ARM_FP) && !defined(__SOFTFP__) \
    && (!defined(__thumb__) || defined(__thumb2__)))
#   define FE_ALL ((uint32_t)0x1f)
#   define FE_INVALID ((uint32_t)0x01)
#   define FE_DIVBYZERO ((uint32_t)0x02)
#   define FE_OVERFLOW ((uint32_t)0x04)
#   define FE_UNDERFLOW ((uint32_t)0x08)
#   define FE_INEXACT ((uint32_t)0x10)
#elif defined(__hppa__) && !defined(__SOFTFP__) && __GNUC__ >= 11
#   define FE_ALL ((uint32_t)0xf8000000)
#   define FE_INVALID ((uint32_t)0x80000000)
#   define FE_DIVBYZERO ((uint32_t)0x40000000)
#   define FE_OVERFLOW ((uint32_t)0x20000000)
#   define FE_UNDERFLOW ((uint32_t)0x10000000)
#   define FE_INEXACT ((uint32_t)0x08000000)
#elif defined(__loongarch_frlen) && __loongarch_frlen != 0
#   define FE_ALL ((uint32_t)0x1f0000)
#   define FE_INVALID ((uint32_t)0x100000)
#   define FE_DIVBYZERO ((uint32_t)0x080000)
#   define FE_OVERFLOW ((uint32_t)0x040000)
#   define FE_UNDERFLOW ((uint32_t)0x020000)
#   define FE_INEXACT ((uint32_t)0x010000)
#elif (defined(__mips__) && defined(__mips_hard_float)) || defined(__SH_FPU_ANY__)
#   define FE_ALL ((uint32_t)0x7c)
#   define FE_INVALID ((uint32_t)0x40)
#   define FE_DIVBYZERO ((uint32_t)0x20)
#   define FE_OVERFLOW ((uint32_t)0x10)
#   define FE_UNDERFLOW ((uint32_t)0x08)
#   define FE_INEXACT ((uint32_t)0x04)
#elif defined(__s390__) && (defined(__clang__) || defined(__FP_FAST_FMAF))
// GCC moves the flags to the low byte of the argument.
#   define FE_ALL ((uint32_t)0xf8)
#   define FE_INVALID ((uint32_t)0x80)
#   define FE_DIVBYZERO ((uint32_t)0x40)
#   define FE_OVERFLOW ((uint32_t)0x20)
#   define FE_UNDERFLOW ((uint32_t)0x10)
#   define FE_INEXACT ((uint32_t)0x08)
#elif defined(__sparc__) && !defined(_SOFT_FLOAT) && !defined(SOFT_FLOAT)
#   define FE_ALL ((uint32_t)0x3e0)
#   define FE_INVALID ((uint32_t)0x200)
#   define FE_OVERFLOW ((uint32_t)0x100)
#   define FE_UNDERFLOW ((uint32_t)0x080)
#   define FE_DIVBYZERO ((uint32_t)0x040)
#   define FE_INEXACT ((uint32_t)0x020)
#endif // !defined(FREESTANDING_LGRT_ENABLE_FLOAT)

#if defined(FE_ALL)

#if defined(__alpha__)

// These name the flags of the FP_C quadword, which only the operating system
// reaches, on completing an instruction with /S, as GCC compiles the operation
// itself: so each gets such an instruction, whatever flags this is built with.
#define FE_ALPHA(instruction, a, b) do { \
    __typeof__(a) FE_ALPHA_a = (a); \
    __typeof__(b) FE_ALPHA_b = (b); \
    \
    __asm__ volatile ( \
        "lds $f10, %0\n\t" \
        "lds $f11, %1\n\t" \
        instruction " $f10, $f11, $f12\n\t" \
        "trapb" \
        : \
        : "m"(FE_ALPHA_a), "m"(FE_ALPHA_b) \
        : "$f10", "$f11", "$f12" \
    ); \
} while (0)
#define FE_DIVIDE(a, b) FE_ALPHA("divs/sui", a, b)
#define FE_MULTIPLY(a, b) FE_ALPHA("muls/su", a, b)
#define FE_COMPARE(a, b) FE_ALPHA("cmpteq/su", a, b)

#elif defined(__arm__)

// GCC rejects floating-point types with -mgeneral-regs-only here, with nothing
// to tell of it, and leaves assembly alone. A trap that some cores delay to
// the next instruction of the FPU comes with the last move.
#define FE_VFP(instruction, a, b) do { \
    __typeof__(a) FE_VFP_a = (a); \
    __typeof__(b) FE_VFP_b = (b); \
    uint32_t FE_VFP_result; \
    \
    __asm__ volatile ( \
        "vmov s14, %1\n\t" \
        "vmov s15, %2\n\t" \
        instruction " s14, s14, s15\n\t" \
        "vmov %0, s14" \
        : "=r"(FE_VFP_result) \
        : "r"((uint32_t)FE_VFP_a), "r"((uint32_t)FE_VFP_b) \
        : "s14", "s15" \
    ); \
    (void)FE_VFP_result; \
} while (0)
#define FE_DIVIDE(a, b) FE_VFP("vdiv.f32", a, b)
#define FE_MULTIPLY(a, b) FE_VFP("vmul.f32", a, b)

#else // defined(__alpha__)

// Through volatile objects, the compiler can neither fold these nor drop them,
// whatever flags this is built with.
union fe_float {
    uint32_t bits;
    float value;
};

#define FE_C(op, a, b) do { \
    __typeof__(a) FE_C_a = (a); \
    __typeof__(b) FE_C_b = (b); \
    volatile union fe_float FE_C_x = { .bits = FE_C_a }; \
    volatile union fe_float FE_C_y = { .bits = FE_C_b }; \
    volatile float FE_C_result = FE_C_x.value op FE_C_y.value; \
    \
    (void)FE_C_result; \
} while (0)
#define FE_MULTIPLY(a, b) FE_C(*, a, b)
#define FE_DIVIDE(a, b) FE_C(/, a, b)

// The denormal exception of x86, which reading such an operand raises.
#define FE_COMPARE(a, b) do { \
    __typeof__(a) FE_COMPARE_a = (a); \
    __typeof__(b) FE_COMPARE_b = (b); \
    volatile union fe_float FE_COMPARE_x = { .bits = FE_COMPARE_a }; \
    volatile union fe_float FE_COMPARE_y = { .bits = FE_COMPARE_b }; \
    volatile int FE_COMPARE_result = FE_COMPARE_x.value == FE_COMPARE_y.value; \
    \
    (void)FE_COMPARE_result; \
} while (0)

#endif // defined(__alpha__)

// No operand here is denormal on SuperH, which traps on one.
__attribute__((__noinline__)) FE_ABI static void fe_operate(uint32_t named) {
    if ((named & FE_INVALID) != 0) {
        FE_DIVIDE(0x00000000, 0x00000000);
    }
#if defined(FE_DENORMAL)
    if ((named & FE_DENORMAL) != 0) {
        FE_COMPARE(0x00000001, 0x00000000);
    }
#endif
    if ((named & FE_DIVBYZERO) != 0) {
        FE_DIVIDE(0x3f800000, 0x00000000);
    }
    if ((named & FE_OVERFLOW) != 0) {
        FE_MULTIPLY(0x7f000000, 0x7f000000);
    }
    if ((named & FE_UNDERFLOW) != 0) {
        FE_MULTIPLY(0x00800000, 0x00800000);
    }
    if ((named & FE_INEXACT) != 0) {
        FE_DIVIDE(0x3f800000, 0x40400000);
    }
}

FE_ABI void atomic_feraiseexcept(int excepts) {
    uint32_t named = (uint32_t)excepts & FE_ALL;

    if (named == 0) {
        return;
    }

    fe_operate(named);
#if defined(__sh__)
    // Where GCC switches precision around an operation, it can put back what
    // it saved before that, along with the flags of then. Out here it has no
    // more reason to switch.
    {
        uint32_t fpscr;

        __asm__ volatile ("sts fpscr, %0" : "=r"(fpscr));
        fpscr |= named;
        __asm__ volatile ("lds %0, fpscr" :: "r"(fpscr));
    }
#endif
}

#endif // defined(FE_ALL)

#if defined(__mips16)
// GCC calls this for the fences of MIPS16, which no instruction does.
__attribute__((__nomips16__)) void sync_synchronize(void) __asm__ ("__sync_synchronize");
__attribute__((__nomips16__)) void sync_synchronize(void) {
    __atomic_thread_fence(__ATOMIC_SEQ_CST);
}
#endif

#if defined(__aarch64__)

// Programs set this at startup if the CPU has the Large System Extension, so
// that the routines below use its instructions instead of exclusive loops.
__attribute__((__visibility__("hidden"))) bool __aarch64_have_lse_atomics = false;

// With outline atomics, atomic builtins compile into calls to the routines
// below, but in functions that say otherwise, as compilers that have the
// option let them. The builtins make LSE instructions in functions that may
// use those, and exclusive loops elsewhere. Those functions must stay apart,
// for no exclusive loop to become an LSE instruction by inlining.
//
// GCC before 6 has no such attributes, and Clang before 16 ignores what it is
// told of LSE, so those make exclusive loops in both, which all CPUs have.
#if defined(__clang__)
#   define AARCH64_EXCLUSIVE __attribute__((__noinline__, __target__("no-outline-atomics")))
#   define AARCH64_LSE __attribute__((__target__("+lse,no-outline-atomics")))
#elif __GNUC__ >= 10 || (__GNUC__ == 9 && __GNUC_MINOR__ >= 4) \
   || (__GNUC__ == 8 && __GNUC_MINOR__ >= 5)
#   define AARCH64_EXCLUSIVE __attribute__((__noinline__, __target__("no-outline-atomics")))
#   define AARCH64_LSE __attribute__((__target__("+lse")))
#elif __GNUC__ >= 6
#   define AARCH64_EXCLUSIVE __attribute__((__noinline__))
#   define AARCH64_LSE __attribute__((__target__("+lse")))
#else
#   define AARCH64_EXCLUSIVE __attribute__((__noinline__))
#   define AARCH64_LSE
#endif

// The objects are of any type, which these may alias.
typedef uint16_t aarch64_u16 __attribute__((__may_alias__));
typedef uint32_t aarch64_u32 __attribute__((__may_alias__));
typedef uint64_t aarch64_u64 __attribute__((__may_alias__));

#define AARCH64_ROUTINE(name, type, params, args, lse, exclusive) \
    AARCH64_EXCLUSIVE static type name params { \
        exclusive \
    } \
    \
    AARCH64_LSE type __##name params; \
    AARCH64_LSE type __##name params { \
        if (__aarch64_have_lse_atomics) { \
            lse \
        } \
        return name args; \
    }

// Each order's row below gives the memory orders of the LSE instruction, then
// those of the exclusive loop, and then whether a barrier follows that.
#define AARCH64_NO_FENCE do {} while (0)
#define AARCH64_FULL_FENCE do { __atomic_thread_fence(__ATOMIC_SEQ_CST); } while (0)

#define AARCH64_CAS(n, type, order, lse_s, lse_f, ex_s, ex_f, fence) \
    AARCH64_ROUTINE( \
        aarch64_cas##n##_##order, type, (type expected, type desired, volatile void *ptr), \
        (expected, desired, ptr), \
        __atomic_compare_exchange_n( \
            (volatile type *)ptr, &expected, desired, false, lse_s, lse_f \
        ); \
        return expected;, \
        __atomic_compare_exchange_n((volatile type *)ptr, &expected, desired, false, ex_s, ex_f); \
        fence; \
        return expected; \
    )

#define AARCH64_CAS_ORDERS(n, type) \
    AARCH64_CAS( \
        n, type, relax, __ATOMIC_RELAXED, __ATOMIC_RELAXED, __ATOMIC_RELAXED, __ATOMIC_RELAXED, \
        AARCH64_NO_FENCE \
    ) \
    AARCH64_CAS( \
        n, type, acq, __ATOMIC_ACQUIRE, __ATOMIC_ACQUIRE, __ATOMIC_ACQUIRE, __ATOMIC_ACQUIRE, \
        AARCH64_NO_FENCE \
    ) \
    AARCH64_CAS( \
        n, type, rel, __ATOMIC_RELEASE, __ATOMIC_RELAXED, __ATOMIC_RELEASE, __ATOMIC_RELAXED, \
        AARCH64_NO_FENCE \
    ) \
    AARCH64_CAS( \
        n, type, acq_rel, __ATOMIC_ACQ_REL, __ATOMIC_ACQUIRE, __ATOMIC_ACQ_REL, __ATOMIC_ACQUIRE, \
        AARCH64_NO_FENCE \
    ) \
    AARCH64_CAS( \
        n, type, sync, __ATOMIC_ACQ_REL, __ATOMIC_ACQUIRE, __ATOMIC_RELEASE, __ATOMIC_RELAXED, \
        AARCH64_FULL_FENCE \
    )

AARCH64_CAS_ORDERS(1, uint8_t)
AARCH64_CAS_ORDERS(2, aarch64_u16)
AARCH64_CAS_ORDERS(4, aarch64_u32)
AARCH64_CAS_ORDERS(8, aarch64_u64)

#if HAS_INT128

// The casp and exclusive pair instructions hold the doubleword at the lower
// address in the first register of a pair, which is the high half on
// big-endian targets.
#if defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#   define AARCH64_FIRST_SHIFT 64
#   define AARCH64_SECOND_SHIFT 0
#else
#   define AARCH64_FIRST_SHIFT 0
#   define AARCH64_SECOND_SHIFT 64
#endif

static inline uint64_t aarch64_first(u128 x) {
    return (uint64_t)(x >> AARCH64_FIRST_SHIFT);
}

static inline uint64_t aarch64_second(u128 x) {
    return (uint64_t)(x >> AARCH64_SECOND_SHIFT);
}

static inline u128 aarch64_pair(uint64_t first, uint64_t second) {
    return ((u128)first << AARCH64_FIRST_SHIFT) | ((u128)second << AARCH64_SECOND_SHIFT);
}

// A 16-byte exclusive load is only single-copy atomic if the store-exclusive
// after it succeeds, so on a mismatch the loop stores the loaded pair back,
// which the builtins of older compilers do not, and GCC has none of these for
// orders below that of __sync. Older assemblers lack the LSE mnemonics, so
// casp is encoded with .inst, on the registers bound with register variables:
// in hex, 48A0Rc82, with Rs = 0, Rt = 2, and Rn = 4, where A and R encode the
// ordering. Each order's row below gives A and R, the stems of the exclusive
// load and store, and the barrier that follows the loop.
#define AARCH64_CAS16(order, lse_a, lse_r, ldx, stx, fence) \
    u128 __aarch64_cas16_##order(u128 expected, u128 desired, volatile void *ptr) { \
        uint64_t addr = (uintptr_t)ptr; \
        uint64_t e0 = aarch64_first(expected); \
        uint64_t e1 = aarch64_second(expected); \
        uint64_t d0 = aarch64_first(desired); \
        uint64_t d1 = aarch64_second(desired); \
        \
        if (__aarch64_have_lse_atomics) { \
            register uint64_t r0 __asm__ ("x0") = e0; \
            register uint64_t r1 __asm__ ("x1") = e1; \
            register uint64_t r2 __asm__ ("x2") = d0; \
            register uint64_t r3 __asm__ ("x3") = d1; \
            register uint64_t r4 __asm__ ("x4") = addr; \
            \
            __asm__ volatile ( \
                ".inst 0x48" lse_a "0" lse_r "c82" \
                : "+r"(r0), "+r"(r1) \
                : "r"(r2), "r"(r3), "r"(r4) \
                : "memory" \
            ); \
            return aarch64_pair(r0, r1); \
        } else { \
            uint64_t o0; \
            uint64_t o1; \
            uint64_t n0; \
            uint64_t n1; \
            uint32_t status; \
            \
            __asm__ volatile ( \
                "1:\n\t" \
                ldx "p %[o0], %[o1], [%[addr]]\n\t" \
                "cmp %[o0], %[e0]\n\t" \
                "ccmp %[o1], %[e1], #0, eq\n\t" \
                "csel %[n0], %[d0], %[o0], eq\n\t" \
                "csel %[n1], %[d1], %[o1], eq\n\t" \
                stx "p %w[status], %[n0], %[n1], [%[addr]]\n\t" \
                "cbnz %w[status], 1b\n\t" \
                fence \
                : [o0] "=&r"(o0), [o1] "=&r"(o1), [n0] "=&r"(n0), [n1] "=&r"(n1), \
                  [status] "=&r"(status) \
                : [e0] "r"(e0), [e1] "r"(e1), [d0] "r"(d0), [d1] "r"(d1), [addr] "r"(addr) \
                : "cc", "memory" \
            ); \
            return aarch64_pair(o0, o1); \
        } \
    }

AARCH64_CAS16(relax, "2", "7", "ldx", "stx", "")
AARCH64_CAS16(acq, "6", "7", "ldax", "stx", "")
AARCH64_CAS16(rel, "2", "f", "ldx", "stlx", "")
AARCH64_CAS16(acq_rel, "6", "f", "ldax", "stlx", "")
AARCH64_CAS16(sync, "6", "f", "ldx", "stlx", "dmb ish")

#endif // HAS_INT128

#define AARCH64_SWP(n, type, order, lse_order, ex_order, fence) \
    AARCH64_ROUTINE( \
        aarch64_swp##n##_##order, type, (type val, volatile void *ptr), (val, ptr), \
        return __atomic_exchange_n((volatile type *)ptr, val, lse_order);, \
        type old = __atomic_exchange_n((volatile type *)ptr, val, ex_order); \
        \
        fence; \
        return old; \
    )

// A __sync lock test-and-set is only an acquire barrier.
#define AARCH64_SWP_ORDERS(n, type) \
    AARCH64_SWP(n, type, relax, __ATOMIC_RELAXED, __ATOMIC_RELAXED, AARCH64_NO_FENCE) \
    AARCH64_SWP(n, type, acq, __ATOMIC_ACQUIRE, __ATOMIC_ACQUIRE, AARCH64_NO_FENCE) \
    AARCH64_SWP(n, type, rel, __ATOMIC_RELEASE, __ATOMIC_RELEASE, AARCH64_NO_FENCE) \
    AARCH64_SWP(n, type, acq_rel, __ATOMIC_ACQ_REL, __ATOMIC_ACQ_REL, AARCH64_NO_FENCE) \
    AARCH64_SWP(n, type, sync, __ATOMIC_ACQUIRE, __ATOMIC_RELAXED, AARCH64_FULL_FENCE)

AARCH64_SWP_ORDERS(1, uint8_t)
AARCH64_SWP_ORDERS(2, aarch64_u16)
AARCH64_SWP_ORDERS(4, aarch64_u32)
AARCH64_SWP_ORDERS(8, aarch64_u64)

// value is what goes into the builtin, for clearing bits its complement.
#define AARCH64_LDOP(op, builtin, value, n, type, order, lse_order, ex_order, fence) \
    AARCH64_ROUTINE( \
        aarch64_##op##n##_##order, type, (type val, volatile void *ptr), (val, ptr), \
        return builtin((volatile type *)ptr, (type)(value), lse_order);, \
        type old = builtin((volatile type *)ptr, (type)(value), ex_order); \
        \
        fence; \
        return old; \
    )

#define AARCH64_LDOP_ORDERS(op, builtin, value, n, type) \
    AARCH64_LDOP( \
        op, builtin, value, n, type, relax, __ATOMIC_RELAXED, __ATOMIC_RELAXED, AARCH64_NO_FENCE \
    ) \
    AARCH64_LDOP( \
        op, builtin, value, n, type, acq, __ATOMIC_ACQUIRE, __ATOMIC_ACQUIRE, AARCH64_NO_FENCE \
    ) \
    AARCH64_LDOP( \
        op, builtin, value, n, type, rel, __ATOMIC_RELEASE, __ATOMIC_RELEASE, AARCH64_NO_FENCE \
    ) \
    AARCH64_LDOP( \
        op, builtin, value, n, type, acq_rel, __ATOMIC_ACQ_REL, __ATOMIC_ACQ_REL, \
        AARCH64_NO_FENCE \
    ) \
    AARCH64_LDOP( \
        op, builtin, value, n, type, sync, __ATOMIC_ACQ_REL, __ATOMIC_RELEASE, AARCH64_FULL_FENCE \
    )

#define AARCH64_LDOP_SIZES(op, builtin, value) \
    AARCH64_LDOP_ORDERS(op, builtin, value, 1, uint8_t) \
    AARCH64_LDOP_ORDERS(op, builtin, value, 2, aarch64_u16) \
    AARCH64_LDOP_ORDERS(op, builtin, value, 4, aarch64_u32) \
    AARCH64_LDOP_ORDERS(op, builtin, value, 8, aarch64_u64)

AARCH64_LDOP_SIZES(ldadd, __atomic_fetch_add, val)
AARCH64_LDOP_SIZES(ldclr, __atomic_fetch_and, ~val)
AARCH64_LDOP_SIZES(ldeor, __atomic_fetch_xor, val)
AARCH64_LDOP_SIZES(ldset, __atomic_fetch_or, val)

#endif // defined(__aarch64__)

#if defined(__riscv) && defined(__riscv_xlen) && (__riscv_xlen == 32 || __riscv_xlen == 64)

// With -msave-restore, prologues call __riscv_save_N with the return address
// in t0, and epilogues jump to __riscv_restore_N, to save and restore ra and
// s0 to s(N - 1). The frame is laid out as the compilers' unwind information
// and frame accesses expect: N + 1 words, rounded up to 16 bytes except with
// the E ABIs, with ra in the top word and the s registers in order below it.
// Entry points whose frames have the same size share code that fills the whole
// frame, as the compilers leave the extra slots alone and the extra registers
// unchanged.

#if __riscv_xlen == 64
#   define RISCV_WORD "8"
#   define RISCV_STORE "sd"
#   define RISCV_LOAD "ld"
#else
#   define RISCV_WORD "4"
#   define RISCV_STORE "sw"
#   define RISCV_LOAD "lw"
#endif

// RISCV_REGSn applies op to ra and s0 to s(n - 2), in the top n words of an
// f-byte frame.
#define RISCV_SLOT(op, reg, f, k) op " " reg ", " #f "-" #k "*" RISCV_WORD "(sp)\n\t"
#define RISCV_REGS1(op, f) RISCV_SLOT(op, "ra", f, 1)
#define RISCV_REGS2(op, f) \
    RISCV_REGS1(op, f) \
    RISCV_SLOT(op, "s0", f, 2)
#define RISCV_REGS3(op, f) \
    RISCV_REGS2(op, f) \
    RISCV_SLOT(op, "s1", f, 3)
#define RISCV_REGS4(op, f) \
    RISCV_REGS3(op, f) \
    RISCV_SLOT(op, "s2", f, 4)
#define RISCV_REGS5(op, f) \
    RISCV_REGS4(op, f) \
    RISCV_SLOT(op, "s3", f, 5)
#define RISCV_REGS6(op, f) \
    RISCV_REGS5(op, f) \
    RISCV_SLOT(op, "s4", f, 6)
#define RISCV_REGS7(op, f) \
    RISCV_REGS6(op, f) \
    RISCV_SLOT(op, "s5", f, 7)
#define RISCV_REGS8(op, f) \
    RISCV_REGS7(op, f) \
    RISCV_SLOT(op, "s6", f, 8)
#define RISCV_REGS9(op, f) \
    RISCV_REGS8(op, f) \
    RISCV_SLOT(op, "s7", f, 9)
#define RISCV_REGS10(op, f) \
    RISCV_REGS9(op, f) \
    RISCV_SLOT(op, "s8", f, 10)
#define RISCV_REGS11(op, f) \
    RISCV_REGS10(op, f) \
    RISCV_SLOT(op, "s9", f, 11)
#define RISCV_REGS12(op, f) \
    RISCV_REGS11(op, f) \
    RISCV_SLOT(op, "s10", f, 12)
#define RISCV_REGS13(op, f) \
    RISCV_REGS12(op, f) \
    RISCV_SLOT(op, "s11", f, 13)

// An entry point's code ends where the code for its frame size does.
#define RISCV_ENTRY(kind, n, f) \
    ".globl __riscv_" #kind "_" #n "\n\t" \
    ".hidden __riscv_" #kind "_" #n "\n\t" \
    ".type __riscv_" #kind "_" #n ", @function\n\t" \
    "__riscv_" #kind "_" #n ":\n\t" \
    ".size __riscv_" #kind "_" #n ", " \
    ".Lriscv_" #kind "_" #f " - __riscv_" #kind "_" #n "\n\t"

#define RISCV_SAVE(f, n) \
    "addi sp, sp, -" #f "\n\t" \
    RISCV_REGS##n(RISCV_STORE, f) \
    "jr t0\n\t" \
    ".Lriscv_save_" #f ":\n\t"

#define RISCV_RESTORE(f, n) \
    RISCV_REGS##n(RISCV_LOAD, f) \
    "addi sp, sp, " #f "\n\t" \
    "ret\n\t" \
    ".Lriscv_restore_" #f ":\n\t"

// Instructions need 2-byte alignment with the C extension, and 4-byte
// alignment without.
#if defined(__riscv_compressed)
#   define RISCV_ALIGN ".p2align 1\n\t"
#else
#   define RISCV_ALIGN ".p2align 2\n\t"
#endif

// Each group of entry points that share code(f, n), for an f-byte frame
// holding n registers, is a statement of its own, in a section named after its
// first entry point, so that linking with --gc-sections drops the unused
// groups.
#define RISCV_GROUP(kind, first, text) \
    __asm__ ( \
        ".pushsection .text.__riscv_" #kind "_" #first ",\"ax\",@progbits\n\t" \
        RISCV_ALIGN \
        text \
        ".popsection" \
    );

#define RISCV_GROUP1(kind, code, a, f, n) RISCV_GROUP(kind, a, RISCV_ENTRY(kind, a, f) code(f, n))

#define RISCV_GROUP2(kind, code, a, b, f, n) \
    RISCV_GROUP(kind, a, RISCV_ENTRY(kind, a, f) RISCV_ENTRY(kind, b, f) code(f, n))

#define RISCV_GROUP4(kind, code, a, b, c, d, f, n) \
    RISCV_GROUP( \
        kind, a, RISCV_ENTRY(kind, a, f) RISCV_ENTRY(kind, b, f) RISCV_ENTRY(kind, c, f) \
                 RISCV_ENTRY(kind, d, f) code(f, n) \
    )

#if defined(__riscv_abi_rve) && __riscv_xlen == 32
#   define RISCV_ROUTINES(kind, code) \
        RISCV_GROUP1(kind, code, 0, 4, 1) \
        RISCV_GROUP1(kind, code, 1, 8, 2) \
        RISCV_GROUP1(kind, code, 2, 12, 3)
#elif defined(__riscv_abi_rve)
#   define RISCV_ROUTINES(kind, code) \
        RISCV_GROUP1(kind, code, 0, 8, 1) \
        RISCV_GROUP1(kind, code, 1, 16, 2) \
        RISCV_GROUP1(kind, code, 2, 24, 3)
#elif __riscv_xlen == 32
#   define RISCV_ROUTINES(kind, code) \
        RISCV_GROUP4(kind, code, 0, 1, 2, 3, 16, 4) \
        RISCV_GROUP4(kind, code, 4, 5, 6, 7, 32, 8) \
        RISCV_GROUP4(kind, code, 8, 9, 10, 11, 48, 12) \
        RISCV_GROUP1(kind, code, 12, 64, 13)
#else // defined(__riscv_abi_rve) && __riscv_xlen == 32
#   define RISCV_ROUTINES(kind, code) \
        RISCV_GROUP2(kind, code, 0, 1, 16, 2) \
        RISCV_GROUP2(kind, code, 2, 3, 32, 4) \
        RISCV_GROUP2(kind, code, 4, 5, 48, 6) \
        RISCV_GROUP2(kind, code, 6, 7, 64, 8) \
        RISCV_GROUP2(kind, code, 8, 9, 80, 10) \
        RISCV_GROUP2(kind, code, 10, 11, 96, 12) \
        RISCV_GROUP1(kind, code, 12, 112, 13)
#endif // defined(__riscv_abi_rve) && __riscv_xlen == 32

RISCV_ROUTINES(save, RISCV_SAVE)
RISCV_ROUTINES(restore, RISCV_RESTORE)

#endif // defined(__riscv) && defined(__riscv_xlen) && (__riscv_xlen == 32 || __riscv_xlen == 64)

#if !defined(FREESTANDING_LGRT_DISABLE_LIBC_FUNCS)

// The C23 bit utilities. Those that count or skip ones work on the complement.
// The builtins are undefined for zero, which is handled first, and narrow
// types promote to unsigned int, whose extra width the leading counts
// subtract.

#define STDC_BITS(type) ((unsigned int)(sizeof(type) * CHAR_BIT))

// Expands f for each type, with the type it promotes to and that type's
// builtins.
#define STDC_TYPES(f) \
    f(uc, unsigned char, unsigned int, __builtin_clz, __builtin_ctz) \
    f(us, unsigned short, unsigned int, __builtin_clz, __builtin_ctz) \
    f(ui, unsigned int, unsigned int, __builtin_clz, __builtin_ctz) \
    f(ul, unsigned long, unsigned long, __builtin_clzl, __builtin_ctzl) \
    f(ull, unsigned long long, unsigned long long, __builtin_clzll, __builtin_ctzll)

// These count the leading and trailing zeros of nonzero values.
#define STDC_COUNTS(sfx, type, wide, clz, ctz) \
    static inline unsigned int stdc_clz_##sfx(type x) { \
        return (unsigned int)clz((wide)x) - (STDC_BITS(wide) - STDC_BITS(type)); \
    } \
    \
    static inline unsigned int stdc_ctz_##sfx(type x) { \
        return (unsigned int)ctz((wide)x); \
    }

STDC_TYPES(STDC_COUNTS)

#define STDC_LEADING_ZEROS(sfx, type, wide, clz, ctz) \
    unsigned int stdc_leading_zeros_##sfx(type value) { \
        return value == 0 ? STDC_BITS(type) : stdc_clz_##sfx(value); \
    }

STDC_TYPES(STDC_LEADING_ZEROS)

#define STDC_LEADING_ONES(sfx, type, wide, clz, ctz) \
    unsigned int stdc_leading_ones_##sfx(type value) { \
        type x = (type)~(wide)value; \
        \
        return x == 0 ? STDC_BITS(type) : stdc_clz_##sfx(x); \
    }

STDC_TYPES(STDC_LEADING_ONES)

#define STDC_TRAILING_ZEROS(sfx, type, wide, clz, ctz) \
    unsigned int stdc_trailing_zeros_##sfx(type value) { \
        return value == 0 ? STDC_BITS(type) : stdc_ctz_##sfx(value); \
    }

STDC_TYPES(STDC_TRAILING_ZEROS)

#define STDC_TRAILING_ONES(sfx, type, wide, clz, ctz) \
    unsigned int stdc_trailing_ones_##sfx(type value) { \
        type x = (type)~(wide)value; \
        \
        return x == 0 ? STDC_BITS(type) : stdc_ctz_##sfx(x); \
    }

STDC_TYPES(STDC_TRAILING_ONES)

#define STDC_FIRST_LEADING_ZERO(sfx, type, wide, clz, ctz) \
    unsigned int stdc_first_leading_zero_##sfx(type value) { \
        type x = (type)~(wide)value; \
        \
        return x == 0 ? 0 : stdc_clz_##sfx(x) + 1; \
    }

STDC_TYPES(STDC_FIRST_LEADING_ZERO)

#define STDC_FIRST_LEADING_ONE(sfx, type, wide, clz, ctz) \
    unsigned int stdc_first_leading_one_##sfx(type value) { \
        return value == 0 ? 0 : stdc_clz_##sfx(value) + 1; \
    }

STDC_TYPES(STDC_FIRST_LEADING_ONE)

#define STDC_FIRST_TRAILING_ZERO(sfx, type, wide, clz, ctz) \
    unsigned int stdc_first_trailing_zero_##sfx(type value) { \
        type x = (type)~(wide)value; \
        \
        return x == 0 ? 0 : stdc_ctz_##sfx(x) + 1; \
    }

STDC_TYPES(STDC_FIRST_TRAILING_ZERO)

#define STDC_FIRST_TRAILING_ONE(sfx, type, wide, clz, ctz) \
    unsigned int stdc_first_trailing_one_##sfx(type value) { \
        return value == 0 ? 0 : stdc_ctz_##sfx(value) + 1; \
    }

STDC_TYPES(STDC_FIRST_TRAILING_ONE)

// Expands f for each type, with the type it promotes to and that type's
// popcount builtin.
#define STDC_POPCOUNT_TYPES(f) \
    f(uc, unsigned char, unsigned int, __builtin_popcount) \
    f(us, unsigned short, unsigned int, __builtin_popcount) \
    f(ui, unsigned int, unsigned int, __builtin_popcount) \
    f(ul, unsigned long, unsigned long, __builtin_popcountl) \
    f(ull, unsigned long long, unsigned long long, __builtin_popcountll)

#define STDC_POPCOUNT(sfx, type, wide, popcount) \
    static inline unsigned int stdc_popcount_##sfx(type x) { \
        return (unsigned int)popcount((wide)x); \
    }

STDC_POPCOUNT_TYPES(STDC_POPCOUNT)

// These give the index of the most significant one of nonzero values.
#define STDC_MSB(sfx, type, wide, clz, ctz) \
    static inline unsigned int stdc_msb_##sfx(type x) { \
        return STDC_BITS(wide) - 1 - (unsigned int)clz((wide)x); \
    }

STDC_TYPES(STDC_MSB)

#define STDC_COUNT_ZEROS(sfx, type, wide, clz, ctz) \
    unsigned int stdc_count_zeros_##sfx(type value) { \
        return STDC_BITS(type) - stdc_popcount_##sfx(value); \
    }

STDC_TYPES(STDC_COUNT_ZEROS)

#define STDC_COUNT_ONES(sfx, type, wide, clz, ctz) \
    unsigned int stdc_count_ones_##sfx(type value) { \
        return stdc_popcount_##sfx(value); \
    }

STDC_TYPES(STDC_COUNT_ONES)

#define STDC_HAS_SINGLE_BIT(sfx, type, wide, clz, ctz) \
    bool stdc_has_single_bit_##sfx(type value) { \
        return value != 0 && ((wide)value & ((wide)value - 1)) == 0; \
    }

STDC_TYPES(STDC_HAS_SINGLE_BIT)

#define STDC_BIT_WIDTH(sfx, type, wide, clz, ctz) \
    unsigned int stdc_bit_width_##sfx(type value) { \
        return value == 0 ? 0 : stdc_msb_##sfx(value) + 1; \
    }

STDC_TYPES(STDC_BIT_WIDTH)

#define STDC_BIT_FLOOR(sfx, type, wide, clz, ctz) \
    type stdc_bit_floor_##sfx(type value) { \
        return value == 0 ? 0 : (type)((wide)1 << stdc_msb_##sfx(value)); \
    }

STDC_TYPES(STDC_BIT_FLOOR)

// Above 1, the result is twice the highest power of two in value - 1. Shifting
// 2 keeps the count below the width, and an unrepresentable result wraps to 0.
#define STDC_BIT_CEIL(sfx, type, wide, clz, ctz) \
    type stdc_bit_ceil_##sfx(type value) { \
        type below = (type)((wide)value - 1); \
        \
        return value <= 1 ? 1 : (type)((wide)2 << stdc_msb_##sfx(below)); \
    }

STDC_TYPES(STDC_BIT_CEIL)

#endif // !defined(FREESTANDING_LGRT_DISABLE_LIBC_FUNCS)

#if defined(__hexagon__)

// When optimising for size, Clang saves and restores the callee-saved pairs
// r17:16 to rR:R-1 with these routines, in that order downwards from fp - 8.
// Prologues call the save routines in the packet of their allocframe, so fp
// already points to the new frame. Each entry point handles its highest pair
// and falls through to the entry point for the next lower one.

#define HEXAGON_ENTRY(name, end) \
    ".globl " name "\n\t" \
    ".hidden " name "\n\t" \
    ".type " name ", @function\n\t" \
    name ":\n\t" \
    ".size " name ", " end " - " name "\n\t"

#define HEXAGON_STORE(pair, offset) "memd(r30+#-" offset ") = " pair
#define HEXAGON_LOAD(pair, offset) pair " = memd(r30+#-" offset ")"

// Defines the entry points prefix R suffix, for R from 27 down to 17, all
// extending to end. Those above 17 apply op to their highest pair; the code
// for r17:16 and the label end follow.
#define HEXAGON_ENTRIES(prefix, suffix, end, op) \
    HEXAGON_ENTRY(prefix "27" suffix, end) \
    "{ " op("r27:26", "48") " }\n\t" \
    HEXAGON_ENTRY(prefix "25" suffix, end) \
    "{ " op("r25:24", "40") " }\n\t" \
    HEXAGON_ENTRY(prefix "23" suffix, end) \
    "{ " op("r23:22", "32") " }\n\t" \
    HEXAGON_ENTRY(prefix "21" suffix, end) \
    "{ " op("r21:20", "24") " }\n\t" \
    HEXAGON_ENTRY(prefix "19" suffix, end) \
    "{ " op("r19:18", "16") " }\n\t" \
    HEXAGON_ENTRY(prefix "17" suffix, end)

__asm__ (
    ".pushsection .text.__save_r16_through_r27,\"ax\",@progbits\n\t"
    ".p2align 2\n\t"
    HEXAGON_ENTRIES("__save_r16_through_r", "", ".Lhexagon_save_end", HEXAGON_STORE)
    "{ " HEXAGON_STORE("r17:16", "8") "; jumpr r31 }\n\t"
    ".Lhexagon_save_end:\n\t"
    ".popsection"
);

__asm__ (
    ".pushsection .text.__restore_r16_through_r27_and_deallocframe,\"ax\",@progbits\n\t"
    ".p2align 2\n\t"
    HEXAGON_ENTRIES(
        "__restore_r16_through_r", "_and_deallocframe", ".Lhexagon_restore_end", HEXAGON_LOAD
    )
    "{ " HEXAGON_LOAD("r17:16", "8") "; dealloc_return }\n\t"
    ".Lhexagon_restore_end:\n\t"
    ".popsection"
);

// As deallocframe reloads lr, the return address waits in r28.
__asm__ (
    ".pushsection "
    ".text.__restore_r16_through_r27_and_deallocframe_before_tailcall,\"ax\",@progbits\n\t"
    ".p2align 2\n\t"
    HEXAGON_ENTRIES(
        "__restore_r16_through_r", "_and_deallocframe_before_tailcall",
        ".Lhexagon_restore_before_tailcall_end", HEXAGON_LOAD
    )
    "{ " HEXAGON_LOAD("r17:16", "8") "; r28 = r31 }\n\t"
    "{ deallocframe; jumpr r28 }\n\t"
    ".Lhexagon_restore_before_tailcall_end:\n\t"
    ".popsection"
);

#endif // defined(__hexagon__)

#if defined(__powerpc__) && !defined(__powerpc64__)

// GCC saves and restores callee-saved registers in 32-bit prologues and
// epilogues with calls to these routines, which find each register's slot at a
// constant distance below the address in r11, or in r0 for the vector
// registers, and leave almost every other register alone. The entry points of
// a family share one sequence, each starting at its first register.

#define PPC_ENTRY(name, end) \
    ".globl " name "\n\t" \
    ".hidden " name "\n\t" \
    ".type " name ", @function\n\t" \
    name ":\n\t" \
    ".size " name ", " end " - " name "\n\t"

// Defines the entry points prefix N suffix, for N from 14 to 31, all extending
// to end, each followed by op(N, w, d), where the slot of rN is w bytes below
// r11 and that of fN d bytes.
#define PPC_ENTRIES(prefix, suffix, end, op) \
    PPC_ENTRY(prefix "14" suffix, end) \
    op("14", "72", "144") \
    PPC_ENTRY(prefix "15" suffix, end) \
    op("15", "68", "136") \
    PPC_ENTRY(prefix "16" suffix, end) \
    op("16", "64", "128") \
    PPC_ENTRY(prefix "17" suffix, end) \
    op("17", "60", "120") \
    PPC_ENTRY(prefix "18" suffix, end) \
    op("18", "56", "112") \
    PPC_ENTRY(prefix "19" suffix, end) \
    op("19", "52", "104") \
    PPC_ENTRY(prefix "20" suffix, end) \
    op("20", "48", "96") \
    PPC_ENTRY(prefix "21" suffix, end) \
    op("21", "44", "88") \
    PPC_ENTRY(prefix "22" suffix, end) \
    op("22", "40", "80") \
    PPC_ENTRY(prefix "23" suffix, end) \
    op("23", "36", "72") \
    PPC_ENTRY(prefix "24" suffix, end) \
    op("24", "32", "64") \
    PPC_ENTRY(prefix "25" suffix, end) \
    op("25", "28", "56") \
    PPC_ENTRY(prefix "26" suffix, end) \
    op("26", "24", "48") \
    PPC_ENTRY(prefix "27" suffix, end) \
    op("27", "20", "40") \
    PPC_ENTRY(prefix "28" suffix, end) \
    op("28", "16", "32") \
    PPC_ENTRY(prefix "29" suffix, end) \
    op("29", "12", "24") \
    PPC_ENTRY(prefix "30" suffix, end) \
    op("30", "8", "16") \
    PPC_ENTRY(prefix "31" suffix, end) \
    op("31", "4", "8")

// The frame is popped after the last load from the save area, which then lies
// below the stack pointer, where signal handlers may overwrite it.
#define PPC_EXIT \
    "lwz %r0, 4(%r11)\n\t" \
    "mr %r1, %r11\n\t" \
    "mtlr %r0\n\t" \
    "blr\n\t"

#define PPC_SAVE_GPR(n, w, d) "stw %r" n ", -" w "(%r11)\n\t"
#define PPC_REST_GPR(n, w, d) "lwz %r" n ", -" w "(%r11)\n\t"

__asm__ (
    ".pushsection .text._savegpr_14,\"ax\",@progbits\n\t"
    ".p2align 2\n\t"
    PPC_ENTRIES("_savegpr_", "", ".Lppc_savegpr_end", PPC_SAVE_GPR)
    "blr\n\t"
    ".Lppc_savegpr_end:\n\t"
    ".popsection"
);

__asm__ (
    ".pushsection .text._restgpr_14,\"ax\",@progbits\n\t"
    ".p2align 2\n\t"
    PPC_ENTRIES("_restgpr_", "", ".Lppc_restgpr_end", PPC_REST_GPR)
    "blr\n\t"
    ".Lppc_restgpr_end:\n\t"
    ".popsection"
);

__asm__ (
    ".pushsection .text._restgpr_14_x,\"ax\",@progbits\n\t"
    ".p2align 2\n\t"
    PPC_ENTRIES("_restgpr_", "_x", ".Lppc_restgpr_x_end", PPC_REST_GPR)
    PPC_EXIT
    ".Lppc_restgpr_x_end:\n\t"
    ".popsection"
);

#if defined(__SPE__)

// GCC for SPE calls these instead: the 32-bit ones save the low halves of the
// registers as those above do, and the 64-bit ones the whole registers, for
// code of any type, not only that of doubles. The offsets of evstdd and evldd
// cannot be negative, so r11 holds the address of the slot of r14 there, 144
// bytes below the top of the frame, whatever register the routine starts at.

#define PPC_SAVE_EV(n, w, d) "evstdd %r" n ", 144-" d "(%r11)\n\t"
#define PPC_REST_EV(n, w, d) "evldd %r" n ", 144-" d "(%r11)\n\t"

#define PPC_EXIT_EV \
    "lwz %r0, 148(%r11)\n\t" \
    "addi %r1, %r11, 144\n\t" \
    "mtlr %r0\n\t" \
    "blr\n\t"

__asm__ (
    ".pushsection .text._save32gpr_14,\"ax\",@progbits\n\t"
    ".p2align 2\n\t"
    PPC_ENTRIES("_save32gpr_", "", ".Lppc_save32gpr_end", PPC_SAVE_GPR)
    "blr\n\t"
    ".Lppc_save32gpr_end:\n\t"
    ".popsection"
);

__asm__ (
    ".pushsection .text._rest32gpr_14,\"ax\",@progbits\n\t"
    ".p2align 2\n\t"
    PPC_ENTRIES("_rest32gpr_", "", ".Lppc_rest32gpr_end", PPC_REST_GPR)
    "blr\n\t"
    ".Lppc_rest32gpr_end:\n\t"
    ".popsection"
);

__asm__ (
    ".pushsection .text._rest32gpr_14_x,\"ax\",@progbits\n\t"
    ".p2align 2\n\t"
    PPC_ENTRIES("_rest32gpr_", "_x", ".Lppc_rest32gpr_x_end", PPC_REST_GPR)
    PPC_EXIT
    ".Lppc_rest32gpr_x_end:\n\t"
    ".popsection"
);

__asm__ (
    ".pushsection .text._save64gpr_14,\"ax\",@progbits\n\t"
    ".p2align 2\n\t"
    PPC_ENTRIES("_save64gpr_", "", ".Lppc_save64gpr_end", PPC_SAVE_EV)
    "blr\n\t"
    ".Lppc_save64gpr_end:\n\t"
    ".popsection"
);

__asm__ (
    ".pushsection .text._rest64gpr_14,\"ax\",@progbits\n\t"
    ".p2align 2\n\t"
    PPC_ENTRIES("_rest64gpr_", "", ".Lppc_rest64gpr_end", PPC_REST_EV)
    "blr\n\t"
    ".Lppc_rest64gpr_end:\n\t"
    ".popsection"
);

__asm__ (
    ".pushsection .text._rest64gpr_14_x,\"ax\",@progbits\n\t"
    ".p2align 2\n\t"
    PPC_ENTRIES("_rest64gpr_", "_x", ".Lppc_rest64gpr_x_end", PPC_REST_EV)
    PPC_EXIT_EV
    ".Lppc_rest64gpr_x_end:\n\t"
    ".popsection"
);

#endif // defined(__SPE__)

#if !defined(_SOFT_FLOAT) && !defined(__NO_FPRS__) && defined(FREESTANDING_LGRT_ENABLE_FLOAT)

#define PPC_SAVE_FPR(n, w, d) "stfd %f" n ", -" d "(%r11)\n\t"
#define PPC_REST_FPR(n, w, d) "lfd %f" n ", -" d "(%r11)\n\t"

__asm__ (
    ".pushsection .text._savefpr_14,\"ax\",@progbits\n\t"
    ".p2align 2\n\t"
    PPC_ENTRIES("_savefpr_", "", ".Lppc_savefpr_end", PPC_SAVE_FPR)
    "blr\n\t"
    ".Lppc_savefpr_end:\n\t"
    ".popsection"
);

__asm__ (
    ".pushsection .text._restfpr_14,\"ax\",@progbits\n\t"
    ".p2align 2\n\t"
    PPC_ENTRIES("_restfpr_", "", ".Lppc_restfpr_end", PPC_REST_FPR)
    "blr\n\t"
    ".Lppc_restfpr_end:\n\t"
    ".popsection"
);

__asm__ (
    ".pushsection .text._restfpr_14_x,\"ax\",@progbits\n\t"
    ".p2align 2\n\t"
    PPC_ENTRIES("_restfpr_", "_x", ".Lppc_restfpr_x_end", PPC_REST_FPR)
    PPC_EXIT
    ".Lppc_restfpr_x_end:\n\t"
    ".popsection"
);

#endif // !defined(_SOFT_FLOAT) && !defined(__NO_FPRS__) && defined(FREESTANDING_LGRT_ENABLE_FLOAT)

#if defined(__ALTIVEC__) && defined(FREESTANDING_LGRT_ENABLE_SIMD)

// Defines the entry points prefix N, for N from 20 to 31, all extending to
// end, each followed by op(N, v), where the slot of vN is v bytes below r0.
#define PPC_VR_ENTRIES(prefix, end, op) \
    PPC_ENTRY(prefix "20", end) \
    op("20", "192") \
    PPC_ENTRY(prefix "21", end) \
    op("21", "176") \
    PPC_ENTRY(prefix "22", end) \
    op("22", "160") \
    PPC_ENTRY(prefix "23", end) \
    op("23", "144") \
    PPC_ENTRY(prefix "24", end) \
    op("24", "128") \
    PPC_ENTRY(prefix "25", end) \
    op("25", "112") \
    PPC_ENTRY(prefix "26", end) \
    op("26", "96") \
    PPC_ENTRY(prefix "27", end) \
    op("27", "80") \
    PPC_ENTRY(prefix "28", end) \
    op("28", "64") \
    PPC_ENTRY(prefix "29", end) \
    op("29", "48") \
    PPC_ENTRY(prefix "30", end) \
    op("30", "32") \
    PPC_ENTRY(prefix "31", end) \
    op("31", "16")

// The vector loads and stores read r0 as zero in their first address operand,
// so that operand is the offset, in r11, which GCC lets these change, rather
// than the r12 of the example in the ABI, which they are not part of.
#define PPC_SAVE_VR(n, v) \
    "li %r11, -" v "\n\t" \
    "stvx %v" n ", %r11, %r0\n\t"
#define PPC_REST_VR(n, v) \
    "li %r11, -" v "\n\t" \
    "lvx %v" n ", %r11, %r0\n\t"

__asm__ (
    ".pushsection .text._savevr_20,\"ax\",@progbits\n\t"
    ".p2align 2\n\t"
    PPC_VR_ENTRIES("_savevr_", ".Lppc_savevr_end", PPC_SAVE_VR)
    "blr\n\t"
    ".Lppc_savevr_end:\n\t"
    ".popsection"
);

__asm__ (
    ".pushsection .text._restvr_20,\"ax\",@progbits\n\t"
    ".p2align 2\n\t"
    PPC_VR_ENTRIES("_restvr_", ".Lppc_restvr_end", PPC_REST_VR)
    "blr\n\t"
    ".Lppc_restvr_end:\n\t"
    ".popsection"
);

#endif // defined(__ALTIVEC__) && defined(FREESTANDING_LGRT_ENABLE_SIMD)

#endif // defined(__powerpc__) && !defined(__powerpc64__)

// Except for the Hexagon names, these have special calling conventions, so
// they are assembly, each changing only the registers its convention allows
// and saving any others on the stack. The most negative value negates to
// itself, its magnitude as an unsigned value, so the signed routines need no
// special case for it.

#if defined(__hexagon__)

// Clang calls these, with the normal calling convention, for division.

__attribute__((__alias__("__udivsi3"))) uint32_t __hexagon_udivsi3(uint32_t a, uint32_t b);

__attribute__((__alias__("__divsi3"))) int32_t __hexagon_divsi3(int32_t a, int32_t b);

__attribute__((__alias__("__umodsi3"))) uint32_t __hexagon_umodsi3(uint32_t a, uint32_t b);

__attribute__((__alias__("__modsi3"))) int32_t __hexagon_modsi3(int32_t a, int32_t b);

__attribute__((__alias__("__udivdi3"))) uint64_t __hexagon_udivdi3(uint64_t a, uint64_t b);

__attribute__((__alias__("__divdi3"))) int64_t __hexagon_divdi3(int64_t a, int64_t b);

__attribute__((__alias__("__umoddi3"))) uint64_t __hexagon_umoddi3(uint64_t a, uint64_t b);

__attribute__((__alias__("__moddi3"))) int64_t __hexagon_moddi3(int64_t a, int64_t b);

// Clang calls this for copies of constant sizes, without using its result.
void *__hexagon_memcpy_likely_aligned_min32bytes_mult8bytes(
    void *dest,
    const void *src,
    size_t n
) {
    return __builtin_memcpy(dest, src, n);
}

#endif // defined(__hexagon__)

#if defined(__csky__)

// GCC calls these for switches on ck801 and ck802, optimising for size, with
// the index in a0 and the table following the call, where lr points. They jump
// to the case. All but lr has to be kept, a0 and the C flag included, and none
// of these instructions changes that flag. Entries hold the distance from the
// table to the case, halved but for words, which are aligned to 4 bytes.
#define CSKY_BEGIN(name) \
    ".pushsection .text." name ",\"ax\",@progbits\n\t" \
    ".p2align 1\n\t" \
    ".globl " name "\n\t" \
    ".hidden " name "\n\t" \
    ".type " name ", @function\n\t" \
    name ":\n\t" \
    "subi sp, sp, 4\n\t" \
    "st.w a1, (sp, 0)\n\t"

#define CSKY_END(name) \
    "ld.w a1, (sp, 0)\n\t" \
    "addi sp, sp, 4\n\t" \
    "rts\n\t" \
    ".size " name ", . - " name "\n\t" \
    ".popsection\n\t"

#define CSKY_CASE(name, scale, load) \
    __asm__ ( \
        CSKY_BEGIN(name) \
        scale \
        "addu a1, lr\n\t" \
        load \
        "lsli a1, a1, 1\n\t" \
        "addu lr, a1\n\t" \
        CSKY_END(name) \
    );

CSKY_CASE(
    "___gnu_csky_case_uqi",
    "mov a1, a0\n\t",
    "ld.b a1, (a1, 0)\n\t"
)

CSKY_CASE(
    "___gnu_csky_case_sqi",
    "mov a1, a0\n\t",
    "ld.b a1, (a1, 0)\n\t"
    "sextb a1, a1\n\t"
)

CSKY_CASE(
    "___gnu_csky_case_uhi",
    "lsli a1, a0, 1\n\t",
    "ld.h a1, (a1, 0)\n\t"
)

CSKY_CASE(
    "___gnu_csky_case_shi",
    "lsli a1, a0, 1\n\t",
    "ld.h a1, (a1, 0)\n\t"
    "sexth a1, a1\n\t"
)

__asm__ (
    CSKY_BEGIN("___gnu_csky_case_si")
    "mov a1, lr\n\t"
    "addi a1, 3\n\t"
    "bclri a1, 0\n\t"
    "bclri a1, 1\n\t"
    "mov lr, a1\n\t"
    "lsli a1, a0, 2\n\t"
    "addu a1, lr\n\t"
    "ld.w a1, (a1, 0)\n\t"
    "addu lr, a1\n\t"
    CSKY_END("___gnu_csky_case_si")
);

#undef CSKY_CASE
#undef CSKY_END
#undef CSKY_BEGIN

#endif // defined(__csky__)

#if defined(__sh__)

// The labels of C functions have an underscore in front on sh-elf.
#define SH_LABEL(name) XSTR(__USER_LABEL_PREFIX__) name

#define SH_BEGIN(name) \
    ".pushsection .text." name ",\"ax\",@progbits\n\t" \
    ".p2align 2\n\t" \
    ".globl " SH_LABEL(name) "\n\t" \
    ".hidden " SH_LABEL(name) "\n\t" \
    ".type " SH_LABEL(name) ", @function\n\t" \
    SH_LABEL(name) ":\n\t"

#define SH_END(name) \
    ".size " SH_LABEL(name) ", . - " SH_LABEL(name) "\n\t" \
    ".popsection"

// Called with jsr, with the dividend in r4 and the divisor in r5, returning
// the quotient in r0, or in FPUL for the FPU variants. These keep registers
// that C may change, so each calls C with those saved on the stack, through an
// address relative to the code but on SH-1, which cannot branch that way.
#define SH_PUSH(r) "mov.l " r ", @-r15\n\t"
#define SH_POP(r) "mov.l @r15+, " r "\n\t"

#define SH_HELPER ASM_CALLED

#if defined(__SH1__)
#   define SH_CALL "jsr @r0\n\t"
#   define SH_TARGET(f) ".long " f "\n\t"
#else
#   define SH_CALL "bsrf r0\n\t"
#   define SH_TARGET(f) ".long " f " - 2b\n\t"
#endif

#define SH_STUB(name, save, result, restore) \
    __asm__ ( \
        SH_BEGIN(#name) \
        "sts.l pr, @-r15\n\t" \
        save \
        "mov.l 3f, r0\n\t" \
        SH_CALL \
        "nop\n\t" \
        "2:\n\t" \
        result \
        restore \
        "lds.l @r15+, pr\n\t" \
        "rts\n\t" \
        "nop\n\t" \
        ".p2align 2\n\t" \
        "3:\n\t" \
        SH_TARGET(SH_LABEL("sh" #name)) \
        SH_END(#name) \
    );

#define SH_DIVISION(name, T, f, save, result, restore) \
    SH_HELPER T sh##name(T a, T b) { \
        uint32_t r; \
        \
        return (T)f(a, b, &r); \
    } \
    \
    SH_STUB(name, save, result, restore)

// The default strategy. These may change only r0, r1, T, PR, MACH, and MACL.
#define SH_SAVE_R2_TO_R7 \
    SH_PUSH("r2") \
    SH_PUSH("r3") \
    SH_PUSH("r4") \
    SH_PUSH("r5") \
    SH_PUSH("r6") \
    SH_PUSH("r7")

#define SH_RESTORE_R2_TO_R7 \
    SH_POP("r7") \
    SH_POP("r6") \
    SH_POP("r5") \
    SH_POP("r4") \
    SH_POP("r3") \
    SH_POP("r2")

SH_DIVISION(__udivsi3_i4i, uint32_t, udivmod32, SH_SAVE_R2_TO_R7, "", SH_RESTORE_R2_TO_R7)

SH_DIVISION(__sdivsi3_i4i, int32_t, divmod32, SH_SAVE_R2_TO_R7, "", SH_RESTORE_R2_TO_R7)

#if defined(__SH_FPU_ANY__)

// For -mdiv=call-fp. __udivsi3_i4 may change r0, r1, r4, and r5. __sdivsi3_i4,
// called through r1, must preserve r0 to r7 and T. Both must keep the FPSCR
// mode bits, which C leaves alone without floating-point types.

SH_DIVISION(
    __udivsi3_i4, uint32_t, udivmod32,
    SH_PUSH("r2")
    SH_PUSH("r3")
    SH_PUSH("r6")
    SH_PUSH("r7"),
    "lds r0, fpul\n\t",
    SH_POP("r7")
    SH_POP("r6")
    SH_POP("r3")
    SH_POP("r2")
)

SH_DIVISION(
    __sdivsi3_i4, int32_t, divmod32,
    SH_PUSH("r0")
    SH_PUSH("r1")
    SH_SAVE_R2_TO_R7
    "movt r0\n\t"
    SH_PUSH("r0"),
    "lds r0, fpul\n\t",
    SH_POP("r0")
    "shlr r0\n\t"
    SH_RESTORE_R2_TO_R7
    SH_POP("r1")
    SH_POP("r0")
)

#endif // defined(__SH_FPU_ANY__)

// For -mdiv=call-div1 and older CPUs. These keep the normal argument and
// result registers, so C callers may call them too. __udivsi3 may change only
// r0, r1, r4, T, and PR, and __sdivsi3 only r0 to r3, T, and PR.

SH_DIVISION(
    __udivsi3, uint32_t, udivmod32,
    SH_PUSH("r2")
    SH_PUSH("r3")
    SH_PUSH("r5")
    SH_PUSH("r6")
    SH_PUSH("r7"), "",
    SH_POP("r7")
    SH_POP("r6")
    SH_POP("r5")
    SH_POP("r3")
    SH_POP("r2")
)

SH_DIVISION(
    __sdivsi3, int32_t, divmod32,
    SH_PUSH("r4")
    SH_PUSH("r5")
    SH_PUSH("r6")
    SH_PUSH("r7"), "",
    SH_POP("r7")
    SH_POP("r6")
    SH_POP("r5")
    SH_POP("r4")
)

// Copies of words from r5 to r4, called with jsr. All but what is stated comes
// back unchanged, the register holding the address included. Each __movmemSIn
// copies n bytes and changes only r0.
#define SH_MOVMEM_FIXED(name, n) \
    __asm__ ( \
        SH_BEGIN(name) \
        ".set .Lsh_offset, 0\n\t" \
        ".rept " #n " / 4\n\t" \
        "mov.l @(.Lsh_offset, r5), r0\n\t" \
        "mov.l r0, @(.Lsh_offset, r4)\n\t" \
        ".set .Lsh_offset, .Lsh_offset + 4\n\t" \
        ".endr\n\t" \
        "rts\n\t" \
        "nop\n\t" \
        SH_END(name) \
    );

SH_MOVMEM_FIXED("__movmemSI4", 4)
SH_MOVMEM_FIXED("__movmemSI8", 8)
SH_MOVMEM_FIXED("__movmemSI12", 12)
SH_MOVMEM_FIXED("__movmemSI12_i4", 12)
SH_MOVMEM_FIXED("__movmemSI16", 16)
SH_MOVMEM_FIXED("__movmemSI20", 20)
SH_MOVMEM_FIXED("__movmemSI24", 24)
SH_MOVMEM_FIXED("__movmemSI28", 28)
SH_MOVMEM_FIXED("__movmemSI32", 32)
SH_MOVMEM_FIXED("__movmemSI36", 36)
SH_MOVMEM_FIXED("__movmemSI40", 40)
SH_MOVMEM_FIXED("__movmemSI44", 44)
SH_MOVMEM_FIXED("__movmemSI48", 48)
SH_MOVMEM_FIXED("__movmemSI52", 52)
SH_MOVMEM_FIXED("__movmemSI56", 56)
SH_MOVMEM_FIXED("__movmemSI60", 60)
SH_MOVMEM_FIXED("__movmemSI64", 64)

#undef SH_MOVMEM_FIXED

// The objects are of any type, which these may alias.
typedef uint32_t sh_word __attribute__((__may_alias__));

// For n words, r6 holds 16 - n % 16 + 16 * (n / 16 - 1). This changes only r0,
// r4, r5, r6, and T. The words are hidden for no compiler to make the loop a
// call to memcpy, which could compile into a call to this.
SH_HELPER void sh__movmem(sh_word *dest, const sh_word *src, uint32_t encoded) {
    uint32_t n = ((((encoded - 1) | 15) + 1) << 1) - encoded;

    for (; n != 0; n--) {
        uint32_t word = *src++;

        HIDE_BIT(word);
        *dest++ = word;
    }
}

SH_STUB(
    __movmem,
    SH_PUSH("r1")
    SH_PUSH("r2")
    SH_PUSH("r3")
    SH_PUSH("r7"), "",
    SH_POP("r7")
    SH_POP("r3")
    SH_POP("r2")
    SH_POP("r1")
)

// These copy r6 + 1 pairs of words, __movmem_i4_odd after one word more. They
// change only r0, r1, r4, r5, r6, and T.
#define SH_MOVMEM_PAIRS(name, first) \
    SH_HELPER void sh##name(sh_word *dest, const sh_word *src, int32_t pairs) { \
        first \
        for (; pairs >= 0; pairs--) { \
            uint32_t a = *src++; \
            uint32_t b = *src++; \
            \
            HIDE_BIT(a); \
            HIDE_BIT(b); \
            *dest++ = a; \
            *dest++ = b; \
        } \
    } \
    \
    SH_STUB( \
        name, \
        SH_PUSH("r2") \
        SH_PUSH("r3") \
        SH_PUSH("r7"), \
        "", \
        SH_POP("r7") \
        SH_POP("r3") \
        SH_POP("r2") \
    )

SH_MOVMEM_PAIRS(__movmem_i4_even, )
SH_MOVMEM_PAIRS(
    __movmem_i4_odd,
    *dest++ = *src++;
)

#undef SH_MOVMEM_PAIRS
#undef SH_DIVISION
#undef SH_STUB
#undef SH_TARGET
#undef SH_CALL
#undef SH_HELPER
#undef SH_SAVE_R2_TO_R7
#undef SH_RESTORE_R2_TO_R7
#undef SH_PUSH
#undef SH_POP

// Arithmetic shifts of r4 by constants, for cores without shad and shld,
// called with jsr like the above. These change only r4 and T.
#define SH_ASHIFTRT(n) \
    __asm__ ( \
        SH_BEGIN("__ashiftrt_r4_" #n) \
        ".if " #n " >= 16\n\t" \
        "shlr16 r4\n\t" \
        "exts.w r4, r4\n\t" \
        ".rept " #n " - 16\n\t" \
        "shar r4\n\t" \
        ".endr\n\t" \
        ".else\n\t" \
        ".rept " #n "\n\t" \
        "shar r4\n\t" \
        ".endr\n\t" \
        ".endif\n\t" \
        "rts\n\t" \
        "nop\n\t" \
        SH_END("__ashiftrt_r4_" #n) \
    );

SH_ASHIFTRT(0)
SH_ASHIFTRT(1)
SH_ASHIFTRT(2)
SH_ASHIFTRT(3)
SH_ASHIFTRT(4)
SH_ASHIFTRT(5)
SH_ASHIFTRT(6)
SH_ASHIFTRT(7)
SH_ASHIFTRT(8)
SH_ASHIFTRT(9)
SH_ASHIFTRT(10)
SH_ASHIFTRT(11)
SH_ASHIFTRT(12)
SH_ASHIFTRT(13)
SH_ASHIFTRT(14)
SH_ASHIFTRT(15)
SH_ASHIFTRT(16)
SH_ASHIFTRT(17)
SH_ASHIFTRT(18)
SH_ASHIFTRT(19)
SH_ASHIFTRT(20)
SH_ASHIFTRT(21)
SH_ASHIFTRT(22)
SH_ASHIFTRT(23)
SH_ASHIFTRT(24)
SH_ASHIFTRT(25)
SH_ASHIFTRT(26)
SH_ASHIFTRT(27)
SH_ASHIFTRT(28)
SH_ASHIFTRT(29)
SH_ASHIFTRT(30)
SH_ASHIFTRT(31)
SH_ASHIFTRT(32)

#undef SH_ASHIFTRT

// r0 = r4 shifted by the low 5 bits of r0, for the same cores and called the
// same way. These change only r0 and T, so r4 comes back from the stack.
#define SH_SHIFT_R0(name, op) \
    __asm__ ( \
        SH_BEGIN(name) \
        "mov.l r4, @-r15\n\t" \
        "tst #16, r0\n\t" \
        "bt 1f\n\t" \
        op "16 r4\n\t" \
        "1:\n\t" \
        "tst #8, r0\n\t" \
        "bt 2f\n\t" \
        op "8 r4\n\t" \
        "2:\n\t" \
        "tst #4, r0\n\t" \
        "bt 3f\n\t" \
        op "2 r4\n\t" \
        op "2 r4\n\t" \
        "3:\n\t" \
        "tst #2, r0\n\t" \
        "bt 4f\n\t" \
        op "2 r4\n\t" \
        "4:\n\t" \
        "tst #1, r0\n\t" \
        "bt 5f\n\t" \
        op " r4\n\t" \
        "5:\n\t" \
        "mov r4, r0\n\t" \
        "rts\n\t" \
        "mov.l @r15+, r4\n\t" \
        SH_END(name) \
    );

SH_SHIFT_R0("__ashlsi3_r0", "shll")
SH_SHIFT_R0("__lshrsi3_r0", "shlr")

#undef SH_SHIFT_R0

// These have the ordinary convention and use the low 5 bits of the count. Each
// bit of it is hidden before its shift by a constant, for no compiler to merge
// these into a shift by a variable amount, which can be a call to the routine
// itself.
#define SH_SHIFT_IF_BIT(x, op, count, amount) do { \
    uint32_t SH_SHIFT_IF_BIT_bit = (count) & (amount); \
    \
    HIDE_BIT(SH_SHIFT_IF_BIT_bit); \
    if (SH_SHIFT_IF_BIT_bit != 0) { \
        (x) op (amount); \
    } \
} while (0)

static inline uint32_t sh_shift_left(uint32_t x, uint32_t count) {
    SH_SHIFT_IF_BIT(x, <<=, count, 16);
    SH_SHIFT_IF_BIT(x, <<=, count, 8);
    SH_SHIFT_IF_BIT(x, <<=, count, 4);
    SH_SHIFT_IF_BIT(x, <<=, count, 2);
    SH_SHIFT_IF_BIT(x, <<=, count, 1);
    return x;
}

static inline uint32_t sh_shift_right(uint32_t x, uint32_t count) {
    SH_SHIFT_IF_BIT(x, >>=, count, 16);
    SH_SHIFT_IF_BIT(x, >>=, count, 8);
    SH_SHIFT_IF_BIT(x, >>=, count, 4);
    SH_SHIFT_IF_BIT(x, >>=, count, 2);
    SH_SHIFT_IF_BIT(x, >>=, count, 1);
    return x;
}

#undef SH_SHIFT_IF_BIT

int32_t __ashlsi3(int32_t a, int b) {
    return (int32_t)sh_shift_left((uint32_t)a, (uint32_t)b);
}

int32_t __lshrsi3(int32_t a, int b) {
    return (int32_t)sh_shift_right((uint32_t)a, (uint32_t)b);
}

// A negative value shifts as its complement, for ones to come in.
int32_t __ashrsi3(int32_t a, int b) {
    uint32_t x = (uint32_t)a;
    uint32_t flip = (uint32_t)0 - (x >> 31);

    HIDE_BIT(flip);
    return (int32_t)(sh_shift_right(x ^ flip, (uint32_t)b) ^ flip);
}

#if defined(__SH_FPU_DOUBLE__) && defined(FREESTANDING_LGRT_ENABLE_FLOAT)

// GCC 4.8 and 4.9 change precision by loading FPSCR from these: the first
// entry for the precision that functions do not start in, the second for the
// one they do. Both round to nearest and flush denormal numbers to zero, as
// those would otherwise raise FPU errors on SH-4.
__attribute__((__used__, __section__(".rodata.__fpscr_values")))
const uint32_t __fpscr_values[2] = {
#if defined(__SH4_SINGLE__) || defined(__SH2A_SINGLE__)
    0x000c0000, 0x00040000
#else
    0x00040000, 0x000c0000
#endif
};

#endif

#endif // defined(__sh__)

#if defined(__sparc__) && !defined(__arch64__)

// GCC and Clang call these where the core has no instructions to multiply or
// to divide. They are ordinary functions, under other names, for which the ABI
// adds what follows.

// The low half of the product goes in %o0 and the high one in %o1, the reverse
// of how C returns 64 bits. A multiplication here could compile into a call to
// this, so it adds shifted words instead.
uint64_t sparc_umul(uint32_t a, uint32_t b) __asm__ (".umul");
uint64_t sparc_umul(uint32_t a, uint32_t b) {
    uint32_t small = a < b ? a : b;
    uint32_t big = a < b ? b : a;
    uint32_t big_high = 0;
    uint32_t low = 0;
    uint32_t high = 0;

    while (small != 0) {
        uint8_t bit = (uint8_t)(small & 1);
        uint32_t mask;
        uint32_t added;

        HIDE_BIT(bit);
        mask = (uint32_t)0 - (uint32_t)bit;
        added = big & mask;
        low += added;
        high += (big_high & mask) + (uint32_t)(low < added);
        big_high = (big_high << 1) | (big >> 31);
        big <<= 1;
        small >>= 1;
    }
    return JOIN_32(low, high);
}

// A divisor of 0 raises software trap 2.
static inline void sparc_check_divisor(uint32_t divisor) {
    if (divisor == 0) {
        __asm__ volatile ("ta 2");
    }
}

int32_t sparc_div(int32_t a, int32_t b) __asm__ (".div");
int32_t sparc_div(int32_t a, int32_t b) {
    sparc_check_divisor((uint32_t)b);
    return __divsi3(a, b);
}

int32_t sparc_rem(int32_t a, int32_t b) __asm__ (".rem");
int32_t sparc_rem(int32_t a, int32_t b) {
    sparc_check_divisor((uint32_t)b);
    return __modsi3(a, b);
}

uint32_t sparc_udiv(uint32_t a, uint32_t b) __asm__ (".udiv");
uint32_t sparc_udiv(uint32_t a, uint32_t b) {
    sparc_check_divisor(b);
    return __udivsi3(a, b);
}

uint32_t sparc_urem(uint32_t a, uint32_t b) __asm__ (".urem");
uint32_t sparc_urem(uint32_t a, uint32_t b) {
    sparc_check_divisor(b);
    return __umodsi3(a, b);
}

#endif // defined(__sparc__) && !defined(__arch64__)

#if defined(__hppa__) && !defined(__LP64__)

// Millicode, called with bl ...,%r31, with the operands in %r26 and %r25.
// These return the result in %r29 through bv %r0(%r31) and may change only
// %r1, %r25, %r26, %r29, %r31, and the carry bits. So they call C, which takes
// the same operands, with the others that it may change saved on a frame of
// their own, below its frame marker. A zero divisor traps, with the
// instruction that the runtime architecture names.
#define HPPA_ZERO_TRAP "addit,= 0, %r25, %r0\n\t"

#define HPPA_MILLICODE(name, check, f) \
    __asm__ ( \
        ".pushsection .text." name ",\"ax\",@progbits\n\t" \
        ".p2align 2\n\t" \
        ".globl " name "\n\t" \
        ".hidden " name "\n\t" \
        ".type " name ", @function\n\t" \
        name ":\n\t" \
        check \
        "ldo 128(%r30), %r30\n\t" \
        "stw %r2, -128(%r30)\n\t" \
        "stw %r19, -124(%r30)\n\t" \
        "stw %r20, -120(%r30)\n\t" \
        "stw %r21, -116(%r30)\n\t" \
        "stw %r22, -112(%r30)\n\t" \
        "stw %r23, -108(%r30)\n\t" \
        "stw %r24, -104(%r30)\n\t" \
        "stw %r28, -100(%r30)\n\t" \
        "stw %r31, -96(%r30)\n\t" \
        "bl " f ", %r2\n\t" \
        "nop\n\t" \
        "copy %r28, %r29\n\t" \
        "ldw -128(%r30), %r2\n\t" \
        "ldw -124(%r30), %r19\n\t" \
        "ldw -120(%r30), %r20\n\t" \
        "ldw -116(%r30), %r21\n\t" \
        "ldw -112(%r30), %r22\n\t" \
        "ldw -108(%r30), %r23\n\t" \
        "ldw -104(%r30), %r24\n\t" \
        "ldw -100(%r30), %r28\n\t" \
        "ldw -96(%r30), %r31\n\t" \
        "bv %r0(%r31)\n\t" \
        "ldo -128(%r30), %r30\n\t" \
        ".size " name ", . - " name "\n\t" \
        ".popsection" \
    );

HPPA_MILLICODE("$$divU", HPPA_ZERO_TRAP, "__udivsi3")
HPPA_MILLICODE("$$remU", HPPA_ZERO_TRAP, "__umodsi3")
HPPA_MILLICODE("$$divI", HPPA_ZERO_TRAP, "__divsi3")
HPPA_MILLICODE("$$remI", HPPA_ZERO_TRAP, "__modsi3")

// Where GCC cannot use the floating-point registers to multiply.
HPPA_MILLICODE("$$mulI", "", "__mulsi3")

// These also trap with a divisor of -1 where the division overflows, which for
// the remainder is documented to include a dividend of 0.

__asm__ (
    ".pushsection .text.$$divoI,\"ax\",@progbits\n\t"
    ".p2align 2\n\t"
    ".globl $$divoI\n\t"
    ".hidden $$divoI\n\t"
    ".type $$divoI, @function\n\t"
    "$$divoI:\n\t"
    "comib,<>,n -1, %r25, 0f\n\t"
    "addo %r26, %r25, %r0\n\t"
    "0:\n\t"
    "b,n $$divI\n\t"
    ".size $$divoI, . - $$divoI\n\t"
    ".popsection"
);

__asm__ (
    ".pushsection .text.$$remoI,\"ax\",@progbits\n\t"
    ".p2align 2\n\t"
    ".globl $$remoI\n\t"
    ".hidden $$remoI\n\t"
    ".type $$remoI, @function\n\t"
    "$$remoI:\n\t"
    "comib,<>,n -1, %r25, 0f\n\t"
    "addo %r26, %r25, %r0\n\t"
    "addit,= 0, %r26, %r0\n\t"
    "0:\n\t"
    "b,n $$remI\n\t"
    ".size $$remoI, . - $$remoI\n\t"
    ".popsection"
);

// Division by constants, called the same way but for the divisor, with the
// same registers to change, where GCC cannot use the floating-point registers
// to multiply.
#define HPPA_DIV_BY(kind, n) \
    __asm__ ( \
        ".pushsection .text.$$div" kind "_" #n ",\"ax\",@progbits\n\t" \
        ".p2align 2\n\t" \
        ".globl $$div" kind "_" #n "\n\t" \
        ".hidden $$div" kind "_" #n "\n\t" \
        ".type $$div" kind "_" #n ", @function\n\t" \
        "$$div" kind "_" #n ":\n\t" \
        "b $$div" kind "\n\t" \
        "ldi " #n ", %r25\n\t" \
        ".size $$div" kind "_" #n ", . - $$div" kind "_" #n "\n\t" \
        ".popsection" \
    );

HPPA_DIV_BY("I", 2)
HPPA_DIV_BY("I", 3)
HPPA_DIV_BY("I", 4)
HPPA_DIV_BY("I", 5)
HPPA_DIV_BY("I", 6)
HPPA_DIV_BY("I", 7)
HPPA_DIV_BY("I", 8)
HPPA_DIV_BY("I", 9)
HPPA_DIV_BY("I", 10)
HPPA_DIV_BY("I", 12)
HPPA_DIV_BY("I", 14)
HPPA_DIV_BY("I", 15)
HPPA_DIV_BY("I", 16)
HPPA_DIV_BY("I", 17)
HPPA_DIV_BY("U", 3)
HPPA_DIV_BY("U", 5)
HPPA_DIV_BY("U", 6)
HPPA_DIV_BY("U", 7)
HPPA_DIV_BY("U", 9)
HPPA_DIV_BY("U", 10)
HPPA_DIV_BY("U", 12)
HPPA_DIV_BY("U", 14)
HPPA_DIV_BY("U", 15)
HPPA_DIV_BY("U", 17)

#undef HPPA_DIV_BY

// Compilers call this for calls through function pointers, with bl
// $$dyncall,%r31, the pointer in %r22, and the return address already in %r2,
// so it branches to the function instead of returning. A pointer with bit 30
// set addresses, with its low two bits cleared, a descriptor holding the code
// address and the value for %r19. It may change only %r1, %r19, %r22, and
// %r31, and must not touch the stack.

__asm__ (
    ".pushsection .text.$$dyncall,\"ax\",@progbits\n\t"
    ".p2align 2\n\t"
    ".globl $$dyncall\n\t"
    ".hidden $$dyncall\n\t"
    ".type $$dyncall, @function\n\t"
    "$$dyncall:\n\t"
    "extru %r22, 30, 1, %r1\n\t"
    "comib,=,n 0, %r1, 0f\n\t"
    "depi 0, 31, 2, %r22\n\t"
    "ldw 4(%r22), %r19\n\t"
    "ldw 0(%r22), %r1\n\t"
    "bv %r0(%r1)\n\t"
    "nop\n\t"
    "0:\n\t"
    "bv %r0(%r22)\n\t"
    "nop\n\t"
    ".size $$dyncall, . - $$dyncall\n\t"
    ".popsection"
);

// GCC calls this before comparing function pointers. Descriptors of one
// function can differ in address but hold the same code address. Values close
// to 0 or to the top of memory are markers, such as -1, rather than pointers.
uintptr_t __canonicalize_funcptr_for_compare(uintptr_t f) {
    if ((f & 2) == 0 || f < 4096 || f >= (uintptr_t)0 - 4096) {
        return f;
    }
    typedef uintptr_t hppa_word __attribute__((__may_alias__));

    return *(const hppa_word *)(f & ~(uintptr_t)3);
}

#endif // defined(__hppa__) && !defined(__LP64__)

#if defined(__alpha__)

// Called with jsr $23,($27),name, with the dividend in $24 and the divisor in
// $25, these return the result in $27 through ret $31,($23),1 and may change
// only $23, $27, and $28. So they call C with all that it may change saved on
// the stack, allocating the space first, as nothing below $30 is safe. The
// 32-bit routines get sign-extended operands and return sign-extended results,
// as C has those types. A zero divisor traps, with the instruction of
// __builtin_trap.
//
// Linkers turn the calls into branches that leave $27 alone, so the address
// for $29 comes from a branch here. The sequence numbers must be unique in the
// file, where the compiler goes up from 1 for its own.
#define ALPHA_DIVISION(name, sequence, T, f) \
    ASM_CALLED T alpha##name(T a, T b) { \
        if (b == 0) { \
            TRAP(); \
        } \
        return f(a, b); \
    } \
    \
    __asm__ ( \
        ".pushsection .text." #name ",\"ax\",@progbits\n\t" \
        ".p2align 2\n\t" \
        ".globl " #name "\n\t" \
        ".hidden " #name "\n\t" \
        ".type " #name ", @function\n\t" \
        #name ":\n\t" \
        "lda $30, -176($30)\n\t" \
        "stq $0, 0($30)\n\t" \
        "stq $1, 8($30)\n\t" \
        "stq $2, 16($30)\n\t" \
        "stq $3, 24($30)\n\t" \
        "stq $4, 32($30)\n\t" \
        "stq $5, 40($30)\n\t" \
        "stq $6, 48($30)\n\t" \
        "stq $7, 56($30)\n\t" \
        "stq $8, 64($30)\n\t" \
        "stq $16, 72($30)\n\t" \
        "stq $17, 80($30)\n\t" \
        "stq $18, 88($30)\n\t" \
        "stq $19, 96($30)\n\t" \
        "stq $20, 104($30)\n\t" \
        "stq $21, 112($30)\n\t" \
        "stq $22, 120($30)\n\t" \
        "stq $23, 128($30)\n\t" \
        "stq $24, 136($30)\n\t" \
        "stq $25, 144($30)\n\t" \
        "stq $26, 152($30)\n\t" \
        "stq $29, 160($30)\n\t" \
        "br $28, 1f\n\t" \
        "1:\n\t" \
        "ldah $29, 0($28) !gpdisp!" sequence "\n\t" \
        "lda $29, 0($29) !gpdisp!" sequence "\n\t" \
        "mov $24, $16\n\t" \
        "mov $25, $17\n\t" \
        "ldq $27, alpha" #name "($29) !literal\n\t" \
        "jsr $26, ($27), alpha" #name "\n\t" \
        "mov $0, $27\n\t" \
        "ldq $0, 0($30)\n\t" \
        "ldq $1, 8($30)\n\t" \
        "ldq $2, 16($30)\n\t" \
        "ldq $3, 24($30)\n\t" \
        "ldq $4, 32($30)\n\t" \
        "ldq $5, 40($30)\n\t" \
        "ldq $6, 48($30)\n\t" \
        "ldq $7, 56($30)\n\t" \
        "ldq $8, 64($30)\n\t" \
        "ldq $16, 72($30)\n\t" \
        "ldq $17, 80($30)\n\t" \
        "ldq $18, 88($30)\n\t" \
        "ldq $19, 96($30)\n\t" \
        "ldq $20, 104($30)\n\t" \
        "ldq $21, 112($30)\n\t" \
        "ldq $22, 120($30)\n\t" \
        "ldq $23, 128($30)\n\t" \
        "ldq $24, 136($30)\n\t" \
        "ldq $25, 144($30)\n\t" \
        "ldq $26, 152($30)\n\t" \
        "ldq $29, 160($30)\n\t" \
        "lda $30, 176($30)\n\t" \
        "ret $31, ($23), 1\n\t" \
        ".size " #name ", . - " #name "\n\t" \
        ".popsection" \
    );

ALPHA_DIVISION(__divqu, "900101", uint64_t, __udivdi3)
ALPHA_DIVISION(__remqu, "900102", uint64_t, __umoddi3)
ALPHA_DIVISION(__divq, "900103", int64_t, __divdi3)
ALPHA_DIVISION(__remq, "900104", int64_t, __moddi3)
ALPHA_DIVISION(__divlu, "900105", uint32_t, __udivsi3)
ALPHA_DIVISION(__remlu, "900106", uint32_t, __umodsi3)
ALPHA_DIVISION(__divl, "900107", int32_t, __divsi3)
ALPHA_DIVISION(__reml, "900108", int32_t, __modsi3)

#undef ALPHA_DIVISION

#endif // defined(__alpha__)

#if defined(__ARM_EABI__) && defined(__ARM_ARCH_ISA_THUMB)

// GCC dispatches Thumb-1 jump tables through these, calling them with bl just
// before the table and with the case index in r0. bl does not change state on
// ARMv4T, so they are Thumb code for that architecture, whatever state the
// rest of the file is in. They may change only ip, lr, and the flags, so r1
// waits in ip while they use it.

// Each helper has a section of its own, so that linkers can drop it if unused,
// and switches to Thumb state and unified syntax for its code, then back to
// the file's own state and syntax. File-scope assembly starts in unified
// syntax with Clang, in Thumb-2 state, and where GCC says so, and in divided
// syntax otherwise.
#if defined(__clang__) || defined(__thumb2__) || defined(__ARM_ASM_SYNTAX_UNIFIED__)
#   define THUMB1_SYNTAX ""
#else
#   define THUMB1_SYNTAX ".syntax divided\n\t"
#endif

#if defined(__thumb__)
#   define THUMB1_RESTORE THUMB1_SYNTAX
#else
#   define THUMB1_RESTORE \
        ".arm\n\t" \
        THUMB1_SYNTAX
#endif

#define THUMB1_BEGIN(name) \
    ".pushsection .text." name ",\"ax\",%progbits\n\t" \
    ".syntax unified\n\t" \
    ".thumb\n\t" \
    ".p2align 2\n\t" \
    ".globl " name "\n\t" \
    ".hidden " name "\n\t" \
    ".type " name ", %function\n\t" \
    ".thumb_func\n\t" \
    name ":\n\t"

#define THUMB1_END(name) \
    ".size " name ", . - " name "\n\t" \
    THUMB1_RESTORE \
    ".popsection"

// The byte and halfword tables start at lr - 1 and hold halved distances to
// the targets. Doubled and added to lr, these keep its Thumb bit. The signed
// loads take only register offsets, so base points r1 where [r1, r0] addresses
// entry r0: at the table start for bytes, and r0 bytes further for halfwords.
#define THUMB1_CASE(name, base, load) \
    THUMB1_BEGIN(name) \
    "mov ip, r1\n\t" \
    base \
    load " r1, [r1, r0]\n\t" \
    "lsls r1, r1, #1\n\t" \
    "add lr, r1\n\t" \
    "mov r1, ip\n\t" \
    "bx lr\n\t" \
    THUMB1_END(name)

#define THUMB1_BYTE_BASE \
    "mov r1, lr\n\t" \
    "subs r1, #1\n\t"
#define THUMB1_HALF_BASE \
    "subs r1, r0, #1\n\t" \
    "add r1, lr\n\t"

__asm__ (
    THUMB1_CASE("__gnu_thumb1_case_uqi", THUMB1_BYTE_BASE, "ldrb")
);

__asm__ (
    THUMB1_CASE("__gnu_thumb1_case_sqi", THUMB1_BYTE_BASE, "ldrsb")
);

__asm__ (
    THUMB1_CASE("__gnu_thumb1_case_uhi", THUMB1_HALF_BASE, "ldrh")
);

__asm__ (
    THUMB1_CASE("__gnu_thumb1_case_shi", THUMB1_HALF_BASE, "ldrsh")
);

// The word table starts at (lr + 2) & ~3, the first word boundary at or after
// lr - 1, and holds distances in bytes, whose sums with its start lack the
// Thumb bit, so mov, which keeps the state, branches to them instead of bx.
__asm__ (
    THUMB1_BEGIN("__gnu_thumb1_case_si")
    "mov ip, r1\n\t"
    "mov r1, lr\n\t"
    "adds r1, #2\n\t"
    "lsrs r1, r1, #2\n\t"
    "lsls r1, r1, #2\n\t"
    "mov lr, r1\n\t"
    "lsls r1, r0, #2\n\t"
    "add r1, lr\n\t"
    "ldr r1, [r1]\n\t"
    "add lr, r1\n\t"
    "mov r1, ip\n\t"
    "mov pc, lr\n\t"
    THUMB1_END("__gnu_thumb1_case_si")
);

#endif // defined(__ARM_EABI__) && defined(__ARM_ARCH_ISA_THUMB)

#if defined(__arc__)

// When optimising for size, GCC saves and restores r13 to rN in prologues and
// epilogues with calls to these, finding r13 at sp and each further register
// in the next word up. Each entry point handles its highest register and falls
// through to the one for the next lower register. None changes the flags.

#define ARC_ENTRY(name, end) \
    ".globl " name "\n\t" \
    ".hidden " name "\n\t" \
    ".type " name ", @function\n\t" \
    name ":\n\t" \
    ".size " name ", " end " - " name "\n\t"

// Defines the entry points prefix N suffix, for N from ARC_FIRST down to 14,
// all extending to end, each followed by op(rN, d), where the slot of rN is d
// bytes above sp. ARC_FIRST is 25, or 15 with the reduced register file, which
// lacks r16 to r25: the assembler would otherwise mark the object as using the
// full register file.
#if defined(__ARC_RF16__)
#   define ARC_FIRST "15"
#   define ARC_HIGH_ENTRIES(prefix, suffix, end, op)
#else // defined(__ARC_RF16__)
#   define ARC_FIRST "25"
#   define ARC_HIGH_ENTRIES(prefix, suffix, end, op) \
        ARC_ENTRY(prefix "25" suffix, end) \
        op("r25", "48") \
        ARC_ENTRY(prefix "24" suffix, end) \
        op("r24", "44") \
        ARC_ENTRY(prefix "23" suffix, end) \
        op("r23", "40") \
        ARC_ENTRY(prefix "22" suffix, end) \
        op("r22", "36") \
        ARC_ENTRY(prefix "21" suffix, end) \
        op("r21", "32") \
        ARC_ENTRY(prefix "20" suffix, end) \
        op("r20", "28") \
        ARC_ENTRY(prefix "19" suffix, end) \
        op("r19", "24") \
        ARC_ENTRY(prefix "18" suffix, end) \
        op("r18", "20") \
        ARC_ENTRY(prefix "17" suffix, end) \
        op("r17", "16") \
        ARC_ENTRY(prefix "16" suffix, end) \
        op("r16", "12")
#endif // defined(__ARC_RF16__)

#define ARC_ENTRIES(prefix, suffix, end, op) \
    ARC_HIGH_ENTRIES(prefix, suffix, end, op) \
    ARC_ENTRY(prefix "15" suffix, end) \
    op("r15", "8") \
    ARC_ENTRY(prefix "14" suffix, end) \
    op("r14", "4")

// Opens the section of the family of entry points prefix N suffix, named after
// the first of them, so that linkers can drop the family if unused.
#define ARC_SECTION(prefix, suffix) \
    ".pushsection .text." prefix ARC_FIRST suffix ",\"ax\",@progbits\n\t" \
    ".p2align 2\n\t"

#define ARC_STORE(reg, d) "st " reg ", [sp, " d "]\n\t"
#define ARC_LOAD(reg, d) "ld " reg ", [sp, " d "]\n\t"

__asm__ (
    ARC_SECTION("__st_r13_to_r", "")
    ARC_ENTRIES("__st_r13_to_r", "", ".Larc_st_end", ARC_STORE)
    "j_s.d [blink]\n\t"
    ARC_STORE("r13", "0")
    ".Larc_st_end:\n\t"
    ".popsection"
);

__asm__ (
    ARC_SECTION("__ld_r13_to_r", "")
    ARC_ENTRIES("__ld_r13_to_r", "", ".Larc_ld_end", ARC_LOAD)
    "j_s.d [blink]\n\t"
    ARC_LOAD("r13", "0")
    ".Larc_ld_end:\n\t"
    ".popsection"
);

// Epilogues end by jumping to these, with r12 holding the size of the frame
// area below the saved blink, to also pop that area and blink and return to
// the function's caller. blink is loaded before sp moves, so that the jump
// waits less for it.
__asm__ (
    ARC_SECTION("__ld_r13_to_r", "_ret")
    ARC_ENTRIES("__ld_r13_to_r", "_ret", ".Larc_ld_ret_end", ARC_LOAD)
    "ld blink, [sp, r12]\n\t"
    ARC_LOAD("r13", "0")
    "add sp, sp, r12\n\t"
    "j_s.d [blink]\n\t"
    "add_s sp, sp, 4\n\t"
    ".Larc_ld_ret_end:\n\t"
    ".popsection"
);

#endif // defined(__arc__)

#if defined(__MSP430__)

// The run-time ABI of MSP430: those of up to 4 bytes have the convention of C,
// those of 8 bytes take their first operand in R11:R8 and their second in
// R15:R12, or a count in R12, and return in R15:R12, the lowest word in the
// lowest register.

#if defined(__MSP430X_LARGE__)
#   define MSP430_CALL "calla"
#   define MSP430_RET "reta\n\t"
#   define MSP430_ADDA "adda"
#else
#   define MSP430_CALL "call"
#   define MSP430_RET "ret\n\t"
#   define MSP430_ADDA "add"
#endif

#define MSP430_ENTRY(name) \
    ".globl " name "\n\t" \
    ".hidden " name "\n\t" \
    ".type " name ", @function\n\t" \
    name ":\n\t"

#define MSP430_SIZED(name, end) \
    MSP430_ENTRY(name) \
    ".size " name ", " end " - " name "\n\t"

#define MSP430_BEGIN(name) \
    ".pushsection .text." name ",\"ax\",@progbits\n\t" \
    ".p2align 1\n\t" \
    MSP430_ENTRY(name)

#define MSP430_END(name) \
    ".size " name ", . - " name "\n\t" \
    ".popsection"

// Calls a routine in C, which takes the second operand on the stack.
#define MSP430_FROM_64(name, f) \
    __asm__ ( \
        MSP430_BEGIN(name) \
        "push r15\n\t" \
        "push r14\n\t" \
        "push r13\n\t" \
        "push r12\n\t" \
        "mov r8, r12\n\t" \
        "mov r9, r13\n\t" \
        "mov r10, r14\n\t" \
        "mov r11, r15\n\t" \
        MSP430_CALL " #" f "\n\t" \
        MSP430_ADDA " #8, r1\n\t" \
        MSP430_RET \
        MSP430_END(name) \
    );

// GCC gives the generic routines above the names and the conventions of the
// run-time ABI by itself, which Clang does not, and 4.9 and 5 two other names
// for those of two.
#if !defined(__clang__) && __GNUC__ < 6
__asm__ (
    ".globl __mspabi_divul\n\t"
    ".hidden __mspabi_divul\n\t"
    ".set __mspabi_divul, __mspabi_divlu\n\t"
    ".globl __mspabi_divull\n\t"
    ".hidden __mspabi_divull\n\t"
    ".set __mspabi_divull, __mspabi_divllu"
);
#endif

#if defined(__clang__)

MSP430_FROM_64("__mspabi_divlli", "__divdi3")
MSP430_FROM_64("__mspabi_divull", "__udivdi3")
MSP430_FROM_64("__mspabi_remlli", "__moddi3")
MSP430_FROM_64("__mspabi_remull", "__umoddi3")
MSP430_FROM_64("__mspabi_mpyll", "__muldi3")

__attribute__((__alias__("__divhi3"))) int16_t __mspabi_divi(int16_t a, int16_t b);

__attribute__((__alias__("__udivhi3"))) uint16_t __mspabi_divu(uint16_t a, uint16_t b);

__attribute__((__alias__("__modhi3"))) int16_t __mspabi_remi(int16_t a, int16_t b);

__attribute__((__alias__("__umodhi3"))) uint16_t __mspabi_remu(uint16_t a, uint16_t b);

__attribute__((__alias__("__divsi3"))) int32_t __mspabi_divli(int32_t a, int32_t b);

__attribute__((__alias__("__udivsi3"))) uint32_t __mspabi_divul(uint32_t a, uint32_t b);

__attribute__((__alias__("__modsi3"))) int32_t __mspabi_remli(int32_t a, int32_t b);

__attribute__((__alias__("__umodsi3"))) uint32_t __mspabi_remul(uint32_t a, uint32_t b);

__attribute__((__alias__("__mulhi3"))) int16_t __mspabi_mpyi(int16_t a, int16_t b);

__attribute__((__alias__("__mulsi3"))) int32_t __mspabi_mpyl(int32_t a, int32_t b);

#endif // defined(__clang__)

#if LGRT_SOFT_FLOAT

// GCC does the same for most of the floating-point routines, which this block
// covers for Clang. The others follow it, for both. The run-time ABI leaves
// the result of a comparison undefined for unordered operands, which Clang
// passes all the same: the first operand counts as greater, as in __ltsf2.
#if defined(__clang__)

MSP430_FROM_64("__mspabi_addd", "__adddf3")
MSP430_FROM_64("__mspabi_subd", "__subdf3")
MSP430_FROM_64("__mspabi_mpyd", "__muldf3")
MSP430_FROM_64("__mspabi_divd", "__divdf3")

FP_ALIAS(uint32_t, __mspabi_addf, "__addsf3", (uint32_t a, uint32_t b))
FP_ALIAS(uint32_t, __mspabi_subf, "__subsf3", (uint32_t a, uint32_t b))
FP_ALIAS(uint32_t, __mspabi_mpyf, "__mulsf3", (uint32_t a, uint32_t b))
FP_ALIAS(uint32_t, __mspabi_divf, "__divsf3", (uint32_t a, uint32_t b))
FP_ALIAS(uint32_t, __mspabi_cvtdf, "__truncdfsf2", (uint64_t a))
FP_ALIAS(uint64_t, __mspabi_cvtfd, "__extendsfdf2", (uint32_t a))
FP_ALIAS(int32_t, __mspabi_fixdli, "__fixdfsi", (uint64_t a))
FP_ALIAS(int64_t, __mspabi_fixdlli, "__fixdfdi", (uint64_t a))
FP_ALIAS(uint32_t, __mspabi_fixdul, "__fixunsdfsi", (uint64_t a))
FP_ALIAS(uint64_t, __mspabi_fixdull, "__fixunsdfdi", (uint64_t a))
FP_ALIAS(int32_t, __mspabi_fixfli, "__fixsfsi", (uint32_t a))
FP_ALIAS(int64_t, __mspabi_fixflli, "__fixsfdi", (uint32_t a))
FP_ALIAS(uint64_t, __mspabi_fltlid, "__floatsidf", (int32_t a))
FP_ALIAS(uint64_t, __mspabi_fltllid, "__floatdidf", (int64_t a))
FP_ALIAS(uint64_t, __mspabi_fltuld, "__floatunsidf", (uint32_t a))
FP_ALIAS(uint64_t, __mspabi_fltulld, "__floatundidf", (uint64_t a))
FP_ALIAS(uint32_t, __mspabi_fltlif, "__floatsisf", (int32_t a))
FP_ALIAS(uint32_t, __mspabi_fltllif, "__floatdisf", (int64_t a))
FP_ALIAS(uint32_t, __mspabi_fltulf, "__floatunsisf", (uint32_t a))
FP_ALIAS(uint32_t, __mspabi_fltullf, "__floatundisf", (uint64_t a))

#endif // defined(__clang__)

MSP430_FROM_64("__mspabi_cmpd", "__ltdf2")

FP_ALIAS(int, __mspabi_cmpf, "__ltsf2", (uint32_t a, uint32_t b))
FP_ALIAS(uint32_t, __mspabi_negf, "__negsf2", (uint32_t a))
FP_ALIAS(uint64_t, __mspabi_negd, "__negdf2", (uint64_t a))
FP_ALIAS(uint32_t, __mspabi_fixful, "__fixunssfsi", (uint32_t a))
FP_ALIAS(uint64_t, __mspabi_fixfull, "__fixunssfdi", (uint32_t a))

// From and to integers of 16 bits, out of range the same as those of 32.

static inline int16_t msp430_nearest_i16(int32_t a) {
    if (a > INT16_MAX) {
        return INT16_MAX;
    }
    return a < INT16_MIN ? INT16_MIN : (int16_t)a;
}

static inline uint16_t msp430_nearest_u16(uint32_t a) {
    return a > UINT16_MAX ? UINT16_MAX : (uint16_t)a;
}

int16_t __mspabi_fixfi(uint32_t a) {
    return msp430_nearest_i16(__fixsfsi(a));
}

uint16_t __mspabi_fixfu(uint32_t a) {
    return msp430_nearest_u16(__fixunssfsi(a));
}

int16_t __mspabi_fixdi(uint64_t a) {
    return msp430_nearest_i16(__fixdfsi(a));
}

uint16_t __mspabi_fixdu(uint64_t a) {
    return msp430_nearest_u16(__fixunsdfsi(a));
}

uint32_t __mspabi_fltif(int16_t a) {
    return __floatsisf(a);
}

uint32_t __mspabi_fltuf(uint16_t a) {
    return __floatunsisf(a);
}

uint64_t __mspabi_fltid(int16_t a) {
    return __floatsidf(a);
}

uint64_t __mspabi_fltud(uint16_t a) {
    return __floatunsidf(a);
}

#endif // LGRT_SOFT_FLOAT

int32_t __mspabi_mpysl(int16_t a, int16_t b) {
    return (int32_t)shift_add_mul32((uint32_t)(int32_t)a, (uint32_t)(int32_t)b);
}

uint32_t __mspabi_mpyul(uint16_t a, uint16_t b) {
    return shift_add_mul32(a, b);
}

uint64_t __mspabi_mpyull(uint32_t a, uint32_t b) {
    return wide_mul32(a, b);
}

// A negative operand read as unsigned adds the other above the product.
int64_t __mspabi_mpysll(int32_t a, int32_t b) {
    uint32_t x = (uint32_t)a;
    uint32_t y = (uint32_t)b;
    uint64_t p = wide_mul32(x, y);
    uint32_t over = (y & ((uint32_t)0 - (x >> 31))) + (x & ((uint32_t)0 - (y >> 31)));

    return (int64_t)(p - ((uint64_t)over << 32));
}

// The shifts of up to 32 bits, by a count and by constants. Those by one bit
// compile into instructions, and the value is hidden between them for no
// compiler to merge them into a shift by a variable amount, a call to these.
//
// Workaround: GCC 4.9 and 5, MSP430, without optimising: an unsigned shift of
// 16 bits by one is a call to one of these, and a signed one an instruction,
// which the value is hidden after for no compiler to take it for the former.
#define MSP430_SHIFT_BY(T, name, n) \
    T name##_##n(T a) { \
        return name(a, n); \
    }

#define MSP430_SHIFTS(T, name, step) \
    __attribute__((__noinline__)) T name(T a, unsigned int n) { \
        for (; n != 0; n--) { \
            step; \
            HIDE_BIT(a); \
        } \
        return a; \
    } \
    \
    MSP430_SHIFT_BY(T, name, 1) \
    MSP430_SHIFT_BY(T, name, 2) \
    MSP430_SHIFT_BY(T, name, 3) \
    MSP430_SHIFT_BY(T, name, 4) \
    MSP430_SHIFT_BY(T, name, 5) \
    MSP430_SHIFT_BY(T, name, 6) \
    MSP430_SHIFT_BY(T, name, 7) \
    MSP430_SHIFT_BY(T, name, 8) \
    MSP430_SHIFT_BY(T, name, 9) \
    MSP430_SHIFT_BY(T, name, 10) \
    MSP430_SHIFT_BY(T, name, 11) \
    MSP430_SHIFT_BY(T, name, 12) \
    MSP430_SHIFT_BY(T, name, 13) \
    MSP430_SHIFT_BY(T, name, 14) \
    MSP430_SHIFT_BY(T, name, 15)

MSP430_SHIFTS(uint16_t, __mspabi_slli, a <<= 1)
MSP430_SHIFTS(int16_t, __mspabi_srai, a >>= 1)
MSP430_SHIFTS(
    uint16_t, __mspabi_srli,
    int16_t halved = (int16_t)a >> 1;
    HIDE_BIT(halved);
    a = (uint16_t)halved & INT16_MAX
)
MSP430_SHIFTS(uint32_t, __mspabi_slll, a <<= 1)
MSP430_SHIFTS(int32_t, __mspabi_sral, a >>= 1)
MSP430_SHIFTS(uint32_t, __mspabi_srll, a >>= 1)

// Workaround: Clang before 8, MSP430: it calls these for shifts of 32 bits.
#if defined(__clang__) && __clang_major__ < 8
__attribute__((__alias__("__mspabi_slll"))) uint32_t __ashlsi3(uint32_t a, unsigned int n);

__attribute__((__alias__("__mspabi_sral"))) int32_t __ashrsi3(int32_t a, unsigned int n);

__attribute__((__alias__("__mspabi_srll"))) uint32_t __lshrsi3(uint32_t a, unsigned int n);
#endif

#if defined(__SIZEOF_INT20__)

__extension__ typedef __int20 i20;
__extension__ typedef unsigned __int20 u20;

// GCC calls these for shifts of __int20 by variable amounts. Those by one bit
// compile into instructions, and the value is hidden between them for no
// compiler to merge them into a shift by a variable amount, a call to these.

u20 __gnu_mspabi_sllp(u20 a, unsigned int n) {
    for (; n != 0; n--) {
        a <<= 1;
        HIDE_BIT(a);
    }
    return a;
}

u20 __gnu_mspabi_srlp(u20 a, unsigned int n) {
    for (; n != 0; n--) {
        a >>= 1;
        HIDE_BIT(a);
    }
    return a;
}

i20 __gnu_mspabi_srap(i20 a, unsigned int n) {
    for (; n != 0; n--) {
        a >>= 1;
        HIDE_BIT(a);
    }
    return a;
}

#endif // defined(__SIZEOF_INT20__)

// Calls a shift in C, which takes the operand where its result goes, and the
// count on the stack.
#define MSP430_SHIFT_64(name, f) \
    __asm__ ( \
        MSP430_BEGIN(name) \
        "push r12\n\t" \
        "mov r8, r12\n\t" \
        "mov r9, r13\n\t" \
        "mov r10, r14\n\t" \
        "mov r11, r15\n\t" \
        MSP430_CALL " #" f "\n\t" \
        MSP430_ADDA " #2, r1\n\t" \
        MSP430_RET \
        MSP430_END(name) \
    );

MSP430_SHIFT_64("__mspabi_sllll", "__ashldi3")
MSP430_SHIFT_64("__mspabi_srall", "__ashrdi3")
MSP430_SHIFT_64("__mspabi_srlll", "__lshrdi3")

// Epilogues optimised for size jump into this, past the pops of the registers
// they did not save.
__asm__ (
    ".pushsection .text.__mspabi_func_epilog_7,\"ax\",@progbits\n\t"
    ".p2align 1\n\t"
    MSP430_SIZED("__mspabi_func_epilog_7", ".Lmsp430_epilogue_end")
    "pop r4\n\t"
    MSP430_SIZED("__mspabi_func_epilog_6", ".Lmsp430_epilogue_end")
    "pop r5\n\t"
    MSP430_SIZED("__mspabi_func_epilog_5", ".Lmsp430_epilogue_end")
    "pop r6\n\t"
    MSP430_SIZED("__mspabi_func_epilog_4", ".Lmsp430_epilogue_end")
    "pop r7\n\t"
    MSP430_SIZED("__mspabi_func_epilog_3", ".Lmsp430_epilogue_end")
    "pop r8\n\t"
    MSP430_SIZED("__mspabi_func_epilog_2", ".Lmsp430_epilogue_end")
    "pop r9\n\t"
    MSP430_SIZED("__mspabi_func_epilog_1", ".Lmsp430_epilogue_end")
    "pop r10\n\t"
    MSP430_RET
    ".Lmsp430_epilogue_end:\n\t"
    ".popsection"
);

// The assembler references these where an object has data to initialise, data
// to zero, or arrays of functions to run. Linker scripts for MSP430 put the
// sections .crt_* in the order of their names, so that the startup code falls
// through the first of these, each a call to the function that does the work.
// The symbols are weak for scripts that lack them.

#define MSP430_CRT_STEP(section, name, helper) \
    __asm__ ( \
        ".pushsection " section ",\"ax\",@progbits\n\t" \
        ".globl " name "\n\t" \
        ".hidden " name "\n\t" \
        name ":\n\t" \
        MSP430_CALL " #" helper "\n\t" \
        ".popsection" \
    );

#define MSP430_CRT_HELPER \
    NO_STACK_PROTECTOR \
    ASM_CALLED __attribute__((__noinline__))

extern char __bssstart[] __attribute__((__weak__));
extern char __bsssize[] __attribute__((__weak__));

MSP430_CRT_HELPER void msp430_init_bss(void) {
    size_t n = (size_t)__bsssize;

    if (n != 0) {
        __builtin_memset(__bssstart, 0, n);
    }
}

MSP430_CRT_STEP(".crt_0100init_bss", "__crt0_init_bss", "msp430_init_bss")

extern char __datastart[] __attribute__((__weak__));
extern const char __romdatastart[] __attribute__((__weak__));
extern char __romdatacopysize[] __attribute__((__weak__));

MSP430_CRT_HELPER void msp430_movedata(void) {
    size_t n = (size_t)__romdatacopysize;

    if (n != 0 && (uintptr_t)__datastart != (uintptr_t)__romdatastart) {
        __builtin_memcpy(__datastart, __romdatastart, n);
    }
}

MSP430_CRT_STEP(".crt_0300movedata", "__crt0_movedata", "msp430_movedata")

typedef void (*msp430_array_entry)(void);

#define MSP430_RUN_ARRAY(section, name, helper, start, end) \
    extern msp430_array_entry start[] __attribute__((__weak__)); \
    extern msp430_array_entry end[] __attribute__((__weak__)); \
    \
    MSP430_CRT_HELPER void helper(void) { \
        for (msp430_array_entry *f = (start); f != (end); f++) { \
            (*f)(); \
        } \
    } \
    \
    MSP430_CRT_STEP(section, name, #helper)

MSP430_RUN_ARRAY(
    ".crt_0500run_preinit_array", "__crt0_run_preinit_array", msp430_run_preinit,
    __preinit_array_start, __preinit_array_end
)

MSP430_RUN_ARRAY(
    ".crt_0600run_init_array", "__crt0_run_init_array", msp430_run_init, __init_array_start,
    __init_array_end
)

// The exit calls this one, which runs the array backwards.
extern msp430_array_entry __fini_array_start[] __attribute__((__weak__));
extern msp430_array_entry __fini_array_end[] __attribute__((__weak__));

__attribute__((__section__(".crt_1000run_fini_array"))) void __crt0_run_fini_array(void) {
    for (msp430_array_entry *f = __fini_array_end; f != __fini_array_start; ) {
        f--;
        (*f)();
    }
}

// All that is asked of this one is to exist.
__attribute__((__section__(".crt_1100run_array"))) void __crt0_run_array(void) {}

#endif // defined(__MSP430__)

#if defined(__AVR__)

// The compilers know which registers each of these changes, and keep values in
// the others across the calls, so these change only their results, the flags,
// and the temporary register. Most are C, called with the registers that it
// may change saved. Those of a few instructions, and those that read flash,
// would spend several times as long saving registers, and are assembly.
// Comments give the conventions that differ from C's. The reduced cores have
// only r16 to r31, with r16 as the temporary register and r17 as the zero
// register, and pass 8-byte values in memory, so their 8-byte routines are in
// C with the convention of C.

#if defined(__AVR_TINY__)
#   define AVR_TMP "r16"
#   define AVR_ZERO "r17"
#else
#   define AVR_TMP "r0"
#   define AVR_ZERO "r1"
#endif

// Workaround: Clang before 16, AVR: it defines no macro for what the core has,
// so these calls reach anywhere on any core, and those that depend on the
// other macros below take the forms that every core has.
#if defined(__AVR_HAVE_JMP_CALL__)
#   define AVR_CALL(f) "call " f "\n\t"
#   define AVR_JUMP(f) "jmp " f "\n\t"
#elif defined(__clang__) && __clang_major__ < 16
#   define AVR_CALL(f) \
        "push r30\n\t" \
        "push r31\n\t" \
        "ldi r30, lo8(gs(" f "))\n\t" \
        "ldi r31, hi8(gs(" f "))\n\t" \
        "icall\n\t" \
        "pop r31\n\t" \
        "pop r30\n\t"
#   define AVR_JUMP(f) \
        AVR_CALL(f) \
        "ret\n\t"
#else
#   define AVR_CALL(f) "rcall " f "\n\t"
#   define AVR_JUMP(f) "rjmp " f "\n\t"
#endif

#define AVR_RAMPZ "0x3b"
#define AVR_SPL "0x3d"
#define AVR_SPH "0x3e"

// With more than 64 KiB of data memory, Z reads it through RAMPZ too.
#if defined(__AVR_ARCH__) && (__AVR_ARCH__ == 105 || __AVR_ARCH__ == 107)
#   define AVR_CLEAR_RAMPZ "out " AVR_RAMPZ ", " AVR_ZERO "\n\t"
#else
#   define AVR_CLEAR_RAMPZ ""
#endif

// Reads the next byte of flash, from Z, or from RAMPZ:Z where flash exceeds 64
// KiB, which only the post-increment forms step by themselves. Reduced cores
// read flash through data memory.
#if defined(__AVR_TINY__)
#   define AVR_READ(r) "ld " r ", Z+\n\t"
#elif defined(__AVR_HAVE_ELPMX__)
#   define AVR_READ(r) "elpm " r ", Z+\n\t"
#elif defined(__AVR_HAVE_ELPM__)
#   define AVR_STEP_RAMPZ_Z \
        "adiw r30, 1\n\t" \
        "brcc 9f\n\t" \
        "in r0, " AVR_RAMPZ "\n\t" \
        "inc r0\n\t" \
        "out " AVR_RAMPZ ", r0\n\t" \
        "9:\n\t"
#   define AVR_READ(r) \
        "elpm\n\t" \
        "mov " r ", r0\n\t" \
        AVR_STEP_RAMPZ_Z
#elif defined(__AVR_HAVE_LPMX__)
#   define AVR_READ(r) "lpm " r ", Z+\n\t"
#else // defined(__AVR_TINY__)
#   define AVR_READ(r) \
        "lpm\n\t" \
        "mov " r ", r0\n\t" \
        "adiw r30, 1\n\t"
#endif // defined(__AVR_TINY__)

// Copies the next byte of flash to X. Stepping RAMPZ:Z takes r0 where only the
// plain elpm exists, so there the byte goes out first.
#if defined(__AVR_HAVE_ELPM__) && !defined(__AVR_HAVE_ELPMX__)
#   define AVR_COPY_FLASH_BYTE \
        "elpm\n\t" \
        "st X+, r0\n\t" \
        AVR_STEP_RAMPZ_Z
#else
#   define AVR_COPY_FLASH_BYTE \
        AVR_READ(AVR_TMP) \
        "st X+, " AVR_TMP "\n\t"
#endif

#if defined(__AVR_HAVE_ELPM__)
#   define AVR_SET_RAMPZ(r) "out " AVR_RAMPZ ", " r "\n\t"
#else
#   define AVR_SET_RAMPZ(r)
#endif

#define AVR_ENTRY(name, end) \
    ".globl " name "\n\t" \
    ".hidden " name "\n\t" \
    ".type " name ", @function\n\t" \
    name ":\n\t" \
    ".size " name ", " end " - " name "\n\t"

#define AVR_BEGIN(name) \
    ".pushsection .text." name ",\"ax\",@progbits\n\t" \
    ".globl " name "\n\t" \
    ".hidden " name "\n\t" \
    ".type " name ", @function\n\t" \
    name ":\n\t"

#define AVR_END(name) \
    ".size " name ", . - " name "\n\t" \
    ".popsection"

#define AVR_NEG4(r3, r2, r1, r0) \
    "com " r3 "\n\t" \
    "com " r2 "\n\t" \
    "com " r1 "\n\t" \
    "neg " r0 "\n\t" \
    "sbci " r1 ", -1\n\t" \
    "sbci " r2 ", -1\n\t" \
    "sbci " r3 ", -1\n\t"

// What the routines in C save, for what C may change and they may not.
#define AVR_HELPER ASM_CALLED

#define AVR_PUSH_X_Z \
    "push r26\n\t" \
    "push r27\n\t" \
    "push r30\n\t" \
    "push r31\n\t"

#define AVR_POP_X_Z \
    "pop r31\n\t" \
    "pop r30\n\t" \
    "pop r27\n\t" \
    "pop r26\n\t"

#define AVR_PUSH_18_TO_21 \
    AVR_PUSH_X_Z \
    "push r18\n\t" \
    "push r19\n\t" \
    "push r20\n\t" \
    "push r21\n\t"

#define AVR_POP_18_TO_21 \
    "pop r21\n\t" \
    "pop r20\n\t" \
    "pop r19\n\t" \
    "pop r18\n\t" \
    AVR_POP_X_Z

#define AVR_PUSH_18_TO_23 \
    AVR_PUSH_18_TO_21 \
    "push r22\n\t" \
    "push r23\n\t"

#define AVR_POP_18_TO_23 \
    "pop r23\n\t" \
    "pop r22\n\t" \
    AVR_POP_18_TO_21

// A routine that calls C, whose registers the convention matches.
#define AVR_STUB(name, helper, push, pop) \
    __asm__ ( \
        AVR_BEGIN(name) \
        push \
        AVR_CALL(helper) \
        pop \
        "ret\n\t" \
        AVR_END(name) \
    );

union avr_words {
    uint32_t whole;
    uint16_t words[2];
    uint8_t bytes[4];
};

// Flash takes its own instructions to read, and reduced cores map it.
static inline uint8_t avr_read_flash(uint32_t address) {
    union avr_words x = { .whole = address };
    uint8_t byte;

#if defined(__AVR_TINY__)
    byte = *(const volatile uint8_t *)(x.words[0] + 0x4000);
#elif defined(__AVR_HAVE_ELPMX__)
    __asm__ volatile (
        "out " AVR_RAMPZ ", %1\n\t"
        "elpm %0, Z\n\t"
        AVR_CLEAR_RAMPZ
        : "=r"(byte)
        : "r"(x.bytes[2]), "z"(x.words[0])
    );
#elif defined(__AVR_HAVE_ELPM__)
    __asm__ volatile (
        "out " AVR_RAMPZ ", %1\n\t"
        "elpm\n\t"
        "mov %0, r0\n\t"
        AVR_CLEAR_RAMPZ
        : "=r"(byte)
        : "r"(x.bytes[2]), "z"(x.words[0])
    );
#elif defined(__AVR_HAVE_LPMX__)
    __asm__ volatile ("lpm %0, Z" : "=r"(byte) : "z"(x.words[0]));
#else // defined(__AVR_TINY__)
    __asm__ volatile (
        "lpm\n\t"
        "mov %0, r0"
        : "=r"(byte)
        : "z"(x.words[0])
    );
#endif // defined(__AVR_TINY__)
    return byte;
}

// The compilers reference these where a program has initialised or zeroed
// data, constructors, or destructors. The startup code falls through the
// sections .init0 to .init9, and the exit through .fini9 to .fini0, so each is
// only a call to the function that does the work, which runs with the data not
// yet there, so without a guard of the stack, which is there. The symbols are
// weak for linker scripts that lack them.

#define AVR_STARTUP AVR_HELPER NO_STACK_PROTECTOR

#define AVR_STEP(section, name, helper) \
    ".pushsection " section ",\"ax\",@progbits\n\t" \
    ".globl " name "\n\t" \
    ".hidden " name "\n\t" \
    name ":\n\t" \
    AVR_CALL(helper) \
    ".popsection\n\t"

// The high byte of a symbol in flash, which C has no way of saying.
#if defined(__AVR_HAVE_ELPM__)
#   define AVR_FLASH_HIGH(high, symbol) __asm__ ("ldi %0, hh8(" symbol ")" : "=d"(high))
#else
#   define AVR_FLASH_HIGH(high, symbol) ((high) = 0)
#endif

extern char __data_start[] __attribute__((__weak__));
extern char __data_end[] __attribute__((__weak__));
extern const char __data_load_start[] __attribute__((__weak__));
extern char __bss_start[] __attribute__((__weak__));
extern char __bss_end[] __attribute__((__weak__));

AVR_STARTUP void avr_copy_data(void) {
    union avr_words from;

    // Not by an initialiser, which can come from the data not yet there.
    from.words[0] = (uint16_t)(uintptr_t)__data_load_start;
    from.words[1] = 0;
    AVR_FLASH_HIGH(from.bytes[2], "__data_load_start");
    for (char *to = __data_start; to != __data_end; to++) {
        *to = (char)avr_read_flash(from.whole);
        from.whole++;
    }
}

AVR_STARTUP void avr_clear_bss(void) {
    size_t n = (size_t)((uintptr_t)__bss_end - (uintptr_t)__bss_start);

    if (n != 0) {
        __builtin_memset(__bss_start, 0, n);
    }
}

__asm__ (
    AVR_STEP(".init4", "__do_copy_data", "avr_copy_data")
    AVR_STEP(".init4", "__do_clear_bss", "avr_clear_bss")
);

// Constructors run from the last to the first, and destructors in order.

extern const char __ctors_start[] __attribute__((__weak__));
extern const char __ctors_end[] __attribute__((__weak__));
extern const char __dtors_start[] __attribute__((__weak__));
extern const char __dtors_end[] __attribute__((__weak__));

static inline void avr_call_from_flash(uint32_t address) {
    union avr_words entry;

    entry.bytes[0] = avr_read_flash(address);
    entry.bytes[1] = avr_read_flash(address + 1);
    ((void (*)(void))(uintptr_t)entry.words[0])();
}

AVR_HELPER void avr_global_ctors(void) {
    union avr_words entry = {
        .words = { (uint16_t)(uintptr_t)__ctors_end, 0 }
    };
    uint16_t n = (uint16_t)((uintptr_t)__ctors_end - (uintptr_t)__ctors_start);

    AVR_FLASH_HIGH(entry.bytes[2], "__ctors_end");
    for (; n != 0; n = (uint16_t)(n - 2)) {
        entry.whole -= 2;
        avr_call_from_flash(entry.whole);
    }
}

__asm__ (
    AVR_STEP(".init6", "__do_global_ctors", "avr_global_ctors")
);

AVR_HELPER void avr_global_dtors(void) {
    union avr_words entry = {
        .words = { (uint16_t)(uintptr_t)__dtors_start, 0 }
    };
    uint16_t n = (uint16_t)((uintptr_t)__dtors_end - (uintptr_t)__dtors_start);

    AVR_FLASH_HIGH(entry.bytes[2], "__dtors_start");
    for (; n != 0; n = (uint16_t)(n - 2)) {
        avr_call_from_flash(entry.whole);
        entry.whole += 2;
    }
}

__asm__ (
    AVR_STEP(".fini6", "__do_global_dtors", "avr_global_dtors")
);

__asm__ (
    AVR_BEGIN("__negsi2")
    AVR_NEG4("r25", "r24", "r23", "r22")
    "ret\n\t"
    AVR_END("__negsi2")
);

__asm__ (
    AVR_BEGIN("__bswapsi2")
    "mov " AVR_TMP ", r22\n\t"
    "mov r22, r25\n\t"
    "mov r25, " AVR_TMP "\n\t"
    "mov " AVR_TMP ", r23\n\t"
    "mov r23, r24\n\t"
    "mov r24, " AVR_TMP "\n\t"
    "ret\n\t"
    AVR_END("__bswapsi2")
);

static inline uint8_t avr_clz16(uint16_t a) {
    uint8_t n = 0;

    while (n < 16 && (int16_t)a >= 0) {
        a <<= 1;
        n++;
    }
    return n;
}

static inline uint8_t avr_ctz16(uint16_t a) {
    uint8_t n = 0;

    while (n < 16 && (a & 1) == 0) {
        a >>= 1;
        n++;
    }
    return n;
}

static inline uint8_t avr_clz32(uint32_t a) {
    union avr_words x = { .whole = a };

    return x.words[1] != 0
         ? avr_clz16(x.words[1])
         : (uint8_t)((unsigned int)16 + avr_clz16(x.words[0]));
}

static inline uint8_t avr_ctz32(uint32_t a) {
    union avr_words x = { .whole = a };

    return x.words[0] != 0
         ? avr_ctz16(x.words[0])
         : (uint8_t)((unsigned int)16 + avr_ctz16(x.words[1]));
}

static inline uint8_t avr_ones8(uint8_t a) {
    uint8_t n = 0;

    while (a != 0) {
        n = (uint8_t)((unsigned int)n + (a & 1));
        a >>= 1;
    }
    return n;
}

static inline uint8_t avr_ones32(uint32_t a) {
    union avr_words x = { .whole = a };

    return (uint8_t)((unsigned int)avr_ones8(x.bytes[0]) + avr_ones8(x.bytes[1])
                   + avr_ones8(x.bytes[2]) + avr_ones8(x.bytes[3]));
}

// Each takes r25:r24 or r25:r22, and returns in r25:r24.
#define AVR_COUNT(name, T, value) \
    AVR_HELPER int avr##name(T a) { \
        return (int)(value); \
    } \
    \
    AVR_STUB(#name, "avr" #name, AVR_PUSH_18_TO_23, AVR_POP_18_TO_23)

AVR_COUNT(__clzhi2, uint16_t, avr_clz16(a))
AVR_COUNT(__clzsi2, uint32_t, avr_clz32(a))
AVR_COUNT(__ctzhi2, uint16_t, avr_ctz16(a))
AVR_COUNT(__ctzsi2, uint32_t, avr_ctz32(a))
AVR_COUNT(__ffshi2, uint16_t, a == 0 ? 0 : (unsigned int)avr_ctz16(a) + 1)
AVR_COUNT(__ffssi2, uint32_t, a == 0 ? 0 : (unsigned int)avr_ctz32(a) + 1)
AVR_COUNT(__popcounthi2, uint16_t, avr_ones32(a))
AVR_COUNT(__popcountsi2, uint32_t, avr_ones32(a))
AVR_COUNT(__parityqi2, uint8_t, avr_ones8(a) & 1)
AVR_COUNT(__parityhi2, uint16_t, avr_ones32(a) & 1)
AVR_COUNT(__paritysi2, uint32_t, avr_ones32(a) & 1)

// The compilers extend its result themselves, from r24.
AVR_HELPER uint8_t avr__popcountqi2(uint8_t a) {
    return avr_ones8(a);
}

AVR_STUB(
    "__popcountqi2", "avr__popcountqi2",
    "push r25\n\t"
    AVR_PUSH_18_TO_23,
    AVR_POP_18_TO_23
    "pop r25\n\t"
)

// The divisions shift the dividend into a remainder of its width, and the bits
// of the quotient into the dividend. A remainder with its top bit set before
// the shift has one more bit than it holds, and exceeds the divisor. These
// take the dividend in the top width bits of a, and give the quotient, with
// the remainder in *rem.
#define AVR_UDIVMOD(T, S, name) \
    static inline T name(T a, T b, uint8_t width, T *rem) { \
        T r = 0; \
        \
        for (uint8_t i = width; i != 0; i--) { \
            bool top = (S)r < 0; \
            \
            r = (T)((T)(r << 1) | (T)((S)a < 0)); \
            a = (T)(a << 1); \
            if (top || r >= b) { \
                r = (T)(r - b); \
                a |= 1; \
            } \
        } \
        *rem = r; \
        return a; \
    }

AVR_UDIVMOD(uint8_t, int8_t, avr_udivmod8)
AVR_UDIVMOD(uint16_t, int16_t, avr_udivmod16)
AVR_UDIVMOD(uint32_t, int32_t, avr_udivmod32)

// The signed ones negate what they give according to these, on magnitudes.
#define AVR_MAGNITUDE(T, x) ((x) < 0 ? (T)((T)0 - (T)(x)) : (T)(x))

union avr_divmod8 {
    uint16_t whole;
    uint8_t parts[2];
};

// r24 / r22, returning the quotient in r24 and the remainder in r25.
static inline uint16_t avr_divide8(uint8_t a, uint8_t b) {
    union avr_divmod8 x;
    uint8_t r;

    x.parts[0] = avr_udivmod8(a, b, 8, &r);
    x.parts[1] = r;
    return x.whole;
}

AVR_HELPER uint16_t avr__udivmodqi4(uint8_t a, uint8_t b) {
    return avr_divide8(a, b);
}

AVR_HELPER uint16_t avr__divmodqi4(int8_t a, int8_t b) {
    union avr_divmod8 x;

    x.whole = avr_divide8(AVR_MAGNITUDE(uint8_t, a), AVR_MAGNITUDE(uint8_t, b));
    if ((a ^ b) < 0) {
        x.parts[0] = (uint8_t)((uint8_t)0 - x.parts[0]);
    }
    if (a < 0) {
        x.parts[1] = (uint8_t)((uint8_t)0 - x.parts[1]);
    }
    return x.whole;
}

AVR_STUB("__udivmodqi4", "avr__udivmodqi4", AVR_PUSH_18_TO_23, AVR_POP_18_TO_23)

AVR_STUB("__divmodqi4", "avr__divmodqi4", AVR_PUSH_18_TO_23, AVR_POP_18_TO_23)

// r25:r24 / r23:r22, returning the quotient in r23:r22 and the remainder in
// r25:r24.
static inline uint32_t avr_divide16(uint16_t a, uint16_t b) {
    union avr_words x;
    uint16_t r;

    x.words[0] = avr_udivmod16(a, b, 16, &r);
    x.words[1] = r;
    return x.whole;
}

AVR_HELPER uint32_t avr__udivmodhi4(uint16_t a, uint16_t b) {
    return avr_divide16(a, b);
}

AVR_HELPER uint32_t avr__divmodhi4(int16_t a, int16_t b) {
    union avr_words x;

    x.whole = avr_divide16(AVR_MAGNITUDE(uint16_t, a), AVR_MAGNITUDE(uint16_t, b));
    if ((a ^ b) < 0) {
        x.words[0] = (uint16_t)((uint16_t)0 - x.words[0]);
    }
    if (a < 0) {
        x.words[1] = (uint16_t)((uint16_t)0 - x.words[1]);
    }
    return x.whole;
}

AVR_STUB("__udivmodhi4", "avr__udivmodhi4", AVR_PUSH_18_TO_21, AVR_POP_18_TO_21)

AVR_STUB("__divmodhi4", "avr__divmodhi4", AVR_PUSH_18_TO_21, AVR_POP_18_TO_21)

// r25:r22 / r21:r18, returning the quotient in r21:r18 and the remainder in
// r25:r22, and likewise in 3 bytes of each, the fourth kept. The reduced cores
// would pass them to C partly on the stack, and take 8 bytes back in memory,
// so C gets them in memory, in the order of these registers, from the stack.
struct avr_operands {
    uint32_t second;
    uint32_t first;
};

#if defined(__AVR_HAVE_8BIT_SP__) || defined(__AVR_SP8__)
#   define AVR_OPERANDS_HIGH "clr r25\n\t"
#else
#   define AVR_OPERANDS_HIGH "in r25, " AVR_SPH "\n\t"
#endif

#define AVR_ON_OPERANDS(name) \
    __asm__ ( \
        AVR_BEGIN(#name) \
        AVR_PUSH_X_Z \
        "push r25\n\t" \
        "push r24\n\t" \
        "push r23\n\t" \
        "push r22\n\t" \
        "push r21\n\t" \
        "push r20\n\t" \
        "push r19\n\t" \
        "push r18\n\t" \
        "in r24, " AVR_SPL "\n\t" \
        AVR_OPERANDS_HIGH \
        "subi r24, -1\n\t" \
        "sbci r25, -1\n\t" \
        AVR_CALL("avr" #name) \
        "pop r18\n\t" \
        "pop r19\n\t" \
        "pop r20\n\t" \
        "pop r21\n\t" \
        "pop r22\n\t" \
        "pop r23\n\t" \
        "pop r24\n\t" \
        "pop r25\n\t" \
        AVR_POP_X_Z \
        "ret\n\t" \
        AVR_END(#name) \
    );

AVR_HELPER void avr__udivmodsi4(struct avr_operands *v) {
    v->second = avr_udivmod32(v->first, v->second, 32, &v->first);
}

AVR_HELPER void avr__divmodsi4(struct avr_operands *v) {
    int32_t a = (int32_t)v->first;
    int32_t b = (int32_t)v->second;
    uint32_t q = avr_udivmod32(
        AVR_MAGNITUDE(uint32_t, a), AVR_MAGNITUDE(uint32_t, b), 32, &v->first
    );

    v->second = (a ^ b) < 0 ? (uint32_t)0 - q : q;
    if (a < 0) {
        v->first = (uint32_t)0 - v->first;
    }
}

AVR_ON_OPERANDS(__udivmodsi4)
AVR_ON_OPERANDS(__divmodsi4)

// r24 * r22, returning in r24.
#if defined(__AVR_HAVE_MUL__)
__asm__ (
    AVR_BEGIN("__mulqi3")
    "mul r24, r22\n\t"
    "mov r24, r0\n\t"
    "clr r1\n\t"
    "ret\n\t"
    AVR_END("__mulqi3")
);
#else // defined(__AVR_HAVE_MUL__)
AVR_HELPER uint8_t avr__mulqi3(uint8_t a, uint8_t b) {
    uint8_t r = 0;

    while (b != 0) {
        uint8_t bit = b & 1;

        HIDE_BIT(bit);
        r = (uint8_t)((unsigned int)r + (a & (uint8_t)((unsigned int)0 - bit)));
        a = (uint8_t)(a << 1);
        b >>= 1;
    }
    return r;
}

AVR_STUB(
    "__mulqi3", "avr__mulqi3",
    "push r25\n\t"
    AVR_PUSH_18_TO_23,
    AVR_POP_18_TO_23
    "pop r25\n\t"
)
#endif // defined(__AVR_HAVE_MUL__)

// r25:r24 * r23:r22, returning in r25:r24.
#if defined(__AVR_HAVE_MUL__)
__asm__ (
    AVR_BEGIN("__mulhi3")
    "mul r25, r22\n\t"
    "mov r25, r0\n\t"
    "mul r24, r23\n\t"
    "add r25, r0\n\t"
    "mul r24, r22\n\t"
    "mov r24, r0\n\t"
    "add r25, r1\n\t"
    "clr r1\n\t"
    "ret\n\t"
    AVR_END("__mulhi3")
);
#else // defined(__AVR_HAVE_MUL__)
AVR_HELPER uint16_t avr__mulhi3(uint16_t a, uint16_t b) {
    uint16_t r = 0;

    while (b != 0) {
        uint16_t bit = b & 1;

        HIDE_BIT(bit);
        r = (uint16_t)(r + (a & (uint16_t)((uint16_t)0 - bit)));
        a = (uint16_t)(a << 1);
        b >>= 1;
    }
    return r;
}

AVR_STUB("__mulhi3", "avr__mulhi3", AVR_PUSH_18_TO_23, AVR_POP_18_TO_23)
#endif // defined(__AVR_HAVE_MUL__)

#if !defined(__AVR_TINY__)

// Workaround: Clang before 13, AVR: it calls these for its shifts of 32 bits.
#if defined(__clang__) && __clang_major__ < 13

uint32_t __ashlsi3(uint32_t a, uint8_t n) {
    union avr_words x = { .whole = a };

    for (; n != 0; n--) {
        bool carry = (int16_t)x.words[0] < 0;

        x.words[0] <<= 1;
        x.words[1] = (uint16_t)(x.words[1] << 1) | (uint16_t)carry;
    }
    return x.whole;
}

uint32_t __lshrsi3(uint32_t a, uint8_t n) {
    union avr_words x = { .whole = a };

    for (; n != 0; n--) {
        bool carry = (x.words[1] & 1) != 0;

        x.words[1] >>= 1;
        x.words[0] = (x.words[0] >> 1) | (carry ? 0x8000 : 0);
    }
    return x.whole;
}

int32_t __ashrsi3(int32_t a, uint8_t n) {
    union avr_words x = { .whole = (uint32_t)a };

    for (; n != 0; n--) {
        bool carry = (x.words[1] & 1) != 0;

        x.words[1] = (uint16_t)((int16_t)x.words[1] >> 1);
        x.words[0] = (x.words[0] >> 1) | (carry ? 0x8000 : 0);
    }
    return (int32_t)x.whole;
}

#endif // defined(__clang__) && __clang_major__ < 13

// Each operates on r25:r18 in place, taking r17:r10 where it takes more.

__asm__ (
    AVR_BEGIN("__adddi3")
    "add r18, r10\n\t"
    "adc r19, r11\n\t"
    "adc r20, r12\n\t"
    "adc r21, r13\n\t"
    "adc r22, r14\n\t"
    "adc r23, r15\n\t"
    "adc r24, r16\n\t"
    "adc r25, r17\n\t"
    "ret\n\t"
    AVR_END("__adddi3")
);

__asm__ (
    AVR_BEGIN("__subdi3")
    "sub r18, r10\n\t"
    "sbc r19, r11\n\t"
    "sbc r20, r12\n\t"
    "sbc r21, r13\n\t"
    "sbc r22, r14\n\t"
    "sbc r23, r15\n\t"
    "sbc r24, r16\n\t"
    "sbc r25, r17\n\t"
    "ret\n\t"
    AVR_END("__subdi3")
);

// The temporary register gets the sign extension of r26.
#define AVR_SIGN_R26 \
    "mov r0, r26\n\t" \
    "lsl r0\n\t" \
    "sbc r0, r0\n\t"

// Adds the sign-extended r26.
__asm__ (
    AVR_BEGIN("__adddi3_s8")
    AVR_SIGN_R26
    "add r18, r26\n\t"
    "adc r19, r0\n\t"
    "adc r20, r0\n\t"
    "adc r21, r0\n\t"
    "adc r22, r0\n\t"
    "adc r23, r0\n\t"
    "adc r24, r0\n\t"
    "adc r25, r0\n\t"
    "ret\n\t"
    AVR_END("__adddi3_s8")
);

// These compare in the flags, which are the results of the subtraction.

__asm__ (
    AVR_BEGIN("__cmpdi2")
    "cp r18, r10\n\t"
    "cpc r19, r11\n\t"
    "cpc r20, r12\n\t"
    "cpc r21, r13\n\t"
    "cpc r22, r14\n\t"
    "cpc r23, r15\n\t"
    "cpc r24, r16\n\t"
    "cpc r25, r17\n\t"
    "ret\n\t"
    AVR_END("__cmpdi2")
);

__asm__ (
    AVR_BEGIN("__cmpdi2_s8")
    AVR_SIGN_R26
    "cp r18, r26\n\t"
    "cpc r19, r0\n\t"
    "cpc r20, r0\n\t"
    "cpc r21, r0\n\t"
    "cpc r22, r0\n\t"
    "cpc r23, r0\n\t"
    "cpc r24, r0\n\t"
    "cpc r25, r0\n\t"
    "ret\n\t"
    AVR_END("__cmpdi2_s8")
);

__asm__ (
    AVR_BEGIN("__negdi2")
    "com r25\n\t"
    "com r24\n\t"
    "com r23\n\t"
    "com r22\n\t"
    "com r21\n\t"
    "com r20\n\t"
    "com r19\n\t"
    "neg r18\n\t"
    "sbci r19, -1\n\t"
    "sbci r20, -1\n\t"
    "sbci r21, -1\n\t"
    "sbci r22, -1\n\t"
    "sbci r23, -1\n\t"
    "sbci r24, -1\n\t"
    "sbci r25, -1\n\t"
    "ret\n\t"
    AVR_END("__negdi2")
);

__asm__ (
    AVR_BEGIN("__bswapdi2")
    "mov r0, r18\n\t"
    "mov r18, r25\n\t"
    "mov r25, r0\n\t"
    "mov r0, r19\n\t"
    "mov r19, r24\n\t"
    "mov r24, r0\n\t"
    "mov r0, r20\n\t"
    "mov r20, r23\n\t"
    "mov r23, r0\n\t"
    "mov r0, r21\n\t"
    "mov r21, r22\n\t"
    "mov r22, r0\n\t"
    "ret\n\t"
    AVR_END("__bswapdi2")
);

// These shift by the byte in r16, as what r17 holds does not count.

AVR_STUB("__ashldi3", "avr__ashldi3", AVR_PUSH_X_Z, AVR_POP_X_Z)

AVR_STUB("__lshrdi3", "avr__lshrdi3", AVR_PUSH_X_Z, AVR_POP_X_Z)

AVR_STUB("__ashrdi3", "avr__ashrdi3", AVR_PUSH_X_Z, AVR_POP_X_Z)

AVR_HELPER uint64_t avr__rotldi3(uint64_t a, uint8_t n) {
    uint8_t s = n & 63;

    if (s == 0) {
        return a;
    }
    return (uint64_t)avr__ashldi3((int64_t)a, s)
         | (uint64_t)avr__lshrdi3((int64_t)a, (uint8_t)((unsigned int)64 - s));
}

AVR_STUB("__rotldi3", "avr__rotldi3", AVR_PUSH_X_Z, AVR_POP_X_Z)

// r25:r22 * r21:r18, returning in r25:r22, or in r25:r18 where the product is
// whole.
#if defined(__AVR_HAVE_MUL__)

// The products of the bytes, added up by columns.
AVR_HELPER uint32_t avr__mulsi3(uint32_t a, uint32_t b) {
    union avr_words x = { .whole = a };
    union avr_words y = { .whole = b };
    union avr_words r;
    uint16_t p00 = (uint16_t)x.bytes[0] * y.bytes[0];
    uint16_t p01 = (uint16_t)x.bytes[0] * y.bytes[1];
    uint16_t p10 = (uint16_t)x.bytes[1] * y.bytes[0];
    uint16_t p02 = (uint16_t)x.bytes[0] * y.bytes[2];
    uint16_t p11 = (uint16_t)x.bytes[1] * y.bytes[1];
    uint16_t p20 = (uint16_t)x.bytes[2] * y.bytes[0];
    uint8_t top = (uint8_t)((uint16_t)x.bytes[0] * y.bytes[3] + (uint16_t)x.bytes[1] * y.bytes[2]
                          + (uint16_t)x.bytes[2] * y.bytes[1] + (uint16_t)x.bytes[3] * y.bytes[0]);
    uint16_t c1 = (uint16_t)((p00 >> 8) + (uint8_t)p01 + (uint8_t)p10);
    uint16_t c2 = (uint16_t)((c1 >> 8) + (p01 >> 8) + (p10 >> 8) + (uint8_t)p02 + (uint8_t)p11
                           + (uint8_t)p20);

    r.bytes[0] = (uint8_t)p00;
    r.bytes[1] = (uint8_t)c1;
    r.bytes[2] = (uint8_t)c2;
    r.bytes[3] = (uint8_t)((c2 >> 8) + (p02 >> 8) + (p11 >> 8) + (p20 >> 8) + top);
    return r.whole;
}

static inline uint64_t avr_wide_product(uint32_t a, uint32_t b) {
    return wide_mul32(a, b);
}

#else // defined(__AVR_HAVE_MUL__)

AVR_HELPER uint32_t avr__mulsi3(uint32_t a, uint32_t b) {
    return shift_add_mul32(a, b);
}

// Adds the second operand above the first for each of its set bits, shifting
// the sum and the first operand down together.
static inline uint64_t avr_wide_product(uint32_t a, uint32_t b) {
    uint32_t high = 0;

    for (uint8_t i = 32; i != 0; i--) {
        bool bit = (a & 1) != 0;
        bool carry = false;

        if (bit) {
            high += b;
            carry = high < b;
        }
        a = (a >> 1) | ((high & 1) != 0 ? (uint32_t)0x80000000 : 0);
        high = (high >> 1) | (carry ? (uint32_t)0x80000000 : 0);
    }
    return JOIN_32(high, a);
}

#endif // defined(__AVR_HAVE_MUL__)

AVR_STUB("__mulsi3", "avr__mulsi3", AVR_PUSH_18_TO_21, AVR_POP_18_TO_21)

AVR_HELPER uint64_t avr__umulsidi3(uint32_t a, uint32_t b) {
    return avr_wide_product(a, b);
}

AVR_STUB("__umulsidi3", "avr__umulsidi3", AVR_PUSH_X_Z, AVR_POP_X_Z)

// A negative operand read as unsigned adds the other above the product.
AVR_HELPER uint64_t avr__mulsidi3(int32_t a, int32_t b) {
    uint32_t x = (uint32_t)a;
    uint32_t y = (uint32_t)b;
    uint64_t p = avr_wide_product(x, y);
    uint32_t over = (a < 0 ? y : 0) + (b < 0 ? x : 0);

    return JOIN_32(HIGH_32(p) - over, (uint32_t)p);
}

AVR_STUB("__mulsidi3", "avr__mulsidi3", AVR_PUSH_X_Z, AVR_POP_X_Z)

// r24:r22 * r20:r18, returning in r24:r22.
__asm__ (
    AVR_BEGIN("__mulpsi3")
    "push r21\n\t"
    "push r25\n\t"
    "clr r21\n\t"
    "clr r25\n\t"
    AVR_CALL("__mulsi3")
    "pop r25\n\t"
    "pop r21\n\t"
    "ret\n\t"
    AVR_END("__mulpsi3")
);

// The dividend's bits go to the top, for the same step as on 32 bits.
static inline uint32_t avr_keep_top(uint32_t kept, uint32_t value) {
    return (kept & (uint32_t)0xff000000) | (value & (uint32_t)0x00ffffff);
}

AVR_HELPER void avr__udivmodpsi4(struct avr_operands *v) {
    uint32_t r;
    uint32_t q = avr_udivmod32(v->first << 8, v->second & (uint32_t)0x00ffffff, 24, &r);

    v->first = avr_keep_top(v->first, q);
    v->second = avr_keep_top(v->second, r);
}

AVR_HELPER void avr__divmodpsi4(struct avr_operands *v) {
    int32_t a = (int32_t)(v->first << 8) >> 8;
    int32_t b = (int32_t)(v->second << 8) >> 8;
    uint32_t r;
    uint32_t q = avr_udivmod32(
        AVR_MAGNITUDE(uint32_t, a) << 8, AVR_MAGNITUDE(uint32_t, b), 24, &r
    );

    v->first = avr_keep_top(v->first, (a ^ b) < 0 ? (uint32_t)0 - q : q);
    v->second = avr_keep_top(v->second, a < 0 ? (uint32_t)0 - r : r);
}

AVR_ON_OPERANDS(__udivmodpsi4)
AVR_ON_OPERANDS(__divmodpsi4)

// Only cores with the multiply instructions get calls to these.
#if defined(__AVR_HAVE_MUL__)

// r19:r18 * r27:r26, returning in r25:r22.
__asm__ (
    AVR_BEGIN("__umulhisi3")
    "mul r18, r26\n\t"
    "mov r22, r0\n\t"
    "mov r23, r1\n\t"
    "mul r19, r27\n\t"
    "mov r24, r0\n\t"
    "mov r25, r1\n\t"
    "mul r18, r27\n\t"
    "add r23, r0\n\t"
    "adc r24, r1\n\t"
    "clr r1\n\t"
    "adc r25, r1\n\t"
    "mul r19, r26\n\t"
    "add r23, r0\n\t"
    "adc r24, r1\n\t"
    "clr r1\n\t"
    "adc r25, r1\n\t"
    "ret\n\t"
    AVR_END("__umulhisi3")
);

// A negative operand read as unsigned is 2^16 too large, which adds the other
// operand to the upper half of the product.
__asm__ (
    AVR_BEGIN("__mulhisi3")
    AVR_CALL("__umulhisi3")
    "sbrs r19, 7\n\t"
    "rjmp 1f\n\t"
    "sub r24, r26\n\t"
    "sbc r25, r27\n\t"
    "1:\n\t"
    "sbrs r27, 7\n\t"
    "rjmp 2f\n\t"
    "sub r24, r18\n\t"
    "sbc r25, r19\n\t"
    "2:\n\t"
    "ret\n\t"
    AVR_END("__mulhisi3")
);

// The operand in r27:r26 is the signed one.
__asm__ (
    AVR_BEGIN("__usmulhisi3")
    AVR_CALL("__umulhisi3")
    "sbrs r27, 7\n\t"
    "rjmp 1f\n\t"
    "sub r24, r18\n\t"
    "sbc r25, r19\n\t"
    "1:\n\t"
    "ret\n\t"
    AVR_END("__usmulhisi3")
);

// r27:r26, extended as the name says, * r21:r18, returning in r25:r22.

__asm__ (
    AVR_BEGIN("__muluhisi3")
    "mov r22, r26\n\t"
    "mov r23, r27\n\t"
    "clr r24\n\t"
    "clr r25\n\t"
    AVR_JUMP("__mulsi3")
    AVR_END("__muluhisi3")
);

__asm__ (
    AVR_BEGIN("__mulshisi3")
    "mov r22, r26\n\t"
    "mov r23, r27\n\t"
    "mov r24, r27\n\t"
    "lsl r24\n\t"
    "sbc r24, r24\n\t"
    "mov r25, r24\n\t"
    AVR_JUMP("__mulsi3")
    AVR_END("__mulshisi3")
);

// The compilers call this one for negative constants.
__asm__ (
    AVR_BEGIN("__mulohisi3")
    "mov r22, r26\n\t"
    "mov r23, r27\n\t"
    "ldi r24, -1\n\t"
    "ldi r25, -1\n\t"
    AVR_JUMP("__mulsi3")
    AVR_END("__mulohisi3")
);

// The signed r25 * r24:r22, returning in r20:r18.
__asm__ (
    AVR_BEGIN("__mulsqipsi3")
    "push r21\n\t"
    "push r22\n\t"
    "push r23\n\t"
    "push r24\n\t"
    "push r25\n\t"
    "mov r18, r25\n\t"
    "mov r19, r25\n\t"
    "lsl r19\n\t"
    "sbc r19, r19\n\t"
    "mov r20, r19\n\t"
    "mov r21, r19\n\t"
    AVR_CALL("__mulsi3")
    "mov r18, r22\n\t"
    "mov r19, r23\n\t"
    "mov r20, r24\n\t"
    "pop r25\n\t"
    "pop r24\n\t"
    "pop r23\n\t"
    "pop r22\n\t"
    "pop r21\n\t"
    "ret\n\t"
    AVR_END("__mulsqipsi3")
);

#else // defined(__AVR_HAVE_MUL__)

// The fractional multiplications, for the cores without their instructions:
// r24 * r25, with r24 signed in the signed ones, shifted left by one,
// returning in r23:r22. A negative operand read as unsigned is 2^8 too large,
// which adds the other operand to the upper half of the product. r26 and the
// zero register are the multiplicand until the end.
__asm__ (
    ".pushsection .text.__fmul,\"ax\",@progbits\n\t"
    AVR_ENTRY("__fmul", ".Lavr_fmul_end")
    "rcall 3f\n\t"
    "rjmp 2f\n\t"
    AVR_ENTRY("__fmuls", ".Lavr_fmul_end")
    "rcall 3f\n\t"
    "sbrc r25, 7\n\t"
    "sub r23, r24\n\t"
    "rjmp 1f\n\t"
    AVR_ENTRY("__fmulsu", ".Lavr_fmul_end")
    "rcall 3f\n\t"
    "1:\n\t"
    "sbrc r24, 7\n\t"
    "sub r23, r25\n\t"
    "2:\n\t"
    "lsl r22\n\t"
    "rol r23\n\t"
    "ret\n\t"
    "3:\n\t"
    "push r26\n\t"
    "mov r26, r24\n\t"
    "mov r0, r25\n\t"
    "clr r22\n\t"
    "clr r23\n\t"
    "4:\n\t"
    "lsr r0\n\t"
    "brcc 5f\n\t"
    "add r22, r26\n\t"
    "adc r23, r1\n\t"
    "5:\n\t"
    "lsl r26\n\t"
    "rol r1\n\t"
    "tst r0\n\t"
    "brne 4b\n\t"
    "clr r1\n\t"
    "pop r26\n\t"
    "ret\n\t"
    ".Lavr_fmul_end:\n\t"
    ".popsection"
);

#endif // defined(__AVR_HAVE_MUL__)

// These load r22 upwards from flash at Z, or at r21:Z, whose top bit tells
// that it points to data memory instead.

#define AVR_LOAD_1(prefix) prefix("r22")
#define AVR_LOAD_2(prefix) AVR_LOAD_1(prefix) prefix("r23")
#define AVR_LOAD_3(prefix) AVR_LOAD_2(prefix) prefix("r24")
#define AVR_LOAD_4(prefix) AVR_LOAD_3(prefix) prefix("r25")

#define AVR_READ_RAM(r) "ld " r ", Z+\n\t"

// __load_N reads the 64 KiB that lpm alone reaches.
#define AVR_READ_NEAR(r) \
    "lpm\n\t" \
    "mov " r ", r0\n\t" \
    "adiw r30, 1\n\t"

#define AVR_FLASH_LOADS(n) \
    __asm__ ( \
        AVR_BEGIN("__load_" #n) \
        "push r30\n\t" \
        "push r31\n\t" \
        AVR_LOAD_##n(AVR_READ_NEAR) \
        "pop r31\n\t" \
        "pop r30\n\t" \
        "ret\n\t" \
        AVR_END("__load_" #n) \
    ); \
    __asm__ ( \
        AVR_BEGIN("__fload_" #n) \
        "push r30\n\t" \
        "push r31\n\t" \
        AVR_SET_RAMPZ("r21") \
        AVR_LOAD_##n(AVR_READ) \
        AVR_CLEAR_RAMPZ \
        "pop r31\n\t" \
        "pop r30\n\t" \
        "ret\n\t" \
        AVR_END("__fload_" #n) \
    ); \
    __asm__ ( \
        AVR_BEGIN("__xload_" #n) \
        "push r30\n\t" \
        "push r31\n\t" \
        "sbrs r21, 7\n\t" \
        "rjmp 1f\n\t" \
        AVR_LOAD_##n(AVR_READ_RAM) \
        "rjmp 2f\n\t" \
        "1:\n\t" \
        AVR_SET_RAMPZ("r21") \
        AVR_LOAD_##n(AVR_READ) \
        AVR_CLEAR_RAMPZ \
        "2:\n\t" \
        "pop r31\n\t" \
        "pop r30\n\t" \
        "ret\n\t" \
        AVR_END("__xload_" #n) \
    );

AVR_FLASH_LOADS(1)
AVR_FLASH_LOADS(2)
AVR_FLASH_LOADS(3)
AVR_FLASH_LOADS(4)

// These copy r25:r24 bytes, or r24 for the _qi ones, from r23:Z to X. The top
// bit of r23 tells flash from data memory as in __xload_N, but for
// __movmemf_N, whose source is always in flash.

#define AVR_COPY_LOOP(copy) \
    "1:\n\t" \
    copy \
    "subi r24, 1\n\t" \
    "sbci r25, 0\n\t" \
    "brne 1b\n\t"

#define AVR_COPY_SAVE \
    "push r24\n\t" \
    "push r25\n\t" \
    "push r26\n\t" \
    "push r27\n\t" \
    "push r30\n\t" \
    "push r31\n\t" \
    "mov r0, r24\n\t" \
    "or r0, r25\n\t" \
    "breq 3f\n\t"

#define AVR_COPY_RESTORE \
    "3:\n\t" \
    "pop r31\n\t" \
    "pop r30\n\t" \
    "pop r27\n\t" \
    "pop r26\n\t" \
    "pop r25\n\t" \
    "pop r24\n\t" \
    "ret\n\t"

#define AVR_COPY_FLASH \
    AVR_SET_RAMPZ("r23") \
    AVR_COPY_LOOP(AVR_COPY_FLASH_BYTE) \
    AVR_CLEAR_RAMPZ

__asm__ (
    ".pushsection .text.__movmemf_qi,\"ax\",@progbits\n\t"
    AVR_ENTRY("__movmemf_qi", ".Lavr_movmemf_end")
    "push r25\n\t"
    "clr r25\n\t"
    "rcall __movmemf_hi\n\t"
    "pop r25\n\t"
    "ret\n\t"
    AVR_ENTRY("__movmemf_hi", ".Lavr_movmemf_end")
    AVR_COPY_SAVE
    AVR_COPY_FLASH
    AVR_COPY_RESTORE
    ".Lavr_movmemf_end:\n\t"
    ".popsection"
);

__asm__ (
    ".pushsection .text.__movmemx_qi,\"ax\",@progbits\n\t"
    AVR_ENTRY("__movmemx_qi", ".Lavr_movmemx_end")
    "push r25\n\t"
    "clr r25\n\t"
    "rcall __movmemx_hi\n\t"
    "pop r25\n\t"
    "ret\n\t"
    AVR_ENTRY("__movmemx_hi", ".Lavr_movmemx_end")
    AVR_COPY_SAVE
    "sbrc r23, 7\n\t"
    "rjmp 2f\n\t"
    AVR_COPY_FLASH
    "rjmp 3f\n\t"
    "2:\n\t"
    AVR_COPY_LOOP(
        "ld r0, Z+\n\t"
        "st X+, r0\n\t"
    )
    AVR_COPY_RESTORE
    ".Lavr_movmemx_end:\n\t"
    ".popsection"
);

#if !defined(__AVR_TINY__)

// GCC calls this for __builtin_avr_strlen_memx, with the ordinary convention:
// the address in r24:r23:r22, whose top bit tells flash from data memory as in
// __xload_N, and the length returned in r25:r24.
uint16_t __strlen_memx(uint32_t address) {
    union avr_words x = { .whole = address };
    uint16_t n = 0;

    if ((x.bytes[2] & 0x80) != 0) {
        const char *s = (const char *)x.words[0];

        while (s[n] != 0) {
            n++;
        }
    } else {
        while (avr_read_flash(address + n) != 0) {
            n++;
        }
    }
    return n;
}

#endif // !defined(__AVR_TINY__)

// Sets the stack pointer from Y, where that takes no masking of interrupts:
// XMEGA cores keep them off after a write of the stack pointer, and it is one
// write on the cores with 8 bits of it. Other cores have no routines of
// -mcall-prologues, which would have to mask them.
#if defined(__AVR_ARCH__) && __AVR_ARCH__ >= 102
#   define AVR_SET_SP \
        "out " AVR_SPL ", r28\n\t" \
        "out " AVR_SPH ", r29\n\t"
#elif defined(__AVR_HAVE_8BIT_SP__) || defined(__AVR_SP8__)
#   define AVR_SET_SP "out " AVR_SPL ", r28\n\t"
#endif

#if defined(__AVR_HAVE_8BIT_SP__) || defined(__AVR_SP8__)
#   define AVR_GET_SP \
        "in r28, " AVR_SPL "\n\t" \
        "clr r29\n\t"
#else
#   define AVR_GET_SP \
        "in r28, " AVR_SPL "\n\t" \
        "in r29, " AVR_SPH "\n\t"
#endif

#if defined(__AVR_HAVE_EIJMP_EICALL__)
#   define AVR_IJMP "eijmp\n\t"
#else
#   define AVR_IJMP "ijmp\n\t"
#endif

#if defined(AVR_SET_SP)

// With -mcall-prologues, prologues jump into this, past the pushes of the
// registers they do not save, 2 bytes each, with the size of their frame in X
// and where to continue, as a word address, in Z. It leaves Y at the frame.
__asm__ (
    AVR_BEGIN("__prologue_saves__")
    "push r2\n\t"
    "push r3\n\t"
    "push r4\n\t"
    "push r5\n\t"
    "push r6\n\t"
    "push r7\n\t"
    "push r8\n\t"
    "push r9\n\t"
    "push r10\n\t"
    "push r11\n\t"
    "push r12\n\t"
    "push r13\n\t"
    "push r14\n\t"
    "push r15\n\t"
    "push r16\n\t"
    "push r17\n\t"
    "push r28\n\t"
    "push r29\n\t"
    AVR_GET_SP
    "sub r28, r26\n\t"
    "sbc r29, r27\n\t"
    AVR_SET_SP
    AVR_IJMP
    AVR_END("__prologue_saves__")
);

// Epilogues jump into this likewise, past the loads of the registers they did
// not save, 2 bytes each, with Y just below the saved registers and their
// number in r30. It returns to the caller of the function.
__asm__ (
    AVR_BEGIN("__epilogue_restores__")
    "ldd r2, Y+18\n\t"
    "ldd r3, Y+17\n\t"
    "ldd r4, Y+16\n\t"
    "ldd r5, Y+15\n\t"
    "ldd r6, Y+14\n\t"
    "ldd r7, Y+13\n\t"
    "ldd r8, Y+12\n\t"
    "ldd r9, Y+11\n\t"
    "ldd r10, Y+10\n\t"
    "ldd r11, Y+9\n\t"
    "ldd r12, Y+8\n\t"
    "ldd r13, Y+7\n\t"
    "ldd r14, Y+6\n\t"
    "ldd r15, Y+5\n\t"
    "ldd r16, Y+4\n\t"
    "ldd r17, Y+3\n\t"
    "ldd r26, Y+2\n\t"
    "ldd r27, Y+1\n\t"
    "add r28, r30\n\t"
    "adc r29, r1\n\t"
    AVR_SET_SP
    "mov r28, r26\n\t"
    "mov r29, r27\n\t"
    "ret\n\t"
    AVR_END("__epilogue_restores__")
);

#endif // defined(AVR_SET_SP)

// GCC dispatches jump tables through this, with the word address of the entry
// in Z, the high byte of it in r24 on cores with a 3-byte program counter, and
// in the carry it shifts out of Z on the other cores with RAMPZ. Before GCC 5,
// the tables of the former cores stay within the 64 KiB that lpm alone
// reaches.
#if defined(__AVR_HAVE_EIJMP_EICALL__) && !defined(__clang__) && __GNUC__ < 5
#   define AVR_TABLE_HIGH
#   define AVR_TABLE_LOAD "lpm"
#elif defined(__AVR_HAVE_EIJMP_EICALL__)
#   define AVR_TABLE_HIGH \
        "rol r24\n\t" \
        "out " AVR_RAMPZ ", r24\n\t"
#   define AVR_TABLE_LOAD "elpm"
#elif defined(__AVR_HAVE_ELPM__)
#   define AVR_TABLE_HIGH \
        "clr r0\n\t" \
        "rol r0\n\t" \
        "out " AVR_RAMPZ ", r0\n\t"
#   define AVR_TABLE_LOAD "elpm"
#else
#   define AVR_TABLE_HIGH
#   define AVR_TABLE_LOAD "lpm"
#endif

#if defined(__AVR_HAVE_LPMX__)
#   define AVR_TABLE_ENTRY \
        AVR_TABLE_LOAD " r0, Z+\n\t" \
        AVR_TABLE_LOAD " r31, Z\n\t" \
        "mov r30, r0\n\t"
#else
#   define AVR_TABLE_ENTRY \
        AVR_TABLE_LOAD "\n\t" \
        "adiw r30, 1\n\t" \
        "push r0\n\t" \
        AVR_TABLE_LOAD "\n\t" \
        "mov r31, r0\n\t" \
        "pop r30\n\t"
#endif

__asm__ (
    AVR_BEGIN("__tablejump2__")
    "lsl r30\n\t"
    "rol r31\n\t"
    AVR_TABLE_HIGH
    AVR_TABLE_ENTRY
    AVR_CLEAR_RAMPZ
    AVR_IJMP
    AVR_END("__tablejump2__")
);

#endif // !defined(__AVR_TINY__)

// Fixed-point routines with conventions of their own. A few instructions serve
// where another routine does the work, and the rest save what C may change, as
// above, around the C of the fixed-point block.
#if !defined(__clang__) && defined(__QQ_FBIT__)

#if defined(__AVR_HAVE_MOVW__)
#   define AVR_MOVE_PAIR(low, high, from_low, from_high) "movw " low ", " from_low "\n\t"
#else
#   define AVR_MOVE_PAIR(low, high, from_low, from_high) \
        "mov " low ", " from_low "\n\t" \
        "mov " high ", " from_high "\n\t"
#endif

// The bits builtins of stdfix.h take a value and give it back, at -O0.
__asm__ (
    AVR_BEGIN("__ret")
    "ret\n\t"
    AVR_END("__ret")
);

// Saturating, in r25:r24 and in r25:r22, with nothing else changed.
__asm__ (
    ".pushsection .text.__ssabs_2,\"ax\",@progbits\n\t"
    AVR_ENTRY("__ssabs_2", ".Lavr_ssabs_2_end")
    "sbrs r25, 7\n\t"
    "ret\n\t"
    AVR_ENTRY("__ssneg_2", ".Lavr_ssabs_2_end")
    "com r25\n\t"
    "neg r24\n\t"
    "sbci r25, -1\n\t"
    "brvc 1f\n\t"
    "subi r24, 1\n\t"
    "sbci r25, 0\n\t"
    "1:\n\t"
    "ret\n\t"
    ".Lavr_ssabs_2_end:\n\t"
    ".popsection"
);

__asm__ (
    ".pushsection .text.__ssabs_4,\"ax\",@progbits\n\t"
    AVR_ENTRY("__ssabs_4", ".Lavr_ssabs_4_end")
    "sbrs r25, 7\n\t"
    "ret\n\t"
    AVR_ENTRY("__ssneg_4", ".Lavr_ssabs_4_end")
    AVR_NEG4("r25", "r24", "r23", "r22")
    "brvc 1f\n\t"
    "subi r22, 1\n\t"
    "sbci r23, 0\n\t"
    "sbci r24, 0\n\t"
    "sbci r25, 0\n\t"
    "1:\n\t"
    "ret\n\t"
    ".Lavr_ssabs_4_end:\n\t"
    ".popsection"
);

#if defined(__AVR_HAVE_MUL__)

// r19:r18 * r27:r26, returning in r25:r24, by the fractional bits of the type:
// half of the last place goes on the whole product, in r25:r22, to round it to
// the nearest value, with ties up, and then the bytes below that place go.
#define AVR_FX_ROUNDED_7 \
    "subi r22, -64\n\t" \
    "sbci r23, -1\n\t" \
    "sbci r24, -1\n\t" \
    "lsl r22\n\t" \
    "rol r23\n\t" \
    "rol r24\n\t" \
    "mov r25, r24\n\t" \
    "mov r24, r23\n\t"

#define AVR_FX_ROUNDED_8 \
    "subi r22, -128\n\t" \
    "sbci r23, -1\n\t" \
    "sbci r24, -1\n\t" \
    "mov r25, r24\n\t" \
    "mov r24, r23\n\t"

#define AVR_FX_ROUNDED_15 \
    "subi r23, -64\n\t" \
    "sbci r24, -1\n\t" \
    "sbci r25, -1\n\t" \
    "lsl r23\n\t" \
    "rol r24\n\t" \
    "rol r25\n\t"

#define AVR_FX_ROUNDED_16 \
    "subi r23, -128\n\t" \
    "sbci r24, -1\n\t" \
    "sbci r25, -1\n\t"

#define AVR_FX_MUL16_EXPANDED(name, product, F) \
    __asm__ ( \
        AVR_BEGIN(name) \
        AVR_CALL(product) \
        AVR_FX_ROUNDED_##F \
        "ret\n\t" \
        AVR_END(name) \
    );

#define AVR_FX_MUL16(name, product, F) AVR_FX_MUL16_EXPANDED(name, product, F)

AVR_FX_MUL16("__mulhq3", "__mulhisi3", __HQ_FBIT__)
AVR_FX_MUL16("__mulha3", "__mulhisi3", __HA_FBIT__)
AVR_FX_MUL16("__muluhq3", "__umulhisi3", __UHQ_FBIT__)
AVR_FX_MUL16("__muluha3", "__umulhisi3", __UHA_FBIT__)

// r19:r16 * r23:r20, returning in r27:r24, with nothing else changed but for
// the flags. The whole product comes in r25:r18, and the result is the bytes
// r23:r20 of its sum with half of the last place, once they line up.
#define AVR_FX_ROUNDED_LONG_15 \
    "subi r19, -64\n\t" \
    "sbci r20, -1\n\t" \
    "sbci r21, -1\n\t" \
    "sbci r22, -1\n\t" \
    "sbci r23, -1\n\t" \
    "lsl r19\n\t" \
    "rol r20\n\t" \
    "rol r21\n\t" \
    "rol r22\n\t" \
    "rol r23\n\t"

#define AVR_FX_ROUNDED_LONG_16 \
    "subi r19, -128\n\t" \
    "sbci r20, -1\n\t" \
    "sbci r21, -1\n\t" \
    "sbci r22, -1\n\t" \
    "sbci r23, -1\n\t"

#define AVR_FX_MUL32_EXPANDED(name, product, F) \
    __asm__ ( \
        AVR_BEGIN(name) \
        "push r18\n\t" \
        "push r19\n\t" \
        "push r20\n\t" \
        "push r21\n\t" \
        "push r22\n\t" \
        "push r23\n\t" \
        "movw r24, r18\n\t" \
        "movw r18, r20\n\t" \
        "movw r20, r22\n\t" \
        "movw r22, r16\n\t" \
        AVR_CALL(product) \
        AVR_FX_ROUNDED_LONG_##F \
        "movw r24, r20\n\t" \
        "movw r26, r22\n\t" \
        "pop r23\n\t" \
        "pop r22\n\t" \
        "pop r21\n\t" \
        "pop r20\n\t" \
        "pop r19\n\t" \
        "pop r18\n\t" \
        "ret\n\t" \
        AVR_END(name) \
    );

#define AVR_FX_MUL32(name, product, F) AVR_FX_MUL32_EXPANDED(name, product, F)

AVR_FX_MUL32("__mulsa3", "__mulsidi3", __SA_FBIT__)
AVR_FX_MUL32("__mulusa3", "__umulsidi3", __USA_FBIT__)

#else // defined(__AVR_HAVE_MUL__)

// r24 * r22, both unsigned, returning in r25:r24.
__asm__ (
    AVR_BEGIN("__umulqihi3")
    "clr r25\n\t"
    "clr r23\n\t"
    AVR_JUMP("__mulhi3")
    AVR_END("__umulqihi3")
);

// r24 * r25, returning in r23, in the way of the multiplication that cores
// with the instruction have inline: the whole product shifted left by one, of
// which the upper byte counts, which rounds down, and the one product that has
// no room in it gives the most positive value.
__asm__ (
    AVR_BEGIN("__mulqq3")
    "mov r22, r25\n\t"
    "mov r23, r25\n\t"
    "lsl r23\n\t"
    "sbc r23, r23\n\t"
    "mov r25, r24\n\t"
    "lsl r25\n\t"
    "sbc r25, r25\n\t"
    AVR_CALL("__mulhi3")
    "lsl r24\n\t"
    "rol r25\n\t"
    "mov r23, r25\n\t"
    "dec r23\n\t"
    "brvs 1f\n\t"
    "inc r23\n\t"
    "1:\n\t"
    "ret\n\t"
    AVR_END("__mulqq3")
);

#endif // defined(__AVR_HAVE_MUL__)

// r25 / r22, returning in r24, with r25 alone changed but for that.
#define AVR_FX_DIV8(name, F, is_signed) \
    AVR_HELPER uint8_t avr##name(uint8_t a, uint8_t b) { \
        return (uint8_t)fx_shared_div8(a, b, FX_PACK(8, F, is_signed, false)); \
    } \
    \
    AVR_STUB( \
        #name, "avr" #name, \
        AVR_PUSH_18_TO_23 \
        "mov r24, r25\n\t", \
        AVR_POP_18_TO_23 \
    )

AVR_FX_DIV8(__divqq3, __QQ_FBIT__, true)
AVR_FX_DIV8(__udivuqq3, __UQQ_FBIT__, false)

// r27:r26 / r23:r22, returning in r25:r24. r27:r26 and r21 may change.
#define AVR_FX_DIV16(name, F, is_signed) \
    AVR_HELPER uint16_t avr##name(uint16_t a, uint16_t b) { \
        return fx_shared_div16(a, b, FX_PACK(16, F, is_signed, false)); \
    } \
    \
    AVR_STUB( \
        #name, "avr" #name, \
        "push r18\n\t" \
        "push r19\n\t" \
        "push r20\n\t" \
        "push r22\n\t" \
        "push r23\n\t" \
        "push r30\n\t" \
        "push r31\n\t" \
        AVR_MOVE_PAIR("r24", "r25", "r26", "r27"), \
        "pop r31\n\t" \
        "pop r30\n\t" \
        "pop r23\n\t" \
        "pop r22\n\t" \
        "pop r20\n\t" \
        "pop r19\n\t" \
        "pop r18\n\t" \
    )

AVR_FX_DIV16(__divhq3, __HQ_FBIT__, true)
AVR_FX_DIV16(__divha3, __HA_FBIT__, true)
AVR_FX_DIV16(__udivuhq3, __UHQ_FBIT__, false)
AVR_FX_DIV16(__udivuha3, __UHA_FBIT__, false)

// r27:r24 / r21:r18, returning in r25:r22. r27:r26 and r31:r30 may change.
// Reduced cores would pass the divisor to C on the stack, where C may change
// it, so there it gets a pointer to it, and the saved copy stays as it is.
#define AVR_FX_DIV32_PUSH \
    "push r21\n\t" \
    "push r20\n\t" \
    "push r19\n\t" \
    "push r18\n\t" \
    AVR_MOVE_PAIR("r22", "r23", "r24", "r25") \
    AVR_MOVE_PAIR("r24", "r25", "r26", "r27")

#define AVR_FX_DIV32_POP \
    "pop r18\n\t" \
    "pop r19\n\t" \
    "pop r20\n\t" \
    "pop r21\n\t"

#if defined(__AVR_TINY__)

#   if defined(__AVR_HAVE_8BIT_SP__) || defined(__AVR_SP8__)
#       define AVR_FX_DIVISOR_HIGH "clr r21\n\t"
#   else
#       define AVR_FX_DIVISOR_HIGH "in r21, " AVR_SPH "\n\t"
#   endif

#   define AVR_FX_DIV32(name, F, is_signed) \
        AVR_HELPER uint32_t avr##name(uint32_t a, const uint32_t *b) { \
            return fx_shared_div32(a, *b, FX_PACK(32, F, is_signed, false)); \
        } \
        \
        AVR_STUB( \
            #name, "avr" #name, \
            AVR_FX_DIV32_PUSH \
            "in r20, " AVR_SPL "\n\t" \
            AVR_FX_DIVISOR_HIGH \
            "subi r20, -1\n\t" \
            "sbci r21, -1\n\t", \
            AVR_FX_DIV32_POP \
        )

#else // defined(__AVR_TINY__)

#   define AVR_FX_DIV32(name, F, is_signed) \
        AVR_HELPER uint32_t avr##name(uint32_t a, uint32_t b) { \
            return fx_shared_div32(a, b, FX_PACK(32, F, is_signed, false)); \
        } \
        \
        AVR_STUB(#name, "avr" #name, AVR_FX_DIV32_PUSH, AVR_FX_DIV32_POP)

#endif // defined(__AVR_TINY__)

AVR_FX_DIV32(__divsa3, __SA_FBIT__, true)
AVR_FX_DIV32(__udivusa3, __USA_FBIT__, false)

// The count in r24, and the value in r22, r23:r22, or r21:r18, returning in
// r24, r25:r24, or r25:r22, which changes what held the value but no more.
#define AVR_FX_ROUND8(m, M, is_signed) \
    AVR_HELPER uint8_t avr__round##m##3(uint8_t x, int8_t n) { \
        return (uint8_t)fx_shared_round8(x, n, FX_PACK(8, __##M##_FBIT__, is_signed, false)); \
    } \
    \
    AVR_STUB( \
        "__round" #m "3", "avr__round" #m "3", \
        "push r25\n\t" \
        "push r23\n\t" \
        AVR_PUSH_18_TO_21 \
        "mov " AVR_TMP ", r22\n\t" \
        "mov r22, r24\n\t" \
        "mov r24, " AVR_TMP "\n\t", \
        AVR_POP_18_TO_21 \
        "pop r23\n\t" \
        "pop r25\n\t" \
    )

#define AVR_FX_ROUND16(m, M, is_signed) \
    AVR_HELPER uint16_t avr__round##m##3(uint16_t x, int8_t n) { \
        return fx_shared_round16(x, n, FX_PACK(16, __##M##_FBIT__, is_signed, false)); \
    } \
    \
    AVR_STUB( \
        "__round" #m "3", "avr__round" #m "3", \
        AVR_PUSH_18_TO_21 \
        "mov " AVR_TMP ", r24\n\t" \
        AVR_MOVE_PAIR("r24", "r25", "r22", "r23") \
        "mov r22, " AVR_TMP "\n\t", \
        AVR_POP_18_TO_21 \
    )

#define AVR_FX_ROUND32(m, M, is_signed) \
    AVR_HELPER uint32_t avr__round##m##3(uint32_t x, int8_t n) { \
        return fx_shared_round32(x, n, FX_PACK(32, __##M##_FBIT__, is_signed, false)); \
    } \
    \
    AVR_STUB( \
        "__round" #m "3", "avr__round" #m "3", \
        AVR_PUSH_X_Z \
        "mov " AVR_TMP ", r24\n\t" \
        AVR_MOVE_PAIR("r24", "r25", "r20", "r21") \
        AVR_MOVE_PAIR("r22", "r23", "r18", "r19") \
        "mov r20, " AVR_TMP "\n\t", \
        AVR_POP_X_Z \
    )

AVR_FX_ROUND8(qq, QQ, true)
AVR_FX_ROUND8(uqq, UQQ, false)
AVR_FX_ROUND16(hq, HQ, true)
AVR_FX_ROUND16(ha, HA, true)
AVR_FX_ROUND16(uhq, UHQ, false)
AVR_FX_ROUND16(uha, UHA, false)
AVR_FX_ROUND32(sq, SQ, true)
AVR_FX_ROUND32(sa, SA, true)
AVR_FX_ROUND32(usq, USQ, false)
AVR_FX_ROUND32(usa, USA, false)

// The compilers add and subtract constants inline on 8 bytes, and saturate
// with these: r25:r18 become all ones if the carry is set, and zeros with the
// other, with nothing else changed.
#if !defined(__AVR_TINY__)

__asm__ (
    AVR_BEGIN("__sbc_8")
    "sbc r18, r18\n\t"
    "sbc r19, r19\n\t"
    "sbc r20, r20\n\t"
    "sbc r21, r21\n\t"
    "sbc r22, r22\n\t"
    "sbc r23, r23\n\t"
    "sbc r24, r24\n\t"
    "sbc r25, r25\n\t"
    "ret\n\t"
    AVR_END("__sbc_8")
);

__asm__ (
    AVR_BEGIN("__clr_8")
    "clr r18\n\t"
    "clr r19\n\t"
    "clr r20\n\t"
    "clr r21\n\t"
    "clr r22\n\t"
    "clr r23\n\t"
    "clr r24\n\t"
    "clr r25\n\t"
    "ret\n\t"
    AVR_END("__clr_8")
);

// r25:r18 and r17:r10, in place, with nothing else changed.
#define AVR_FX_8_BYTES(op, expression) \
    AVR_HELPER uint64_t avr_fx_##op(uint64_t a, uint64_t b) { \
        return (expression); \
    }

#define AVR_FX_8_BYTES_STUB(name, op) AVR_STUB(name, "avr_fx_" #op, AVR_PUSH_X_Z, AVR_POP_X_Z)

AVR_FX_8_BYTES(ssadd, fx_ssadd64(a, b, 64))
AVR_FX_8_BYTES(sssub, fx_sssub64(a, b, 64))
AVR_FX_8_BYTES(usadd, fx_usadd64(a, b, 64))
AVR_FX_8_BYTES(ussub, fx_ussub64(a, b))

AVR_FX_8_BYTES_STUB("__ssadddq3", ssadd)
AVR_FX_8_BYTES_STUB("__ssaddda3", ssadd)
AVR_FX_8_BYTES_STUB("__ssaddta3", ssadd)
AVR_FX_8_BYTES_STUB("__sssubdq3", sssub)
AVR_FX_8_BYTES_STUB("__sssubda3", sssub)
AVR_FX_8_BYTES_STUB("__sssubta3", sssub)
AVR_FX_8_BYTES_STUB("__usaddudq3", usadd)
AVR_FX_8_BYTES_STUB("__usadduda3", usadd)
AVR_FX_8_BYTES_STUB("__usadduta3", usadd)
AVR_FX_8_BYTES_STUB("__ussubudq3", ussub)
AVR_FX_8_BYTES_STUB("__ussubuda3", ussub)
AVR_FX_8_BYTES_STUB("__ussubuta3", ussub)

#endif // !defined(__AVR_TINY__)

#endif // !defined(__clang__) && defined(__QQ_FBIT__)

#endif // defined(__AVR__)

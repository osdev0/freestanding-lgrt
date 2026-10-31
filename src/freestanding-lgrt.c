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

#if !defined(__GNUC__) && !defined(__clang__)
#error "freestanding-lgrt requires GCC or Clang"
#elif (defined(__clang__) && __clang_major__ < 6) \
   || (!defined(__clang__) \
    && (__GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ < 8)))
#error "freestanding-lgrt requires GCC 4.8 or later, or Clang 6 or later"
#endif

/*
 * Known issues of compilers, and what to do about them when building this:
 *
 * Clang 12 at -Oz miscompiles code that its machine outliner factors out for
 * ARM M-profile targets: build with -mno-outline there.
 *
 * On MIPS64, and on SPARC64 with Clang before 21, GCC and Clang pass __int128
 * arguments differently: build this with the same compiler as the code that
 * calls its 16-byte atomic routines.
 */

/*
 * Workaround: GCC 12, SuperH: it miscompiles conditional branches when
 * optimising, so the file is built without optimisation there.
 */
#if !defined(__clang__) && defined(__sh__) && __GNUC__ == 12
#pragma GCC optimize ("O0")
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#if defined(__ARM_EABI__)
#define LGRT_AAPCS __attribute__((__pcs__("aapcs")))
#else
#define LGRT_AAPCS
#endif

#if defined(__SIZEOF_INT128__)
#define LGRT_HAS_INT128 1
__extension__ typedef __int128 lgrt_i128;
__extension__ typedef unsigned __int128 lgrt_u128;
#else
#define LGRT_HAS_INT128 0
#endif

/*
 * AVR and MSP430 have no instruction that traps, and GCC calls abort there, so
 * these spin.
 *
 * Workaround: Clang before 10, RISC-V; Clang before 9, Hexagon; GCC, SuperH,
 * OpenRISC, MicroBlaze, Xtensa, and ARC; GCC 4.8, AArch64 and ARM:
 * __builtin_trap() becomes a call to abort or an instruction that does not
 * trap, so these execute one that traps instead, and spin in case it does not.
 */
#if defined(__AVR__) || defined(__MSP430__)
#define LGRT_TRAP() \
    do { \
        for (;;) { \
        } \
    } while (0)
#elif defined(__clang__)
#if defined(__riscv) && __clang_major__ < 10
#define LGRT_TRAP() \
    do { \
        __asm__ volatile ("unimp"); \
        for (;;) { \
        } \
    } while (0)
#elif defined(__hexagon__) && __clang_major__ < 9
/* A misaligned load from an unmapped address. */
#define LGRT_TRAP() \
    do { \
        __asm__ volatile ("r1:0 = memd(##0xbadc0fee)" : : : "r0", "r1"); \
        for (;;) { \
        } \
    } while (0)
#endif
#elif defined(__sh__)
#define LGRT_TRAP() \
    do { \
        __asm__ volatile (".word 0xfffd"); \
        for (;;) { \
        } \
    } while (0)
#elif defined(__or1k__)
/* A misaligned load from an unmapped address, as QEMU stops on l.trap. */
#define LGRT_TRAP() \
    do { \
        __asm__ volatile ("l.lwz r13, -0x1012(r0)" : : : "r13"); \
        for (;;) { \
        } \
    } while (0)
#elif defined(__MICROBLAZE__)
/*
 * A load from an unmapped address, as the illegal instruction exception is an
 * option of the cores.
 */
#define LGRT_TRAP() \
    do { \
        __asm__ volatile ("lwi r3, r0, -0x1012" : : : "r3"); \
        for (;;) { \
        } \
    } while (0)
#elif defined(__XTENSA__)
#define LGRT_TRAP() \
    do { \
        __asm__ volatile ("ill"); \
        for (;;) { \
        } \
    } while (0)
#elif defined(__ARC600__) || defined(__ARC601__)
#define LGRT_TRAP() \
    do { \
        __asm__ volatile ("swi"); \
        for (;;) { \
        } \
    } while (0)
#elif defined(__arc__)
#define LGRT_TRAP() \
    do { \
        __asm__ volatile ("trap_s 5"); \
        for (;;) { \
        } \
    } while (0)
#elif __GNUC__ == 4 && __GNUC_MINOR__ == 8
#if defined(__aarch64__)
#define LGRT_TRAP() \
    do { \
        __asm__ volatile ("brk #1000"); \
        for (;;) { \
        } \
    } while (0)
#elif defined(__arm__)
/* udf, encoded by hand as old assemblers lack the mnemonic. */
#if defined(__thumb__)
#define LGRT_TRAP() \
    do { \
        __asm__ volatile (".inst.n 0xdeff"); \
        for (;;) { \
        } \
    } while (0)
#else
#define LGRT_TRAP() \
    do { \
        __asm__ volatile (".inst 0xe7f000f0"); \
        for (;;) { \
        } \
    } while (0)
#endif
#endif
#endif

#if !defined(LGRT_TRAP)
#define LGRT_TRAP() \
    do { \
        __builtin_trap(); \
    } while (0)
#endif

/*
 * The compiler's bit-counting and byte-swapping builtins can compile into
 * calls to the routines below, so these must never use them.
 */

static inline uint32_t lgrt_clz32(uint32_t x) {
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
    /* The leading one, if any, is now in one of the top two bits. */
    return n + (uint32_t)(x < (uint32_t)0x80000000) + (uint32_t)(x == 0);
}

static inline uint32_t lgrt_clz64(uint64_t x) {
    uint32_t hi = (uint32_t)(x >> 32);
    uint32_t lo = (uint32_t)x;
    uint32_t z = (uint32_t)(hi == 0);

    /* Search lo if hi is zero, else hi. */
    return (z << 5) + lgrt_clz32(hi | (lo & ((uint32_t)0 - z)));
}

/* Those of AVR with special conventions are assembly, further on. */
#if !defined(__AVR__)
LGRT_AAPCS int __clzsi2(int32_t a);
LGRT_AAPCS int __clzsi2(int32_t a) {
    return (int)lgrt_clz32((uint32_t)a);
}
#endif

LGRT_AAPCS int __clzdi2(int64_t a);
LGRT_AAPCS int __clzdi2(int64_t a) {
    return (int)lgrt_clz64((uint64_t)a);
}

#if LGRT_HAS_INT128
LGRT_AAPCS int __clzti2(lgrt_i128 a);
LGRT_AAPCS int __clzti2(lgrt_i128 a) {
    lgrt_u128 x = (lgrt_u128)a;
    uint64_t hi = (uint64_t)(x >> 64);
    uint64_t lo = (uint64_t)x;
    uint64_t z = (uint64_t)(hi == 0);

    return (int)((z << 6) + lgrt_clz64(hi | (lo & ((uint64_t)0 - z))));
}
#endif

static inline uint32_t lgrt_ctz32(uint32_t x) {
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
    /* The lowest one, if any, is now in one of the bottom two bits. */
    return n + (uint32_t)((x & 1) == 0) + (uint32_t)(x == 0);
}

static inline uint32_t lgrt_ctz64(uint64_t x) {
    uint32_t lo = (uint32_t)x;
    uint32_t hi = (uint32_t)(x >> 32);
    uint32_t z = (uint32_t)(lo == 0);

    /* Search hi if lo is zero, else lo. */
    return (z << 5) + lgrt_ctz32(lo | (hi & ((uint32_t)0 - z)));
}

#if !defined(__AVR__)
LGRT_AAPCS int __ctzsi2(int32_t a);
LGRT_AAPCS int __ctzsi2(int32_t a) {
    return (int)lgrt_ctz32((uint32_t)a);
}
#endif

LGRT_AAPCS int __ctzdi2(int64_t a);
LGRT_AAPCS int __ctzdi2(int64_t a) {
    return (int)lgrt_ctz64((uint64_t)a);
}

#if LGRT_HAS_INT128
static inline uint32_t lgrt_ctz128(lgrt_u128 x) {
    uint64_t lo = (uint64_t)x;
    uint64_t hi = (uint64_t)(x >> 64);
    uint64_t z = (uint64_t)(lo == 0);

    return (uint32_t)(z << 6) + lgrt_ctz64(lo | (hi & ((uint64_t)0 - z)));
}

LGRT_AAPCS int __ctzti2(lgrt_i128 a);
LGRT_AAPCS int __ctzti2(lgrt_i128 a) {
    return (int)lgrt_ctz128((lgrt_u128)a);
}
#endif

#if !defined(__AVR__)
LGRT_AAPCS int __ffssi2(int32_t a);
LGRT_AAPCS int __ffssi2(int32_t a) {
    uint32_t x = (uint32_t)a;

    if (x == 0) {
        return 0;
    }
    return (int)(lgrt_ctz32(x) + 1);
}
#endif

LGRT_AAPCS int __ffsdi2(int64_t a);
LGRT_AAPCS int __ffsdi2(int64_t a) {
    uint64_t x = (uint64_t)a;

    if (x == 0) {
        return 0;
    }
    return (int)(lgrt_ctz64(x) + 1);
}

#if LGRT_HAS_INT128
LGRT_AAPCS int __ffsti2(lgrt_i128 a);
LGRT_AAPCS int __ffsti2(lgrt_i128 a) {
    lgrt_u128 x = (lgrt_u128)a;

    if (x == 0) {
        return 0;
    }
    return (int)(lgrt_ctz128(x) + 1);
}
#endif

/*
 * The redundant sign bits are the leading zeros, but for the sign bit itself,
 * of the value with its complement for a negative one.
 */

LGRT_AAPCS int __clrsbsi2(int32_t a);
LGRT_AAPCS int __clrsbsi2(int32_t a) {
    uint32_t x = (uint32_t)a;

    return (int)(lgrt_clz32(x ^ ((uint32_t)0 - (x >> 31))) - 1);
}

LGRT_AAPCS int __clrsbdi2(int64_t a);
LGRT_AAPCS int __clrsbdi2(int64_t a) {
    uint64_t x = (uint64_t)a;

    return (int)(lgrt_clz64(x ^ ((uint64_t)0 - (x >> 63))) - 1);
}

#if LGRT_HAS_INT128
LGRT_AAPCS int __clrsbti2(lgrt_i128 a);
LGRT_AAPCS int __clrsbti2(lgrt_i128 a) {
    lgrt_u128 x = (lgrt_u128)a;
    lgrt_u128 y = x ^ ((lgrt_u128)0 - (x >> 127));
    uint64_t hi = (uint64_t)(y >> 64);
    uint64_t lo = (uint64_t)y;
    uint64_t z = (uint64_t)(hi == 0);

    return (int)((z << 6) + lgrt_clz64(hi | (lo & ((uint64_t)0 - z))) - 1);
}
#endif

/*
 * No multiplications: they are library calls on targets without a multiplier.
 * Wider counts add up the per-nibble counts of their parts, which still fit.
 */

static inline uint32_t lgrt_nibble_popcounts32(uint32_t x) {
    x -= (x >> 1) & 0x55555555;
    return (x & 0x33333333) + ((x >> 2) & 0x33333333);
}

/* Each nibble of x must be at most 8. */
static inline uint32_t lgrt_sum_nibbles32(uint32_t x) {
    x = (x & 0x0f0f0f0f) + ((x >> 4) & 0x0f0f0f0f);
    x += x >> 8;
    x += x >> 16;
    return x & 0xff;
}

#if !defined(__AVR__)
LGRT_AAPCS int __popcountsi2(int32_t a);
LGRT_AAPCS int __popcountsi2(int32_t a) {
    return (int)lgrt_sum_nibbles32(lgrt_nibble_popcounts32((uint32_t)a));
}
#endif

#if LGRT_HAS_INT128

/*
 * Targets with 128-bit integers have 64-bit registers: count 64 bits at a
 * time.
 */

static inline uint64_t lgrt_nibble_popcounts64(uint64_t x) {
    x -= (x >> 1) & 0x5555555555555555;
    return (x & 0x3333333333333333) + ((x >> 2) & 0x3333333333333333);
}

/* Each nibble of x must be at most 8. */
static inline uint32_t lgrt_sum_nibbles64(uint64_t x) {
    x = (x & 0x0f0f0f0f0f0f0f0f) + ((x >> 4) & 0x0f0f0f0f0f0f0f0f);
    x += x >> 8;
    x += x >> 16;
    x += x >> 32;
    return (uint32_t)x & 0xff;
}

LGRT_AAPCS int __popcountdi2(int64_t a);
LGRT_AAPCS int __popcountdi2(int64_t a) {
    return (int)lgrt_sum_nibbles64(lgrt_nibble_popcounts64((uint64_t)a));
}

LGRT_AAPCS int __popcountti2(lgrt_i128 a);
LGRT_AAPCS int __popcountti2(lgrt_i128 a) {
    lgrt_u128 x = (lgrt_u128)a;
    uint64_t lo = lgrt_nibble_popcounts64((uint64_t)x);
    uint64_t hi = lgrt_nibble_popcounts64((uint64_t)(x >> 64));

    return (int)lgrt_sum_nibbles64(lo + hi);
}

#else

LGRT_AAPCS int __popcountdi2(int64_t a);
LGRT_AAPCS int __popcountdi2(int64_t a) {
    uint64_t x = (uint64_t)a;
    uint32_t lo = lgrt_nibble_popcounts32((uint32_t)x);
    uint32_t hi = lgrt_nibble_popcounts32((uint32_t)(x >> 32));

    return (int)lgrt_sum_nibbles32(lo + hi);
}

#endif

static inline uint32_t lgrt_parity32(uint32_t x) {
    x ^= x >> 16;
    x ^= x >> 8;
    x ^= x >> 4;
    x ^= x >> 2;
    x ^= x >> 1;
    return x & 1;
}

#if !defined(__AVR__)
LGRT_AAPCS int __paritysi2(int32_t a);
LGRT_AAPCS int __paritysi2(int32_t a) {
    return (int)lgrt_parity32((uint32_t)a);
}
#endif

LGRT_AAPCS int __paritydi2(int64_t a);
LGRT_AAPCS int __paritydi2(int64_t a) {
    uint64_t x = (uint64_t)a;

    return (int)lgrt_parity32((uint32_t)x ^ (uint32_t)(x >> 32));
}

#if LGRT_HAS_INT128
LGRT_AAPCS int __parityti2(lgrt_i128 a);
LGRT_AAPCS int __parityti2(lgrt_i128 a) {
    lgrt_u128 x = (lgrt_u128)a;
    uint64_t y = (uint64_t)x ^ (uint64_t)(x >> 64);

    return (int)lgrt_parity32((uint32_t)y ^ (uint32_t)(y >> 32));
}
#endif

#if !defined(__AVR__) || defined(__AVR_TINY__)

static inline uint32_t lgrt_bswap32(uint32_t x) {
    uint32_t y = x;

#if !defined(__clang__) && defined(__XTENSA__) && __GNUC__ >= 13
    /*
     * Workaround: GCC 13 to 16, Xtensa: optimising for size, it recognises the
     * swap and calls __bswapsi2 for it, which this is part of, so the swap
     * takes its bytes from two copies of the value, which it cannot tell are
     * equal.
     */
    __asm__ ("" : "+r"(y));
#endif
    x = ((x >> 8) & 0x00ff00ff) | ((y & 0x00ff00ff) << 8);
    return (x >> 16) | (x << 16);
}

#if !defined(__AVR__)
LGRT_AAPCS uint32_t __bswapsi2(uint32_t a);
LGRT_AAPCS uint32_t __bswapsi2(uint32_t a) {
    return lgrt_bswap32(a);
}
#endif

LGRT_AAPCS uint64_t __bswapdi2(uint64_t a);
LGRT_AAPCS uint64_t __bswapdi2(uint64_t a) {
    uint64_t lo = lgrt_bswap32((uint32_t)a);
    uint64_t hi = lgrt_bswap32((uint32_t)(a >> 32));

    return (lo << 32) | hi;
}
#endif

/*
 * Compilers may implement double-word comparisons by calling these routines,
 * so they compare single-word halves.
 */

#if !defined(__AVR__) || defined(__AVR_TINY__)
LGRT_AAPCS int __cmpdi2(int64_t a, int64_t b);
LGRT_AAPCS int __cmpdi2(int64_t a, int64_t b) {
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

#if LGRT_HAS_INT128
LGRT_AAPCS int __cmpti2(lgrt_i128 a, lgrt_i128 b);
LGRT_AAPCS int __cmpti2(lgrt_i128 a, lgrt_i128 b) {
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

LGRT_AAPCS int __ucmpdi2(uint64_t a, uint64_t b);
LGRT_AAPCS int __ucmpdi2(uint64_t a, uint64_t b) {
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

#if LGRT_HAS_INT128
LGRT_AAPCS int __ucmpti2(lgrt_u128 a, lgrt_u128 b);
LGRT_AAPCS int __ucmpti2(lgrt_u128 a, lgrt_u128 b) {
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

/* Negate as unsigned, as -a overflows for the most negative value. */

#if !defined(__AVR__) || defined(__AVR_TINY__)
LGRT_AAPCS int64_t __negdi2(int64_t a);
LGRT_AAPCS int64_t __negdi2(int64_t a) {
    return (int64_t)((uint64_t)0 - (uint64_t)a);
}
#endif

#if LGRT_HAS_INT128
LGRT_AAPCS lgrt_i128 __negti2(lgrt_i128 a);
LGRT_AAPCS lgrt_i128 __negti2(lgrt_i128 a) {
    return (lgrt_i128)((lgrt_u128)0 - (lgrt_u128)a);
}
#endif

/*
 * Variable double-word shifts can compile into calls to these routines, so
 * they shift single-word halves. No shift may reach the width of its operand:
 * the count is masked, and bits crossing between the halves move in two steps,
 * as the masked count may be zero. Signed right shifts are arithmetic with GCC
 * and Clang. The count is a byte on AVR, where what follows it is undefined.
 */

#if defined(__AVR__)
typedef uint8_t lgrt_shift_count;
#else
typedef int lgrt_shift_count;
#endif

/*
 * Those of AVR, but for its reduced cores, are assembly, further on. Those of
 * the run-time ABI of MSP430 are too, and GCC 4.9 calls these instead.
 */
#if defined(__AVR__) && !defined(__AVR_TINY__)
#define LGRT_GENERIC_SHIFTS_64 0
#else
#define LGRT_GENERIC_SHIFTS_64 1
#endif

/*
 * The reduced AVR cores, and GCC 4.9 for MSP430, call these for shifts by 32
 * too, so they split and join their values in memory there.
 */
#if defined(__AVR_TINY__) || defined(__MSP430__)
union lgrt_words_64 {
    uint64_t whole;
    uint32_t words[2];
};

#define LGRT_HIGH_32(x) (((union lgrt_words_64){ .whole = (x) }).words[1])
#define LGRT_JOIN_32(hi, lo) \
    (((union lgrt_words_64){ .words = { (lo), (hi) } }).whole)
#else
#define LGRT_HIGH_32(x) ((uint32_t)((x) >> 32))
#define LGRT_JOIN_32(hi, lo) (((uint64_t)(hi) << 32) | (lo))
#endif

#if LGRT_GENERIC_SHIFTS_64
LGRT_AAPCS int64_t __ashldi3(int64_t a, lgrt_shift_count b);
LGRT_AAPCS int64_t __ashldi3(int64_t a, lgrt_shift_count b) {
    uint64_t x = (uint64_t)a;
    uint32_t lo = (uint32_t)x;
    uint32_t hi = LGRT_HIGH_32(x);
    uint32_t n = (uint32_t)b;
    uint32_t s = n & 31;

    if ((n & 32) != 0) {
        hi = lo << s;
        lo = 0;
    } else {
        hi = (hi << s) | ((lo >> 1) >> (31 - s));
        lo <<= s;
    }
    return (int64_t)LGRT_JOIN_32(hi, lo);
}
#endif

#if LGRT_HAS_INT128
LGRT_AAPCS lgrt_i128 __ashlti3(lgrt_i128 a, int b);
LGRT_AAPCS lgrt_i128 __ashlti3(lgrt_i128 a, int b) {
    lgrt_u128 x = (lgrt_u128)a;
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
    return (lgrt_i128)(((lgrt_u128)hi << 64) | lo);
}
#endif

#if LGRT_GENERIC_SHIFTS_64
LGRT_AAPCS int64_t __ashrdi3(int64_t a, lgrt_shift_count b);
LGRT_AAPCS int64_t __ashrdi3(int64_t a, lgrt_shift_count b) {
    uint64_t x = (uint64_t)a;
    uint32_t lo = (uint32_t)x;
    uint32_t hi = LGRT_HIGH_32(x);
    uint32_t n = (uint32_t)b;
    uint32_t s = n & 31;

    if ((n & 32) != 0) {
        lo = (uint32_t)((int32_t)hi >> s);
        hi = (uint32_t)((int32_t)hi >> 31);
    } else {
        lo = (lo >> s) | ((hi << 1) << (31 - s));
        hi = (uint32_t)((int32_t)hi >> s);
    }
    return (int64_t)LGRT_JOIN_32(hi, lo);
}
#endif

#if LGRT_HAS_INT128
LGRT_AAPCS lgrt_i128 __ashrti3(lgrt_i128 a, int b);
LGRT_AAPCS lgrt_i128 __ashrti3(lgrt_i128 a, int b) {
    lgrt_u128 x = (lgrt_u128)a;
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
    return (lgrt_i128)(((lgrt_u128)hi << 64) | lo);
}
#endif

#if LGRT_GENERIC_SHIFTS_64
LGRT_AAPCS int64_t __lshrdi3(int64_t a, lgrt_shift_count b);
LGRT_AAPCS int64_t __lshrdi3(int64_t a, lgrt_shift_count b) {
    uint64_t x = (uint64_t)a;
    uint32_t lo = (uint32_t)x;
    uint32_t hi = LGRT_HIGH_32(x);
    uint32_t n = (uint32_t)b;
    uint32_t s = n & 31;

    if ((n & 32) != 0) {
        lo = hi >> s;
        hi = 0;
    } else {
        lo = (lo >> s) | ((hi << 1) << (31 - s));
        hi >>= s;
    }
    return (int64_t)LGRT_JOIN_32(hi, lo);
}
#endif

#if LGRT_HAS_INT128
LGRT_AAPCS lgrt_i128 __lshrti3(lgrt_i128 a, int b);
LGRT_AAPCS lgrt_i128 __lshrti3(lgrt_i128 a, int b) {
    lgrt_u128 x = (lgrt_u128)a;
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
    return (lgrt_i128)(((lgrt_u128)hi << 64) | lo);
}
#endif

#if __SIZEOF_POINTER__ == 8 || __SIZEOF_LONG__ == 8
#define LGRT_64BIT 1
#else
#define LGRT_64BIT 0
#endif

/*
 * Compilers call these where there is no multiply instruction, so they shift
 * and add, with the smaller operand as the multiplier to end the loop sooner.
 * On 64-bit targets, compilers call __muldi3 even for 32-bit multiplications.
 *
 * Workaround: GCC 14 to 16, ARC EM and HS without a multiplier, optimising for
 * size: it makes a multiplication by the bit out of its mask, and calls the
 * function that this is part of, for ever, so it is not told that the mask is
 * of one bit.
 */

#define LGRT_HIDE_BIT(bit) __asm__ ("" : "+r"(bit))

#if !defined(__AVR__) || defined(__AVR_TINY__)

static inline uint32_t lgrt_shift_add_mul32(uint32_t a, uint32_t b) {
    uint32_t small = a < b ? a : b;
    uint32_t big = a < b ? b : a;
    uint32_t r = 0;

    while (small != 0) {
        uint8_t bit = (uint8_t)(small & 1);

        LGRT_HIDE_BIT(bit);
        r += big & ((uint32_t)0 - (uint32_t)bit);
        big <<= 1;
        small >>= 1;
    }
    return r;
}

LGRT_AAPCS int32_t __mulsi3(int32_t a, int32_t b);
LGRT_AAPCS int32_t __mulsi3(int32_t a, int32_t b) {
    return (int32_t)lgrt_shift_add_mul32((uint32_t)a, (uint32_t)b);
}

#endif

#if LGRT_64BIT

static inline uint64_t lgrt_shift_add_mul64(uint64_t a, uint64_t b) {
    uint64_t small = a < b ? a : b;
    uint64_t big = a < b ? b : a;
    uint64_t r = 0;

    while (small != 0) {
        uint8_t bit = (uint8_t)(small & 1);

        LGRT_HIDE_BIT(bit);
        r += big & ((uint64_t)0 - (uint64_t)bit);
        big <<= 1;
        small >>= 1;
    }
    return r;
}

LGRT_AAPCS int64_t __muldi3(int64_t a, int64_t b);
LGRT_AAPCS int64_t __muldi3(int64_t a, int64_t b) {
    return (int64_t)lgrt_shift_add_mul64((uint64_t)a, (uint64_t)b);
}

#else

/*
 * A widening multiplication could compile into a call to __muldi3, so the
 * product comes from 16-bit pieces. Neither middle sum can overflow, as
 * (2^16 - 1)^2 + 2^16 - 1 < 2^32.
 */
static inline uint64_t lgrt_wide_mul32(uint32_t a, uint32_t b) {
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

LGRT_AAPCS int64_t __muldi3(int64_t a, int64_t b);
LGRT_AAPCS int64_t __muldi3(int64_t a, int64_t b) {
    uint64_t x = (uint64_t)a;
    uint64_t y = (uint64_t)b;
    uint32_t xl = (uint32_t)x;
    uint32_t yl = (uint32_t)y;
    uint32_t cross = (uint32_t)(x >> 32) * yl + xl * (uint32_t)(y >> 32);

    /* The cross terms only reach the high half. */
    return (int64_t)(lgrt_wide_mul32(xl, yl) + ((uint64_t)cross << 32));
}

#if defined(__XTENSA__)
/*
 * GCC for Xtensa calls this for the 64-bit products of 32-bit operands where
 * the core has no instruction for their high half.
 */
uint64_t __umulsidi3(uint32_t a, uint32_t b);
uint64_t __umulsidi3(uint32_t a, uint32_t b) {
    return lgrt_wide_mul32(a, b);
}
#endif

#endif

#if LGRT_HAS_INT128

/*
 * A 64 by 64 to 128-bit multiplication could compile into a call to __multi3,
 * so the product comes from 32-bit pieces. Neither middle sum can overflow, as
 * (2^32 - 1)^2 + 2^32 - 1 < 2^64.
 */
static inline lgrt_u128 lgrt_wide_mul64(uint64_t a, uint64_t b) {
    uint64_t a0 = a & 0xffffffff;
    uint64_t a1 = a >> 32;
    uint64_t b0 = b & 0xffffffff;
    uint64_t b1 = b >> 32;
    uint64_t p00 = a0 * b0;
    uint64_t m1 = a1 * b0 + (p00 >> 32);
    uint64_t m2 = a0 * b1 + (m1 & 0xffffffff);
    uint64_t hi = a1 * b1 + (m1 >> 32) + (m2 >> 32);
    uint64_t lo = (m2 << 32) | (p00 & 0xffffffff);

    return ((lgrt_u128)hi << 64) | lo;
}

LGRT_AAPCS lgrt_i128 __multi3(lgrt_i128 a, lgrt_i128 b);
LGRT_AAPCS lgrt_i128 __multi3(lgrt_i128 a, lgrt_i128 b) {
    lgrt_u128 x = (lgrt_u128)a;
    lgrt_u128 y = (lgrt_u128)b;
    uint64_t xl = (uint64_t)x;
    uint64_t yl = (uint64_t)y;
    uint64_t cross = (uint64_t)(x >> 64) * yl + xl * (uint64_t)(y >> 64);

    /* The cross terms only reach the high half. */
    return (lgrt_i128)(lgrt_wide_mul64(xl, yl) + ((lgrt_u128)cross << 64));
}

#endif

/*
 * With -ftrapv, signed arithmetic can compile into calls to the routines
 * below, so they, and everything they call, compute on unsigned values.
 *
 * Products of magnitudes overflow if both have a nonzero high half. Otherwise,
 * the smaller magnitude times each half of the larger one gives two partial
 * products, whose sum is exact unless the high one exceeds a half word or the
 * sum carries out. A negative product may have a magnitude one larger than a
 * positive one.
 */

#if LGRT_64BIT

/* On 64-bit targets, the product of the sign-extended operands is exact. */
static inline uint32_t lgrt_mulo32(int32_t a, int32_t b, bool *overflow) {
    uint64_t p = (uint64_t)a * (uint64_t)b;

    *overflow = ((p + (uint64_t)0x80000000) >> 32) != 0;
    return (uint32_t)p;
}

#else

static inline uint32_t lgrt_mulo32(int32_t a, int32_t b, bool *overflow) {
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

#endif

LGRT_AAPCS int32_t __mulosi4(int32_t a, int32_t b, int *overflow);
LGRT_AAPCS int32_t __mulosi4(int32_t a, int32_t b, int *overflow) {
    bool overflowed;
    uint32_t p = lgrt_mulo32(a, b, &overflowed);

    *overflow = overflowed;
    return (int32_t)p;
}

static inline uint64_t lgrt_mulo64(int64_t a, int64_t b, bool *overflow) {
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
    *overflow = (mid >> 32) != 0 || p < low
        || p > (uint64_t)0x7fffffffffffffff + neg;
    return (p ^ ((uint64_t)0 - neg)) + neg;
}

LGRT_AAPCS int64_t __mulodi4(int64_t a, int64_t b, int *overflow);
LGRT_AAPCS int64_t __mulodi4(int64_t a, int64_t b, int *overflow) {
    bool overflowed;
    uint64_t p = lgrt_mulo64(a, b, &overflowed);

    *overflow = overflowed;
    return (int64_t)p;
}

#if LGRT_HAS_INT128

static inline lgrt_u128 lgrt_mulo128(
    lgrt_i128 a, lgrt_i128 b, bool *overflow
) {
    lgrt_u128 x = (lgrt_u128)a;
    lgrt_u128 y = (lgrt_u128)b;
    lgrt_u128 xs = (lgrt_u128)0 - (x >> 127);
    lgrt_u128 ys = (lgrt_u128)0 - (y >> 127);
    lgrt_u128 xm = (x ^ xs) - xs;
    lgrt_u128 ym = (y ^ ys) - ys;
    lgrt_u128 neg = (x ^ y) >> 127;
    uint64_t small;
    lgrt_u128 big;
    lgrt_u128 mid;
    lgrt_u128 low;
    lgrt_u128 p;

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
    mid = (lgrt_u128)small * (uint64_t)(big >> 64);
    low = (lgrt_u128)small * (uint64_t)big;
    p = (mid << 64) + low;
    /*
     * Workaround: GCC 4.8, AArch64: it needs SIMD registers to load 128-bit
     * constants, so this uses none.
     */
    *overflow = (mid >> 64) != 0 || p < low
        || ((p >> 127) != 0 && (neg == 0 || (p << 1) != 0));
    return (p ^ ((lgrt_u128)0 - neg)) + neg;
}

LGRT_AAPCS lgrt_i128 __muloti4(lgrt_i128 a, lgrt_i128 b, int *overflow);
LGRT_AAPCS lgrt_i128 __muloti4(lgrt_i128 a, lgrt_i128 b, int *overflow) {
    bool overflowed;
    lgrt_u128 p = lgrt_mulo128(a, b, &overflowed);

    *overflow = overflowed;
    return (lgrt_i128)p;
}

#endif

LGRT_AAPCS int32_t __mulvsi3(int32_t a, int32_t b);
LGRT_AAPCS int32_t __mulvsi3(int32_t a, int32_t b) {
    bool overflow;
    uint32_t p = lgrt_mulo32(a, b, &overflow);

    if (overflow) {
        LGRT_TRAP();
    }
    return (int32_t)p;
}

LGRT_AAPCS int64_t __mulvdi3(int64_t a, int64_t b);
LGRT_AAPCS int64_t __mulvdi3(int64_t a, int64_t b) {
    bool overflow;
    uint64_t p = lgrt_mulo64(a, b, &overflow);

    if (overflow) {
        LGRT_TRAP();
    }
    return (int64_t)p;
}

#if LGRT_HAS_INT128
LGRT_AAPCS lgrt_i128 __mulvti3(lgrt_i128 a, lgrt_i128 b);
LGRT_AAPCS lgrt_i128 __mulvti3(lgrt_i128 a, lgrt_i128 b) {
    bool overflow;
    lgrt_u128 p = lgrt_mulo128(a, b, &overflow);

    if (overflow) {
        LGRT_TRAP();
    }
    return (lgrt_i128)p;
}
#endif

/*
 * a + b overflows exactly when the sum's sign differs from those of a and b.
 */

LGRT_AAPCS int32_t __addvsi3(int32_t a, int32_t b);
LGRT_AAPCS int32_t __addvsi3(int32_t a, int32_t b) {
    uint32_t x = (uint32_t)a;
    uint32_t y = (uint32_t)b;
    uint32_t s = x + y;

    if ((((s ^ x) & (s ^ y)) >> 31) != 0) {
        LGRT_TRAP();
    }
    return (int32_t)s;
}

LGRT_AAPCS int64_t __addvdi3(int64_t a, int64_t b);
LGRT_AAPCS int64_t __addvdi3(int64_t a, int64_t b) {
    uint64_t x = (uint64_t)a;
    uint64_t y = (uint64_t)b;
    uint64_t s = x + y;

    if ((((s ^ x) & (s ^ y)) >> 63) != 0) {
        LGRT_TRAP();
    }
    return (int64_t)s;
}

#if LGRT_HAS_INT128
LGRT_AAPCS lgrt_i128 __addvti3(lgrt_i128 a, lgrt_i128 b);
LGRT_AAPCS lgrt_i128 __addvti3(lgrt_i128 a, lgrt_i128 b) {
    lgrt_u128 x = (lgrt_u128)a;
    lgrt_u128 y = (lgrt_u128)b;
    lgrt_u128 s = x + y;

    if ((((s ^ x) & (s ^ y)) >> 127) != 0) {
        LGRT_TRAP();
    }
    return (lgrt_i128)s;
}
#endif

/*
 * a - b overflows exactly when a and b differ in sign and the difference's
 * sign differs from that of a.
 */

LGRT_AAPCS int32_t __subvsi3(int32_t a, int32_t b);
LGRT_AAPCS int32_t __subvsi3(int32_t a, int32_t b) {
    uint32_t x = (uint32_t)a;
    uint32_t y = (uint32_t)b;
    uint32_t d = x - y;

    if ((((x ^ y) & (x ^ d)) >> 31) != 0) {
        LGRT_TRAP();
    }
    return (int32_t)d;
}

LGRT_AAPCS int64_t __subvdi3(int64_t a, int64_t b);
LGRT_AAPCS int64_t __subvdi3(int64_t a, int64_t b) {
    uint64_t x = (uint64_t)a;
    uint64_t y = (uint64_t)b;
    uint64_t d = x - y;

    if ((((x ^ y) & (x ^ d)) >> 63) != 0) {
        LGRT_TRAP();
    }
    return (int64_t)d;
}

#if LGRT_HAS_INT128
LGRT_AAPCS lgrt_i128 __subvti3(lgrt_i128 a, lgrt_i128 b);
LGRT_AAPCS lgrt_i128 __subvti3(lgrt_i128 a, lgrt_i128 b) {
    lgrt_u128 x = (lgrt_u128)a;
    lgrt_u128 y = (lgrt_u128)b;
    lgrt_u128 d = x - y;

    if ((((x ^ y) & (x ^ d)) >> 127) != 0) {
        LGRT_TRAP();
    }
    return (lgrt_i128)d;
}
#endif

/*
 * Without a divide instruction, compilers turn divisions into calls to the
 * routines below, at the operands' width but at least 64 bits on 64-bit
 * targets, or into calls to target-specific helpers that this file does not
 * define. So the routines below use / and % only on narrower operands, and
 * only where the target has a divide instruction for those, calling their own
 * long division elsewhere. The 32-bit routines never use them, as narrower
 * operands are promoted to int, and neither do the 64-bit ones on 64-bit
 * targets.
 *
 * LGRT_HW_DIV32 tells whether the target has a divide instruction for 32-bit
 * operands, and LGRT_HW_DIV64 whether it has one for 64-bit operands held in
 * single registers.
 */

#if defined(__i386__) || defined(__x86_64__) || defined(__aarch64__) \
 || (defined(__arm__) && defined(__ARM_FEATURE_IDIV)) || defined(__mips__) \
 || defined(__powerpc__) || defined(__s390__) || defined(__loongarch__) \
 || (defined(__riscv) && defined(__riscv_div)) || defined(__sparc_v8__) \
 || defined(__sparcv8) || defined(__sparc_v9__) || defined(__sparcv9) \
 || defined(__mc68020__) || defined(__mc68030__) || defined(__mc68040__) \
 || defined(__mc68060__) || defined(__mcfhwdiv__) || defined(__ARC_DIVREM__)
#define LGRT_HW_DIV32 1
#else
#define LGRT_HW_DIV32 0
#endif

#if defined(__x86_64__) || defined(__aarch64__) \
 || (defined(__mips64) && LGRT_64BIT) || defined(__powerpc64__) \
 || defined(__s390x__) || defined(__loongarch64) \
 || (defined(__riscv) && defined(__riscv_div) && __riscv_xlen == 64) \
 || (defined(__sparc__) && defined(__arch64__))
#define LGRT_HW_DIV64 1
#else
#define LGRT_HW_DIV64 0
#endif

/*
 * Unlike the bit-counting routines, the division routines can use the clz
 * builtins. x | 1 has the leading zeros of x, except for zero, for which the
 * builtins are undefined.
 */

static inline uint32_t lgrt_div_clz32(uint32_t x) {
#if __SIZEOF_INT__ < 4
    return (uint32_t)__builtin_clzl((unsigned long)(x | 1));
#else
    return (uint32_t)__builtin_clz((unsigned int)(x | 1));
#endif
}

static inline uint32_t lgrt_div_clz64(uint64_t x) {
    return (uint32_t)__builtin_clzll((unsigned long long)(x | 1));
}

/*
 * Binary long division over the bit positions where the quotient can have set
 * bits. Aligning the divisor's top bit with the dividend's keeps the remainder
 * below twice the divisor, so each step subtracts at most once.
 */
static inline uint32_t lgrt_udivmod32(uint32_t a, uint32_t b, uint32_t *rem) {
    uint32_t q = 0;
    uint32_t n;
    uint32_t d;

    if (b > a) {
        *rem = a;
        return 0;
    }
    n = lgrt_div_clz32(b) - lgrt_div_clz32(a);
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
LGRT_AAPCS uint32_t __udivmodsi4(uint32_t a, uint32_t b, uint32_t *rem);
LGRT_AAPCS uint32_t __udivmodsi4(uint32_t a, uint32_t b, uint32_t *rem) {
    uint32_t r;
    uint32_t q = lgrt_udivmod32(a, b, &r);

    if (rem != NULL) {
        *rem = r;
    }
    return q;
}
#endif

#if !LGRT_64BIT
static inline uint32_t lgrt_hw_udivmod32(
    uint32_t a, uint32_t b, uint32_t *rem
) {
#if LGRT_HW_DIV32
    *rem = a % b;
    return a / b;
#else
    return lgrt_udivmod32(a, b, rem);
#endif
}
#endif

static inline uint64_t lgrt_udivmod64(uint64_t a, uint64_t b, uint64_t *rem) {
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
        uint32_t q32 = lgrt_hw_udivmod32((uint32_t)a, (uint32_t)b, &r);

        *rem = r;
        return q32;
    }
#endif
    n = lgrt_div_clz64(b) - lgrt_div_clz64(a);
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

LGRT_AAPCS uint64_t __udivmoddi4(uint64_t a, uint64_t b, uint64_t *rem);
LGRT_AAPCS uint64_t __udivmoddi4(uint64_t a, uint64_t b, uint64_t *rem) {
    uint64_t r;
    uint64_t q = lgrt_udivmod64(a, b, &r);

    if (rem != NULL) {
        *rem = r;
    }
    return q;
}

#if LGRT_HAS_INT128

static inline uint64_t lgrt_hw_udivmod64(
    uint64_t a, uint64_t b, uint64_t *rem
) {
#if LGRT_HW_DIV64
    *rem = a % b;
    return a / b;
#else
    return lgrt_udivmod64(a, b, rem);
#endif
}

#if defined(__x86_64__)

/*
 * Divides hi:lo by v. As hi < v, the quotient fits in 64 bits, so divq cannot
 * fault.
 */
static inline uint64_t lgrt_udiv128by64(
    uint64_t hi, uint64_t lo, uint64_t v, uint64_t *rem
) {
    uint64_t q;
    uint64_t r;

    __asm__ (
        "{divq %4|div %4}"
        : "=a"(q), "=d"(r)
        : "0"(lo), "1"(hi), "r"(v)
        : "cc"
    );
    *rem = r;
    return q;
}

#else

/*
 * A step of Knuth's Algorithm D with 32-bit digits: divides u:next by v, where
 * v has its top bit set and u < v, so that the quotient is a single digit. Its
 * estimate exceeds it by at most two, and as v has two digits, comparing with
 * the low one tells exactly whether the estimate is too large.
 */
static inline uint32_t lgrt_udiv96by64(
    uint64_t u, uint32_t next, uint64_t v, uint64_t *rem
) {
    uint64_t vh = v >> 32;
    uint64_t vl = v & 0xffffffff;
    uint64_t r;
    uint64_t q = lgrt_hw_udivmod64(u, vh, &r);

    if ((q >> 32) != 0 || q * vl > ((r << 32) | next)) {
        q--;
        r += vh;
        if ((r >> 32) == 0
         && ((q >> 32) != 0 || q * vl > ((r << 32) | next))) {
            q--;
        }
    }
    *rem = (u << 32) + next - q * v;
    return (uint32_t)q;
}

/* Divides hi:lo by v, where hi < v, so that the quotient fits in 64 bits. */
static inline uint64_t lgrt_udiv128by64(
    uint64_t hi, uint64_t lo, uint64_t v, uint64_t *rem
) {
    uint32_t s = lgrt_div_clz64(v);
    uint64_t r;
    uint32_t q1;
    uint32_t q0;

    /* Normalise v. s may be zero, so bits move from lo to hi in two shifts. */
    v <<= s;
    hi = (hi << s) | ((lo >> 1) >> (63 - s));
    lo <<= s;
    q1 = lgrt_udiv96by64(hi, (uint32_t)(lo >> 32), v, &r);
    q0 = lgrt_udiv96by64(r, (uint32_t)lo, v, &r);
    *rem = r >> s;
    return ((uint64_t)q1 << 32) | q0;
}

#endif

static inline lgrt_u128 lgrt_udivmod128(
    lgrt_u128 a, lgrt_u128 b, lgrt_u128 *rem
) {
    uint64_t ah = (uint64_t)(a >> 64);
    uint64_t al = (uint64_t)a;
    uint64_t bh = (uint64_t)(b >> 64);
    uint64_t bl = (uint64_t)b;
    uint64_t qh = 0;
    uint64_t q;
    uint64_t r;
    lgrt_u128 d;
    uint32_t n;

    if (b > a) {
        *rem = a;
        return 0;
    }
    if (ah == 0) {
        q = lgrt_hw_udivmod64(al, bl, &r);
        *rem = r;
        return q;
    }
    if (bh == 0) {
        if (ah >= bl) {
            qh = lgrt_hw_udivmod64(ah, bl, &ah);
        }
        q = lgrt_udiv128by64(ah, al, bl, &r);
        *rem = r;
        return ((lgrt_u128)qh << 64) | q;
    }
    /* As b does not fit in 64 bits, the quotient does. */
    n = lgrt_div_clz64(bh) - lgrt_div_clz64(ah);
    d = b << n;
    q = 0;
    do {
        uint64_t c = (uint64_t)(a >= d);

        a -= d & ((lgrt_u128)0 - c);
        q = (q << 1) | c;
        d >>= 1;
    } while (n-- != 0);
    *rem = a;
    return q;
}

LGRT_AAPCS lgrt_u128 __udivmodti4(lgrt_u128 a, lgrt_u128 b, lgrt_u128 *rem);
LGRT_AAPCS lgrt_u128 __udivmodti4(lgrt_u128 a, lgrt_u128 b, lgrt_u128 *rem) {
    lgrt_u128 r;
    lgrt_u128 q = lgrt_udivmod128(a, b, &r);

    if (rem != NULL) {
        *rem = r;
    }
    return q;
}

#endif

/*
 * SuperH's __udivsi3 is assembly with a special convention, defined further
 * on.
 */
#if !defined(__sh__)
LGRT_AAPCS uint32_t __udivsi3(uint32_t a, uint32_t b);
LGRT_AAPCS uint32_t __udivsi3(uint32_t a, uint32_t b) {
    uint32_t r;

    return lgrt_udivmod32(a, b, &r);
}
#endif

LGRT_AAPCS uint64_t __udivdi3(uint64_t a, uint64_t b);
LGRT_AAPCS uint64_t __udivdi3(uint64_t a, uint64_t b) {
    uint64_t r;

    return lgrt_udivmod64(a, b, &r);
}

#if LGRT_HAS_INT128
LGRT_AAPCS lgrt_u128 __udivti3(lgrt_u128 a, lgrt_u128 b);
LGRT_AAPCS lgrt_u128 __udivti3(lgrt_u128 a, lgrt_u128 b) {
    lgrt_u128 r;

    return lgrt_udivmod128(a, b, &r);
}
#endif

LGRT_AAPCS uint32_t __umodsi3(uint32_t a, uint32_t b);
LGRT_AAPCS uint32_t __umodsi3(uint32_t a, uint32_t b) {
    uint32_t r;

    lgrt_udivmod32(a, b, &r);
    return r;
}

LGRT_AAPCS uint64_t __umoddi3(uint64_t a, uint64_t b);
LGRT_AAPCS uint64_t __umoddi3(uint64_t a, uint64_t b) {
    uint64_t r;

    lgrt_udivmod64(a, b, &r);
    return r;
}

#if LGRT_HAS_INT128
LGRT_AAPCS lgrt_u128 __umodti3(lgrt_u128 a, lgrt_u128 b);
LGRT_AAPCS lgrt_u128 __umodti3(lgrt_u128 a, lgrt_u128 b) {
    lgrt_u128 r;

    lgrt_udivmod128(a, b, &r);
    return r;
}
#endif

/*
 * Signed division divides the magnitudes as unsigned values, then negates the
 * quotient if the signs differ, and the remainder if a is negative. Unsigned
 * arithmetic lets the most negative value divided by -1 wrap, and cannot trap
 * with -ftrapv.
 */

static inline uint32_t lgrt_divmod32(int32_t a, int32_t b, uint32_t *rem) {
    uint32_t x = (uint32_t)a;
    uint32_t y = (uint32_t)b;
    uint32_t xs = (uint32_t)0 - (x >> 31);
    uint32_t ys = (uint32_t)0 - (y >> 31);
    uint32_t qs = xs ^ ys;
    uint32_t r;
    uint32_t q = lgrt_udivmod32((x ^ xs) - xs, (y ^ ys) - ys, &r);

    *rem = (r ^ xs) - xs;
    return (q ^ qs) - qs;
}

LGRT_AAPCS int32_t __divsi3(int32_t a, int32_t b);
LGRT_AAPCS int32_t __divsi3(int32_t a, int32_t b) {
    uint32_t r;

    return (int32_t)lgrt_divmod32(a, b, &r);
}

static inline uint64_t lgrt_divmod64(int64_t a, int64_t b, uint64_t *rem) {
    uint64_t x = (uint64_t)a;
    uint64_t y = (uint64_t)b;
    uint64_t xs = (uint64_t)0 - (x >> 63);
    uint64_t ys = (uint64_t)0 - (y >> 63);
    uint64_t qs = xs ^ ys;
    uint64_t r;
    uint64_t q = lgrt_udivmod64((x ^ xs) - xs, (y ^ ys) - ys, &r);

    *rem = (r ^ xs) - xs;
    return (q ^ qs) - qs;
}

LGRT_AAPCS int64_t __divdi3(int64_t a, int64_t b);
LGRT_AAPCS int64_t __divdi3(int64_t a, int64_t b) {
    uint64_t r;

    return (int64_t)lgrt_divmod64(a, b, &r);
}

#if LGRT_HAS_INT128

static inline lgrt_u128 lgrt_divmod128(
    lgrt_i128 a, lgrt_i128 b, lgrt_u128 *rem
) {
    lgrt_u128 x = (lgrt_u128)a;
    lgrt_u128 y = (lgrt_u128)b;
    lgrt_u128 xs = (lgrt_u128)0 - (x >> 127);
    lgrt_u128 ys = (lgrt_u128)0 - (y >> 127);
    lgrt_u128 qs = xs ^ ys;
    lgrt_u128 r;
    lgrt_u128 q = lgrt_udivmod128((x ^ xs) - xs, (y ^ ys) - ys, &r);

    *rem = (r ^ xs) - xs;
    return (q ^ qs) - qs;
}

LGRT_AAPCS lgrt_i128 __divti3(lgrt_i128 a, lgrt_i128 b);
LGRT_AAPCS lgrt_i128 __divti3(lgrt_i128 a, lgrt_i128 b) {
    lgrt_u128 r;

    return (lgrt_i128)lgrt_divmod128(a, b, &r);
}

#endif

LGRT_AAPCS int32_t __modsi3(int32_t a, int32_t b);
LGRT_AAPCS int32_t __modsi3(int32_t a, int32_t b) {
    uint32_t r;

    lgrt_divmod32(a, b, &r);
    return (int32_t)r;
}

LGRT_AAPCS int64_t __moddi3(int64_t a, int64_t b);
LGRT_AAPCS int64_t __moddi3(int64_t a, int64_t b) {
    uint64_t r;

    lgrt_divmod64(a, b, &r);
    return (int64_t)r;
}

#if LGRT_HAS_INT128
LGRT_AAPCS lgrt_i128 __modti3(lgrt_i128 a, lgrt_i128 b);
LGRT_AAPCS lgrt_i128 __modti3(lgrt_i128 a, lgrt_i128 b) {
    lgrt_u128 r;

    lgrt_divmod128(a, b, &r);
    return (lgrt_i128)r;
}
#endif

#if !defined(__AVR__)
LGRT_AAPCS int32_t __divmodsi4(int32_t a, int32_t b, int32_t *rem);
LGRT_AAPCS int32_t __divmodsi4(int32_t a, int32_t b, int32_t *rem) {
    uint32_t r;
    uint32_t q = lgrt_divmod32(a, b, &r);

    if (rem != NULL) {
        *rem = (int32_t)r;
    }
    return (int32_t)q;
}
#endif

LGRT_AAPCS int64_t __divmoddi4(int64_t a, int64_t b, int64_t *rem);
LGRT_AAPCS int64_t __divmoddi4(int64_t a, int64_t b, int64_t *rem) {
    uint64_t r;
    uint64_t q = lgrt_divmod64(a, b, &r);

    if (rem != NULL) {
        *rem = (int64_t)r;
    }
    return (int64_t)q;
}

#if LGRT_HAS_INT128
LGRT_AAPCS lgrt_i128 __divmodti4(lgrt_i128 a, lgrt_i128 b, lgrt_i128 *rem);
LGRT_AAPCS lgrt_i128 __divmodti4(lgrt_i128 a, lgrt_i128 b, lgrt_i128 *rem) {
    lgrt_u128 r;
    lgrt_u128 q = lgrt_divmod128(a, b, &r);

    if (rem != NULL) {
        *rem = (lgrt_i128)r;
    }
    return (lgrt_i128)q;
}
#endif

/*
 * With -ftrapv, signed arithmetic compiles into calls to overflow-checking
 * routines such as these, so they compute on unsigned values.
 */

LGRT_AAPCS int32_t __negvsi2(int32_t a);
LGRT_AAPCS int32_t __negvsi2(int32_t a) {
    uint32_t x = (uint32_t)a;

    if (x == (uint32_t)0x80000000) {
        LGRT_TRAP();
    }
    return (int32_t)((uint32_t)0 - x);
}

LGRT_AAPCS int64_t __negvdi2(int64_t a);
LGRT_AAPCS int64_t __negvdi2(int64_t a) {
    uint64_t x = (uint64_t)a;

    if (x == (uint64_t)0x8000000000000000) {
        LGRT_TRAP();
    }
    return (int64_t)((uint64_t)0 - x);
}

#if LGRT_HAS_INT128
LGRT_AAPCS lgrt_i128 __negvti2(lgrt_i128 a);
LGRT_AAPCS lgrt_i128 __negvti2(lgrt_i128 a) {
    lgrt_u128 x = (lgrt_u128)a;

    /*
     * Workaround: GCC 4.8, AArch64: it needs SIMD registers to load 128-bit
     * constants, so this uses none.
     */
    if ((x >> 127) != 0 && (x << 1) == 0) {
        LGRT_TRAP();
    }
    return (lgrt_i128)((lgrt_u128)0 - x);
}
#endif

/* Only the most negative value has a magnitude with the top bit set. */

LGRT_AAPCS int32_t __absvsi2(int32_t a);
LGRT_AAPCS int32_t __absvsi2(int32_t a) {
    uint32_t x = (uint32_t)a;
    uint32_t s = (uint32_t)0 - (x >> 31);
    uint32_t m = (x ^ s) - s;

    if ((m >> 31) != 0) {
        LGRT_TRAP();
    }
    return (int32_t)m;
}

LGRT_AAPCS int64_t __absvdi2(int64_t a);
LGRT_AAPCS int64_t __absvdi2(int64_t a) {
    uint64_t x = (uint64_t)a;
    uint64_t s = (uint64_t)0 - (x >> 63);
    uint64_t m = (x ^ s) - s;

    if ((m >> 63) != 0) {
        LGRT_TRAP();
    }
    return (int64_t)m;
}

#if LGRT_HAS_INT128
LGRT_AAPCS lgrt_i128 __absvti2(lgrt_i128 a);
LGRT_AAPCS lgrt_i128 __absvti2(lgrt_i128 a) {
    lgrt_u128 x = (lgrt_u128)a;
    lgrt_u128 s = (lgrt_u128)0 - (x >> 127);
    lgrt_u128 m = (x ^ s) - s;

    if ((m >> 127) != 0) {
        LGRT_TRAP();
    }
    return (lgrt_i128)m;
}
#endif

#if __SIZEOF_INT__ == 2

/*
 * On targets whose int has 16 bits, -ftrapv checks int arithmetic with these,
 * so they compute on 16-bit unsigned values, or on 32-bit ones for products,
 * which fit.
 */

int16_t __addvhi3(int16_t a, int16_t b);
int16_t __addvhi3(int16_t a, int16_t b) {
    uint16_t x = (uint16_t)a;
    uint16_t y = (uint16_t)b;
    uint16_t s = x + y;

    if ((((s ^ x) & (s ^ y)) >> 15) != 0) {
        LGRT_TRAP();
    }
    return (int16_t)s;
}

int16_t __subvhi3(int16_t a, int16_t b);
int16_t __subvhi3(int16_t a, int16_t b) {
    uint16_t x = (uint16_t)a;
    uint16_t y = (uint16_t)b;
    uint16_t d = x - y;

    if ((((x ^ y) & (x ^ d)) >> 15) != 0) {
        LGRT_TRAP();
    }
    return (int16_t)d;
}

int16_t __mulvhi3(int16_t a, int16_t b);
int16_t __mulvhi3(int16_t a, int16_t b) {
    bool overflow;
    uint32_t p = lgrt_mulo32(a, b, &overflow);

    if (((p + (uint32_t)0x8000) >> 16) != 0) {
        LGRT_TRAP();
    }
    return (int16_t)p;
}

int16_t __negvhi2(int16_t a);
int16_t __negvhi2(int16_t a) {
    uint16_t x = (uint16_t)a;

    if (x == (uint16_t)0x8000) {
        LGRT_TRAP();
    }
    return (int16_t)((uint16_t)0 - x);
}

int16_t __absvhi2(int16_t a);
int16_t __absvhi2(int16_t a) {
    uint16_t x = (uint16_t)a;
    uint16_t s = (uint16_t)0 - (x >> 15);
    uint16_t m = (x ^ s) - s;

    if ((m >> 15) != 0) {
        LGRT_TRAP();
    }
    return (int16_t)m;
}

int __clrsbhi2(int16_t a);
int __clrsbhi2(int16_t a) {
    uint16_t x = (uint16_t)a;
    uint16_t y = x ^ ((uint16_t)0 - (x >> 15));

    return (int)(lgrt_clz32(y) - 17);
}

/* Those of AVR have special conventions, and are assembly, further on. */
#if !defined(__AVR__)

/* GCC 4.9 for MSP430 calls these for switches. */
int __cmpsi2(int32_t a, int32_t b);
int __cmpsi2(int32_t a, int32_t b) {
    return a < b ? 0 : (a > b ? 2 : 1);
}

int __ucmpsi2(uint32_t a, uint32_t b);
int __ucmpsi2(uint32_t a, uint32_t b) {
    return a < b ? 0 : (a > b ? 2 : 1);
}

int __clzhi2(uint16_t a);
int __clzhi2(uint16_t a) {
    return (int)(lgrt_clz32(a) - 16);
}

/* Bit 16 stops the count at the width for zero. */
int __ctzhi2(uint16_t a);
int __ctzhi2(uint16_t a) {
    return (int)lgrt_ctz32((uint32_t)a | 0x10000);
}

int __ffshi2(uint16_t a);
int __ffshi2(uint16_t a) {
    return a == 0 ? 0 : (int)(lgrt_ctz32(a) + 1);
}

int __popcounthi2(uint16_t a);
int __popcounthi2(uint16_t a) {
    return (int)lgrt_sum_nibbles32(lgrt_nibble_popcounts32(a));
}

int __parityhi2(uint16_t a);
int __parityhi2(uint16_t a) {
    return (int)lgrt_parity32(a);
}

int16_t __mulhi3(int16_t a, int16_t b);
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

/* The bit that shifting the remainder loses makes it exceed the divisor. */
static inline uint16_t lgrt_udivmod16(uint16_t a, uint16_t b, uint16_t *rem) {
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

static inline uint16_t lgrt_divmod16(int16_t a, int16_t b, uint16_t *rem) {
    uint16_t x = (uint16_t)a;
    uint16_t y = (uint16_t)b;
    uint16_t xs = (uint16_t)0 - (x >> 15);
    uint16_t ys = (uint16_t)0 - (y >> 15);
    uint16_t qs = xs ^ ys;
    uint16_t r;
    uint16_t q = lgrt_udivmod16((x ^ xs) - xs, (y ^ ys) - ys, &r);

    *rem = (r ^ xs) - xs;
    return (q ^ qs) - qs;
}

uint16_t __udivhi3(uint16_t a, uint16_t b);
uint16_t __udivhi3(uint16_t a, uint16_t b) {
    uint16_t r;

    return lgrt_udivmod16(a, b, &r);
}

uint16_t __umodhi3(uint16_t a, uint16_t b);
uint16_t __umodhi3(uint16_t a, uint16_t b) {
    uint16_t r;

    lgrt_udivmod16(a, b, &r);
    return r;
}

int16_t __divhi3(int16_t a, int16_t b);
int16_t __divhi3(int16_t a, int16_t b) {
    uint16_t r;

    return (int16_t)lgrt_divmod16(a, b, &r);
}

int16_t __modhi3(int16_t a, int16_t b);
int16_t __modhi3(int16_t a, int16_t b) {
    uint16_t r;

    lgrt_divmod16(a, b, &r);
    return (int16_t)r;
}

#endif

#endif

#if defined(__ARM_EABI__)

LGRT_AAPCS uint32_t __aeabi_uidiv(uint32_t a, uint32_t b);
LGRT_AAPCS uint32_t __aeabi_uidiv(
    uint32_t a, uint32_t b
) __attribute__((__alias__("__udivsi3")));

LGRT_AAPCS int32_t __aeabi_idiv(int32_t a, int32_t b);
LGRT_AAPCS int32_t __aeabi_idiv(
    int32_t a, int32_t b
) __attribute__((__alias__("__divsi3")));

/*
 * These return the quotient in r0 and the remainder in r1, which hold the low
 * and high halves of a 64-bit integer on little-endian targets, and the high
 * and low halves on big-endian ones.
 */

static inline uint64_t lgrt_aeabi_pair(uint32_t r0, uint32_t r1) {
#if defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
    return ((uint64_t)r0 << 32) | r1;
#else
    return ((uint64_t)r1 << 32) | r0;
#endif
}

LGRT_AAPCS uint64_t __aeabi_uidivmod(unsigned int a, unsigned int b);
LGRT_AAPCS uint64_t __aeabi_uidivmod(unsigned int a, unsigned int b) {
    uint32_t r;
    uint32_t q = lgrt_udivmod32(a, b, &r);

    return lgrt_aeabi_pair(q, r);
}

LGRT_AAPCS uint64_t __aeabi_idivmod(int a, int b);
LGRT_AAPCS uint64_t __aeabi_idivmod(int a, int b) {
    uint32_t r;
    uint32_t q = lgrt_divmod32(a, b, &r);

    return lgrt_aeabi_pair(q, r);
}

#endif

#if defined(__ARM_EABI__)

/*
 * The assembly routines below are naked functions, so that the compiler emits
 * their symbols. GCC assembles inline assembly in divided syntax and, in older
 * versions, its own ARM and Thumb-1 code too, so the assembly switches to
 * unified syntax and, with GCC outside Thumb-2, back.
 */

#if defined(__clang__) || defined(__thumb2__)
#define LGRT_ASM_END ""
#else
#define LGRT_ASM_END ".syntax divided\n"
#endif

#if defined(__ARM_FEATURE_BTI_DEFAULT)
#define LGRT_ASM_BTI "bti\n"
#else
#define LGRT_ASM_BTI ""
#endif

/* On ARMv4T, popping into pc does not switch between ARM and Thumb state. */
#if defined(__ARM_ARCH_4T__) || (defined(__ARM_ARCH) && __ARM_ARCH < 5)
#define LGRT_ARM_V4T 1
#else
#define LGRT_ARM_V4T 0
#endif

#if defined(__thumb__) && !defined(__thumb2__)
#define LGRT_THUMB1 1
#else
#define LGRT_THUMB1 0
#endif

/*
 * These return the quotient in r0 and r1 and the remainder in r2 and r3, which
 * C cannot do. The dividend and divisor stay in r0 to r3 for the call, and the
 * third argument, on the stack, is the address of a slot for the remainder.
 * From sp at the call, the frame holds that address, padding, the slot, and
 * the saved registers. Popping the slot loads it in address order, which is
 * how a register pair holds a 64-bit value on either endianness.
 */

#if defined(__ARM_FEATURE_PAC_DEFAULT)
/* r12 holds the authentication code of lr, so it is saved with lr. */
#if defined(__ARM_FEATURE_BTI_DEFAULT)
#define LGRT_DIVMOD_ENTRY \
    "pacbti r12, lr, sp\n" \
    "push {r12, lr}\n"
#else
#define LGRT_DIVMOD_ENTRY \
    "pac r12, lr, sp\n" \
    "push {r12, lr}\n"
#endif
#define LGRT_DIVMOD_TEMP "r12"
#define LGRT_DIVMOD_EXIT \
    "pop {r2, r3, r12, lr}\n" \
    "aut r12, lr, sp\n" \
    "bx lr\n"
#else
#define LGRT_DIVMOD_ENTRY \
    LGRT_ASM_BTI \
    "push {r4, lr}\n"
#define LGRT_DIVMOD_TEMP "r4"
#if LGRT_THUMB1 && LGRT_ARM_V4T
/* Thumb-1 cannot pop into lr, and r0 to r3 hold the results. */
#define LGRT_DIVMOD_EXIT \
    "ldr r2, [sp, #12]\n" \
    "mov lr, r2\n" \
    "pop {r2, r3, r4}\n" \
    "add sp, sp, #4\n" \
    "bx lr\n"
#elif LGRT_ARM_V4T
#define LGRT_DIVMOD_EXIT \
    "pop {r2, r3, r4, lr}\n" \
    "bx lr\n"
#else
#define LGRT_DIVMOD_EXIT "pop {r2, r3, r4, pc}\n"
#endif
#endif

#define LGRT_DIVMOD_ASM(f) \
    ".syntax unified\n" \
    LGRT_DIVMOD_ENTRY \
    "sub sp, sp, #16\n" \
    "add " LGRT_DIVMOD_TEMP ", sp, #8\n" \
    "str " LGRT_DIVMOD_TEMP ", [sp]\n" \
    "bl " f "\n" \
    "add sp, sp, #8\n" \
    LGRT_DIVMOD_EXIT \
    LGRT_ASM_END

/*
 * Workaround: GCC, ARM: it warns that the parameters of naked functions are
 * unused.
 */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

LGRT_AAPCS uint64_t __aeabi_uldivmod(uint64_t a, uint64_t b);
LGRT_AAPCS __attribute__((__naked__)) uint64_t __aeabi_uldivmod(
    uint64_t a, uint64_t b
) {
    __asm__ volatile (
        LGRT_DIVMOD_ASM("__udivmoddi4")
    );
}

LGRT_AAPCS int64_t __aeabi_ldivmod(int64_t a, int64_t b);
LGRT_AAPCS __attribute__((__naked__)) int64_t __aeabi_ldivmod(
    int64_t a, int64_t b
) {
    __asm__ volatile (
        LGRT_DIVMOD_ASM("__divmoddi4")
    );
}

#pragma GCC diagnostic pop

/* The run-time ABI's division by zero handlers, which programs may replace. */

LGRT_AAPCS int __aeabi_idiv0(
    int return_value
) __attribute__((__weak__, __visibility__("hidden")));
LGRT_AAPCS int __aeabi_idiv0(int return_value) {
    return return_value;
}

LGRT_AAPCS int64_t __aeabi_ldiv0(
    int64_t return_value
) __attribute__((__weak__, __visibility__("hidden")));
LGRT_AAPCS int64_t __aeabi_ldiv0(int64_t return_value) {
    return return_value;
}

/* __cmpdi2 and __ucmpdi2 return one more than these. */

LGRT_AAPCS int __aeabi_lcmp(int64_t a, int64_t b);
LGRT_AAPCS int __aeabi_lcmp(int64_t a, int64_t b) {
    return (int)((unsigned int)__cmpdi2(a, b) - 1);
}

LGRT_AAPCS int __aeabi_ulcmp(uint64_t a, uint64_t b);
LGRT_AAPCS int __aeabi_ulcmp(uint64_t a, uint64_t b) {
    return (int)((unsigned int)__ucmpdi2(a, b) - 1);
}

LGRT_AAPCS int64_t __aeabi_lmul(int64_t a, int64_t b);
LGRT_AAPCS int64_t __aeabi_lmul(
    int64_t a, int64_t b
) __attribute__((__alias__("__muldi3")));

LGRT_AAPCS int64_t __aeabi_llsl(int64_t a, int b);
LGRT_AAPCS int64_t __aeabi_llsl(
    int64_t a, int b
) __attribute__((__alias__("__ashldi3")));

LGRT_AAPCS int64_t __aeabi_llsr(int64_t a, int b);
LGRT_AAPCS int64_t __aeabi_llsr(
    int64_t a, int b
) __attribute__((__alias__("__lshrdi3")));

LGRT_AAPCS int64_t __aeabi_lasr(int64_t a, int b);
LGRT_AAPCS int64_t __aeabi_lasr(
    int64_t a, int b
) __attribute__((__alias__("__ashrdi3")));

/*
 * C code can compile into calls to these routines, so they are assembly that
 * branches to memcpy and friends. Thumb-1 branches cannot reach those, so
 * there these call them, with r3 padding the stack to 8 bytes and, on ARMv4T,
 * carrying the return address back.
 */

#if LGRT_THUMB1 && LGRT_ARM_V4T
#define LGRT_ASM_TAIL_CALL(f) \
    "push {r3, lr}\n" \
    "bl " f "\n" \
    "pop {r2, r3}\n" \
    "bx r3\n"
#elif LGRT_THUMB1
#define LGRT_ASM_TAIL_CALL(f) \
    "push {r3, lr}\n" \
    "bl " f "\n" \
    "pop {r3, pc}\n"
#elif defined(__thumb2__)
#define LGRT_ASM_TAIL_CALL(f) "b.w " f "\n"
#else
#define LGRT_ASM_TAIL_CALL(f) "b " f "\n"
#endif

/* Workaround: GCC, ARM: as for the division routines. */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

LGRT_AAPCS void __aeabi_memcpy(void *dest, const void *src, size_t n);
LGRT_AAPCS __attribute__((__naked__)) void __aeabi_memcpy(
    void *dest, const void *src, size_t n
) {
    __asm__ volatile (
        ".syntax unified\n"
        LGRT_ASM_BTI
        LGRT_ASM_TAIL_CALL("memcpy")
        LGRT_ASM_END
    );
}

LGRT_AAPCS void __aeabi_memcpy4(void *dest, const void *src, size_t n);
LGRT_AAPCS void __aeabi_memcpy4(
    void *dest, const void *src, size_t n
) __attribute__((__alias__("__aeabi_memcpy")));

LGRT_AAPCS void __aeabi_memcpy8(void *dest, const void *src, size_t n);
LGRT_AAPCS void __aeabi_memcpy8(
    void *dest, const void *src, size_t n
) __attribute__((__alias__("__aeabi_memcpy")));

LGRT_AAPCS void __aeabi_memmove(void *dest, const void *src, size_t n);
LGRT_AAPCS __attribute__((__naked__)) void __aeabi_memmove(
    void *dest, const void *src, size_t n
) {
    __asm__ volatile (
        ".syntax unified\n"
        LGRT_ASM_BTI
        LGRT_ASM_TAIL_CALL("memmove")
        LGRT_ASM_END
    );
}

LGRT_AAPCS void __aeabi_memmove4(void *dest, const void *src, size_t n);
LGRT_AAPCS void __aeabi_memmove4(
    void *dest, const void *src, size_t n
) __attribute__((__alias__("__aeabi_memmove")));

LGRT_AAPCS void __aeabi_memmove8(void *dest, const void *src, size_t n);
LGRT_AAPCS void __aeabi_memmove8(
    void *dest, const void *src, size_t n
) __attribute__((__alias__("__aeabi_memmove")));

/*
 * memset takes the value before the count. The moves set flags, as Thumb-1
 * before ARMv6 has no other moves between low registers.
 */

LGRT_AAPCS void __aeabi_memset(void *dest, size_t n, int c);
LGRT_AAPCS __attribute__((__naked__)) void __aeabi_memset(
    void *dest, size_t n, int c
) {
    __asm__ volatile (
        ".syntax unified\n"
        LGRT_ASM_BTI
        "movs r3, r1\n"
        "movs r1, r2\n"
        "movs r2, r3\n"
        LGRT_ASM_TAIL_CALL("memset")
        LGRT_ASM_END
    );
}

LGRT_AAPCS void __aeabi_memset4(void *dest, size_t n, int c);
LGRT_AAPCS void __aeabi_memset4(
    void *dest, size_t n, int c
) __attribute__((__alias__("__aeabi_memset")));

LGRT_AAPCS void __aeabi_memset8(void *dest, size_t n, int c);
LGRT_AAPCS void __aeabi_memset8(
    void *dest, size_t n, int c
) __attribute__((__alias__("__aeabi_memset")));

LGRT_AAPCS void __aeabi_memclr(void *dest, size_t n);
LGRT_AAPCS __attribute__((__naked__)) void __aeabi_memclr(
    void *dest, size_t n
) {
    __asm__ volatile (
        ".syntax unified\n"
        LGRT_ASM_BTI
        "movs r2, r1\n"
        "movs r1, #0\n"
        LGRT_ASM_TAIL_CALL("memset")
        LGRT_ASM_END
    );
}

LGRT_AAPCS void __aeabi_memclr4(void *dest, size_t n);
LGRT_AAPCS void __aeabi_memclr4(
    void *dest, size_t n
) __attribute__((__alias__("__aeabi_memclr")));

LGRT_AAPCS void __aeabi_memclr8(void *dest, size_t n);
LGRT_AAPCS void __aeabi_memclr8(
    void *dest, size_t n
) __attribute__((__alias__("__aeabi_memclr")));

LGRT_AAPCS int __aeabi_memcmp(const void *a, const void *b, size_t n);
LGRT_AAPCS __attribute__((__naked__)) int __aeabi_memcmp(
    const void *a, const void *b, size_t n
) {
    __asm__ volatile (
        ".syntax unified\n"
        LGRT_ASM_BTI
        LGRT_ASM_TAIL_CALL("memcmp")
        LGRT_ASM_END
    );
}

LGRT_AAPCS int __aeabi_memcmp4(const void *a, const void *b, size_t n);
LGRT_AAPCS int __aeabi_memcmp4(
    const void *a, const void *b, size_t n
) __attribute__((__alias__("__aeabi_memcmp")));

LGRT_AAPCS int __aeabi_memcmp8(const void *a, const void *b, size_t n);
LGRT_AAPCS int __aeabi_memcmp8(
    const void *a, const void *b, size_t n
) __attribute__((__alias__("__aeabi_memcmp")));

#pragma GCC diagnostic pop

#endif

/*
 * The atomic routines need the atomic instructions of the target, and nothing
 * but them: neither the help of an operating system, nor masked interrupts. So
 * they exist only where the compiler implements pointer-sized atomics inline
 * with such instructions. Where it gets those wrong, LGRT_WORD_CAS stands in
 * for them: a compare-exchange of aligned words, on which the accesses of up
 * to 4 bytes are lock-free, so that they are atomic with respect to the loads
 * and stores that the compilers inline.
 */
#if defined(__i386__) && !defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_4)
/* No compare-exchange on the 80386, where Clang uses it all the same. */
#define LGRT_NO_ATOMICS 1
#elif defined(__arm__) \
   && (!defined(__ARM_ARCH) || __ARM_ARCH < 6 \
    || (defined(__thumb__) && !defined(__thumb2__) && __ARM_ARCH < 8))
/*
 * No exclusive loads and stores before ARMv6, or in Thumb-1 before ARMv8-M
 * Baseline.
 */
#define LGRT_NO_ATOMICS 1
#elif defined(__arm__) \
   && ((defined(__clang__) && defined(__ARM_FEATURE_LDREX) \
     && (__ARM_FEATURE_LDREX & 1) == 0) \
    || (!defined(__clang__) && defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_4) \
     && !defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_1)))
/*
 * Workaround: ARMv6 without K: Clang uses the byte, halfword, and doubleword
 * exclusives that ARMv6K added, and GCC may turn byte and halfword atomics
 * into calls to the __sync routines, which are built on them.
 */
#define LGRT_WORD_CAS 1
#elif defined(__sparc__) && !defined(__arch64__) \
   && !defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_4)
/* No compare-exchange before SPARC V9. */
#define LGRT_NO_ATOMICS 1
#elif defined(__hppa__)
/*
 * No compare-exchange on PA-RISC, where GCC implements even the __atomic
 * builtins with calls to __sync routines.
 */
#define LGRT_NO_ATOMICS 1
#elif defined(__sh__) && !defined(__SH_ATOMIC_MODEL_HARD_LLCS__)
/*
 * Only the movli.l and movco.l of SH4A are such instructions: the other atomic
 * models of GCC rely on the kernel, or on masked interrupts.
 */
#define LGRT_NO_ATOMICS 1
#elif defined(__mips) && __mips == 1
/* No ll and sc on MIPS I, which GCC uses all the same, for kernels to fake. */
#define LGRT_NO_ATOMICS 1
#elif defined(__loongarch__) && defined(__loongarch_grlen) \
   && __loongarch_grlen == 32 \
   && !(defined(__clang__) && __clang_major__ >= 21)
/*
 * Workaround: GCC, and Clang before 21, 32-bit LoongArch: they get atomics
 * wrong.
 */
#define LGRT_WORD_CAS 1
#elif !defined(__clang__) && defined(__MICROBLAZE__)
/*
 * Workaround: GCC (16 at least), MicroBlaze: its 4-byte compare-exchange takes
 * two words that differ in their top bit alone for equal where the one it
 * finds has that bit set, as the cmp it compares them with puts the signed
 * comparison in that bit. Before 14.4, and in 15.1 and 15.2, it also gives
 * back the comparison it makes, which is 0 where it succeeds, for its result.
 * So the exchanges, the other read-modify-write operations, and test-and-set
 * it builds on it, and those of 1 and 2 bytes, get wrong values.
 */
#define LGRT_WORD_CAS 1
#elif !defined(__clang__) && !defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_4)
/*
 * What GCC claims to be lock-free without that, it calls __sync routines for.
 */
#define LGRT_NO_ATOMICS 1
#elif !defined(__GCC_ATOMIC_POINTER_LOCK_FREE) \
   || __GCC_ATOMIC_POINTER_LOCK_FREE != 2
#define LGRT_NO_ATOMICS 1
#endif

#if !defined(LGRT_WORD_CAS)
#define LGRT_WORD_CAS 0
#endif

#if defined(LGRT_NO_ATOMICS)
#define LGRT_HAS_ATOMICS 0
#else
#define LGRT_HAS_ATOMICS 1
#endif

#if LGRT_HAS_ATOMICS

/*
 * Compilers reserve the names of the atomic routines for their builtins, so
 * the routines have other names in C and get theirs from asm labels.
 */
#define LGRT_STR(x) #x
#define LGRT_XSTR(x) LGRT_STR(x)
#define LGRT_ASM_LABEL(name) __asm__ (LGRT_XSTR(__USER_LABEL_PREFIX__) #name)

/*
 * Clang turns atomic builtins on types aligned below their size, such as
 * 64-bit integers on IA-32, into calls to the routines below, so the builtins
 * operate on these types instead.
 */
typedef uint16_t lgrt_atomic_u16 __attribute__((__aligned__(2)));
typedef uint32_t lgrt_atomic_u32 __attribute__((__aligned__(4)));
typedef uint64_t lgrt_atomic_u64 __attribute__((__aligned__(8)));
#if LGRT_HAS_INT128
typedef lgrt_u128 lgrt_atomic_u128 __attribute__((__aligned__(16)));
#endif
typedef uintptr_t lgrt_lock_word __attribute__((__aligned__(
    sizeof(uintptr_t)
)));

/*
 * Objects that are not lock-free are accessed under a lock chosen by hashing
 * their address: the lowest bits rarely tell objects apart, so they are
 * dropped, and higher ones are folded in.
 */
#define LGRT_LOCK_BITS 9
#define LGRT_LOCK_COUNT ((size_t)1 << LGRT_LOCK_BITS)

static lgrt_lock_word lgrt_locks[LGRT_LOCK_COUNT];

static inline lgrt_lock_word *lgrt_lock_of(const volatile void *ptr) {
    uintptr_t h = (uintptr_t)ptr >> 3;

    h ^= h >> LGRT_LOCK_BITS;
    h ^= h >> (2 * LGRT_LOCK_BITS);
    return &lgrt_locks[h & (LGRT_LOCK_COUNT - 1)];
}

#if LGRT_WORD_CAS
/* A full barrier, or what the target needs for one. */
static inline void lgrt_fence(void) {
#if defined(__arm__)
    uint32_t zero = 0;

    /* The data memory barrier of ARMv6. */
    __asm__ volatile (
        "mcr p15, 0, %0, c7, c10, 5"
        :
        : "r"(zero)
        : "memory"
    );
#elif defined(__loongarch__)
    __asm__ volatile ("dbar 0" : : : "memory");
#else
    __asm__ volatile ("" : : : "memory");
#endif
}
#endif

#if LGRT_WORD_CAS

/* The compare-exchange of an aligned word, which gives back what it found. */
#if defined(__arm__)

static inline uint32_t lgrt_word_cas(
    volatile uint32_t *word, uint32_t expected, uint32_t desired
) {
    uint32_t found;
    uint32_t failed;

    lgrt_fence();
    __asm__ volatile (
        "1:\n"
        "ldrex %0, [%2]\n"
        "cmp %0, %3\n"
        "bne 2f\n"
        "strex %1, %4, [%2]\n"
        "cmp %1, #0\n"
        "bne 1b\n"
        "2:"
        : "=&r"(found), "=&r"(failed)
        : "r"(word), "r"(expected), "r"(desired)
        : "cc", "memory"
    );
    lgrt_fence();
    return found;
}

#elif defined(__loongarch__)

static inline uint32_t lgrt_word_cas(
    volatile uint32_t *word, uint32_t expected, uint32_t desired
) {
    uint32_t found;
    uint32_t stored;

    __asm__ volatile (
        "1:\n"
        "ll.w %0, %2, 0\n"
        "bne %0, %3, 2f\n"
        "move %1, %4\n"
        "sc.w %1, %2, 0\n"
        "beqz %1, 1b\n"
        "2:\n"
        "dbar 0"
        : "=&r"(found), "=&r"(stored)
        : "r"(word), "r"(expected), "r"(desired)
        : "memory"
    );
    return found;
}

#elif defined(__MICROBLAZE__)

static inline uint32_t lgrt_word_cas(
    volatile uint32_t *word, uint32_t expected, uint32_t desired
) {
    uint32_t found;
    uint32_t c;

    __asm__ volatile (
        "addc r0, r0, r0\n"
        "1:\n"
        "lwx %0, %2, r0\n"
        "addic %1, r0, 0\n"
        "bnei %1, 1b\n"
        "xor %1, %0, %3\n"
        "bnei %1, 2f\n"
        "swx %4, %2, r0\n"
        "addic %1, r0, 0\n"
        "bnei %1, 1b\n"
        "2:"
        : "=&r"(found), "=&r"(c)
        : "r"(word), "r"(expected), "r"(desired)
        : "cc", "memory"
    );
    return found;
}

#endif

#endif

static inline void lgrt_lock(lgrt_lock_word *lock) {
#if LGRT_WORD_CAS
    while (lgrt_word_cas((volatile uint32_t *)lock, 0, 1) != 0) {
        while (*(volatile lgrt_lock_word *)lock != 0) {
        }
    }
#else
    while (__atomic_exchange_n(lock, 1, __ATOMIC_ACQUIRE) != 0) {
        while (__atomic_load_n(lock, __ATOMIC_RELAXED) != 0) {
        }
    }
#endif
}

static inline void lgrt_unlock(lgrt_lock_word *lock) {
#if LGRT_WORD_CAS
    lgrt_fence();
    *(volatile lgrt_lock_word *)lock = 0;
#else
    __atomic_store_n(lock, 0, __ATOMIC_RELEASE);
#endif
}

/*
 * An object of n bytes, for n of 1, 2, 4, 8, and 16, is accessed lock-free
 * when LGRT_LOCK_FREE(n) holds and the object is aligned to n. Every builtin
 * on n bytes sits under a plain if on that constant, so that it vanishes where
 * the constant is false instead of compiling into a call to the routine
 * containing it. On words, those of up to 4 bytes are the only ones that need
 * no lock.
 *
 * Workaround: GCC 5 and 6, 32-bit ARM without doubleword exclusives; Clang
 * before 9, 80486: they claim that 8-byte objects are always lock-free where
 * they are not, GCC calling __sync routines for them and Clang using the
 * cmpxchg8b that the Pentium added, so LGRT_LOCK_FREE(8) is false there.
 */
#if LGRT_WORD_CAS
#define LGRT_LOCK_FREE(n) ((n) <= 4)
#elif (defined(__arm__) \
  && !(defined(__ARM_FEATURE_LDREX) && (__ARM_FEATURE_LDREX & 8) != 0)) \
 || (defined(__i386__) && !defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_8))
#define LGRT_LOCK_FREE(n) ((n) != 8 && __atomic_always_lock_free(n, 0))
#else
#define LGRT_LOCK_FREE(n) (__atomic_always_lock_free(n, 0))
#endif

static inline bool lgrt_aligned(const volatile void *ptr, size_t n) {
    return ((uintptr_t)ptr & (n - 1)) == 0;
}

/*
 * Buffers other than the objects are not shared, but may be misaligned, so
 * they are copied with lgrt_copy, as are objects under their locks. When
 * optimising for size, Clang turns misaligned word accesses into calls to
 * __aeabi_uread4 and friends on ARM without unaligned accesses, so there
 * lgrt_copy copies bytes, through volatile loads that it cannot merge into
 * words.
 */
#if defined(__clang__) && defined(__arm__) && !defined(__ARM_FEATURE_UNALIGNED)
static inline void lgrt_copy(void *dest, const volatile void *src, size_t n) {
    unsigned char *d = dest;
    const volatile unsigned char *s = src;
    size_t i;

    for (i = 0; i < n; i++) {
        d[i] = s[i];
    }
}
#elif !defined(__clang__) && defined(__sparc__) && !defined(__arch64__)
/*
 * GCC for 32-bit SPARC has the 8-byte loads and stores inline, as one
 * instruction each, without the lock, so those under the lock are one
 * instruction too, for the others not to see a value partly written.
 */
#define LGRT_COPY_WHOLE_8 1
static inline void lgrt_copy(void *dest, const volatile void *src, size_t n) {
    if (n == 8) {
        uint64_t v;

        if (lgrt_aligned(src, 8)) {
            v = *(const volatile lgrt_atomic_u64 *)src;
        } else {
            __builtin_memcpy(&v, (const void *)src, 8);
        }
        if (lgrt_aligned(dest, 8)) {
            *(volatile lgrt_atomic_u64 *)dest = v;
        } else {
            __builtin_memcpy(dest, &v, 8);
        }
        return;
    }
    __builtin_memcpy(dest, (const void *)src, n);
}
#else
static inline void lgrt_copy(void *dest, const volatile void *src, size_t n) {
    __builtin_memcpy(dest, (const void *)src, n);
}
#endif

#if LGRT_WORD_CAS
/*
 * The compare-exchange of the n bytes at ptr, of up to 4, on the aligned word
 * they are in, which writes what it found to expected where it fails.
 */
static inline bool lgrt_word_compare_exchange(
    volatile void *ptr, size_t n, void *expected, const void *desired
) {
    uintptr_t at = (uintptr_t)ptr & 3;
    volatile uint32_t *word = (volatile uint32_t *)((uintptr_t)ptr - at);
    uint32_t found = *word;

    for (;;) {
        uint32_t want = found;
        uint32_t next = found;
        uint32_t seen;

        lgrt_copy((unsigned char *)&want + at, expected, n);
        if (want != found) {
            lgrt_copy(expected, (unsigned char *)&found + at, n);
            return false;
        }
        lgrt_copy((unsigned char *)&next + at, desired, n);
        seen = lgrt_word_cas(word, found, next);
        if (seen == found) {
            return true;
        }
        found = seen;
    }
}

/*
 * The exchange of the n bytes at ptr, of up to 4, which writes what it found
 * to old.
 */
static inline void lgrt_word_exchange(
    volatile void *ptr, size_t n, const void *val, void *old
) {
    lgrt_copy(old, ptr, n);
    while (!lgrt_word_compare_exchange(ptr, n, old, val)) {
    }
}

/* Aligned loads and stores of up to 4 bytes are atomic by themselves. */
#define LGRT_ATOMIC_LOAD(p, model) \
    __extension__ ({ \
        __typeof__(*(p)) lgrt_loaded_ = *(p); \
        \
        (void)(model); \
        lgrt_fence(); \
        lgrt_loaded_; \
    })

#define LGRT_ATOMIC_STORE(p, val, model) \
    do { \
        (void)(model); \
        lgrt_fence(); \
        *(p) = (val); \
        lgrt_fence(); \
    } while (0)
#else
#define LGRT_ATOMIC_LOAD(p, model) __atomic_load_n(p, model)
#define LGRT_ATOMIC_STORE(p, val, model) __atomic_store_n(p, val, model)
#endif

static inline void lgrt_locked_load(
    size_t size, const volatile void *src, void *dest
) {
    lgrt_lock_word *lock = lgrt_lock_of(src);

    lgrt_lock(lock);
    lgrt_copy(dest, src, size);
    lgrt_unlock(lock);
}

static inline void lgrt_locked_store(
    size_t size, volatile void *dest, const void *src
) {
    lgrt_lock_word *lock = lgrt_lock_of(dest);

    lgrt_lock(lock);
    lgrt_copy((void *)dest, src, size);
    lgrt_unlock(lock);
}

static inline void lgrt_locked_exchange(
    size_t size, volatile void *ptr, const void *val, void *old
) {
    lgrt_lock_word *lock = lgrt_lock_of(ptr);

    lgrt_lock(lock);
    /*
     * Callers may pass one buffer as both val and old, whose bytes are then
     * swapped.
     */
    if (val != old) {
        lgrt_copy(old, ptr, size);
        lgrt_copy((void *)ptr, val, size);
#if defined(LGRT_COPY_WHOLE_8)
    } else if (size == 8) {
        uint64_t t;

        lgrt_copy(&t, ptr, 8);
        lgrt_copy((void *)ptr, val, 8);
        lgrt_copy(old, &t, 8);
#endif
    } else {
        unsigned char *p = (unsigned char *)ptr;
        unsigned char *o = old;
        size_t i;

        for (i = 0; i < size; i++) {
            unsigned char t = p[i];

            p[i] = o[i];
            o[i] = t;
        }
    }
    lgrt_unlock(lock);
}

static inline bool lgrt_locked_compare_exchange(
    size_t size, volatile void *ptr, void *expected, const void *desired
) {
    lgrt_lock_word *lock = lgrt_lock_of(ptr);
    bool equal;

    lgrt_lock(lock);
    equal = __builtin_memcmp((const void *)ptr, expected, size) == 0;
    if (equal) {
        lgrt_copy((void *)ptr, desired, size);
    } else {
        lgrt_copy(expected, ptr, size);
    }
    lgrt_unlock(lock);
    return equal;
}

#if LGRT_HAS_INT128 && defined(__s390x__) && !defined(__clang__)

/*
 * Workaround: GCC, s390x: it compiles 16-byte atomic builtins into library
 * calls, that is, into calls to the routines below, so the 16-byte helpers
 * further down use these instead. lpq, stpq, and cdsg access aligned quadwords
 * atomically, through the even/odd register pairs in which GCC holds 128-bit
 * values. Only loads may pass earlier stores on s390x, which the serialisation
 * after sequentially consistent stores prevents, and cdsg serialises, so no
 * memory order needs more.
 */
#define LGRT_S390X_ASM_16 1

static inline lgrt_u128 lgrt_s390x_load_16(
    const volatile void *ptr, int model
) {
    const volatile lgrt_atomic_u128 *p = ptr;
    lgrt_u128 v;

    (void)model;
    __asm__ volatile (
        "lpq %0,%1"
        : "=d"(v)
        : "Q"(*p)
        : "memory"
    );
    return v;
}

static inline void lgrt_s390x_store_16(
    volatile void *ptr, lgrt_u128 val, int model
) {
    volatile lgrt_atomic_u128 *p = ptr;

    if (model == __ATOMIC_SEQ_CST) {
        __asm__ volatile (
            "stpq %1,%0\n"
            "bcr 15,0"
            : "=Q"(*p)
            : "d"(val)
            : "memory"
        );
    } else {
        __asm__ volatile (
            "stpq %1,%0"
            : "=Q"(*p)
            : "d"(val)
            : "memory"
        );
    }
}

/*
 * cdsg sets condition code 0 when it stores desired, and otherwise loads the
 * quadword into the pair that held expected.
 */
static inline bool lgrt_s390x_compare_exchange_16(
    volatile void *ptr, lgrt_u128 *expected, lgrt_u128 desired, int success,
    int failure
) {
    volatile lgrt_atomic_u128 *p = ptr;
    lgrt_u128 e = *expected;
    int cc;

    (void)success;
    (void)failure;
    __asm__ volatile (
        "cdsg %0,%3,%1\n"
        "ipm %2\n"
        "srl %2,28"
        : "+d"(e), "+Q"(*p), "=d"(cc)
        : "d"(desired)
        : "cc", "memory"
    );
    *expected = e;
    return cc == 0;
}

#else
#define LGRT_S390X_ASM_16 0
#endif

#if LGRT_HAS_INT128 && defined(__aarch64__) && defined(__clang__) \
 && (__clang_major__ < 8 || (__clang_major__ < 23 && defined(__AARCH64EB__)))

/*
 * Workaround: Clang before 8, AArch64 with LSE; Clang before 23, big-endian
 * AArch64: in 16-byte atomics, the first uses casp on odd registers or gets
 * its success flag wrong, without defining a macro that tells whether LSE is
 * enabled, and the second swaps the halves of the values it stores. There, the
 * 16-byte helpers below use this file's own compare-and-swap routines, defined
 * further on, picking the one whose ordering covers both memory orders: an
 * order acquires unless it is relaxed or release, and releases unless it is
 * relaxed, consume, or acquire.
 */
#define LGRT_AARCH64_CAS_16 1

lgrt_u128 __aarch64_cas16_relax(
    lgrt_u128 expected, lgrt_u128 desired, volatile void *ptr
);
lgrt_u128 __aarch64_cas16_acq(
    lgrt_u128 expected, lgrt_u128 desired, volatile void *ptr
);
lgrt_u128 __aarch64_cas16_rel(
    lgrt_u128 expected, lgrt_u128 desired, volatile void *ptr
);
lgrt_u128 __aarch64_cas16_acq_rel(
    lgrt_u128 expected, lgrt_u128 desired, volatile void *ptr
);

/*
 * Returns the value read, which equals expected exactly when desired was
 * stored.
 */
static inline lgrt_u128 lgrt_aarch64_cas_16(
    volatile void *ptr, lgrt_u128 expected, lgrt_u128 desired, int success,
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

#else
#define LGRT_AARCH64_CAS_16 0
#endif

/*
 * Where LGRT_ATOMIC_HELPERS_16 is 1, the 16-byte atomic builtins cannot be
 * used, and lock-free 16-byte objects are accessed with these helpers instead.
 * They take the builtins' memory orders, and lgrt_compare_exchange_16 stores
 * the value it read in expected when it fails. On AArch64, a load is a
 * compare-exchange of 0 with 0, which returns the value and, if it is 0,
 * writes it back unchanged.
 */
#if LGRT_S390X_ASM_16 || LGRT_AARCH64_CAS_16
#define LGRT_ATOMIC_HELPERS_16 1

static inline lgrt_u128 lgrt_load_16(const volatile void *ptr, int model) {
#if LGRT_S390X_ASM_16
    return lgrt_s390x_load_16(ptr, model);
#else
    return lgrt_aarch64_cas_16((volatile void *)ptr, 0, 0, model, model);
#endif
}

static inline bool lgrt_compare_exchange_16(
    volatile void *ptr, lgrt_u128 *expected, lgrt_u128 desired, int success,
    int failure
) {
#if LGRT_S390X_ASM_16
    return lgrt_s390x_compare_exchange_16(
        ptr, expected, desired, success, failure
    );
#else
    lgrt_u128 e = *expected;

    *expected = lgrt_aarch64_cas_16(ptr, e, desired, success, failure);
    return *expected == e;
#endif
}

static inline lgrt_u128 lgrt_exchange_16(
    volatile void *ptr, lgrt_u128 val, int model
) {
    lgrt_u128 old = lgrt_load_16(ptr, __ATOMIC_RELAXED);
    bool done;

    do {
        done = lgrt_compare_exchange_16(
            ptr, &old, val, model, __ATOMIC_RELAXED
        );
    } while (!done);
    return old;
}

static inline void lgrt_store_16(
    volatile void *ptr, lgrt_u128 val, int model
) {
#if LGRT_S390X_ASM_16
    lgrt_s390x_store_16(ptr, val, model);
#else
    lgrt_exchange_16(ptr, val, model);
#endif
}

#else
#define LGRT_ATOMIC_HELPERS_16 0
#endif

bool lgrt_atomic_is_lock_free(
    size_t size, void *ptr
) LGRT_ASM_LABEL(__atomic_is_lock_free);
bool lgrt_atomic_is_lock_free(size_t size, void *ptr) {
    if (LGRT_LOCK_FREE(1)) {
        if (size == 1) {
            return true;
        }
    }
    if (LGRT_LOCK_FREE(2)) {
        if (size == 2) {
            return lgrt_aligned(ptr, 2);
        }
    }
    if (LGRT_LOCK_FREE(4)) {
        if (size == 4) {
            return lgrt_aligned(ptr, 4);
        }
    }
    if (LGRT_LOCK_FREE(8)) {
        if (size == 8) {
            return lgrt_aligned(ptr, 8);
        }
    }
#if LGRT_HAS_INT128
    if (LGRT_LOCK_FREE(16)) {
        if (size == 16) {
            return lgrt_aligned(ptr, 16);
        }
    }
#endif
    return false;
}

/*
 * The generic routines leave lock-free objects to the sized routines, declared
 * here and defined after them.
 *
 * Workaround: GCC before 8, SuperH: at -O3, it cannot allocate registers for
 * the atomic sequences of several sizes in one function, so the sized routines
 * are not inlined there.
 */
#if !defined(__clang__) && defined(__sh__) && __GNUC__ < 8
#define LGRT_SIZED_NOINLINE __attribute__((__noinline__))
#else
#define LGRT_SIZED_NOINLINE
#endif

uint8_t lgrt_atomic_load_1(
    const volatile void *ptr, int model
) LGRT_ASM_LABEL(__atomic_load_1) LGRT_SIZED_NOINLINE;
uint16_t lgrt_atomic_load_2(
    const volatile void *ptr, int model
) LGRT_ASM_LABEL(__atomic_load_2) LGRT_SIZED_NOINLINE;
uint32_t lgrt_atomic_load_4(
    const volatile void *ptr, int model
) LGRT_ASM_LABEL(__atomic_load_4) LGRT_SIZED_NOINLINE;
uint64_t lgrt_atomic_load_8(
    const volatile void *ptr, int model
) LGRT_ASM_LABEL(__atomic_load_8) LGRT_SIZED_NOINLINE;
#if LGRT_HAS_INT128
lgrt_u128 lgrt_atomic_load_16(
    const volatile void *ptr, int model
) LGRT_ASM_LABEL(__atomic_load_16) LGRT_SIZED_NOINLINE;
#endif

void lgrt_atomic_store_1(
    volatile void *ptr, uint8_t val, int model
) LGRT_ASM_LABEL(__atomic_store_1) LGRT_SIZED_NOINLINE;
void lgrt_atomic_store_2(
    volatile void *ptr, uint16_t val, int model
) LGRT_ASM_LABEL(__atomic_store_2) LGRT_SIZED_NOINLINE;
void lgrt_atomic_store_4(
    volatile void *ptr, uint32_t val, int model
) LGRT_ASM_LABEL(__atomic_store_4) LGRT_SIZED_NOINLINE;
void lgrt_atomic_store_8(
    volatile void *ptr, uint64_t val, int model
) LGRT_ASM_LABEL(__atomic_store_8) LGRT_SIZED_NOINLINE;
#if LGRT_HAS_INT128
void lgrt_atomic_store_16(
    volatile void *ptr, lgrt_u128 val, int model
) LGRT_ASM_LABEL(__atomic_store_16) LGRT_SIZED_NOINLINE;
#endif

uint8_t lgrt_atomic_exchange_1(
    volatile void *ptr, uint8_t val, int model
) LGRT_ASM_LABEL(__atomic_exchange_1) LGRT_SIZED_NOINLINE;
uint16_t lgrt_atomic_exchange_2(
    volatile void *ptr, uint16_t val, int model
) LGRT_ASM_LABEL(__atomic_exchange_2) LGRT_SIZED_NOINLINE;
uint32_t lgrt_atomic_exchange_4(
    volatile void *ptr, uint32_t val, int model
) LGRT_ASM_LABEL(__atomic_exchange_4) LGRT_SIZED_NOINLINE;
uint64_t lgrt_atomic_exchange_8(
    volatile void *ptr, uint64_t val, int model
) LGRT_ASM_LABEL(__atomic_exchange_8) LGRT_SIZED_NOINLINE;
#if LGRT_HAS_INT128
lgrt_u128 lgrt_atomic_exchange_16(
    volatile void *ptr, lgrt_u128 val, int model
) LGRT_ASM_LABEL(__atomic_exchange_16) LGRT_SIZED_NOINLINE;
#endif

bool lgrt_atomic_compare_exchange_1(
    volatile void *ptr, void *expected, uint8_t desired, int success,
    int failure
) LGRT_ASM_LABEL(__atomic_compare_exchange_1) LGRT_SIZED_NOINLINE;
bool lgrt_atomic_compare_exchange_2(
    volatile void *ptr, void *expected, uint16_t desired, int success,
    int failure
) LGRT_ASM_LABEL(__atomic_compare_exchange_2) LGRT_SIZED_NOINLINE;
bool lgrt_atomic_compare_exchange_4(
    volatile void *ptr, void *expected, uint32_t desired, int success,
    int failure
) LGRT_ASM_LABEL(__atomic_compare_exchange_4) LGRT_SIZED_NOINLINE;
bool lgrt_atomic_compare_exchange_8(
    volatile void *ptr, void *expected, uint64_t desired, int success,
    int failure
) LGRT_ASM_LABEL(__atomic_compare_exchange_8) LGRT_SIZED_NOINLINE;
#if LGRT_HAS_INT128
bool lgrt_atomic_compare_exchange_16(
    volatile void *ptr, void *expected, lgrt_u128 desired, int success,
    int failure
) LGRT_ASM_LABEL(__atomic_compare_exchange_16) LGRT_SIZED_NOINLINE;
#endif

void lgrt_atomic_load(
    size_t size, void *src, void *dest, int model
) LGRT_ASM_LABEL(__atomic_load);
void lgrt_atomic_load(size_t size, void *src, void *dest, int model) {
    if (LGRT_LOCK_FREE(1)) {
        if (size == 1) {
            uint8_t v = lgrt_atomic_load_1(src, model);

            lgrt_copy(dest, &v, 1);
            return;
        }
    }
    if (LGRT_LOCK_FREE(2)) {
        if (size == 2 && lgrt_aligned(src, 2)) {
            uint16_t v = lgrt_atomic_load_2(src, model);

            lgrt_copy(dest, &v, 2);
            return;
        }
    }
    if (LGRT_LOCK_FREE(4)) {
        if (size == 4 && lgrt_aligned(src, 4)) {
            uint32_t v = lgrt_atomic_load_4(src, model);

            lgrt_copy(dest, &v, 4);
            return;
        }
    }
    if (LGRT_LOCK_FREE(8)) {
        if (size == 8 && lgrt_aligned(src, 8)) {
            uint64_t v = lgrt_atomic_load_8(src, model);

            lgrt_copy(dest, &v, 8);
            return;
        }
    }
#if LGRT_HAS_INT128
    if (LGRT_LOCK_FREE(16)) {
        if (size == 16 && lgrt_aligned(src, 16)) {
            lgrt_u128 v = lgrt_atomic_load_16(src, model);

            lgrt_copy(dest, &v, 16);
            return;
        }
    }
#endif
    lgrt_locked_load(size, src, dest);
}

void lgrt_atomic_store(
    size_t size, void *dest, void *src, int model
) LGRT_ASM_LABEL(__atomic_store);
void lgrt_atomic_store(size_t size, void *dest, void *src, int model) {
    if (LGRT_LOCK_FREE(1)) {
        if (size == 1) {
            uint8_t v;

            lgrt_copy(&v, src, 1);
            lgrt_atomic_store_1(dest, v, model);
            return;
        }
    }
    if (LGRT_LOCK_FREE(2)) {
        if (size == 2 && lgrt_aligned(dest, 2)) {
            uint16_t v;

            lgrt_copy(&v, src, 2);
            lgrt_atomic_store_2(dest, v, model);
            return;
        }
    }
    if (LGRT_LOCK_FREE(4)) {
        if (size == 4 && lgrt_aligned(dest, 4)) {
            uint32_t v;

            lgrt_copy(&v, src, 4);
            lgrt_atomic_store_4(dest, v, model);
            return;
        }
    }
    if (LGRT_LOCK_FREE(8)) {
        if (size == 8 && lgrt_aligned(dest, 8)) {
            uint64_t v;

            lgrt_copy(&v, src, 8);
            lgrt_atomic_store_8(dest, v, model);
            return;
        }
    }
#if LGRT_HAS_INT128
    if (LGRT_LOCK_FREE(16)) {
        if (size == 16 && lgrt_aligned(dest, 16)) {
            lgrt_u128 v;

            lgrt_copy(&v, src, 16);
            lgrt_atomic_store_16(dest, v, model);
            return;
        }
    }
#endif
    lgrt_locked_store(size, dest, src);
}

void lgrt_atomic_exchange(
    size_t size, void *ptr, void *val, void *old, int model
) LGRT_ASM_LABEL(__atomic_exchange);
void lgrt_atomic_exchange(
    size_t size, void *ptr, void *val, void *old, int model
) {
    if (LGRT_LOCK_FREE(1)) {
        if (size == 1) {
            uint8_t x;

            lgrt_copy(&x, val, 1);
            x = lgrt_atomic_exchange_1(ptr, x, model);
            lgrt_copy(old, &x, 1);
            return;
        }
    }
    if (LGRT_LOCK_FREE(2)) {
        if (size == 2 && lgrt_aligned(ptr, 2)) {
            uint16_t x;

            lgrt_copy(&x, val, 2);
            x = lgrt_atomic_exchange_2(ptr, x, model);
            lgrt_copy(old, &x, 2);
            return;
        }
    }
    if (LGRT_LOCK_FREE(4)) {
        if (size == 4 && lgrt_aligned(ptr, 4)) {
            uint32_t x;

            lgrt_copy(&x, val, 4);
            x = lgrt_atomic_exchange_4(ptr, x, model);
            lgrt_copy(old, &x, 4);
            return;
        }
    }
    if (LGRT_LOCK_FREE(8)) {
        if (size == 8 && lgrt_aligned(ptr, 8)) {
            uint64_t x;

            lgrt_copy(&x, val, 8);
            x = lgrt_atomic_exchange_8(ptr, x, model);
            lgrt_copy(old, &x, 8);
            return;
        }
    }
#if LGRT_HAS_INT128
    if (LGRT_LOCK_FREE(16)) {
        if (size == 16 && lgrt_aligned(ptr, 16)) {
            lgrt_u128 x;

            lgrt_copy(&x, val, 16);
            x = lgrt_atomic_exchange_16(ptr, x, model);
            lgrt_copy(old, &x, 16);
            return;
        }
    }
#endif
    lgrt_locked_exchange(size, ptr, val, old);
}

/*
 * Compilers drop the weak flag when they call these routines, so they are
 * strong.
 */
bool lgrt_atomic_compare_exchange(
    size_t size, void *ptr, void *expected, void *desired, int success,
    int failure
) LGRT_ASM_LABEL(__atomic_compare_exchange);
bool lgrt_atomic_compare_exchange(
    size_t size, void *ptr, void *expected, void *desired, int success,
    int failure
) {
    if (LGRT_LOCK_FREE(1)) {
        if (size == 1) {
            uint8_t d;

            lgrt_copy(&d, desired, 1);
            return lgrt_atomic_compare_exchange_1(
                ptr, expected, d, success, failure
            );
        }
    }
    if (LGRT_LOCK_FREE(2)) {
        if (size == 2 && lgrt_aligned(ptr, 2)) {
            uint16_t d;

            lgrt_copy(&d, desired, 2);
            return lgrt_atomic_compare_exchange_2(
                ptr, expected, d, success, failure
            );
        }
    }
    if (LGRT_LOCK_FREE(4)) {
        if (size == 4 && lgrt_aligned(ptr, 4)) {
            uint32_t d;

            lgrt_copy(&d, desired, 4);
            return lgrt_atomic_compare_exchange_4(
                ptr, expected, d, success, failure
            );
        }
    }
    if (LGRT_LOCK_FREE(8)) {
        if (size == 8 && lgrt_aligned(ptr, 8)) {
            uint64_t d;

            lgrt_copy(&d, desired, 8);
            return lgrt_atomic_compare_exchange_8(
                ptr, expected, d, success, failure
            );
        }
    }
#if LGRT_HAS_INT128
    if (LGRT_LOCK_FREE(16)) {
        if (size == 16 && lgrt_aligned(ptr, 16)) {
            lgrt_u128 d;

            lgrt_copy(&d, desired, 16);
            return lgrt_atomic_compare_exchange_16(
                ptr, expected, d, success, failure
            );
        }
    }
#endif
    return lgrt_locked_compare_exchange(size, ptr, expected, desired);
}

uint8_t lgrt_atomic_load_1(const volatile void *ptr, int model) {
    uint8_t v;

    if (LGRT_LOCK_FREE(1)) {
        return LGRT_ATOMIC_LOAD((const volatile uint8_t *)ptr, model);
    }
    lgrt_locked_load(1, ptr, &v);
    return v;
}

uint16_t lgrt_atomic_load_2(const volatile void *ptr, int model) {
    uint16_t v;

    if (LGRT_LOCK_FREE(2)) {
        if (lgrt_aligned(ptr, 2)) {
            return LGRT_ATOMIC_LOAD(
                (const volatile lgrt_atomic_u16 *)ptr, model
            );
        }
    }
    lgrt_locked_load(2, ptr, &v);
    return v;
}

uint32_t lgrt_atomic_load_4(const volatile void *ptr, int model) {
    uint32_t v;

    if (LGRT_LOCK_FREE(4)) {
        if (lgrt_aligned(ptr, 4)) {
            return LGRT_ATOMIC_LOAD(
                (const volatile lgrt_atomic_u32 *)ptr, model
            );
        }
    }
    lgrt_locked_load(4, ptr, &v);
    return v;
}

#if defined(__clang__) && __clang_major__ < 9 && defined(__i386__) \
 && !defined(_SOFT_FLOAT)
/*
 * Workaround: Clang before 9, IA-32: it loads 8 bytes with cmpxchg8b, which
 * writes, and so faults where the object is read-only, so there 8 bytes are
 * loaded through the x87 instead, whose 8-byte loads are atomic, and exact for
 * integers.
 */
#define LGRT_X87_LOAD_8 1

static inline uint64_t lgrt_x87_load_8(const volatile void *ptr) {
    uint64_t v;

    __asm__ volatile (
        "fildll %1\n"
        "fistpll %0"
        : "=m"(v)
        : "m"(*(const volatile lgrt_atomic_u64 *)ptr)
        : "memory"
    );
    return v;
}
#else
#define LGRT_X87_LOAD_8 0
#endif

uint64_t lgrt_atomic_load_8(const volatile void *ptr, int model) {
    uint64_t v;

    if (LGRT_LOCK_FREE(8)) {
        if (lgrt_aligned(ptr, 8)) {
#if LGRT_X87_LOAD_8
            (void)model;
            return lgrt_x87_load_8(ptr);
#else
            return __atomic_load_n(
                (const volatile lgrt_atomic_u64 *)ptr, model
            );
#endif
        }
    }
    lgrt_locked_load(8, ptr, &v);
    return v;
}

#if LGRT_HAS_INT128
lgrt_u128 lgrt_atomic_load_16(const volatile void *ptr, int model) {
    lgrt_u128 v;

    if (LGRT_LOCK_FREE(16)) {
        if (lgrt_aligned(ptr, 16)) {
#if LGRT_ATOMIC_HELPERS_16
            return lgrt_load_16(ptr, model);
#else
            return __atomic_load_n(
                (const volatile lgrt_atomic_u128 *)ptr, model
            );
#endif
        }
    }
    lgrt_locked_load(16, ptr, &v);
    return v;
}
#endif

void lgrt_atomic_store_1(volatile void *ptr, uint8_t val, int model) {
    if (LGRT_LOCK_FREE(1)) {
        LGRT_ATOMIC_STORE((volatile uint8_t *)ptr, val, model);
        return;
    }
    lgrt_locked_store(1, ptr, &val);
}

void lgrt_atomic_store_2(volatile void *ptr, uint16_t val, int model) {
    if (LGRT_LOCK_FREE(2)) {
        if (lgrt_aligned(ptr, 2)) {
            LGRT_ATOMIC_STORE((volatile lgrt_atomic_u16 *)ptr, val, model);
            return;
        }
    }
    lgrt_locked_store(2, ptr, &val);
}

void lgrt_atomic_store_4(volatile void *ptr, uint32_t val, int model) {
    if (LGRT_LOCK_FREE(4)) {
        if (lgrt_aligned(ptr, 4)) {
            LGRT_ATOMIC_STORE((volatile lgrt_atomic_u32 *)ptr, val, model);
            return;
        }
    }
    lgrt_locked_store(4, ptr, &val);
}

void lgrt_atomic_store_8(volatile void *ptr, uint64_t val, int model) {
    if (LGRT_LOCK_FREE(8)) {
        if (lgrt_aligned(ptr, 8)) {
            __atomic_store_n((volatile lgrt_atomic_u64 *)ptr, val, model);
            return;
        }
    }
    lgrt_locked_store(8, ptr, &val);
}

#if LGRT_HAS_INT128
void lgrt_atomic_store_16(volatile void *ptr, lgrt_u128 val, int model) {
    if (LGRT_LOCK_FREE(16)) {
        if (lgrt_aligned(ptr, 16)) {
#if LGRT_ATOMIC_HELPERS_16
            lgrt_store_16(ptr, val, model);
#else
            __atomic_store_n((volatile lgrt_atomic_u128 *)ptr, val, model);
#endif
            return;
        }
    }
    lgrt_locked_store(16, ptr, &val);
}
#endif

uint8_t lgrt_atomic_exchange_1(volatile void *ptr, uint8_t val, int model) {
    uint8_t old;

    if (LGRT_LOCK_FREE(1)) {
#if LGRT_WORD_CAS
        (void)model;
        lgrt_word_exchange(ptr, 1, &val, &old);
        return old;
#else
        return __atomic_exchange_n((volatile uint8_t *)ptr, val, model);
#endif
    }
    lgrt_locked_exchange(1, ptr, &val, &old);
    return old;
}

uint16_t lgrt_atomic_exchange_2(volatile void *ptr, uint16_t val, int model) {
    uint16_t old;

    if (LGRT_LOCK_FREE(2)) {
        if (lgrt_aligned(ptr, 2)) {
#if LGRT_WORD_CAS
            (void)model;
            lgrt_word_exchange(ptr, 2, &val, &old);
            return old;
#else
            return __atomic_exchange_n(
                (volatile lgrt_atomic_u16 *)ptr, val, model
            );
#endif
        }
    }
    lgrt_locked_exchange(2, ptr, &val, &old);
    return old;
}

uint32_t lgrt_atomic_exchange_4(volatile void *ptr, uint32_t val, int model) {
    uint32_t old;

    if (LGRT_LOCK_FREE(4)) {
        if (lgrt_aligned(ptr, 4)) {
#if LGRT_WORD_CAS
            (void)model;
            lgrt_word_exchange(ptr, 4, &val, &old);
            return old;
#else
            return __atomic_exchange_n(
                (volatile lgrt_atomic_u32 *)ptr, val, model
            );
#endif
        }
    }
    lgrt_locked_exchange(4, ptr, &val, &old);
    return old;
}

uint64_t lgrt_atomic_exchange_8(volatile void *ptr, uint64_t val, int model) {
    uint64_t old;

    if (LGRT_LOCK_FREE(8)) {
        if (lgrt_aligned(ptr, 8)) {
            return __atomic_exchange_n(
                (volatile lgrt_atomic_u64 *)ptr, val, model
            );
        }
    }
    lgrt_locked_exchange(8, ptr, &val, &old);
    return old;
}

#if LGRT_HAS_INT128
lgrt_u128 lgrt_atomic_exchange_16(
    volatile void *ptr, lgrt_u128 val, int model
) {
    lgrt_u128 old;

    if (LGRT_LOCK_FREE(16)) {
        if (lgrt_aligned(ptr, 16)) {
#if LGRT_ATOMIC_HELPERS_16
            return lgrt_exchange_16(ptr, val, model);
#else
            return __atomic_exchange_n(
                (volatile lgrt_atomic_u128 *)ptr, val, model
            );
#endif
        }
    }
    lgrt_locked_exchange(16, ptr, &val, &old);
    return old;
}
#endif

bool lgrt_atomic_compare_exchange_1(
    volatile void *ptr, void *expected, uint8_t desired, int success,
    int failure
) {
    if (LGRT_LOCK_FREE(1)) {
#if LGRT_WORD_CAS
        (void)success;
        (void)failure;
        return lgrt_word_compare_exchange(ptr, 1, expected, &desired);
#else
        volatile uint8_t *p = ptr;
        uint8_t e;
        bool ok;

        lgrt_copy(&e, expected, 1);
        ok = __atomic_compare_exchange_n(
            p, &e, desired, false, success, failure
        );
        if (ok) {
            return true;
        }
        lgrt_copy(expected, &e, 1);
        return false;
#endif
    }
    return lgrt_locked_compare_exchange(1, ptr, expected, &desired);
}

bool lgrt_atomic_compare_exchange_2(
    volatile void *ptr, void *expected, uint16_t desired, int success,
    int failure
) {
    if (LGRT_LOCK_FREE(2)) {
        if (lgrt_aligned(ptr, 2)) {
#if LGRT_WORD_CAS
            (void)success;
            (void)failure;
            return lgrt_word_compare_exchange(ptr, 2, expected, &desired);
#else
            volatile lgrt_atomic_u16 *p = ptr;
            lgrt_atomic_u16 e;
            bool ok;

            lgrt_copy(&e, expected, 2);
            ok = __atomic_compare_exchange_n(
                p, &e, desired, false, success, failure
            );
            if (ok) {
                return true;
            }
            lgrt_copy(expected, &e, 2);
            return false;
#endif
        }
    }
    return lgrt_locked_compare_exchange(2, ptr, expected, &desired);
}

/*
 * Workaround: Clang before 10.0.1, 64-bit RISC-V: its 4-byte compare-exchanges
 * compare the word they load, which is sign-extended, with the expected one as
 * it comes, which may be zero-extended, and then report that they stored the
 * value that they did not.
 */
#if defined(__clang__) && defined(__riscv) && __riscv_xlen == 64 \
 && defined(__riscv_atomic) \
 && (__clang_major__ < 10 \
  || (__clang_major__ == 10 && __clang_patchlevel__ < 1))
#define LGRT_RISCV64_CAS_4 1

static inline bool lgrt_riscv64_compare_exchange_4(
    volatile void *ptr, void *expected, uint32_t desired
) {
    int32_t e;
    int64_t want;
    int64_t found;
    int64_t failed;

    lgrt_copy(&e, expected, 4);
    want = e;
    __asm__ volatile (
        "1:\n"
        "lr.w.aqrl %0, (%2)\n"
        "bne %0, %3, 2f\n"
        "sc.w.rl %1, %4, (%2)\n"
        "bnez %1, 1b\n"
        "2:"
        : "=&r"(found), "=&r"(failed)
        : "r"(ptr), "r"(want), "r"(desired)
        : "memory"
    );
    if (found == want) {
        return true;
    }
    e = (int32_t)found;
    lgrt_copy(expected, &e, 4);
    return false;
}
#else
#define LGRT_RISCV64_CAS_4 0
#endif

bool lgrt_atomic_compare_exchange_4(
    volatile void *ptr, void *expected, uint32_t desired, int success,
    int failure
) {
    if (LGRT_LOCK_FREE(4)) {
        if (lgrt_aligned(ptr, 4)) {
#if LGRT_RISCV64_CAS_4
            (void)success;
            (void)failure;
            return lgrt_riscv64_compare_exchange_4(ptr, expected, desired);
#elif LGRT_WORD_CAS
            (void)success;
            (void)failure;
            return lgrt_word_compare_exchange(ptr, 4, expected, &desired);
#else
            volatile lgrt_atomic_u32 *p = ptr;
            lgrt_atomic_u32 e;
            bool ok;

            lgrt_copy(&e, expected, 4);
            ok = __atomic_compare_exchange_n(
                p, &e, desired, false, success, failure
            );
            if (ok) {
                return true;
            }
            lgrt_copy(expected, &e, 4);
            return false;
#endif
        }
    }
    return lgrt_locked_compare_exchange(4, ptr, expected, &desired);
}

bool lgrt_atomic_compare_exchange_8(
    volatile void *ptr, void *expected, uint64_t desired, int success,
    int failure
) {
    if (LGRT_LOCK_FREE(8)) {
        if (lgrt_aligned(ptr, 8)) {
            volatile lgrt_atomic_u64 *p = ptr;
            lgrt_atomic_u64 e;
            bool ok;

            lgrt_copy(&e, expected, 8);
            ok = __atomic_compare_exchange_n(
                p, &e, desired, false, success, failure
            );
            if (ok) {
                return true;
            }
            lgrt_copy(expected, &e, 8);
            return false;
        }
    }
    return lgrt_locked_compare_exchange(8, ptr, expected, &desired);
}

#if LGRT_HAS_INT128
bool lgrt_atomic_compare_exchange_16(
    volatile void *ptr, void *expected, lgrt_u128 desired, int success,
    int failure
) {
    if (LGRT_LOCK_FREE(16)) {
        if (lgrt_aligned(ptr, 16)) {
            lgrt_atomic_u128 e;
            bool ok;

            lgrt_copy(&e, expected, 16);
#if LGRT_ATOMIC_HELPERS_16
            ok = lgrt_compare_exchange_16(ptr, &e, desired, success, failure);
#else
            ok = __atomic_compare_exchange_n(
                (volatile lgrt_atomic_u128 *)ptr, &e, desired, false, success,
                failure
            );
#endif
            if (!ok) {
                lgrt_copy(expected, &e, 16);
            }
            return ok;
        }
    }
    return lgrt_locked_compare_exchange(16, ptr, expected, &desired);
}
#endif

#endif

#if LGRT_HAS_ATOMICS

/*
 * These define __atomic_fetch_OP_N for each OP and N. Under the lock, values
 * narrower than int are operated on as unsigned int, as they would otherwise
 * promote to int, whose arithmetic can compile into overflow-checking calls
 * with -ftrapv.
 */

#define LGRT_OP_ADD(x, v) ((x) + (v))
#define LGRT_OP_SUB(x, v) ((x) - (v))
#define LGRT_OP_AND(x, v) ((x) & (v))
#define LGRT_OP_OR(x, v) ((x) | (v))
#define LGRT_OP_XOR(x, v) ((x) ^ (v))
#define LGRT_OP_NAND(x, v) (~((x) & (v)))

/*
 * fetch(op, n) names the builtin, or the function, that the lock-free path
 * calls.
 */
#define LGRT_FETCH_OP(op, apply, n, type, atomic_type, arith_type, fetch) \
    type lgrt_atomic_fetch_##op##_##n( \
        volatile void *ptr, type val, int model \
    ) LGRT_ASM_LABEL(__atomic_fetch_##op##_##n); \
    type lgrt_atomic_fetch_##op##_##n( \
        volatile void *ptr, type val, int model \
    ) { \
        lgrt_lock_word *lock; \
        type x; \
        type y; \
        \
        if (LGRT_LOCK_FREE(n)) { \
            if (lgrt_aligned(ptr, n)) { \
                return fetch(op, n)((volatile atomic_type *)ptr, val, model); \
            } \
        } \
        lock = lgrt_lock_of(ptr); \
        lgrt_lock(lock); \
        lgrt_copy(&x, ptr, n); \
        y = (type)apply((arith_type)x, (arith_type)val); \
        lgrt_copy((void *)ptr, &y, n); \
        lgrt_unlock(lock); \
        return x; \
    }

#define LGRT_FETCH_BUILTIN(op, n) __atomic_fetch_##op

#if LGRT_WORD_CAS
/*
 * The lock-free paths of the routines of up to 4 bytes loop on
 * lgrt_word_compare_exchange instead.
 */
#define LGRT_FETCH_WORD(op, n) lgrt_word_fetch_##op##_##n
#define LGRT_FETCH_OP_WORD(op, apply, n, type, atomic_type) \
    static inline type lgrt_word_fetch_##op##_##n( \
        volatile atomic_type *p, type val, int model \
    ) { \
        type x; \
        type y; \
        \
        (void)model; \
        lgrt_copy(&x, p, n); \
        do { \
            y = (type)apply((uint32_t)x, (uint32_t)val); \
        } while (!lgrt_word_compare_exchange(p, n, &x, &y)); \
        return x; \
    } \
    LGRT_FETCH_OP( \
        op, apply, n, type, atomic_type, uint32_t, LGRT_FETCH_WORD \
    )
#define LGRT_FETCH_OP_NARROW(op, apply, n, type, atomic_type) \
    LGRT_FETCH_OP_WORD(op, apply, n, type, atomic_type)
#define LGRT_FETCH_OP_4(op, apply) \
    LGRT_FETCH_OP_WORD(op, apply, 4, uint32_t, lgrt_atomic_u32)
#elif !defined(__clang__) && __GNUC__ == 16 && __GNUC_MINOR__ == 1 \
 && defined(__mips__)
/*
 * Workaround: GCC 16.1, MIPS: when optimising, it compiles byte and halfword
 * fetch-and-add, -and, -or, and -xor into fetch-nand, so there the lock-free
 * paths of the 1- and 2-byte routines loop on compare-exchanges instead.
 */
#define LGRT_FETCH_CAS(op, n) lgrt_cas_fetch_##op##_##n
#define LGRT_FETCH_OP_NARROW(op, apply, n, type, atomic_type) \
    static inline type lgrt_cas_fetch_##op##_##n( \
        volatile atomic_type *p, type val, int model \
    ) { \
        atomic_type x = __atomic_load_n(p, __ATOMIC_RELAXED); \
        type y; \
        bool done; \
        \
        do { \
            y = (type)apply((unsigned int)x, (unsigned int)val); \
            done = __atomic_compare_exchange_n( \
                p, &x, y, false, model, __ATOMIC_RELAXED \
            ); \
        } while (!done); \
        return x; \
    } \
    LGRT_FETCH_OP( \
        op, apply, n, type, atomic_type, unsigned int, LGRT_FETCH_CAS \
    )
#else
#define LGRT_FETCH_OP_NARROW(op, apply, n, type, atomic_type) \
    LGRT_FETCH_OP( \
        op, apply, n, type, atomic_type, unsigned int, LGRT_FETCH_BUILTIN \
    )
#endif

#if !defined(LGRT_FETCH_OP_4)
#define LGRT_FETCH_OP_4(op, apply) \
    LGRT_FETCH_OP( \
        op, apply, 4, uint32_t, lgrt_atomic_u32, uint32_t, \
        LGRT_FETCH_BUILTIN \
    )
#endif

#if LGRT_ATOMIC_HELPERS_16
/*
 * Where the 16-byte builtins cannot be used, the lock-free paths of the
 * 16-byte routines loop on lgrt_compare_exchange_16 instead.
 */
#define LGRT_FETCH_HELPER(op, n) lgrt_fetch_##op##_##n
#define LGRT_FETCH_OP_16(op, apply) \
    static inline lgrt_u128 lgrt_fetch_##op##_16( \
        volatile void *ptr, lgrt_u128 val, int model \
    ) { \
        lgrt_u128 x = lgrt_load_16(ptr, __ATOMIC_RELAXED); \
        bool done; \
        \
        do { \
            done = lgrt_compare_exchange_16( \
                ptr, &x, apply(x, val), model, __ATOMIC_RELAXED \
            ); \
        } while (!done); \
        return x; \
    } \
    LGRT_FETCH_OP( \
        op, apply, 16, lgrt_u128, lgrt_atomic_u128, lgrt_u128, \
        LGRT_FETCH_HELPER \
    )
#elif LGRT_HAS_INT128
#define LGRT_FETCH_OP_16(op, apply) \
    LGRT_FETCH_OP( \
        op, apply, 16, lgrt_u128, lgrt_atomic_u128, lgrt_u128, \
        LGRT_FETCH_BUILTIN \
    )
#else
#define LGRT_FETCH_OP_16(op, apply)
#endif

#define LGRT_FETCH_OPS(op, apply) \
    LGRT_FETCH_OP_NARROW(op, apply, 1, uint8_t, uint8_t) \
    LGRT_FETCH_OP_NARROW(op, apply, 2, uint16_t, lgrt_atomic_u16) \
    LGRT_FETCH_OP_4(op, apply) \
    LGRT_FETCH_OP( \
        op, apply, 8, uint64_t, lgrt_atomic_u64, uint64_t, \
        LGRT_FETCH_BUILTIN \
    ) \
    LGRT_FETCH_OP_16(op, apply)

LGRT_FETCH_OPS(add, LGRT_OP_ADD)
LGRT_FETCH_OPS(sub, LGRT_OP_SUB)
LGRT_FETCH_OPS(and, LGRT_OP_AND)
LGRT_FETCH_OPS(or, LGRT_OP_OR)
LGRT_FETCH_OPS(xor, LGRT_OP_XOR)
LGRT_FETCH_OPS(nand, LGRT_OP_NAND)

/* The fences where LGRT_WORD_CAS stands in, as the builtins may be wrong. */
#if LGRT_WORD_CAS
#define LGRT_THREAD_FENCE(order) \
    do { \
        (void)(order); \
        lgrt_fence(); \
    } while (0)
#define LGRT_SIGNAL_FENCE(order) \
    do { \
        (void)(order); \
        __asm__ volatile ("" : : : "memory"); \
    } while (0)
#else
#define LGRT_THREAD_FENCE(order) __atomic_thread_fence(order)
#define LGRT_SIGNAL_FENCE(order) __atomic_signal_fence(order)
#endif

#if __STDC_VERSION__ >= 201112 && defined(__has_include)
#if __has_include(<stdatomic.h>)

#include <stdatomic.h>

/*
 * <stdatomic.h> defines these as macros, but programs may also call them as
 * functions. Where LGRT_WORD_CAS stands in, they use the routines, as GCC may
 * make a byte test-and-set a plain load and store, or a library call.
 */

#undef atomic_flag_test_and_set
bool atomic_flag_test_and_set(volatile atomic_flag *object);
bool atomic_flag_test_and_set(volatile atomic_flag *object) {
#if LGRT_WORD_CAS
    return lgrt_atomic_exchange_1(
        (volatile void *)object, __GCC_ATOMIC_TEST_AND_SET_TRUEVAL,
        __ATOMIC_SEQ_CST
    ) != 0;
#else
    return __atomic_test_and_set((volatile void *)object, __ATOMIC_SEQ_CST);
#endif
}

#undef atomic_flag_test_and_set_explicit
bool atomic_flag_test_and_set_explicit(
    volatile atomic_flag *object, memory_order order
);
bool atomic_flag_test_and_set_explicit(
    volatile atomic_flag *object, memory_order order
) {
#if LGRT_WORD_CAS
    return lgrt_atomic_exchange_1(
        (volatile void *)object, __GCC_ATOMIC_TEST_AND_SET_TRUEVAL, order
    ) != 0;
#else
    return __atomic_test_and_set((volatile void *)object, order);
#endif
}

#undef atomic_flag_clear
void atomic_flag_clear(volatile atomic_flag *object);
void atomic_flag_clear(volatile atomic_flag *object) {
#if LGRT_WORD_CAS
    lgrt_atomic_store_1((volatile void *)object, 0, __ATOMIC_SEQ_CST);
#else
    __atomic_clear((volatile void *)object, __ATOMIC_SEQ_CST);
#endif
}

#undef atomic_flag_clear_explicit
void atomic_flag_clear_explicit(
    volatile atomic_flag *object, memory_order order
);
void atomic_flag_clear_explicit(
    volatile atomic_flag *object, memory_order order
) {
#if LGRT_WORD_CAS
    lgrt_atomic_store_1((volatile void *)object, 0, order);
#else
    __atomic_clear((volatile void *)object, order);
#endif
}

#undef atomic_thread_fence
void atomic_thread_fence(memory_order order);
void atomic_thread_fence(memory_order order) {
    LGRT_THREAD_FENCE(order);
}

#undef atomic_signal_fence
void atomic_signal_fence(memory_order order);
void atomic_signal_fence(memory_order order) {
    LGRT_SIGNAL_FENCE(order);
}

#endif
#endif

/*
 * Compilers call these for the __sync builtins, on the sizes they have no
 * inline code for, and on some targets for the __atomic builtins too.
 */

#define LGRT_SYNC_FETCH(op, apply, n, type) \
    type lgrt_sync_fetch_and_##op##_##n( \
        volatile void *ptr, type val \
    ) LGRT_ASM_LABEL(__sync_fetch_and_##op##_##n); \
    type lgrt_sync_fetch_and_##op##_##n(volatile void *ptr, type val) { \
        return lgrt_atomic_fetch_##op##_##n(ptr, val, __ATOMIC_SEQ_CST); \
    } \
    \
    type lgrt_sync_##op##_and_fetch_##n( \
        volatile void *ptr, type val \
    ) LGRT_ASM_LABEL(__sync_##op##_and_fetch_##n); \
    type lgrt_sync_##op##_and_fetch_##n(volatile void *ptr, type val) { \
        type x = lgrt_atomic_fetch_##op##_##n(ptr, val, __ATOMIC_SEQ_CST); \
        \
        return (type)apply((lgrt_sync_wide_##n)x, (lgrt_sync_wide_##n)val); \
    }

#define LGRT_SYNC_SIZE(n, type) \
    LGRT_SYNC_FETCH(add, LGRT_OP_ADD, n, type) \
    LGRT_SYNC_FETCH(sub, LGRT_OP_SUB, n, type) \
    LGRT_SYNC_FETCH(and, LGRT_OP_AND, n, type) \
    LGRT_SYNC_FETCH(or, LGRT_OP_OR, n, type) \
    LGRT_SYNC_FETCH(xor, LGRT_OP_XOR, n, type) \
    LGRT_SYNC_FETCH(nand, LGRT_OP_NAND, n, type) \
    \
    type lgrt_sync_val_compare_and_swap_##n( \
        volatile void *ptr, type expected, type desired \
    ) LGRT_ASM_LABEL(__sync_val_compare_and_swap_##n); \
    type lgrt_sync_val_compare_and_swap_##n( \
        volatile void *ptr, type expected, type desired \
    ) { \
        lgrt_atomic_compare_exchange_##n( \
            ptr, &expected, desired, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST \
        ); \
        return expected; \
    } \
    \
    bool lgrt_sync_bool_compare_and_swap_##n( \
        volatile void *ptr, type expected, type desired \
    ) LGRT_ASM_LABEL(__sync_bool_compare_and_swap_##n); \
    bool lgrt_sync_bool_compare_and_swap_##n( \
        volatile void *ptr, type expected, type desired \
    ) { \
        return lgrt_atomic_compare_exchange_##n( \
            ptr, &expected, desired, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST \
        ); \
    } \
    \
    type lgrt_sync_lock_test_and_set_##n( \
        volatile void *ptr, type val \
    ) LGRT_ASM_LABEL(__sync_lock_test_and_set_##n); \
    type lgrt_sync_lock_test_and_set_##n(volatile void *ptr, type val) { \
        return lgrt_atomic_exchange_##n(ptr, val, __ATOMIC_ACQUIRE); \
    } \
    \
    void lgrt_sync_lock_release_##n( \
        volatile void *ptr \
    ) LGRT_ASM_LABEL(__sync_lock_release_##n); \
    void lgrt_sync_lock_release_##n(volatile void *ptr) { \
        lgrt_atomic_store_##n(ptr, 0, __ATOMIC_RELEASE); \
    }

/*
 * Values narrower than int are operated on as unsigned int, for the reason of
 * the routines above.
 */
typedef unsigned int lgrt_sync_wide_1;
typedef unsigned int lgrt_sync_wide_2;
typedef uint32_t lgrt_sync_wide_4;
typedef uint64_t lgrt_sync_wide_8;

LGRT_SYNC_SIZE(1, uint8_t)
LGRT_SYNC_SIZE(2, uint16_t)
LGRT_SYNC_SIZE(4, uint32_t)
LGRT_SYNC_SIZE(8, uint64_t)

#if LGRT_HAS_INT128
typedef lgrt_u128 lgrt_sync_wide_16;

LGRT_SYNC_SIZE(16, lgrt_u128)
#endif

#if LGRT_WORD_CAS
void lgrt_sync_synchronize(void) LGRT_ASM_LABEL(__sync_synchronize);
void lgrt_sync_synchronize(void) {
    lgrt_fence();
}
#elif defined(__mips16)
/* GCC calls this for the fences of MIPS16, which no instruction does. */
__attribute__((__nomips16__))
void lgrt_sync_synchronize(void) LGRT_ASM_LABEL(__sync_synchronize);
__attribute__((__nomips16__))
void lgrt_sync_synchronize(void) {
    __asm__ volatile ("sync" : : : "memory");
}
#endif

#endif

#if defined(__aarch64__)

/*
 * Programs set this at startup if the CPU has the Large System Extension, so
 * that the routines below use its instructions instead of exclusive loops.
 */
extern bool __aarch64_have_lse_atomics
    __attribute__((__visibility__("hidden")));
bool __aarch64_have_lse_atomics = false;

/*
 * With outline atomics, atomic builtins compile into calls to the routines
 * below, so these use inline assembly instead. Older assemblers lack the LSE
 * mnemonics, so those instructions are encoded with .inst, on the registers
 * the arguments arrive in, bound with register variables. In hex, they are
 *
 *     CAS:            S8A0Rc41, with Rs = 0, Rt = 1, and Rn = 2
 *     CASP:           48A0Rc82, with Rs = 0, Rt = 2, and Rn = 4
 *     LD<op> and SWP: S8A0O020, with Rs = Rt = 0 and Rn = 1
 *
 * where S encodes the size, A and R the ordering, and O the operation. Each
 * order's row below gives A (and R), the stems of the exclusive load and
 * store, and the barrier that follows the exclusive loop.
 */

/*
 * Callers may leave garbage above narrow arguments, so the loop compares a
 * zero-extended copy.
 */
#define LGRT_AARCH64_CAS( \
    n, type, wide, reg, sfx, size, order, lse_a, lse_r, ldx, stx, fence \
) \
    type __aarch64_cas##n##_##order( \
        type expected, type desired, volatile void *ptr \
    ); \
    type __aarch64_cas##n##_##order( \
        type expected, type desired, volatile void *ptr \
    ) { \
        uint64_t addr = (uintptr_t)ptr; \
        \
        if (__aarch64_have_lse_atomics) { \
            register type r0 __asm__ (reg "0") = expected; \
            register type r1 __asm__ (reg "1") = desired; \
            register uint64_t r2 __asm__ ("x2") = addr; \
            \
            __asm__ volatile ( \
                ".inst 0x" size "8" lse_a "0" lse_r "c41" \
                : "+r"(r0) \
                : "r"(r1), "r"(r2) \
                : "memory" \
            ); \
            return r0; \
        } else { \
            wide ext = expected; \
            type old; \
            uint32_t status; \
            \
            __asm__ volatile ( \
                "1:\n" \
                ldx "r" sfx " %" reg "[old], [%[addr]]\n" \
                "cmp %" reg "[old], %" reg "[ext]\n" \
                "b.ne 2f\n" \
                stx "r" sfx " %w[status], %" reg "[desired], [%[addr]]\n" \
                "cbnz %w[status], 1b\n" \
                "2:\n" \
                fence \
                : [old] "=&r"(old), [status] "=&r"(status) \
                : [ext] "r"(ext), [desired] "r"(desired), [addr] "r"(addr) \
                : "cc", "memory" \
            ); \
            return old; \
        } \
    }

#define LGRT_AARCH64_CAS_ORDERS(n, type, wide, reg, sfx, size) \
    LGRT_AARCH64_CAS( \
        n, type, wide, reg, sfx, size, relax, "a", "7", "ldx", "stx", "" \
    ) \
    LGRT_AARCH64_CAS( \
        n, type, wide, reg, sfx, size, acq, "e", "7", "ldax", "stx", "" \
    ) \
    LGRT_AARCH64_CAS( \
        n, type, wide, reg, sfx, size, rel, "a", "f", "ldx", "stlx", "" \
    ) \
    LGRT_AARCH64_CAS( \
        n, type, wide, reg, sfx, size, acq_rel, "e", "f", "ldax", "stlx", "" \
    ) \
    LGRT_AARCH64_CAS( \
        n, type, wide, reg, sfx, size, sync, "e", "f", "ldx", "stlx", \
        "dmb ish\n" \
    )

LGRT_AARCH64_CAS_ORDERS(1, uint8_t, uint32_t, "w", "b", "0")
LGRT_AARCH64_CAS_ORDERS(2, uint16_t, uint32_t, "w", "h", "4")
LGRT_AARCH64_CAS_ORDERS(4, uint32_t, uint32_t, "w", "", "8")
LGRT_AARCH64_CAS_ORDERS(8, uint64_t, uint64_t, "x", "", "c")

#if LGRT_HAS_INT128

/*
 * casp and the exclusive pair instructions hold the doubleword at the lower
 * address in the first register of a pair, which is the high half on
 * big-endian targets.
 */
#if defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define LGRT_AARCH64_FIRST_SHIFT 64
#define LGRT_AARCH64_SECOND_SHIFT 0
#else
#define LGRT_AARCH64_FIRST_SHIFT 0
#define LGRT_AARCH64_SECOND_SHIFT 64
#endif

static inline uint64_t lgrt_aarch64_first(lgrt_u128 x) {
    return (uint64_t)(x >> LGRT_AARCH64_FIRST_SHIFT);
}

static inline uint64_t lgrt_aarch64_second(lgrt_u128 x) {
    return (uint64_t)(x >> LGRT_AARCH64_SECOND_SHIFT);
}

static inline lgrt_u128 lgrt_aarch64_pair(uint64_t first, uint64_t second) {
    return ((lgrt_u128)first << LGRT_AARCH64_FIRST_SHIFT)
        | ((lgrt_u128)second << LGRT_AARCH64_SECOND_SHIFT);
}

/*
 * A 16-byte exclusive load is only single-copy atomic if the store-exclusive
 * after it succeeds, so on a mismatch the loop stores the loaded pair back.
 */
#define LGRT_AARCH64_CAS16(order, lse_a, lse_r, ldx, stx, fence) \
    lgrt_u128 __aarch64_cas16_##order( \
        lgrt_u128 expected, lgrt_u128 desired, volatile void *ptr \
    ); \
    lgrt_u128 __aarch64_cas16_##order( \
        lgrt_u128 expected, lgrt_u128 desired, volatile void *ptr \
    ) { \
        uint64_t addr = (uintptr_t)ptr; \
        uint64_t e0 = lgrt_aarch64_first(expected); \
        uint64_t e1 = lgrt_aarch64_second(expected); \
        uint64_t d0 = lgrt_aarch64_first(desired); \
        uint64_t d1 = lgrt_aarch64_second(desired); \
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
            return lgrt_aarch64_pair(r0, r1); \
        } else { \
            uint64_t o0; \
            uint64_t o1; \
            uint64_t n0; \
            uint64_t n1; \
            uint32_t status; \
            \
            __asm__ volatile ( \
                "1:\n" \
                ldx "p %[o0], %[o1], [%[addr]]\n" \
                "cmp %[o0], %[e0]\n" \
                "ccmp %[o1], %[e1], #0, eq\n" \
                "csel %[n0], %[d0], %[o0], eq\n" \
                "csel %[n1], %[d1], %[o1], eq\n" \
                stx "p %w[status], %[n0], %[n1], [%[addr]]\n" \
                "cbnz %w[status], 1b\n" \
                fence \
                : [o0] "=&r"(o0), [o1] "=&r"(o1), [n0] "=&r"(n0), \
                    [n1] "=&r"(n1), [status] "=&r"(status) \
                : [e0] "r"(e0), [e1] "r"(e1), [d0] "r"(d0), [d1] "r"(d1), \
                    [addr] "r"(addr) \
                : "cc", "memory" \
            ); \
            return lgrt_aarch64_pair(o0, o1); \
        } \
    }

LGRT_AARCH64_CAS16(relax, "2", "7", "ldx", "stx", "")
LGRT_AARCH64_CAS16(acq, "6", "7", "ldax", "stx", "")
LGRT_AARCH64_CAS16(rel, "2", "f", "ldx", "stlx", "")
LGRT_AARCH64_CAS16(acq_rel, "6", "f", "ldax", "stlx", "")
LGRT_AARCH64_CAS16(sync, "6", "f", "ldx", "stlx", "dmb ish\n")

#endif

#define LGRT_AARCH64_SWP( \
    n, type, reg, sfx, size, order, lse_a, ldx, stx, fence \
) \
    type __aarch64_swp##n##_##order(type val, volatile void *ptr); \
    type __aarch64_swp##n##_##order(type val, volatile void *ptr) { \
        uint64_t addr = (uintptr_t)ptr; \
        \
        if (__aarch64_have_lse_atomics) { \
            register type r0 __asm__ (reg "0") = val; \
            register uint64_t r1 __asm__ ("x1") = addr; \
            \
            __asm__ volatile ( \
                ".inst 0x" size "8" lse_a "08020" \
                : "+r"(r0) \
                : "r"(r1) \
                : "memory" \
            ); \
            return r0; \
        } else { \
            type old; \
            uint32_t status; \
            \
            __asm__ volatile ( \
                "1:\n" \
                ldx "r" sfx " %" reg "[old], [%[addr]]\n" \
                stx "r" sfx " %w[status], %" reg "[val], [%[addr]]\n" \
                "cbnz %w[status], 1b\n" \
                fence \
                : [old] "=&r"(old), [status] "=&r"(status) \
                : [val] "r"(val), [addr] "r"(addr) \
                : "memory" \
            ); \
            return old; \
        } \
    }

/* A __sync lock test-and-set is only an acquire barrier. */
#define LGRT_AARCH64_SWP_ORDERS(n, type, reg, sfx, size) \
    LGRT_AARCH64_SWP(n, type, reg, sfx, size, relax, "2", "ldx", "stx", "") \
    LGRT_AARCH64_SWP(n, type, reg, sfx, size, acq, "a", "ldax", "stx", "") \
    LGRT_AARCH64_SWP(n, type, reg, sfx, size, rel, "6", "ldx", "stlx", "") \
    LGRT_AARCH64_SWP( \
        n, type, reg, sfx, size, acq_rel, "e", "ldax", "stlx", "" \
    ) \
    LGRT_AARCH64_SWP( \
        n, type, reg, sfx, size, sync, "a", "ldx", "stx", "dmb ish\n" \
    )

LGRT_AARCH64_SWP_ORDERS(1, uint8_t, "w", "b", "3")
LGRT_AARCH64_SWP_ORDERS(2, uint16_t, "w", "h", "7")
LGRT_AARCH64_SWP_ORDERS(4, uint32_t, "w", "", "b")
LGRT_AARCH64_SWP_ORDERS(8, uint64_t, "x", "", "f")

#define LGRT_AARCH64_LDOP( \
    op, opc, insn, n, type, reg, sfx, size, order, lse_a, ldx, stx, fence \
) \
    type __aarch64_##op##n##_##order(type val, volatile void *ptr); \
    type __aarch64_##op##n##_##order(type val, volatile void *ptr) { \
        uint64_t addr = (uintptr_t)ptr; \
        \
        if (__aarch64_have_lse_atomics) { \
            register type r0 __asm__ (reg "0") = val; \
            register uint64_t r1 __asm__ ("x1") = addr; \
            \
            __asm__ volatile ( \
                ".inst 0x" size "8" lse_a "0" opc "020" \
                : "+r"(r0) \
                : "r"(r1) \
                : "memory" \
            ); \
            return r0; \
        } else { \
            type old; \
            type next; \
            uint32_t status; \
            \
            __asm__ volatile ( \
                "1:\n" \
                ldx "r" sfx " %" reg "[old], [%[addr]]\n" \
                insn " %" reg "[next], %" reg "[old], %" reg "[val]\n" \
                stx "r" sfx " %w[status], %" reg "[next], [%[addr]]\n" \
                "cbnz %w[status], 1b\n" \
                fence \
                : [old] "=&r"(old), [next] "=&r"(next), \
                    [status] "=&r"(status) \
                : [val] "r"(val), [addr] "r"(addr) \
                : "memory" \
            ); \
            return old; \
        } \
    }

#define LGRT_AARCH64_LDOP_ORDERS(op, opc, insn, n, type, reg, sfx, size) \
    LGRT_AARCH64_LDOP( \
        op, opc, insn, n, type, reg, sfx, size, relax, "2", "ldx", "stx", "" \
    ) \
    LGRT_AARCH64_LDOP( \
        op, opc, insn, n, type, reg, sfx, size, acq, "a", "ldax", "stx", "" \
    ) \
    LGRT_AARCH64_LDOP( \
        op, opc, insn, n, type, reg, sfx, size, rel, "6", "ldx", "stlx", "" \
    ) \
    LGRT_AARCH64_LDOP( \
        op, opc, insn, n, type, reg, sfx, size, acq_rel, "e", "ldax", "stlx", \
        "" \
    ) \
    LGRT_AARCH64_LDOP( \
        op, opc, insn, n, type, reg, sfx, size, sync, "e", "ldx", "stlx", \
        "dmb ish\n" \
    )

#define LGRT_AARCH64_LDOP_SIZES(op, opc, insn) \
    LGRT_AARCH64_LDOP_ORDERS(op, opc, insn, 1, uint8_t, "w", "b", "3") \
    LGRT_AARCH64_LDOP_ORDERS(op, opc, insn, 2, uint16_t, "w", "h", "7") \
    LGRT_AARCH64_LDOP_ORDERS(op, opc, insn, 4, uint32_t, "w", "", "b") \
    LGRT_AARCH64_LDOP_ORDERS(op, opc, insn, 8, uint64_t, "x", "", "f")

LGRT_AARCH64_LDOP_SIZES(ldadd, "0", "add")
LGRT_AARCH64_LDOP_SIZES(ldclr, "1", "bic")
LGRT_AARCH64_LDOP_SIZES(ldeor, "2", "eor")
LGRT_AARCH64_LDOP_SIZES(ldset, "3", "orr")

#endif

#if defined(__riscv) && defined(__riscv_xlen) \
 && (__riscv_xlen == 32 || __riscv_xlen == 64)

/*
 * With -msave-restore, prologues call __riscv_save_N with the return address
 * in t0, and epilogues jump to __riscv_restore_N, to save and restore ra and
 * s0 to s(N - 1). The frame is laid out as the compilers' unwind information
 * and frame accesses expect: N + 1 words, rounded up to 16 bytes except with
 * the E ABIs, with ra in the top word and the s registers in order below it.
 * Entry points whose frames have the same size share code that fills the whole
 * frame, as the compilers leave the extra slots alone and the extra registers
 * unchanged.
 */

#if __riscv_xlen == 64
#define LGRT_RISCV_WORD "8"
#define LGRT_RISCV_STORE "sd"
#define LGRT_RISCV_LOAD "ld"
#else
#define LGRT_RISCV_WORD "4"
#define LGRT_RISCV_STORE "sw"
#define LGRT_RISCV_LOAD "lw"
#endif

/*
 * LGRT_RISCV_REGSn applies op to ra and s0 to s(n - 2), in the top n words of
 * an f-byte frame.
 */
#define LGRT_RISCV_SLOT(op, reg, f, k) \
    op " " reg ", " #f "-" #k "*" LGRT_RISCV_WORD "(sp)\n"
#define LGRT_RISCV_REGS1(op, f) LGRT_RISCV_SLOT(op, "ra", f, 1)
#define LGRT_RISCV_REGS2(op, f) \
    LGRT_RISCV_REGS1(op, f) \
    LGRT_RISCV_SLOT(op, "s0", f, 2)
#define LGRT_RISCV_REGS3(op, f) \
    LGRT_RISCV_REGS2(op, f) \
    LGRT_RISCV_SLOT(op, "s1", f, 3)
#define LGRT_RISCV_REGS4(op, f) \
    LGRT_RISCV_REGS3(op, f) \
    LGRT_RISCV_SLOT(op, "s2", f, 4)
#define LGRT_RISCV_REGS5(op, f) \
    LGRT_RISCV_REGS4(op, f) \
    LGRT_RISCV_SLOT(op, "s3", f, 5)
#define LGRT_RISCV_REGS6(op, f) \
    LGRT_RISCV_REGS5(op, f) \
    LGRT_RISCV_SLOT(op, "s4", f, 6)
#define LGRT_RISCV_REGS7(op, f) \
    LGRT_RISCV_REGS6(op, f) \
    LGRT_RISCV_SLOT(op, "s5", f, 7)
#define LGRT_RISCV_REGS8(op, f) \
    LGRT_RISCV_REGS7(op, f) \
    LGRT_RISCV_SLOT(op, "s6", f, 8)
#define LGRT_RISCV_REGS9(op, f) \
    LGRT_RISCV_REGS8(op, f) \
    LGRT_RISCV_SLOT(op, "s7", f, 9)
#define LGRT_RISCV_REGS10(op, f) \
    LGRT_RISCV_REGS9(op, f) \
    LGRT_RISCV_SLOT(op, "s8", f, 10)
#define LGRT_RISCV_REGS11(op, f) \
    LGRT_RISCV_REGS10(op, f) \
    LGRT_RISCV_SLOT(op, "s9", f, 11)
#define LGRT_RISCV_REGS12(op, f) \
    LGRT_RISCV_REGS11(op, f) \
    LGRT_RISCV_SLOT(op, "s10", f, 12)
#define LGRT_RISCV_REGS13(op, f) \
    LGRT_RISCV_REGS12(op, f) \
    LGRT_RISCV_SLOT(op, "s11", f, 13)

/* An entry point's code ends where the code for its frame size does. */
#define LGRT_RISCV_ENTRY(kind, n, f) \
    ".globl __riscv_" #kind "_" #n "\n" \
    ".hidden __riscv_" #kind "_" #n "\n" \
    ".type __riscv_" #kind "_" #n ", @function\n" \
    "__riscv_" #kind "_" #n ":\n" \
    ".size __riscv_" #kind "_" #n ", " \
    ".Llgrt_riscv_" #kind "_" #f " - __riscv_" #kind "_" #n "\n"

#define LGRT_RISCV_SAVE(f, n) \
    "addi sp, sp, -" #f "\n" \
    LGRT_RISCV_REGS##n(LGRT_RISCV_STORE, f) \
    "jr t0\n" \
    ".Llgrt_riscv_save_" #f ":\n"

#define LGRT_RISCV_RESTORE(f, n) \
    LGRT_RISCV_REGS##n(LGRT_RISCV_LOAD, f) \
    "addi sp, sp, " #f "\n" \
    "ret\n" \
    ".Llgrt_riscv_restore_" #f ":\n"

/*
 * Instructions need 2-byte alignment with the C extension, and 4-byte
 * alignment without.
 */
#if defined(__riscv_compressed)
#define LGRT_RISCV_ALIGN ".p2align 1\n"
#else
#define LGRT_RISCV_ALIGN ".p2align 2\n"
#endif

/*
 * Each group of entry points that share code(f, n), for an f-byte frame
 * holding n registers, is a statement of its own, in a section named after its
 * first entry point, so that linking with --gc-sections drops the unused
 * groups.
 */
#define LGRT_RISCV_GROUP(kind, first, text) \
    __asm__ ( \
        ".pushsection .text.__riscv_" #kind "_" #first ",\"ax\",@progbits\n" \
        LGRT_RISCV_ALIGN \
        text \
        ".popsection\n" \
    );

#define LGRT_RISCV_GROUP1(kind, code, a, f, n) \
    LGRT_RISCV_GROUP(kind, a, LGRT_RISCV_ENTRY(kind, a, f) code(f, n))

#define LGRT_RISCV_GROUP2(kind, code, a, b, f, n) \
    LGRT_RISCV_GROUP( \
        kind, a, \
        LGRT_RISCV_ENTRY(kind, a, f) LGRT_RISCV_ENTRY(kind, b, f) code(f, n) \
    )

#define LGRT_RISCV_GROUP4(kind, code, a, b, c, d, f, n) \
    LGRT_RISCV_GROUP( \
        kind, a, \
        LGRT_RISCV_ENTRY(kind, a, f) LGRT_RISCV_ENTRY(kind, b, f) \
            LGRT_RISCV_ENTRY(kind, c, f) LGRT_RISCV_ENTRY(kind, d, f) \
            code(f, n) \
    )

#if defined(__riscv_abi_rve) && __riscv_xlen == 32
#define LGRT_RISCV_ROUTINES(kind, code) \
    LGRT_RISCV_GROUP1(kind, code, 0, 4, 1) \
    LGRT_RISCV_GROUP1(kind, code, 1, 8, 2) \
    LGRT_RISCV_GROUP1(kind, code, 2, 12, 3)
#elif defined(__riscv_abi_rve)
#define LGRT_RISCV_ROUTINES(kind, code) \
    LGRT_RISCV_GROUP1(kind, code, 0, 8, 1) \
    LGRT_RISCV_GROUP1(kind, code, 1, 16, 2) \
    LGRT_RISCV_GROUP1(kind, code, 2, 24, 3)
#elif __riscv_xlen == 32
#define LGRT_RISCV_ROUTINES(kind, code) \
    LGRT_RISCV_GROUP4(kind, code, 0, 1, 2, 3, 16, 4) \
    LGRT_RISCV_GROUP4(kind, code, 4, 5, 6, 7, 32, 8) \
    LGRT_RISCV_GROUP4(kind, code, 8, 9, 10, 11, 48, 12) \
    LGRT_RISCV_GROUP1(kind, code, 12, 64, 13)
#else
#define LGRT_RISCV_ROUTINES(kind, code) \
    LGRT_RISCV_GROUP2(kind, code, 0, 1, 16, 2) \
    LGRT_RISCV_GROUP2(kind, code, 2, 3, 32, 4) \
    LGRT_RISCV_GROUP2(kind, code, 4, 5, 48, 6) \
    LGRT_RISCV_GROUP2(kind, code, 6, 7, 64, 8) \
    LGRT_RISCV_GROUP2(kind, code, 8, 9, 80, 10) \
    LGRT_RISCV_GROUP2(kind, code, 10, 11, 96, 12) \
    LGRT_RISCV_GROUP1(kind, code, 12, 112, 13)
#endif

LGRT_RISCV_ROUTINES(save, LGRT_RISCV_SAVE)
LGRT_RISCV_ROUTINES(restore, LGRT_RISCV_RESTORE)

#endif

/*
 * The C23 bit utilities. Those that count or skip ones work on the complement.
 * The builtins are undefined for zero, which is handled first, and narrow
 * types promote to unsigned int, whose extra width the leading counts
 * subtract.
 */

#define LGRT_STDC_BITS(type) ((unsigned int)(sizeof(type) * __CHAR_BIT__))

/*
 * Expands f for each type, with the type it promotes to and that type's
 * builtins.
 */
#define LGRT_STDC_TYPES(f) \
    f(uc, unsigned char, unsigned int, __builtin_clz, __builtin_ctz) \
    f(us, unsigned short, unsigned int, __builtin_clz, __builtin_ctz) \
    f(ui, unsigned int, unsigned int, __builtin_clz, __builtin_ctz) \
    f(ul, unsigned long, unsigned long, __builtin_clzl, __builtin_ctzl) \
    f( \
        ull, unsigned long long, unsigned long long, __builtin_clzll, \
        __builtin_ctzll \
    )

/* These count the leading and trailing zeros of nonzero values. */
#define LGRT_STDC_COUNTS(sfx, type, wide, clz, ctz) \
    static inline unsigned int lgrt_stdc_clz_##sfx(type x) { \
        return (unsigned int)clz((wide)x) \
            - (LGRT_STDC_BITS(wide) - LGRT_STDC_BITS(type)); \
    } \
    \
    static inline unsigned int lgrt_stdc_ctz_##sfx(type x) { \
        return (unsigned int)ctz((wide)x); \
    }

LGRT_STDC_TYPES(LGRT_STDC_COUNTS)

#define LGRT_STDC_LEADING_ZEROS(sfx, type, wide, clz, ctz) \
    unsigned int stdc_leading_zeros_##sfx(type value); \
    unsigned int stdc_leading_zeros_##sfx(type value) { \
        return value == 0 ? LGRT_STDC_BITS(type) \
            : lgrt_stdc_clz_##sfx(value); \
    }

LGRT_STDC_TYPES(LGRT_STDC_LEADING_ZEROS)

#define LGRT_STDC_LEADING_ONES(sfx, type, wide, clz, ctz) \
    unsigned int stdc_leading_ones_##sfx(type value); \
    unsigned int stdc_leading_ones_##sfx(type value) { \
        type x = (type)~(wide)value; \
        \
        return x == 0 ? LGRT_STDC_BITS(type) : lgrt_stdc_clz_##sfx(x); \
    }

LGRT_STDC_TYPES(LGRT_STDC_LEADING_ONES)

#define LGRT_STDC_TRAILING_ZEROS(sfx, type, wide, clz, ctz) \
    unsigned int stdc_trailing_zeros_##sfx(type value); \
    unsigned int stdc_trailing_zeros_##sfx(type value) { \
        return value == 0 ? LGRT_STDC_BITS(type) \
            : lgrt_stdc_ctz_##sfx(value); \
    }

LGRT_STDC_TYPES(LGRT_STDC_TRAILING_ZEROS)

#define LGRT_STDC_TRAILING_ONES(sfx, type, wide, clz, ctz) \
    unsigned int stdc_trailing_ones_##sfx(type value); \
    unsigned int stdc_trailing_ones_##sfx(type value) { \
        type x = (type)~(wide)value; \
        \
        return x == 0 ? LGRT_STDC_BITS(type) : lgrt_stdc_ctz_##sfx(x); \
    }

LGRT_STDC_TYPES(LGRT_STDC_TRAILING_ONES)

#define LGRT_STDC_FIRST_LEADING_ZERO(sfx, type, wide, clz, ctz) \
    unsigned int stdc_first_leading_zero_##sfx(type value); \
    unsigned int stdc_first_leading_zero_##sfx(type value) { \
        type x = (type)~(wide)value; \
        \
        return x == 0 ? 0 : lgrt_stdc_clz_##sfx(x) + 1; \
    }

LGRT_STDC_TYPES(LGRT_STDC_FIRST_LEADING_ZERO)

#define LGRT_STDC_FIRST_LEADING_ONE(sfx, type, wide, clz, ctz) \
    unsigned int stdc_first_leading_one_##sfx(type value); \
    unsigned int stdc_first_leading_one_##sfx(type value) { \
        return value == 0 ? 0 : lgrt_stdc_clz_##sfx(value) + 1; \
    }

LGRT_STDC_TYPES(LGRT_STDC_FIRST_LEADING_ONE)

#define LGRT_STDC_FIRST_TRAILING_ZERO(sfx, type, wide, clz, ctz) \
    unsigned int stdc_first_trailing_zero_##sfx(type value); \
    unsigned int stdc_first_trailing_zero_##sfx(type value) { \
        type x = (type)~(wide)value; \
        \
        return x == 0 ? 0 : lgrt_stdc_ctz_##sfx(x) + 1; \
    }

LGRT_STDC_TYPES(LGRT_STDC_FIRST_TRAILING_ZERO)

#define LGRT_STDC_FIRST_TRAILING_ONE(sfx, type, wide, clz, ctz) \
    unsigned int stdc_first_trailing_one_##sfx(type value); \
    unsigned int stdc_first_trailing_one_##sfx(type value) { \
        return value == 0 ? 0 : lgrt_stdc_ctz_##sfx(value) + 1; \
    }

LGRT_STDC_TYPES(LGRT_STDC_FIRST_TRAILING_ONE)

/*
 * Expands f for each type, with the type it promotes to and that type's
 * popcount builtin.
 */
#define LGRT_STDC_POPCOUNT_TYPES(f) \
    f(uc, unsigned char, unsigned int, __builtin_popcount) \
    f(us, unsigned short, unsigned int, __builtin_popcount) \
    f(ui, unsigned int, unsigned int, __builtin_popcount) \
    f(ul, unsigned long, unsigned long, __builtin_popcountl) \
    f(ull, unsigned long long, unsigned long long, __builtin_popcountll)

#define LGRT_STDC_POPCOUNT(sfx, type, wide, popcount) \
    static inline unsigned int lgrt_stdc_popcount_##sfx(type x) { \
        return (unsigned int)popcount((wide)x); \
    }

LGRT_STDC_POPCOUNT_TYPES(LGRT_STDC_POPCOUNT)

/* These give the index of the most significant one of nonzero values. */
#define LGRT_STDC_MSB(sfx, type, wide, clz, ctz) \
    static inline unsigned int lgrt_stdc_msb_##sfx(type x) { \
        return LGRT_STDC_BITS(wide) - 1 - (unsigned int)clz((wide)x); \
    }

LGRT_STDC_TYPES(LGRT_STDC_MSB)

#define LGRT_STDC_COUNT_ZEROS(sfx, type, wide, clz, ctz) \
    unsigned int stdc_count_zeros_##sfx(type value); \
    unsigned int stdc_count_zeros_##sfx(type value) { \
        return LGRT_STDC_BITS(type) - lgrt_stdc_popcount_##sfx(value); \
    }

LGRT_STDC_TYPES(LGRT_STDC_COUNT_ZEROS)

#define LGRT_STDC_COUNT_ONES(sfx, type, wide, clz, ctz) \
    unsigned int stdc_count_ones_##sfx(type value); \
    unsigned int stdc_count_ones_##sfx(type value) { \
        return lgrt_stdc_popcount_##sfx(value); \
    }

LGRT_STDC_TYPES(LGRT_STDC_COUNT_ONES)

#define LGRT_STDC_HAS_SINGLE_BIT(sfx, type, wide, clz, ctz) \
    bool stdc_has_single_bit_##sfx(type value); \
    bool stdc_has_single_bit_##sfx(type value) { \
        return value != 0 && ((wide)value & ((wide)value - 1)) == 0; \
    }

LGRT_STDC_TYPES(LGRT_STDC_HAS_SINGLE_BIT)

#define LGRT_STDC_BIT_WIDTH(sfx, type, wide, clz, ctz) \
    unsigned int stdc_bit_width_##sfx(type value); \
    unsigned int stdc_bit_width_##sfx(type value) { \
        return value == 0 ? 0 : lgrt_stdc_msb_##sfx(value) + 1; \
    }

LGRT_STDC_TYPES(LGRT_STDC_BIT_WIDTH)

#define LGRT_STDC_BIT_FLOOR(sfx, type, wide, clz, ctz) \
    type stdc_bit_floor_##sfx(type value); \
    type stdc_bit_floor_##sfx(type value) { \
        return value == 0 ? 0 \
            : (type)((wide)1 << lgrt_stdc_msb_##sfx(value)); \
    }

LGRT_STDC_TYPES(LGRT_STDC_BIT_FLOOR)

/*
 * Above 1, the result is twice the highest power of two in value - 1. Shifting
 * 2 keeps the count below the width, and an unrepresentable result wraps to 0.
 */
#define LGRT_STDC_BIT_CEIL(sfx, type, wide, clz, ctz) \
    type stdc_bit_ceil_##sfx(type value); \
    type stdc_bit_ceil_##sfx(type value) { \
        type below = (type)((wide)value - 1); \
        \
        return value <= 1 ? 1 \
            : (type)((wide)2 << lgrt_stdc_msb_##sfx(below)); \
    }

LGRT_STDC_TYPES(LGRT_STDC_BIT_CEIL)

#if defined(__hexagon__)

/*
 * When optimising for size, Clang saves and restores the callee-saved pairs
 * r17:16 to rR:R-1 with these routines, in that order downwards from fp - 8.
 * Prologues call the save routines in the packet of their allocframe, so fp
 * already points to the new frame. Each entry point handles its highest pair
 * and falls through to the entry point for the next lower one.
 */

#define LGRT_HEXAGON_ENTRY(name, end) \
    ".globl " name "\n" \
    ".hidden " name "\n" \
    ".type " name ", @function\n" \
    name ":\n" \
    ".size " name ", " end " - " name "\n"

#define LGRT_HEXAGON_STORE(pair, offset) "memd(r30+#-" offset ") = " pair
#define LGRT_HEXAGON_LOAD(pair, offset) pair " = memd(r30+#-" offset ")"

/*
 * Defines the entry points prefix R suffix, for R from 27 down to 17, all
 * extending to end. Those above 17 apply op to their highest pair; the code
 * for r17:16 and the label end follow.
 */
#define LGRT_HEXAGON_ENTRIES(prefix, suffix, end, op) \
    LGRT_HEXAGON_ENTRY(prefix "27" suffix, end) \
    "{ " op("r27:26", "48") " }\n" \
    LGRT_HEXAGON_ENTRY(prefix "25" suffix, end) \
    "{ " op("r25:24", "40") " }\n" \
    LGRT_HEXAGON_ENTRY(prefix "23" suffix, end) \
    "{ " op("r23:22", "32") " }\n" \
    LGRT_HEXAGON_ENTRY(prefix "21" suffix, end) \
    "{ " op("r21:20", "24") " }\n" \
    LGRT_HEXAGON_ENTRY(prefix "19" suffix, end) \
    "{ " op("r19:18", "16") " }\n" \
    LGRT_HEXAGON_ENTRY(prefix "17" suffix, end)

__asm__ (
    ".pushsection .text.__save_r16_through_r27,\"ax\",@progbits\n"
    ".p2align 2\n"
    LGRT_HEXAGON_ENTRIES(
        "__save_r16_through_r", "", ".Llgrt_hexagon_save_end",
        LGRT_HEXAGON_STORE
    )
    "{ " LGRT_HEXAGON_STORE("r17:16", "8") "; jumpr r31 }\n"
    ".Llgrt_hexagon_save_end:\n"
    ".popsection\n"
);

__asm__ (
    ".pushsection "
    ".text.__restore_r16_through_r27_and_deallocframe,\"ax\",@progbits\n"
    ".p2align 2\n"
    LGRT_HEXAGON_ENTRIES(
        "__restore_r16_through_r", "_and_deallocframe",
        ".Llgrt_hexagon_restore_end", LGRT_HEXAGON_LOAD
    )
    "{ " LGRT_HEXAGON_LOAD("r17:16", "8") "; dealloc_return }\n"
    ".Llgrt_hexagon_restore_end:\n"
    ".popsection\n"
);

/* deallocframe reloads lr, so the return address waits in r28. */
__asm__ (
    ".pushsection "
    ".text.__restore_r16_through_r27_and_deallocframe_before_tailcall,"
    "\"ax\",@progbits\n"
    ".p2align 2\n"
    LGRT_HEXAGON_ENTRIES(
        "__restore_r16_through_r", "_and_deallocframe_before_tailcall",
        ".Llgrt_hexagon_restore_before_tailcall_end", LGRT_HEXAGON_LOAD
    )
    "{ " LGRT_HEXAGON_LOAD("r17:16", "8") "; r28 = r31 }\n"
    "{ deallocframe; jumpr r28 }\n"
    ".Llgrt_hexagon_restore_before_tailcall_end:\n"
    ".popsection\n"
);

#endif

#if defined(__powerpc__) && !defined(__powerpc64__)

/*
 * GCC saves and restores callee-saved registers in 32-bit prologues and
 * epilogues with calls to these routines, which find each register's slot at a
 * fixed distance below the address in r11, or in r0 for the vector registers,
 * and leave almost every other register alone. The entry points of a family
 * share one sequence, each starting at its first register.
 */

#define LGRT_PPC_ENTRY(name, end) \
    ".globl " name "\n" \
    ".hidden " name "\n" \
    ".type " name ", @function\n" \
    name ":\n" \
    ".size " name ", " end " - " name "\n"

/*
 * Defines the entry points prefix N suffix, for N from 14 to 31, all extending
 * to end, each followed by op(N, w, d), where the slot of rN is w bytes below
 * r11 and that of fN d bytes.
 */
#define LGRT_PPC_ENTRIES(prefix, suffix, end, op) \
    LGRT_PPC_ENTRY(prefix "14" suffix, end) \
    op("14", "72", "144") \
    LGRT_PPC_ENTRY(prefix "15" suffix, end) \
    op("15", "68", "136") \
    LGRT_PPC_ENTRY(prefix "16" suffix, end) \
    op("16", "64", "128") \
    LGRT_PPC_ENTRY(prefix "17" suffix, end) \
    op("17", "60", "120") \
    LGRT_PPC_ENTRY(prefix "18" suffix, end) \
    op("18", "56", "112") \
    LGRT_PPC_ENTRY(prefix "19" suffix, end) \
    op("19", "52", "104") \
    LGRT_PPC_ENTRY(prefix "20" suffix, end) \
    op("20", "48", "96") \
    LGRT_PPC_ENTRY(prefix "21" suffix, end) \
    op("21", "44", "88") \
    LGRT_PPC_ENTRY(prefix "22" suffix, end) \
    op("22", "40", "80") \
    LGRT_PPC_ENTRY(prefix "23" suffix, end) \
    op("23", "36", "72") \
    LGRT_PPC_ENTRY(prefix "24" suffix, end) \
    op("24", "32", "64") \
    LGRT_PPC_ENTRY(prefix "25" suffix, end) \
    op("25", "28", "56") \
    LGRT_PPC_ENTRY(prefix "26" suffix, end) \
    op("26", "24", "48") \
    LGRT_PPC_ENTRY(prefix "27" suffix, end) \
    op("27", "20", "40") \
    LGRT_PPC_ENTRY(prefix "28" suffix, end) \
    op("28", "16", "32") \
    LGRT_PPC_ENTRY(prefix "29" suffix, end) \
    op("29", "12", "24") \
    LGRT_PPC_ENTRY(prefix "30" suffix, end) \
    op("30", "8", "16") \
    LGRT_PPC_ENTRY(prefix "31" suffix, end) \
    op("31", "4", "8")

/*
 * The frame is popped after the last load from the save area, which then lies
 * below the stack pointer, where signal handlers may overwrite it.
 */
#define LGRT_PPC_EXIT \
    "lwz %r0, 4(%r11)\n" \
    "mr %r1, %r11\n" \
    "mtlr %r0\n" \
    "blr\n"

#define LGRT_PPC_SAVE_GPR(n, w, d) "stw %r" n ", -" w "(%r11)\n"
#define LGRT_PPC_REST_GPR(n, w, d) "lwz %r" n ", -" w "(%r11)\n"

__asm__ (
    ".pushsection .text._savegpr_14,\"ax\",@progbits\n"
    ".p2align 2\n"
    LGRT_PPC_ENTRIES(
        "_savegpr_", "", ".Llgrt_ppc_savegpr_end", LGRT_PPC_SAVE_GPR
    )
    "blr\n"
    ".Llgrt_ppc_savegpr_end:\n"
    ".popsection\n"
);

__asm__ (
    ".pushsection .text._restgpr_14,\"ax\",@progbits\n"
    ".p2align 2\n"
    LGRT_PPC_ENTRIES(
        "_restgpr_", "", ".Llgrt_ppc_restgpr_end", LGRT_PPC_REST_GPR
    )
    "blr\n"
    ".Llgrt_ppc_restgpr_end:\n"
    ".popsection\n"
);

__asm__ (
    ".pushsection .text._restgpr_14_x,\"ax\",@progbits\n"
    ".p2align 2\n"
    LGRT_PPC_ENTRIES(
        "_restgpr_", "_x", ".Llgrt_ppc_restgpr_x_end", LGRT_PPC_REST_GPR
    )
    LGRT_PPC_EXIT
    ".Llgrt_ppc_restgpr_x_end:\n"
    ".popsection\n"
);

#if defined(__SPE__)

/*
 * GCC for SPE calls these instead: the 32-bit ones save the low halves of the
 * registers as those above do, and the 64-bit ones the whole registers, where
 * the hardware holds doubles in them. The offsets of evstdd and evldd cannot
 * be negative, so r11 holds the address of the slot of r14 there, 144 bytes
 * below the top of the frame, whatever register the routine starts at.
 */

#define LGRT_PPC_SAVE_EV(n, w, d) "evstdd %r" n ", 144-" d "(%r11)\n"
#define LGRT_PPC_REST_EV(n, w, d) "evldd %r" n ", 144-" d "(%r11)\n"

#define LGRT_PPC_EXIT_EV \
    "lwz %r0, 148(%r11)\n" \
    "addi %r1, %r11, 144\n" \
    "mtlr %r0\n" \
    "blr\n"

__asm__ (
    ".pushsection .text._save32gpr_14,\"ax\",@progbits\n"
    ".p2align 2\n"
    LGRT_PPC_ENTRIES(
        "_save32gpr_", "", ".Llgrt_ppc_save32gpr_end", LGRT_PPC_SAVE_GPR
    )
    "blr\n"
    ".Llgrt_ppc_save32gpr_end:\n"
    ".popsection\n"
);

__asm__ (
    ".pushsection .text._rest32gpr_14,\"ax\",@progbits\n"
    ".p2align 2\n"
    LGRT_PPC_ENTRIES(
        "_rest32gpr_", "", ".Llgrt_ppc_rest32gpr_end", LGRT_PPC_REST_GPR
    )
    "blr\n"
    ".Llgrt_ppc_rest32gpr_end:\n"
    ".popsection\n"
);

__asm__ (
    ".pushsection .text._rest32gpr_14_x,\"ax\",@progbits\n"
    ".p2align 2\n"
    LGRT_PPC_ENTRIES(
        "_rest32gpr_", "_x", ".Llgrt_ppc_rest32gpr_x_end", LGRT_PPC_REST_GPR
    )
    LGRT_PPC_EXIT
    ".Llgrt_ppc_rest32gpr_x_end:\n"
    ".popsection\n"
);

__asm__ (
    ".pushsection .text._save64gpr_14,\"ax\",@progbits\n"
    ".p2align 2\n"
    LGRT_PPC_ENTRIES(
        "_save64gpr_", "", ".Llgrt_ppc_save64gpr_end", LGRT_PPC_SAVE_EV
    )
    "blr\n"
    ".Llgrt_ppc_save64gpr_end:\n"
    ".popsection\n"
);

__asm__ (
    ".pushsection .text._rest64gpr_14,\"ax\",@progbits\n"
    ".p2align 2\n"
    LGRT_PPC_ENTRIES(
        "_rest64gpr_", "", ".Llgrt_ppc_rest64gpr_end", LGRT_PPC_REST_EV
    )
    "blr\n"
    ".Llgrt_ppc_rest64gpr_end:\n"
    ".popsection\n"
);

__asm__ (
    ".pushsection .text._rest64gpr_14_x,\"ax\",@progbits\n"
    ".p2align 2\n"
    LGRT_PPC_ENTRIES(
        "_rest64gpr_", "_x", ".Llgrt_ppc_rest64gpr_x_end", LGRT_PPC_REST_EV
    )
    LGRT_PPC_EXIT_EV
    ".Llgrt_ppc_rest64gpr_x_end:\n"
    ".popsection\n"
);

#endif

#if !defined(_SOFT_FLOAT) && !defined(__NO_FPRS__)

#define LGRT_PPC_SAVE_FPR(n, w, d) "stfd %f" n ", -" d "(%r11)\n"
#define LGRT_PPC_REST_FPR(n, w, d) "lfd %f" n ", -" d "(%r11)\n"

__asm__ (
    ".pushsection .text._savefpr_14,\"ax\",@progbits\n"
    ".p2align 2\n"
    LGRT_PPC_ENTRIES(
        "_savefpr_", "", ".Llgrt_ppc_savefpr_end", LGRT_PPC_SAVE_FPR
    )
    "blr\n"
    ".Llgrt_ppc_savefpr_end:\n"
    ".popsection\n"
);

__asm__ (
    ".pushsection .text._restfpr_14,\"ax\",@progbits\n"
    ".p2align 2\n"
    LGRT_PPC_ENTRIES(
        "_restfpr_", "", ".Llgrt_ppc_restfpr_end", LGRT_PPC_REST_FPR
    )
    "blr\n"
    ".Llgrt_ppc_restfpr_end:\n"
    ".popsection\n"
);

__asm__ (
    ".pushsection .text._restfpr_14_x,\"ax\",@progbits\n"
    ".p2align 2\n"
    LGRT_PPC_ENTRIES(
        "_restfpr_", "_x", ".Llgrt_ppc_restfpr_x_end", LGRT_PPC_REST_FPR
    )
    LGRT_PPC_EXIT
    ".Llgrt_ppc_restfpr_x_end:\n"
    ".popsection\n"
);

#endif

#if defined(__ALTIVEC__)

/*
 * Defines the entry points prefix N, for N from 20 to 31, all extending to
 * end, each followed by op(N, v), where the slot of vN is v bytes below r0.
 */
#define LGRT_PPC_VR_ENTRIES(prefix, end, op) \
    LGRT_PPC_ENTRY(prefix "20", end) \
    op("20", "192") \
    LGRT_PPC_ENTRY(prefix "21", end) \
    op("21", "176") \
    LGRT_PPC_ENTRY(prefix "22", end) \
    op("22", "160") \
    LGRT_PPC_ENTRY(prefix "23", end) \
    op("23", "144") \
    LGRT_PPC_ENTRY(prefix "24", end) \
    op("24", "128") \
    LGRT_PPC_ENTRY(prefix "25", end) \
    op("25", "112") \
    LGRT_PPC_ENTRY(prefix "26", end) \
    op("26", "96") \
    LGRT_PPC_ENTRY(prefix "27", end) \
    op("27", "80") \
    LGRT_PPC_ENTRY(prefix "28", end) \
    op("28", "64") \
    LGRT_PPC_ENTRY(prefix "29", end) \
    op("29", "48") \
    LGRT_PPC_ENTRY(prefix "30", end) \
    op("30", "32") \
    LGRT_PPC_ENTRY(prefix "31", end) \
    op("31", "16")

/*
 * The vector loads and stores read r0 as zero in their first address operand,
 * so that operand is the offset, in r11.
 */
#define LGRT_PPC_SAVE_VR(n, v) \
    "li %r11, -" v "\n" \
    "stvx %v" n ", %r11, %r0\n"
#define LGRT_PPC_REST_VR(n, v) \
    "li %r11, -" v "\n" \
    "lvx %v" n ", %r11, %r0\n"

__asm__ (
    ".pushsection .text._savevr_20,\"ax\",@progbits\n"
    ".p2align 2\n"
    LGRT_PPC_VR_ENTRIES("_savevr_", ".Llgrt_ppc_savevr_end", LGRT_PPC_SAVE_VR)
    "blr\n"
    ".Llgrt_ppc_savevr_end:\n"
    ".popsection\n"
);

__asm__ (
    ".pushsection .text._restvr_20,\"ax\",@progbits\n"
    ".p2align 2\n"
    LGRT_PPC_VR_ENTRIES("_restvr_", ".Llgrt_ppc_restvr_end", LGRT_PPC_REST_VR)
    "blr\n"
    ".Llgrt_ppc_restvr_end:\n"
    ".popsection\n"
);

#endif

#endif

/*
 * Except for the Hexagon names, these have special calling conventions, so
 * they are assembly, each changing only the registers its convention allows
 * and saving any others on the stack. The most negative value negates to
 * itself, its magnitude as an unsigned value, so the signed routines need no
 * special case for it.
 */

#if defined(__hexagon__)

/* Clang calls these, with the normal calling convention, for division. */

uint32_t __hexagon_udivsi3(uint32_t a, uint32_t b);
uint32_t __hexagon_udivsi3(
    uint32_t a, uint32_t b
) __attribute__((__alias__("__udivsi3")));

int32_t __hexagon_divsi3(int32_t a, int32_t b);
int32_t __hexagon_divsi3(
    int32_t a, int32_t b
) __attribute__((__alias__("__divsi3")));

uint32_t __hexagon_umodsi3(uint32_t a, uint32_t b);
uint32_t __hexagon_umodsi3(
    uint32_t a, uint32_t b
) __attribute__((__alias__("__umodsi3")));

int32_t __hexagon_modsi3(int32_t a, int32_t b);
int32_t __hexagon_modsi3(
    int32_t a, int32_t b
) __attribute__((__alias__("__modsi3")));

uint64_t __hexagon_udivdi3(uint64_t a, uint64_t b);
uint64_t __hexagon_udivdi3(
    uint64_t a, uint64_t b
) __attribute__((__alias__("__udivdi3")));

int64_t __hexagon_divdi3(int64_t a, int64_t b);
int64_t __hexagon_divdi3(
    int64_t a, int64_t b
) __attribute__((__alias__("__divdi3")));

uint64_t __hexagon_umoddi3(uint64_t a, uint64_t b);
uint64_t __hexagon_umoddi3(
    uint64_t a, uint64_t b
) __attribute__((__alias__("__umoddi3")));

int64_t __hexagon_moddi3(int64_t a, int64_t b);
int64_t __hexagon_moddi3(
    int64_t a, int64_t b
) __attribute__((__alias__("__moddi3")));

#endif

#if defined(__sh__)

/*
 * Called with jsr, with the dividend in r4 and the divisor in r5, returning
 * the quotient in r0, or in FPUL for the FPU variants.
 */

#define LGRT_SH_STEP(q, r, d) \
    "shll " q "\n" \
    "rotcl " r "\n" \
    "cmp/hs " d ", " r "\n" \
    "bf 1f\n" \
    "sub " d ", " r "\n" \
    "add #1, " q "\n" \
    "1:\n"

/*
 * The default strategy. These may change only r0, r1, T, PR, MACH, and MACL,
 * so __sdivsi3_i4i saves r2 on the stack.
 */

__asm__ (
    ".pushsection .text.__udivsi3_i4i,\"ax\",@progbits\n"
    ".p2align 2\n"
    ".globl __udivsi3_i4i\n"
    ".hidden __udivsi3_i4i\n"
    ".type __udivsi3_i4i, @function\n"
    "__udivsi3_i4i:\n"
    "mov r4, r0\n"
    "mov #0, r1\n"
    ".rept 32\n"
    LGRT_SH_STEP("r0", "r1", "r5")
    ".endr\n"
    "rts\n"
    "nop\n"
    ".size __udivsi3_i4i, . - __udivsi3_i4i\n"
    ".popsection\n"
);

__asm__ (
    ".pushsection .text.__sdivsi3_i4i,\"ax\",@progbits\n"
    ".p2align 2\n"
    ".globl __sdivsi3_i4i\n"
    ".hidden __sdivsi3_i4i\n"
    ".type __sdivsi3_i4i, @function\n"
    "__sdivsi3_i4i:\n"
    "mov.l r2, @-r15\n"
    "mov r4, r0\n"
    "cmp/pz r0\n"
    "bt 4f\n"
    "neg r0, r0\n"
    "4:\n"
    "mov r5, r2\n"
    "cmp/pz r2\n"
    "bt 5f\n"
    "neg r2, r2\n"
    "5:\n"
    "mov #0, r1\n"
    ".rept 32\n"
    LGRT_SH_STEP("r0", "r1", "r2")
    ".endr\n"
    "mov r4, r1\n"
    "xor r5, r1\n"
    "cmp/pz r1\n"
    "bt 6f\n"
    "neg r0, r0\n"
    "6:\n"
    "mov.l @r15+, r2\n"
    "rts\n"
    "nop\n"
    ".size __sdivsi3_i4i, . - __sdivsi3_i4i\n"
    ".popsection\n"
);

#if defined(__SH_FPU_ANY__)

/*
 * For -mdiv=call-fp. __udivsi3_i4 may change r0, r1, r4, and r5. __sdivsi3_i4,
 * called through r1, must preserve r0 to r7 and T, so it saves those it uses,
 * T included. Both must keep the FPSCR mode bits, so neither touches FPSCR.
 */

__asm__ (
    ".pushsection .text.__udivsi3_i4,\"ax\",@progbits\n"
    ".p2align 2\n"
    ".globl __udivsi3_i4\n"
    ".hidden __udivsi3_i4\n"
    ".type __udivsi3_i4, @function\n"
    "__udivsi3_i4:\n"
    "mov r4, r0\n"
    "mov #0, r1\n"
    ".rept 32\n"
    LGRT_SH_STEP("r0", "r1", "r5")
    ".endr\n"
    "lds r0, fpul\n"
    "rts\n"
    "nop\n"
    ".size __udivsi3_i4, . - __udivsi3_i4\n"
    ".popsection\n"
);

__asm__ (
    ".pushsection .text.__sdivsi3_i4,\"ax\",@progbits\n"
    ".p2align 2\n"
    ".globl __sdivsi3_i4\n"
    ".hidden __sdivsi3_i4\n"
    ".type __sdivsi3_i4, @function\n"
    "__sdivsi3_i4:\n"
    "mov.l r0, @-r15\n"
    "mov.l r1, @-r15\n"
    "mov.l r2, @-r15\n"
    "mov.l r3, @-r15\n"
    "movt r3\n"
    "mov r4, r0\n"
    "cmp/pz r0\n"
    "bt 4f\n"
    "neg r0, r0\n"
    "4:\n"
    "mov r5, r2\n"
    "cmp/pz r2\n"
    "bt 5f\n"
    "neg r2, r2\n"
    "5:\n"
    "mov #0, r1\n"
    ".rept 32\n"
    LGRT_SH_STEP("r0", "r1", "r2")
    ".endr\n"
    "mov r4, r1\n"
    "xor r5, r1\n"
    "cmp/pz r1\n"
    "bt 6f\n"
    "neg r0, r0\n"
    "6:\n"
    "lds r0, fpul\n"
    "shlr r3\n"
    "mov.l @r15+, r3\n"
    "mov.l @r15+, r2\n"
    "mov.l @r15+, r1\n"
    "mov.l @r15+, r0\n"
    "rts\n"
    "nop\n"
    ".size __sdivsi3_i4, . - __sdivsi3_i4\n"
    ".popsection\n"
);

#endif

/*
 * For -mdiv=call-div1 and older CPUs. These keep the normal argument and
 * result registers, so C callers may call them too. __udivsi3 may change only
 * r0, r1, r4, T, and PR, and __sdivsi3 only r0 to r3, T, and PR.
 */

__asm__ (
    ".pushsection .text.__udivsi3,\"ax\",@progbits\n"
    ".p2align 2\n"
    ".globl __udivsi3\n"
    ".hidden __udivsi3\n"
    ".type __udivsi3, @function\n"
    "__udivsi3:\n"
    "mov #0, r0\n"
    "mov #32, r1\n"
    "1:\n"
    "shll r4\n"
    "rotcl r0\n"
    "cmp/hs r5, r0\n"
    "bf 3f\n"
    "sub r5, r0\n"
    "add #1, r4\n"
    "3:\n"
    "dt r1\n"
    "bf 1b\n"
    "mov r4, r0\n"
    "rts\n"
    "nop\n"
    ".size __udivsi3, . - __udivsi3\n"
    ".popsection\n"
);

__asm__ (
    ".pushsection .text.__sdivsi3,\"ax\",@progbits\n"
    ".p2align 2\n"
    ".globl __sdivsi3\n"
    ".hidden __sdivsi3\n"
    ".type __sdivsi3, @function\n"
    "__sdivsi3:\n"
    "mov r4, r2\n"
    "cmp/pz r2\n"
    "bt 4f\n"
    "neg r2, r2\n"
    "4:\n"
    "mov r5, r3\n"
    "cmp/pz r3\n"
    "bt 5f\n"
    "neg r3, r3\n"
    "5:\n"
    "mov #0, r0\n"
    "mov #32, r1\n"
    "1:\n"
    "shll r2\n"
    "rotcl r0\n"
    "cmp/hs r3, r0\n"
    "bf 3f\n"
    "sub r3, r0\n"
    "add #1, r2\n"
    "3:\n"
    "dt r1\n"
    "bf 1b\n"
    "mov r4, r1\n"
    "xor r5, r1\n"
    "cmp/pz r1\n"
    "bt 6f\n"
    "neg r2, r2\n"
    "6:\n"
    "mov r2, r0\n"
    "rts\n"
    "nop\n"
    ".size __sdivsi3, . - __sdivsi3\n"
    ".popsection\n"
);

#undef LGRT_SH_STEP

#endif

#if defined(__sparc__) && !defined(__arch64__)

/*
 * GCC and Clang call these where the core has no instructions to multiply or
 * to divide. They are ordinary functions, under other names.
 */
int32_t lgrt_sparc_umul(int32_t a, int32_t b) __asm__ (".umul");
int32_t lgrt_sparc_umul(
    int32_t a, int32_t b
) __attribute__((__alias__("__mulsi3")));

int32_t lgrt_sparc_div(int32_t a, int32_t b) __asm__ (".div");
int32_t lgrt_sparc_div(
    int32_t a, int32_t b
) __attribute__((__alias__("__divsi3")));

int32_t lgrt_sparc_rem(int32_t a, int32_t b) __asm__ (".rem");
int32_t lgrt_sparc_rem(
    int32_t a, int32_t b
) __attribute__((__alias__("__modsi3")));

uint32_t lgrt_sparc_udiv(uint32_t a, uint32_t b) __asm__ (".udiv");
uint32_t lgrt_sparc_udiv(
    uint32_t a, uint32_t b
) __attribute__((__alias__("__udivsi3")));

uint32_t lgrt_sparc_urem(uint32_t a, uint32_t b) __asm__ (".urem");
uint32_t lgrt_sparc_urem(
    uint32_t a, uint32_t b
) __attribute__((__alias__("__umodsi3")));

#endif

#if defined(__hppa__) && !defined(__LP64__)

/*
 * Millicode, called with bl ...,%r31, with the dividend in %r26 and the
 * divisor in %r25. These return the result in %r29 through bv %r0(%r31) and
 * may change only %r1, %r25, %r26, %r29, %r31, and the carry bits.
 */

#define LGRT_HPPA_STEP \
    "add %r26, %r26, %r26\n" \
    "addc %r29, %r29, %r29\n" \
    "comb,<<,n %r29, %r25, 0f\n" \
    "sub %r29, %r25, %r29\n" \
    "ldo 1(%r26), %r26\n" \
    "0:\n"

__asm__ (
    ".pushsection .text.$$divU,\"ax\",@progbits\n"
    ".p2align 2\n"
    ".globl $$divU\n"
    ".hidden $$divU\n"
    ".type $$divU, @function\n"
    "$$divU:\n"
    "copy %r0, %r29\n"
    ".rept 32\n"
    LGRT_HPPA_STEP
    ".endr\n"
    "bv %r0(%r31)\n"
    "copy %r26, %r29\n"
    ".size $$divU, . - $$divU\n"
    ".popsection\n"
);

__asm__ (
    ".pushsection .text.$$remU,\"ax\",@progbits\n"
    ".p2align 2\n"
    ".globl $$remU\n"
    ".hidden $$remU\n"
    ".type $$remU, @function\n"
    "$$remU:\n"
    "copy %r0, %r29\n"
    ".rept 32\n"
    LGRT_HPPA_STEP
    ".endr\n"
    "bv,n %r0(%r31)\n"
    ".size $$remU, . - $$remU\n"
    ".popsection\n"
);

__asm__ (
    ".pushsection .text.$$divI,\"ax\",@progbits\n"
    ".p2align 2\n"
    ".globl $$divI\n"
    ".hidden $$divI\n"
    ".type $$divI, @function\n"
    "$$divI:\n"
    "xor %r26, %r25, %r1\n"
    "or,>= %r0, %r25, %r0\n"
    "sub %r0, %r25, %r25\n"
    "or,>= %r0, %r26, %r0\n"
    "sub %r0, %r26, %r26\n"
    "copy %r0, %r29\n"
    ".rept 32\n"
    LGRT_HPPA_STEP
    ".endr\n"
    "or,>= %r0, %r1, %r0\n"
    "sub %r0, %r26, %r26\n"
    "bv %r0(%r31)\n"
    "copy %r26, %r29\n"
    ".size $$divI, . - $$divI\n"
    ".popsection\n"
);

__asm__ (
    ".pushsection .text.$$remI,\"ax\",@progbits\n"
    ".p2align 2\n"
    ".globl $$remI\n"
    ".hidden $$remI\n"
    ".type $$remI, @function\n"
    "$$remI:\n"
    "copy %r26, %r1\n"
    "or,>= %r0, %r25, %r0\n"
    "sub %r0, %r25, %r25\n"
    "or,>= %r0, %r26, %r0\n"
    "sub %r0, %r26, %r26\n"
    "copy %r0, %r29\n"
    ".rept 32\n"
    LGRT_HPPA_STEP
    ".endr\n"
    "or,>= %r0, %r1, %r0\n"
    "sub %r0, %r29, %r29\n"
    "bv,n %r0(%r31)\n"
    ".size $$remI, . - $$remI\n"
    ".popsection\n"
);

#undef LGRT_HPPA_STEP

/*
 * Called the same way, with the operands in %r26 and %r25, where GCC cannot
 * use the floating-point registers to multiply.
 */
__asm__ (
    ".pushsection .text.$$mulI,\"ax\",@progbits\n"
    ".p2align 2\n"
    ".globl $$mulI\n"
    ".hidden $$mulI\n"
    ".type $$mulI, @function\n"
    "$$mulI:\n"
    "copy %r0, %r29\n"
    "0:\n"
    "comb,=,n %r25, %r0, 1f\n"
    "extru,= %r25, 31, 1, %r0\n"
    "addl %r29, %r26, %r29\n"
    "add %r26, %r26, %r26\n"
    "b 0b\n"
    "extru %r25, 30, 31, %r25\n"
    "1:\n"
    "bv,n %r0(%r31)\n"
    ".size $$mulI, . - $$mulI\n"
    ".popsection\n"
);

/*
 * Compilers call this for calls through function pointers, with bl
 * $$dyncall,%r31, the pointer in %r22, and the return address already in %r2,
 * so it branches to the function instead of returning. A pointer with bit 30
 * set addresses, with its low two bits cleared, a descriptor holding the code
 * address and the value for %r19. It may change only %r1, %r19, %r22, and
 * %r31, and must not touch the stack.
 */

__asm__ (
    ".pushsection .text.$$dyncall,\"ax\",@progbits\n"
    ".p2align 2\n"
    ".globl $$dyncall\n"
    ".hidden $$dyncall\n"
    ".type $$dyncall, @function\n"
    "$$dyncall:\n"
    "extru %r22, 30, 1, %r1\n"
    "comib,=,n 0, %r1, 0f\n"
    "depi 0, 31, 2, %r22\n"
    "ldw 4(%r22), %r19\n"
    "ldw 0(%r22), %r1\n"
    "bv %r0(%r1)\n"
    "nop\n"
    "0:\n"
    "bv %r0(%r22)\n"
    "nop\n"
    ".size $$dyncall, . - $$dyncall\n"
    ".popsection\n"
);

#endif

#if defined(__alpha__)

/*
 * Called with jsr $23,($27),name, with the dividend in $24 and the divisor in
 * $25, these return the result in $27 through ret $31,($23),1 and may change
 * only $23, $27, and $28, so they save their working registers on the stack,
 * allocating the space first, as nothing below $30 is safe. The 32-bit
 * routines get sign-extended operands, of which the unsigned ones use only the
 * low halves, and return sign-extended results. They move the dividend to the
 * high half so that the 64-bit step applies.
 */

#define LGRT_ALPHA_PROLOGUE(name) \
    ".pushsection .text." name ",\"ax\",@progbits\n" \
    ".p2align 2\n" \
    ".globl " name "\n" \
    ".hidden " name "\n" \
    ".type " name ", @function\n" \
    name ":\n" \
    "lda $30, -64($30)\n" \
    "stq $0, 0($30)\n" \
    "stq $1, 8($30)\n" \
    "stq $2, 16($30)\n" \
    "stq $3, 24($30)\n" \
    "stq $4, 32($30)\n" \
    "stq $5, 40($30)\n" \
    "stq $6, 48($30)\n"

#define LGRT_ALPHA_EPILOGUE(name) \
    "ldq $0, 0($30)\n" \
    "ldq $1, 8($30)\n" \
    "ldq $2, 16($30)\n" \
    "ldq $3, 24($30)\n" \
    "ldq $4, 32($30)\n" \
    "ldq $5, 40($30)\n" \
    "ldq $6, 48($30)\n" \
    "lda $30, 64($30)\n" \
    "ret $31, ($23), 1\n" \
    ".size " name ", . - " name "\n" \
    ".popsection\n"

#define LGRT_ALPHA_STEP \
    "srl $0, 63, $3\n" \
    "addq $0, $0, $0\n" \
    "addq $1, $1, $1\n" \
    "bis $1, $3, $1\n" \
    "cmpule $2, $1, $3\n" \
    "subq $1, $2, $4\n" \
    "cmovne $3, $4, $1\n" \
    "bis $0, $3, $0\n"

#define LGRT_ALPHA_LOOP(cnt) \
    "lda $6, " #cnt "($31)\n" \
    "7:\n" \
    LGRT_ALPHA_STEP \
    "subq $6, 1, $6\n" \
    "bne $6, 7b\n"

__asm__ (
    LGRT_ALPHA_PROLOGUE("__divqu")
    "mov $24, $0\n"
    "mov $31, $1\n"
    "mov $25, $2\n"
    LGRT_ALPHA_LOOP(64)
    "mov $0, $27\n"
    LGRT_ALPHA_EPILOGUE("__divqu")
);

__asm__ (
    LGRT_ALPHA_PROLOGUE("__remqu")
    "mov $24, $0\n"
    "mov $31, $1\n"
    "mov $25, $2\n"
    LGRT_ALPHA_LOOP(64)
    "mov $1, $27\n"
    LGRT_ALPHA_EPILOGUE("__remqu")
);

__asm__ (
    LGRT_ALPHA_PROLOGUE("__divq")
    "xor $24, $25, $5\n"
    "mov $24, $0\n"
    "subq $31, $0, $3\n"
    "cmovlt $0, $3, $0\n"
    "mov $25, $2\n"
    "subq $31, $2, $3\n"
    "cmovlt $2, $3, $2\n"
    "mov $31, $1\n"
    LGRT_ALPHA_LOOP(64)
    "subq $31, $0, $3\n"
    "cmovlt $5, $3, $0\n"
    "mov $0, $27\n"
    LGRT_ALPHA_EPILOGUE("__divq")
);

__asm__ (
    LGRT_ALPHA_PROLOGUE("__remq")
    "mov $24, $5\n"
    "mov $24, $0\n"
    "subq $31, $0, $3\n"
    "cmovlt $0, $3, $0\n"
    "mov $25, $2\n"
    "subq $31, $2, $3\n"
    "cmovlt $2, $3, $2\n"
    "mov $31, $1\n"
    LGRT_ALPHA_LOOP(64)
    "subq $31, $1, $3\n"
    "cmovlt $5, $3, $1\n"
    "mov $1, $27\n"
    LGRT_ALPHA_EPILOGUE("__remq")
);

__asm__ (
    LGRT_ALPHA_PROLOGUE("__divlu")
    "zapnot $24, 15, $0\n"
    "sll $0, 32, $0\n"
    "zapnot $25, 15, $2\n"
    "mov $31, $1\n"
    LGRT_ALPHA_LOOP(32)
    "addl $0, $31, $27\n"
    LGRT_ALPHA_EPILOGUE("__divlu")
);

__asm__ (
    LGRT_ALPHA_PROLOGUE("__remlu")
    "zapnot $24, 15, $0\n"
    "sll $0, 32, $0\n"
    "zapnot $25, 15, $2\n"
    "mov $31, $1\n"
    LGRT_ALPHA_LOOP(32)
    "addl $1, $31, $27\n"
    LGRT_ALPHA_EPILOGUE("__remlu")
);

__asm__ (
    LGRT_ALPHA_PROLOGUE("__divl")
    "xor $24, $25, $5\n"
    "mov $24, $0\n"
    "subq $31, $0, $3\n"
    "cmovlt $0, $3, $0\n"
    "sll $0, 32, $0\n"
    "mov $25, $2\n"
    "subq $31, $2, $3\n"
    "cmovlt $2, $3, $2\n"
    "mov $31, $1\n"
    LGRT_ALPHA_LOOP(32)
    "addl $0, $31, $0\n"
    "subq $31, $0, $3\n"
    "cmovlt $5, $3, $0\n"
    "mov $0, $27\n"
    LGRT_ALPHA_EPILOGUE("__divl")
);

__asm__ (
    LGRT_ALPHA_PROLOGUE("__reml")
    "mov $24, $5\n"
    "mov $24, $0\n"
    "subq $31, $0, $3\n"
    "cmovlt $0, $3, $0\n"
    "sll $0, 32, $0\n"
    "mov $25, $2\n"
    "subq $31, $2, $3\n"
    "cmovlt $2, $3, $2\n"
    "mov $31, $1\n"
    LGRT_ALPHA_LOOP(32)
    "addl $1, $31, $1\n"
    "subq $31, $1, $3\n"
    "cmovlt $5, $3, $1\n"
    "mov $1, $27\n"
    LGRT_ALPHA_EPILOGUE("__reml")
);

#undef LGRT_ALPHA_PROLOGUE
#undef LGRT_ALPHA_EPILOGUE
#undef LGRT_ALPHA_STEP
#undef LGRT_ALPHA_LOOP

#endif

#if defined(__ARM_EABI__) && defined(__ARM_ARCH_ISA_THUMB)

/*
 * GCC dispatches Thumb-1 jump tables through these, calling them with bl just
 * before the table and with the case index in r0. bl does not change state on
 * ARMv4T, so they are Thumb code for that architecture, whatever state the
 * rest of the file is in. They may change only ip, lr, and the flags, so r1
 * waits in ip while they use it.
 */

/*
 * Each helper has a section of its own, so that linkers can drop it if unused,
 * and switches to Thumb state and unified syntax for its code, then back to
 * the file's own state and syntax. File-scope assembly starts in unified
 * syntax with Clang, in Thumb-2 state, and where GCC says so, and in divided
 * syntax otherwise.
 */
#if defined(__clang__) || defined(__thumb2__) \
 || defined(__ARM_ASM_SYNTAX_UNIFIED__)
#define LGRT_THUMB1_SYNTAX ""
#else
#define LGRT_THUMB1_SYNTAX ".syntax divided\n"
#endif

#if defined(__thumb__)
#define LGRT_THUMB1_RESTORE LGRT_THUMB1_SYNTAX
#else
#define LGRT_THUMB1_RESTORE ".arm\n" LGRT_THUMB1_SYNTAX
#endif

#define LGRT_THUMB1_BEGIN(name) \
    ".pushsection .text." name ",\"ax\",%progbits\n" \
    ".syntax unified\n" \
    ".thumb\n" \
    ".p2align 2\n" \
    ".globl " name "\n" \
    ".hidden " name "\n" \
    ".type " name ", %function\n" \
    ".thumb_func\n" \
    name ":\n"

#define LGRT_THUMB1_END(name) \
    ".size " name ", . - " name "\n" \
    LGRT_THUMB1_RESTORE \
    ".popsection\n"

/*
 * The byte and halfword tables start at lr - 1 and hold halved distances to
 * the targets, which, doubled and added to lr, keep its Thumb bit. The signed
 * loads take only register offsets, so base points r1 where [r1, r0] addresses
 * entry r0: at the table start for bytes, and r0 bytes further for halfwords.
 */
#define LGRT_THUMB1_CASE(name, base, load) \
    LGRT_THUMB1_BEGIN(name) \
    "mov ip, r1\n" \
    base \
    load " r1, [r1, r0]\n" \
    "lsls r1, r1, #1\n" \
    "add lr, r1\n" \
    "mov r1, ip\n" \
    "bx lr\n" \
    LGRT_THUMB1_END(name)

#define LGRT_THUMB1_BYTE_BASE \
    "mov r1, lr\n" \
    "subs r1, #1\n"
#define LGRT_THUMB1_HALF_BASE \
    "subs r1, r0, #1\n" \
    "add r1, lr\n"

__asm__ (
    LGRT_THUMB1_CASE("__gnu_thumb1_case_uqi", LGRT_THUMB1_BYTE_BASE, "ldrb")
);

__asm__ (
    LGRT_THUMB1_CASE("__gnu_thumb1_case_sqi", LGRT_THUMB1_BYTE_BASE, "ldrsb")
);

__asm__ (
    LGRT_THUMB1_CASE("__gnu_thumb1_case_uhi", LGRT_THUMB1_HALF_BASE, "ldrh")
);

__asm__ (
    LGRT_THUMB1_CASE("__gnu_thumb1_case_shi", LGRT_THUMB1_HALF_BASE, "ldrsh")
);

/*
 * The word table starts at (lr + 2) & ~3, the first word boundary at or after
 * lr - 1, and holds distances in bytes, whose sums with its start lack the
 * Thumb bit, so mov, which keeps the state, branches to them instead of bx.
 */
__asm__ (
    LGRT_THUMB1_BEGIN("__gnu_thumb1_case_si")
    "mov ip, r1\n"
    "mov r1, lr\n"
    "adds r1, #2\n"
    "lsrs r1, r1, #2\n"
    "lsls r1, r1, #2\n"
    "mov lr, r1\n"
    "lsls r1, r0, #2\n"
    "add r1, lr\n"
    "ldr r1, [r1]\n"
    "add lr, r1\n"
    "mov r1, ip\n"
    "mov pc, lr\n"
    LGRT_THUMB1_END("__gnu_thumb1_case_si")
);

#endif

#if defined(__arc__)

/*
 * When optimising for size, GCC saves and restores r13 to rN in prologues and
 * epilogues with calls to these, finding r13 at sp and each further register
 * in the next word up. Each entry point handles its highest register and falls
 * through to the one for the next lower register. None changes the flags.
 */

#define LGRT_ARC_ENTRY(name, end) \
    ".globl " name "\n" \
    ".hidden " name "\n" \
    ".type " name ", @function\n" \
    name ":\n" \
    ".size " name ", " end " - " name "\n"

/*
 * Defines the entry points prefix N suffix, for N from LGRT_ARC_FIRST down to
 * 14, all extending to end, each followed by op(rN, d), where the slot of rN
 * is d bytes above sp. LGRT_ARC_FIRST is 25, or 15 with the reduced register
 * file, which lacks r16 to r25: the assembler would otherwise mark the object
 * as using the full register file.
 */
#if defined(__ARC_RF16__)
#define LGRT_ARC_FIRST "15"
#define LGRT_ARC_HIGH_ENTRIES(prefix, suffix, end, op)
#else
#define LGRT_ARC_FIRST "25"
#define LGRT_ARC_HIGH_ENTRIES(prefix, suffix, end, op) \
    LGRT_ARC_ENTRY(prefix "25" suffix, end) \
    op("r25", "48") \
    LGRT_ARC_ENTRY(prefix "24" suffix, end) \
    op("r24", "44") \
    LGRT_ARC_ENTRY(prefix "23" suffix, end) \
    op("r23", "40") \
    LGRT_ARC_ENTRY(prefix "22" suffix, end) \
    op("r22", "36") \
    LGRT_ARC_ENTRY(prefix "21" suffix, end) \
    op("r21", "32") \
    LGRT_ARC_ENTRY(prefix "20" suffix, end) \
    op("r20", "28") \
    LGRT_ARC_ENTRY(prefix "19" suffix, end) \
    op("r19", "24") \
    LGRT_ARC_ENTRY(prefix "18" suffix, end) \
    op("r18", "20") \
    LGRT_ARC_ENTRY(prefix "17" suffix, end) \
    op("r17", "16") \
    LGRT_ARC_ENTRY(prefix "16" suffix, end) \
    op("r16", "12")
#endif

#define LGRT_ARC_ENTRIES(prefix, suffix, end, op) \
    LGRT_ARC_HIGH_ENTRIES(prefix, suffix, end, op) \
    LGRT_ARC_ENTRY(prefix "15" suffix, end) \
    op("r15", "8") \
    LGRT_ARC_ENTRY(prefix "14" suffix, end) \
    op("r14", "4")

/*
 * Opens the section of the family of entry points prefix N suffix, named after
 * the first of them, so that linkers can drop the family if unused.
 */
#define LGRT_ARC_SECTION(prefix, suffix) \
    ".pushsection .text." prefix LGRT_ARC_FIRST suffix ",\"ax\",@progbits\n" \
    ".p2align 2\n"

#define LGRT_ARC_STORE(reg, d) "st " reg ", [sp, " d "]\n"
#define LGRT_ARC_LOAD(reg, d) "ld " reg ", [sp, " d "]\n"

__asm__ (
    LGRT_ARC_SECTION("__st_r13_to_r", "")
    LGRT_ARC_ENTRIES("__st_r13_to_r", "", ".Llgrt_arc_st_end", LGRT_ARC_STORE)
    "j_s.d [blink]\n"
    LGRT_ARC_STORE("r13", "0")
    ".Llgrt_arc_st_end:\n"
    ".popsection\n"
);

__asm__ (
    LGRT_ARC_SECTION("__ld_r13_to_r", "")
    LGRT_ARC_ENTRIES("__ld_r13_to_r", "", ".Llgrt_arc_ld_end", LGRT_ARC_LOAD)
    "j_s.d [blink]\n"
    LGRT_ARC_LOAD("r13", "0")
    ".Llgrt_arc_ld_end:\n"
    ".popsection\n"
);

/*
 * Epilogues end by jumping to these, with r12 holding the size of the frame
 * area below the saved blink, to also pop that area and blink and return to
 * the function's caller. blink is loaded before sp moves, so that the jump
 * waits less for it.
 */
__asm__ (
    LGRT_ARC_SECTION("__ld_r13_to_r", "_ret")
    LGRT_ARC_ENTRIES(
        "__ld_r13_to_r", "_ret", ".Llgrt_arc_ld_ret_end", LGRT_ARC_LOAD
    )
    "ld blink, [sp, r12]\n"
    LGRT_ARC_LOAD("r13", "0")
    "add sp, sp, r12\n"
    "j_s.d [blink]\n"
    "add_s sp, sp, 4\n"
    ".Llgrt_arc_ld_ret_end:\n"
    ".popsection\n"
);

#endif

#if defined(__MSP430__)

/*
 * The run-time ABI of MSP430: those of up to 4 bytes have the convention of C,
 * those of 8 bytes take their first operand in R11:R8 and their second in
 * R15:R12, or a count in R12, and return in R15:R12, the lowest word in the
 * lowest register.
 */

#if defined(__MSP430X_LARGE__)
#define LGRT_MSP430_CALL "calla"
#define LGRT_MSP430_RET "reta\n"
#define LGRT_MSP430_MOVA "mova"
#define LGRT_MSP430_ADDA "adda"
#define LGRT_MSP430_SUBA "suba"
#define LGRT_MSP430_CMPA "cmpa"
#define LGRT_MSP430_MOVB "movx.b"
#define LGRT_MSP430_WORD "4"
#else
#define LGRT_MSP430_CALL "call"
#define LGRT_MSP430_RET "ret\n"
#define LGRT_MSP430_MOVA "mov"
#define LGRT_MSP430_ADDA "add"
#define LGRT_MSP430_SUBA "sub"
#define LGRT_MSP430_CMPA "cmp"
#define LGRT_MSP430_MOVB "mov.b"
#define LGRT_MSP430_WORD "2"
#endif

#define LGRT_MSP430_ENTRY(name) \
    ".globl " name "\n" \
    ".hidden " name "\n" \
    ".type " name ", @function\n" \
    name ":\n"

#define LGRT_MSP430_SIZED(name, end) \
    LGRT_MSP430_ENTRY(name) \
    ".size " name ", " end " - " name "\n"

#define LGRT_MSP430_BEGIN(name) \
    ".pushsection .text." name ",\"ax\",@progbits\n" \
    ".p2align 1\n" \
    LGRT_MSP430_ENTRY(name)

#define LGRT_MSP430_END(name) \
    ".size " name ", . - " name "\n" \
    ".popsection\n"

/* Calls a routine in C, which takes the second operand on the stack. */
#define LGRT_MSP430_FROM_64(name, f) \
    __asm__ ( \
        LGRT_MSP430_BEGIN(name) \
        "push r15\n" \
        "push r14\n" \
        "push r13\n" \
        "push r12\n" \
        "mov r8, r12\n" \
        "mov r9, r13\n" \
        "mov r10, r14\n" \
        "mov r11, r15\n" \
        LGRT_MSP430_CALL " #" f "\n" \
        LGRT_MSP430_ADDA " #8, r1\n" \
        LGRT_MSP430_RET \
        LGRT_MSP430_END(name) \
    );

/*
 * GCC gives the generic routines above the names and the conventions of the
 * run-time ABI by itself, which Clang does not, and 4.9 two other names for
 * those of two.
 */
#if !defined(__clang__) && __GNUC__ < 5
__asm__ (
    ".globl __mspabi_divul\n"
    ".hidden __mspabi_divul\n"
    ".set __mspabi_divul, __mspabi_divlu\n"
    ".globl __mspabi_divull\n"
    ".hidden __mspabi_divull\n"
    ".set __mspabi_divull, __mspabi_divllu\n"
);
#endif

#if defined(__clang__)

LGRT_MSP430_FROM_64("__mspabi_divlli", "__divdi3")
LGRT_MSP430_FROM_64("__mspabi_divull", "__udivdi3")
LGRT_MSP430_FROM_64("__mspabi_remlli", "__moddi3")
LGRT_MSP430_FROM_64("__mspabi_remull", "__umoddi3")
LGRT_MSP430_FROM_64("__mspabi_mpyll", "__muldi3")

int16_t __mspabi_divi(int16_t a, int16_t b);
int16_t __mspabi_divi(
    int16_t a, int16_t b
) __attribute__((__alias__("__divhi3")));

uint16_t __mspabi_divu(uint16_t a, uint16_t b);
uint16_t __mspabi_divu(
    uint16_t a, uint16_t b
) __attribute__((__alias__("__udivhi3")));

int16_t __mspabi_remi(int16_t a, int16_t b);
int16_t __mspabi_remi(
    int16_t a, int16_t b
) __attribute__((__alias__("__modhi3")));

uint16_t __mspabi_remu(uint16_t a, uint16_t b);
uint16_t __mspabi_remu(
    uint16_t a, uint16_t b
) __attribute__((__alias__("__umodhi3")));

int32_t __mspabi_divli(int32_t a, int32_t b);
int32_t __mspabi_divli(
    int32_t a, int32_t b
) __attribute__((__alias__("__divsi3")));

uint32_t __mspabi_divul(uint32_t a, uint32_t b);
uint32_t __mspabi_divul(
    uint32_t a, uint32_t b
) __attribute__((__alias__("__udivsi3")));

int32_t __mspabi_remli(int32_t a, int32_t b);
int32_t __mspabi_remli(
    int32_t a, int32_t b
) __attribute__((__alias__("__modsi3")));

uint32_t __mspabi_remul(uint32_t a, uint32_t b);
uint32_t __mspabi_remul(
    uint32_t a, uint32_t b
) __attribute__((__alias__("__umodsi3")));

int16_t __mspabi_mpyi(int16_t a, int16_t b);
int16_t __mspabi_mpyi(
    int16_t a, int16_t b
) __attribute__((__alias__("__mulhi3")));

int32_t __mspabi_mpyl(int32_t a, int32_t b);
int32_t __mspabi_mpyl(
    int32_t a, int32_t b
) __attribute__((__alias__("__mulsi3")));

#endif

int32_t __mspabi_mpysl(int16_t a, int16_t b);
int32_t __mspabi_mpysl(int16_t a, int16_t b) {
    return (int32_t)lgrt_shift_add_mul32(
        (uint32_t)(int32_t)a, (uint32_t)(int32_t)b
    );
}

uint32_t __mspabi_mpyul(uint16_t a, uint16_t b);
uint32_t __mspabi_mpyul(uint16_t a, uint16_t b) {
    return lgrt_shift_add_mul32(a, b);
}

uint64_t __mspabi_mpyull(uint32_t a, uint32_t b);
uint64_t __mspabi_mpyull(uint32_t a, uint32_t b) {
    return lgrt_wide_mul32(a, b);
}

/* A negative operand read as unsigned adds the other above the product. */
int64_t __mspabi_mpysll(int32_t a, int32_t b);
int64_t __mspabi_mpysll(int32_t a, int32_t b) {
    uint32_t x = (uint32_t)a;
    uint32_t y = (uint32_t)b;
    uint64_t p = lgrt_wide_mul32(x, y);
    uint32_t over = (y & ((uint32_t)0 - (x >> 31)))
        + (x & ((uint32_t)0 - (y >> 31)));

    return (int64_t)(p - ((uint64_t)over << 32));
}

/* The shifts by constants, each falling through to the one by one less. */
#define LGRT_MSP430_COUNTS(prefix, end, step) \
    LGRT_MSP430_SIZED(prefix "15", end) \
    step \
    LGRT_MSP430_SIZED(prefix "14", end) \
    step \
    LGRT_MSP430_SIZED(prefix "13", end) \
    step \
    LGRT_MSP430_SIZED(prefix "12", end) \
    step \
    LGRT_MSP430_SIZED(prefix "11", end) \
    step \
    LGRT_MSP430_SIZED(prefix "10", end) \
    step \
    LGRT_MSP430_SIZED(prefix "9", end) \
    step \
    LGRT_MSP430_SIZED(prefix "8", end) \
    step \
    LGRT_MSP430_SIZED(prefix "7", end) \
    step \
    LGRT_MSP430_SIZED(prefix "6", end) \
    step \
    LGRT_MSP430_SIZED(prefix "5", end) \
    step \
    LGRT_MSP430_SIZED(prefix "4", end) \
    step \
    LGRT_MSP430_SIZED(prefix "3", end) \
    step \
    LGRT_MSP430_SIZED(prefix "2", end) \
    step \
    LGRT_MSP430_SIZED(prefix "1", end) \
    step \
    LGRT_MSP430_RET

/* The shifts by the count in r. */
#define LGRT_MSP430_SHIFT(name, r, step) \
    __asm__ ( \
        LGRT_MSP430_BEGIN(name) \
        "tst " r "\n" \
        "jz 2f\n" \
        "1:\n" \
        step \
        "sub #1, " r "\n" \
        "jnz 1b\n" \
        "2:\n" \
        LGRT_MSP430_RET \
        LGRT_MSP430_END(name) \
    );

#define LGRT_MSP430_SHIFTS(prefix, r, step) \
    LGRT_MSP430_SHIFT(prefix, r, step) \
    __asm__ ( \
        ".pushsection .text." prefix "_15,\"ax\",@progbits\n" \
        ".p2align 1\n" \
        LGRT_MSP430_COUNTS(prefix "_", ".Llgrt_msp430_" prefix "_end", step) \
        ".Llgrt_msp430_" prefix "_end:\n" \
        ".popsection\n" \
    );

#define LGRT_MSP430_SHL16 "add r12, r12\n"
#define LGRT_MSP430_SAR16 "rra r12\n"
#define LGRT_MSP430_SHR16 \
    "clrc\n" \
    "rrc r12\n"
#define LGRT_MSP430_SHL32 \
    "add r12, r12\n" \
    "addc r13, r13\n"
#define LGRT_MSP430_SAR32 \
    "rra r13\n" \
    "rrc r12\n"
#define LGRT_MSP430_SHR32 \
    "clrc\n" \
    "rrc r13\n" \
    "rrc r12\n"

LGRT_MSP430_SHIFTS("__mspabi_slli", "r13", LGRT_MSP430_SHL16)
LGRT_MSP430_SHIFTS("__mspabi_srai", "r13", LGRT_MSP430_SAR16)
LGRT_MSP430_SHIFTS("__mspabi_srli", "r13", LGRT_MSP430_SHR16)
LGRT_MSP430_SHIFTS("__mspabi_slll", "r14", LGRT_MSP430_SHL32)
LGRT_MSP430_SHIFTS("__mspabi_sral", "r14", LGRT_MSP430_SAR32)
LGRT_MSP430_SHIFTS("__mspabi_srll", "r14", LGRT_MSP430_SHR32)

/* Workaround: Clang before 8, MSP430: it calls these for shifts of 32 bits. */
#if defined(__clang__) && __clang_major__ < 8
__asm__ (
    ".globl __ashlsi3\n"
    ".hidden __ashlsi3\n"
    ".set __ashlsi3, __mspabi_slll\n"
    ".globl __ashrsi3\n"
    ".hidden __ashrsi3\n"
    ".set __ashrsi3, __mspabi_sral\n"
    ".globl __lshrsi3\n"
    ".hidden __lshrsi3\n"
    ".set __lshrsi3, __mspabi_srll\n"
);
#endif

/* The count moves to r11, as the result goes where it was. */
#define LGRT_MSP430_SHIFT_64(name, step) \
    __asm__ ( \
        LGRT_MSP430_BEGIN(name) \
        "mov r11, r15\n" \
        "mov r10, r14\n" \
        "mov r9, r13\n" \
        "mov r12, r11\n" \
        "mov r8, r12\n" \
        "tst r11\n" \
        "jz 2f\n" \
        "1:\n" \
        step \
        "sub #1, r11\n" \
        "jnz 1b\n" \
        "2:\n" \
        LGRT_MSP430_RET \
        LGRT_MSP430_END(name) \
    );

LGRT_MSP430_SHIFT_64(
    "__mspabi_sllll",
    "add r12, r12\n"
    "addc r13, r13\n"
    "addc r14, r14\n"
    "addc r15, r15\n"
)

LGRT_MSP430_SHIFT_64(
    "__mspabi_srall",
    "rra r15\n"
    "rrc r14\n"
    "rrc r13\n"
    "rrc r12\n"
)

LGRT_MSP430_SHIFT_64(
    "__mspabi_srlll",
    "clrc\n"
    "rrc r15\n"
    "rrc r14\n"
    "rrc r13\n"
    "rrc r12\n"
)

/*
 * Epilogues optimised for size jump into this, past the pops of the registers
 * they did not save.
 */
__asm__ (
    ".pushsection .text.__mspabi_func_epilog_7,\"ax\",@progbits\n"
    ".p2align 1\n"
    LGRT_MSP430_SIZED("__mspabi_func_epilog_7", ".Llgrt_msp430_epilog_end")
    "pop r4\n"
    LGRT_MSP430_SIZED("__mspabi_func_epilog_6", ".Llgrt_msp430_epilog_end")
    "pop r5\n"
    LGRT_MSP430_SIZED("__mspabi_func_epilog_5", ".Llgrt_msp430_epilog_end")
    "pop r6\n"
    LGRT_MSP430_SIZED("__mspabi_func_epilog_4", ".Llgrt_msp430_epilog_end")
    "pop r7\n"
    LGRT_MSP430_SIZED("__mspabi_func_epilog_3", ".Llgrt_msp430_epilog_end")
    "pop r8\n"
    LGRT_MSP430_SIZED("__mspabi_func_epilog_2", ".Llgrt_msp430_epilog_end")
    "pop r9\n"
    LGRT_MSP430_SIZED("__mspabi_func_epilog_1", ".Llgrt_msp430_epilog_end")
    "pop r10\n"
    LGRT_MSP430_RET
    ".Llgrt_msp430_epilog_end:\n"
    ".popsection\n"
);

/*
 * The assembler references these where an object has data to initialise, data
 * to zero, or arrays of functions to run. Linker scripts for MSP430 put the
 * sections .crt_* in the order of their names, so that the startup code falls
 * through the first of these. The symbols are weak for scripts that lack them.
 */

__asm__ (
    ".pushsection .crt_0100init_bss,\"ax\",@progbits\n"
    ".weak __bssstart\n"
    ".weak __bsssize\n"
    ".globl __crt0_init_bss\n"
    ".hidden __crt0_init_bss\n"
    "__crt0_init_bss:\n"
    LGRT_MSP430_MOVA " #__bssstart, r12\n"
    LGRT_MSP430_MOVA " #__bsssize, r13\n"
    LGRT_MSP430_CMPA " #0, r13\n"
    "jz 2f\n"
    "1:\n"
    LGRT_MSP430_MOVB " #0, 0(r12)\n"
    LGRT_MSP430_ADDA " #1, r12\n"
    LGRT_MSP430_SUBA " #1, r13\n"
    "jnz 1b\n"
    "2:\n"
    ".popsection\n"
);

__asm__ (
    ".pushsection .crt_0300movedata,\"ax\",@progbits\n"
    ".weak __datastart\n"
    ".weak __romdatastart\n"
    ".weak __romdatacopysize\n"
    ".globl __crt0_movedata\n"
    ".hidden __crt0_movedata\n"
    "__crt0_movedata:\n"
    LGRT_MSP430_MOVA " #__datastart, r12\n"
    LGRT_MSP430_MOVA " #__romdatastart, r13\n"
    LGRT_MSP430_MOVA " #__romdatacopysize, r14\n"
    LGRT_MSP430_CMPA " r12, r13\n"
    "jeq 2f\n"
    LGRT_MSP430_CMPA " #0, r14\n"
    "jz 2f\n"
    "1:\n"
    LGRT_MSP430_MOVB " @r13, 0(r12)\n"
    LGRT_MSP430_ADDA " #1, r13\n"
    LGRT_MSP430_ADDA " #1, r12\n"
    LGRT_MSP430_SUBA " #1, r14\n"
    "jnz 1b\n"
    "2:\n"
    ".popsection\n"
);

#define LGRT_MSP430_RUN_ARRAY(section, name, start, end) \
    __asm__ ( \
        ".pushsection " section ",\"ax\",@progbits\n" \
        ".weak " start "\n" \
        ".weak " end "\n" \
        ".globl " name "\n" \
        ".hidden " name "\n" \
        name ":\n" \
        LGRT_MSP430_MOVA " #" start ", r4\n" \
        LGRT_MSP430_MOVA " #" end ", r5\n" \
        LGRT_MSP430_CALL " #__crt0_run_array\n" \
        ".popsection\n" \
    );

LGRT_MSP430_RUN_ARRAY(
    ".crt_0500run_preinit_array", "__crt0_run_preinit_array",
    "__preinit_array_start", "__preinit_array_end"
)

LGRT_MSP430_RUN_ARRAY(
    ".crt_0600run_init_array", "__crt0_run_init_array", "__init_array_start",
    "__init_array_end"
)

/* The exit calls this one, which runs the array backwards. */
__asm__ (
    ".pushsection .crt_1000run_fini_array,\"ax\",@progbits\n"
    ".weak __fini_array_start\n"
    ".weak __fini_array_end\n"
    LGRT_MSP430_SIZED("__crt0_run_fini_array", ".Llgrt_msp430_fini_end")
    "push r4\n"
    "push r5\n"
    LGRT_MSP430_MOVA " #__fini_array_end, r4\n"
    LGRT_MSP430_MOVA " #__fini_array_start, r5\n"
    "jmp 2f\n"
    "1:\n"
    LGRT_MSP430_SUBA " #" LGRT_MSP430_WORD ", r4\n"
#if defined(__MSP430X_LARGE__)
    "calla @r4\n"
#else
    "call @r4\n"
#endif
    "2:\n"
    LGRT_MSP430_CMPA " r4, r5\n"
    "jne 1b\n"
    "pop r5\n"
    "pop r4\n"
    LGRT_MSP430_RET
    ".Llgrt_msp430_fini_end:\n"
    ".popsection\n"
);

/* Runs the functions from r4 up to r5, which they keep. */
__asm__ (
    ".pushsection .crt_1100run_array,\"ax\",@progbits\n"
    LGRT_MSP430_SIZED("__crt0_run_array", ".Llgrt_msp430_run_end")
    "jmp 2f\n"
    "1:\n"
#if defined(__MSP430X_LARGE__)
    "calla @r4\n"
#else
    "call @r4\n"
#endif
    LGRT_MSP430_ADDA " #" LGRT_MSP430_WORD ", r4\n"
    "2:\n"
    LGRT_MSP430_CMPA " r4, r5\n"
    "jne 1b\n"
    LGRT_MSP430_RET
    ".Llgrt_msp430_run_end:\n"
    ".popsection\n"
);

#endif

#if defined(__AVR__)

/*
 * The compilers know which registers each of these changes, and keep values in
 * the others across the calls, so these are assembly, and change only their
 * results, the flags, and the temporary register. Comments give the
 * conventions that differ from C's. The reduced cores have only r16 to r31,
 * with r16 as the temporary register and r17 as the zero register, and pass
 * 8-byte values in memory, so their 8-byte routines are in C.
 */

#if defined(__AVR_TINY__)
#define LGRT_AVR_TMP "r16"
#define LGRT_AVR_ZERO "r17"
#else
#define LGRT_AVR_TMP "r0"
#define LGRT_AVR_ZERO "r1"
#endif

/*
 * Workaround: Clang before 16, AVR: it defines no macro for what the core has,
 * so these calls reach anywhere on any core, and those that depend on the
 * other macros below take the forms that every core has.
 */
#if defined(__AVR_HAVE_JMP_CALL__)
#define LGRT_AVR_CALL(f) "call " f "\n"
#define LGRT_AVR_JUMP(f) "jmp " f "\n"
#elif defined(__clang__) && __clang_major__ < 16
#define LGRT_AVR_CALL(f) \
    "push r30\n" \
    "push r31\n" \
    "ldi r30, lo8(gs(" f "))\n" \
    "ldi r31, hi8(gs(" f "))\n" \
    "icall\n" \
    "pop r31\n" \
    "pop r30\n"
#define LGRT_AVR_JUMP(f) \
    LGRT_AVR_CALL(f) \
    "ret\n"
#else
#define LGRT_AVR_CALL(f) "rcall " f "\n"
#define LGRT_AVR_JUMP(f) "rjmp " f "\n"
#endif

#define LGRT_AVR_RAMPZ "0x3b"
#define LGRT_AVR_SPL "0x3d"
#define LGRT_AVR_SPH "0x3e"

/* With more than 64 KiB of data memory, Z reads it through RAMPZ too. */
#if defined(__AVR_ARCH__) && (__AVR_ARCH__ == 105 || __AVR_ARCH__ == 107)
#define LGRT_AVR_CLEAR_RAMPZ "out " LGRT_AVR_RAMPZ ", " LGRT_AVR_ZERO "\n"
#else
#define LGRT_AVR_CLEAR_RAMPZ ""
#endif

/*
 * Reads the next byte of flash, from Z, or from RAMPZ:Z where flash exceeds
 * 64 KiB, which only the post-increment forms step by themselves. Reduced
 * cores read flash through data memory.
 */
#if defined(__AVR_TINY__)
#define LGRT_AVR_READ(r) "ld " r ", Z+\n"
#elif defined(__AVR_HAVE_ELPMX__)
#define LGRT_AVR_READ(r) "elpm " r ", Z+\n"
#elif defined(__AVR_HAVE_ELPM__)
#define LGRT_AVR_READ(r) \
    "elpm\n" \
    "mov " r ", r0\n" \
    "adiw r30, 1\n" \
    "brcc 9f\n" \
    "in r0, " LGRT_AVR_RAMPZ "\n" \
    "inc r0\n" \
    "out " LGRT_AVR_RAMPZ ", r0\n" \
    "9:\n"
#elif defined(__AVR_HAVE_LPMX__)
#define LGRT_AVR_READ(r) "lpm " r ", Z+\n"
#else
#define LGRT_AVR_READ(r) \
    "lpm\n" \
    "mov " r ", r0\n" \
    "adiw r30, 1\n"
#endif

#if defined(__AVR_HAVE_ELPM__)
#define LGRT_AVR_SET_RAMPZ(r) "out " LGRT_AVR_RAMPZ ", " r "\n"
#else
#define LGRT_AVR_SET_RAMPZ(r)
#endif

#define LGRT_AVR_ENTRY(name, end) \
    ".globl " name "\n" \
    ".hidden " name "\n" \
    ".type " name ", @function\n" \
    name ":\n" \
    ".size " name ", " end " - " name "\n"

#define LGRT_AVR_BEGIN(name) \
    ".pushsection .text." name ",\"ax\",@progbits\n" \
    ".globl " name "\n" \
    ".hidden " name "\n" \
    ".type " name ", @function\n" \
    name ":\n"

#define LGRT_AVR_END(name) \
    ".size " name ", . - " name "\n" \
    ".popsection\n"

#define LGRT_AVR_NEG2(r1, r0) \
    "com " r1 "\n" \
    "neg " r0 "\n" \
    "sbci " r1 ", -1\n"

#define LGRT_AVR_NEG3(r2, r1, r0) \
    "com " r2 "\n" \
    "com " r1 "\n" \
    "neg " r0 "\n" \
    "sbci " r1 ", -1\n" \
    "sbci " r2 ", -1\n"

#define LGRT_AVR_NEG4(r3, r2, r1, r0) \
    "com " r3 "\n" \
    "com " r2 "\n" \
    "com " r1 "\n" \
    "neg " r0 "\n" \
    "sbci " r1 ", -1\n" \
    "sbci " r2 ", -1\n" \
    "sbci " r3 ", -1\n"

/* Loads the temporary register with a count, through r, left at zero. */
#define LGRT_AVR_COUNT(r, n) \
    "ldi " r ", " n "\n" \
    "mov " LGRT_AVR_TMP ", " r "\n" \
    "clr " r "\n"

/*
 * The compilers reference these where a program has initialised or zeroed
 * data, constructors, or destructors. The startup code falls through the
 * sections .init0 to .init9, and the exit through .fini9 to .fini0, so these
 * do not return. The symbols are weak for linker scripts that lack them.
 */

#if defined(__AVR_TINY__)
#define LGRT_AVR_FLASH_DATA " + 0x4000"
#define LGRT_AVR_KEPT "r18"
#else
#define LGRT_AVR_FLASH_DATA ""
#define LGRT_AVR_KEPT "r17"
#endif

/* Workaround: Clang, reduced AVR cores: it rejects the icall they have. */
#if defined(__AVR_TINY__)
#define LGRT_AVR_ICALL ".word 0x9509\n"
#elif defined(__AVR_HAVE_EIJMP_EICALL__)
#define LGRT_AVR_ICALL "eicall\n"
#else
#define LGRT_AVR_ICALL "icall\n"
#endif

#if defined(__AVR_HAVE_ELPM__)
#define LGRT_AVR_LDI_HH8(r, symbol) "ldi " r ", hh8(" symbol ")\n"
#define LGRT_AVR_STEP_HH8(op, value) op " r16, " value "\n"
#define LGRT_AVR_CMP_HH8(symbol) \
    "ldi r24, hh8(" symbol ")\n" \
    "cpc r16, r24\n"
#else
#define LGRT_AVR_LDI_HH8(r, symbol)
#define LGRT_AVR_STEP_HH8(op, value)
#define LGRT_AVR_CMP_HH8(symbol)
#endif

__asm__ (
    ".pushsection .init4,\"ax\",@progbits\n"
    ".weak __data_start\n"
    ".weak __data_end\n"
    ".weak __data_load_start\n"
    ".weak __bss_start\n"
    ".weak __bss_end\n"
    ".globl __do_copy_data\n"
    ".hidden __do_copy_data\n"
    "__do_copy_data:\n"
    "ldi r24, hi8(__data_end)\n"
    "ldi r26, lo8(__data_start)\n"
    "ldi r27, hi8(__data_start)\n"
    "ldi r30, lo8(__data_load_start" LGRT_AVR_FLASH_DATA ")\n"
    "ldi r31, hi8(__data_load_start" LGRT_AVR_FLASH_DATA ")\n"
    LGRT_AVR_LDI_HH8("r25", "__data_load_start")
    LGRT_AVR_SET_RAMPZ("r25")
    "rjmp 2f\n"
    "1:\n"
    LGRT_AVR_READ(LGRT_AVR_TMP)
    "st X+, " LGRT_AVR_TMP "\n"
    "2:\n"
    "cpi r26, lo8(__data_end)\n"
    "cpc r27, r24\n"
    "brne 1b\n"
    LGRT_AVR_CLEAR_RAMPZ
    ".globl __do_clear_bss\n"
    ".hidden __do_clear_bss\n"
    "__do_clear_bss:\n"
    "ldi r24, hi8(__bss_end)\n"
    "ldi r26, lo8(__bss_start)\n"
    "ldi r27, hi8(__bss_start)\n"
    "rjmp 2f\n"
    "1:\n"
    "st X+, " LGRT_AVR_ZERO "\n"
    "2:\n"
    "cpi r26, lo8(__bss_end)\n"
    "cpc r27, r24\n"
    "brne 1b\n"
    ".popsection\n"
);

/*
 * Constructors run from the last to the first, and destructors from the first
 * to the last, in registers that they keep.
 */
__asm__ (
    ".pushsection .init6,\"ax\",@progbits\n"
    ".weak __ctors_start\n"
    ".weak __ctors_end\n"
    ".globl __do_global_ctors\n"
    ".hidden __do_global_ctors\n"
    "__do_global_ctors:\n"
    "ldi " LGRT_AVR_KEPT ", hi8(__ctors_start)\n"
    "ldi r28, lo8(__ctors_end)\n"
    "ldi r29, hi8(__ctors_end)\n"
    LGRT_AVR_LDI_HH8("r16", "__ctors_end")
    "rjmp 2f\n"
    "1:\n"
    "subi r28, 2\n"
    "sbci r29, 0\n"
    LGRT_AVR_STEP_HH8("sbci", "0")
    "mov r30, r28\n"
    "mov r31, r29\n"
    LGRT_AVR_SET_RAMPZ("r16")
    LGRT_AVR_READ("r24")
    LGRT_AVR_READ("r25")
    LGRT_AVR_CLEAR_RAMPZ
    "mov r30, r24\n"
    "mov r31, r25\n"
    LGRT_AVR_ICALL
    "2:\n"
    "cpi r28, lo8(__ctors_start)\n"
    "cpc r29, " LGRT_AVR_KEPT "\n"
    LGRT_AVR_CMP_HH8("__ctors_start")
    "brne 1b\n"
    ".popsection\n"
);

__asm__ (
    ".pushsection .fini6,\"ax\",@progbits\n"
    ".weak __dtors_start\n"
    ".weak __dtors_end\n"
    ".globl __do_global_dtors\n"
    ".hidden __do_global_dtors\n"
    "__do_global_dtors:\n"
    "ldi " LGRT_AVR_KEPT ", hi8(__dtors_end)\n"
    "ldi r28, lo8(__dtors_start)\n"
    "ldi r29, hi8(__dtors_start)\n"
    LGRT_AVR_LDI_HH8("r16", "__dtors_start")
    "rjmp 2f\n"
    "1:\n"
    "mov r30, r28\n"
    "mov r31, r29\n"
    LGRT_AVR_SET_RAMPZ("r16")
    LGRT_AVR_READ("r24")
    LGRT_AVR_READ("r25")
    LGRT_AVR_CLEAR_RAMPZ
    "subi r28, -2\n"
    "sbci r29, -1\n"
    LGRT_AVR_STEP_HH8("sbci", "-1")
    "mov r30, r24\n"
    "mov r31, r25\n"
    LGRT_AVR_ICALL
    "2:\n"
    "cpi r28, lo8(__dtors_end)\n"
    "cpc r29, " LGRT_AVR_KEPT "\n"
    LGRT_AVR_CMP_HH8("__dtors_end")
    "brne 1b\n"
    ".popsection\n"
);

__asm__ (
    LGRT_AVR_BEGIN("__negsi2")
    LGRT_AVR_NEG4("r25", "r24", "r23", "r22")
    "ret\n"
    LGRT_AVR_END("__negsi2")
);

__asm__ (
    LGRT_AVR_BEGIN("__bswapsi2")
    "mov " LGRT_AVR_TMP ", r22\n"
    "mov r22, r25\n"
    "mov r25, " LGRT_AVR_TMP "\n"
    "mov " LGRT_AVR_TMP ", r23\n"
    "mov r23, r24\n"
    "mov r24, " LGRT_AVR_TMP "\n"
    "ret\n"
    LGRT_AVR_END("__bswapsi2")
);

/* Each takes r25:r24 or r25:r22, and returns in r25:r24. */

__asm__ (
    LGRT_AVR_BEGIN("__clzhi2")
    "clr " LGRT_AVR_TMP "\n"
    "1:\n"
    "tst r25\n"
    "brmi 2f\n"
    "lsl r24\n"
    "rol r25\n"
    "inc " LGRT_AVR_TMP "\n"
    "sbrs " LGRT_AVR_TMP ", 4\n"
    "rjmp 1b\n"
    "2:\n"
    "mov r24, " LGRT_AVR_TMP "\n"
    "clr r25\n"
    "ret\n"
    LGRT_AVR_END("__clzhi2")
);

__asm__ (
    LGRT_AVR_BEGIN("__clzsi2")
    "push r22\n"
    "push r23\n"
    "clr " LGRT_AVR_TMP "\n"
    "1:\n"
    "tst r25\n"
    "brmi 2f\n"
    "lsl r22\n"
    "rol r23\n"
    "rol r24\n"
    "rol r25\n"
    "inc " LGRT_AVR_TMP "\n"
    "sbrs " LGRT_AVR_TMP ", 5\n"
    "rjmp 1b\n"
    "2:\n"
    "mov r24, " LGRT_AVR_TMP "\n"
    "clr r25\n"
    "pop r23\n"
    "pop r22\n"
    "ret\n"
    LGRT_AVR_END("__clzsi2")
);

__asm__ (
    LGRT_AVR_BEGIN("__ctzhi2")
    "clr " LGRT_AVR_TMP "\n"
    "1:\n"
    "sbrc r24, 0\n"
    "rjmp 2f\n"
    "lsr r25\n"
    "ror r24\n"
    "inc " LGRT_AVR_TMP "\n"
    "sbrs " LGRT_AVR_TMP ", 4\n"
    "rjmp 1b\n"
    "2:\n"
    "mov r24, " LGRT_AVR_TMP "\n"
    "clr r25\n"
    "ret\n"
    LGRT_AVR_END("__ctzhi2")
);

__asm__ (
    LGRT_AVR_BEGIN("__ctzsi2")
    "push r22\n"
    "push r23\n"
    "clr " LGRT_AVR_TMP "\n"
    "1:\n"
    "sbrc r22, 0\n"
    "rjmp 2f\n"
    "lsr r25\n"
    "ror r24\n"
    "ror r23\n"
    "ror r22\n"
    "inc " LGRT_AVR_TMP "\n"
    "sbrs " LGRT_AVR_TMP ", 5\n"
    "rjmp 1b\n"
    "2:\n"
    "mov r24, " LGRT_AVR_TMP "\n"
    "clr r25\n"
    "pop r23\n"
    "pop r22\n"
    "ret\n"
    LGRT_AVR_END("__ctzsi2")
);

__asm__ (
    LGRT_AVR_BEGIN("__ffshi2")
    "clr " LGRT_AVR_TMP "\n"
    "1:\n"
    "inc " LGRT_AVR_TMP "\n"
    "lsr r25\n"
    "ror r24\n"
    "brcs 2f\n"
    "sbrs " LGRT_AVR_TMP ", 4\n"
    "rjmp 1b\n"
    "clr " LGRT_AVR_TMP "\n"
    "2:\n"
    "mov r24, " LGRT_AVR_TMP "\n"
    "clr r25\n"
    "ret\n"
    LGRT_AVR_END("__ffshi2")
);

__asm__ (
    LGRT_AVR_BEGIN("__ffssi2")
    "push r22\n"
    "push r23\n"
    "clr " LGRT_AVR_TMP "\n"
    "1:\n"
    "inc " LGRT_AVR_TMP "\n"
    "lsr r25\n"
    "ror r24\n"
    "ror r23\n"
    "ror r22\n"
    "brcs 2f\n"
    "sbrs " LGRT_AVR_TMP ", 5\n"
    "rjmp 1b\n"
    "clr " LGRT_AVR_TMP "\n"
    "2:\n"
    "mov r24, " LGRT_AVR_TMP "\n"
    "clr r25\n"
    "pop r23\n"
    "pop r22\n"
    "ret\n"
    LGRT_AVR_END("__ffssi2")
);

/* Adds the set bits of a register to the temporary one, and clears it. */
#define LGRT_AVR_COUNT_ONES(r) \
    "1:\n" \
    "lsr " r "\n" \
    "adc " LGRT_AVR_TMP ", " LGRT_AVR_ZERO "\n" \
    "tst " r "\n" \
    "brne 1b\n"

/* The compilers extend its result themselves. */
__asm__ (
    LGRT_AVR_BEGIN("__popcountqi2")
    "clr " LGRT_AVR_TMP "\n"
    LGRT_AVR_COUNT_ONES("r24")
    "mov r24, " LGRT_AVR_TMP "\n"
    "ret\n"
    LGRT_AVR_END("__popcountqi2")
);

__asm__ (
    LGRT_AVR_BEGIN("__popcounthi2")
    "clr " LGRT_AVR_TMP "\n"
    LGRT_AVR_COUNT_ONES("r24")
    LGRT_AVR_COUNT_ONES("r25")
    "mov r24, " LGRT_AVR_TMP "\n"
    "ret\n"
    LGRT_AVR_END("__popcounthi2")
);

__asm__ (
    LGRT_AVR_BEGIN("__popcountsi2")
    "push r22\n"
    "push r23\n"
    "clr " LGRT_AVR_TMP "\n"
    LGRT_AVR_COUNT_ONES("r22")
    LGRT_AVR_COUNT_ONES("r23")
    LGRT_AVR_COUNT_ONES("r24")
    LGRT_AVR_COUNT_ONES("r25")
    "mov r24, " LGRT_AVR_TMP "\n"
    "pop r23\n"
    "pop r22\n"
    "ret\n"
    LGRT_AVR_END("__popcountsi2")
);

/* __parityqi2 returns in r25:r24 too. The wider ones fold into it. */
__asm__ (
    ".pushsection .text.__paritysi2,\"ax\",@progbits\n"
    LGRT_AVR_ENTRY("__paritysi2", ".Llgrt_avr_parity_end")
    "eor r24, r22\n"
    "eor r24, r23\n"
    LGRT_AVR_ENTRY("__parityhi2", ".Llgrt_avr_parity_end")
    "eor r24, r25\n"
    LGRT_AVR_ENTRY("__parityqi2", ".Llgrt_avr_parity_end")
    "mov " LGRT_AVR_TMP ", r24\n"
    "swap " LGRT_AVR_TMP "\n"
    "eor r24, " LGRT_AVR_TMP "\n"
    "mov " LGRT_AVR_TMP ", r24\n"
    "lsr " LGRT_AVR_TMP "\n"
    "lsr " LGRT_AVR_TMP "\n"
    "eor r24, " LGRT_AVR_TMP "\n"
    "mov " LGRT_AVR_TMP ", r24\n"
    "lsr " LGRT_AVR_TMP "\n"
    "eor r24, " LGRT_AVR_TMP "\n"
    "andi r24, 1\n"
    "clr r25\n"
    "ret\n"
    ".Llgrt_avr_parity_end:\n"
    ".popsection\n"
);

/*
 * The divisions shift the dividend into a remainder of its width, and the bits
 * of the quotient into the dividend. A carry out of the remainder is its one
 * more bit, and means that the remainder exceeds the divisor.
 */

/* r24 / r22, returning the quotient in r24 and the remainder in r25. */
__asm__ (
    LGRT_AVR_BEGIN("__udivmodqi4")
    LGRT_AVR_COUNT("r25", "8")
    "1:\n"
    "lsl r24\n"
    "rol r25\n"
    "brcs 2f\n"
    "cp r25, r22\n"
    "brcs 3f\n"
    "2:\n"
    "sub r25, r22\n"
    "inc r24\n"
    "3:\n"
    "dec " LGRT_AVR_TMP "\n"
    "brne 1b\n"
    "ret\n"
    LGRT_AVR_END("__udivmodqi4")
);

/*
 * The signed ones divide the magnitudes, then negate the quotient if the signs
 * differ, which the stack remembers, and the remainder if the dividend is
 * negative, which T remembers.
 */
__asm__ (
    LGRT_AVR_BEGIN("__divmodqi4")
    "push r22\n"
    "mov " LGRT_AVR_TMP ", r24\n"
    "eor " LGRT_AVR_TMP ", r22\n"
    "push " LGRT_AVR_TMP "\n"
    "bst r24, 7\n"
    "sbrc r24, 7\n"
    "neg r24\n"
    "sbrc r22, 7\n"
    "neg r22\n"
    LGRT_AVR_CALL("__udivmodqi4")
    "pop " LGRT_AVR_TMP "\n"
    "sbrc " LGRT_AVR_TMP ", 7\n"
    "neg r24\n"
    "brtc 1f\n"
    "neg r25\n"
    "1:\n"
    "pop r22\n"
    "ret\n"
    LGRT_AVR_END("__divmodqi4")
);

#define LGRT_AVR_DIVMOD(name, udivmod, a, b, neg_a, neg_b, neg_q, neg_r) \
    LGRT_AVR_BEGIN(name) \
    "mov " LGRT_AVR_TMP ", " a "\n" \
    "eor " LGRT_AVR_TMP ", " b "\n" \
    "push " LGRT_AVR_TMP "\n" \
    "bst " a ", 7\n" \
    "sbrs " a ", 7\n" \
    "rjmp 1f\n" \
    neg_a \
    "1:\n" \
    "sbrs " b ", 7\n" \
    "rjmp 2f\n" \
    neg_b \
    "2:\n" \
    LGRT_AVR_CALL(udivmod) \
    "pop " LGRT_AVR_TMP "\n" \
    "sbrs " LGRT_AVR_TMP ", 7\n" \
    "rjmp 3f\n" \
    neg_q \
    "3:\n" \
    "brtc 4f\n" \
    neg_r \
    "4:\n" \
    "ret\n" \
    LGRT_AVR_END(name)

/*
 * r25:r24 / r23:r22, returning the quotient in r23:r22 and the remainder in
 * r25:r24.
 */
__asm__ (
    LGRT_AVR_BEGIN("__udivmodhi4")
    "push r26\n"
    "push r27\n"
    LGRT_AVR_COUNT("r26", "16")
    "clr r27\n"
    "1:\n"
    "lsl r24\n"
    "rol r25\n"
    "rol r26\n"
    "rol r27\n"
    "brcs 2f\n"
    "cp r26, r22\n"
    "cpc r27, r23\n"
    "brcs 3f\n"
    "2:\n"
    "sub r26, r22\n"
    "sbc r27, r23\n"
    "inc r24\n"
    "3:\n"
    "dec " LGRT_AVR_TMP "\n"
    "brne 1b\n"
    "mov r22, r24\n"
    "mov r23, r25\n"
    "mov r24, r26\n"
    "mov r25, r27\n"
    "pop r27\n"
    "pop r26\n"
    "ret\n"
    LGRT_AVR_END("__udivmodhi4")
);

__asm__ (
    LGRT_AVR_DIVMOD(
        "__divmodhi4", "__udivmodhi4", "r25", "r23",
        LGRT_AVR_NEG2("r25", "r24"), LGRT_AVR_NEG2("r23", "r22"),
        LGRT_AVR_NEG2("r23", "r22"), LGRT_AVR_NEG2("r25", "r24")
    )
);

/*
 * r25:r22 / r21:r18, returning the quotient in r21:r18 and the remainder in
 * r25:r22.
 */
__asm__ (
    LGRT_AVR_BEGIN("__udivmodsi4")
    "push r26\n"
    "push r27\n"
    "push r30\n"
    "push r31\n"
    LGRT_AVR_COUNT("r26", "32")
    "clr r27\n"
    "clr r30\n"
    "clr r31\n"
    "1:\n"
    "lsl r22\n"
    "rol r23\n"
    "rol r24\n"
    "rol r25\n"
    "rol r26\n"
    "rol r27\n"
    "rol r30\n"
    "rol r31\n"
    "brcs 2f\n"
    "cp r26, r18\n"
    "cpc r27, r19\n"
    "cpc r30, r20\n"
    "cpc r31, r21\n"
    "brcs 3f\n"
    "2:\n"
    "sub r26, r18\n"
    "sbc r27, r19\n"
    "sbc r30, r20\n"
    "sbc r31, r21\n"
    "inc r22\n"
    "3:\n"
    "dec " LGRT_AVR_TMP "\n"
    "brne 1b\n"
    "mov r18, r22\n"
    "mov r19, r23\n"
    "mov r20, r24\n"
    "mov r21, r25\n"
    "mov r22, r26\n"
    "mov r23, r27\n"
    "mov r24, r30\n"
    "mov r25, r31\n"
    "pop r31\n"
    "pop r30\n"
    "pop r27\n"
    "pop r26\n"
    "ret\n"
    LGRT_AVR_END("__udivmodsi4")
);

__asm__ (
    LGRT_AVR_DIVMOD(
        "__divmodsi4", "__udivmodsi4", "r25", "r21",
        LGRT_AVR_NEG4("r25", "r24", "r23", "r22"),
        LGRT_AVR_NEG4("r21", "r20", "r19", "r18"),
        LGRT_AVR_NEG4("r21", "r20", "r19", "r18"),
        LGRT_AVR_NEG4("r25", "r24", "r23", "r22")
    )
);

/* r24 * r22, returning in r24. */
#if defined(__AVR_HAVE_MUL__)
__asm__ (
    LGRT_AVR_BEGIN("__mulqi3")
    "mul r24, r22\n"
    "mov r24, r0\n"
    "clr r1\n"
    "ret\n"
    LGRT_AVR_END("__mulqi3")
);
#else
__asm__ (
    LGRT_AVR_BEGIN("__mulqi3")
    "push r22\n"
    "clr " LGRT_AVR_TMP "\n"
    "1:\n"
    "lsr r22\n"
    "brcc 2f\n"
    "add " LGRT_AVR_TMP ", r24\n"
    "2:\n"
    "lsl r24\n"
    "tst r22\n"
    "brne 1b\n"
    "mov r24, " LGRT_AVR_TMP "\n"
    "pop r22\n"
    "ret\n"
    LGRT_AVR_END("__mulqi3")
);
#endif

/* r25:r24 * r23:r22, returning in r25:r24. */
#if defined(__AVR_HAVE_MUL__)
__asm__ (
    LGRT_AVR_BEGIN("__mulhi3")
    "mul r25, r22\n"
    "mov r25, r0\n"
    "mul r24, r23\n"
    "add r25, r0\n"
    "mul r24, r22\n"
    "mov r24, r0\n"
    "add r25, r1\n"
    "clr r1\n"
    "ret\n"
    LGRT_AVR_END("__mulhi3")
);
#else
/* The zero register is the high half of the sum until the end. */
__asm__ (
    LGRT_AVR_BEGIN("__mulhi3")
    "push r22\n"
    "push r23\n"
    "clr " LGRT_AVR_TMP "\n"
    "1:\n"
    "lsr r23\n"
    "ror r22\n"
    "brcc 2f\n"
    "add " LGRT_AVR_TMP ", r24\n"
    "adc " LGRT_AVR_ZERO ", r25\n"
    "2:\n"
    "lsl r24\n"
    "rol r25\n"
    "tst r22\n"
    "brne 1b\n"
    "tst r23\n"
    "brne 1b\n"
    "mov r24, " LGRT_AVR_TMP "\n"
    "mov r25, " LGRT_AVR_ZERO "\n"
    "clr " LGRT_AVR_ZERO "\n"
    "pop r23\n"
    "pop r22\n"
    "ret\n"
    LGRT_AVR_END("__mulhi3")
);
#endif

#if !defined(__AVR_TINY__)

/*
 * Workaround: Clang before 13, AVR: it calls these for its shifts of 32 bits.
 */
#if defined(__clang__) && __clang_major__ < 13

#define LGRT_AVR_SHIFT_32(name, step) \
    __asm__ ( \
        LGRT_AVR_BEGIN(name) \
        "tst r20\n" \
        "breq 2f\n" \
        "1:\n" \
        step \
        "dec r20\n" \
        "brne 1b\n" \
        "2:\n" \
        "ret\n" \
        LGRT_AVR_END(name) \
    );

LGRT_AVR_SHIFT_32(
    "__ashlsi3",
    "lsl r22\n"
    "rol r23\n"
    "rol r24\n"
    "rol r25\n"
)

LGRT_AVR_SHIFT_32(
    "__lshrsi3",
    "lsr r25\n"
    "ror r24\n"
    "ror r23\n"
    "ror r22\n"
)

LGRT_AVR_SHIFT_32(
    "__ashrsi3",
    "asr r25\n"
    "ror r24\n"
    "ror r23\n"
    "ror r22\n"
)

#endif

/* Each operates on r25:r18 in place, taking r17:r10 where it takes more. */

__asm__ (
    LGRT_AVR_BEGIN("__adddi3")
    "add r18, r10\n"
    "adc r19, r11\n"
    "adc r20, r12\n"
    "adc r21, r13\n"
    "adc r22, r14\n"
    "adc r23, r15\n"
    "adc r24, r16\n"
    "adc r25, r17\n"
    "ret\n"
    LGRT_AVR_END("__adddi3")
);

__asm__ (
    LGRT_AVR_BEGIN("__subdi3")
    "sub r18, r10\n"
    "sbc r19, r11\n"
    "sbc r20, r12\n"
    "sbc r21, r13\n"
    "sbc r22, r14\n"
    "sbc r23, r15\n"
    "sbc r24, r16\n"
    "sbc r25, r17\n"
    "ret\n"
    LGRT_AVR_END("__subdi3")
);

/* The temporary register gets the sign extension of r26. */
#define LGRT_AVR_SIGN_R26 \
    "mov r0, r26\n" \
    "lsl r0\n" \
    "sbc r0, r0\n"

/* Adds the sign-extended r26. */
__asm__ (
    LGRT_AVR_BEGIN("__adddi3_s8")
    LGRT_AVR_SIGN_R26
    "add r18, r26\n"
    "adc r19, r0\n"
    "adc r20, r0\n"
    "adc r21, r0\n"
    "adc r22, r0\n"
    "adc r23, r0\n"
    "adc r24, r0\n"
    "adc r25, r0\n"
    "ret\n"
    LGRT_AVR_END("__adddi3_s8")
);

/* These compare in the flags, which are the results of the subtraction. */

__asm__ (
    LGRT_AVR_BEGIN("__cmpdi2")
    "cp r18, r10\n"
    "cpc r19, r11\n"
    "cpc r20, r12\n"
    "cpc r21, r13\n"
    "cpc r22, r14\n"
    "cpc r23, r15\n"
    "cpc r24, r16\n"
    "cpc r25, r17\n"
    "ret\n"
    LGRT_AVR_END("__cmpdi2")
);

__asm__ (
    LGRT_AVR_BEGIN("__cmpdi2_s8")
    LGRT_AVR_SIGN_R26
    "cp r18, r26\n"
    "cpc r19, r0\n"
    "cpc r20, r0\n"
    "cpc r21, r0\n"
    "cpc r22, r0\n"
    "cpc r23, r0\n"
    "cpc r24, r0\n"
    "cpc r25, r0\n"
    "ret\n"
    LGRT_AVR_END("__cmpdi2_s8")
);

__asm__ (
    LGRT_AVR_BEGIN("__negdi2")
    "com r25\n"
    "com r24\n"
    "com r23\n"
    "com r22\n"
    "com r21\n"
    "com r20\n"
    "com r19\n"
    "neg r18\n"
    "sbci r19, -1\n"
    "sbci r20, -1\n"
    "sbci r21, -1\n"
    "sbci r22, -1\n"
    "sbci r23, -1\n"
    "sbci r24, -1\n"
    "sbci r25, -1\n"
    "ret\n"
    LGRT_AVR_END("__negdi2")
);

__asm__ (
    LGRT_AVR_BEGIN("__bswapdi2")
    "mov r0, r18\n"
    "mov r18, r25\n"
    "mov r25, r0\n"
    "mov r0, r19\n"
    "mov r19, r24\n"
    "mov r24, r0\n"
    "mov r0, r20\n"
    "mov r20, r23\n"
    "mov r23, r0\n"
    "mov r0, r21\n"
    "mov r21, r22\n"
    "mov r22, r0\n"
    "ret\n"
    LGRT_AVR_END("__bswapdi2")
);

/* These shift by the byte in r16, as what r17 holds does not count. */

#define LGRT_AVR_SHIFT_LOOP(step) \
    "mov r0, r16\n" \
    "tst r0\n" \
    "breq 2f\n" \
    "1:\n" \
    step \
    "dec r0\n" \
    "brne 1b\n" \
    "2:\n" \
    "ret\n"

#define LGRT_AVR_SHIFT_LEFT \
    "lsl r18\n" \
    "rol r19\n" \
    "rol r20\n" \
    "rol r21\n" \
    "rol r22\n" \
    "rol r23\n" \
    "rol r24\n" \
    "rol r25\n"

#define LGRT_AVR_SHIFT_RIGHT(first) \
    first " r25\n" \
    "ror r24\n" \
    "ror r23\n" \
    "ror r22\n" \
    "ror r21\n" \
    "ror r20\n" \
    "ror r19\n" \
    "ror r18\n"

__asm__ (
    LGRT_AVR_BEGIN("__ashldi3")
    LGRT_AVR_SHIFT_LOOP(LGRT_AVR_SHIFT_LEFT)
    LGRT_AVR_END("__ashldi3")
);

__asm__ (
    LGRT_AVR_BEGIN("__lshrdi3")
    LGRT_AVR_SHIFT_LOOP(LGRT_AVR_SHIFT_RIGHT("lsr"))
    LGRT_AVR_END("__lshrdi3")
);

__asm__ (
    LGRT_AVR_BEGIN("__ashrdi3")
    LGRT_AVR_SHIFT_LOOP(LGRT_AVR_SHIFT_RIGHT("asr"))
    LGRT_AVR_END("__ashrdi3")
);

__asm__ (
    LGRT_AVR_BEGIN("__rotldi3")
    LGRT_AVR_SHIFT_LOOP(LGRT_AVR_SHIFT_LEFT "adc r18, r1\n")
    LGRT_AVR_END("__rotldi3")
);

/*
 * r25:r22 * r21:r18, returning in r25:r22, or in r25:r18 where the product is
 * whole.
 */
#if defined(__AVR_HAVE_MUL__)

/*
 * Adds the products of each pair of bytes of a column up in r30:r27:r26, with
 * r31 at zero, moves on to the next column by pushing the sum's low byte, and
 * pops the results at the end, as they overlap the operands.
 */
#define LGRT_AVR_MAC(x, y) \
    "mul " x ", " y "\n" \
    "add r26, r0\n" \
    "adc r27, r1\n" \
    "adc r30, r31\n"

#define LGRT_AVR_COLUMN \
    "push r26\n" \
    "mov r26, r27\n" \
    "mov r27, r30\n" \
    "clr r30\n"

#define LGRT_AVR_COLUMNS_BEGIN \
    "push r26\n" \
    "push r27\n" \
    "push r30\n" \
    "push r31\n" \
    "clr r26\n" \
    "clr r27\n" \
    "clr r30\n" \
    "clr r31\n"

#define LGRT_AVR_COLUMNS_END \
    "clr r1\n" \
    "pop r31\n" \
    "pop r30\n" \
    "pop r27\n" \
    "pop r26\n" \
    "ret\n"

__asm__ (
    LGRT_AVR_BEGIN("__mulsi3")
    LGRT_AVR_COLUMNS_BEGIN
    LGRT_AVR_MAC("r22", "r18")
    LGRT_AVR_COLUMN
    LGRT_AVR_MAC("r22", "r19")
    LGRT_AVR_MAC("r23", "r18")
    LGRT_AVR_COLUMN
    LGRT_AVR_MAC("r22", "r20")
    LGRT_AVR_MAC("r23", "r19")
    LGRT_AVR_MAC("r24", "r18")
    LGRT_AVR_COLUMN
    LGRT_AVR_MAC("r22", "r21")
    LGRT_AVR_MAC("r23", "r20")
    LGRT_AVR_MAC("r24", "r19")
    LGRT_AVR_MAC("r25", "r18")
    "mov r25, r26\n"
    "pop r24\n"
    "pop r23\n"
    "pop r22\n"
    LGRT_AVR_COLUMNS_END
    LGRT_AVR_END("__mulsi3")
);

__asm__ (
    LGRT_AVR_BEGIN("__umulsidi3")
    LGRT_AVR_COLUMNS_BEGIN
    LGRT_AVR_MAC("r22", "r18")
    LGRT_AVR_COLUMN
    LGRT_AVR_MAC("r22", "r19")
    LGRT_AVR_MAC("r23", "r18")
    LGRT_AVR_COLUMN
    LGRT_AVR_MAC("r22", "r20")
    LGRT_AVR_MAC("r23", "r19")
    LGRT_AVR_MAC("r24", "r18")
    LGRT_AVR_COLUMN
    LGRT_AVR_MAC("r22", "r21")
    LGRT_AVR_MAC("r23", "r20")
    LGRT_AVR_MAC("r24", "r19")
    LGRT_AVR_MAC("r25", "r18")
    LGRT_AVR_COLUMN
    LGRT_AVR_MAC("r23", "r21")
    LGRT_AVR_MAC("r24", "r20")
    LGRT_AVR_MAC("r25", "r19")
    LGRT_AVR_COLUMN
    LGRT_AVR_MAC("r24", "r21")
    LGRT_AVR_MAC("r25", "r20")
    LGRT_AVR_COLUMN
    LGRT_AVR_MAC("r25", "r21")
    "mov r24, r26\n"
    "mov r25, r27\n"
    "pop r23\n"
    "pop r22\n"
    "pop r21\n"
    "pop r20\n"
    "pop r19\n"
    "pop r18\n"
    LGRT_AVR_COLUMNS_END
    LGRT_AVR_END("__umulsidi3")
);

#else

/* The zero register and r27:r26 are the upper bytes of the sum, to the end. */
__asm__ (
    LGRT_AVR_BEGIN("__mulsi3")
    "push r18\n"
    "push r19\n"
    "push r20\n"
    "push r21\n"
    "push r26\n"
    "push r27\n"
    "push r30\n"
    "clr r0\n"
    "clr r26\n"
    "clr r27\n"
    "1:\n"
    "lsr r21\n"
    "ror r20\n"
    "ror r19\n"
    "ror r18\n"
    "brcc 2f\n"
    "add r0, r22\n"
    "adc r1, r23\n"
    "adc r26, r24\n"
    "adc r27, r25\n"
    "2:\n"
    "lsl r22\n"
    "rol r23\n"
    "rol r24\n"
    "rol r25\n"
    "mov r30, r18\n"
    "or r30, r19\n"
    "or r30, r20\n"
    "or r30, r21\n"
    "brne 1b\n"
    "mov r22, r0\n"
    "mov r23, r1\n"
    "mov r24, r26\n"
    "mov r25, r27\n"
    "clr r1\n"
    "pop r30\n"
    "pop r27\n"
    "pop r26\n"
    "pop r21\n"
    "pop r20\n"
    "pop r19\n"
    "pop r18\n"
    "ret\n"
    LGRT_AVR_END("__mulsi3")
);

/*
 * Adds the second operand above the first for each of its set bits, shifting
 * the sum and the first operand down together.
 */
__asm__ (
    LGRT_AVR_BEGIN("__umulsidi3")
    "push r26\n"
    "push r27\n"
    "push r30\n"
    "push r31\n"
    LGRT_AVR_COUNT("r26", "32")
    "clr r27\n"
    "clr r30\n"
    "clr r31\n"
    "1:\n"
    "clc\n"
    "sbrs r22, 0\n"
    "rjmp 2f\n"
    "add r26, r18\n"
    "adc r27, r19\n"
    "adc r30, r20\n"
    "adc r31, r21\n"
    "2:\n"
    "ror r31\n"
    "ror r30\n"
    "ror r27\n"
    "ror r26\n"
    "ror r25\n"
    "ror r24\n"
    "ror r23\n"
    "ror r22\n"
    "dec r0\n"
    "brne 1b\n"
    "mov r18, r22\n"
    "mov r19, r23\n"
    "mov r20, r24\n"
    "mov r21, r25\n"
    "mov r22, r26\n"
    "mov r23, r27\n"
    "mov r24, r30\n"
    "mov r25, r31\n"
    "pop r31\n"
    "pop r30\n"
    "pop r27\n"
    "pop r26\n"
    "ret\n"
    LGRT_AVR_END("__umulsidi3")
);

#endif

/*
 * Multiplies the magnitudes, and negates the product if the signs differ,
 * which T remembers.
 */
__asm__ (
    LGRT_AVR_BEGIN("__mulsidi3")
    "mov r0, r25\n"
    "eor r0, r21\n"
    "bst r0, 7\n"
    "sbrs r25, 7\n"
    "rjmp 1f\n"
    LGRT_AVR_NEG4("r25", "r24", "r23", "r22")
    "1:\n"
    "sbrs r21, 7\n"
    "rjmp 2f\n"
    LGRT_AVR_NEG4("r21", "r20", "r19", "r18")
    "2:\n"
    LGRT_AVR_CALL("__umulsidi3")
    "brtc 3f\n"
    LGRT_AVR_JUMP("__negdi2")
    "3:\n"
    "ret\n"
    LGRT_AVR_END("__mulsidi3")
);

/* r24:r22 * r20:r18, returning in r24:r22. */
__asm__ (
    LGRT_AVR_BEGIN("__mulpsi3")
    "push r21\n"
    "push r25\n"
    "clr r21\n"
    "clr r25\n"
    LGRT_AVR_CALL("__mulsi3")
    "pop r25\n"
    "pop r21\n"
    "ret\n"
    LGRT_AVR_END("__mulpsi3")
);

/*
 * r24:r22 / r20:r18, returning the quotient in r24:r22 and the remainder in
 * r20:r18.
 */
__asm__ (
    LGRT_AVR_BEGIN("__udivmodpsi4")
    "push r26\n"
    "push r27\n"
    "push r30\n"
    LGRT_AVR_COUNT("r26", "24")
    "clr r27\n"
    "clr r30\n"
    "1:\n"
    "lsl r22\n"
    "rol r23\n"
    "rol r24\n"
    "rol r26\n"
    "rol r27\n"
    "rol r30\n"
    "brcs 2f\n"
    "cp r26, r18\n"
    "cpc r27, r19\n"
    "cpc r30, r20\n"
    "brcs 3f\n"
    "2:\n"
    "sub r26, r18\n"
    "sbc r27, r19\n"
    "sbc r30, r20\n"
    "inc r22\n"
    "3:\n"
    "dec r0\n"
    "brne 1b\n"
    "mov r18, r26\n"
    "mov r19, r27\n"
    "mov r20, r30\n"
    "pop r30\n"
    "pop r27\n"
    "pop r26\n"
    "ret\n"
    LGRT_AVR_END("__udivmodpsi4")
);

__asm__ (
    LGRT_AVR_DIVMOD(
        "__divmodpsi4", "__udivmodpsi4", "r24", "r20",
        LGRT_AVR_NEG3("r24", "r23", "r22"), LGRT_AVR_NEG3("r20", "r19", "r18"),
        LGRT_AVR_NEG3("r24", "r23", "r22"), LGRT_AVR_NEG3("r20", "r19", "r18")
    )
);

/* Only cores with the multiply instructions get calls to these. */
#if defined(__AVR_HAVE_MUL__)

/* r19:r18 * r27:r26, returning in r25:r22. */
__asm__ (
    LGRT_AVR_BEGIN("__umulhisi3")
    "mul r18, r26\n"
    "mov r22, r0\n"
    "mov r23, r1\n"
    "mul r19, r27\n"
    "mov r24, r0\n"
    "mov r25, r1\n"
    "mul r18, r27\n"
    "add r23, r0\n"
    "adc r24, r1\n"
    "clr r1\n"
    "adc r25, r1\n"
    "mul r19, r26\n"
    "add r23, r0\n"
    "adc r24, r1\n"
    "clr r1\n"
    "adc r25, r1\n"
    "ret\n"
    LGRT_AVR_END("__umulhisi3")
);

/*
 * A negative operand read as unsigned is 2^16 too large, which adds the other
 * operand to the upper half of the product.
 */
__asm__ (
    LGRT_AVR_BEGIN("__mulhisi3")
    LGRT_AVR_CALL("__umulhisi3")
    "sbrs r19, 7\n"
    "rjmp 1f\n"
    "sub r24, r26\n"
    "sbc r25, r27\n"
    "1:\n"
    "sbrs r27, 7\n"
    "rjmp 2f\n"
    "sub r24, r18\n"
    "sbc r25, r19\n"
    "2:\n"
    "ret\n"
    LGRT_AVR_END("__mulhisi3")
);

/* The operand in r27:r26 is the signed one. */
__asm__ (
    LGRT_AVR_BEGIN("__usmulhisi3")
    LGRT_AVR_CALL("__umulhisi3")
    "sbrs r27, 7\n"
    "rjmp 1f\n"
    "sub r24, r18\n"
    "sbc r25, r19\n"
    "1:\n"
    "ret\n"
    LGRT_AVR_END("__usmulhisi3")
);

/* r27:r26, extended as the name says, * r21:r18, returning in r25:r22. */

__asm__ (
    LGRT_AVR_BEGIN("__muluhisi3")
    "mov r22, r26\n"
    "mov r23, r27\n"
    "clr r24\n"
    "clr r25\n"
    LGRT_AVR_JUMP("__mulsi3")
    LGRT_AVR_END("__muluhisi3")
);

__asm__ (
    LGRT_AVR_BEGIN("__mulshisi3")
    "mov r22, r26\n"
    "mov r23, r27\n"
    "mov r24, r27\n"
    "lsl r24\n"
    "sbc r24, r24\n"
    "mov r25, r24\n"
    LGRT_AVR_JUMP("__mulsi3")
    LGRT_AVR_END("__mulshisi3")
);

/* The compilers call this one for negative constants. */
__asm__ (
    LGRT_AVR_BEGIN("__mulohisi3")
    "mov r22, r26\n"
    "mov r23, r27\n"
    "ldi r24, -1\n"
    "ldi r25, -1\n"
    LGRT_AVR_JUMP("__mulsi3")
    LGRT_AVR_END("__mulohisi3")
);

/* The signed r25 * r24:r22, returning in r20:r18. */
__asm__ (
    LGRT_AVR_BEGIN("__mulsqipsi3")
    "push r21\n"
    "push r22\n"
    "push r23\n"
    "push r24\n"
    "push r25\n"
    "mov r18, r25\n"
    "mov r19, r25\n"
    "lsl r19\n"
    "sbc r19, r19\n"
    "mov r20, r19\n"
    "mov r21, r19\n"
    LGRT_AVR_CALL("__mulsi3")
    "mov r18, r22\n"
    "mov r19, r23\n"
    "mov r20, r24\n"
    "pop r25\n"
    "pop r24\n"
    "pop r23\n"
    "pop r22\n"
    "pop r21\n"
    "ret\n"
    LGRT_AVR_END("__mulsqipsi3")
);

#else

/*
 * The fractional multiplications, for the cores without their instructions:
 * r24 * r25, with r24 signed in the signed ones, shifted left by one,
 * returning in r23:r22. A negative operand read as unsigned is 2^8 too large,
 * which adds the other operand to the upper half of the product. r26 and the
 * zero register are the multiplicand until the end.
 */
__asm__ (
    ".pushsection .text.__fmul,\"ax\",@progbits\n"
    LGRT_AVR_ENTRY("__fmul", ".Llgrt_avr_fmul_end")
    "rcall 3f\n"
    "rjmp 2f\n"
    LGRT_AVR_ENTRY("__fmuls", ".Llgrt_avr_fmul_end")
    "rcall 3f\n"
    "sbrc r25, 7\n"
    "sub r23, r24\n"
    "rjmp 1f\n"
    LGRT_AVR_ENTRY("__fmulsu", ".Llgrt_avr_fmul_end")
    "rcall 3f\n"
    "1:\n"
    "sbrc r24, 7\n"
    "sub r23, r25\n"
    "2:\n"
    "lsl r22\n"
    "rol r23\n"
    "ret\n"
    "3:\n"
    "push r26\n"
    "mov r26, r24\n"
    "mov r0, r25\n"
    "clr r22\n"
    "clr r23\n"
    "4:\n"
    "lsr r0\n"
    "brcc 5f\n"
    "add r22, r26\n"
    "adc r23, r1\n"
    "5:\n"
    "lsl r26\n"
    "rol r1\n"
    "tst r0\n"
    "brne 4b\n"
    "clr r1\n"
    "pop r26\n"
    "ret\n"
    ".Llgrt_avr_fmul_end:\n"
    ".popsection\n"
);

#endif

/*
 * These load r22 upwards from flash at Z, or at r21:Z, whose top bit tells
 * that it points to data memory instead.
 */

#define LGRT_AVR_LOAD_1(prefix) prefix("r22")
#define LGRT_AVR_LOAD_2(prefix) LGRT_AVR_LOAD_1(prefix) prefix("r23")
#define LGRT_AVR_LOAD_3(prefix) LGRT_AVR_LOAD_2(prefix) prefix("r24")
#define LGRT_AVR_LOAD_4(prefix) LGRT_AVR_LOAD_3(prefix) prefix("r25")

#define LGRT_AVR_READ_RAM(r) "ld " r ", Z+\n"

/* __load_N reads the 64 KiB that lpm alone reaches. */
#define LGRT_AVR_READ_NEAR(r) \
    "lpm\n" \
    "mov " r ", r0\n" \
    "adiw r30, 1\n"

#define LGRT_AVR_FLASH_LOADS(n) \
    __asm__ ( \
        LGRT_AVR_BEGIN("__load_" #n) \
        "push r30\n" \
        "push r31\n" \
        LGRT_AVR_LOAD_##n(LGRT_AVR_READ_NEAR) \
        "pop r31\n" \
        "pop r30\n" \
        "ret\n" \
        LGRT_AVR_END("__load_" #n) \
    ); \
    __asm__ ( \
        LGRT_AVR_BEGIN("__fload_" #n) \
        "push r30\n" \
        "push r31\n" \
        LGRT_AVR_SET_RAMPZ("r21") \
        LGRT_AVR_LOAD_##n(LGRT_AVR_READ) \
        LGRT_AVR_CLEAR_RAMPZ \
        "pop r31\n" \
        "pop r30\n" \
        "ret\n" \
        LGRT_AVR_END("__fload_" #n) \
    ); \
    __asm__ ( \
        LGRT_AVR_BEGIN("__xload_" #n) \
        "push r30\n" \
        "push r31\n" \
        "sbrs r21, 7\n" \
        "rjmp 1f\n" \
        LGRT_AVR_LOAD_##n(LGRT_AVR_READ_RAM) \
        "rjmp 2f\n" \
        "1:\n" \
        LGRT_AVR_SET_RAMPZ("r21") \
        LGRT_AVR_LOAD_##n(LGRT_AVR_READ) \
        LGRT_AVR_CLEAR_RAMPZ \
        "2:\n" \
        "pop r31\n" \
        "pop r30\n" \
        "ret\n" \
        LGRT_AVR_END("__xload_" #n) \
    );

LGRT_AVR_FLASH_LOADS(1)
LGRT_AVR_FLASH_LOADS(2)
LGRT_AVR_FLASH_LOADS(3)
LGRT_AVR_FLASH_LOADS(4)

/*
 * These copy r25:r24 bytes, or r24 for the _qi ones, from r23:Z to X. The top
 * bit of r23 tells flash from data memory as in __xload_N, but for
 * __movmemf_N, whose source is always in flash.
 */

#define LGRT_AVR_COPY_LOOP(read) \
    "1:\n" \
    read \
    "st X+, r0\n" \
    "subi r24, 1\n" \
    "sbci r25, 0\n" \
    "brne 1b\n"

#define LGRT_AVR_COPY_SAVE \
    "push r24\n" \
    "push r25\n" \
    "push r26\n" \
    "push r27\n" \
    "push r30\n" \
    "push r31\n" \
    "mov r0, r24\n" \
    "or r0, r25\n" \
    "breq 3f\n"

#define LGRT_AVR_COPY_RESTORE \
    "3:\n" \
    "pop r31\n" \
    "pop r30\n" \
    "pop r27\n" \
    "pop r26\n" \
    "pop r25\n" \
    "pop r24\n" \
    "ret\n"

#define LGRT_AVR_COPY_FLASH \
    LGRT_AVR_SET_RAMPZ("r23") \
    LGRT_AVR_COPY_LOOP(LGRT_AVR_READ("r0")) \
    LGRT_AVR_CLEAR_RAMPZ

__asm__ (
    ".pushsection .text.__movmemf_qi,\"ax\",@progbits\n"
    LGRT_AVR_ENTRY("__movmemf_qi", ".Llgrt_avr_movmemf_end")
    "push r25\n"
    "clr r25\n"
    "rcall __movmemf_hi\n"
    "pop r25\n"
    "ret\n"
    LGRT_AVR_ENTRY("__movmemf_hi", ".Llgrt_avr_movmemf_end")
    LGRT_AVR_COPY_SAVE
    LGRT_AVR_COPY_FLASH
    LGRT_AVR_COPY_RESTORE
    ".Llgrt_avr_movmemf_end:\n"
    ".popsection\n"
);

__asm__ (
    ".pushsection .text.__movmemx_qi,\"ax\",@progbits\n"
    LGRT_AVR_ENTRY("__movmemx_qi", ".Llgrt_avr_movmemx_end")
    "push r25\n"
    "clr r25\n"
    "rcall __movmemx_hi\n"
    "pop r25\n"
    "ret\n"
    LGRT_AVR_ENTRY("__movmemx_hi", ".Llgrt_avr_movmemx_end")
    LGRT_AVR_COPY_SAVE
    "sbrc r23, 7\n"
    "rjmp 2f\n"
    LGRT_AVR_COPY_FLASH
    "rjmp 3f\n"
    "2:\n"
    LGRT_AVR_COPY_LOOP("ld r0, Z+\n")
    LGRT_AVR_COPY_RESTORE
    ".Llgrt_avr_movmemx_end:\n"
    ".popsection\n"
);

/*
 * Sets the stack pointer from Y, where that takes no masking of interrupts:
 * XMEGA cores keep them off after a write of the stack pointer, and it is one
 * write on the cores with 8 bits of it. Other cores have no routines of
 * -mcall-prologues, which would have to mask them.
 */
#if defined(__AVR_ARCH__) && __AVR_ARCH__ >= 102
#define LGRT_AVR_SET_SP \
    "out " LGRT_AVR_SPL ", r28\n" \
    "out " LGRT_AVR_SPH ", r29\n"
#elif defined(__AVR_HAVE_8BIT_SP__) || defined(__AVR_SP8__)
#define LGRT_AVR_SET_SP "out " LGRT_AVR_SPL ", r28\n"
#endif

#if defined(__AVR_HAVE_8BIT_SP__) || defined(__AVR_SP8__)
#define LGRT_AVR_GET_SP \
    "in r28, " LGRT_AVR_SPL "\n" \
    "clr r29\n"
#else
#define LGRT_AVR_GET_SP \
    "in r28, " LGRT_AVR_SPL "\n" \
    "in r29, " LGRT_AVR_SPH "\n"
#endif

#if defined(__AVR_HAVE_EIJMP_EICALL__)
#define LGRT_AVR_IJMP "eijmp\n"
#else
#define LGRT_AVR_IJMP "ijmp\n"
#endif

#if defined(LGRT_AVR_SET_SP)

/*
 * With -mcall-prologues, prologues jump into this, past the pushes of the
 * registers they do not save, 2 bytes each, with the size of their frame in
 * X and where to continue, as a word address, in Z. It leaves Y at the frame.
 */
__asm__ (
    LGRT_AVR_BEGIN("__prologue_saves__")
    "push r2\n"
    "push r3\n"
    "push r4\n"
    "push r5\n"
    "push r6\n"
    "push r7\n"
    "push r8\n"
    "push r9\n"
    "push r10\n"
    "push r11\n"
    "push r12\n"
    "push r13\n"
    "push r14\n"
    "push r15\n"
    "push r16\n"
    "push r17\n"
    "push r28\n"
    "push r29\n"
    LGRT_AVR_GET_SP
    "sub r28, r26\n"
    "sbc r29, r27\n"
    LGRT_AVR_SET_SP
    LGRT_AVR_IJMP
    LGRT_AVR_END("__prologue_saves__")
);

/*
 * Epilogues jump into this likewise, past the loads of the registers they did
 * not save, 2 bytes each, with Y just below the saved registers and their
 * number in r30. It returns to the caller of the function.
 */
__asm__ (
    LGRT_AVR_BEGIN("__epilogue_restores__")
    "ldd r2, Y+18\n"
    "ldd r3, Y+17\n"
    "ldd r4, Y+16\n"
    "ldd r5, Y+15\n"
    "ldd r6, Y+14\n"
    "ldd r7, Y+13\n"
    "ldd r8, Y+12\n"
    "ldd r9, Y+11\n"
    "ldd r10, Y+10\n"
    "ldd r11, Y+9\n"
    "ldd r12, Y+8\n"
    "ldd r13, Y+7\n"
    "ldd r14, Y+6\n"
    "ldd r15, Y+5\n"
    "ldd r16, Y+4\n"
    "ldd r17, Y+3\n"
    "ldd r26, Y+2\n"
    "ldd r27, Y+1\n"
    "add r28, r30\n"
    "adc r29, r1\n"
    LGRT_AVR_SET_SP
    "mov r28, r26\n"
    "mov r29, r27\n"
    "ret\n"
    LGRT_AVR_END("__epilogue_restores__")
);

#endif

/*
 * GCC dispatches jump tables through this, with the word address of the entry
 * in Z, the high byte of it in r24 on cores with a 3-byte program counter, and
 * in the carry it shifts out of Z on the other cores with RAMPZ. Before GCC 5,
 * the tables of the former cores stay within the 64 KiB that lpm alone
 * reaches.
 */
#if defined(__AVR_HAVE_EIJMP_EICALL__) && !defined(__clang__) && __GNUC__ < 5
#define LGRT_AVR_TABLE_HIGH
#define LGRT_AVR_TABLE_LOAD "lpm"
#elif defined(__AVR_HAVE_EIJMP_EICALL__)
#define LGRT_AVR_TABLE_HIGH \
    "rol r24\n" \
    "out " LGRT_AVR_RAMPZ ", r24\n"
#define LGRT_AVR_TABLE_LOAD "elpm"
#elif defined(__AVR_HAVE_ELPM__)
#define LGRT_AVR_TABLE_HIGH \
    "clr r0\n" \
    "rol r0\n" \
    "out " LGRT_AVR_RAMPZ ", r0\n"
#define LGRT_AVR_TABLE_LOAD "elpm"
#else
#define LGRT_AVR_TABLE_HIGH
#define LGRT_AVR_TABLE_LOAD "lpm"
#endif

#if defined(__AVR_HAVE_LPMX__)
#define LGRT_AVR_TABLE_ENTRY \
    LGRT_AVR_TABLE_LOAD " r0, Z+\n" \
    LGRT_AVR_TABLE_LOAD " r31, Z\n" \
    "mov r30, r0\n"
#else
#define LGRT_AVR_TABLE_ENTRY \
    LGRT_AVR_TABLE_LOAD "\n" \
    "adiw r30, 1\n" \
    "push r0\n" \
    LGRT_AVR_TABLE_LOAD "\n" \
    "mov r31, r0\n" \
    "pop r30\n"
#endif

__asm__ (
    LGRT_AVR_BEGIN("__tablejump2__")
    "lsl r30\n"
    "rol r31\n"
    LGRT_AVR_TABLE_HIGH
    LGRT_AVR_TABLE_ENTRY
    LGRT_AVR_CLEAR_RAMPZ
    LGRT_AVR_IJMP
    LGRT_AVR_END("__tablejump2__")
);

#endif

#endif

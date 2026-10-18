//===-- int_lib.h - configuration header for compiler-rt  -----------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
// 2024/01/21 - Modified by Mintsuki for use inside freestanding-lgrt
//
//===----------------------------------------------------------------------===//
//
// This file is a configuration header for compiler-rt.
// This file is not part of the interface of this library.
//
//===----------------------------------------------------------------------===//

#ifndef INT_LIB_H
#define INT_LIB_H

// Assumption: Signed integral is 2's complement.
// Assumption: Right shift of signed negative is arithmetic shift.
// Assumption: Endianness is little or big (not mixed).

// ABI macro definitions

#ifdef __ARM_EABI__
#ifdef COMPILER_RT_ARMHF_TARGET
#define COMPILER_RT_ABI
#else
#define COMPILER_RT_ABI __attribute__((__pcs__("aapcs")))
#endif
#else
#define COMPILER_RT_ABI
#endif

#define AEABI_RTABI __attribute__((__pcs__("aapcs")))

#define ALWAYS_INLINE __attribute__((always_inline))
#define NOINLINE __attribute__((noinline))
#define NORETURN __attribute__((noreturn))
#define UNUSED __attribute__((unused))

#ifndef SYMBOL_NAME
#define STR(a) #a
#define XSTR(a) STR(a)
#define SYMBOL_NAME(name) XSTR(__USER_LABEL_PREFIX__) #name
#endif

#define COMPILER_RT_ALIAS(name, aliasname) \
  COMPILER_RT_ABI __typeof(name) aliasname __attribute__((__alias__(#name)));

// Include the standard compiler builtin headers we use functionality from.
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>

// Include the commonly used internal type definitions.
#include "int_types.h"

// Include internal utility function declarations.
#include "int_util.h"

COMPILER_RT_ABI int __paritysi2(si_int a);
COMPILER_RT_ABI int __paritydi2(di_int a);

COMPILER_RT_ABI di_int __divdi3(di_int a, di_int b);
COMPILER_RT_ABI si_int __divsi3(si_int a, si_int b);
COMPILER_RT_ABI su_int __udivsi3(su_int n, su_int d);

COMPILER_RT_ABI su_int __udivmodsi4(su_int a, su_int b, su_int *rem);
COMPILER_RT_ABI du_int __udivmoddi4(du_int a, du_int b, du_int *rem);
#ifdef CRT_HAS_128BIT
COMPILER_RT_ABI int __clzti2(ti_int a);
COMPILER_RT_ABI tu_int __udivmodti4(tu_int a, tu_int b, tu_int *rem);
#endif

#endif // INT_LIB_H

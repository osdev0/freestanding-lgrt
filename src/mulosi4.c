//===-- mulosi4.c - Implement __mulosi4 -----------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
// 2024/08/10 - Modified by Mintsuki for use inside freestanding-lgrt
//
//===----------------------------------------------------------------------===//
//
// This file implements __mulosi4 for the compiler_rt library.
//
//===----------------------------------------------------------------------===//

#define fixint_t si_int
#define fixuint_t su_int
#include "int_mulo_impl.inc"

// Returns: a * b

// Effects: sets *overflow to 1  if a * b overflows

COMPILER_RT_ABI si_int __mulosi4(si_int a, si_int b, int *overflow) {
  return __muloXi4(a, b, overflow);
}

#undef fixint_t
#undef fixuint_t

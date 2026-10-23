//===-- stdc_count_zeros_ull.c --------------------------------------------===//
//
// Part of freestanding-lgrt, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements stdc_count_zeros_ull from C23's stdbit.h.
//
//===----------------------------------------------------------------------===//

unsigned int stdc_count_zeros_ull(unsigned long long value) {
  // The zeros of value are the ones of its complement.
  return (unsigned int)__builtin_popcountll(~value);
}

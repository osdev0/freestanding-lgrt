//===-- stdc_first_leading_zero_ull.c -------------------------------------===//
//
// Part of freestanding-lgrt, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements stdc_first_leading_zero_ull from C23's stdbit.h.
//
//===----------------------------------------------------------------------===//

unsigned int stdc_first_leading_zero_ull(unsigned long long value) {
  // The first leading zero of value is the first leading one of its
  // complement.
  unsigned long long complement = ~value;
  if (complement == 0)
    return 0;
  return (unsigned int)__builtin_clzll(complement) + 1;
}

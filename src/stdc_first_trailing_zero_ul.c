//===-- stdc_first_trailing_zero_ul.c -------------------------------------===//
//
// Part of freestanding-lgrt, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements stdc_first_trailing_zero_ul from C23's stdbit.h.
//
//===----------------------------------------------------------------------===//

unsigned int stdc_first_trailing_zero_ul(unsigned long value) {
  // The first trailing zero of value is the first trailing one of its
  // complement.
  unsigned long complement = ~value;
  if (complement == 0)
    return 0;
  return (unsigned int)__builtin_ctzl(complement) + 1;
}

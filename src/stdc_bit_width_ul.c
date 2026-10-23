//===-- stdc_bit_width_ul.c -----------------------------------------------===//
//
// Part of freestanding-lgrt, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements stdc_bit_width_ul from C23's stdbit.h.
//
//===----------------------------------------------------------------------===//

unsigned int stdc_bit_width_ul(unsigned long value) {
  // The width of the type that __builtin_clzl counts the leading zeros of.
  const int bits = (int)sizeof(unsigned long) * __CHAR_BIT__;
  if (value == 0)
    return 0;
  return (unsigned int)(bits - __builtin_clzl(value));
}

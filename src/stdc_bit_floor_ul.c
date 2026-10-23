//===-- stdc_bit_floor_ul.c -----------------------------------------------===//
//
// Part of freestanding-lgrt, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements stdc_bit_floor_ul from C23's stdbit.h.
//
//===----------------------------------------------------------------------===//

unsigned long stdc_bit_floor_ul(unsigned long value) {
  // The width of the type that __builtin_clzl counts the leading zeros of.
  const int bits = (int)sizeof(unsigned long) * __CHAR_BIT__;
  if (value == 0)
    return 0;
  // 2 to the index of the most significant one of value.
  return 1ul << (bits - 1 - __builtin_clzl(value));
}

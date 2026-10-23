//===-- stdc_bit_floor_us.c -----------------------------------------------===//
//
// Part of freestanding-lgrt, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements stdc_bit_floor_us from C23's stdbit.h.
//
//===----------------------------------------------------------------------===//

unsigned short stdc_bit_floor_us(unsigned short value) {
  // The width of the type that __builtin_clz counts the leading zeros of.
  const int bits = (int)sizeof(unsigned int) * __CHAR_BIT__;
  if (value == 0)
    return 0;
  // 2 to the index of the most significant one of value.
  return (unsigned short)(1u << (bits - 1 - __builtin_clz(value)));
}

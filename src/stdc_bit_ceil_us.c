//===-- stdc_bit_ceil_us.c ------------------------------------------------===//
//
// Part of freestanding-lgrt, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements stdc_bit_ceil_us from C23's stdbit.h.
//
//===----------------------------------------------------------------------===//

unsigned short stdc_bit_ceil_us(unsigned short value) {
  // The width of the type that __builtin_clz counts the leading zeros of.
  const int bits = (int)sizeof(unsigned int) * __CHAR_BIT__;
  if (value <= 1)
    return 1;
  // 2 to the bit width of value - 1, where the type has a bit for it.
  int exponent = bits - __builtin_clz((unsigned int)value - 1);
  if (exponent >= (int)sizeof(value) * __CHAR_BIT__)
    return 0;
  return (unsigned short)(1u << exponent);
}

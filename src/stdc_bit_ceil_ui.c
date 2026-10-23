//===-- stdc_bit_ceil_ui.c ------------------------------------------------===//
//
// Part of freestanding-lgrt, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements stdc_bit_ceil_ui from C23's stdbit.h.
//
//===----------------------------------------------------------------------===//

unsigned int stdc_bit_ceil_ui(unsigned int value) {
  // The width of the type that __builtin_clz counts the leading zeros of.
  const int bits = (int)sizeof(unsigned int) * __CHAR_BIT__;
  if (value <= 1)
    return 1;
  // 2 to the bit width of value - 1, where the type has a bit for it.
  int exponent = bits - __builtin_clz(value - 1);
  if (exponent >= (int)sizeof(value) * __CHAR_BIT__)
    return 0;
  return 1u << exponent;
}

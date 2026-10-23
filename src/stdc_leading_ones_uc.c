//===-- stdc_leading_ones_uc.c --------------------------------------------===//
//
// Part of freestanding-lgrt, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements stdc_leading_ones_uc from C23's stdbit.h.
//
//===----------------------------------------------------------------------===//

unsigned int stdc_leading_ones_uc(unsigned char value) {
  // __builtin_clz counts the leading zeros of an unsigned int, which has these
  // many more bits than value.
  const int extra = (int)(sizeof(unsigned int) - sizeof(value)) * __CHAR_BIT__;
  // The leading ones of value are the leading zeros of its complement.
  unsigned char complement = (unsigned char)~value;
  if (complement == 0)
    return sizeof(value) * __CHAR_BIT__;
  return (unsigned int)(__builtin_clz(complement) - extra);
}

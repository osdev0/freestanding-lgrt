//===-- stdc_trailing_ones_uc.c -------------------------------------------===//
//
// Part of freestanding-lgrt, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements stdc_trailing_ones_uc from C23's stdbit.h.
//
//===----------------------------------------------------------------------===//

unsigned int stdc_trailing_ones_uc(unsigned char value) {
  // The trailing ones of value are the trailing zeros of its complement.
  unsigned char complement = (unsigned char)~value;
  if (complement == 0)
    return sizeof(value) * __CHAR_BIT__;
  return (unsigned int)__builtin_ctz(complement);
}

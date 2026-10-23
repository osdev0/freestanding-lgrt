//===-- stdc_first_leading_one_us.c ---------------------------------------===//
//
// Part of freestanding-lgrt, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements stdc_first_leading_one_us from C23's stdbit.h.
//
//===----------------------------------------------------------------------===//

unsigned int stdc_first_leading_one_us(unsigned short value) {
  // __builtin_clz counts the leading zeros of an unsigned int, which has these
  // many more bits than value.
  const int extra = (int)(sizeof(unsigned int) - sizeof(value)) * __CHAR_BIT__;
  if (value == 0)
    return 0;
  return (unsigned int)(__builtin_clz(value) - extra) + 1;
}

//===-- stdc_leading_zeros_ui.c -------------------------------------------===//
//
// Part of freestanding-lgrt, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements stdc_leading_zeros_ui from C23's stdbit.h.
//
//===----------------------------------------------------------------------===//

unsigned int stdc_leading_zeros_ui(unsigned int value) {
  if (value == 0)
    return sizeof(value) * __CHAR_BIT__;
  return (unsigned int)__builtin_clz(value);
}

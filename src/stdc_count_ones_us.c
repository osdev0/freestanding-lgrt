//===-- stdc_count_ones_us.c ----------------------------------------------===//
//
// Part of freestanding-lgrt, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements stdc_count_ones_us from C23's stdbit.h.
//
//===----------------------------------------------------------------------===//

unsigned int stdc_count_ones_us(unsigned short value) {
  return (unsigned int)__builtin_popcount(value);
}

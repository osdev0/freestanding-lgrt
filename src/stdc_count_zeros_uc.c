//===-- stdc_count_zeros_uc.c ---------------------------------------------===//
//
// Part of freestanding-lgrt, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements stdc_count_zeros_uc from C23's stdbit.h.
//
//===----------------------------------------------------------------------===//

unsigned int stdc_count_zeros_uc(unsigned char value) {
  // The zeros of value are the ones of its complement.
  return (unsigned int)__builtin_popcount((unsigned char)~value);
}

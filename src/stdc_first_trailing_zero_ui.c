//===-- stdc_first_trailing_zero_ui.c -------------------------------------===//
//
// Part of freestanding-lgrt, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements stdc_first_trailing_zero_ui from C23's stdbit.h.
//
//===----------------------------------------------------------------------===//

unsigned int stdc_first_trailing_zero_ui(unsigned int value) {
  // The first trailing zero of value is the first trailing one of its
  // complement.
  unsigned int complement = ~value;
  if (complement == 0)
    return 0;
  return (unsigned int)__builtin_ctz(complement) + 1;
}

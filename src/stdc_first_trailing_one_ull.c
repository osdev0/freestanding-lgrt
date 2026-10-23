//===-- stdc_first_trailing_one_ull.c -------------------------------------===//
//
// Part of freestanding-lgrt, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements stdc_first_trailing_one_ull from C23's stdbit.h.
//
//===----------------------------------------------------------------------===//

unsigned int stdc_first_trailing_one_ull(unsigned long long value) {
  if (value == 0)
    return 0;
  return (unsigned int)__builtin_ctzll(value) + 1;
}

//===-- stdc_has_single_bit_ui.c ------------------------------------------===//
//
// Part of freestanding-lgrt, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements stdc_has_single_bit_ui from C23's stdbit.h.
//
//===----------------------------------------------------------------------===//

_Bool stdc_has_single_bit_ui(unsigned int value) {
  return value != 0 && (value & (value - 1)) == 0;
}

//===-- cpu_model/aarch64.c - Support for __cpu_model builtin  ----*- C -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
// 2026/10/17 - Modified by Mintsuki for use inside freestanding-lgrt
//
//===----------------------------------------------------------------------===//
//
//  This file is based on LLVM's lib/Support/Host.cpp.
//  It implements __aarch64_have_lse_atomics for AArch64.
//
//===----------------------------------------------------------------------===//

#include <stdbool.h>

#if defined(__aarch64__)

// LSE support detection for out-of-line atomics
// using HWCAP and Auxiliary vector
_Bool __aarch64_have_lse_atomics
    __attribute__((visibility("hidden"), nocommon)) = false;

// When unimplemented, we leave __aarch64_have_lse_atomics initialized to false.

#endif

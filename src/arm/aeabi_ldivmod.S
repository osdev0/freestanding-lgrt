//===-- aeabi_ldivmod.S - EABI ldivmod implementation ---------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
// 2026/10/17 - Modified by Mintsuki for use inside freestanding-lgrt
//
//===----------------------------------------------------------------------===//

#include "../assembly.h"

// struct { int64_t quot, int64_t rem}
//        __aeabi_ldivmod(int64_t numerator, int64_t denominator) {
//   int64_t rem, quot;
//   quot = __divmoddi4(numerator, denominator, &rem);
//   return {quot, rem};
// }

        .syntax unified
        .p2align 2
DEFINE_COMPILERRT_FUNCTION(__aeabi_ldivmod)
        PACBTI_LANDING
#if defined(__ARM_FEATURE_PAC_DEFAULT)
        push    {r6, r12, lr}
#else
        push    {r6, lr}
#endif
        sub     sp, sp, #16
        add     r6, sp, #8
        str     r6, [sp]
        bl      SYMBOL_NAME(__divmoddi4)
        ldr     r2, [sp, #8]
        ldr     r3, [sp, #12]
        add     sp, sp, #16
#if defined(__ARM_FEATURE_PAC_DEFAULT)
        pop     {r6, r12, lr}
        PAC_RETURN
#else
        POP_PC_WITH_REGS r6
#endif
END_COMPILERRT_FUNCTION(__aeabi_ldivmod)

NO_EXEC_STACK_DIRECTIVE


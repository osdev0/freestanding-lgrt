//===-- aeabi_uldivmod.S - EABI uldivmod implementation -------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
// 2026/10/17 - Modified by Mintsuki for use inside cc-runtime
//
//===----------------------------------------------------------------------===//

#include "../assembly.h"

// struct { uint64_t quot, uint64_t rem}
//        __aeabi_uldivmod(uint64_t numerator, uint64_t denominator) {
//   uint64_t rem, quot;
//   quot = __udivmoddi4(numerator, denominator, &rem);
//   return {quot, rem};
// }

        .syntax unified
        .p2align 2
DEFINE_COMPILERRT_FUNCTION(__aeabi_uldivmod)
        PACBTI_LANDING
#if defined(__ARM_FEATURE_PAC_DEFAULT)
        push    {r6, r12, lr}
#else
        push    {r6, lr}
#endif
        sub	sp, sp, #16
        add	r6, sp, #8
        str	r6, [sp]
        bl	SYMBOL_NAME(__udivmoddi4)
        ldr	r2, [sp, #8]
        ldr	r3, [sp, #12]
        add	sp, sp, #16
#if defined(__ARM_FEATURE_PAC_DEFAULT)
        pop     {r6, r12, lr}
        PAC_RETURN
#else
        POP_PC_WITH_REGS r6
#endif
END_COMPILERRT_FUNCTION(__aeabi_uldivmod)

NO_EXEC_STACK_DIRECTIVE


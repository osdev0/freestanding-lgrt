// ==============================================================================
// The LLVM Project is under the Apache License v2.0 with LLVM Exceptions:
// ==============================================================================
//
//                                  Apache License
//                            Version 2.0, January 2004
//                         http://www.apache.org/licenses/
//
//     TERMS AND CONDITIONS FOR USE, REPRODUCTION, AND DISTRIBUTION
//
//     1. Definitions.
//
//       "License" shall mean the terms and conditions for use, reproduction,
//       and distribution as defined by Sections 1 through 9 of this document.
//
//       "Licensor" shall mean the copyright owner or entity authorized by
//       the copyright owner that is granting the License.
//
//       "Legal Entity" shall mean the union of the acting entity and all
//       other entities that control, are controlled by, or are under common
//       control with that entity. For the purposes of this definition,
//       "control" means (i) the power, direct or indirect, to cause the
//       direction or management of such entity, whether by contract or
//       otherwise, or (ii) ownership of fifty percent (50%) or more of the
//       outstanding shares, or (iii) beneficial ownership of such entity.
//
//       "You" (or "Your") shall mean an individual or Legal Entity
//       exercising permissions granted by this License.
//
//       "Source" form shall mean the preferred form for making modifications,
//       including but not limited to software source code, documentation
//       source, and configuration files.
//
//       "Object" form shall mean any form resulting from mechanical
//       transformation or translation of a Source form, including but
//       not limited to compiled object code, generated documentation,
//       and conversions to other media types.
//
//       "Work" shall mean the work of authorship, whether in Source or
//       Object form, made available under the License, as indicated by a
//       copyright notice that is included in or attached to the work
//       (an example is provided in the Appendix below).
//
//       "Derivative Works" shall mean any work, whether in Source or Object
//       form, that is based on (or derived from) the Work and for which the
//       editorial revisions, annotations, elaborations, or other modifications
//       represent, as a whole, an original work of authorship. For the purposes
//       of this License, Derivative Works shall not include works that remain
//       separable from, or merely link (or bind by name) to the interfaces of,
//       the Work and Derivative Works thereof.
//
//       "Contribution" shall mean any work of authorship, including
//       the original version of the Work and any modifications or additions
//       to that Work or Derivative Works thereof, that is intentionally
//       submitted to Licensor for inclusion in the Work by the copyright owner
//       or by an individual or Legal Entity authorized to submit on behalf of
//       the copyright owner. For the purposes of this definition, "submitted"
//       means any form of electronic, verbal, or written communication sent
//       to the Licensor or its representatives, including but not limited to
//       communication on electronic mailing lists, source code control systems,
//       and issue tracking systems that are managed by, or on behalf of, the
//       Licensor for the purpose of discussing and improving the Work, but
//       excluding communication that is conspicuously marked or otherwise
//       designated in writing by the copyright owner as "Not a Contribution."
//
//       "Contributor" shall mean Licensor and any individual or Legal Entity
//       on behalf of whom a Contribution has been received by Licensor and
//       subsequently incorporated within the Work.
//
//     2. Grant of Copyright License. Subject to the terms and conditions of
//       this License, each Contributor hereby grants to You a perpetual,
//       worldwide, non-exclusive, no-charge, royalty-free, irrevocable
//       copyright license to reproduce, prepare Derivative Works of,
//       publicly display, publicly perform, sublicense, and distribute the
//       Work and such Derivative Works in Source or Object form.
//
//     3. Grant of Patent License. Subject to the terms and conditions of
//       this License, each Contributor hereby grants to You a perpetual,
//       worldwide, non-exclusive, no-charge, royalty-free, irrevocable
//       (except as stated in this section) patent license to make, have made,
//       use, offer to sell, sell, import, and otherwise transfer the Work,
//       where such license applies only to those patent claims licensable
//       by such Contributor that are necessarily infringed by their
//       Contribution(s) alone or by combination of their Contribution(s)
//       with the Work to which such Contribution(s) was submitted. If You
//       institute patent litigation against any entity (including a
//       cross-claim or counterclaim in a lawsuit) alleging that the Work
//       or a Contribution incorporated within the Work constitutes direct
//       or contributory patent infringement, then any patent licenses
//       granted to You under this License for that Work shall terminate
//       as of the date such litigation is filed.
//
//     4. Redistribution. You may reproduce and distribute copies of the
//       Work or Derivative Works thereof in any medium, with or without
//       modifications, and in Source or Object form, provided that You
//       meet the following conditions:
//
//       (a) You must give any other recipients of the Work or
//           Derivative Works a copy of this License; and
//
//       (b) You must cause any modified files to carry prominent notices
//           stating that You changed the files; and
//
//       (c) You must retain, in the Source form of any Derivative Works
//           that You distribute, all copyright, patent, trademark, and
//           attribution notices from the Source form of the Work,
//           excluding those notices that do not pertain to any part of
//           the Derivative Works; and
//
//       (d) If the Work includes a "NOTICE" text file as part of its
//           distribution, then any Derivative Works that You distribute must
//           include a readable copy of the attribution notices contained
//           within such NOTICE file, excluding those notices that do not
//           pertain to any part of the Derivative Works, in at least one
//           of the following places: within a NOTICE text file distributed
//           as part of the Derivative Works; within the Source form or
//           documentation, if provided along with the Derivative Works; or,
//           within a display generated by the Derivative Works, if and
//           wherever such third-party notices normally appear. The contents
//           of the NOTICE file are for informational purposes only and
//           do not modify the License. You may add Your own attribution
//           notices within Derivative Works that You distribute, alongside
//           or as an addendum to the NOTICE text from the Work, provided
//           that such additional attribution notices cannot be construed
//           as modifying the License.
//
//       You may add Your own copyright statement to Your modifications and
//       may provide additional or different license terms and conditions
//       for use, reproduction, or distribution of Your modifications, or
//       for any such Derivative Works as a whole, provided Your use,
//       reproduction, and distribution of the Work otherwise complies with
//       the conditions stated in this License.
//
//     5. Submission of Contributions. Unless You explicitly state otherwise,
//       any Contribution intentionally submitted for inclusion in the Work
//       by You to the Licensor shall be under the terms and conditions of
//       this License, without any additional terms or conditions.
//       Notwithstanding the above, nothing herein shall supersede or modify
//       the terms of any separate license agreement you may have executed
//       with Licensor regarding such Contributions.
//
//     6. Trademarks. This License does not grant permission to use the trade
//       names, trademarks, service marks, or product names of the Licensor,
//       except as required for reasonable and customary use in describing the
//       origin of the Work and reproducing the content of the NOTICE file.
//
//     7. Disclaimer of Warranty. Unless required by applicable law or
//       agreed to in writing, Licensor provides the Work (and each
//       Contributor provides its Contributions) on an "AS IS" BASIS,
//       WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
//       implied, including, without limitation, any warranties or conditions
//       of TITLE, NON-INFRINGEMENT, MERCHANTABILITY, or FITNESS FOR A
//       PARTICULAR PURPOSE. You are solely responsible for determining the
//       appropriateness of using or redistributing the Work and assume any
//       risks associated with Your exercise of permissions under this License.
//
//     8. Limitation of Liability. In no event and under no legal theory,
//       whether in tort (including negligence), contract, or otherwise,
//       unless required by applicable law (such as deliberate and grossly
//       negligent acts) or agreed to in writing, shall any Contributor be
//       liable to You for damages, including any direct, indirect, special,
//       incidental, or consequential damages of any character arising as a
//       result of this License or out of the use or inability to use the
//       Work (including but not limited to damages for loss of goodwill,
//       work stoppage, computer failure or malfunction, or any and all
//       other commercial damages or losses), even if such Contributor
//       has been advised of the possibility of such damages.
//
//     9. Accepting Warranty or Additional Liability. While redistributing
//       the Work or Derivative Works thereof, You may choose to offer,
//       and charge a fee for, acceptance of support, warranty, indemnity,
//       or other liability obligations and/or rights consistent with this
//       License. However, in accepting such obligations, You may act only
//       on Your own behalf and on Your sole responsibility, not on behalf
//       of any other Contributor, and only if You agree to indemnify,
//       defend, and hold each Contributor harmless for any liability
//       incurred by, or claims asserted against, such Contributor by reason
//       of your accepting any such warranty or additional liability.
//
//     END OF TERMS AND CONDITIONS
//
//     APPENDIX: How to apply the Apache License to your work.
//
//       To apply the Apache License to your work, attach the following
//       boilerplate notice, with the fields enclosed by brackets "[]"
//       replaced with your own identifying information. (Don't include
//       the brackets!)  The text should be enclosed in the appropriate
//       comment syntax for the file format. We also recommend that a
//       file or class name and description of purpose be included on the
//       same "printed page" as the copyright notice for easier
//       identification within third-party archives.
//
//     Copyright [yyyy] [name of copyright owner]
//
//     Licensed under the Apache License, Version 2.0 (the "License");
//     you may not use this file except in compliance with the License.
//     You may obtain a copy of the License at
//
//        http://www.apache.org/licenses/LICENSE-2.0
//
//     Unless required by applicable law or agreed to in writing, software
//     distributed under the License is distributed on an "AS IS" BASIS,
//     WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//     See the License for the specific language governing permissions and
//     limitations under the License.
//
//
// ---- LLVM Exceptions to the Apache 2.0 License ----
//
// As an exception, if, as a result of your compiling your source code, portions
// of this Software are embedded into an Object form of such source code, you
// may redistribute such embedded portions in such Object form without complying
// with the conditions of Sections 4(a), 4(b) and 4(d) of the License.
//
// In addition, if you combine or link compiled forms of this Software with
// software that is licensed under the GPLv2 ("Combined Software") and if a
// court of competent jurisdiction determines that the patent provision (Section
// 3), the indemnity provision (Section 9) or other Section of the License
// conflicts with the conditions of the GPLv2, you may retroactively and
// prospectively choose to deem waived or otherwise exclude such Section(s) of
// the License, but only in their entirety and only with respect to the Combined
// Software.
//
// ==============================================================================
// Software from third parties included in the LLVM Project:
// ==============================================================================
// The LLVM Project contains third party software which is under different license
// terms. All such code will be identified clearly using at least one of two
// mechanisms:
// 1) It will be in a separate directory tree with its own `LICENSE.txt` or
//    `LICENSE` file at the top containing the specific license and restrictions
//    which apply to that software, or
// 2) It will contain specific license and restriction terms at the top of every
//    file.
//
// ==============================================================================
// Legacy LLVM License (https://llvm.org/docs/DeveloperPolicy.html#legacy):
// ==============================================================================
//
// The compiler_rt library is dual licensed under both the University of Illinois
// "BSD-Like" license and the MIT license.  As a user of this code you may choose
// to use it under either license.  As a contributor, you agree to allow your code
// to be used under both.
//
// Full text of the relevant licenses is included below.
//
// ==============================================================================
//
// University of Illinois/NCSA
// Open Source License
//
// Copyright (c) 2009-2019 by the contributors listed in CREDITS.TXT
//
// All rights reserved.
//
// Developed by:
//
//     LLVM Team
//
//     University of Illinois at Urbana-Champaign
//
//     http://llvm.org
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal with
// the Software without restriction, including without limitation the rights to
// use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
// of the Software, and to permit persons to whom the Software is furnished to do
// so, subject to the following conditions:
//
//     * Redistributions of source code must retain the above copyright notice,
//       this list of conditions and the following disclaimers.
//
//     * Redistributions in binary form must reproduce the above copyright notice,
//       this list of conditions and the following disclaimers in the
//       documentation and/or other materials provided with the distribution.
//
//     * Neither the names of the LLVM Team, University of Illinois at
//       Urbana-Champaign, nor the names of its contributors may be used to
//       endorse or promote products derived from this Software without specific
//       prior written permission.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
// FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
// CONTRIBUTORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS WITH THE
// SOFTWARE.
//
// ==============================================================================
//
// Copyright (c) 2009-2015 by the contributors listed in CREDITS.TXT
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// ---- Start of embedded CREDITS.TXT, as referred to above ----
//
// This file is a partial list of people who have contributed to the LLVM/CompilerRT
// project.  If you have contributed a patch or made some other contribution to
// LLVM/CompilerRT, please submit a patch to this file to add yourself, and it will be
// done!
//
// The list is sorted by surname and formatted to allow easy grepping and
// beautification by scripts.  The fields are: name (N), email (E), web-address
// (W), PGP key ID and fingerprint (P), description (D), and snail-mail address
// (S).
//
// N: Craig van Vliet
// E: cvanvliet@auroraux.org
// W: http://www.auroraux.org
// D: Code style and Readability fixes.
//
// N: Edward O'Callaghan
// E: eocallaghan@auroraux.org
// W: http://www.auroraux.org
// D: CMake'ify Compiler-RT build system
// D: Maintain Solaris & AuroraUX ports of Compiler-RT
//
// N: Howard Hinnant
// E: hhinnant@apple.com
// D: Architect and primary author of compiler-rt
//
// N: Guan-Hong Liu
// E: koviankevin@hotmail.com
// D: IEEE Quad-precision functions
//
// N: Joerg Sonnenberger
// E: joerg@NetBSD.org
// D: Maintains NetBSD port.
//
// N: Matt Thomas
// E: matt@NetBSD.org
// D: ARM improvements.
//
// N: Mintsuki
// E: mintsuki@protonmail.com
// D: freestanding-lgrt: the selection of builtins, their packing into a single
// D: C file (pack.sh), the functions of C23's stdbit.h (stdc_*.c), and the
// D: modifications noted in the source files.
//
// ---- End of embedded CREDITS.TXT ----

// Only GCC and Clang, building ELF objects for x86 (including 16-bit code),
// AArch64, ARM, RISC-V or LoongArch, are supported.
#if !defined(__clang__) &&                                                     \
    (!defined(__GNUC__) || defined(__INTEL_COMPILER) ||                        \
     defined(__NVCOMPILER) || defined(__PGI) || defined(_CRAYC) ||             \
     defined(__TINYC__) || defined(__PCC__) || defined(__LCC__) ||             \
     defined(__COMPCERT__) || defined(__CC_ARM) ||                             \
     defined(__TI_COMPILER_VERSION__))
#error "freestanding-lgrt: unsupported compiler, use GCC or Clang"
#endif
// Workaround: Clang up to 16, bare-metal x86, AArch64 and LoongArch: it does
// not always define __ELF__, so only targets known not to be ELF are ruled out.
#if !defined(__ELF__) &&                                                       \
    (!defined(__clang__) || __clang_major__ >= 17 || defined(_WIN32) ||        \
     defined(__CYGWIN__) || defined(__APPLE__) || defined(__MACH__))
#error "freestanding-lgrt: unsupported object format, only ELF is supported"
#endif
#if !defined(__x86_64__) && !defined(__i386__) && !defined(__ia16__) &&        \
    !defined(__aarch64__) && !defined(__arm__) && !defined(__riscv) &&         \
    !defined(__loongarch__)
#error "freestanding-lgrt: unsupported architecture"
#endif

#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#pragma GCC diagnostic ignored "-Wunused-function"

#define FREESTANDING_LGRT_ASM_STR(...) #__VA_ARGS__
#define FREESTANDING_LGRT_ASM(...) FREESTANDING_LGRT_ASM_STR(__VA_ARGS__)

//===-- int_endianness.h - configuration header for compiler-rt -----------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
// 2024/01/21 - Modified by Mintsuki for use inside freestanding-lgrt
//
//===----------------------------------------------------------------------===//
//
// This file is a configuration header for compiler-rt.
// This file is not part of the interface of this library.
//
//===----------------------------------------------------------------------===//

#ifndef INT_ENDIANNESS_H
#define INT_ENDIANNESS_H

// Clang and GCC provide built-in endianness definitions.
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define _YUGA_LITTLE_ENDIAN 0
#define _YUGA_BIG_ENDIAN 1
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define _YUGA_LITTLE_ENDIAN 1
#define _YUGA_BIG_ENDIAN 0
#endif // __BYTE_ORDER__

#endif // INT_ENDIANNESS_H
#ifndef COMPILERRT_ASSEMBLY_H
#define COMPILERRT_ASSEMBLY_H
#define SEPARATOR ;
#define HIDDEN(name) .hidden name
#define LOCAL_LABEL(name) .L_##name
#define FILE_LEVEL_DIRECTIVE
#if defined(__arm__) || defined(__aarch64__)
#define SYMBOL_IS_FUNC(name) .type name,%function
#else
#define SYMBOL_IS_FUNC(name) .type name,@function
#endif
#define CONST_SECTION .section .rodata
#define NO_EXEC_STACK_DIRECTIVE .section .note.GNU-stack,"",%progbits
#if defined(__aarch64__) && defined(COMPILER_RT_EXECUTE_ONLY_CODE)
#define TEXT_SECTION                                                             .section .text,"axy",@progbits,unique,0
#else
#define TEXT_SECTION                                                             .text
#endif
#if defined(__arm__) || defined(__aarch64__)
#define FUNC_ALIGN                                                               .balign 16 SEPARATOR
#else
#define FUNC_ALIGN
#endif
#define NT_GNU_PROPERTY_TYPE_0 5
#define GNU_PROPERTY_AARCH64_FEATURE_1_AND 0xc0000000
#define GNU_PROPERTY_AARCH64_FEATURE_1_BTI 1
#define GNU_PROPERTY_AARCH64_FEATURE_1_PAC 2
#define GNU_PROPERTY_AARCH64_FEATURE_1_GCS 4
#if defined(__ARM_FEATURE_BTI_DEFAULT)
#define BTI_FLAG GNU_PROPERTY_AARCH64_FEATURE_1_BTI
#else
#define BTI_FLAG 0
#endif
#if defined(__ARM_FEATURE_PAC_DEFAULT) && (__ARM_FEATURE_PAC_DEFAULT & 3)
#define PAC_FLAG GNU_PROPERTY_AARCH64_FEATURE_1_PAC
#else
#define PAC_FLAG 0
#endif
#if defined(__ARM_FEATURE_GCS_DEFAULT)
#define GCS_FLAG GNU_PROPERTY_AARCH64_FEATURE_1_GCS
#else
#define GCS_FLAG 0
#endif
#define GNU_PROPERTY(type, value)                                                .pushsection .note.gnu.property, "a" SEPARATOR                                 .p2align 3 SEPARATOR                                                           .word 4 SEPARATOR                                                              .word 16 SEPARATOR                                                             .word NT_GNU_PROPERTY_TYPE_0 SEPARATOR                                         .asciz "GNU" SEPARATOR                                                         .word type SEPARATOR                                                           .word 4 SEPARATOR                                                              .word value SEPARATOR                                                          .word 0 SEPARATOR                                                              .popsection
#if BTI_FLAG != 0
#define BTI_C hint #34
#define BTI_J hint #36
#else
#define BTI_C
#define BTI_J
#endif
#if (BTI_FLAG | PAC_FLAG | GCS_FLAG) != 0
#define GNU_PROPERTY_BTI_PAC_GCS                                                 GNU_PROPERTY(GNU_PROPERTY_AARCH64_FEATURE_1_AND,                                            BTI_FLAG | PAC_FLAG | GCS_FLAG)
#else
#define GNU_PROPERTY_BTI_PAC_GCS
#endif
#if defined(__clang__) || defined(__GCC_HAVE_DWARF2_CFI_ASM)
#define CFI_START .cfi_startproc
#define CFI_END .cfi_endproc
#else
#define CFI_START
#define CFI_END
#endif
#if defined(__arm__)
#if defined(__thumb2__) || defined(__thumb__)
#define DEFINE_CODE_STATE .thumb SEPARATOR
#define DECLARE_FUNC_ENCODING    .thumb_func SEPARATOR
#if defined(__thumb2__)
#define USE_THUMB_2
#define IT(cond)  it cond
#define ITT(cond) itt cond
#define ITE(cond) ite cond
#else
#define USE_THUMB_1
#define IT(cond)
#define ITT(cond)
#define ITE(cond)
#endif 
#else 
#define DEFINE_CODE_STATE .arm SEPARATOR
#define DECLARE_FUNC_ENCODING
#define IT(cond)
#define ITT(cond)
#define ITE(cond)
#endif
#if defined(USE_THUMB_1) && defined(USE_THUMB_2)
#error "USE_THUMB_1 and USE_THUMB_2 can't be defined together."
#endif
#if defined(__ARM_ARCH_4T__) || __ARM_ARCH >= 5
#define ARM_HAS_BX
#endif
#if !defined(__ARM_FEATURE_CLZ) && !defined(USE_THUMB_1) &&      (__ARM_ARCH >= 6 || (__ARM_ARCH == 5 && !defined(__ARM_ARCH_5__)))
#define __ARM_FEATURE_CLZ
#endif
#ifdef ARM_HAS_BX
#define JMP(r) bx r
#define JMPc(r, c) bx##c r
#else
#define JMP(r) mov pc, r
#define JMPc(r, c) mov##c pc, r
#endif
#if 1
#if __ARM_ARCH >= 5
__asm__(
    ".macro POP_PC\n"
    "  pop {pc}\n"
    ".endm\n"
    ".macro POP_PC_WITH_REGS regs:vararg\n"
    "  pop {\\regs, pc}\n"
    ".endm\n"
);
#else
__asm__(
    ".macro POP_PC\n"
    "  pop {ip}\n"
    "  " FREESTANDING_LGRT_ASM(JMP(ip)) "\n"
    ".endm\n"
    ".macro POP_PC_WITH_REGS regs:vararg\n"
    "  pop {\\regs, ip}\n"
    "  " FREESTANDING_LGRT_ASM(JMP(ip)) "\n"
    ".endm\n"
);
#endif
#endif
#if defined(USE_THUMB_2)
#define WIDE(op) op.w
#else
#define WIDE(op) op
#endif
#if defined(__ARM_FEATURE_PAC_DEFAULT) && defined(__ARM_FEATURE_BTI_DEFAULT)
#define PACBTI_LANDING pacbti r12, lr, sp
#elif defined(__ARM_FEATURE_PAC_DEFAULT)
#define PACBTI_LANDING pac r12, lr, sp
#elif defined(__ARM_FEATURE_BTI_DEFAULT)
#define PACBTI_LANDING bti
#else
#define PACBTI_LANDING
#endif
#if defined(__ARM_FEATURE_PAUTH)
#define PAC_RETURN bxaut r12, lr, sp
#else
#define PAC_RETURN aut r12, lr, sp SEPARATOR bx lr
#endif
#else 
#define DECLARE_FUNC_ENCODING
#define DEFINE_CODE_STATE
#endif
#define GLUE2_(a, b) a##b
#define GLUE(a, b) GLUE2_(a, b)
#define GLUE2(a, b) GLUE2_(a, b)
#define GLUE3_(a, b, c) a##b##c
#define GLUE3(a, b, c) GLUE3_(a, b, c)
#define GLUE4_(a, b, c, d) a##b##c##d
#define GLUE4(a, b, c, d) GLUE4_(a, b, c, d)
#ifndef SYMBOL_NAME
#define SYMBOL_NAME(name) GLUE(__USER_LABEL_PREFIX__, name)
#endif
#define FUNC_SYMBOL(name) name
#ifdef VISIBILITY_HIDDEN
#define DECLARE_SYMBOL_VISIBILITY(name)                                          HIDDEN(SYMBOL_NAME(name)) SEPARATOR
#define DECLARE_SYMBOL_VISIBILITY_UNMANGLED(name)   HIDDEN(name) SEPARATOR
#else
#define DECLARE_SYMBOL_VISIBILITY(name)
#define DECLARE_SYMBOL_VISIBILITY_UNMANGLED(name)
#endif
#define DEFINE_COMPILERRT_FUNCTION(name)                                         TEXT_SECTION SEPARATOR                                                         DEFINE_CODE_STATE                                                              FILE_LEVEL_DIRECTIVE SEPARATOR                                                 .globl FUNC_SYMBOL(SYMBOL_NAME(name)) SEPARATOR                                SYMBOL_IS_FUNC(SYMBOL_NAME(name)) SEPARATOR                                    DECLARE_SYMBOL_VISIBILITY(name)                                                DECLARE_FUNC_ENCODING                                                          FUNC_SYMBOL(SYMBOL_NAME(name)):
#define DEFINE_COMPILERRT_THUMB_FUNCTION(name)                                   TEXT_SECTION SEPARATOR                                                         DEFINE_CODE_STATE                                                              FILE_LEVEL_DIRECTIVE SEPARATOR                                                 .globl FUNC_SYMBOL(SYMBOL_NAME(name)) SEPARATOR                                SYMBOL_IS_FUNC(SYMBOL_NAME(name)) SEPARATOR                                    DECLARE_SYMBOL_VISIBILITY(name) SEPARATOR                                      .thumb_func SEPARATOR                                                          FUNC_SYMBOL(SYMBOL_NAME(name)):
#define DEFINE_COMPILERRT_PRIVATE_FUNCTION(name)                                 TEXT_SECTION SEPARATOR                                                         DEFINE_CODE_STATE                                                              FILE_LEVEL_DIRECTIVE SEPARATOR                                                 .globl FUNC_SYMBOL(SYMBOL_NAME(name)) SEPARATOR                                SYMBOL_IS_FUNC(SYMBOL_NAME(name)) SEPARATOR                                    HIDDEN(SYMBOL_NAME(name)) SEPARATOR                                            DECLARE_FUNC_ENCODING                                                          FUNC_SYMBOL(SYMBOL_NAME(name)):
#define DEFINE_COMPILERRT_PRIVATE_FUNCTION_UNMANGLED(name)                       TEXT_SECTION SEPARATOR                                                         DEFINE_CODE_STATE                                                              .globl FUNC_SYMBOL(name) SEPARATOR                                             SYMBOL_IS_FUNC(name) SEPARATOR                                                 HIDDEN(name) SEPARATOR                                                         DECLARE_FUNC_ENCODING                                                          FUNC_SYMBOL(name):
#define DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(name)                       TEXT_SECTION SEPARATOR                                                         DEFINE_CODE_STATE                                                              FUNC_ALIGN                                                                     .globl FUNC_SYMBOL(name) SEPARATOR                                             SYMBOL_IS_FUNC(name) SEPARATOR                                                 DECLARE_SYMBOL_VISIBILITY_UNMANGLED(FUNC_SYMBOL(name)) SEPARATOR               DECLARE_FUNC_ENCODING                                                          FUNC_SYMBOL(name):                                                             SEPARATOR CFI_START                                                            SEPARATOR BTI_C
#define DEFINE_COMPILERRT_FUNCTION_ALIAS(name, target)                           .globl FUNC_SYMBOL(SYMBOL_NAME(name)) SEPARATOR                                SYMBOL_IS_FUNC(SYMBOL_NAME(name)) SEPARATOR                                    DECLARE_SYMBOL_VISIBILITY(name) SEPARATOR                                      .set FUNC_SYMBOL(SYMBOL_NAME(name)), FUNC_SYMBOL(SYMBOL_NAME(target)) SEPARATOR
#if defined(__ARM_EABI__)
#define DEFINE_AEABI_FUNCTION_ALIAS(aeabi_name, name)                            DEFINE_COMPILERRT_FUNCTION_ALIAS(aeabi_name, name)
#else
#define DEFINE_AEABI_FUNCTION_ALIAS(aeabi_name, name)
#endif
#define END_COMPILERRT_FUNCTION(name)                                            .size SYMBOL_NAME(name), . - SYMBOL_NAME(name)
#define END_COMPILERRT_OUTLINE_FUNCTION(name)                                    CFI_END SEPARATOR                                                              .size SYMBOL_NAME(name), . - SYMBOL_NAME(name)
#ifdef __arm__
#if _YUGA_BIG_ENDIAN
#define VMOV_TO_DOUBLE(dst, src0, src1) vmov dst, src1, src0 SEPARATOR
#define VMOV_FROM_DOUBLE(dst0, dst1, src) vmov dst1, dst0, src SEPARATOR
#else
#define VMOV_TO_DOUBLE(dst, src0, src1) vmov dst, src0, src1 SEPARATOR
#define VMOV_FROM_DOUBLE(dst0, dst1, src) vmov dst0, dst1, src SEPARATOR
#endif
#endif
#endif 
//===-- int_lib.h - configuration header for compiler-rt  -----------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
// 2024/01/21 - Modified by Mintsuki for use inside freestanding-lgrt
//
//===----------------------------------------------------------------------===//
//
// This file is not part of the interface of this library.
//
// This file defines various standard types, most importantly a number of unions
// used to access parts of larger types.
//
//===----------------------------------------------------------------------===//

#ifndef INT_TYPES_H
#define INT_TYPES_H


// si_int is defined in Linux sysroot's asm-generic/siginfo.h
#ifdef si_int
#undef si_int
#endif
typedef int32_t si_int;
typedef uint32_t su_int;
#if UINT_MAX == 0xFFFFFFFF
#define clzsi __builtin_clz
#define ctzsi __builtin_ctz
#elif ULONG_MAX == 0xFFFFFFFF
#define clzsi __builtin_clzl
#define ctzsi __builtin_ctzl
#else
#error could not determine appropriate clzsi macro for this system
#endif

typedef int64_t di_int;
typedef uint64_t du_int;

typedef union {
  di_int all;
  struct {
#if _YUGA_LITTLE_ENDIAN
    su_int low;
    si_int high;
#else
    si_int high;
    su_int low;
#endif // _YUGA_LITTLE_ENDIAN
  } s;
} dwords;

typedef union {
  du_int all;
  struct {
#if _YUGA_LITTLE_ENDIAN
    su_int low;
    su_int high;
#else
    su_int high;
    su_int low;
#endif // _YUGA_LITTLE_ENDIAN
  } s;
} udwords;

#if defined(__LP64__) || defined(__SIZEOF_INT128__)
#define CRT_HAS_128BIT
#endif

#ifdef CRT_HAS_128BIT
typedef int ti_int __attribute__((mode(TI)));
typedef unsigned tu_int __attribute__((mode(TI)));

typedef union {
  ti_int all;
  struct {
#if _YUGA_LITTLE_ENDIAN
    du_int low;
    di_int high;
#else
    di_int high;
    du_int low;
#endif // _YUGA_LITTLE_ENDIAN
  } s;
} twords;

typedef union {
  tu_int all;
  struct {
#if _YUGA_LITTLE_ENDIAN
    du_int low;
    du_int high;
#else
    du_int high;
    du_int low;
#endif // _YUGA_LITTLE_ENDIAN
  } s;
} utwords;

#endif // CRT_HAS_128BIT

#endif // INT_TYPES_H
//===-- int_lib.h - configuration header for compiler-rt  -----------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
// 2024/01/21 - Modified by Mintsuki for use inside freestanding-lgrt
//
//===----------------------------------------------------------------------===//
//
// This file is a configuration header for compiler-rt.
// This file is not part of the interface of this library.
//
//===----------------------------------------------------------------------===//

#ifndef INT_LIB_H
#define INT_LIB_H

// Assumption: Signed integral is 2's complement.
// Assumption: Right shift of signed negative is arithmetic shift.
// Assumption: Endianness is little or big (not mixed).

// ABI macro definitions

#ifdef __ARM_EABI__
#ifdef COMPILER_RT_ARMHF_TARGET
#define COMPILER_RT_ABI
#else
#define COMPILER_RT_ABI __attribute__((__pcs__("aapcs")))
#endif
#else
#define COMPILER_RT_ABI
#endif

#define AEABI_RTABI __attribute__((__pcs__("aapcs")))

#define ALWAYS_INLINE __attribute__((always_inline))
#define NOINLINE __attribute__((noinline))
#define NORETURN __attribute__((noreturn))
#define UNUSED __attribute__((unused))

#ifndef SYMBOL_NAME
#define STR(a) #a
#define XSTR(a) STR(a)
#define SYMBOL_NAME(name) XSTR(__USER_LABEL_PREFIX__) #name
#endif

#define COMPILER_RT_ALIAS(name, aliasname) \
  COMPILER_RT_ABI __typeof(name) aliasname __attribute__((__alias__(#name)));

// Include the standard compiler builtin headers we use functionality from.

// Include the commonly used internal type definitions.

// Include internal utility function declarations.

COMPILER_RT_ABI int __paritysi2(si_int a);
COMPILER_RT_ABI int __paritydi2(di_int a);

COMPILER_RT_ABI di_int __divdi3(di_int a, di_int b);
COMPILER_RT_ABI si_int __divsi3(si_int a, si_int b);
COMPILER_RT_ABI su_int __udivsi3(su_int n, su_int d);

COMPILER_RT_ABI su_int __udivmodsi4(su_int a, su_int b, su_int *rem);
COMPILER_RT_ABI du_int __udivmoddi4(du_int a, du_int b, du_int *rem);
#ifdef CRT_HAS_128BIT
COMPILER_RT_ABI int __clzti2(ti_int a);
COMPILER_RT_ABI tu_int __udivmodti4(tu_int a, tu_int b, tu_int *rem);
#endif

#endif // INT_LIB_H
//===-- int_util.h - internal utility functions ---------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file is not part of the interface of this library.
//
// This file defines non-inline utilities which are available for use in the
// library. The function definitions themselves are all contained in int_util.c
// which will always be compiled into any compiler-rt library.
//
//===----------------------------------------------------------------------===//

#ifndef INT_UTIL_H
#define INT_UTIL_H

/// \brief Trigger a program abort (or panic for kernel code).
#define compilerrt_abort() __compilerrt_abort_impl(__FILE__, __LINE__, __func__)

NORETURN void __compilerrt_abort_impl(const char *file, int line,
                                      const char *function);

#define COMPILE_TIME_ASSERT(expr) COMPILE_TIME_ASSERT1(expr, __COUNTER__)
#define COMPILE_TIME_ASSERT1(expr, cnt) COMPILE_TIME_ASSERT2(expr, cnt)
#define COMPILE_TIME_ASSERT2(expr, cnt)                                        \
  typedef char ct_assert_##cnt[(expr) ? 1 : -1] UNUSED

// Force unrolling the code specified to be repeated N times.
#define REPEAT_0_TIMES(code_to_repeat) /* do nothing */
#define REPEAT_1_TIMES(code_to_repeat) code_to_repeat
#define REPEAT_2_TIMES(code_to_repeat)                                         \
  REPEAT_1_TIMES(code_to_repeat)                                               \
  code_to_repeat
#define REPEAT_3_TIMES(code_to_repeat)                                         \
  REPEAT_2_TIMES(code_to_repeat)                                               \
  code_to_repeat
#define REPEAT_4_TIMES(code_to_repeat)                                         \
  REPEAT_3_TIMES(code_to_repeat)                                               \
  code_to_repeat

#define REPEAT_N_TIMES_(N, code_to_repeat) REPEAT_##N##_TIMES(code_to_repeat)
#define REPEAT_N_TIMES(N, code_to_repeat) REPEAT_N_TIMES_(N, code_to_repeat)

#endif // INT_UTIL_H
//===-- absvdi2.c - Implement __absvdi2 -----------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements __absvdi2 for the compiler_rt library.
//
//===----------------------------------------------------------------------===//


// Returns: absolute value

// Effects: aborts if abs(x) < 0

COMPILER_RT_ABI di_int __absvdi2(di_int a) {
  const int N = (int)(sizeof(di_int) * CHAR_BIT);
  if (a == ((di_int)((du_int)1 << (N - 1))))
    compilerrt_abort();
  const di_int t = a >> (N - 1);
  return (a ^ t) - t;
}
//===-- absvsi2.c - Implement __absvsi2 -----------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements __absvsi2 for the compiler_rt library.
//
//===----------------------------------------------------------------------===//


// Returns: absolute value

// Effects: aborts if abs(x) < 0

COMPILER_RT_ABI si_int __absvsi2(si_int a) {
  const int N = (int)(sizeof(si_int) * CHAR_BIT);
  if (a == ((si_int)((su_int)1 << (N - 1))))
    compilerrt_abort();
  const si_int t = a >> (N - 1);
  return (a ^ t) - t;
}
//===-- absvti2.c - Implement __absvdi2 -----------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements __absvti2 for the compiler_rt library.
//
//===----------------------------------------------------------------------===//


#ifdef CRT_HAS_128BIT

// Returns: absolute value

// Effects: aborts if abs(x) < 0

COMPILER_RT_ABI ti_int __absvti2(ti_int a) {
  const int N = (int)(sizeof(ti_int) * CHAR_BIT);
  if (a == (ti_int)((tu_int)1 << (N - 1)))
    compilerrt_abort();
  const ti_int s = a >> (N - 1);
  return (a ^ s) - s;
}

#endif // CRT_HAS_128BIT
//===-- addvdi3.c - Implement __addvdi3 -----------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements __addvdi3 for the compiler_rt library.
//
//===----------------------------------------------------------------------===//


// Returns: a + b

// Effects: aborts if a + b overflows

COMPILER_RT_ABI di_int __addvdi3(di_int a, di_int b) {
  di_int s = (du_int)a + (du_int)b;
  if (b >= 0) {
    if (s < a)
      compilerrt_abort();
  } else {
    if (s >= a)
      compilerrt_abort();
  }
  return s;
}
//===-- addvsi3.c - Implement __addvsi3 -----------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements __addvsi3 for the compiler_rt library.
//
//===----------------------------------------------------------------------===//


// Returns: a + b

// Effects: aborts if a + b overflows

COMPILER_RT_ABI si_int __addvsi3(si_int a, si_int b) {
  si_int s = (su_int)a + (su_int)b;
  if (b >= 0) {
    if (s < a)
      compilerrt_abort();
  } else {
    if (s >= a)
      compilerrt_abort();
  }
  return s;
}
//===-- addvti3.c - Implement __addvti3 -----------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements __addvti3 for the compiler_rt library.
//
//===----------------------------------------------------------------------===//


#ifdef CRT_HAS_128BIT

// Returns: a + b

// Effects: aborts if a + b overflows

COMPILER_RT_ABI ti_int __addvti3(ti_int a, ti_int b) {
  ti_int s = (tu_int)a + (tu_int)b;
  if (b >= 0) {
    if (s < a)
      compilerrt_abort();
  } else {
    if (s >= a)
      compilerrt_abort();
  }
  return s;
}

#endif // CRT_HAS_128BIT
#if defined(__arm__)
//===-- aeabi_div0.c - ARM Runtime ABI support routines for compiler-rt ---===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements the division by zero helper routines as specified by the
// Run-time ABI for the ARM Architecture.
//
//===----------------------------------------------------------------------===//

// RTABI 4.3.2 - Division by zero
//
// The *div0 functions:
// - Return the value passed to them as a parameter
// - Or, return a fixed value defined by the execution environment (such as 0)
// - Or, raise a signal (often SIGFPE) or throw an exception, and do not return
//
// An application may provide its own implementations of the *div0 functions to
// for a particular behaviour from the *div and *divmod functions called out of
// line.


// provide an unused declaration to pacify pendantic compilation
extern unsigned char declaration;

#if defined(__ARM_EABI__)
AEABI_RTABI int __attribute__((weak)) __attribute__((visibility("hidden")))
__aeabi_idiv0(int return_value) {
  return return_value;
}

AEABI_RTABI long long __attribute__((weak))
__attribute__((visibility("hidden"))) __aeabi_ldiv0(long long return_value) {
  return return_value;
}
#endif
#endif
// ====-- ashldi3.c - Implement __ashldi3 ---------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements __ashldi3 for the compiler_rt library.
//
//===----------------------------------------------------------------------===//


// Returns: a << b

// Precondition:  0 <= b < bits_in_dword

COMPILER_RT_ABI di_int __ashldi3(di_int a, int b) {
  const int bits_in_word = (int)(sizeof(si_int) * CHAR_BIT);
  dwords input;
  dwords result;
  input.all = a;
  if (b & bits_in_word) /* bits_in_word <= b < bits_in_dword */ {
    result.s.low = 0;
    result.s.high = input.s.low << (b - bits_in_word);
  } else /* 0 <= b < bits_in_word */ {
    if (b == 0)
      return a;
    result.s.low = input.s.low << b;
    result.s.high =
        ((su_int)input.s.high << b) | (input.s.low >> (bits_in_word - b));
  }
  return result.all;
}

#if defined(__ARM_EABI__)
COMPILER_RT_ALIAS(__ashldi3, __aeabi_llsl)
#endif
//===-- ashlti3.c - Implement __ashlti3 -----------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements __ashlti3 for the compiler_rt library.
//
//===----------------------------------------------------------------------===//


#ifdef CRT_HAS_128BIT

// Returns: a << b

// Precondition:  0 <= b < bits_in_tword

COMPILER_RT_ABI ti_int __ashlti3(ti_int a, int b) {
  const int bits_in_dword = (int)(sizeof(di_int) * CHAR_BIT);
  twords input;
  twords result;
  input.all = a;
  if (b & bits_in_dword) /* bits_in_dword <= b < bits_in_tword */ {
    result.s.low = 0;
    result.s.high = input.s.low << (b - bits_in_dword);
  } else /* 0 <= b < bits_in_dword */ {
    if (b == 0)
      return a;
    result.s.low = input.s.low << b;
    result.s.high =
        ((du_int)input.s.high << b) | (input.s.low >> (bits_in_dword - b));
  }
  return result.all;
}

#endif // CRT_HAS_128BIT
//===-- ashrdi3.c - Implement __ashrdi3 -----------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements __ashrdi3 for the compiler_rt library.
//
//===----------------------------------------------------------------------===//


// Returns: arithmetic a >> b

// Precondition:  0 <= b < bits_in_dword

COMPILER_RT_ABI di_int __ashrdi3(di_int a, int b) {
  const int bits_in_word = (int)(sizeof(si_int) * CHAR_BIT);
  dwords input;
  dwords result;
  input.all = a;
  if (b & bits_in_word) /* bits_in_word <= b < bits_in_dword */ {
    // result.s.high = input.s.high < 0 ? -1 : 0
    result.s.high = input.s.high >> (bits_in_word - 1);
    result.s.low = input.s.high >> (b - bits_in_word);
  } else /* 0 <= b < bits_in_word */ {
    if (b == 0)
      return a;
    result.s.high = input.s.high >> b;
    result.s.low =
        ((su_int)input.s.high << (bits_in_word - b)) | (input.s.low >> b);
  }
  return result.all;
}

#if defined(__ARM_EABI__)
COMPILER_RT_ALIAS(__ashrdi3, __aeabi_lasr)
#endif
//===-- ashrti3.c - Implement __ashrti3 -----------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements __ashrti3 for the compiler_rt library.
//
//===----------------------------------------------------------------------===//


#ifdef CRT_HAS_128BIT

// Returns: arithmetic a >> b

// Precondition:  0 <= b < bits_in_tword

COMPILER_RT_ABI ti_int __ashrti3(ti_int a, int b) {
  const int bits_in_dword = (int)(sizeof(di_int) * CHAR_BIT);
  twords input;
  twords result;
  input.all = a;
  if (b & bits_in_dword) /* bits_in_dword <= b < bits_in_tword */ {
    // result.s.high = input.s.high < 0 ? -1 : 0
    result.s.high = input.s.high >> (bits_in_dword - 1);
    result.s.low = input.s.high >> (b - bits_in_dword);
  } else /* 0 <= b < bits_in_dword */ {
    if (b == 0)
      return a;
    result.s.high = input.s.high >> b;
    result.s.low =
        ((du_int)input.s.high << (bits_in_dword - b)) | (input.s.low >> b);
  }
  return result.all;
}

#endif // CRT_HAS_128BIT
//===-- atomic.c - Implement support functions for atomic operations.------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
// 2026/10/17 - Modified by Mintsuki for use inside freestanding-lgrt
//
//===----------------------------------------------------------------------===//
//
//  atomic.c defines a set of functions for performing atomic accesses on
//  arbitrary-sized memory locations.  This design uses locks that should
//  be fast in the uncontended case, for two reasons:
//
//  1) This code must work with C programs that do not link to anything
//     (including pthreads) and so it should not depend on any pthread
//     functions. If the user wishes to opt into using pthreads, they may do so.
//  2) Atomic operations, rather than explicit mutexes, are most commonly used
//     on code where contended operations are rate.
//
//  To avoid needing a per-object lock, this code allocates an array of
//  locks and hashes the object pointers to find the one that it should use.
//  For operations that must be atomic on two locations, the lower lock is
//  always acquired first, to avoid deadlock.
//
//===----------------------------------------------------------------------===//



// Built where the compiler can do pointer-sized atomics inline, with
// instructions the CPU has, which ARM has from v6 on, except in Thumb1 code
// before ARMv8-M Baseline. GCC is not supported on 32-bit LoongArch.
//
// Workaround: GCC up to 4.9, all targets: __atomic_always_lock_free is not a
// constant expression, and up to 4.8, _Atomic is missing.
//
// Workaround: Clang up to at least 23, 80386: it reports atomics as lock-free,
// and uses cmpxchg and xadd for them, which the 80486 added.
//
// Workaround: Clang up to at least 23, ARM before v6K: it reports byte,
// halfword and doubleword atomics as lock-free, and uses the exclusives for
// them that v6K added.
//
// Workaround: GCC up to at least 13, ARM Linux targets before v6K: it turns
// byte and halfword atomics into __sync_* calls.
//
// Workaround: Clang 16 to 20, 32-bit LoongArch: it cannot compile some atomic
// operations.
#if (defined(__clang__) || defined(__GNUC__)) &&                               \
    !(!defined(__clang__) && __GNUC__ < 5) &&                                  \
    __GCC_ATOMIC_POINTER_LOCK_FREE == 2 &&                                     \
    !(defined(__i386__) && !defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_4)) &&    \
    !(defined(__arm__) &&                                                      \
      (__ARM_ARCH < 6 ||                                                       \
       (defined(__thumb__) && !defined(__thumb2__) && __ARM_ARCH < 8))) &&     \
    !(defined(__arm__) && defined(__clang__) &&                                \
      defined(__ARM_FEATURE_LDREX) && !(__ARM_FEATURE_LDREX & 1)) &&           \
    !(defined(__arm__) && !defined(__clang__) && defined(__linux__) &&         \
      !defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_1)) &&                         \
    !(defined(__loongarch__) && __loongarch_grlen == 32 &&                     \
      (!defined(__clang__) || __clang_major__ < 21))

// _Atomic and _Static_assert are C11, which pedantic C99 builds would reject.
//
// Workaround: GCC 5 up to at least 16, all targets: its -Wpedantic says that
// the expression of the static assertion below is not an integer constant
// expression.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"

// We use __builtin_mem* here to avoid dependencies on libc-provided headers.
#define memcpy __builtin_memcpy
#define memcmp __builtin_memcmp

// Clang objects if you redefine a builtin.  This little hack allows us to
// define a function with the same name as an intrinsic.
#pragma redefine_extname __atomic_load_c SYMBOL_NAME(__atomic_load)
#pragma redefine_extname __atomic_store_c SYMBOL_NAME(__atomic_store)
#pragma redefine_extname __atomic_exchange_c SYMBOL_NAME(__atomic_exchange)
#pragma redefine_extname __atomic_compare_exchange_c SYMBOL_NAME(              \
    __atomic_compare_exchange)
#pragma redefine_extname __atomic_is_lock_free_c SYMBOL_NAME(                  \
    __atomic_is_lock_free)

#ifndef __clang__
// GCC has no __c11_atomic_* builtins, but equivalent __atomic_* ones, which
// accept pointers to _Atomic types too.
#define __c11_atomic_load __atomic_load_n
#define __c11_atomic_store __atomic_store_n
#define __c11_atomic_exchange __atomic_exchange_n
#define __c11_atomic_compare_exchange_strong(p, e, d, s, f)                    \
  __atomic_compare_exchange_n(p, e, d, false, s, f)
#define __c11_atomic_compare_exchange_weak(p, e, d, s, f)                      \
  __atomic_compare_exchange_n(p, e, d, true, s, f)
#define __c11_atomic_fetch_add __atomic_fetch_add
#define __c11_atomic_fetch_sub __atomic_fetch_sub
#define __c11_atomic_fetch_and __atomic_fetch_and
#define __c11_atomic_fetch_or __atomic_fetch_or
#define __c11_atomic_fetch_xor __atomic_fetch_xor
#define __c11_atomic_fetch_nand __atomic_fetch_nand

// Workaround: GCC 5 up to at least 16, all targets: it does not apply the
// pragmas above to definitions, and it treats names such as __atomic_load_4 as
// its own builtins, so all functions here get a _c suffix, and declarations
// that give them their real names as asm labels.
#define ATOMIC_STR_(x) #x
#define ATOMIC_STR(x) ATOMIC_STR_(x)
#define ATOMIC_DECL(ret, name, params)                                         \
  ret name##_c params __asm__(ATOMIC_STR(SYMBOL_NAME(name)))
ATOMIC_DECL(bool, __atomic_is_lock_free, (size_t, void *));
ATOMIC_DECL(void, __atomic_load, (size_t, void *, void *, int));
ATOMIC_DECL(void, __atomic_store, (size_t, void *, void *, int));
ATOMIC_DECL(int, __atomic_compare_exchange,
            (size_t, void *, void *, void *, int, int));
ATOMIC_DECL(void, __atomic_exchange, (size_t, void *, void *, void *, int));
#endif

/// Number of locks.  This allocates one page on 32-bit platforms, two on
/// 64-bit.  This can be specified externally if a different trade between
/// memory usage and contention probability is required for a given platform.
#ifndef SPINLOCK_COUNT
#define SPINLOCK_COUNT (1 << 10)
#endif
static const long SPINLOCK_MASK = SPINLOCK_COUNT - 1;

////////////////////////////////////////////////////////////////////////////////
// Platform-specific lock implementation.  Falls back to spinlocks if none is
// defined.  Each platform should define the Lock type, and corresponding
// lock() and unlock() functions.
////////////////////////////////////////////////////////////////////////////////
_Static_assert(__atomic_always_lock_free(sizeof(uintptr_t), 0),
               "Implementation assumes lock-free pointer-size cmpxchg");
typedef _Atomic(uintptr_t) Lock;
/// Unlock a lock.  This is a release operation.
__inline static void unlock(Lock *l) {
  __c11_atomic_store(l, 0, __ATOMIC_RELEASE);
}
/// Locks a lock.  In the current implementation, this is potentially
/// unbounded in the contended case.
__inline static void lock(Lock *l) {
  uintptr_t old = 0;
  while (!__c11_atomic_compare_exchange_weak(l, &old, 1, __ATOMIC_ACQUIRE,
                                             __ATOMIC_RELAXED))
    old = 0;
}
/// locks for atomic operations
static Lock locks[SPINLOCK_COUNT];

/// Returns a lock to use for a given pointer.
static __inline Lock *lock_for_pointer(void *ptr) {
  intptr_t hash = (intptr_t)ptr;
  // Disregard the lowest 4 bits.  We want all values that may be part of the
  // same memory operation to hash to the same value and therefore use the same
  // lock.
  hash >>= 4;
  // Use the next bits as the basis for the hash
  intptr_t low = hash & SPINLOCK_MASK;
  // Now use the high(er) set of bits to perturb the hash, so that we don't
  // get collisions from atomic fields in a single object
  hash >>= 16;
  hash ^= low;
  // Return a pointer to the word to use
  return locks + (hash & SPINLOCK_MASK);
}

/// Macros for determining whether a size is lock free.
#define ATOMIC_ALWAYS_LOCK_FREE_OR_ALIGNED_LOCK_FREE(size, p)                  \
  (__atomic_always_lock_free(size, p) ||                                       \
   (__atomic_always_lock_free(size, 0) && ((uintptr_t)p % size) == 0))
#define IS_LOCK_FREE_1(p) ATOMIC_ALWAYS_LOCK_FREE_OR_ALIGNED_LOCK_FREE(1, p)
#define IS_LOCK_FREE_2(p) ATOMIC_ALWAYS_LOCK_FREE_OR_ALIGNED_LOCK_FREE(2, p)
#define IS_LOCK_FREE_4(p) ATOMIC_ALWAYS_LOCK_FREE_OR_ALIGNED_LOCK_FREE(4, p)
#define IS_LOCK_FREE_8(p) ATOMIC_ALWAYS_LOCK_FREE_OR_ALIGNED_LOCK_FREE(8, p)
#define IS_LOCK_FREE_16(p) ATOMIC_ALWAYS_LOCK_FREE_OR_ALIGNED_LOCK_FREE(16, p)

/// Macro that calls the compiler-generated lock-free versions of functions
/// when they exist.
#define TRY_LOCK_FREE_CASE(n, type, ptr)                                       \
  case n:                                                                      \
    if (IS_LOCK_FREE_##n(ptr)) {                                               \
      LOCK_FREE_ACTION(type);                                                  \
    }                                                                          \
    break;
#ifdef __SIZEOF_INT128__
#define TRY_LOCK_FREE_CASE_16(p) TRY_LOCK_FREE_CASE(16, __uint128_t, p)
#else
#define TRY_LOCK_FREE_CASE_16(p) /* __uint128_t not available */
#endif

#define LOCK_FREE_CASES(ptr)                                                   \
  do {                                                                         \
    switch (size) {                                                            \
      TRY_LOCK_FREE_CASE(1, uint8_t, ptr)                                      \
      TRY_LOCK_FREE_CASE(2, uint16_t, ptr)                                     \
      TRY_LOCK_FREE_CASE(4, uint32_t, ptr)                                     \
      TRY_LOCK_FREE_CASE(8, uint64_t, ptr)                                     \
      TRY_LOCK_FREE_CASE_16(ptr) /* __uint128_t may not be supported */        \
    default:                                                                   \
      break;                                                                   \
    }                                                                          \
  } while (0)

/// Whether atomic operations for the given size (and alignment) are lock-free.
bool __atomic_is_lock_free_c(size_t size, void *ptr) {
#define LOCK_FREE_ACTION(type) return true;
  LOCK_FREE_CASES(ptr);
#undef LOCK_FREE_ACTION
  return false;
}

/// An atomic load operation.  This is atomic with respect to the source
/// pointer only.
void __atomic_load_c(size_t size, void *src, void *dest, int model) {
#define LOCK_FREE_ACTION(type)                                                 \
  *((type *)dest) = __c11_atomic_load((_Atomic(type) *)src, model);            \
  return;
  LOCK_FREE_CASES(src);
#undef LOCK_FREE_ACTION
  Lock *l = lock_for_pointer(src);
  lock(l);
  memcpy(dest, src, size);
  unlock(l);
}

/// An atomic store operation.  This is atomic with respect to the destination
/// pointer only.
void __atomic_store_c(size_t size, void *dest, void *src, int model) {
#define LOCK_FREE_ACTION(type)                                                 \
  __c11_atomic_store((_Atomic(type) *)dest, *(type *)src, model);              \
  return;
  LOCK_FREE_CASES(dest);
#undef LOCK_FREE_ACTION
  Lock *l = lock_for_pointer(dest);
  lock(l);
  memcpy(dest, src, size);
  unlock(l);
}

/// Atomic compare and exchange operation.  If the value at *ptr is identical
/// to the value at *expected, then this copies value at *desired to *ptr.  If
/// they  are not, then this stores the current value from *ptr in *expected.
///
/// This function returns 1 if the exchange takes place or 0 if it fails.
int __atomic_compare_exchange_c(size_t size, void *ptr, void *expected,
                                void *desired, int success, int failure) {
#define LOCK_FREE_ACTION(type)                                                 \
  return __c11_atomic_compare_exchange_strong(                                 \
      (_Atomic(type) *)ptr, (type *)expected, *(type *)desired, success,       \
      failure)
  LOCK_FREE_CASES(ptr);
#undef LOCK_FREE_ACTION
  Lock *l = lock_for_pointer(ptr);
  lock(l);
  if (memcmp(ptr, expected, size) == 0) {
    memcpy(ptr, desired, size);
    unlock(l);
    return 1;
  }
  memcpy(expected, ptr, size);
  unlock(l);
  return 0;
}

/// Performs an atomic exchange operation between two pointers.  This is atomic
/// with respect to the target address.
void __atomic_exchange_c(size_t size, void *ptr, void *val, void *old,
                         int model) {
#define LOCK_FREE_ACTION(type)                                                 \
  *(type *)old =                                                               \
      __c11_atomic_exchange((_Atomic(type) *)ptr, *(type *)val, model);        \
  return;
  LOCK_FREE_CASES(ptr);
#undef LOCK_FREE_ACTION
  Lock *l = lock_for_pointer(ptr);
  lock(l);
  memcpy(old, ptr, size);
  memcpy(ptr, val, size);
  unlock(l);
}

////////////////////////////////////////////////////////////////////////////////
// Where the size is known at compile time, the compiler may emit calls to
// specialised versions of the above functions.
////////////////////////////////////////////////////////////////////////////////
#ifdef __SIZEOF_INT128__
#define OPTIMISED_CASES                                                        \
  OPTIMISED_CASE(1, IS_LOCK_FREE_1, uint8_t)                                   \
  OPTIMISED_CASE(2, IS_LOCK_FREE_2, uint16_t)                                  \
  OPTIMISED_CASE(4, IS_LOCK_FREE_4, uint32_t)                                  \
  OPTIMISED_CASE(8, IS_LOCK_FREE_8, uint64_t)                                  \
  OPTIMISED_CASE(16, IS_LOCK_FREE_16, __uint128_t)
#else
#define OPTIMISED_CASES                                                        \
  OPTIMISED_CASE(1, IS_LOCK_FREE_1, uint8_t)                                   \
  OPTIMISED_CASE(2, IS_LOCK_FREE_2, uint16_t)                                  \
  OPTIMISED_CASE(4, IS_LOCK_FREE_4, uint32_t)                                  \
  OPTIMISED_CASE(8, IS_LOCK_FREE_8, uint64_t)
#endif

#ifdef __clang__
#define ATOMIC_NAME(name) name
#else
// See above: GCC gets these functions with a _c suffix too.
#define ATOMIC_NAME(name) name##_c
#define OPTIMISED_CASE(n, lockfree, type)                                      \
  ATOMIC_DECL(type, __atomic_load_##n, (type *, int));                         \
  ATOMIC_DECL(void, __atomic_store_##n, (type *, type, int));                  \
  ATOMIC_DECL(type, __atomic_exchange_##n, (type *, type, int));               \
  ATOMIC_DECL(bool, __atomic_compare_exchange_##n,                             \
              (type *, type *, type, int, int));                               \
  ATOMIC_DECL(type, __atomic_fetch_add_##n, (type *, type, int));              \
  ATOMIC_DECL(type, __atomic_fetch_sub_##n, (type *, type, int));              \
  ATOMIC_DECL(type, __atomic_fetch_and_##n, (type *, type, int));              \
  ATOMIC_DECL(type, __atomic_fetch_or_##n, (type *, type, int));               \
  ATOMIC_DECL(type, __atomic_fetch_xor_##n, (type *, type, int));              \
  ATOMIC_DECL(type, __atomic_fetch_nand_##n, (type *, type, int));
OPTIMISED_CASES
#undef OPTIMISED_CASE
#endif

// clang-format off
#define OPTIMISED_CASE(n, lockfree, type)                                      \
  type ATOMIC_NAME(__atomic_load_##n)(type *src, int model) {                  \
    if (lockfree(src))                                                         \
      return __c11_atomic_load((_Atomic(type) *)src, model);                   \
    Lock *l = lock_for_pointer(src);                                           \
    lock(l);                                                                   \
    type val = *src;                                                           \
    unlock(l);                                                                 \
    return val;                                                                \
  }
OPTIMISED_CASES
#undef OPTIMISED_CASE

#define OPTIMISED_CASE(n, lockfree, type)                                      \
  void ATOMIC_NAME(__atomic_store_##n)(type *dest, type val, int model) {      \
    if (lockfree(dest)) {                                                      \
      __c11_atomic_store((_Atomic(type) *)dest, val, model);                   \
      return;                                                                  \
    }                                                                          \
    Lock *l = lock_for_pointer(dest);                                          \
    lock(l);                                                                   \
    *dest = val;                                                               \
    unlock(l);                                                                 \
    return;                                                                    \
  }
OPTIMISED_CASES
#undef OPTIMISED_CASE

#define OPTIMISED_CASE(n, lockfree, type)                                      \
  type ATOMIC_NAME(__atomic_exchange_##n)(type *dest, type val, int model) {   \
    if (lockfree(dest))                                                        \
      return __c11_atomic_exchange((_Atomic(type) *)dest, val, model);         \
    Lock *l = lock_for_pointer(dest);                                          \
    lock(l);                                                                   \
    type tmp = *dest;                                                          \
    *dest = val;                                                               \
    unlock(l);                                                                 \
    return tmp;                                                                \
  }
OPTIMISED_CASES
#undef OPTIMISED_CASE

#define OPTIMISED_CASE(n, lockfree, type)                                      \
  bool ATOMIC_NAME(__atomic_compare_exchange_##n)(type *ptr, type *expected,   \
                                                  type desired, int success,   \
                                                  int failure) {               \
    if (lockfree(ptr))                                                         \
      return __c11_atomic_compare_exchange_strong(                             \
          (_Atomic(type) *)ptr, expected, desired, success, failure);          \
    Lock *l = lock_for_pointer(ptr);                                           \
    lock(l);                                                                   \
    if (*ptr == *expected) {                                                   \
      *ptr = desired;                                                          \
      unlock(l);                                                               \
      return true;                                                             \
    }                                                                          \
    *expected = *ptr;                                                          \
    unlock(l);                                                                 \
    return false;                                                              \
  }
OPTIMISED_CASES
#undef OPTIMISED_CASE

////////////////////////////////////////////////////////////////////////////////
// Atomic read-modify-write operations for integers of various sizes.
////////////////////////////////////////////////////////////////////////////////
#define ATOMIC_RMW(n, lockfree, type, opname, op)                              \
  type ATOMIC_NAME(__atomic_fetch_##opname##_##n)(type *ptr, type val,         \
                                                  int model) {                 \
    if (lockfree(ptr))                                                         \
      return __c11_atomic_fetch_##opname((_Atomic(type) *)ptr, val, model);    \
    Lock *l = lock_for_pointer(ptr);                                           \
    lock(l);                                                                   \
    type tmp = *ptr;                                                           \
    *ptr = tmp op val;                                                         \
    unlock(l);                                                                 \
    return tmp;                                                                \
  }

#define ATOMIC_RMW_NAND(n, lockfree, type)                                     \
  type ATOMIC_NAME(__atomic_fetch_nand_##n)(type *ptr, type val, int model) {  \
    if (lockfree(ptr))                                                         \
      return __c11_atomic_fetch_nand((_Atomic(type) *)ptr, val, model);        \
    Lock *l = lock_for_pointer(ptr);                                           \
    lock(l);                                                                   \
    type tmp = *ptr;                                                           \
    *ptr = ~(tmp & val);                                                       \
    unlock(l);                                                                 \
    return tmp;                                                                \
  }
// clang-format on

#define OPTIMISED_CASE(n, lockfree, type) ATOMIC_RMW(n, lockfree, type, add, +)
OPTIMISED_CASES
#undef OPTIMISED_CASE
#define OPTIMISED_CASE(n, lockfree, type) ATOMIC_RMW(n, lockfree, type, sub, -)
OPTIMISED_CASES
#undef OPTIMISED_CASE
#define OPTIMISED_CASE(n, lockfree, type) ATOMIC_RMW(n, lockfree, type, and, &)
OPTIMISED_CASES
#undef OPTIMISED_CASE
#define OPTIMISED_CASE(n, lockfree, type) ATOMIC_RMW(n, lockfree, type, or, |)
OPTIMISED_CASES
#undef OPTIMISED_CASE
#define OPTIMISED_CASE(n, lockfree, type) ATOMIC_RMW(n, lockfree, type, xor, ^)
OPTIMISED_CASES
#undef OPTIMISED_CASE
// Allow build with clang without __c11_atomic_fetch_nand builtin (pre-14)
// and with GCC, which has it.
#ifdef __clang__
#define HAS_ATOMIC_FETCH_NAND __has_builtin(__c11_atomic_fetch_nand)
#else
#define HAS_ATOMIC_FETCH_NAND 1
#endif
#if HAS_ATOMIC_FETCH_NAND
#define OPTIMISED_CASE(n, lockfree, type) ATOMIC_RMW_NAND(n, lockfree, type)
OPTIMISED_CASES
#undef OPTIMISED_CASE
#endif

#undef memcpy
#undef memcmp
#undef SPINLOCK_COUNT
#undef ATOMIC_ALWAYS_LOCK_FREE_OR_ALIGNED_LOCK_FREE
#undef IS_LOCK_FREE_1
#undef IS_LOCK_FREE_2
#undef IS_LOCK_FREE_4
#undef IS_LOCK_FREE_8
#undef IS_LOCK_FREE_16
#undef TRY_LOCK_FREE_CASE
#undef TRY_LOCK_FREE_CASE_16
#undef LOCK_FREE_CASES
#undef OPTIMISED_CASES
#undef ATOMIC_RMW
#undef ATOMIC_RMW_NAND
#undef ATOMIC_NAME
#undef HAS_ATOMIC_FETCH_NAND
#ifndef __clang__
#undef __c11_atomic_load
#undef __c11_atomic_store
#undef __c11_atomic_exchange
#undef __c11_atomic_compare_exchange_strong
#undef __c11_atomic_compare_exchange_weak
#undef __c11_atomic_fetch_add
#undef __c11_atomic_fetch_sub
#undef __c11_atomic_fetch_and
#undef __c11_atomic_fetch_or
#undef __c11_atomic_fetch_xor
#undef __c11_atomic_fetch_nand
#undef ATOMIC_STR_
#undef ATOMIC_STR
#undef ATOMIC_DECL
#endif

#pragma GCC diagnostic pop

#endif
//===-- atomic_flag_clear.c -----------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
// 2026/10/17 - Modified by Mintsuki for use inside freestanding-lgrt
//
//===----------------------------------------------------------------------===//
//
// This file implements atomic_flag_clear from C11's stdatomic.h.
//
//===----------------------------------------------------------------------===//

#ifndef __has_include
#define __has_include(inc) 0
#endif

// Built as C11 or later, where atomic.c is, except with GCC on ARM before v6K.
//
// Workaround: GCC 6 up to at least 14, ARM before v6K: up to 13, it makes a
// byte test-and-set a plain load and store, which is not atomic, and from 14
// on, a call to a library function.
#if __has_include(<stdatomic.h>) && defined(__STDC_VERSION__) &&               \
    __STDC_VERSION__ >= 201112L &&                                             \
    (defined(__clang__) || defined(__GNUC__)) &&                               \
    !(!defined(__clang__) && __GNUC__ < 5) &&                                  \
    __GCC_ATOMIC_POINTER_LOCK_FREE == 2 &&                                     \
    !(defined(__i386__) && !defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_4)) &&    \
    !(defined(__arm__) &&                                                      \
      (__ARM_ARCH < 6 ||                                                       \
       (defined(__thumb__) && !defined(__thumb2__) && __ARM_ARCH < 8))) &&     \
    !(defined(__arm__) && defined(__clang__) &&                                \
      defined(__ARM_FEATURE_LDREX) && !(__ARM_FEATURE_LDREX & 1)) &&           \
    !(defined(__arm__) && !defined(__clang__) &&                               \
      !defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_1)) &&                         \
    !(defined(__loongarch__) && __loongarch_grlen == 32 &&                     \
      (!defined(__clang__) || __clang_major__ < 21))

#include <stdatomic.h>
#undef atomic_flag_clear
void atomic_flag_clear(volatile atomic_flag *object) {
  __atomic_clear(object, __ATOMIC_SEQ_CST);
}

#endif
//===-- atomic_flag_clear_explicit.c --------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
// 2026/10/17 - Modified by Mintsuki for use inside freestanding-lgrt
//
//===----------------------------------------------------------------------===//
//
// This file implements atomic_flag_clear_explicit from C11's stdatomic.h.
//
//===----------------------------------------------------------------------===//

#ifndef __has_include
#define __has_include(inc) 0
#endif

// Built as C11 or later, where atomic.c is, except with GCC on ARM before v6K.
//
// Workaround: GCC 6 up to at least 14, ARM before v6K: up to 13, it makes a
// byte test-and-set a plain load and store, which is not atomic, and from 14
// on, a call to a library function.
#if __has_include(<stdatomic.h>) && defined(__STDC_VERSION__) &&               \
    __STDC_VERSION__ >= 201112L &&                                             \
    (defined(__clang__) || defined(__GNUC__)) &&                               \
    !(!defined(__clang__) && __GNUC__ < 5) &&                                  \
    __GCC_ATOMIC_POINTER_LOCK_FREE == 2 &&                                     \
    !(defined(__i386__) && !defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_4)) &&    \
    !(defined(__arm__) &&                                                      \
      (__ARM_ARCH < 6 ||                                                       \
       (defined(__thumb__) && !defined(__thumb2__) && __ARM_ARCH < 8))) &&     \
    !(defined(__arm__) && defined(__clang__) &&                                \
      defined(__ARM_FEATURE_LDREX) && !(__ARM_FEATURE_LDREX & 1)) &&           \
    !(defined(__arm__) && !defined(__clang__) &&                               \
      !defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_1)) &&                         \
    !(defined(__loongarch__) && __loongarch_grlen == 32 &&                     \
      (!defined(__clang__) || __clang_major__ < 21))

#include <stdatomic.h>
#undef atomic_flag_clear_explicit
void atomic_flag_clear_explicit(volatile atomic_flag *object,
                                memory_order order) {
  __atomic_clear(object, order);
}

#endif
//===-- atomic_flag_test_and_set.c ----------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
// 2026/10/17 - Modified by Mintsuki for use inside freestanding-lgrt
//
//===----------------------------------------------------------------------===//
//
// This file implements atomic_flag_test_and_set from C11's stdatomic.h.
//
//===----------------------------------------------------------------------===//

#ifndef __has_include
#define __has_include(inc) 0
#endif

// Built as C11 or later, where atomic.c is, except with GCC on ARM before v6K.
//
// Workaround: GCC 6 up to at least 14, ARM before v6K: up to 13, it makes a
// byte test-and-set a plain load and store, which is not atomic, and from 14
// on, a call to a library function.
#if __has_include(<stdatomic.h>) && defined(__STDC_VERSION__) &&               \
    __STDC_VERSION__ >= 201112L &&                                             \
    (defined(__clang__) || defined(__GNUC__)) &&                               \
    !(!defined(__clang__) && __GNUC__ < 5) &&                                  \
    __GCC_ATOMIC_POINTER_LOCK_FREE == 2 &&                                     \
    !(defined(__i386__) && !defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_4)) &&    \
    !(defined(__arm__) &&                                                      \
      (__ARM_ARCH < 6 ||                                                       \
       (defined(__thumb__) && !defined(__thumb2__) && __ARM_ARCH < 8))) &&     \
    !(defined(__arm__) && defined(__clang__) &&                                \
      defined(__ARM_FEATURE_LDREX) && !(__ARM_FEATURE_LDREX & 1)) &&           \
    !(defined(__arm__) && !defined(__clang__) &&                               \
      !defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_1)) &&                         \
    !(defined(__loongarch__) && __loongarch_grlen == 32 &&                     \
      (!defined(__clang__) || __clang_major__ < 21))

#include <stdatomic.h>
#undef atomic_flag_test_and_set
_Bool atomic_flag_test_and_set(volatile atomic_flag *object) {
  return __atomic_test_and_set(object, __ATOMIC_SEQ_CST);
}

#endif
//===-- atomic_flag_test_and_set_explicit.c -------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
// 2026/10/17 - Modified by Mintsuki for use inside freestanding-lgrt
//
//===----------------------------------------------------------------------===//
//
// This file implements atomic_flag_test_and_set_explicit from C11's stdatomic.h
//
//===----------------------------------------------------------------------===//

#ifndef __has_include
#define __has_include(inc) 0
#endif

// Built as C11 or later, where atomic.c is, except with GCC on ARM before v6K.
//
// Workaround: GCC 6 up to at least 14, ARM before v6K: up to 13, it makes a
// byte test-and-set a plain load and store, which is not atomic, and from 14
// on, a call to a library function.
#if __has_include(<stdatomic.h>) && defined(__STDC_VERSION__) &&               \
    __STDC_VERSION__ >= 201112L &&                                             \
    (defined(__clang__) || defined(__GNUC__)) &&                               \
    !(!defined(__clang__) && __GNUC__ < 5) &&                                  \
    __GCC_ATOMIC_POINTER_LOCK_FREE == 2 &&                                     \
    !(defined(__i386__) && !defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_4)) &&    \
    !(defined(__arm__) &&                                                      \
      (__ARM_ARCH < 6 ||                                                       \
       (defined(__thumb__) && !defined(__thumb2__) && __ARM_ARCH < 8))) &&     \
    !(defined(__arm__) && defined(__clang__) &&                                \
      defined(__ARM_FEATURE_LDREX) && !(__ARM_FEATURE_LDREX & 1)) &&           \
    !(defined(__arm__) && !defined(__clang__) &&                               \
      !defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_1)) &&                         \
    !(defined(__loongarch__) && __loongarch_grlen == 32 &&                     \
      (!defined(__clang__) || __clang_major__ < 21))

#include <stdatomic.h>
#undef atomic_flag_test_and_set_explicit
_Bool atomic_flag_test_and_set_explicit(volatile atomic_flag *object,
                                        memory_order order) {
  return __atomic_test_and_set(object, order);
}

#endif
//===-- atomic_signal_fence.c ---------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
// 2026/10/17 - Modified by Mintsuki for use inside freestanding-lgrt
//
//===----------------------------------------------------------------------===//
//
// This file implements atomic_signal_fence from C11's stdatomic.h.
//
//===----------------------------------------------------------------------===//

#ifndef __has_include
#define __has_include(inc) 0
#endif

// Built as C11 or later, where atomic.c is, except with GCC on ARM before v6K.
//
// Workaround: GCC 6 up to at least 14, ARM before v6K: up to 13, it makes a
// byte test-and-set a plain load and store, which is not atomic, and from 14
// on, a call to a library function.
#if __has_include(<stdatomic.h>) && defined(__STDC_VERSION__) &&               \
    __STDC_VERSION__ >= 201112L &&                                             \
    (defined(__clang__) || defined(__GNUC__)) &&                               \
    !(!defined(__clang__) && __GNUC__ < 5) &&                                  \
    __GCC_ATOMIC_POINTER_LOCK_FREE == 2 &&                                     \
    !(defined(__i386__) && !defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_4)) &&    \
    !(defined(__arm__) &&                                                      \
      (__ARM_ARCH < 6 ||                                                       \
       (defined(__thumb__) && !defined(__thumb2__) && __ARM_ARCH < 8))) &&     \
    !(defined(__arm__) && defined(__clang__) &&                                \
      defined(__ARM_FEATURE_LDREX) && !(__ARM_FEATURE_LDREX & 1)) &&           \
    !(defined(__arm__) && !defined(__clang__) &&                               \
      !defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_1)) &&                         \
    !(defined(__loongarch__) && __loongarch_grlen == 32 &&                     \
      (!defined(__clang__) || __clang_major__ < 21))

#include <stdatomic.h>
#undef atomic_signal_fence
void atomic_signal_fence(memory_order order) { __atomic_signal_fence(order); }

#endif
//===-- atomic_thread_fence.c ---------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
// 2026/10/17 - Modified by Mintsuki for use inside freestanding-lgrt
//
//===----------------------------------------------------------------------===//
//
// This file implements atomic_thread_fence from C11's stdatomic.h.
//
//===----------------------------------------------------------------------===//

#ifndef __has_include
#define __has_include(inc) 0
#endif

// Built as C11 or later, where atomic.c is, except with GCC on ARM before v6K.
//
// Workaround: GCC 6 up to at least 14, ARM before v6K: up to 13, it makes a
// byte test-and-set a plain load and store, which is not atomic, and from 14
// on, a call to a library function.
#if __has_include(<stdatomic.h>) && defined(__STDC_VERSION__) &&               \
    __STDC_VERSION__ >= 201112L &&                                             \
    (defined(__clang__) || defined(__GNUC__)) &&                               \
    !(!defined(__clang__) && __GNUC__ < 5) &&                                  \
    __GCC_ATOMIC_POINTER_LOCK_FREE == 2 &&                                     \
    !(defined(__i386__) && !defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_4)) &&    \
    !(defined(__arm__) &&                                                      \
      (__ARM_ARCH < 6 ||                                                       \
       (defined(__thumb__) && !defined(__thumb2__) && __ARM_ARCH < 8))) &&     \
    !(defined(__arm__) && defined(__clang__) &&                                \
      defined(__ARM_FEATURE_LDREX) && !(__ARM_FEATURE_LDREX & 1)) &&           \
    !(defined(__arm__) && !defined(__clang__) &&                               \
      !defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_1)) &&                         \
    !(defined(__loongarch__) && __loongarch_grlen == 32 &&                     \
      (!defined(__clang__) || __clang_major__ < 21))

#include <stdatomic.h>
#undef atomic_thread_fence
void atomic_thread_fence(memory_order order) { __atomic_thread_fence(order); }

#endif
//===-- bswapdi2.c - Implement __bswapdi2 ---------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements __bswapdi2 for the compiler_rt library.
//
//===----------------------------------------------------------------------===//


COMPILER_RT_ABI uint64_t __bswapdi2(uint64_t u) {
  return (
      (((u)&0xff00000000000000ULL) >> 56) |
      (((u)&0x00ff000000000000ULL) >> 40) |
      (((u)&0x0000ff0000000000ULL) >> 24) |
      (((u)&0x000000ff00000000ULL) >> 8)  |
      (((u)&0x00000000ff000000ULL) << 8)  |
      (((u)&0x0000000000ff0000ULL) << 24) |
      (((u)&0x000000000000ff00ULL) << 40) |
      (((u)&0x00000000000000ffULL) << 56));
}
//===-- bswapsi2.c - Implement __bswapsi2 ---------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements __bswapsi2 for the compiler_rt library.
//
//===----------------------------------------------------------------------===//


COMPILER_RT_ABI uint32_t __bswapsi2(uint32_t u) {
  return ((((u)&0xff000000) >> 24) |
          (((u)&0x00ff0000) >> 8)  |
          (((u)&0x0000ff00) << 8)  |
          (((u)&0x000000ff) << 24));
}
//===-- clzdi2.c - Implement __clzdi2 -------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
// 2024/08/10 - Modified by Mintsuki for use inside freestanding-lgrt
//
//===----------------------------------------------------------------------===//
//
// This file implements __clzdi2 for the compiler_rt library.
//
//===----------------------------------------------------------------------===//


// Returns: the number of leading 0-bits

#if defined(__riscv) && __SIZEOF_POINTER__ >= 8
// On 64-bit architectures with neither a native clz instruction nor a native
// ctz instruction, `__builtin_clz` resolves to `__clzdi2` rather than
// __clzsi2 as libgcc does not ship with `__clzsi2`, leading to infinite
// recursion.
#define __builtin_clz(a) __clzsi2(a)
extern int __clzsi2(si_int);
#endif

// Precondition: a != 0

COMPILER_RT_ABI int __clzdi2(di_int a) {
  dwords x;
  x.all = a;
  const si_int f = -(x.s.high == 0);
  return clzsi((x.s.high & ~f) | (x.s.low & f)) +
         (f & ((si_int)(sizeof(si_int) * CHAR_BIT)));
}

#ifdef __builtin_clz
#undef __builtin_clz
#endif
//===-- clzsi2.c - Implement __clzsi2 -------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements __clzsi2 for the compiler_rt library.
//
//===----------------------------------------------------------------------===//


// Returns: the number of leading 0-bits

// Precondition: a != 0

COMPILER_RT_ABI int __clzsi2(si_int a) {
  su_int x = (su_int)a;
  si_int t = ((x & 0xFFFF0000) == 0) << 4; // if (x is small) t = 16 else 0
  x >>= 16 - t;                            // x = [0 - 0xFFFF]
  su_int r = t;                            // r = [0, 16]
  // return r + clz(x)
  t = ((x & 0xFF00) == 0) << 3;
  x >>= 8 - t; // x = [0 - 0xFF]
  r += t;      // r = [0, 8, 16, 24]
  // return r + clz(x)
  t = ((x & 0xF0) == 0) << 2;
  x >>= 4 - t; // x = [0 - 0xF]
  r += t;      // r = [0, 4, 8, 12, 16, 20, 24, 28]
  // return r + clz(x)
  t = ((x & 0xC) == 0) << 1;
  x >>= 2 - t; // x = [0 - 3]
  r += t;      // r = [0 - 30] and is even
  // return r + clz(x)
  //     switch (x)
  //     {
  //     case 0:
  //         return r + 2;
  //     case 1:
  //         return r + 1;
  //     case 2:
  //     case 3:
  //         return r;
  //     }
  return r + ((2 - x) & -((x & 2) == 0));
}
//===-- clzti2.c - Implement __clzti2 -------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements __clzti2 for the compiler_rt library.
//
//===----------------------------------------------------------------------===//


#ifdef CRT_HAS_128BIT

// Returns: the number of leading 0-bits

// Precondition: a != 0

COMPILER_RT_ABI int __clzti2(ti_int a) {
  twords x;
  x.all = a;
  const di_int f = -(x.s.high == 0);
  return __builtin_clzll((x.s.high & ~f) | (x.s.low & f)) +
         ((si_int)f & ((si_int)(sizeof(di_int) * CHAR_BIT)));
}

#endif // CRT_HAS_128BIT
//===-- cmpdi2.c - Implement __cmpdi2 -------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements __cmpdi2 for the compiler_rt library.
//
//===----------------------------------------------------------------------===//


// Returns: if (a <  b) returns 0
//           if (a == b) returns 1
//           if (a >  b) returns 2

COMPILER_RT_ABI si_int __cmpdi2(di_int a, di_int b) {
  dwords x;
  x.all = a;
  dwords y;
  y.all = b;
  if (x.s.high < y.s.high)
    return 0;
  if (x.s.high > y.s.high)
    return 2;
  if (x.s.low < y.s.low)
    return 0;
  if (x.s.low > y.s.low)
    return 2;
  return 1;
}

#ifdef __ARM_EABI__
// Returns: if (a <  b) returns -1
//           if (a == b) returns  0
//           if (a >  b) returns  1
COMPILER_RT_ABI si_int __aeabi_lcmp(di_int a, di_int b) {
  return __cmpdi2(a, b) - 1;
}
#endif
//===-- cmpti2.c - Implement __cmpti2 -------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements __cmpti2 for the compiler_rt library.
//
//===----------------------------------------------------------------------===//


#ifdef CRT_HAS_128BIT

// Returns:  if (a <  b) returns 0
//           if (a == b) returns 1
//           if (a >  b) returns 2

COMPILER_RT_ABI si_int __cmpti2(ti_int a, ti_int b) {
  twords x;
  x.all = a;
  twords y;
  y.all = b;
  if (x.s.high < y.s.high)
    return 0;
  if (x.s.high > y.s.high)
    return 2;
  if (x.s.low < y.s.low)
    return 0;
  if (x.s.low > y.s.low)
    return 2;
  return 1;
}

#endif // CRT_HAS_128BIT
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


#if defined(__aarch64__)

// LSE support detection for out-of-line atomics
// using HWCAP and Auxiliary vector
_Bool __aarch64_have_lse_atomics
    __attribute__((visibility("hidden"), nocommon)) = false;

// When unimplemented, we leave __aarch64_have_lse_atomics initialized to false.

#endif
//===-- ctzdi2.c - Implement __ctzdi2 -------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
// 2024/08/10 - Modified by Mintsuki for use inside freestanding-lgrt
//
//===----------------------------------------------------------------------===//
//
// This file implements __ctzdi2 for the compiler_rt library.
//
//===----------------------------------------------------------------------===//


// Returns: the number of trailing 0-bits

#if !defined(__clang__) && defined(__riscv) && __SIZEOF_POINTER__ >= 8
// On 64-bit architectures with neither a native clz instruction nor a native
// ctz instruction, gcc resolves __builtin_ctz to __ctzdi2 rather than
// __ctzsi2, leading to infinite recursion.
#define __builtin_ctz(a) __ctzsi2(a)
extern int __ctzsi2(si_int);
#endif

// Precondition: a != 0

COMPILER_RT_ABI int __ctzdi2(di_int a) {
  dwords x;
  x.all = a;
  const si_int f = -(x.s.low == 0);
  return ctzsi((x.s.high & f) | (x.s.low & ~f)) +
         (f & ((si_int)(sizeof(si_int) * CHAR_BIT)));
}

#ifdef __builtin_ctz
#undef __builtin_ctz
#endif
//===-- ctzsi2.c - Implement __ctzsi2 -------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements __ctzsi2 for the compiler_rt library.
//
//===----------------------------------------------------------------------===//


// Returns: the number of trailing 0-bits

// Precondition: a != 0

COMPILER_RT_ABI int __ctzsi2(si_int a) {
  su_int x = (su_int)a;
  si_int t = ((x & 0x0000FFFF) == 0)
             << 4; // if (x has no small bits) t = 16 else 0
  x >>= t;         // x = [0 - 0xFFFF] + higher garbage bits
  su_int r = t;    // r = [0, 16]
  // return r + ctz(x)
  t = ((x & 0x00FF) == 0) << 3;
  x >>= t; // x = [0 - 0xFF] + higher garbage bits
  r += t;  // r = [0, 8, 16, 24]
  // return r + ctz(x)
  t = ((x & 0x0F) == 0) << 2;
  x >>= t; // x = [0 - 0xF] + higher garbage bits
  r += t;  // r = [0, 4, 8, 12, 16, 20, 24, 28]
  // return r + ctz(x)
  t = ((x & 0x3) == 0) << 1;
  x >>= t;
  x &= 3; // x = [0 - 3]
  r += t; // r = [0 - 30] and is even
  // return r + ctz(x)

  //  The branch-less return statement below is equivalent
  //  to the following switch statement:
  //     switch (x)
  //    {
  //     case 0:
  //         return r + 2;
  //     case 2:
  //         return r + 1;
  //     case 1:
  //     case 3:
  //         return r;
  //     }
  return r + ((2 - (x >> 1)) & -((x & 1) == 0));
}
//===-- ctzti2.c - Implement __ctzti2 -------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements __ctzti2 for the compiler_rt library.
//
//===----------------------------------------------------------------------===//


#ifdef CRT_HAS_128BIT

// Returns: the number of trailing 0-bits

// Precondition: a != 0

COMPILER_RT_ABI int __ctzti2(ti_int a) {
  twords x;
  x.all = a;
  const di_int f = -(x.s.low == 0);
  return __builtin_ctzll((x.s.high & f) | (x.s.low & ~f)) +
         ((si_int)f & ((si_int)(sizeof(di_int) * CHAR_BIT)));
}

#endif // CRT_HAS_128BIT
//===-- divdi3.c - Implement __divdi3 -------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
// 2024/08/10 - Modified by Mintsuki for use inside freestanding-lgrt
//
//===----------------------------------------------------------------------===//
//
// This file implements __divdi3 for the compiler_rt library.
//
//===----------------------------------------------------------------------===//


// Returns: a / b

#define fixint_t di_int
#define fixuint_t du_int
#define COMPUTE_UDIV(a, b) __udivmoddi4((a), (b), (du_int *)0)
//===-- int_div_impl.inc - Integer division ---------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
// 2024/10/20 - Modified by Mintsuki for use inside freestanding-lgrt
//
//===----------------------------------------------------------------------===//
//
// Helpers used by __udivsi3, __umodsi3, __udivdi3, and __umodsi3.
//
//===----------------------------------------------------------------------===//

#define clz(a) (sizeof(a) == sizeof(unsigned long long) ? __builtin_clzll(a) : clzsi(a))

#undef __udivXi3
#define __udivXi3 __udivXi3_1

// Adapted from Figure 3-40 of The PowerPC Compiler Writer's Guide
static __inline fixuint_t __udivXi3(fixuint_t n, fixuint_t d) {
  const unsigned N = sizeof(fixuint_t) * CHAR_BIT;
  // d == 0 cases are unspecified.
  unsigned sr = (d ? clz(d) : N) - (n ? clz(n) : N);
  // 0 <= sr <= N - 1 or sr is very large.
  if (sr > N - 1) // n < d
    return 0;
  if (sr == N - 1) // d == 1
    return n;
  ++sr;
  // 1 <= sr <= N - 1. Shifts do not trigger UB.
  fixuint_t r = n >> sr;
  n <<= N - sr;
  fixuint_t carry = 0;
  for (; sr > 0; --sr) {
    r = (r << 1) | (n >> (N - 1));
    n = (n << 1) | carry;
    // Branch-less version of:
    // carry = 0;
    // if (r >= d) r -= d, carry = 1;
    const fixint_t s = (fixint_t)(d - r - 1) >> (N - 1);
    carry = s & 1;
    r -= d & s;
  }
  n = (n << 1) | carry;
  return n;
}

#undef __umodXi3
#define __umodXi3 __umodXi3_2

// Mostly identical to __udivXi3 but the return values are different.
static __inline fixuint_t __umodXi3(fixuint_t n, fixuint_t d) {
  const unsigned N = sizeof(fixuint_t) * CHAR_BIT;
  // d == 0 cases are unspecified.
  unsigned sr = (d ? clz(d) : N) - (n ? clz(n) : N);
  // 0 <= sr <= N - 1 or sr is very large.
  if (sr > N - 1) // n < d
    return n;
  if (sr == N - 1) // d == 1
    return 0;
  ++sr;
  // 1 <= sr <= N - 1. Shifts do not trigger UB.
  fixuint_t r = n >> sr;
  n <<= N - sr;
  fixuint_t carry = 0;
  for (; sr > 0; --sr) {
    r = (r << 1) | (n >> (N - 1));
    n = (n << 1) | carry;
    // Branch-less version of:
    // carry = 0;
    // if (r >= d) r -= d, carry = 1;
    const fixint_t s = (fixint_t)(d - r - 1) >> (N - 1);
    carry = s & 1;
    r -= d & s;
  }
  return r;
}

#undef __divXi3

#ifdef COMPUTE_UDIV

#define __divXi3 __divXi3_3

static __inline fixint_t __divXi3(fixint_t a, fixint_t b) {
  const int N = (int)(sizeof(fixint_t) * CHAR_BIT) - 1;
  fixint_t s_a = a >> N;                            // s_a = a < 0 ? -1 : 0
  fixint_t s_b = b >> N;                            // s_b = b < 0 ? -1 : 0
  fixuint_t a_u = (fixuint_t)(a ^ s_a) + (-s_a);    // negate if s_a == -1
  fixuint_t b_u = (fixuint_t)(b ^ s_b) + (-s_b);    // negate if s_b == -1
  s_a ^= s_b;                                       // sign of quotient
  return (COMPUTE_UDIV(a_u, b_u) ^ s_a) + (-s_a);   // negate if s_a == -1
}
#endif // COMPUTE_UDIV

#undef __modXi3

#ifdef ASSIGN_UMOD

#define __modXi3 __modXi3_4

static __inline fixint_t __modXi3(fixint_t a, fixint_t b) {
  const int N = (int)(sizeof(fixint_t) * CHAR_BIT) - 1;
  fixint_t s = b >> N;                              // s = b < 0 ? -1 : 0
  fixuint_t b_u = (fixuint_t)(b ^ s) + (-s);        // negate if s == -1
  s = a >> N;                                       // s = a < 0 ? -1 : 0
  fixuint_t a_u = (fixuint_t)(a ^ s) + (-s);        // negate if s == -1
  fixuint_t res;
  ASSIGN_UMOD(res, a_u, b_u);
  return (res ^ s) + (-s);                          // negate if s == -1
}
#endif // ASSIGN_UMOD

#undef clz

COMPILER_RT_ABI di_int __divdi3(di_int a, di_int b) { return __divXi3(a, b); }

#undef fixint_t
#undef fixuint_t
#undef COMPUTE_UDIV
//===-- divmoddi4.c - Implement __divmoddi4 -------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements __divmoddi4 for the compiler_rt library.
//
//===----------------------------------------------------------------------===//


// Returns: a / b, *rem = a % b

COMPILER_RT_ABI di_int __divmoddi4(di_int a, di_int b, di_int *rem) {
  const int bits_in_dword_m1 = (int)(sizeof(di_int) * CHAR_BIT) - 1;
  di_int s_a = a >> bits_in_dword_m1;                   // s_a = a < 0 ? -1 : 0
  di_int s_b = b >> bits_in_dword_m1;                   // s_b = b < 0 ? -1 : 0
  a = (du_int)(a ^ s_a) - s_a;                          // negate if s_a == -1
  b = (du_int)(b ^ s_b) - s_b;                          // negate if s_b == -1
  s_b ^= s_a;                                           // sign of quotient
  du_int r;
  di_int q = (__udivmoddi4(a, b, &r) ^ s_b) - s_b;      // negate if s_b == -1
  *rem = (r ^ s_a) - s_a;                               // negate if s_a == -1
  return q;
}
//===-- divmodsi4.c - Implement __divmodsi4
//--------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements __divmodsi4 for the compiler_rt library.
//
//===----------------------------------------------------------------------===//


// Returns: a / b, *rem = a % b

COMPILER_RT_ABI si_int __divmodsi4(si_int a, si_int b, si_int *rem) {
  const int bits_in_word_m1 = (int)(sizeof(si_int) * CHAR_BIT) - 1;
  si_int s_a = a >> bits_in_word_m1;                    // s_a = a < 0 ? -1 : 0
  si_int s_b = b >> bits_in_word_m1;                    // s_b = b < 0 ? -1 : 0
  a = (su_int)(a ^ s_a) - s_a;                          // negate if s_a == -1
  b = (su_int)(b ^ s_b) - s_b;                          // negate if s_b == -1
  s_b ^= s_a;                                           // sign of quotient
  su_int r;
  si_int q = (__udivmodsi4(a, b, &r) ^ s_b) - s_b;      // negate if s_b == -1
  *rem = (r ^ s_a) - s_a;                               // negate if s_a == -1
  return q;
}
//===-- divmodti4.c - Implement __divmodti4 -------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements __divmodti4 for the compiler_rt library.
//
//===----------------------------------------------------------------------===//


#ifdef CRT_HAS_128BIT

// Returns: a / b, *rem = a % b

COMPILER_RT_ABI ti_int __divmodti4(ti_int a, ti_int b, ti_int *rem) {
  const int bits_in_tword_m1 = (int)(sizeof(ti_int) * CHAR_BIT) - 1;
  ti_int s_a = a >> bits_in_tword_m1;                   // s_a = a < 0 ? -1 : 0
  ti_int s_b = b >> bits_in_tword_m1;                   // s_b = b < 0 ? -1 : 0
  a = (tu_int)(a ^ s_a) - s_a;                          // negate if s_a == -1
  b = (tu_int)(b ^ s_b) - s_b;                          // negate if s_b == -1
  s_b ^= s_a;                                           // sign of quotient
  tu_int r;
  ti_int q = (__udivmodti4(a, b, &r) ^ s_b) - s_b;      // negate if s_b == -1
  *rem = (r ^ s_a) - s_a;                               // negate if s_a == -1
  return q;
}

#endif // CRT_HAS_128BIT
//===-- divsi3.c - Implement __divsi3 -------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
// 2024/08/10 - Modified by Mintsuki for use inside freestanding-lgrt
//
//===----------------------------------------------------------------------===//
//
// This file implements __divsi3 for the compiler_rt library.
//
//===----------------------------------------------------------------------===//


// Returns: a / b

#define fixint_t si_int
#define fixuint_t su_int
// On CPUs without unsigned hardware division support,
//  this calls __udivsi3 (notice the cast to su_int).
// On CPUs with unsigned hardware division support,
//  this uses the unsigned division instruction.
#define COMPUTE_UDIV(a, b) ((su_int)(a) / (su_int)(b))
//===-- int_div_impl.inc - Integer division ---------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
// 2024/10/20 - Modified by Mintsuki for use inside freestanding-lgrt
//
//===----------------------------------------------------------------------===//
//
// Helpers used by __udivsi3, __umodsi3, __udivdi3, and __umodsi3.
//
//===----------------------------------------------------------------------===//

#define clz(a) (sizeof(a) == sizeof(unsigned long long) ? __builtin_clzll(a) : clzsi(a))

#undef __udivXi3
#define __udivXi3 __udivXi3_5

// Adapted from Figure 3-40 of The PowerPC Compiler Writer's Guide
static __inline fixuint_t __udivXi3(fixuint_t n, fixuint_t d) {
  const unsigned N = sizeof(fixuint_t) * CHAR_BIT;
  // d == 0 cases are unspecified.
  unsigned sr = (d ? clz(d) : N) - (n ? clz(n) : N);
  // 0 <= sr <= N - 1 or sr is very large.
  if (sr > N - 1) // n < d
    return 0;
  if (sr == N - 1) // d == 1
    return n;
  ++sr;
  // 1 <= sr <= N - 1. Shifts do not trigger UB.
  fixuint_t r = n >> sr;
  n <<= N - sr;
  fixuint_t carry = 0;
  for (; sr > 0; --sr) {
    r = (r << 1) | (n >> (N - 1));
    n = (n << 1) | carry;
    // Branch-less version of:
    // carry = 0;
    // if (r >= d) r -= d, carry = 1;
    const fixint_t s = (fixint_t)(d - r - 1) >> (N - 1);
    carry = s & 1;
    r -= d & s;
  }
  n = (n << 1) | carry;
  return n;
}

#undef __umodXi3
#define __umodXi3 __umodXi3_6

// Mostly identical to __udivXi3 but the return values are different.
static __inline fixuint_t __umodXi3(fixuint_t n, fixuint_t d) {
  const unsigned N = sizeof(fixuint_t) * CHAR_BIT;
  // d == 0 cases are unspecified.
  unsigned sr = (d ? clz(d) : N) - (n ? clz(n) : N);
  // 0 <= sr <= N - 1 or sr is very large.
  if (sr > N - 1) // n < d
    return n;
  if (sr == N - 1) // d == 1
    return 0;
  ++sr;
  // 1 <= sr <= N - 1. Shifts do not trigger UB.
  fixuint_t r = n >> sr;
  n <<= N - sr;
  fixuint_t carry = 0;
  for (; sr > 0; --sr) {
    r = (r << 1) | (n >> (N - 1));
    n = (n << 1) | carry;
    // Branch-less version of:
    // carry = 0;
    // if (r >= d) r -= d, carry = 1;
    const fixint_t s = (fixint_t)(d - r - 1) >> (N - 1);
    carry = s & 1;
    r -= d & s;
  }
  return r;
}

#undef __divXi3

#ifdef COMPUTE_UDIV

#define __divXi3 __divXi3_7

static __inline fixint_t __divXi3(fixint_t a, fixint_t b) {
  const int N = (int)(sizeof(fixint_t) * CHAR_BIT) - 1;
  fixint_t s_a = a >> N;                            // s_a = a < 0 ? -1 : 0
  fixint_t s_b = b >> N;                            // s_b = b < 0 ? -1 : 0
  fixuint_t a_u = (fixuint_t)(a ^ s_a) + (-s_a);    // negate if s_a == -1
  fixuint_t b_u = (fixuint_t)(b ^ s_b) + (-s_b);    // negate if s_b == -1
  s_a ^= s_b;                                       // sign of quotient
  return (COMPUTE_UDIV(a_u, b_u) ^ s_a) + (-s_a);   // negate if s_a == -1
}
#endif // COMPUTE_UDIV

#undef __modXi3

#ifdef ASSIGN_UMOD

#define __modXi3 __modXi3_8

static __inline fixint_t __modXi3(fixint_t a, fixint_t b) {
  const int N = (int)(sizeof(fixint_t) * CHAR_BIT) - 1;
  fixint_t s = b >> N;                              // s = b < 0 ? -1 : 0
  fixuint_t b_u = (fixuint_t)(b ^ s) + (-s);        // negate if s == -1
  s = a >> N;                                       // s = a < 0 ? -1 : 0
  fixuint_t a_u = (fixuint_t)(a ^ s) + (-s);        // negate if s == -1
  fixuint_t res;
  ASSIGN_UMOD(res, a_u, b_u);
  return (res ^ s) + (-s);                          // negate if s == -1
}
#endif // ASSIGN_UMOD

#undef clz

COMPILER_RT_ABI si_int __divsi3(si_int a, si_int b) { return __divXi3(a, b); }

#if defined(__ARM_EABI__)
COMPILER_RT_ALIAS(__divsi3, __aeabi_idiv)
#endif

#undef fixint_t
#undef fixuint_t
#undef COMPUTE_UDIV
//===-- divti3.c - Implement __divti3 -------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
// 2024/08/10 - Modified by Mintsuki for use inside freestanding-lgrt
//
//===----------------------------------------------------------------------===//
//
// This file implements __divti3 for the compiler_rt library.
//
//===----------------------------------------------------------------------===//


#ifdef CRT_HAS_128BIT

// Returns: a / b

#define fixint_t ti_int
#define fixuint_t tu_int
#define COMPUTE_UDIV(a, b) __udivmodti4((a), (b), (tu_int *)0)
//===-- int_div_impl.inc - Integer division ---------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
// 2024/10/20 - Modified by Mintsuki for use inside freestanding-lgrt
//
//===----------------------------------------------------------------------===//
//
// Helpers used by __udivsi3, __umodsi3, __udivdi3, and __umodsi3.
//
//===----------------------------------------------------------------------===//

#define clz(a) (sizeof(a) == sizeof(unsigned long long) ? __builtin_clzll(a) : clzsi(a))

#undef __udivXi3
#define __udivXi3 __udivXi3_9

// Adapted from Figure 3-40 of The PowerPC Compiler Writer's Guide
static __inline fixuint_t __udivXi3(fixuint_t n, fixuint_t d) {
  const unsigned N = sizeof(fixuint_t) * CHAR_BIT;
  // d == 0 cases are unspecified.
  unsigned sr = (d ? clz(d) : N) - (n ? clz(n) : N);
  // 0 <= sr <= N - 1 or sr is very large.
  if (sr > N - 1) // n < d
    return 0;
  if (sr == N - 1) // d == 1
    return n;
  ++sr;
  // 1 <= sr <= N - 1. Shifts do not trigger UB.
  fixuint_t r = n >> sr;
  n <<= N - sr;
  fixuint_t carry = 0;
  for (; sr > 0; --sr) {
    r = (r << 1) | (n >> (N - 1));
    n = (n << 1) | carry;
    // Branch-less version of:
    // carry = 0;
    // if (r >= d) r -= d, carry = 1;
    const fixint_t s = (fixint_t)(d - r - 1) >> (N - 1);
    carry = s & 1;
    r -= d & s;
  }
  n = (n << 1) | carry;
  return n;
}

#undef __umodXi3
#define __umodXi3 __umodXi3_10

// Mostly identical to __udivXi3 but the return values are different.
static __inline fixuint_t __umodXi3(fixuint_t n, fixuint_t d) {
  const unsigned N = sizeof(fixuint_t) * CHAR_BIT;
  // d == 0 cases are unspecified.
  unsigned sr = (d ? clz(d) : N) - (n ? clz(n) : N);
  // 0 <= sr <= N - 1 or sr is very large.
  if (sr > N - 1) // n < d
    return n;
  if (sr == N - 1) // d == 1
    return 0;
  ++sr;
  // 1 <= sr <= N - 1. Shifts do not trigger UB.
  fixuint_t r = n >> sr;
  n <<= N - sr;
  fixuint_t carry = 0;
  for (; sr > 0; --sr) {
    r = (r << 1) | (n >> (N - 1));
    n = (n << 1) | carry;
    // Branch-less version of:
    // carry = 0;
    // if (r >= d) r -= d, carry = 1;
    const fixint_t s = (fixint_t)(d - r - 1) >> (N - 1);
    carry = s & 1;
    r -= d & s;
  }
  return r;
}

#undef __divXi3

#ifdef COMPUTE_UDIV

#define __divXi3 __divXi3_11

static __inline fixint_t __divXi3(fixint_t a, fixint_t b) {
  const int N = (int)(sizeof(fixint_t) * CHAR_BIT) - 1;
  fixint_t s_a = a >> N;                            // s_a = a < 0 ? -1 : 0
  fixint_t s_b = b >> N;                            // s_b = b < 0 ? -1 : 0
  fixuint_t a_u = (fixuint_t)(a ^ s_a) + (-s_a);    // negate if s_a == -1
  fixuint_t b_u = (fixuint_t)(b ^ s_b) + (-s_b);    // negate if s_b == -1
  s_a ^= s_b;                                       // sign of quotient
  return (COMPUTE_UDIV(a_u, b_u) ^ s_a) + (-s_a);   // negate if s_a == -1
}
#endif // COMPUTE_UDIV

#undef __modXi3

#ifdef ASSIGN_UMOD

#define __modXi3 __modXi3_12

static __inline fixint_t __modXi3(fixint_t a, fixint_t b) {
  const int N = (int)(sizeof(fixint_t) * CHAR_BIT) - 1;
  fixint_t s = b >> N;                              // s = b < 0 ? -1 : 0
  fixuint_t b_u = (fixuint_t)(b ^ s) + (-s);        // negate if s == -1
  s = a >> N;                                       // s = a < 0 ? -1 : 0
  fixuint_t a_u = (fixuint_t)(a ^ s) + (-s);        // negate if s == -1
  fixuint_t res;
  ASSIGN_UMOD(res, a_u, b_u);
  return (res ^ s) + (-s);                          // negate if s == -1
}
#endif // ASSIGN_UMOD

#undef clz

COMPILER_RT_ABI ti_int __divti3(ti_int a, ti_int b) { return __divXi3(a, b); }

#undef fixint_t
#undef fixuint_t
#undef COMPUTE_UDIV

#endif // CRT_HAS_128BIT
//===-- ffsdi2.c - Implement __ffsdi2 -------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements __ffsdi2 for the compiler_rt library.
//
//===----------------------------------------------------------------------===//


// Returns: the index of the least significant 1-bit in a, or
// the value zero if a is zero. The least significant bit is index one.

COMPILER_RT_ABI int __ffsdi2(di_int a) {
  dwords x;
  x.all = a;
  if (x.s.low == 0) {
    if (x.s.high == 0)
      return 0;
    return ctzsi(x.s.high) + (1 + sizeof(si_int) * CHAR_BIT);
  }
  return ctzsi(x.s.low) + 1;
}
//===-- ffssi2.c - Implement __ffssi2 -------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements __ffssi2 for the compiler_rt library.
//
//===----------------------------------------------------------------------===//


// Returns: the index of the least significant 1-bit in a, or
// the value zero if a is zero. The least significant bit is index one.

COMPILER_RT_ABI int __ffssi2(si_int a) {
  if (a == 0) {
    return 0;
  }
  return ctzsi(a) + 1;
}
//===-- ffsti2.c - Implement __ffsti2 -------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements __ffsti2 for the compiler_rt library.
//
//===----------------------------------------------------------------------===//


#ifdef CRT_HAS_128BIT

// Returns: the index of the least significant 1-bit in a, or
// the value zero if a is zero. The least significant bit is index one.

COMPILER_RT_ABI int __ffsti2(ti_int a) {
  twords x;
  x.all = a;
  if (x.s.low == 0) {
    if (x.s.high == 0)
      return 0;
    return __builtin_ctzll(x.s.high) + (1 + sizeof(di_int) * CHAR_BIT);
  }
  return __builtin_ctzll(x.s.low) + 1;
}

#endif // CRT_HAS_128BIT
//===-- int_util.c - Implement internal utilities -------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
// 2024/01/21 - Modified by Mintsuki for use inside freestanding-lgrt
//
//===----------------------------------------------------------------------===//


// NOTE: The definitions in this file are declared weak because we clients to be
// able to arbitrarily package individual functions into separate .a files. If
// we did not declare these weak, some link situations might end up seeing
// duplicate strong definitions of the same symbol.
//
// We can't use this solution for kernel use (which may not support weak), but
// currently expect that when built for kernel use all the functionality is
// packaged into a single library.

__attribute__((weak))
__attribute__((visibility("hidden")))
void __compilerrt_abort_impl(const char *file, int line, const char *function) {
  (void)file; (void)line; (void)function;
#if !__STDC_HOSTED__
  // Avoid depending on libc when compiling with -ffreestanding.
  __builtin_trap();
#else
  __builtin_abort();
#endif
}
//===-- lshrdi3.c - Implement __lshrdi3 -----------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements __lshrdi3 for the compiler_rt library.
//
//===----------------------------------------------------------------------===//


// Returns: logical a >> b

// Precondition:  0 <= b < bits_in_dword

COMPILER_RT_ABI di_int __lshrdi3(di_int a, int b) {
  const int bits_in_word = (int)(sizeof(si_int) * CHAR_BIT);
  udwords input;
  udwords result;
  input.all = a;
  if (b & bits_in_word) /* bits_in_word <= b < bits_in_dword */ {
    result.s.high = 0;
    result.s.low = input.s.high >> (b - bits_in_word);
  } else /* 0 <= b < bits_in_word */ {
    if (b == 0)
      return a;
    result.s.high = input.s.high >> b;
    result.s.low = (input.s.high << (bits_in_word - b)) | (input.s.low >> b);
  }
  return result.all;
}

#if defined(__ARM_EABI__)
COMPILER_RT_ALIAS(__lshrdi3, __aeabi_llsr)
#endif
//===-- lshrti3.c - Implement __lshrti3 -----------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements __lshrti3 for the compiler_rt library.
//
//===----------------------------------------------------------------------===//


#ifdef CRT_HAS_128BIT

// Returns: logical a >> b

// Precondition:  0 <= b < bits_in_tword

COMPILER_RT_ABI ti_int __lshrti3(ti_int a, int b) {
  const int bits_in_dword = (int)(sizeof(di_int) * CHAR_BIT);
  utwords input;
  utwords result;
  input.all = a;
  if (b & bits_in_dword) /* bits_in_dword <= b < bits_in_tword */ {
    result.s.high = 0;
    result.s.low = input.s.high >> (b - bits_in_dword);
  } else /* 0 <= b < bits_in_dword */ {
    if (b == 0)
      return a;
    result.s.high = input.s.high >> b;
    result.s.low = (input.s.high << (bits_in_dword - b)) | (input.s.low >> b);
  }
  return result.all;
}

#endif // CRT_HAS_128BIT
//===-- moddi3.c - Implement __moddi3 -------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
// 2024/08/10 - Modified by Mintsuki for use inside freestanding-lgrt
//
//===----------------------------------------------------------------------===//
//
// This file implements __moddi3 for the compiler_rt library.
//
//===----------------------------------------------------------------------===//


// Returns: a % b

#define fixint_t di_int
#define fixuint_t du_int
#define ASSIGN_UMOD(res, a, b) __udivmoddi4((a), (b), &(res))
//===-- int_div_impl.inc - Integer division ---------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
// 2024/10/20 - Modified by Mintsuki for use inside freestanding-lgrt
//
//===----------------------------------------------------------------------===//
//
// Helpers used by __udivsi3, __umodsi3, __udivdi3, and __umodsi3.
//
//===----------------------------------------------------------------------===//

#define clz(a) (sizeof(a) == sizeof(unsigned long long) ? __builtin_clzll(a) : clzsi(a))

#undef __udivXi3
#define __udivXi3 __udivXi3_13

// Adapted from Figure 3-40 of The PowerPC Compiler Writer's Guide
static __inline fixuint_t __udivXi3(fixuint_t n, fixuint_t d) {
  const unsigned N = sizeof(fixuint_t) * CHAR_BIT;
  // d == 0 cases are unspecified.
  unsigned sr = (d ? clz(d) : N) - (n ? clz(n) : N);
  // 0 <= sr <= N - 1 or sr is very large.
  if (sr > N - 1) // n < d
    return 0;
  if (sr == N - 1) // d == 1
    return n;
  ++sr;
  // 1 <= sr <= N - 1. Shifts do not trigger UB.
  fixuint_t r = n >> sr;
  n <<= N - sr;
  fixuint_t carry = 0;
  for (; sr > 0; --sr) {
    r = (r << 1) | (n >> (N - 1));
    n = (n << 1) | carry;
    // Branch-less version of:
    // carry = 0;
    // if (r >= d) r -= d, carry = 1;
    const fixint_t s = (fixint_t)(d - r - 1) >> (N - 1);
    carry = s & 1;
    r -= d & s;
  }
  n = (n << 1) | carry;
  return n;
}

#undef __umodXi3
#define __umodXi3 __umodXi3_14

// Mostly identical to __udivXi3 but the return values are different.
static __inline fixuint_t __umodXi3(fixuint_t n, fixuint_t d) {
  const unsigned N = sizeof(fixuint_t) * CHAR_BIT;
  // d == 0 cases are unspecified.
  unsigned sr = (d ? clz(d) : N) - (n ? clz(n) : N);
  // 0 <= sr <= N - 1 or sr is very large.
  if (sr > N - 1) // n < d
    return n;
  if (sr == N - 1) // d == 1
    return 0;
  ++sr;
  // 1 <= sr <= N - 1. Shifts do not trigger UB.
  fixuint_t r = n >> sr;
  n <<= N - sr;
  fixuint_t carry = 0;
  for (; sr > 0; --sr) {
    r = (r << 1) | (n >> (N - 1));
    n = (n << 1) | carry;
    // Branch-less version of:
    // carry = 0;
    // if (r >= d) r -= d, carry = 1;
    const fixint_t s = (fixint_t)(d - r - 1) >> (N - 1);
    carry = s & 1;
    r -= d & s;
  }
  return r;
}

#undef __divXi3

#ifdef COMPUTE_UDIV

#define __divXi3 __divXi3_15

static __inline fixint_t __divXi3(fixint_t a, fixint_t b) {
  const int N = (int)(sizeof(fixint_t) * CHAR_BIT) - 1;
  fixint_t s_a = a >> N;                            // s_a = a < 0 ? -1 : 0
  fixint_t s_b = b >> N;                            // s_b = b < 0 ? -1 : 0
  fixuint_t a_u = (fixuint_t)(a ^ s_a) + (-s_a);    // negate if s_a == -1
  fixuint_t b_u = (fixuint_t)(b ^ s_b) + (-s_b);    // negate if s_b == -1
  s_a ^= s_b;                                       // sign of quotient
  return (COMPUTE_UDIV(a_u, b_u) ^ s_a) + (-s_a);   // negate if s_a == -1
}
#endif // COMPUTE_UDIV

#undef __modXi3

#ifdef ASSIGN_UMOD

#define __modXi3 __modXi3_16

static __inline fixint_t __modXi3(fixint_t a, fixint_t b) {
  const int N = (int)(sizeof(fixint_t) * CHAR_BIT) - 1;
  fixint_t s = b >> N;                              // s = b < 0 ? -1 : 0
  fixuint_t b_u = (fixuint_t)(b ^ s) + (-s);        // negate if s == -1
  s = a >> N;                                       // s = a < 0 ? -1 : 0
  fixuint_t a_u = (fixuint_t)(a ^ s) + (-s);        // negate if s == -1
  fixuint_t res;
  ASSIGN_UMOD(res, a_u, b_u);
  return (res ^ s) + (-s);                          // negate if s == -1
}
#endif // ASSIGN_UMOD

#undef clz

COMPILER_RT_ABI di_int __moddi3(di_int a, di_int b) { return __modXi3(a, b); }

#undef fixint_t
#undef fixuint_t
#undef ASSIGN_UMOD
//===-- modsi3.c - Implement __modsi3 -------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements __modsi3 for the compiler_rt library.
//
//===----------------------------------------------------------------------===//


// Returns: a % b

COMPILER_RT_ABI si_int __modsi3(si_int a, si_int b) {
  return a - __divsi3(a, b) * b;
}
//===-- modti3.c - Implement __modti3 -------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
// 2024/08/10 - Modified by Mintsuki for use inside freestanding-lgrt
//
//===----------------------------------------------------------------------===//
//
// This file implements __modti3 for the compiler_rt library.
//
//===----------------------------------------------------------------------===//


#ifdef CRT_HAS_128BIT

// Returns: a % b

#define fixint_t ti_int
#define fixuint_t tu_int
#define ASSIGN_UMOD(res, a, b) __udivmodti4((a), (b), &(res))
//===-- int_div_impl.inc - Integer division ---------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
// 2024/10/20 - Modified by Mintsuki for use inside freestanding-lgrt
//
//===----------------------------------------------------------------------===//
//
// Helpers used by __udivsi3, __umodsi3, __udivdi3, and __umodsi3.
//
//===----------------------------------------------------------------------===//

#define clz(a) (sizeof(a) == sizeof(unsigned long long) ? __builtin_clzll(a) : clzsi(a))

#undef __udivXi3
#define __udivXi3 __udivXi3_17

// Adapted from Figure 3-40 of The PowerPC Compiler Writer's Guide
static __inline fixuint_t __udivXi3(fixuint_t n, fixuint_t d) {
  const unsigned N = sizeof(fixuint_t) * CHAR_BIT;
  // d == 0 cases are unspecified.
  unsigned sr = (d ? clz(d) : N) - (n ? clz(n) : N);
  // 0 <= sr <= N - 1 or sr is very large.
  if (sr > N - 1) // n < d
    return 0;
  if (sr == N - 1) // d == 1
    return n;
  ++sr;
  // 1 <= sr <= N - 1. Shifts do not trigger UB.
  fixuint_t r = n >> sr;
  n <<= N - sr;
  fixuint_t carry = 0;
  for (; sr > 0; --sr) {
    r = (r << 1) | (n >> (N - 1));
    n = (n << 1) | carry;
    // Branch-less version of:
    // carry = 0;
    // if (r >= d) r -= d, carry = 1;
    const fixint_t s = (fixint_t)(d - r - 1) >> (N - 1);
    carry = s & 1;
    r -= d & s;
  }
  n = (n << 1) | carry;
  return n;
}

#undef __umodXi3
#define __umodXi3 __umodXi3_18

// Mostly identical to __udivXi3 but the return values are different.
static __inline fixuint_t __umodXi3(fixuint_t n, fixuint_t d) {
  const unsigned N = sizeof(fixuint_t) * CHAR_BIT;
  // d == 0 cases are unspecified.
  unsigned sr = (d ? clz(d) : N) - (n ? clz(n) : N);
  // 0 <= sr <= N - 1 or sr is very large.
  if (sr > N - 1) // n < d
    return n;
  if (sr == N - 1) // d == 1
    return 0;
  ++sr;
  // 1 <= sr <= N - 1. Shifts do not trigger UB.
  fixuint_t r = n >> sr;
  n <<= N - sr;
  fixuint_t carry = 0;
  for (; sr > 0; --sr) {
    r = (r << 1) | (n >> (N - 1));
    n = (n << 1) | carry;
    // Branch-less version of:
    // carry = 0;
    // if (r >= d) r -= d, carry = 1;
    const fixint_t s = (fixint_t)(d - r - 1) >> (N - 1);
    carry = s & 1;
    r -= d & s;
  }
  return r;
}

#undef __divXi3

#ifdef COMPUTE_UDIV

#define __divXi3 __divXi3_19

static __inline fixint_t __divXi3(fixint_t a, fixint_t b) {
  const int N = (int)(sizeof(fixint_t) * CHAR_BIT) - 1;
  fixint_t s_a = a >> N;                            // s_a = a < 0 ? -1 : 0
  fixint_t s_b = b >> N;                            // s_b = b < 0 ? -1 : 0
  fixuint_t a_u = (fixuint_t)(a ^ s_a) + (-s_a);    // negate if s_a == -1
  fixuint_t b_u = (fixuint_t)(b ^ s_b) + (-s_b);    // negate if s_b == -1
  s_a ^= s_b;                                       // sign of quotient
  return (COMPUTE_UDIV(a_u, b_u) ^ s_a) + (-s_a);   // negate if s_a == -1
}
#endif // COMPUTE_UDIV

#undef __modXi3

#ifdef ASSIGN_UMOD

#define __modXi3 __modXi3_20

static __inline fixint_t __modXi3(fixint_t a, fixint_t b) {
  const int N = (int)(sizeof(fixint_t) * CHAR_BIT) - 1;
  fixint_t s = b >> N;                              // s = b < 0 ? -1 : 0
  fixuint_t b_u = (fixuint_t)(b ^ s) + (-s);        // negate if s == -1
  s = a >> N;                                       // s = a < 0 ? -1 : 0
  fixuint_t a_u = (fixuint_t)(a ^ s) + (-s);        // negate if s == -1
  fixuint_t res;
  ASSIGN_UMOD(res, a_u, b_u);
  return (res ^ s) + (-s);                          // negate if s == -1
}
#endif // ASSIGN_UMOD

#undef clz

COMPILER_RT_ABI ti_int __modti3(ti_int a, ti_int b) { return __modXi3(a, b); }

#undef fixint_t
#undef fixuint_t
#undef ASSIGN_UMOD

#endif // CRT_HAS_128BIT
#if !((defined(__riscv) && __riscv_xlen == 64))
//===-- muldi3.c - Implement __muldi3 -------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements __muldi3 for the compiler_rt library.
//
//===----------------------------------------------------------------------===//


// Returns: a * b

static di_int __muldsi3(su_int a, su_int b) {
  dwords r;
  const int bits_in_word_2 = (int)(sizeof(si_int) * CHAR_BIT) / 2;
  const su_int lower_mask = (su_int)~0 >> bits_in_word_2;
  r.s.low = (a & lower_mask) * (b & lower_mask);
  su_int t = r.s.low >> bits_in_word_2;
  r.s.low &= lower_mask;
  t += (a >> bits_in_word_2) * (b & lower_mask);
  r.s.low += (t & lower_mask) << bits_in_word_2;
  r.s.high = t >> bits_in_word_2;
  t = r.s.low >> bits_in_word_2;
  r.s.low &= lower_mask;
  t += (b >> bits_in_word_2) * (a & lower_mask);
  r.s.low += (t & lower_mask) << bits_in_word_2;
  r.s.high += t >> bits_in_word_2;
  r.s.high += (a >> bits_in_word_2) * (b >> bits_in_word_2);
  return r.all;
}

// Returns: a * b

COMPILER_RT_ABI di_int __muldi3(di_int a, di_int b) {
  dwords x;
  x.all = a;
  dwords y;
  y.all = b;
  dwords r;
  r.all = __muldsi3(x.s.low, y.s.low);
  r.s.high += x.s.high * y.s.low + x.s.low * y.s.high;
  return r.all;
}

#if defined(__ARM_EABI__)
COMPILER_RT_ALIAS(__muldi3, __aeabi_lmul)
#endif
#endif
//===-- mulodi4.c - Implement __mulodi4 -----------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
// 2024/08/10 - Modified by Mintsuki for use inside freestanding-lgrt
//
//===----------------------------------------------------------------------===//
//
// This file implements __mulodi4 for the compiler_rt library.
//
//===----------------------------------------------------------------------===//

#define fixint_t di_int
#define fixuint_t du_int
//===-- int_mulo_impl.inc - Implement __mulo[sdt]i4 ---------------*- C -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
// 2024/10/20 - Modified by Mintsuki for use inside freestanding-lgrt
//
//===----------------------------------------------------------------------===//
//
// Helper used by __mulosi4, __mulodi4 and __muloti4.
//
//===----------------------------------------------------------------------===//


// Returns: a * b

// Effects: sets *overflow to 1  if a * b overflows

#undef __muloXi4
#define __muloXi4 __muloXi4_21

static __inline fixint_t __muloXi4(fixint_t a, fixint_t b, int *overflow) {
  const int N = (int)(sizeof(fixint_t) * CHAR_BIT);
  const fixint_t MIN = (fixint_t)((fixuint_t)1 << (N - 1));
  const fixint_t MAX = ~MIN;
  *overflow = 0;
  fixint_t result = (fixuint_t)a * b;
  if (a == MIN) {
    if (b != 0 && b != 1)
      *overflow = 1;
    return result;
  }
  if (b == MIN) {
    if (a != 0 && a != 1)
      *overflow = 1;
    return result;
  }
  fixint_t sa = a >> (N - 1);
  fixint_t abs_a = (a ^ sa) - sa;
  fixint_t sb = b >> (N - 1);
  fixint_t abs_b = (b ^ sb) - sb;
  if (abs_a < 2 || abs_b < 2)
    return result;
  if (sa == sb) {
    if (abs_a > MAX / abs_b)
      *overflow = 1;
  } else {
    if (abs_a > MIN / -abs_b)
      *overflow = 1;
  }
  return result;
}

// Returns: a * b

// Effects: sets *overflow to 1  if a * b overflows

COMPILER_RT_ABI di_int __mulodi4(di_int a, di_int b, int *overflow) {
  return __muloXi4(a, b, overflow);
}

#undef fixint_t
#undef fixuint_t
//===-- mulosi4.c - Implement __mulosi4 -----------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
// 2024/08/10 - Modified by Mintsuki for use inside freestanding-lgrt
//
//===----------------------------------------------------------------------===//
//
// This file implements __mulosi4 for the compiler_rt library.
//
//===----------------------------------------------------------------------===//

#define fixint_t si_int
#define fixuint_t su_int
//===-- int_mulo_impl.inc - Implement __mulo[sdt]i4 ---------------*- C -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
// 2024/10/20 - Modified by Mintsuki for use inside freestanding-lgrt
//
//===----------------------------------------------------------------------===//
//
// Helper used by __mulosi4, __mulodi4 and __muloti4.
//
//===----------------------------------------------------------------------===//


// Returns: a * b

// Effects: sets *overflow to 1  if a * b overflows

#undef __muloXi4
#define __muloXi4 __muloXi4_22

static __inline fixint_t __muloXi4(fixint_t a, fixint_t b, int *overflow) {
  const int N = (int)(sizeof(fixint_t) * CHAR_BIT);
  const fixint_t MIN = (fixint_t)((fixuint_t)1 << (N - 1));
  const fixint_t MAX = ~MIN;
  *overflow = 0;
  fixint_t result = (fixuint_t)a * b;
  if (a == MIN) {
    if (b != 0 && b != 1)
      *overflow = 1;
    return result;
  }
  if (b == MIN) {
    if (a != 0 && a != 1)
      *overflow = 1;
    return result;
  }
  fixint_t sa = a >> (N - 1);
  fixint_t abs_a = (a ^ sa) - sa;
  fixint_t sb = b >> (N - 1);
  fixint_t abs_b = (b ^ sb) - sb;
  if (abs_a < 2 || abs_b < 2)
    return result;
  if (sa == sb) {
    if (abs_a > MAX / abs_b)
      *overflow = 1;
  } else {
    if (abs_a > MIN / -abs_b)
      *overflow = 1;
  }
  return result;
}

// Returns: a * b

// Effects: sets *overflow to 1  if a * b overflows

COMPILER_RT_ABI si_int __mulosi4(si_int a, si_int b, int *overflow) {
  return __muloXi4(a, b, overflow);
}

#undef fixint_t
#undef fixuint_t
//===-- muloti4.c - Implement __muloti4 -----------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
// 2024/08/10 - Modified by Mintsuki for use inside freestanding-lgrt
//
//===----------------------------------------------------------------------===//
//
// This file implements __muloti4 for the compiler_rt library.
//
//===----------------------------------------------------------------------===//


#ifdef CRT_HAS_128BIT

// Returns: a * b

// Effects: sets *overflow to 1  if a * b overflows

#define fixint_t ti_int
#define fixuint_t tu_int
//===-- int_mulo_impl.inc - Implement __mulo[sdt]i4 ---------------*- C -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
// 2024/10/20 - Modified by Mintsuki for use inside freestanding-lgrt
//
//===----------------------------------------------------------------------===//
//
// Helper used by __mulosi4, __mulodi4 and __muloti4.
//
//===----------------------------------------------------------------------===//


// Returns: a * b

// Effects: sets *overflow to 1  if a * b overflows

#undef __muloXi4
#define __muloXi4 __muloXi4_23

static __inline fixint_t __muloXi4(fixint_t a, fixint_t b, int *overflow) {
  const int N = (int)(sizeof(fixint_t) * CHAR_BIT);
  const fixint_t MIN = (fixint_t)((fixuint_t)1 << (N - 1));
  const fixint_t MAX = ~MIN;
  *overflow = 0;
  fixint_t result = (fixuint_t)a * b;
  if (a == MIN) {
    if (b != 0 && b != 1)
      *overflow = 1;
    return result;
  }
  if (b == MIN) {
    if (a != 0 && a != 1)
      *overflow = 1;
    return result;
  }
  fixint_t sa = a >> (N - 1);
  fixint_t abs_a = (a ^ sa) - sa;
  fixint_t sb = b >> (N - 1);
  fixint_t abs_b = (b ^ sb) - sb;
  if (abs_a < 2 || abs_b < 2)
    return result;
  if (sa == sb) {
    if (abs_a > MAX / abs_b)
      *overflow = 1;
  } else {
    if (abs_a > MIN / -abs_b)
      *overflow = 1;
  }
  return result;
}

COMPILER_RT_ABI ti_int __muloti4(ti_int a, ti_int b, int *overflow) {
  return __muloXi4(a, b, overflow);
}

#undef fixint_t
#undef fixuint_t

#endif // CRT_HAS_128BIT
//===-- multi3.c - Implement __multi3 -------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements __multi3 for the compiler_rt library.
//
//===----------------------------------------------------------------------===//


#ifdef CRT_HAS_128BIT

// Returns: a * b

static ti_int __mulddi3(du_int a, du_int b) {
  twords r;
  const int bits_in_dword_2 = (int)(sizeof(di_int) * CHAR_BIT) / 2;
  const du_int lower_mask = (du_int)~0 >> bits_in_dword_2;
  r.s.low = (a & lower_mask) * (b & lower_mask);
  du_int t = r.s.low >> bits_in_dword_2;
  r.s.low &= lower_mask;
  t += (a >> bits_in_dword_2) * (b & lower_mask);
  r.s.low += (t & lower_mask) << bits_in_dword_2;
  r.s.high = t >> bits_in_dword_2;
  t = r.s.low >> bits_in_dword_2;
  r.s.low &= lower_mask;
  t += (b >> bits_in_dword_2) * (a & lower_mask);
  r.s.low += (t & lower_mask) << bits_in_dword_2;
  r.s.high += t >> bits_in_dword_2;
  r.s.high += (a >> bits_in_dword_2) * (b >> bits_in_dword_2);
  return r.all;
}

// Returns: a * b

COMPILER_RT_ABI ti_int __multi3(ti_int a, ti_int b) {
  twords x;
  x.all = a;
  twords y;
  y.all = b;
  twords r;
  r.all = __mulddi3(x.s.low, y.s.low);
  r.s.high += x.s.high * y.s.low + x.s.low * y.s.high;
  return r.all;
}

#endif // CRT_HAS_128BIT
//===-- mulvdi3.c - Implement __mulvdi3 -----------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
// 2024/08/10 - Modified by Mintsuki for use inside freestanding-lgrt
//
//===----------------------------------------------------------------------===//
//
// This file implements __mulvdi3 for the compiler_rt library.
//
//===----------------------------------------------------------------------===//

#define fixint_t di_int
#define fixuint_t du_int
//===-- int_mulv_impl.inc - Implement __mulv[sdt]i3 ---------------*- C -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
// 2024/10/20 - Modified by Mintsuki for use inside freestanding-lgrt
//
//===----------------------------------------------------------------------===//
//
// Helper used by __mulvsi3, __mulvdi3 and __mulvti3.
//
//===----------------------------------------------------------------------===//


// Returns: a * b

// Effects: aborts if a * b overflows

#undef __mulvXi3
#define __mulvXi3 __mulvXi3_24

static __inline fixint_t __mulvXi3(fixint_t a, fixint_t b) {
  const int N = (int)(sizeof(fixint_t) * CHAR_BIT);
  const fixint_t MIN = (fixint_t)((fixuint_t)1 << (N - 1));
  const fixint_t MAX = ~MIN;
  if (a == MIN) {
    if (b == 0 || b == 1)
      return a * b;
    compilerrt_abort();
  }
  if (b == MIN) {
    if (a == 0 || a == 1)
      return a * b;
    compilerrt_abort();
  }
  fixint_t sa = a >> (N - 1);
  fixint_t abs_a = (a ^ sa) - sa;
  fixint_t sb = b >> (N - 1);
  fixint_t abs_b = (b ^ sb) - sb;
  if (abs_a < 2 || abs_b < 2)
    return a * b;
  if (sa == sb) {
    if (abs_a > MAX / abs_b)
      compilerrt_abort();
  } else {
    if (abs_a > MIN / -abs_b)
      compilerrt_abort();
  }
  return a * b;
}

// Returns: a * b

// Effects: aborts if a * b overflows

COMPILER_RT_ABI di_int __mulvdi3(di_int a, di_int b) { return __mulvXi3(a, b); }

#undef fixint_t
#undef fixuint_t
//===-- mulvsi3.c - Implement __mulvsi3 -----------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
// 2024/08/10 - Modified by Mintsuki for use inside freestanding-lgrt
//
//===----------------------------------------------------------------------===//
//
// This file implements __mulvsi3 for the compiler_rt library.
//
//===----------------------------------------------------------------------===//

#define fixint_t si_int
#define fixuint_t su_int
//===-- int_mulv_impl.inc - Implement __mulv[sdt]i3 ---------------*- C -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
// 2024/10/20 - Modified by Mintsuki for use inside freestanding-lgrt
//
//===----------------------------------------------------------------------===//
//
// Helper used by __mulvsi3, __mulvdi3 and __mulvti3.
//
//===----------------------------------------------------------------------===//


// Returns: a * b

// Effects: aborts if a * b overflows

#undef __mulvXi3
#define __mulvXi3 __mulvXi3_25

static __inline fixint_t __mulvXi3(fixint_t a, fixint_t b) {
  const int N = (int)(sizeof(fixint_t) * CHAR_BIT);
  const fixint_t MIN = (fixint_t)((fixuint_t)1 << (N - 1));
  const fixint_t MAX = ~MIN;
  if (a == MIN) {
    if (b == 0 || b == 1)
      return a * b;
    compilerrt_abort();
  }
  if (b == MIN) {
    if (a == 0 || a == 1)
      return a * b;
    compilerrt_abort();
  }
  fixint_t sa = a >> (N - 1);
  fixint_t abs_a = (a ^ sa) - sa;
  fixint_t sb = b >> (N - 1);
  fixint_t abs_b = (b ^ sb) - sb;
  if (abs_a < 2 || abs_b < 2)
    return a * b;
  if (sa == sb) {
    if (abs_a > MAX / abs_b)
      compilerrt_abort();
  } else {
    if (abs_a > MIN / -abs_b)
      compilerrt_abort();
  }
  return a * b;
}

// Returns: a * b

// Effects: aborts if a * b overflows

COMPILER_RT_ABI si_int __mulvsi3(si_int a, si_int b) { return __mulvXi3(a, b); }

#undef fixint_t
#undef fixuint_t
//===-- mulvti3.c - Implement __mulvti3 -----------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
// 2024/08/10 - Modified by Mintsuki for use inside freestanding-lgrt
//
//===----------------------------------------------------------------------===//
//
// This file implements __mulvti3 for the compiler_rt library.
//
//===----------------------------------------------------------------------===//


#ifdef CRT_HAS_128BIT

// Returns: a * b

// Effects: aborts if a * b overflows

#define fixint_t ti_int
#define fixuint_t tu_int
//===-- int_mulv_impl.inc - Implement __mulv[sdt]i3 ---------------*- C -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
// 2024/10/20 - Modified by Mintsuki for use inside freestanding-lgrt
//
//===----------------------------------------------------------------------===//
//
// Helper used by __mulvsi3, __mulvdi3 and __mulvti3.
//
//===----------------------------------------------------------------------===//


// Returns: a * b

// Effects: aborts if a * b overflows

#undef __mulvXi3
#define __mulvXi3 __mulvXi3_26

static __inline fixint_t __mulvXi3(fixint_t a, fixint_t b) {
  const int N = (int)(sizeof(fixint_t) * CHAR_BIT);
  const fixint_t MIN = (fixint_t)((fixuint_t)1 << (N - 1));
  const fixint_t MAX = ~MIN;
  if (a == MIN) {
    if (b == 0 || b == 1)
      return a * b;
    compilerrt_abort();
  }
  if (b == MIN) {
    if (a == 0 || a == 1)
      return a * b;
    compilerrt_abort();
  }
  fixint_t sa = a >> (N - 1);
  fixint_t abs_a = (a ^ sa) - sa;
  fixint_t sb = b >> (N - 1);
  fixint_t abs_b = (b ^ sb) - sb;
  if (abs_a < 2 || abs_b < 2)
    return a * b;
  if (sa == sb) {
    if (abs_a > MAX / abs_b)
      compilerrt_abort();
  } else {
    if (abs_a > MIN / -abs_b)
      compilerrt_abort();
  }
  return a * b;
}

COMPILER_RT_ABI ti_int __mulvti3(ti_int a, ti_int b) { return __mulvXi3(a, b); }

#undef fixint_t
#undef fixuint_t

#endif // CRT_HAS_128BIT
//===-- negdi2.c - Implement __negdi2 -------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements __negdi2 for the compiler_rt library.
//
//===----------------------------------------------------------------------===//


// Returns: -a

COMPILER_RT_ABI di_int __negdi2(di_int a) {
  // Note: this routine is here for API compatibility; any sane compiler
  // should expand it inline.
  return -(du_int)a;
}
//===-- negti2.c - Implement __negti2 -------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements __negti2 for the compiler_rt library.
//
//===----------------------------------------------------------------------===//


#ifdef CRT_HAS_128BIT

// Returns: -a

COMPILER_RT_ABI ti_int __negti2(ti_int a) {
  // Note: this routine is here for API compatibility; any sane compiler
  // should expand it inline.
  return -(tu_int)a;
}

#endif // CRT_HAS_128BIT
//===-- negvdi2.c - Implement __negvdi2 -----------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements __negvdi2 for the compiler_rt library.
//
//===----------------------------------------------------------------------===//


// Returns: -a

// Effects: aborts if -a overflows

COMPILER_RT_ABI di_int __negvdi2(di_int a) {
  const di_int MIN =
      (di_int)((du_int)1 << ((int)(sizeof(di_int) * CHAR_BIT) - 1));
  if (a == MIN)
    compilerrt_abort();
  return -a;
}
//===-- negvsi2.c - Implement __negvsi2 -----------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements __negvsi2 for the compiler_rt library.
//
//===----------------------------------------------------------------------===//


// Returns: -a

// Effects: aborts if -a overflows

COMPILER_RT_ABI si_int __negvsi2(si_int a) {
  const si_int MIN =
      (si_int)((su_int)1 << ((int)(sizeof(si_int) * CHAR_BIT) - 1));
  if (a == MIN)
    compilerrt_abort();
  return -a;
}
//===-- negvti2.c - Implement __negvti2 -----------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements __negvti2 for the compiler_rt library.
//
//===----------------------------------------------------------------------===//


#ifdef CRT_HAS_128BIT

// Returns: -a

// Effects: aborts if -a overflows

COMPILER_RT_ABI ti_int __negvti2(ti_int a) {
  const ti_int MIN = (tu_int)1 << ((int)(sizeof(ti_int) * CHAR_BIT) - 1);
  if (a == MIN)
    compilerrt_abort();
  return -a;
}

#endif // CRT_HAS_128BIT
//===-- paritydi2.c - Implement __paritydi2 -------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements __paritydi2 for the compiler_rt library.
//
//===----------------------------------------------------------------------===//


// Returns: 1 if number of bits is odd else returns 0

COMPILER_RT_ABI int __paritydi2(di_int a) {
  dwords x;
  x.all = a;
  su_int x2 = x.s.high ^ x.s.low;
  x2 ^= x2 >> 16;
  x2 ^= x2 >> 8;
  x2 ^= x2 >> 4;
  return (0x6996 >> (x2 & 0xF)) & 1;
}
//===-- paritysi2.c - Implement __paritysi2 -------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements __paritysi2 for the compiler_rt library.
//
//===----------------------------------------------------------------------===//


// Returns: 1 if number of bits is odd else returns 0

COMPILER_RT_ABI int __paritysi2(si_int a) {
  su_int x = (su_int)a;
  x ^= x >> 16;
  x ^= x >> 8;
  x ^= x >> 4;
  return (0x6996 >> (x & 0xF)) & 1;
}
//===-- parityti2.c - Implement __parityti2 -------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements __parityti2 for the compiler_rt library.
//
//===----------------------------------------------------------------------===//


#ifdef CRT_HAS_128BIT

// Returns: 1 if number of bits is odd else returns 0

COMPILER_RT_ABI int __parityti2(ti_int a) {
  twords x;
  dwords x2;
  x.all = a;
  x2.all = x.s.high ^ x.s.low;
  su_int x3 = x2.s.high ^ x2.s.low;
  x3 ^= x3 >> 16;
  x3 ^= x3 >> 8;
  x3 ^= x3 >> 4;
  return (0x6996 >> (x3 & 0xF)) & 1;
}

#endif // CRT_HAS_128BIT
//===-- popcountdi2.c - Implement __popcountdi2 ---------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements __popcountdi2 for the compiler_rt library.
//
//===----------------------------------------------------------------------===//


// Returns: count of 1 bits

COMPILER_RT_ABI int __popcountdi2(di_int a) {
  du_int x2 = (du_int)a;
  x2 = x2 - ((x2 >> 1) & 0x5555555555555555uLL);
  // Every 2 bits holds the sum of every pair of bits (32)
  x2 = ((x2 >> 2) & 0x3333333333333333uLL) + (x2 & 0x3333333333333333uLL);
  // Every 4 bits holds the sum of every 4-set of bits (3 significant bits) (16)
  x2 = (x2 + (x2 >> 4)) & 0x0F0F0F0F0F0F0F0FuLL;
  // Every 8 bits holds the sum of every 8-set of bits (4 significant bits) (8)
  su_int x = (su_int)(x2 + (x2 >> 32));
  // The lower 32 bits hold four 16 bit sums (5 significant bits).
  //   Upper 32 bits are garbage
  x = x + (x >> 16);
  // The lower 16 bits hold two 32 bit sums (6 significant bits).
  //   Upper 16 bits are garbage
  return (x + (x >> 8)) & 0x0000007F; // (7 significant bits)
}
//===-- popcountsi2.c - Implement __popcountsi2 ---------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements __popcountsi2 for the compiler_rt library.
//
//===----------------------------------------------------------------------===//


// Returns: count of 1 bits

COMPILER_RT_ABI int __popcountsi2(si_int a) {
  su_int x = (su_int)a;
  x = x - ((x >> 1) & 0x55555555);
  // Every 2 bits holds the sum of every pair of bits
  x = ((x >> 2) & 0x33333333) + (x & 0x33333333);
  // Every 4 bits holds the sum of every 4-set of bits (3 significant bits)
  x = (x + (x >> 4)) & 0x0F0F0F0F;
  // Every 8 bits holds the sum of every 8-set of bits (4 significant bits)
  x = (x + (x >> 16));
  // The lower 16 bits hold two 8 bit sums (5 significant bits).
  //    Upper 16 bits are garbage
  return (x + (x >> 8)) & 0x0000003F; // (6 significant bits)
}
//===-- popcountti2.c - Implement __popcountti2
//----------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements __popcountti2 for the compiler_rt library.
//
//===----------------------------------------------------------------------===//


#ifdef CRT_HAS_128BIT

// Returns: count of 1 bits

COMPILER_RT_ABI int __popcountti2(ti_int a) {
  tu_int x3 = (tu_int)a;
  x3 = x3 - ((x3 >> 1) &
             (((tu_int)0x5555555555555555uLL << 64) | 0x5555555555555555uLL));
  // Every 2 bits holds the sum of every pair of bits (64)
  x3 = ((x3 >> 2) &
        (((tu_int)0x3333333333333333uLL << 64) | 0x3333333333333333uLL)) +
       (x3 & (((tu_int)0x3333333333333333uLL << 64) | 0x3333333333333333uLL));
  // Every 4 bits holds the sum of every 4-set of bits (3 significant bits) (32)
  x3 = (x3 + (x3 >> 4)) &
       (((tu_int)0x0F0F0F0F0F0F0F0FuLL << 64) | 0x0F0F0F0F0F0F0F0FuLL);
  // Every 8 bits holds the sum of every 8-set of bits (4 significant bits) (16)
  du_int x2 = (du_int)(x3 + (x3 >> 64));
  // Every 8 bits holds the sum of every 8-set of bits (5 significant bits) (8)
  su_int x = (su_int)(x2 + (x2 >> 32));
  // Every 8 bits holds the sum of every 8-set of bits (6 significant bits) (4)
  x = x + (x >> 16);
  // Every 8 bits holds the sum of every 8-set of bits (7 significant bits) (2)
  //
  // Upper 16 bits are garbage
  return (x + (x >> 8)) & 0xFF; // (8 significant bits)
}

#endif // CRT_HAS_128BIT
//===-- stdc_bit_ceil_uc.c ------------------------------------------------===//
//
// Part of freestanding-lgrt, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements stdc_bit_ceil_uc from C23's stdbit.h.
//
//===----------------------------------------------------------------------===//

unsigned char stdc_bit_ceil_uc(unsigned char value) {
  // The width of the type that __builtin_clz counts the leading zeros of.
  const int bits = (int)sizeof(unsigned int) * __CHAR_BIT__;
  if (value <= 1)
    return 1;
  // 2 to the bit width of value - 1, where the type has a bit for it.
  int exponent = bits - __builtin_clz((unsigned int)value - 1);
  if (exponent >= (int)sizeof(value) * __CHAR_BIT__)
    return 0;
  return (unsigned char)(1u << exponent);
}
//===-- stdc_bit_ceil_ui.c ------------------------------------------------===//
//
// Part of freestanding-lgrt, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements stdc_bit_ceil_ui from C23's stdbit.h.
//
//===----------------------------------------------------------------------===//

unsigned int stdc_bit_ceil_ui(unsigned int value) {
  // The width of the type that __builtin_clz counts the leading zeros of.
  const int bits = (int)sizeof(unsigned int) * __CHAR_BIT__;
  if (value <= 1)
    return 1;
  // 2 to the bit width of value - 1, where the type has a bit for it.
  int exponent = bits - __builtin_clz(value - 1);
  if (exponent >= (int)sizeof(value) * __CHAR_BIT__)
    return 0;
  return 1u << exponent;
}
//===-- stdc_bit_ceil_ul.c ------------------------------------------------===//
//
// Part of freestanding-lgrt, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements stdc_bit_ceil_ul from C23's stdbit.h.
//
//===----------------------------------------------------------------------===//

unsigned long stdc_bit_ceil_ul(unsigned long value) {
  // The width of the type that __builtin_clzl counts the leading zeros of.
  const int bits = (int)sizeof(unsigned long) * __CHAR_BIT__;
  if (value <= 1)
    return 1;
  // 2 to the bit width of value - 1, where the type has a bit for it.
  int exponent = bits - __builtin_clzl(value - 1);
  if (exponent >= (int)sizeof(value) * __CHAR_BIT__)
    return 0;
  return 1ul << exponent;
}
//===-- stdc_bit_ceil_ull.c -----------------------------------------------===//
//
// Part of freestanding-lgrt, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements stdc_bit_ceil_ull from C23's stdbit.h.
//
//===----------------------------------------------------------------------===//

unsigned long long stdc_bit_ceil_ull(unsigned long long value) {
  // The width of the type that __builtin_clzll counts the leading zeros of.
  const int bits = (int)sizeof(unsigned long long) * __CHAR_BIT__;
  if (value <= 1)
    return 1;
  // 2 to the bit width of value - 1, where the type has a bit for it.
  int exponent = bits - __builtin_clzll(value - 1);
  if (exponent >= (int)sizeof(value) * __CHAR_BIT__)
    return 0;
  return 1ull << exponent;
}
//===-- stdc_bit_ceil_us.c ------------------------------------------------===//
//
// Part of freestanding-lgrt, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements stdc_bit_ceil_us from C23's stdbit.h.
//
//===----------------------------------------------------------------------===//

unsigned short stdc_bit_ceil_us(unsigned short value) {
  // The width of the type that __builtin_clz counts the leading zeros of.
  const int bits = (int)sizeof(unsigned int) * __CHAR_BIT__;
  if (value <= 1)
    return 1;
  // 2 to the bit width of value - 1, where the type has a bit for it.
  int exponent = bits - __builtin_clz((unsigned int)value - 1);
  if (exponent >= (int)sizeof(value) * __CHAR_BIT__)
    return 0;
  return (unsigned short)(1u << exponent);
}
//===-- stdc_bit_floor_uc.c -----------------------------------------------===//
//
// Part of freestanding-lgrt, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements stdc_bit_floor_uc from C23's stdbit.h.
//
//===----------------------------------------------------------------------===//

unsigned char stdc_bit_floor_uc(unsigned char value) {
  // The width of the type that __builtin_clz counts the leading zeros of.
  const int bits = (int)sizeof(unsigned int) * __CHAR_BIT__;
  if (value == 0)
    return 0;
  // 2 to the index of the most significant one of value.
  return (unsigned char)(1u << (bits - 1 - __builtin_clz(value)));
}
//===-- stdc_bit_floor_ui.c -----------------------------------------------===//
//
// Part of freestanding-lgrt, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements stdc_bit_floor_ui from C23's stdbit.h.
//
//===----------------------------------------------------------------------===//

unsigned int stdc_bit_floor_ui(unsigned int value) {
  // The width of the type that __builtin_clz counts the leading zeros of.
  const int bits = (int)sizeof(unsigned int) * __CHAR_BIT__;
  if (value == 0)
    return 0;
  // 2 to the index of the most significant one of value.
  return 1u << (bits - 1 - __builtin_clz(value));
}
//===-- stdc_bit_floor_ul.c -----------------------------------------------===//
//
// Part of freestanding-lgrt, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements stdc_bit_floor_ul from C23's stdbit.h.
//
//===----------------------------------------------------------------------===//

unsigned long stdc_bit_floor_ul(unsigned long value) {
  // The width of the type that __builtin_clzl counts the leading zeros of.
  const int bits = (int)sizeof(unsigned long) * __CHAR_BIT__;
  if (value == 0)
    return 0;
  // 2 to the index of the most significant one of value.
  return 1ul << (bits - 1 - __builtin_clzl(value));
}
//===-- stdc_bit_floor_ull.c ----------------------------------------------===//
//
// Part of freestanding-lgrt, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements stdc_bit_floor_ull from C23's stdbit.h.
//
//===----------------------------------------------------------------------===//

unsigned long long stdc_bit_floor_ull(unsigned long long value) {
  // The width of the type that __builtin_clzll counts the leading zeros of.
  const int bits = (int)sizeof(unsigned long long) * __CHAR_BIT__;
  if (value == 0)
    return 0;
  // 2 to the index of the most significant one of value.
  return 1ull << (bits - 1 - __builtin_clzll(value));
}
//===-- stdc_bit_floor_us.c -----------------------------------------------===//
//
// Part of freestanding-lgrt, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements stdc_bit_floor_us from C23's stdbit.h.
//
//===----------------------------------------------------------------------===//

unsigned short stdc_bit_floor_us(unsigned short value) {
  // The width of the type that __builtin_clz counts the leading zeros of.
  const int bits = (int)sizeof(unsigned int) * __CHAR_BIT__;
  if (value == 0)
    return 0;
  // 2 to the index of the most significant one of value.
  return (unsigned short)(1u << (bits - 1 - __builtin_clz(value)));
}
//===-- stdc_bit_width_uc.c -----------------------------------------------===//
//
// Part of freestanding-lgrt, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements stdc_bit_width_uc from C23's stdbit.h.
//
//===----------------------------------------------------------------------===//

unsigned int stdc_bit_width_uc(unsigned char value) {
  // The width of the type that __builtin_clz counts the leading zeros of.
  const int bits = (int)sizeof(unsigned int) * __CHAR_BIT__;
  if (value == 0)
    return 0;
  return (unsigned int)(bits - __builtin_clz(value));
}
//===-- stdc_bit_width_ui.c -----------------------------------------------===//
//
// Part of freestanding-lgrt, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements stdc_bit_width_ui from C23's stdbit.h.
//
//===----------------------------------------------------------------------===//

unsigned int stdc_bit_width_ui(unsigned int value) {
  // The width of the type that __builtin_clz counts the leading zeros of.
  const int bits = (int)sizeof(unsigned int) * __CHAR_BIT__;
  if (value == 0)
    return 0;
  return (unsigned int)(bits - __builtin_clz(value));
}
//===-- stdc_bit_width_ul.c -----------------------------------------------===//
//
// Part of freestanding-lgrt, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements stdc_bit_width_ul from C23's stdbit.h.
//
//===----------------------------------------------------------------------===//

unsigned int stdc_bit_width_ul(unsigned long value) {
  // The width of the type that __builtin_clzl counts the leading zeros of.
  const int bits = (int)sizeof(unsigned long) * __CHAR_BIT__;
  if (value == 0)
    return 0;
  return (unsigned int)(bits - __builtin_clzl(value));
}
//===-- stdc_bit_width_ull.c ----------------------------------------------===//
//
// Part of freestanding-lgrt, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements stdc_bit_width_ull from C23's stdbit.h.
//
//===----------------------------------------------------------------------===//

unsigned int stdc_bit_width_ull(unsigned long long value) {
  // The width of the type that __builtin_clzll counts the leading zeros of.
  const int bits = (int)sizeof(unsigned long long) * __CHAR_BIT__;
  if (value == 0)
    return 0;
  return (unsigned int)(bits - __builtin_clzll(value));
}
//===-- stdc_bit_width_us.c -----------------------------------------------===//
//
// Part of freestanding-lgrt, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements stdc_bit_width_us from C23's stdbit.h.
//
//===----------------------------------------------------------------------===//

unsigned int stdc_bit_width_us(unsigned short value) {
  // The width of the type that __builtin_clz counts the leading zeros of.
  const int bits = (int)sizeof(unsigned int) * __CHAR_BIT__;
  if (value == 0)
    return 0;
  return (unsigned int)(bits - __builtin_clz(value));
}
//===-- stdc_count_ones_uc.c ----------------------------------------------===//
//
// Part of freestanding-lgrt, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements stdc_count_ones_uc from C23's stdbit.h.
//
//===----------------------------------------------------------------------===//

unsigned int stdc_count_ones_uc(unsigned char value) {
  return (unsigned int)__builtin_popcount(value);
}
//===-- stdc_count_ones_ui.c ----------------------------------------------===//
//
// Part of freestanding-lgrt, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements stdc_count_ones_ui from C23's stdbit.h.
//
//===----------------------------------------------------------------------===//

unsigned int stdc_count_ones_ui(unsigned int value) {
  return (unsigned int)__builtin_popcount(value);
}
//===-- stdc_count_ones_ul.c ----------------------------------------------===//
//
// Part of freestanding-lgrt, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements stdc_count_ones_ul from C23's stdbit.h.
//
//===----------------------------------------------------------------------===//

unsigned int stdc_count_ones_ul(unsigned long value) {
  return (unsigned int)__builtin_popcountl(value);
}
//===-- stdc_count_ones_ull.c ---------------------------------------------===//
//
// Part of freestanding-lgrt, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements stdc_count_ones_ull from C23's stdbit.h.
//
//===----------------------------------------------------------------------===//

unsigned int stdc_count_ones_ull(unsigned long long value) {
  return (unsigned int)__builtin_popcountll(value);
}
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
//===-- stdc_count_zeros_ui.c ---------------------------------------------===//
//
// Part of freestanding-lgrt, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements stdc_count_zeros_ui from C23's stdbit.h.
//
//===----------------------------------------------------------------------===//

unsigned int stdc_count_zeros_ui(unsigned int value) {
  // The zeros of value are the ones of its complement.
  return (unsigned int)__builtin_popcount(~value);
}
//===-- stdc_count_zeros_ul.c ---------------------------------------------===//
//
// Part of freestanding-lgrt, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements stdc_count_zeros_ul from C23's stdbit.h.
//
//===----------------------------------------------------------------------===//

unsigned int stdc_count_zeros_ul(unsigned long value) {
  // The zeros of value are the ones of its complement.
  return (unsigned int)__builtin_popcountl(~value);
}
//===-- stdc_count_zeros_ull.c --------------------------------------------===//
//
// Part of freestanding-lgrt, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements stdc_count_zeros_ull from C23's stdbit.h.
//
//===----------------------------------------------------------------------===//

unsigned int stdc_count_zeros_ull(unsigned long long value) {
  // The zeros of value are the ones of its complement.
  return (unsigned int)__builtin_popcountll(~value);
}
//===-- stdc_count_zeros_us.c ---------------------------------------------===//
//
// Part of freestanding-lgrt, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements stdc_count_zeros_us from C23's stdbit.h.
//
//===----------------------------------------------------------------------===//

unsigned int stdc_count_zeros_us(unsigned short value) {
  // The zeros of value are the ones of its complement.
  return (unsigned int)__builtin_popcount((unsigned short)~value);
}
//===-- stdc_first_leading_one_uc.c ---------------------------------------===//
//
// Part of freestanding-lgrt, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements stdc_first_leading_one_uc from C23's stdbit.h.
//
//===----------------------------------------------------------------------===//

unsigned int stdc_first_leading_one_uc(unsigned char value) {
  // __builtin_clz counts the leading zeros of an unsigned int, which has these
  // many more bits than value.
  const int extra = (int)(sizeof(unsigned int) - sizeof(value)) * __CHAR_BIT__;
  if (value == 0)
    return 0;
  return (unsigned int)(__builtin_clz(value) - extra) + 1;
}
//===-- stdc_first_leading_one_ui.c ---------------------------------------===//
//
// Part of freestanding-lgrt, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements stdc_first_leading_one_ui from C23's stdbit.h.
//
//===----------------------------------------------------------------------===//

unsigned int stdc_first_leading_one_ui(unsigned int value) {
  if (value == 0)
    return 0;
  return (unsigned int)__builtin_clz(value) + 1;
}
//===-- stdc_first_leading_one_ul.c ---------------------------------------===//
//
// Part of freestanding-lgrt, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements stdc_first_leading_one_ul from C23's stdbit.h.
//
//===----------------------------------------------------------------------===//

unsigned int stdc_first_leading_one_ul(unsigned long value) {
  if (value == 0)
    return 0;
  return (unsigned int)__builtin_clzl(value) + 1;
}
//===-- stdc_first_leading_one_ull.c --------------------------------------===//
//
// Part of freestanding-lgrt, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements stdc_first_leading_one_ull from C23's stdbit.h.
//
//===----------------------------------------------------------------------===//

unsigned int stdc_first_leading_one_ull(unsigned long long value) {
  if (value == 0)
    return 0;
  return (unsigned int)__builtin_clzll(value) + 1;
}
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
//===-- stdc_first_leading_zero_uc.c --------------------------------------===//
//
// Part of freestanding-lgrt, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements stdc_first_leading_zero_uc from C23's stdbit.h.
//
//===----------------------------------------------------------------------===//

unsigned int stdc_first_leading_zero_uc(unsigned char value) {
  // __builtin_clz counts the leading zeros of an unsigned int, which has these
  // many more bits than value.
  const int extra = (int)(sizeof(unsigned int) - sizeof(value)) * __CHAR_BIT__;
  // The first leading zero of value is the first leading one of its
  // complement.
  unsigned char complement = (unsigned char)~value;
  if (complement == 0)
    return 0;
  return (unsigned int)(__builtin_clz(complement) - extra) + 1;
}
//===-- stdc_first_leading_zero_ui.c --------------------------------------===//
//
// Part of freestanding-lgrt, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements stdc_first_leading_zero_ui from C23's stdbit.h.
//
//===----------------------------------------------------------------------===//

unsigned int stdc_first_leading_zero_ui(unsigned int value) {
  // The first leading zero of value is the first leading one of its
  // complement.
  unsigned int complement = ~value;
  if (complement == 0)
    return 0;
  return (unsigned int)__builtin_clz(complement) + 1;
}
//===-- stdc_first_leading_zero_ul.c --------------------------------------===//
//
// Part of freestanding-lgrt, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements stdc_first_leading_zero_ul from C23's stdbit.h.
//
//===----------------------------------------------------------------------===//

unsigned int stdc_first_leading_zero_ul(unsigned long value) {
  // The first leading zero of value is the first leading one of its
  // complement.
  unsigned long complement = ~value;
  if (complement == 0)
    return 0;
  return (unsigned int)__builtin_clzl(complement) + 1;
}
//===-- stdc_first_leading_zero_ull.c -------------------------------------===//
//
// Part of freestanding-lgrt, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements stdc_first_leading_zero_ull from C23's stdbit.h.
//
//===----------------------------------------------------------------------===//

unsigned int stdc_first_leading_zero_ull(unsigned long long value) {
  // The first leading zero of value is the first leading one of its
  // complement.
  unsigned long long complement = ~value;
  if (complement == 0)
    return 0;
  return (unsigned int)__builtin_clzll(complement) + 1;
}
//===-- stdc_first_leading_zero_us.c --------------------------------------===//
//
// Part of freestanding-lgrt, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements stdc_first_leading_zero_us from C23's stdbit.h.
//
//===----------------------------------------------------------------------===//

unsigned int stdc_first_leading_zero_us(unsigned short value) {
  // __builtin_clz counts the leading zeros of an unsigned int, which has these
  // many more bits than value.
  const int extra = (int)(sizeof(unsigned int) - sizeof(value)) * __CHAR_BIT__;
  // The first leading zero of value is the first leading one of its
  // complement.
  unsigned short complement = (unsigned short)~value;
  if (complement == 0)
    return 0;
  return (unsigned int)(__builtin_clz(complement) - extra) + 1;
}
//===-- stdc_first_trailing_one_uc.c --------------------------------------===//
//
// Part of freestanding-lgrt, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements stdc_first_trailing_one_uc from C23's stdbit.h.
//
//===----------------------------------------------------------------------===//

unsigned int stdc_first_trailing_one_uc(unsigned char value) {
  if (value == 0)
    return 0;
  return (unsigned int)__builtin_ctz(value) + 1;
}
//===-- stdc_first_trailing_one_ui.c --------------------------------------===//
//
// Part of freestanding-lgrt, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements stdc_first_trailing_one_ui from C23's stdbit.h.
//
//===----------------------------------------------------------------------===//

unsigned int stdc_first_trailing_one_ui(unsigned int value) {
  if (value == 0)
    return 0;
  return (unsigned int)__builtin_ctz(value) + 1;
}
//===-- stdc_first_trailing_one_ul.c --------------------------------------===//
//
// Part of freestanding-lgrt, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements stdc_first_trailing_one_ul from C23's stdbit.h.
//
//===----------------------------------------------------------------------===//

unsigned int stdc_first_trailing_one_ul(unsigned long value) {
  if (value == 0)
    return 0;
  return (unsigned int)__builtin_ctzl(value) + 1;
}
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
//===-- stdc_first_trailing_one_us.c --------------------------------------===//
//
// Part of freestanding-lgrt, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements stdc_first_trailing_one_us from C23's stdbit.h.
//
//===----------------------------------------------------------------------===//

unsigned int stdc_first_trailing_one_us(unsigned short value) {
  if (value == 0)
    return 0;
  return (unsigned int)__builtin_ctz(value) + 1;
}
//===-- stdc_first_trailing_zero_uc.c -------------------------------------===//
//
// Part of freestanding-lgrt, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements stdc_first_trailing_zero_uc from C23's stdbit.h.
//
//===----------------------------------------------------------------------===//

unsigned int stdc_first_trailing_zero_uc(unsigned char value) {
  // The first trailing zero of value is the first trailing one of its
  // complement.
  unsigned char complement = (unsigned char)~value;
  if (complement == 0)
    return 0;
  return (unsigned int)__builtin_ctz(complement) + 1;
}
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
//===-- stdc_first_trailing_zero_ul.c -------------------------------------===//
//
// Part of freestanding-lgrt, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements stdc_first_trailing_zero_ul from C23's stdbit.h.
//
//===----------------------------------------------------------------------===//

unsigned int stdc_first_trailing_zero_ul(unsigned long value) {
  // The first trailing zero of value is the first trailing one of its
  // complement.
  unsigned long complement = ~value;
  if (complement == 0)
    return 0;
  return (unsigned int)__builtin_ctzl(complement) + 1;
}
//===-- stdc_first_trailing_zero_ull.c ------------------------------------===//
//
// Part of freestanding-lgrt, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements stdc_first_trailing_zero_ull from C23's stdbit.h.
//
//===----------------------------------------------------------------------===//

unsigned int stdc_first_trailing_zero_ull(unsigned long long value) {
  // The first trailing zero of value is the first trailing one of its
  // complement.
  unsigned long long complement = ~value;
  if (complement == 0)
    return 0;
  return (unsigned int)__builtin_ctzll(complement) + 1;
}
//===-- stdc_first_trailing_zero_us.c -------------------------------------===//
//
// Part of freestanding-lgrt, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements stdc_first_trailing_zero_us from C23's stdbit.h.
//
//===----------------------------------------------------------------------===//

unsigned int stdc_first_trailing_zero_us(unsigned short value) {
  // The first trailing zero of value is the first trailing one of its
  // complement.
  unsigned short complement = (unsigned short)~value;
  if (complement == 0)
    return 0;
  return (unsigned int)__builtin_ctz(complement) + 1;
}
//===-- stdc_has_single_bit_uc.c ------------------------------------------===//
//
// Part of freestanding-lgrt, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements stdc_has_single_bit_uc from C23's stdbit.h.
//
//===----------------------------------------------------------------------===//

_Bool stdc_has_single_bit_uc(unsigned char value) {
  return value != 0 && (value & (value - 1)) == 0;
}
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
//===-- stdc_has_single_bit_ul.c ------------------------------------------===//
//
// Part of freestanding-lgrt, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements stdc_has_single_bit_ul from C23's stdbit.h.
//
//===----------------------------------------------------------------------===//

_Bool stdc_has_single_bit_ul(unsigned long value) {
  return value != 0 && (value & (value - 1)) == 0;
}
//===-- stdc_has_single_bit_ull.c -----------------------------------------===//
//
// Part of freestanding-lgrt, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements stdc_has_single_bit_ull from C23's stdbit.h.
//
//===----------------------------------------------------------------------===//

_Bool stdc_has_single_bit_ull(unsigned long long value) {
  return value != 0 && (value & (value - 1)) == 0;
}
//===-- stdc_has_single_bit_us.c ------------------------------------------===//
//
// Part of freestanding-lgrt, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements stdc_has_single_bit_us from C23's stdbit.h.
//
//===----------------------------------------------------------------------===//

_Bool stdc_has_single_bit_us(unsigned short value) {
  return value != 0 && (value & (value - 1)) == 0;
}
//===-- stdc_leading_ones_uc.c --------------------------------------------===//
//
// Part of freestanding-lgrt, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements stdc_leading_ones_uc from C23's stdbit.h.
//
//===----------------------------------------------------------------------===//

unsigned int stdc_leading_ones_uc(unsigned char value) {
  // __builtin_clz counts the leading zeros of an unsigned int, which has these
  // many more bits than value.
  const int extra = (int)(sizeof(unsigned int) - sizeof(value)) * __CHAR_BIT__;
  // The leading ones of value are the leading zeros of its complement.
  unsigned char complement = (unsigned char)~value;
  if (complement == 0)
    return sizeof(value) * __CHAR_BIT__;
  return (unsigned int)(__builtin_clz(complement) - extra);
}
//===-- stdc_leading_ones_ui.c --------------------------------------------===//
//
// Part of freestanding-lgrt, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements stdc_leading_ones_ui from C23's stdbit.h.
//
//===----------------------------------------------------------------------===//

unsigned int stdc_leading_ones_ui(unsigned int value) {
  // The leading ones of value are the leading zeros of its complement.
  unsigned int complement = ~value;
  if (complement == 0)
    return sizeof(value) * __CHAR_BIT__;
  return (unsigned int)__builtin_clz(complement);
}
//===-- stdc_leading_ones_ul.c --------------------------------------------===//
//
// Part of freestanding-lgrt, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements stdc_leading_ones_ul from C23's stdbit.h.
//
//===----------------------------------------------------------------------===//

unsigned int stdc_leading_ones_ul(unsigned long value) {
  // The leading ones of value are the leading zeros of its complement.
  unsigned long complement = ~value;
  if (complement == 0)
    return sizeof(value) * __CHAR_BIT__;
  return (unsigned int)__builtin_clzl(complement);
}
//===-- stdc_leading_ones_ull.c -------------------------------------------===//
//
// Part of freestanding-lgrt, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements stdc_leading_ones_ull from C23's stdbit.h.
//
//===----------------------------------------------------------------------===//

unsigned int stdc_leading_ones_ull(unsigned long long value) {
  // The leading ones of value are the leading zeros of its complement.
  unsigned long long complement = ~value;
  if (complement == 0)
    return sizeof(value) * __CHAR_BIT__;
  return (unsigned int)__builtin_clzll(complement);
}
//===-- stdc_leading_ones_us.c --------------------------------------------===//
//
// Part of freestanding-lgrt, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements stdc_leading_ones_us from C23's stdbit.h.
//
//===----------------------------------------------------------------------===//

unsigned int stdc_leading_ones_us(unsigned short value) {
  // __builtin_clz counts the leading zeros of an unsigned int, which has these
  // many more bits than value.
  const int extra = (int)(sizeof(unsigned int) - sizeof(value)) * __CHAR_BIT__;
  // The leading ones of value are the leading zeros of its complement.
  unsigned short complement = (unsigned short)~value;
  if (complement == 0)
    return sizeof(value) * __CHAR_BIT__;
  return (unsigned int)(__builtin_clz(complement) - extra);
}
//===-- stdc_leading_zeros_uc.c -------------------------------------------===//
//
// Part of freestanding-lgrt, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements stdc_leading_zeros_uc from C23's stdbit.h.
//
//===----------------------------------------------------------------------===//

unsigned int stdc_leading_zeros_uc(unsigned char value) {
  // __builtin_clz counts the leading zeros of an unsigned int, which has these
  // many more bits than value.
  const int extra = (int)(sizeof(unsigned int) - sizeof(value)) * __CHAR_BIT__;
  if (value == 0)
    return sizeof(value) * __CHAR_BIT__;
  return (unsigned int)(__builtin_clz(value) - extra);
}
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
//===-- stdc_leading_zeros_ul.c -------------------------------------------===//
//
// Part of freestanding-lgrt, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements stdc_leading_zeros_ul from C23's stdbit.h.
//
//===----------------------------------------------------------------------===//

unsigned int stdc_leading_zeros_ul(unsigned long value) {
  if (value == 0)
    return sizeof(value) * __CHAR_BIT__;
  return (unsigned int)__builtin_clzl(value);
}
//===-- stdc_leading_zeros_ull.c ------------------------------------------===//
//
// Part of freestanding-lgrt, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements stdc_leading_zeros_ull from C23's stdbit.h.
//
//===----------------------------------------------------------------------===//

unsigned int stdc_leading_zeros_ull(unsigned long long value) {
  if (value == 0)
    return sizeof(value) * __CHAR_BIT__;
  return (unsigned int)__builtin_clzll(value);
}
//===-- stdc_leading_zeros_us.c -------------------------------------------===//
//
// Part of freestanding-lgrt, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements stdc_leading_zeros_us from C23's stdbit.h.
//
//===----------------------------------------------------------------------===//

unsigned int stdc_leading_zeros_us(unsigned short value) {
  // __builtin_clz counts the leading zeros of an unsigned int, which has these
  // many more bits than value.
  const int extra = (int)(sizeof(unsigned int) - sizeof(value)) * __CHAR_BIT__;
  if (value == 0)
    return sizeof(value) * __CHAR_BIT__;
  return (unsigned int)(__builtin_clz(value) - extra);
}
//===-- stdc_trailing_ones_uc.c -------------------------------------------===//
//
// Part of freestanding-lgrt, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements stdc_trailing_ones_uc from C23's stdbit.h.
//
//===----------------------------------------------------------------------===//

unsigned int stdc_trailing_ones_uc(unsigned char value) {
  // The trailing ones of value are the trailing zeros of its complement.
  unsigned char complement = (unsigned char)~value;
  if (complement == 0)
    return sizeof(value) * __CHAR_BIT__;
  return (unsigned int)__builtin_ctz(complement);
}
//===-- stdc_trailing_ones_ui.c -------------------------------------------===//
//
// Part of freestanding-lgrt, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements stdc_trailing_ones_ui from C23's stdbit.h.
//
//===----------------------------------------------------------------------===//

unsigned int stdc_trailing_ones_ui(unsigned int value) {
  // The trailing ones of value are the trailing zeros of its complement.
  unsigned int complement = ~value;
  if (complement == 0)
    return sizeof(value) * __CHAR_BIT__;
  return (unsigned int)__builtin_ctz(complement);
}
//===-- stdc_trailing_ones_ul.c -------------------------------------------===//
//
// Part of freestanding-lgrt, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements stdc_trailing_ones_ul from C23's stdbit.h.
//
//===----------------------------------------------------------------------===//

unsigned int stdc_trailing_ones_ul(unsigned long value) {
  // The trailing ones of value are the trailing zeros of its complement.
  unsigned long complement = ~value;
  if (complement == 0)
    return sizeof(value) * __CHAR_BIT__;
  return (unsigned int)__builtin_ctzl(complement);
}
//===-- stdc_trailing_ones_ull.c ------------------------------------------===//
//
// Part of freestanding-lgrt, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements stdc_trailing_ones_ull from C23's stdbit.h.
//
//===----------------------------------------------------------------------===//

unsigned int stdc_trailing_ones_ull(unsigned long long value) {
  // The trailing ones of value are the trailing zeros of its complement.
  unsigned long long complement = ~value;
  if (complement == 0)
    return sizeof(value) * __CHAR_BIT__;
  return (unsigned int)__builtin_ctzll(complement);
}
//===-- stdc_trailing_ones_us.c -------------------------------------------===//
//
// Part of freestanding-lgrt, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements stdc_trailing_ones_us from C23's stdbit.h.
//
//===----------------------------------------------------------------------===//

unsigned int stdc_trailing_ones_us(unsigned short value) {
  // The trailing ones of value are the trailing zeros of its complement.
  unsigned short complement = (unsigned short)~value;
  if (complement == 0)
    return sizeof(value) * __CHAR_BIT__;
  return (unsigned int)__builtin_ctz(complement);
}
//===-- stdc_trailing_zeros_uc.c ------------------------------------------===//
//
// Part of freestanding-lgrt, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements stdc_trailing_zeros_uc from C23's stdbit.h.
//
//===----------------------------------------------------------------------===//

unsigned int stdc_trailing_zeros_uc(unsigned char value) {
  if (value == 0)
    return sizeof(value) * __CHAR_BIT__;
  return (unsigned int)__builtin_ctz(value);
}
//===-- stdc_trailing_zeros_ui.c ------------------------------------------===//
//
// Part of freestanding-lgrt, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements stdc_trailing_zeros_ui from C23's stdbit.h.
//
//===----------------------------------------------------------------------===//

unsigned int stdc_trailing_zeros_ui(unsigned int value) {
  if (value == 0)
    return sizeof(value) * __CHAR_BIT__;
  return (unsigned int)__builtin_ctz(value);
}
//===-- stdc_trailing_zeros_ul.c ------------------------------------------===//
//
// Part of freestanding-lgrt, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements stdc_trailing_zeros_ul from C23's stdbit.h.
//
//===----------------------------------------------------------------------===//

unsigned int stdc_trailing_zeros_ul(unsigned long value) {
  if (value == 0)
    return sizeof(value) * __CHAR_BIT__;
  return (unsigned int)__builtin_ctzl(value);
}
//===-- stdc_trailing_zeros_ull.c -----------------------------------------===//
//
// Part of freestanding-lgrt, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements stdc_trailing_zeros_ull from C23's stdbit.h.
//
//===----------------------------------------------------------------------===//

unsigned int stdc_trailing_zeros_ull(unsigned long long value) {
  if (value == 0)
    return sizeof(value) * __CHAR_BIT__;
  return (unsigned int)__builtin_ctzll(value);
}
//===-- stdc_trailing_zeros_us.c ------------------------------------------===//
//
// Part of freestanding-lgrt, under the Apache License v2.0 with LLVM
// Exceptions. See LICENSE.TXT for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements stdc_trailing_zeros_us from C23's stdbit.h.
//
//===----------------------------------------------------------------------===//

unsigned int stdc_trailing_zeros_us(unsigned short value) {
  if (value == 0)
    return sizeof(value) * __CHAR_BIT__;
  return (unsigned int)__builtin_ctz(value);
}
//===-- subvdi3.c - Implement __subvdi3 -----------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements __subvdi3 for the compiler_rt library.
//
//===----------------------------------------------------------------------===//


// Returns: a - b

// Effects: aborts if a - b overflows

COMPILER_RT_ABI di_int __subvdi3(di_int a, di_int b) {
  di_int s = (du_int)a - (du_int)b;
  if (b >= 0) {
    if (s > a)
      compilerrt_abort();
  } else {
    if (s <= a)
      compilerrt_abort();
  }
  return s;
}
//===-- subvsi3.c - Implement __subvsi3 -----------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements __subvsi3 for the compiler_rt library.
//
//===----------------------------------------------------------------------===//


// Returns: a - b

// Effects: aborts if a - b overflows

COMPILER_RT_ABI si_int __subvsi3(si_int a, si_int b) {
  si_int s = (su_int)a - (su_int)b;
  if (b >= 0) {
    if (s > a)
      compilerrt_abort();
  } else {
    if (s <= a)
      compilerrt_abort();
  }
  return s;
}
//===-- subvti3.c - Implement __subvti3 -----------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements __subvti3 for the compiler_rt library.
//
//===----------------------------------------------------------------------===//


#ifdef CRT_HAS_128BIT

// Returns: a - b

// Effects: aborts if a - b overflows

COMPILER_RT_ABI ti_int __subvti3(ti_int a, ti_int b) {
  ti_int s = (tu_int)a - (tu_int)b;
  if (b >= 0) {
    if (s > a)
      compilerrt_abort();
  } else {
    if (s <= a)
      compilerrt_abort();
  }
  return s;
}

#endif // CRT_HAS_128BIT
//===-- ucmpdi2.c - Implement __ucmpdi2 -----------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements __ucmpdi2 for the compiler_rt library.
//
//===----------------------------------------------------------------------===//


// Returns:  if (a <  b) returns 0
//           if (a == b) returns 1
//           if (a >  b) returns 2

COMPILER_RT_ABI si_int __ucmpdi2(du_int a, du_int b) {
  udwords x;
  x.all = a;
  udwords y;
  y.all = b;
  if (x.s.high < y.s.high)
    return 0;
  if (x.s.high > y.s.high)
    return 2;
  if (x.s.low < y.s.low)
    return 0;
  if (x.s.low > y.s.low)
    return 2;
  return 1;
}

#ifdef __ARM_EABI__
// Returns: if (a <  b) returns -1
//           if (a == b) returns  0
//           if (a >  b) returns  1
COMPILER_RT_ABI si_int __aeabi_ulcmp(di_int a, di_int b) {
  return __ucmpdi2(a, b) - 1;
}
#endif
//===-- ucmpti2.c - Implement __ucmpti2 -----------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements __ucmpti2 for the compiler_rt library.
//
//===----------------------------------------------------------------------===//


#ifdef CRT_HAS_128BIT

// Returns:  if (a <  b) returns 0
//           if (a == b) returns 1
//           if (a >  b) returns 2

COMPILER_RT_ABI si_int __ucmpti2(tu_int a, tu_int b) {
  utwords x;
  x.all = a;
  utwords y;
  y.all = b;
  if (x.s.high < y.s.high)
    return 0;
  if (x.s.high > y.s.high)
    return 2;
  if (x.s.low < y.s.low)
    return 0;
  if (x.s.low > y.s.low)
    return 2;
  return 1;
}

#endif // CRT_HAS_128BIT
//===-- udivdi3.c - Implement __udivdi3 -----------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
// 2024/08/10 - Modified by Mintsuki for use inside freestanding-lgrt
//
//===----------------------------------------------------------------------===//
//
// This file implements __udivdi3 for the compiler_rt library.
//
//===----------------------------------------------------------------------===//


#define fixuint_t du_int
#define fixint_t di_int
//===-- int_div_impl.inc - Integer division ---------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
// 2024/10/20 - Modified by Mintsuki for use inside freestanding-lgrt
//
//===----------------------------------------------------------------------===//
//
// Helpers used by __udivsi3, __umodsi3, __udivdi3, and __umodsi3.
//
//===----------------------------------------------------------------------===//

#define clz(a) (sizeof(a) == sizeof(unsigned long long) ? __builtin_clzll(a) : clzsi(a))

#undef __udivXi3
#define __udivXi3 __udivXi3_27

// Adapted from Figure 3-40 of The PowerPC Compiler Writer's Guide
static __inline fixuint_t __udivXi3(fixuint_t n, fixuint_t d) {
  const unsigned N = sizeof(fixuint_t) * CHAR_BIT;
  // d == 0 cases are unspecified.
  unsigned sr = (d ? clz(d) : N) - (n ? clz(n) : N);
  // 0 <= sr <= N - 1 or sr is very large.
  if (sr > N - 1) // n < d
    return 0;
  if (sr == N - 1) // d == 1
    return n;
  ++sr;
  // 1 <= sr <= N - 1. Shifts do not trigger UB.
  fixuint_t r = n >> sr;
  n <<= N - sr;
  fixuint_t carry = 0;
  for (; sr > 0; --sr) {
    r = (r << 1) | (n >> (N - 1));
    n = (n << 1) | carry;
    // Branch-less version of:
    // carry = 0;
    // if (r >= d) r -= d, carry = 1;
    const fixint_t s = (fixint_t)(d - r - 1) >> (N - 1);
    carry = s & 1;
    r -= d & s;
  }
  n = (n << 1) | carry;
  return n;
}

#undef __umodXi3
#define __umodXi3 __umodXi3_28

// Mostly identical to __udivXi3 but the return values are different.
static __inline fixuint_t __umodXi3(fixuint_t n, fixuint_t d) {
  const unsigned N = sizeof(fixuint_t) * CHAR_BIT;
  // d == 0 cases are unspecified.
  unsigned sr = (d ? clz(d) : N) - (n ? clz(n) : N);
  // 0 <= sr <= N - 1 or sr is very large.
  if (sr > N - 1) // n < d
    return n;
  if (sr == N - 1) // d == 1
    return 0;
  ++sr;
  // 1 <= sr <= N - 1. Shifts do not trigger UB.
  fixuint_t r = n >> sr;
  n <<= N - sr;
  fixuint_t carry = 0;
  for (; sr > 0; --sr) {
    r = (r << 1) | (n >> (N - 1));
    n = (n << 1) | carry;
    // Branch-less version of:
    // carry = 0;
    // if (r >= d) r -= d, carry = 1;
    const fixint_t s = (fixint_t)(d - r - 1) >> (N - 1);
    carry = s & 1;
    r -= d & s;
  }
  return r;
}

#undef __divXi3

#ifdef COMPUTE_UDIV

#define __divXi3 __divXi3_29

static __inline fixint_t __divXi3(fixint_t a, fixint_t b) {
  const int N = (int)(sizeof(fixint_t) * CHAR_BIT) - 1;
  fixint_t s_a = a >> N;                            // s_a = a < 0 ? -1 : 0
  fixint_t s_b = b >> N;                            // s_b = b < 0 ? -1 : 0
  fixuint_t a_u = (fixuint_t)(a ^ s_a) + (-s_a);    // negate if s_a == -1
  fixuint_t b_u = (fixuint_t)(b ^ s_b) + (-s_b);    // negate if s_b == -1
  s_a ^= s_b;                                       // sign of quotient
  return (COMPUTE_UDIV(a_u, b_u) ^ s_a) + (-s_a);   // negate if s_a == -1
}
#endif // COMPUTE_UDIV

#undef __modXi3

#ifdef ASSIGN_UMOD

#define __modXi3 __modXi3_30

static __inline fixint_t __modXi3(fixint_t a, fixint_t b) {
  const int N = (int)(sizeof(fixint_t) * CHAR_BIT) - 1;
  fixint_t s = b >> N;                              // s = b < 0 ? -1 : 0
  fixuint_t b_u = (fixuint_t)(b ^ s) + (-s);        // negate if s == -1
  s = a >> N;                                       // s = a < 0 ? -1 : 0
  fixuint_t a_u = (fixuint_t)(a ^ s) + (-s);        // negate if s == -1
  fixuint_t res;
  ASSIGN_UMOD(res, a_u, b_u);
  return (res ^ s) + (-s);                          // negate if s == -1
}
#endif // ASSIGN_UMOD

#undef clz

// Returns: a / b

COMPILER_RT_ABI du_int __udivdi3(du_int a, du_int b) {
  return __udivXi3(a, b);
}

#undef fixuint_t
#undef fixint_t
//===-- udivmoddi4.c - Implement __udivmoddi4 -----------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
// 2024/01/21 - Modified by Mintsuki for use inside freestanding-lgrt
//
//===----------------------------------------------------------------------===//
//
// This file implements __udivmoddi4 for the compiler_rt library.
//
//===----------------------------------------------------------------------===//


// Effects: if rem != 0, *rem = a % b
// Returns: a / b

// Translated from Figure 3-40 of The PowerPC Compiler Writer's Guide

COMPILER_RT_ABI du_int __udivmoddi4(du_int a, du_int b, du_int *rem) {
  const unsigned n_uword_bits = sizeof(su_int) * CHAR_BIT;
  const unsigned n_udword_bits = sizeof(du_int) * CHAR_BIT;
  udwords n;
  n.all = a;
  udwords d;
  d.all = b;
  udwords q;
  udwords r;
  unsigned sr;
  // special cases, X is unknown, K != 0
  if (n.s.high == 0) {
    if (d.s.high == 0) {
      // 0 X
      // ---
      // 0 X
      if (rem)
        *rem = n.s.low % d.s.low;
      return n.s.low / d.s.low;
    }
    // 0 X
    // ---
    // K X
    if (rem)
      *rem = n.s.low;
    return 0;
  }
  // n.s.high != 0
  if (d.s.low == 0) {
    if (d.s.high == 0) {
      // K X
      // ---
      // 0 0
      if (rem)
        *rem = n.s.high % d.s.low;
      return n.s.high / d.s.low;
    }
    // d.s.high != 0
    if (n.s.low == 0) {
      // K 0
      // ---
      // K 0
      if (rem) {
        r.s.high = n.s.high % d.s.high;
        r.s.low = 0;
        *rem = r.all;
      }
      return n.s.high / d.s.high;
    }
    // K K
    // ---
    // K 0
    if ((d.s.high & (d.s.high - 1)) == 0) /* if d is a power of 2 */ {
      if (rem) {
        r.s.low = n.s.low;
        r.s.high = n.s.high & (d.s.high - 1);
        *rem = r.all;
      }
      return n.s.high >> ctzsi(d.s.high);
    }
    // K K
    // ---
    // K 0
    sr = clzsi(d.s.high) - clzsi(n.s.high);
    // 0 <= sr <= n_uword_bits - 2 or sr large
    if (sr > n_uword_bits - 2) {
      if (rem)
        *rem = n.all;
      return 0;
    }
    ++sr;
    // 1 <= sr <= n_uword_bits - 1
    // q.all = n.all << (n_udword_bits - sr);
    q.s.low = 0;
    q.s.high = n.s.low << (n_uword_bits - sr);
    // r.all = n.all >> sr;
    r.s.high = n.s.high >> sr;
    r.s.low = (n.s.high << (n_uword_bits - sr)) | (n.s.low >> sr);
  } else /* d.s.low != 0 */ {
    if (d.s.high == 0) {
      // K X
      // ---
      // 0 K
      if ((d.s.low & (d.s.low - 1)) == 0) /* if d is a power of 2 */ {
        if (rem)
          *rem = n.s.low & (d.s.low - 1);
        if (d.s.low == 1)
          return n.all;
        sr = ctzsi(d.s.low);
        q.s.high = n.s.high >> sr;
        q.s.low = (n.s.high << (n_uword_bits - sr)) | (n.s.low >> sr);
        return q.all;
      }
      // K X
      // ---
      // 0 K
      sr = 1 + n_uword_bits + clzsi(d.s.low) - clzsi(n.s.high);
      // 2 <= sr <= n_udword_bits - 1
      // q.all = n.all << (n_udword_bits - sr);
      // r.all = n.all >> sr;
      if (sr == n_uword_bits) {
        q.s.low = 0;
        q.s.high = n.s.low;
        r.s.high = 0;
        r.s.low = n.s.high;
      } else if (sr < n_uword_bits) /* 2 <= sr <= n_uword_bits - 1 */ {
        q.s.low = 0;
        q.s.high = n.s.low << (n_uword_bits - sr);
        r.s.high = n.s.high >> sr;
        r.s.low = (n.s.high << (n_uword_bits - sr)) | (n.s.low >> sr);
      } else /* n_uword_bits + 1 <= sr <= n_udword_bits - 1 */ {
        q.s.low = n.s.low << (n_udword_bits - sr);
        q.s.high = (n.s.high << (n_udword_bits - sr)) |
                   (n.s.low >> (sr - n_uword_bits));
        r.s.high = 0;
        r.s.low = n.s.high >> (sr - n_uword_bits);
      }
    } else {
      // K X
      // ---
      // K K
      sr = clzsi(d.s.high) - clzsi(n.s.high);
      // 0 <= sr <= n_uword_bits - 1 or sr large
      if (sr > n_uword_bits - 1) {
        if (rem)
          *rem = n.all;
        return 0;
      }
      ++sr;
      // 1 <= sr <= n_uword_bits
      // q.all = n.all << (n_udword_bits - sr);
      q.s.low = 0;
      if (sr == n_uword_bits) {
        q.s.high = n.s.low;
        r.s.high = 0;
        r.s.low = n.s.high;
      } else {
        q.s.high = n.s.low << (n_uword_bits - sr);
        r.s.high = n.s.high >> sr;
        r.s.low = (n.s.high << (n_uword_bits - sr)) | (n.s.low >> sr);
      }
    }
  }
  // Not a special case
  // q and r are initialized with:
  // q.all = n.all << (n_udword_bits - sr);
  // r.all = n.all >> sr;
  // 1 <= sr <= n_udword_bits - 1
  su_int carry = 0;
  for (; sr > 0; --sr) {
    // r:q = ((r:q)  << 1) | carry
    r.s.high = (r.s.high << 1) | (r.s.low >> (n_uword_bits - 1));
    r.s.low = (r.s.low << 1) | (q.s.high >> (n_uword_bits - 1));
    q.s.high = (q.s.high << 1) | (q.s.low >> (n_uword_bits - 1));
    q.s.low = (q.s.low << 1) | carry;
    // carry = 0;
    // if (r.all >= d.all)
    // {
    //      r.all -= d.all;
    //      carry = 1;
    // }
    const di_int s = (di_int)(d.all - r.all - 1) >> (n_udword_bits - 1);
    carry = s & 1;
    r.all -= d.all & s;
  }
  q.all = (q.all << 1) | carry;
  if (rem)
    *rem = r.all;
  return q.all;
}
//===-- udivmodsi4.c - Implement __udivmodsi4 -----------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements __udivmodsi4 for the compiler_rt library.
//
//===----------------------------------------------------------------------===//


// Returns: a / b, *rem = a % b

COMPILER_RT_ABI su_int __udivmodsi4(su_int a, su_int b, su_int *rem) {
  si_int d = __udivsi3(a, b);
  *rem = a - (d * b);
  return d;
}
//===-- udivmodti4.c - Implement __udivmodti4 -----------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
// 2026/10/17 - Modified by Mintsuki for use inside freestanding-lgrt
//
//===----------------------------------------------------------------------===//
//
// This file implements __udivmodti4 for the compiler_rt library.
//
//===----------------------------------------------------------------------===//


#ifdef CRT_HAS_128BIT

// Returns the 128 bit division result by 64 bit. Result must fit in 64 bits.
// Remainder stored in r.
// Taken and adjusted from libdivide libdivide_128_div_64_to_64 division
// fallback. For a correctness proof see the reference for this algorithm
// in Knuth, Volume 2, section 4.3.1, Algorithm D.
UNUSED
static inline du_int udiv128by64to64default(du_int u1, du_int u0, du_int v,
                                            du_int *r) {
  const unsigned n_udword_bits = sizeof(du_int) * CHAR_BIT;
  const du_int b = (1ULL << (n_udword_bits / 2)); // Number base (32 bits)
  du_int un1, un0;                                // Norm. dividend LSD's
  du_int vn1, vn0;                                // Norm. divisor digits
  du_int q1, q0;                                  // Quotient digits
  du_int un64, un21, un10;                        // Dividend digit pairs
  du_int rhat;                                    // A remainder
  si_int s;                                       // Shift amount for normalization

  s = __builtin_clzll(v);
  if (s > 0) {
    // Normalize the divisor.
    v = v << s;
    un64 = (u1 << s) | (u0 >> (n_udword_bits - s));
    un10 = u0 << s; // Shift dividend left
  } else {
    // Avoid undefined behavior of (u0 >> 64).
    un64 = u1;
    un10 = u0;
  }

  // Break divisor up into two 32-bit digits.
  vn1 = v >> (n_udword_bits / 2);
  vn0 = v & 0xFFFFFFFF;

  // Break right half of dividend into two digits.
  un1 = un10 >> (n_udword_bits / 2);
  un0 = un10 & 0xFFFFFFFF;

  // Compute the first quotient digit, q1.
  q1 = un64 / vn1;
  rhat = un64 - q1 * vn1;

  // q1 has at most error 2. No more than 2 iterations.
  while (q1 >= b || q1 * vn0 > b * rhat + un1) {
    q1 = q1 - 1;
    rhat = rhat + vn1;
    if (rhat >= b)
      break;
  }

  un21 = un64 * b + un1 - q1 * v;

  // Compute the second quotient digit.
  q0 = un21 / vn1;
  rhat = un21 - q0 * vn1;

  // q0 has at most error 2. No more than 2 iterations.
  while (q0 >= b || q0 * vn0 > b * rhat + un0) {
    q0 = q0 - 1;
    rhat = rhat + vn1;
    if (rhat >= b)
      break;
  }

  *r = (un21 * b + un0 - q0 * v) >> s;
  return q1 * b + q0;
}

static inline du_int udiv128by64to64(du_int u1, du_int u0, du_int v,
                                     du_int *r) {
#if defined(__x86_64__)
  du_int result;
  __asm__("{divq %[v]|div %[v]}"
          : "=a"(result), "=d"(*r)
          : [ v ] "r"(v), "a"(u0), "d"(u1));
  return result;
#else
  return udiv128by64to64default(u1, u0, v, r);
#endif
}

// Effects: if rem != 0, *rem = a % b
// Returns: a / b

COMPILER_RT_ABI tu_int __udivmodti4(tu_int a, tu_int b, tu_int *rem) {
  const unsigned n_utword_bits = sizeof(tu_int) * CHAR_BIT;
  utwords dividend;
  dividend.all = a;
  utwords divisor;
  divisor.all = b;
  utwords quotient;
  utwords remainder;
  if (divisor.all > dividend.all) {
    if (rem)
      *rem = dividend.all;
    return 0;
  }
  // When the divisor fits in 64 bits, we can use an optimized path.
  if (divisor.s.high == 0) {
    remainder.s.high = 0;
    if (dividend.s.high < divisor.s.low) {
      // The result fits in 64 bits.
      quotient.s.low = udiv128by64to64(dividend.s.high, dividend.s.low,
                                       divisor.s.low, &remainder.s.low);
      quotient.s.high = 0;
    } else {
      // First, divide with the high part to get the remainder in dividend.s.high.
      // After that dividend.s.high < divisor.s.low.
      quotient.s.high = dividend.s.high / divisor.s.low;
      dividend.s.high = dividend.s.high % divisor.s.low;
      quotient.s.low = udiv128by64to64(dividend.s.high, dividend.s.low,
                                       divisor.s.low, &remainder.s.low);
    }
    if (rem)
      *rem = remainder.all;
    return quotient.all;
  }
  // 0 <= shift <= 63.
  si_int shift =
      __builtin_clzll(divisor.s.high) - __builtin_clzll(dividend.s.high);
  divisor.all <<= shift;
  quotient.s.high = 0;
  quotient.s.low = 0;
  for (; shift >= 0; --shift) {
    quotient.s.low <<= 1;
    // Branch free version of.
    // if (dividend.all >= divisor.all)
    // {
    //    dividend.all -= divisor.all;
    //    carry = 1;
    // }
    const ti_int s =
        (ti_int)(divisor.all - dividend.all - 1) >> (n_utword_bits - 1);
    quotient.s.low |= s & 1;
    dividend.all -= divisor.all & s;
    divisor.all >>= 1;
  }
  if (rem)
    *rem = dividend.all;
  return quotient.all;
}

#endif // CRT_HAS_128BIT
//===-- udivsi3.c - Implement __udivsi3 -----------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
// 2024/08/10 - Modified by Mintsuki for use inside freestanding-lgrt
//
//===----------------------------------------------------------------------===//
//
// This file implements __udivsi3 for the compiler_rt library.
//
//===----------------------------------------------------------------------===//


#define fixuint_t su_int
#define fixint_t si_int
//===-- int_div_impl.inc - Integer division ---------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
// 2024/10/20 - Modified by Mintsuki for use inside freestanding-lgrt
//
//===----------------------------------------------------------------------===//
//
// Helpers used by __udivsi3, __umodsi3, __udivdi3, and __umodsi3.
//
//===----------------------------------------------------------------------===//

#define clz(a) (sizeof(a) == sizeof(unsigned long long) ? __builtin_clzll(a) : clzsi(a))

#undef __udivXi3
#define __udivXi3 __udivXi3_31

// Adapted from Figure 3-40 of The PowerPC Compiler Writer's Guide
static __inline fixuint_t __udivXi3(fixuint_t n, fixuint_t d) {
  const unsigned N = sizeof(fixuint_t) * CHAR_BIT;
  // d == 0 cases are unspecified.
  unsigned sr = (d ? clz(d) : N) - (n ? clz(n) : N);
  // 0 <= sr <= N - 1 or sr is very large.
  if (sr > N - 1) // n < d
    return 0;
  if (sr == N - 1) // d == 1
    return n;
  ++sr;
  // 1 <= sr <= N - 1. Shifts do not trigger UB.
  fixuint_t r = n >> sr;
  n <<= N - sr;
  fixuint_t carry = 0;
  for (; sr > 0; --sr) {
    r = (r << 1) | (n >> (N - 1));
    n = (n << 1) | carry;
    // Branch-less version of:
    // carry = 0;
    // if (r >= d) r -= d, carry = 1;
    const fixint_t s = (fixint_t)(d - r - 1) >> (N - 1);
    carry = s & 1;
    r -= d & s;
  }
  n = (n << 1) | carry;
  return n;
}

#undef __umodXi3
#define __umodXi3 __umodXi3_32

// Mostly identical to __udivXi3 but the return values are different.
static __inline fixuint_t __umodXi3(fixuint_t n, fixuint_t d) {
  const unsigned N = sizeof(fixuint_t) * CHAR_BIT;
  // d == 0 cases are unspecified.
  unsigned sr = (d ? clz(d) : N) - (n ? clz(n) : N);
  // 0 <= sr <= N - 1 or sr is very large.
  if (sr > N - 1) // n < d
    return n;
  if (sr == N - 1) // d == 1
    return 0;
  ++sr;
  // 1 <= sr <= N - 1. Shifts do not trigger UB.
  fixuint_t r = n >> sr;
  n <<= N - sr;
  fixuint_t carry = 0;
  for (; sr > 0; --sr) {
    r = (r << 1) | (n >> (N - 1));
    n = (n << 1) | carry;
    // Branch-less version of:
    // carry = 0;
    // if (r >= d) r -= d, carry = 1;
    const fixint_t s = (fixint_t)(d - r - 1) >> (N - 1);
    carry = s & 1;
    r -= d & s;
  }
  return r;
}

#undef __divXi3

#ifdef COMPUTE_UDIV

#define __divXi3 __divXi3_33

static __inline fixint_t __divXi3(fixint_t a, fixint_t b) {
  const int N = (int)(sizeof(fixint_t) * CHAR_BIT) - 1;
  fixint_t s_a = a >> N;                            // s_a = a < 0 ? -1 : 0
  fixint_t s_b = b >> N;                            // s_b = b < 0 ? -1 : 0
  fixuint_t a_u = (fixuint_t)(a ^ s_a) + (-s_a);    // negate if s_a == -1
  fixuint_t b_u = (fixuint_t)(b ^ s_b) + (-s_b);    // negate if s_b == -1
  s_a ^= s_b;                                       // sign of quotient
  return (COMPUTE_UDIV(a_u, b_u) ^ s_a) + (-s_a);   // negate if s_a == -1
}
#endif // COMPUTE_UDIV

#undef __modXi3

#ifdef ASSIGN_UMOD

#define __modXi3 __modXi3_34

static __inline fixint_t __modXi3(fixint_t a, fixint_t b) {
  const int N = (int)(sizeof(fixint_t) * CHAR_BIT) - 1;
  fixint_t s = b >> N;                              // s = b < 0 ? -1 : 0
  fixuint_t b_u = (fixuint_t)(b ^ s) + (-s);        // negate if s == -1
  s = a >> N;                                       // s = a < 0 ? -1 : 0
  fixuint_t a_u = (fixuint_t)(a ^ s) + (-s);        // negate if s == -1
  fixuint_t res;
  ASSIGN_UMOD(res, a_u, b_u);
  return (res ^ s) + (-s);                          // negate if s == -1
}
#endif // ASSIGN_UMOD

#undef clz

// Returns: a / b

COMPILER_RT_ABI su_int __udivsi3(su_int a, su_int b) {
  return __udivXi3(a, b);
}

#if defined(__ARM_EABI__)
COMPILER_RT_ALIAS(__udivsi3, __aeabi_uidiv)
#endif

#undef fixuint_t
#undef fixint_t
//===-- udivti3.c - Implement __udivti3 -----------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements __udivti3 for the compiler_rt library.
//
//===----------------------------------------------------------------------===//


#ifdef CRT_HAS_128BIT

// Returns: a / b

COMPILER_RT_ABI tu_int __udivti3(tu_int a, tu_int b) {
  return __udivmodti4(a, b, 0);
}

#endif // CRT_HAS_128BIT
//===-- umoddi3.c - Implement __umoddi3 -----------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
// 2024/08/10 - Modified by Mintsuki for use inside freestanding-lgrt
//
//===----------------------------------------------------------------------===//
//
// This file implements __umoddi3 for the compiler_rt library.
//
//===----------------------------------------------------------------------===//


#define fixuint_t du_int
#define fixint_t di_int
//===-- int_div_impl.inc - Integer division ---------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
// 2024/10/20 - Modified by Mintsuki for use inside freestanding-lgrt
//
//===----------------------------------------------------------------------===//
//
// Helpers used by __udivsi3, __umodsi3, __udivdi3, and __umodsi3.
//
//===----------------------------------------------------------------------===//

#define clz(a) (sizeof(a) == sizeof(unsigned long long) ? __builtin_clzll(a) : clzsi(a))

#undef __udivXi3
#define __udivXi3 __udivXi3_35

// Adapted from Figure 3-40 of The PowerPC Compiler Writer's Guide
static __inline fixuint_t __udivXi3(fixuint_t n, fixuint_t d) {
  const unsigned N = sizeof(fixuint_t) * CHAR_BIT;
  // d == 0 cases are unspecified.
  unsigned sr = (d ? clz(d) : N) - (n ? clz(n) : N);
  // 0 <= sr <= N - 1 or sr is very large.
  if (sr > N - 1) // n < d
    return 0;
  if (sr == N - 1) // d == 1
    return n;
  ++sr;
  // 1 <= sr <= N - 1. Shifts do not trigger UB.
  fixuint_t r = n >> sr;
  n <<= N - sr;
  fixuint_t carry = 0;
  for (; sr > 0; --sr) {
    r = (r << 1) | (n >> (N - 1));
    n = (n << 1) | carry;
    // Branch-less version of:
    // carry = 0;
    // if (r >= d) r -= d, carry = 1;
    const fixint_t s = (fixint_t)(d - r - 1) >> (N - 1);
    carry = s & 1;
    r -= d & s;
  }
  n = (n << 1) | carry;
  return n;
}

#undef __umodXi3
#define __umodXi3 __umodXi3_36

// Mostly identical to __udivXi3 but the return values are different.
static __inline fixuint_t __umodXi3(fixuint_t n, fixuint_t d) {
  const unsigned N = sizeof(fixuint_t) * CHAR_BIT;
  // d == 0 cases are unspecified.
  unsigned sr = (d ? clz(d) : N) - (n ? clz(n) : N);
  // 0 <= sr <= N - 1 or sr is very large.
  if (sr > N - 1) // n < d
    return n;
  if (sr == N - 1) // d == 1
    return 0;
  ++sr;
  // 1 <= sr <= N - 1. Shifts do not trigger UB.
  fixuint_t r = n >> sr;
  n <<= N - sr;
  fixuint_t carry = 0;
  for (; sr > 0; --sr) {
    r = (r << 1) | (n >> (N - 1));
    n = (n << 1) | carry;
    // Branch-less version of:
    // carry = 0;
    // if (r >= d) r -= d, carry = 1;
    const fixint_t s = (fixint_t)(d - r - 1) >> (N - 1);
    carry = s & 1;
    r -= d & s;
  }
  return r;
}

#undef __divXi3

#ifdef COMPUTE_UDIV

#define __divXi3 __divXi3_37

static __inline fixint_t __divXi3(fixint_t a, fixint_t b) {
  const int N = (int)(sizeof(fixint_t) * CHAR_BIT) - 1;
  fixint_t s_a = a >> N;                            // s_a = a < 0 ? -1 : 0
  fixint_t s_b = b >> N;                            // s_b = b < 0 ? -1 : 0
  fixuint_t a_u = (fixuint_t)(a ^ s_a) + (-s_a);    // negate if s_a == -1
  fixuint_t b_u = (fixuint_t)(b ^ s_b) + (-s_b);    // negate if s_b == -1
  s_a ^= s_b;                                       // sign of quotient
  return (COMPUTE_UDIV(a_u, b_u) ^ s_a) + (-s_a);   // negate if s_a == -1
}
#endif // COMPUTE_UDIV

#undef __modXi3

#ifdef ASSIGN_UMOD

#define __modXi3 __modXi3_38

static __inline fixint_t __modXi3(fixint_t a, fixint_t b) {
  const int N = (int)(sizeof(fixint_t) * CHAR_BIT) - 1;
  fixint_t s = b >> N;                              // s = b < 0 ? -1 : 0
  fixuint_t b_u = (fixuint_t)(b ^ s) + (-s);        // negate if s == -1
  s = a >> N;                                       // s = a < 0 ? -1 : 0
  fixuint_t a_u = (fixuint_t)(a ^ s) + (-s);        // negate if s == -1
  fixuint_t res;
  ASSIGN_UMOD(res, a_u, b_u);
  return (res ^ s) + (-s);                          // negate if s == -1
}
#endif // ASSIGN_UMOD

#undef clz

// Returns: a % b

COMPILER_RT_ABI du_int __umoddi3(du_int a, du_int b) {
  return __umodXi3(a, b);
}

#undef fixuint_t
#undef fixint_t
//===-- umodsi3.c - Implement __umodsi3 -----------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
// 2024/08/10 - Modified by Mintsuki for use inside freestanding-lgrt
//
//===----------------------------------------------------------------------===//
//
// This file implements __umodsi3 for the compiler_rt library.
//
//===----------------------------------------------------------------------===//


#define fixuint_t su_int
#define fixint_t si_int
//===-- int_div_impl.inc - Integer division ---------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
// 2024/10/20 - Modified by Mintsuki for use inside freestanding-lgrt
//
//===----------------------------------------------------------------------===//
//
// Helpers used by __udivsi3, __umodsi3, __udivdi3, and __umodsi3.
//
//===----------------------------------------------------------------------===//

#define clz(a) (sizeof(a) == sizeof(unsigned long long) ? __builtin_clzll(a) : clzsi(a))

#undef __udivXi3
#define __udivXi3 __udivXi3_39

// Adapted from Figure 3-40 of The PowerPC Compiler Writer's Guide
static __inline fixuint_t __udivXi3(fixuint_t n, fixuint_t d) {
  const unsigned N = sizeof(fixuint_t) * CHAR_BIT;
  // d == 0 cases are unspecified.
  unsigned sr = (d ? clz(d) : N) - (n ? clz(n) : N);
  // 0 <= sr <= N - 1 or sr is very large.
  if (sr > N - 1) // n < d
    return 0;
  if (sr == N - 1) // d == 1
    return n;
  ++sr;
  // 1 <= sr <= N - 1. Shifts do not trigger UB.
  fixuint_t r = n >> sr;
  n <<= N - sr;
  fixuint_t carry = 0;
  for (; sr > 0; --sr) {
    r = (r << 1) | (n >> (N - 1));
    n = (n << 1) | carry;
    // Branch-less version of:
    // carry = 0;
    // if (r >= d) r -= d, carry = 1;
    const fixint_t s = (fixint_t)(d - r - 1) >> (N - 1);
    carry = s & 1;
    r -= d & s;
  }
  n = (n << 1) | carry;
  return n;
}

#undef __umodXi3
#define __umodXi3 __umodXi3_40

// Mostly identical to __udivXi3 but the return values are different.
static __inline fixuint_t __umodXi3(fixuint_t n, fixuint_t d) {
  const unsigned N = sizeof(fixuint_t) * CHAR_BIT;
  // d == 0 cases are unspecified.
  unsigned sr = (d ? clz(d) : N) - (n ? clz(n) : N);
  // 0 <= sr <= N - 1 or sr is very large.
  if (sr > N - 1) // n < d
    return n;
  if (sr == N - 1) // d == 1
    return 0;
  ++sr;
  // 1 <= sr <= N - 1. Shifts do not trigger UB.
  fixuint_t r = n >> sr;
  n <<= N - sr;
  fixuint_t carry = 0;
  for (; sr > 0; --sr) {
    r = (r << 1) | (n >> (N - 1));
    n = (n << 1) | carry;
    // Branch-less version of:
    // carry = 0;
    // if (r >= d) r -= d, carry = 1;
    const fixint_t s = (fixint_t)(d - r - 1) >> (N - 1);
    carry = s & 1;
    r -= d & s;
  }
  return r;
}

#undef __divXi3

#ifdef COMPUTE_UDIV

#define __divXi3 __divXi3_41

static __inline fixint_t __divXi3(fixint_t a, fixint_t b) {
  const int N = (int)(sizeof(fixint_t) * CHAR_BIT) - 1;
  fixint_t s_a = a >> N;                            // s_a = a < 0 ? -1 : 0
  fixint_t s_b = b >> N;                            // s_b = b < 0 ? -1 : 0
  fixuint_t a_u = (fixuint_t)(a ^ s_a) + (-s_a);    // negate if s_a == -1
  fixuint_t b_u = (fixuint_t)(b ^ s_b) + (-s_b);    // negate if s_b == -1
  s_a ^= s_b;                                       // sign of quotient
  return (COMPUTE_UDIV(a_u, b_u) ^ s_a) + (-s_a);   // negate if s_a == -1
}
#endif // COMPUTE_UDIV

#undef __modXi3

#ifdef ASSIGN_UMOD

#define __modXi3 __modXi3_42

static __inline fixint_t __modXi3(fixint_t a, fixint_t b) {
  const int N = (int)(sizeof(fixint_t) * CHAR_BIT) - 1;
  fixint_t s = b >> N;                              // s = b < 0 ? -1 : 0
  fixuint_t b_u = (fixuint_t)(b ^ s) + (-s);        // negate if s == -1
  s = a >> N;                                       // s = a < 0 ? -1 : 0
  fixuint_t a_u = (fixuint_t)(a ^ s) + (-s);        // negate if s == -1
  fixuint_t res;
  ASSIGN_UMOD(res, a_u, b_u);
  return (res ^ s) + (-s);                          // negate if s == -1
}
#endif // ASSIGN_UMOD

#undef clz

// Returns: a % b

COMPILER_RT_ABI su_int __umodsi3(su_int a, su_int b) {
  return __umodXi3(a, b);
}

#undef fixuint_t
#undef fixint_t
//===-- umodti3.c - Implement __umodti3 -----------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements __umodti3 for the compiler_rt library.
//
//===----------------------------------------------------------------------===//


#ifdef CRT_HAS_128BIT

// Returns: a % b

COMPILER_RT_ABI tu_int __umodti3(tu_int a, tu_int b) {
  tu_int r;
  __udivmodti4(a, b, &r);
  return r;
}

#endif // CRT_HAS_128BIT
#if defined(__aarch64__)
#define L_cas
#define SIZE 1
#define MODEL 1
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S b
#define UXT uxtb
#define B 0x00000000
#define SUFF _relax
#define A
#define L
#define M 0x000000
#define N 0x000000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) w(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(cas))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
);
#ifdef HAS_ASM_LSE
#define CAS GLUE4(cas, A, L, S) s(0), s(1), [x2]
#else
#define CAS .inst 0x08a07c41 + B + M
#endif
__asm__(
    "        " FREESTANDING_LGRT_ASM(CAS) "    \n"
    "        ret\n"
    "8:\n"
    "        " FREESTANDING_LGRT_ASM(UXT) "    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x2]\n"
    "        cmp    " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        bne    1f\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp1)) ", " FREESTANDING_LGRT_ASM(s(1)) ", [x2]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp1)) ", 0b\n"
    "1:\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(cas))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef CAS
#undef L_cas
#undef SIZE
#undef MODEL
#define L_cas
#define SIZE 1
#define MODEL 2
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S b
#define UXT uxtb
#define B 0x00000000
#define SUFF _acq
#define A a
#define L
#define M 0x400000
#define N 0x800000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) w(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(cas))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
);
#ifdef HAS_ASM_LSE
#define CAS GLUE4(cas, A, L, S) s(0), s(1), [x2]
#else
#define CAS .inst 0x08a07c41 + B + M
#endif
__asm__(
    "        " FREESTANDING_LGRT_ASM(CAS) "    \n"
    "        ret\n"
    "8:\n"
    "        " FREESTANDING_LGRT_ASM(UXT) "    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x2]\n"
    "        cmp    " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        bne    1f\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp1)) ", " FREESTANDING_LGRT_ASM(s(1)) ", [x2]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp1)) ", 0b\n"
    "1:\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(cas))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef CAS
#undef L_cas
#undef SIZE
#undef MODEL
#define L_cas
#define SIZE 1
#define MODEL 3
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S b
#define UXT uxtb
#define B 0x00000000
#define SUFF _rel
#define A
#define L l
#define M 0x008000
#define N 0x400000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) w(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(cas))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
);
#ifdef HAS_ASM_LSE
#define CAS GLUE4(cas, A, L, S) s(0), s(1), [x2]
#else
#define CAS .inst 0x08a07c41 + B + M
#endif
__asm__(
    "        " FREESTANDING_LGRT_ASM(CAS) "    \n"
    "        ret\n"
    "8:\n"
    "        " FREESTANDING_LGRT_ASM(UXT) "    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x2]\n"
    "        cmp    " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        bne    1f\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp1)) ", " FREESTANDING_LGRT_ASM(s(1)) ", [x2]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp1)) ", 0b\n"
    "1:\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(cas))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef CAS
#undef L_cas
#undef SIZE
#undef MODEL
#define L_cas
#define SIZE 1
#define MODEL 4
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S b
#define UXT uxtb
#define B 0x00000000
#define SUFF _acq_rel
#define A a
#define L l
#define M 0x408000
#define N 0xc00000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) w(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(cas))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
);
#ifdef HAS_ASM_LSE
#define CAS GLUE4(cas, A, L, S) s(0), s(1), [x2]
#else
#define CAS .inst 0x08a07c41 + B + M
#endif
__asm__(
    "        " FREESTANDING_LGRT_ASM(CAS) "    \n"
    "        ret\n"
    "8:\n"
    "        " FREESTANDING_LGRT_ASM(UXT) "    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x2]\n"
    "        cmp    " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        bne    1f\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp1)) ", " FREESTANDING_LGRT_ASM(s(1)) ", [x2]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp1)) ", 0b\n"
    "1:\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(cas))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef CAS
#undef L_cas
#undef SIZE
#undef MODEL
#define L_cas
#define SIZE 1
#define MODEL 5
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S b
#define UXT uxtb
#define B 0x00000000
#define SUFF _sync
#define A a
#define L l
#define M 0x408000
#define N 0xc00000
#define BARRIER dmb ish
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) w(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE3(ld, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(cas))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
);
#ifdef HAS_ASM_LSE
#define CAS GLUE4(cas, A, L, S) s(0), s(1), [x2]
#else
#define CAS .inst 0x08a07c41 + B + M
#endif
__asm__(
    "        " FREESTANDING_LGRT_ASM(CAS) "    \n"
    "        ret\n"
    "8:\n"
    "        " FREESTANDING_LGRT_ASM(UXT) "    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x2]\n"
    "        cmp    " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        bne    1f\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp1)) ", " FREESTANDING_LGRT_ASM(s(1)) ", [x2]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp1)) ", 0b\n"
    "1:\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(cas))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef CAS
#undef L_cas
#undef SIZE
#undef MODEL
#define L_cas
#define SIZE 2
#define MODEL 1
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S h
#define UXT uxth
#define B 0x40000000
#define SUFF _relax
#define A
#define L
#define M 0x000000
#define N 0x000000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) w(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(cas))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
);
#ifdef HAS_ASM_LSE
#define CAS GLUE4(cas, A, L, S) s(0), s(1), [x2]
#else
#define CAS .inst 0x08a07c41 + B + M
#endif
__asm__(
    "        " FREESTANDING_LGRT_ASM(CAS) "    \n"
    "        ret\n"
    "8:\n"
    "        " FREESTANDING_LGRT_ASM(UXT) "    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x2]\n"
    "        cmp    " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        bne    1f\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp1)) ", " FREESTANDING_LGRT_ASM(s(1)) ", [x2]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp1)) ", 0b\n"
    "1:\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(cas))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef CAS
#undef L_cas
#undef SIZE
#undef MODEL
#define L_cas
#define SIZE 2
#define MODEL 2
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S h
#define UXT uxth
#define B 0x40000000
#define SUFF _acq
#define A a
#define L
#define M 0x400000
#define N 0x800000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) w(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(cas))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
);
#ifdef HAS_ASM_LSE
#define CAS GLUE4(cas, A, L, S) s(0), s(1), [x2]
#else
#define CAS .inst 0x08a07c41 + B + M
#endif
__asm__(
    "        " FREESTANDING_LGRT_ASM(CAS) "    \n"
    "        ret\n"
    "8:\n"
    "        " FREESTANDING_LGRT_ASM(UXT) "    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x2]\n"
    "        cmp    " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        bne    1f\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp1)) ", " FREESTANDING_LGRT_ASM(s(1)) ", [x2]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp1)) ", 0b\n"
    "1:\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(cas))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef CAS
#undef L_cas
#undef SIZE
#undef MODEL
#define L_cas
#define SIZE 2
#define MODEL 3
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S h
#define UXT uxth
#define B 0x40000000
#define SUFF _rel
#define A
#define L l
#define M 0x008000
#define N 0x400000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) w(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(cas))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
);
#ifdef HAS_ASM_LSE
#define CAS GLUE4(cas, A, L, S) s(0), s(1), [x2]
#else
#define CAS .inst 0x08a07c41 + B + M
#endif
__asm__(
    "        " FREESTANDING_LGRT_ASM(CAS) "    \n"
    "        ret\n"
    "8:\n"
    "        " FREESTANDING_LGRT_ASM(UXT) "    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x2]\n"
    "        cmp    " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        bne    1f\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp1)) ", " FREESTANDING_LGRT_ASM(s(1)) ", [x2]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp1)) ", 0b\n"
    "1:\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(cas))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef CAS
#undef L_cas
#undef SIZE
#undef MODEL
#define L_cas
#define SIZE 2
#define MODEL 4
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S h
#define UXT uxth
#define B 0x40000000
#define SUFF _acq_rel
#define A a
#define L l
#define M 0x408000
#define N 0xc00000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) w(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(cas))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
);
#ifdef HAS_ASM_LSE
#define CAS GLUE4(cas, A, L, S) s(0), s(1), [x2]
#else
#define CAS .inst 0x08a07c41 + B + M
#endif
__asm__(
    "        " FREESTANDING_LGRT_ASM(CAS) "    \n"
    "        ret\n"
    "8:\n"
    "        " FREESTANDING_LGRT_ASM(UXT) "    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x2]\n"
    "        cmp    " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        bne    1f\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp1)) ", " FREESTANDING_LGRT_ASM(s(1)) ", [x2]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp1)) ", 0b\n"
    "1:\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(cas))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef CAS
#undef L_cas
#undef SIZE
#undef MODEL
#define L_cas
#define SIZE 2
#define MODEL 5
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S h
#define UXT uxth
#define B 0x40000000
#define SUFF _sync
#define A a
#define L l
#define M 0x408000
#define N 0xc00000
#define BARRIER dmb ish
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) w(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE3(ld, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(cas))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
);
#ifdef HAS_ASM_LSE
#define CAS GLUE4(cas, A, L, S) s(0), s(1), [x2]
#else
#define CAS .inst 0x08a07c41 + B + M
#endif
__asm__(
    "        " FREESTANDING_LGRT_ASM(CAS) "    \n"
    "        ret\n"
    "8:\n"
    "        " FREESTANDING_LGRT_ASM(UXT) "    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x2]\n"
    "        cmp    " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        bne    1f\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp1)) ", " FREESTANDING_LGRT_ASM(s(1)) ", [x2]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp1)) ", 0b\n"
    "1:\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(cas))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef CAS
#undef L_cas
#undef SIZE
#undef MODEL
#define L_cas
#define SIZE 4
#define MODEL 1
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S
#define UXT mov
#define B 0x80000000
#define SUFF _relax
#define A
#define L
#define M 0x000000
#define N 0x000000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) w(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(cas))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
);
#ifdef HAS_ASM_LSE
#define CAS GLUE4(cas, A, L, S) s(0), s(1), [x2]
#else
#define CAS .inst 0x08a07c41 + B + M
#endif
__asm__(
    "        " FREESTANDING_LGRT_ASM(CAS) "    \n"
    "        ret\n"
    "8:\n"
    "        " FREESTANDING_LGRT_ASM(UXT) "    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x2]\n"
    "        cmp    " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        bne    1f\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp1)) ", " FREESTANDING_LGRT_ASM(s(1)) ", [x2]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp1)) ", 0b\n"
    "1:\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(cas))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef CAS
#undef L_cas
#undef SIZE
#undef MODEL
#define L_cas
#define SIZE 4
#define MODEL 2
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S
#define UXT mov
#define B 0x80000000
#define SUFF _acq
#define A a
#define L
#define M 0x400000
#define N 0x800000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) w(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(cas))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
);
#ifdef HAS_ASM_LSE
#define CAS GLUE4(cas, A, L, S) s(0), s(1), [x2]
#else
#define CAS .inst 0x08a07c41 + B + M
#endif
__asm__(
    "        " FREESTANDING_LGRT_ASM(CAS) "    \n"
    "        ret\n"
    "8:\n"
    "        " FREESTANDING_LGRT_ASM(UXT) "    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x2]\n"
    "        cmp    " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        bne    1f\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp1)) ", " FREESTANDING_LGRT_ASM(s(1)) ", [x2]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp1)) ", 0b\n"
    "1:\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(cas))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef CAS
#undef L_cas
#undef SIZE
#undef MODEL
#define L_cas
#define SIZE 4
#define MODEL 3
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S
#define UXT mov
#define B 0x80000000
#define SUFF _rel
#define A
#define L l
#define M 0x008000
#define N 0x400000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) w(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(cas))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
);
#ifdef HAS_ASM_LSE
#define CAS GLUE4(cas, A, L, S) s(0), s(1), [x2]
#else
#define CAS .inst 0x08a07c41 + B + M
#endif
__asm__(
    "        " FREESTANDING_LGRT_ASM(CAS) "    \n"
    "        ret\n"
    "8:\n"
    "        " FREESTANDING_LGRT_ASM(UXT) "    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x2]\n"
    "        cmp    " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        bne    1f\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp1)) ", " FREESTANDING_LGRT_ASM(s(1)) ", [x2]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp1)) ", 0b\n"
    "1:\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(cas))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef CAS
#undef L_cas
#undef SIZE
#undef MODEL
#define L_cas
#define SIZE 4
#define MODEL 4
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S
#define UXT mov
#define B 0x80000000
#define SUFF _acq_rel
#define A a
#define L l
#define M 0x408000
#define N 0xc00000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) w(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(cas))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
);
#ifdef HAS_ASM_LSE
#define CAS GLUE4(cas, A, L, S) s(0), s(1), [x2]
#else
#define CAS .inst 0x08a07c41 + B + M
#endif
__asm__(
    "        " FREESTANDING_LGRT_ASM(CAS) "    \n"
    "        ret\n"
    "8:\n"
    "        " FREESTANDING_LGRT_ASM(UXT) "    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x2]\n"
    "        cmp    " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        bne    1f\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp1)) ", " FREESTANDING_LGRT_ASM(s(1)) ", [x2]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp1)) ", 0b\n"
    "1:\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(cas))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef CAS
#undef L_cas
#undef SIZE
#undef MODEL
#define L_cas
#define SIZE 4
#define MODEL 5
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S
#define UXT mov
#define B 0x80000000
#define SUFF _sync
#define A a
#define L l
#define M 0x408000
#define N 0xc00000
#define BARRIER dmb ish
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) w(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE3(ld, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(cas))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
);
#ifdef HAS_ASM_LSE
#define CAS GLUE4(cas, A, L, S) s(0), s(1), [x2]
#else
#define CAS .inst 0x08a07c41 + B + M
#endif
__asm__(
    "        " FREESTANDING_LGRT_ASM(CAS) "    \n"
    "        ret\n"
    "8:\n"
    "        " FREESTANDING_LGRT_ASM(UXT) "    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x2]\n"
    "        cmp    " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        bne    1f\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp1)) ", " FREESTANDING_LGRT_ASM(s(1)) ", [x2]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp1)) ", 0b\n"
    "1:\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(cas))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef CAS
#undef L_cas
#undef SIZE
#undef MODEL
#define L_cas
#define SIZE 8
#define MODEL 1
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S
#define UXT mov
#define B 0xc0000000
#define SUFF _relax
#define A
#define L
#define M 0x000000
#define N 0x000000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) x(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(cas))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
);
#ifdef HAS_ASM_LSE
#define CAS GLUE4(cas, A, L, S) s(0), s(1), [x2]
#else
#define CAS .inst 0x08a07c41 + B + M
#endif
__asm__(
    "        " FREESTANDING_LGRT_ASM(CAS) "    \n"
    "        ret\n"
    "8:\n"
    "        " FREESTANDING_LGRT_ASM(UXT) "    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x2]\n"
    "        cmp    " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        bne    1f\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp1)) ", " FREESTANDING_LGRT_ASM(s(1)) ", [x2]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp1)) ", 0b\n"
    "1:\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(cas))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef CAS
#undef L_cas
#undef SIZE
#undef MODEL
#define L_cas
#define SIZE 8
#define MODEL 2
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S
#define UXT mov
#define B 0xc0000000
#define SUFF _acq
#define A a
#define L
#define M 0x400000
#define N 0x800000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) x(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(cas))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
);
#ifdef HAS_ASM_LSE
#define CAS GLUE4(cas, A, L, S) s(0), s(1), [x2]
#else
#define CAS .inst 0x08a07c41 + B + M
#endif
__asm__(
    "        " FREESTANDING_LGRT_ASM(CAS) "    \n"
    "        ret\n"
    "8:\n"
    "        " FREESTANDING_LGRT_ASM(UXT) "    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x2]\n"
    "        cmp    " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        bne    1f\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp1)) ", " FREESTANDING_LGRT_ASM(s(1)) ", [x2]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp1)) ", 0b\n"
    "1:\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(cas))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef CAS
#undef L_cas
#undef SIZE
#undef MODEL
#define L_cas
#define SIZE 8
#define MODEL 3
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S
#define UXT mov
#define B 0xc0000000
#define SUFF _rel
#define A
#define L l
#define M 0x008000
#define N 0x400000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) x(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(cas))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
);
#ifdef HAS_ASM_LSE
#define CAS GLUE4(cas, A, L, S) s(0), s(1), [x2]
#else
#define CAS .inst 0x08a07c41 + B + M
#endif
__asm__(
    "        " FREESTANDING_LGRT_ASM(CAS) "    \n"
    "        ret\n"
    "8:\n"
    "        " FREESTANDING_LGRT_ASM(UXT) "    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x2]\n"
    "        cmp    " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        bne    1f\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp1)) ", " FREESTANDING_LGRT_ASM(s(1)) ", [x2]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp1)) ", 0b\n"
    "1:\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(cas))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef CAS
#undef L_cas
#undef SIZE
#undef MODEL
#define L_cas
#define SIZE 8
#define MODEL 4
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S
#define UXT mov
#define B 0xc0000000
#define SUFF _acq_rel
#define A a
#define L l
#define M 0x408000
#define N 0xc00000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) x(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(cas))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
);
#ifdef HAS_ASM_LSE
#define CAS GLUE4(cas, A, L, S) s(0), s(1), [x2]
#else
#define CAS .inst 0x08a07c41 + B + M
#endif
__asm__(
    "        " FREESTANDING_LGRT_ASM(CAS) "    \n"
    "        ret\n"
    "8:\n"
    "        " FREESTANDING_LGRT_ASM(UXT) "    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x2]\n"
    "        cmp    " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        bne    1f\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp1)) ", " FREESTANDING_LGRT_ASM(s(1)) ", [x2]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp1)) ", 0b\n"
    "1:\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(cas))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef CAS
#undef L_cas
#undef SIZE
#undef MODEL
#define L_cas
#define SIZE 8
#define MODEL 5
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S
#define UXT mov
#define B 0xc0000000
#define SUFF _sync
#define A a
#define L l
#define M 0x408000
#define N 0xc00000
#define BARRIER dmb ish
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) x(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE3(ld, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(cas))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
);
#ifdef HAS_ASM_LSE
#define CAS GLUE4(cas, A, L, S) s(0), s(1), [x2]
#else
#define CAS .inst 0x08a07c41 + B + M
#endif
__asm__(
    "        " FREESTANDING_LGRT_ASM(CAS) "    \n"
    "        ret\n"
    "8:\n"
    "        " FREESTANDING_LGRT_ASM(UXT) "    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x2]\n"
    "        cmp    " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        bne    1f\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp1)) ", " FREESTANDING_LGRT_ASM(s(1)) ", [x2]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp1)) ", 0b\n"
    "1:\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(cas))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef CAS
#undef L_cas
#undef SIZE
#undef MODEL
#define L_cas
#define SIZE 16
#define MODEL 1
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S
#define UXT mov
#define SUFF _relax
#define A
#define L
#define M 0x000000
#define N 0x000000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) x(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(cas))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
);
#define LDXP GLUE3(ld, A, xp)
#define STXP GLUE3(st, L, xp)
#ifdef HAS_ASM_LSE
#define CASP GLUE3(casp, A, L)  x0, x1, x2, x3, [x4]
#else
#define CASP .inst 0x48207c82 + M
#endif
__asm__(
    "        " FREESTANDING_LGRT_ASM(CASP) "   \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(x(tmp0)) ", x0\n"
    "        mov    " FREESTANDING_LGRT_ASM(x(tmp1)) ", x1\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXP) "   x0, x1, [x4]\n"
    "        cmp    x0, " FREESTANDING_LGRT_ASM(x(tmp0)) "\n"
    "        ccmp   x1, " FREESTANDING_LGRT_ASM(x(tmp1)) ", #0, eq\n"
    "        bne    1f\n"
    "        " FREESTANDING_LGRT_ASM(STXP) "   " FREESTANDING_LGRT_ASM(w(tmp2)) ", x2, x3, [x4]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp2)) ", 0b\n"
    "1:\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(cas))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef LDXP
#undef STXP
#undef CASP
#undef L_cas
#undef SIZE
#undef MODEL
#define L_cas
#define SIZE 16
#define MODEL 2
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S
#define UXT mov
#define SUFF _acq
#define A a
#define L
#define M 0x400000
#define N 0x800000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) x(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(cas))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
);
#define LDXP GLUE3(ld, A, xp)
#define STXP GLUE3(st, L, xp)
#ifdef HAS_ASM_LSE
#define CASP GLUE3(casp, A, L)  x0, x1, x2, x3, [x4]
#else
#define CASP .inst 0x48207c82 + M
#endif
__asm__(
    "        " FREESTANDING_LGRT_ASM(CASP) "   \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(x(tmp0)) ", x0\n"
    "        mov    " FREESTANDING_LGRT_ASM(x(tmp1)) ", x1\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXP) "   x0, x1, [x4]\n"
    "        cmp    x0, " FREESTANDING_LGRT_ASM(x(tmp0)) "\n"
    "        ccmp   x1, " FREESTANDING_LGRT_ASM(x(tmp1)) ", #0, eq\n"
    "        bne    1f\n"
    "        " FREESTANDING_LGRT_ASM(STXP) "   " FREESTANDING_LGRT_ASM(w(tmp2)) ", x2, x3, [x4]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp2)) ", 0b\n"
    "1:\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(cas))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef LDXP
#undef STXP
#undef CASP
#undef L_cas
#undef SIZE
#undef MODEL
#define L_cas
#define SIZE 16
#define MODEL 3
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S
#define UXT mov
#define SUFF _rel
#define A
#define L l
#define M 0x008000
#define N 0x400000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) x(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(cas))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
);
#define LDXP GLUE3(ld, A, xp)
#define STXP GLUE3(st, L, xp)
#ifdef HAS_ASM_LSE
#define CASP GLUE3(casp, A, L)  x0, x1, x2, x3, [x4]
#else
#define CASP .inst 0x48207c82 + M
#endif
__asm__(
    "        " FREESTANDING_LGRT_ASM(CASP) "   \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(x(tmp0)) ", x0\n"
    "        mov    " FREESTANDING_LGRT_ASM(x(tmp1)) ", x1\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXP) "   x0, x1, [x4]\n"
    "        cmp    x0, " FREESTANDING_LGRT_ASM(x(tmp0)) "\n"
    "        ccmp   x1, " FREESTANDING_LGRT_ASM(x(tmp1)) ", #0, eq\n"
    "        bne    1f\n"
    "        " FREESTANDING_LGRT_ASM(STXP) "   " FREESTANDING_LGRT_ASM(w(tmp2)) ", x2, x3, [x4]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp2)) ", 0b\n"
    "1:\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(cas))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef LDXP
#undef STXP
#undef CASP
#undef L_cas
#undef SIZE
#undef MODEL
#define L_cas
#define SIZE 16
#define MODEL 4
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S
#define UXT mov
#define SUFF _acq_rel
#define A a
#define L l
#define M 0x408000
#define N 0xc00000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) x(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(cas))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
);
#define LDXP GLUE3(ld, A, xp)
#define STXP GLUE3(st, L, xp)
#ifdef HAS_ASM_LSE
#define CASP GLUE3(casp, A, L)  x0, x1, x2, x3, [x4]
#else
#define CASP .inst 0x48207c82 + M
#endif
__asm__(
    "        " FREESTANDING_LGRT_ASM(CASP) "   \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(x(tmp0)) ", x0\n"
    "        mov    " FREESTANDING_LGRT_ASM(x(tmp1)) ", x1\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXP) "   x0, x1, [x4]\n"
    "        cmp    x0, " FREESTANDING_LGRT_ASM(x(tmp0)) "\n"
    "        ccmp   x1, " FREESTANDING_LGRT_ASM(x(tmp1)) ", #0, eq\n"
    "        bne    1f\n"
    "        " FREESTANDING_LGRT_ASM(STXP) "   " FREESTANDING_LGRT_ASM(w(tmp2)) ", x2, x3, [x4]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp2)) ", 0b\n"
    "1:\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(cas))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef LDXP
#undef STXP
#undef CASP
#undef L_cas
#undef SIZE
#undef MODEL
#define L_cas
#define SIZE 16
#define MODEL 5
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S
#define UXT mov
#define SUFF _sync
#define A a
#define L l
#define M 0x408000
#define N 0xc00000
#define BARRIER dmb ish
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) x(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE3(ld, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(cas))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
);
#define LDXP GLUE2(ld, xp)
#define STXP GLUE3(st, L, xp)
#ifdef HAS_ASM_LSE
#define CASP GLUE3(casp, A, L)  x0, x1, x2, x3, [x4]
#else
#define CASP .inst 0x48207c82 + M
#endif
__asm__(
    "        " FREESTANDING_LGRT_ASM(CASP) "   \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(x(tmp0)) ", x0\n"
    "        mov    " FREESTANDING_LGRT_ASM(x(tmp1)) ", x1\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXP) "   x0, x1, [x4]\n"
    "        cmp    x0, " FREESTANDING_LGRT_ASM(x(tmp0)) "\n"
    "        ccmp   x1, " FREESTANDING_LGRT_ASM(x(tmp1)) ", #0, eq\n"
    "        bne    1f\n"
    "        " FREESTANDING_LGRT_ASM(STXP) "   " FREESTANDING_LGRT_ASM(w(tmp2)) ", x2, x3, [x4]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp2)) ", 0b\n"
    "1:\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(cas))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef LDXP
#undef STXP
#undef CASP
#undef L_cas
#undef SIZE
#undef MODEL
#define L_swp
#define SIZE 1
#define MODEL 1
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S b
#define UXT uxtb
#define B 0x00000000
#define SUFF _relax
#define A
#define L
#define M 0x000000
#define N 0x000000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) w(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#ifdef HAS_ASM_LSE
#define SWP GLUE4(swp, A, L, S)  s(0), s(0), [x1]
#else
#define SWP .inst 0x38208020 + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(swp))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(SWP) "    \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp1)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp1)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(swp))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef SWP
#undef L_swp
#undef SIZE
#undef MODEL
#define L_swp
#define SIZE 1
#define MODEL 2
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S b
#define UXT uxtb
#define B 0x00000000
#define SUFF _acq
#define A a
#define L
#define M 0x400000
#define N 0x800000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) w(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#ifdef HAS_ASM_LSE
#define SWP GLUE4(swp, A, L, S)  s(0), s(0), [x1]
#else
#define SWP .inst 0x38208020 + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(swp))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(SWP) "    \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp1)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp1)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(swp))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef SWP
#undef L_swp
#undef SIZE
#undef MODEL
#define L_swp
#define SIZE 1
#define MODEL 3
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S b
#define UXT uxtb
#define B 0x00000000
#define SUFF _rel
#define A
#define L l
#define M 0x008000
#define N 0x400000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) w(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#ifdef HAS_ASM_LSE
#define SWP GLUE4(swp, A, L, S)  s(0), s(0), [x1]
#else
#define SWP .inst 0x38208020 + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(swp))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(SWP) "    \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp1)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp1)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(swp))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef SWP
#undef L_swp
#undef SIZE
#undef MODEL
#define L_swp
#define SIZE 1
#define MODEL 4
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S b
#define UXT uxtb
#define B 0x00000000
#define SUFF _acq_rel
#define A a
#define L l
#define M 0x408000
#define N 0xc00000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) w(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#ifdef HAS_ASM_LSE
#define SWP GLUE4(swp, A, L, S)  s(0), s(0), [x1]
#else
#define SWP .inst 0x38208020 + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(swp))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(SWP) "    \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp1)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp1)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(swp))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef SWP
#undef L_swp
#undef SIZE
#undef MODEL
#define L_swp
#define SIZE 1
#define MODEL 5
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S b
#define UXT uxtb
#define B 0x00000000
#define SUFF _sync
#define A a
#define L
#define M 0x400000
#define N 0x800000
#define BARRIER dmb ish
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) w(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE3(ld, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#ifdef HAS_ASM_LSE
#define SWP GLUE4(swp, A, L, S)  s(0), s(0), [x1]
#else
#define SWP .inst 0x38208020 + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(swp))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(SWP) "    \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp1)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp1)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(swp))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef SWP
#undef L_swp
#undef SIZE
#undef MODEL
#define L_swp
#define SIZE 2
#define MODEL 1
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S h
#define UXT uxth
#define B 0x40000000
#define SUFF _relax
#define A
#define L
#define M 0x000000
#define N 0x000000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) w(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#ifdef HAS_ASM_LSE
#define SWP GLUE4(swp, A, L, S)  s(0), s(0), [x1]
#else
#define SWP .inst 0x38208020 + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(swp))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(SWP) "    \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp1)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp1)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(swp))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef SWP
#undef L_swp
#undef SIZE
#undef MODEL
#define L_swp
#define SIZE 2
#define MODEL 2
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S h
#define UXT uxth
#define B 0x40000000
#define SUFF _acq
#define A a
#define L
#define M 0x400000
#define N 0x800000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) w(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#ifdef HAS_ASM_LSE
#define SWP GLUE4(swp, A, L, S)  s(0), s(0), [x1]
#else
#define SWP .inst 0x38208020 + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(swp))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(SWP) "    \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp1)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp1)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(swp))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef SWP
#undef L_swp
#undef SIZE
#undef MODEL
#define L_swp
#define SIZE 2
#define MODEL 3
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S h
#define UXT uxth
#define B 0x40000000
#define SUFF _rel
#define A
#define L l
#define M 0x008000
#define N 0x400000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) w(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#ifdef HAS_ASM_LSE
#define SWP GLUE4(swp, A, L, S)  s(0), s(0), [x1]
#else
#define SWP .inst 0x38208020 + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(swp))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(SWP) "    \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp1)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp1)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(swp))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef SWP
#undef L_swp
#undef SIZE
#undef MODEL
#define L_swp
#define SIZE 2
#define MODEL 4
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S h
#define UXT uxth
#define B 0x40000000
#define SUFF _acq_rel
#define A a
#define L l
#define M 0x408000
#define N 0xc00000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) w(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#ifdef HAS_ASM_LSE
#define SWP GLUE4(swp, A, L, S)  s(0), s(0), [x1]
#else
#define SWP .inst 0x38208020 + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(swp))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(SWP) "    \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp1)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp1)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(swp))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef SWP
#undef L_swp
#undef SIZE
#undef MODEL
#define L_swp
#define SIZE 2
#define MODEL 5
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S h
#define UXT uxth
#define B 0x40000000
#define SUFF _sync
#define A a
#define L
#define M 0x400000
#define N 0x800000
#define BARRIER dmb ish
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) w(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE3(ld, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#ifdef HAS_ASM_LSE
#define SWP GLUE4(swp, A, L, S)  s(0), s(0), [x1]
#else
#define SWP .inst 0x38208020 + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(swp))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(SWP) "    \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp1)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp1)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(swp))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef SWP
#undef L_swp
#undef SIZE
#undef MODEL
#define L_swp
#define SIZE 4
#define MODEL 1
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S
#define UXT mov
#define B 0x80000000
#define SUFF _relax
#define A
#define L
#define M 0x000000
#define N 0x000000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) w(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#ifdef HAS_ASM_LSE
#define SWP GLUE4(swp, A, L, S)  s(0), s(0), [x1]
#else
#define SWP .inst 0x38208020 + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(swp))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(SWP) "    \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp1)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp1)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(swp))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef SWP
#undef L_swp
#undef SIZE
#undef MODEL
#define L_swp
#define SIZE 4
#define MODEL 2
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S
#define UXT mov
#define B 0x80000000
#define SUFF _acq
#define A a
#define L
#define M 0x400000
#define N 0x800000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) w(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#ifdef HAS_ASM_LSE
#define SWP GLUE4(swp, A, L, S)  s(0), s(0), [x1]
#else
#define SWP .inst 0x38208020 + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(swp))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(SWP) "    \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp1)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp1)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(swp))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef SWP
#undef L_swp
#undef SIZE
#undef MODEL
#define L_swp
#define SIZE 4
#define MODEL 3
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S
#define UXT mov
#define B 0x80000000
#define SUFF _rel
#define A
#define L l
#define M 0x008000
#define N 0x400000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) w(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#ifdef HAS_ASM_LSE
#define SWP GLUE4(swp, A, L, S)  s(0), s(0), [x1]
#else
#define SWP .inst 0x38208020 + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(swp))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(SWP) "    \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp1)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp1)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(swp))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef SWP
#undef L_swp
#undef SIZE
#undef MODEL
#define L_swp
#define SIZE 4
#define MODEL 4
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S
#define UXT mov
#define B 0x80000000
#define SUFF _acq_rel
#define A a
#define L l
#define M 0x408000
#define N 0xc00000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) w(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#ifdef HAS_ASM_LSE
#define SWP GLUE4(swp, A, L, S)  s(0), s(0), [x1]
#else
#define SWP .inst 0x38208020 + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(swp))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(SWP) "    \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp1)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp1)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(swp))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef SWP
#undef L_swp
#undef SIZE
#undef MODEL
#define L_swp
#define SIZE 4
#define MODEL 5
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S
#define UXT mov
#define B 0x80000000
#define SUFF _sync
#define A a
#define L
#define M 0x400000
#define N 0x800000
#define BARRIER dmb ish
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) w(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE3(ld, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#ifdef HAS_ASM_LSE
#define SWP GLUE4(swp, A, L, S)  s(0), s(0), [x1]
#else
#define SWP .inst 0x38208020 + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(swp))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(SWP) "    \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp1)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp1)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(swp))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef SWP
#undef L_swp
#undef SIZE
#undef MODEL
#define L_swp
#define SIZE 8
#define MODEL 1
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S
#define UXT mov
#define B 0xc0000000
#define SUFF _relax
#define A
#define L
#define M 0x000000
#define N 0x000000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) x(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#ifdef HAS_ASM_LSE
#define SWP GLUE4(swp, A, L, S)  s(0), s(0), [x1]
#else
#define SWP .inst 0x38208020 + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(swp))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(SWP) "    \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp1)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp1)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(swp))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef SWP
#undef L_swp
#undef SIZE
#undef MODEL
#define L_swp
#define SIZE 8
#define MODEL 2
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S
#define UXT mov
#define B 0xc0000000
#define SUFF _acq
#define A a
#define L
#define M 0x400000
#define N 0x800000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) x(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#ifdef HAS_ASM_LSE
#define SWP GLUE4(swp, A, L, S)  s(0), s(0), [x1]
#else
#define SWP .inst 0x38208020 + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(swp))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(SWP) "    \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp1)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp1)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(swp))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef SWP
#undef L_swp
#undef SIZE
#undef MODEL
#define L_swp
#define SIZE 8
#define MODEL 3
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S
#define UXT mov
#define B 0xc0000000
#define SUFF _rel
#define A
#define L l
#define M 0x008000
#define N 0x400000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) x(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#ifdef HAS_ASM_LSE
#define SWP GLUE4(swp, A, L, S)  s(0), s(0), [x1]
#else
#define SWP .inst 0x38208020 + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(swp))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(SWP) "    \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp1)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp1)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(swp))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef SWP
#undef L_swp
#undef SIZE
#undef MODEL
#define L_swp
#define SIZE 8
#define MODEL 4
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S
#define UXT mov
#define B 0xc0000000
#define SUFF _acq_rel
#define A a
#define L l
#define M 0x408000
#define N 0xc00000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) x(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#ifdef HAS_ASM_LSE
#define SWP GLUE4(swp, A, L, S)  s(0), s(0), [x1]
#else
#define SWP .inst 0x38208020 + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(swp))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(SWP) "    \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp1)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp1)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(swp))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef SWP
#undef L_swp
#undef SIZE
#undef MODEL
#define L_swp
#define SIZE 8
#define MODEL 5
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S
#define UXT mov
#define B 0xc0000000
#define SUFF _sync
#define A a
#define L
#define M 0x400000
#define N 0x800000
#define BARRIER dmb ish
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) x(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE3(ld, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#ifdef HAS_ASM_LSE
#define SWP GLUE4(swp, A, L, S)  s(0), s(0), [x1]
#else
#define SWP .inst 0x38208020 + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(swp))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(SWP) "    \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp1)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp1)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(swp))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef SWP
#undef L_swp
#undef SIZE
#undef MODEL
#define L_ldadd
#define SIZE 1
#define MODEL 1
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S b
#define UXT uxtb
#define B 0x00000000
#define SUFF _relax
#define A
#define L
#define M 0x000000
#define N 0x000000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) w(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#define LDNM ldadd
#define OP add
#define OPN 0x0000
#ifdef HAS_ASM_LSE
#define LDOP GLUE4(LDNM, A, L, S) s(0), s(0), [x1]
#else
#define LDOP .inst 0x38200020 + OPN + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(LDNM))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(LDOP) " \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(OP) "     " FREESTANDING_LGRT_ASM(s(tmp1)) ", " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp2)) ", " FREESTANDING_LGRT_ASM(s(tmp1)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp2)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(LDNM))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef LDNM
#undef OP
#undef OPN
#undef LDOP
#undef L_ldadd
#undef SIZE
#undef MODEL
#define L_ldadd
#define SIZE 1
#define MODEL 2
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S b
#define UXT uxtb
#define B 0x00000000
#define SUFF _acq
#define A a
#define L
#define M 0x400000
#define N 0x800000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) w(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#define LDNM ldadd
#define OP add
#define OPN 0x0000
#ifdef HAS_ASM_LSE
#define LDOP GLUE4(LDNM, A, L, S) s(0), s(0), [x1]
#else
#define LDOP .inst 0x38200020 + OPN + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(LDNM))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(LDOP) " \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(OP) "     " FREESTANDING_LGRT_ASM(s(tmp1)) ", " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp2)) ", " FREESTANDING_LGRT_ASM(s(tmp1)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp2)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(LDNM))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef LDNM
#undef OP
#undef OPN
#undef LDOP
#undef L_ldadd
#undef SIZE
#undef MODEL
#define L_ldadd
#define SIZE 1
#define MODEL 3
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S b
#define UXT uxtb
#define B 0x00000000
#define SUFF _rel
#define A
#define L l
#define M 0x008000
#define N 0x400000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) w(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#define LDNM ldadd
#define OP add
#define OPN 0x0000
#ifdef HAS_ASM_LSE
#define LDOP GLUE4(LDNM, A, L, S) s(0), s(0), [x1]
#else
#define LDOP .inst 0x38200020 + OPN + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(LDNM))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(LDOP) " \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(OP) "     " FREESTANDING_LGRT_ASM(s(tmp1)) ", " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp2)) ", " FREESTANDING_LGRT_ASM(s(tmp1)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp2)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(LDNM))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef LDNM
#undef OP
#undef OPN
#undef LDOP
#undef L_ldadd
#undef SIZE
#undef MODEL
#define L_ldadd
#define SIZE 1
#define MODEL 4
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S b
#define UXT uxtb
#define B 0x00000000
#define SUFF _acq_rel
#define A a
#define L l
#define M 0x408000
#define N 0xc00000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) w(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#define LDNM ldadd
#define OP add
#define OPN 0x0000
#ifdef HAS_ASM_LSE
#define LDOP GLUE4(LDNM, A, L, S) s(0), s(0), [x1]
#else
#define LDOP .inst 0x38200020 + OPN + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(LDNM))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(LDOP) " \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(OP) "     " FREESTANDING_LGRT_ASM(s(tmp1)) ", " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp2)) ", " FREESTANDING_LGRT_ASM(s(tmp1)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp2)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(LDNM))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef LDNM
#undef OP
#undef OPN
#undef LDOP
#undef L_ldadd
#undef SIZE
#undef MODEL
#define L_ldadd
#define SIZE 1
#define MODEL 5
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S b
#define UXT uxtb
#define B 0x00000000
#define SUFF _sync
#define A a
#define L l
#define M 0x408000
#define N 0xc00000
#define BARRIER dmb ish
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) w(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE3(ld, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#define LDNM ldadd
#define OP add
#define OPN 0x0000
#ifdef HAS_ASM_LSE
#define LDOP GLUE4(LDNM, A, L, S) s(0), s(0), [x1]
#else
#define LDOP .inst 0x38200020 + OPN + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(LDNM))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(LDOP) " \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(OP) "     " FREESTANDING_LGRT_ASM(s(tmp1)) ", " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp2)) ", " FREESTANDING_LGRT_ASM(s(tmp1)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp2)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(LDNM))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef LDNM
#undef OP
#undef OPN
#undef LDOP
#undef L_ldadd
#undef SIZE
#undef MODEL
#define L_ldadd
#define SIZE 2
#define MODEL 1
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S h
#define UXT uxth
#define B 0x40000000
#define SUFF _relax
#define A
#define L
#define M 0x000000
#define N 0x000000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) w(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#define LDNM ldadd
#define OP add
#define OPN 0x0000
#ifdef HAS_ASM_LSE
#define LDOP GLUE4(LDNM, A, L, S) s(0), s(0), [x1]
#else
#define LDOP .inst 0x38200020 + OPN + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(LDNM))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(LDOP) " \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(OP) "     " FREESTANDING_LGRT_ASM(s(tmp1)) ", " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp2)) ", " FREESTANDING_LGRT_ASM(s(tmp1)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp2)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(LDNM))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef LDNM
#undef OP
#undef OPN
#undef LDOP
#undef L_ldadd
#undef SIZE
#undef MODEL
#define L_ldadd
#define SIZE 2
#define MODEL 2
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S h
#define UXT uxth
#define B 0x40000000
#define SUFF _acq
#define A a
#define L
#define M 0x400000
#define N 0x800000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) w(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#define LDNM ldadd
#define OP add
#define OPN 0x0000
#ifdef HAS_ASM_LSE
#define LDOP GLUE4(LDNM, A, L, S) s(0), s(0), [x1]
#else
#define LDOP .inst 0x38200020 + OPN + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(LDNM))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(LDOP) " \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(OP) "     " FREESTANDING_LGRT_ASM(s(tmp1)) ", " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp2)) ", " FREESTANDING_LGRT_ASM(s(tmp1)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp2)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(LDNM))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef LDNM
#undef OP
#undef OPN
#undef LDOP
#undef L_ldadd
#undef SIZE
#undef MODEL
#define L_ldadd
#define SIZE 2
#define MODEL 3
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S h
#define UXT uxth
#define B 0x40000000
#define SUFF _rel
#define A
#define L l
#define M 0x008000
#define N 0x400000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) w(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#define LDNM ldadd
#define OP add
#define OPN 0x0000
#ifdef HAS_ASM_LSE
#define LDOP GLUE4(LDNM, A, L, S) s(0), s(0), [x1]
#else
#define LDOP .inst 0x38200020 + OPN + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(LDNM))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(LDOP) " \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(OP) "     " FREESTANDING_LGRT_ASM(s(tmp1)) ", " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp2)) ", " FREESTANDING_LGRT_ASM(s(tmp1)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp2)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(LDNM))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef LDNM
#undef OP
#undef OPN
#undef LDOP
#undef L_ldadd
#undef SIZE
#undef MODEL
#define L_ldadd
#define SIZE 2
#define MODEL 4
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S h
#define UXT uxth
#define B 0x40000000
#define SUFF _acq_rel
#define A a
#define L l
#define M 0x408000
#define N 0xc00000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) w(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#define LDNM ldadd
#define OP add
#define OPN 0x0000
#ifdef HAS_ASM_LSE
#define LDOP GLUE4(LDNM, A, L, S) s(0), s(0), [x1]
#else
#define LDOP .inst 0x38200020 + OPN + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(LDNM))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(LDOP) " \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(OP) "     " FREESTANDING_LGRT_ASM(s(tmp1)) ", " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp2)) ", " FREESTANDING_LGRT_ASM(s(tmp1)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp2)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(LDNM))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef LDNM
#undef OP
#undef OPN
#undef LDOP
#undef L_ldadd
#undef SIZE
#undef MODEL
#define L_ldadd
#define SIZE 2
#define MODEL 5
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S h
#define UXT uxth
#define B 0x40000000
#define SUFF _sync
#define A a
#define L l
#define M 0x408000
#define N 0xc00000
#define BARRIER dmb ish
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) w(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE3(ld, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#define LDNM ldadd
#define OP add
#define OPN 0x0000
#ifdef HAS_ASM_LSE
#define LDOP GLUE4(LDNM, A, L, S) s(0), s(0), [x1]
#else
#define LDOP .inst 0x38200020 + OPN + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(LDNM))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(LDOP) " \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(OP) "     " FREESTANDING_LGRT_ASM(s(tmp1)) ", " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp2)) ", " FREESTANDING_LGRT_ASM(s(tmp1)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp2)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(LDNM))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef LDNM
#undef OP
#undef OPN
#undef LDOP
#undef L_ldadd
#undef SIZE
#undef MODEL
#define L_ldadd
#define SIZE 4
#define MODEL 1
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S
#define UXT mov
#define B 0x80000000
#define SUFF _relax
#define A
#define L
#define M 0x000000
#define N 0x000000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) w(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#define LDNM ldadd
#define OP add
#define OPN 0x0000
#ifdef HAS_ASM_LSE
#define LDOP GLUE4(LDNM, A, L, S) s(0), s(0), [x1]
#else
#define LDOP .inst 0x38200020 + OPN + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(LDNM))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(LDOP) " \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(OP) "     " FREESTANDING_LGRT_ASM(s(tmp1)) ", " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp2)) ", " FREESTANDING_LGRT_ASM(s(tmp1)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp2)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(LDNM))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef LDNM
#undef OP
#undef OPN
#undef LDOP
#undef L_ldadd
#undef SIZE
#undef MODEL
#define L_ldadd
#define SIZE 4
#define MODEL 2
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S
#define UXT mov
#define B 0x80000000
#define SUFF _acq
#define A a
#define L
#define M 0x400000
#define N 0x800000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) w(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#define LDNM ldadd
#define OP add
#define OPN 0x0000
#ifdef HAS_ASM_LSE
#define LDOP GLUE4(LDNM, A, L, S) s(0), s(0), [x1]
#else
#define LDOP .inst 0x38200020 + OPN + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(LDNM))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(LDOP) " \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(OP) "     " FREESTANDING_LGRT_ASM(s(tmp1)) ", " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp2)) ", " FREESTANDING_LGRT_ASM(s(tmp1)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp2)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(LDNM))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef LDNM
#undef OP
#undef OPN
#undef LDOP
#undef L_ldadd
#undef SIZE
#undef MODEL
#define L_ldadd
#define SIZE 4
#define MODEL 3
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S
#define UXT mov
#define B 0x80000000
#define SUFF _rel
#define A
#define L l
#define M 0x008000
#define N 0x400000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) w(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#define LDNM ldadd
#define OP add
#define OPN 0x0000
#ifdef HAS_ASM_LSE
#define LDOP GLUE4(LDNM, A, L, S) s(0), s(0), [x1]
#else
#define LDOP .inst 0x38200020 + OPN + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(LDNM))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(LDOP) " \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(OP) "     " FREESTANDING_LGRT_ASM(s(tmp1)) ", " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp2)) ", " FREESTANDING_LGRT_ASM(s(tmp1)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp2)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(LDNM))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef LDNM
#undef OP
#undef OPN
#undef LDOP
#undef L_ldadd
#undef SIZE
#undef MODEL
#define L_ldadd
#define SIZE 4
#define MODEL 4
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S
#define UXT mov
#define B 0x80000000
#define SUFF _acq_rel
#define A a
#define L l
#define M 0x408000
#define N 0xc00000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) w(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#define LDNM ldadd
#define OP add
#define OPN 0x0000
#ifdef HAS_ASM_LSE
#define LDOP GLUE4(LDNM, A, L, S) s(0), s(0), [x1]
#else
#define LDOP .inst 0x38200020 + OPN + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(LDNM))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(LDOP) " \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(OP) "     " FREESTANDING_LGRT_ASM(s(tmp1)) ", " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp2)) ", " FREESTANDING_LGRT_ASM(s(tmp1)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp2)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(LDNM))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef LDNM
#undef OP
#undef OPN
#undef LDOP
#undef L_ldadd
#undef SIZE
#undef MODEL
#define L_ldadd
#define SIZE 4
#define MODEL 5
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S
#define UXT mov
#define B 0x80000000
#define SUFF _sync
#define A a
#define L l
#define M 0x408000
#define N 0xc00000
#define BARRIER dmb ish
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) w(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE3(ld, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#define LDNM ldadd
#define OP add
#define OPN 0x0000
#ifdef HAS_ASM_LSE
#define LDOP GLUE4(LDNM, A, L, S) s(0), s(0), [x1]
#else
#define LDOP .inst 0x38200020 + OPN + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(LDNM))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(LDOP) " \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(OP) "     " FREESTANDING_LGRT_ASM(s(tmp1)) ", " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp2)) ", " FREESTANDING_LGRT_ASM(s(tmp1)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp2)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(LDNM))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef LDNM
#undef OP
#undef OPN
#undef LDOP
#undef L_ldadd
#undef SIZE
#undef MODEL
#define L_ldadd
#define SIZE 8
#define MODEL 1
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S
#define UXT mov
#define B 0xc0000000
#define SUFF _relax
#define A
#define L
#define M 0x000000
#define N 0x000000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) x(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#define LDNM ldadd
#define OP add
#define OPN 0x0000
#ifdef HAS_ASM_LSE
#define LDOP GLUE4(LDNM, A, L, S) s(0), s(0), [x1]
#else
#define LDOP .inst 0x38200020 + OPN + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(LDNM))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(LDOP) " \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(OP) "     " FREESTANDING_LGRT_ASM(s(tmp1)) ", " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp2)) ", " FREESTANDING_LGRT_ASM(s(tmp1)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp2)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(LDNM))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef LDNM
#undef OP
#undef OPN
#undef LDOP
#undef L_ldadd
#undef SIZE
#undef MODEL
#define L_ldadd
#define SIZE 8
#define MODEL 2
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S
#define UXT mov
#define B 0xc0000000
#define SUFF _acq
#define A a
#define L
#define M 0x400000
#define N 0x800000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) x(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#define LDNM ldadd
#define OP add
#define OPN 0x0000
#ifdef HAS_ASM_LSE
#define LDOP GLUE4(LDNM, A, L, S) s(0), s(0), [x1]
#else
#define LDOP .inst 0x38200020 + OPN + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(LDNM))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(LDOP) " \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(OP) "     " FREESTANDING_LGRT_ASM(s(tmp1)) ", " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp2)) ", " FREESTANDING_LGRT_ASM(s(tmp1)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp2)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(LDNM))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef LDNM
#undef OP
#undef OPN
#undef LDOP
#undef L_ldadd
#undef SIZE
#undef MODEL
#define L_ldadd
#define SIZE 8
#define MODEL 3
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S
#define UXT mov
#define B 0xc0000000
#define SUFF _rel
#define A
#define L l
#define M 0x008000
#define N 0x400000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) x(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#define LDNM ldadd
#define OP add
#define OPN 0x0000
#ifdef HAS_ASM_LSE
#define LDOP GLUE4(LDNM, A, L, S) s(0), s(0), [x1]
#else
#define LDOP .inst 0x38200020 + OPN + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(LDNM))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(LDOP) " \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(OP) "     " FREESTANDING_LGRT_ASM(s(tmp1)) ", " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp2)) ", " FREESTANDING_LGRT_ASM(s(tmp1)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp2)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(LDNM))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef LDNM
#undef OP
#undef OPN
#undef LDOP
#undef L_ldadd
#undef SIZE
#undef MODEL
#define L_ldadd
#define SIZE 8
#define MODEL 4
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S
#define UXT mov
#define B 0xc0000000
#define SUFF _acq_rel
#define A a
#define L l
#define M 0x408000
#define N 0xc00000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) x(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#define LDNM ldadd
#define OP add
#define OPN 0x0000
#ifdef HAS_ASM_LSE
#define LDOP GLUE4(LDNM, A, L, S) s(0), s(0), [x1]
#else
#define LDOP .inst 0x38200020 + OPN + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(LDNM))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(LDOP) " \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(OP) "     " FREESTANDING_LGRT_ASM(s(tmp1)) ", " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp2)) ", " FREESTANDING_LGRT_ASM(s(tmp1)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp2)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(LDNM))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef LDNM
#undef OP
#undef OPN
#undef LDOP
#undef L_ldadd
#undef SIZE
#undef MODEL
#define L_ldadd
#define SIZE 8
#define MODEL 5
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S
#define UXT mov
#define B 0xc0000000
#define SUFF _sync
#define A a
#define L l
#define M 0x408000
#define N 0xc00000
#define BARRIER dmb ish
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) x(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE3(ld, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#define LDNM ldadd
#define OP add
#define OPN 0x0000
#ifdef HAS_ASM_LSE
#define LDOP GLUE4(LDNM, A, L, S) s(0), s(0), [x1]
#else
#define LDOP .inst 0x38200020 + OPN + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(LDNM))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(LDOP) " \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(OP) "     " FREESTANDING_LGRT_ASM(s(tmp1)) ", " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp2)) ", " FREESTANDING_LGRT_ASM(s(tmp1)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp2)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(LDNM))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef LDNM
#undef OP
#undef OPN
#undef LDOP
#undef L_ldadd
#undef SIZE
#undef MODEL
#define L_ldclr
#define SIZE 1
#define MODEL 1
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S b
#define UXT uxtb
#define B 0x00000000
#define SUFF _relax
#define A
#define L
#define M 0x000000
#define N 0x000000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) w(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#define LDNM ldclr
#define OP bic
#define OPN 0x1000
#ifdef HAS_ASM_LSE
#define LDOP GLUE4(LDNM, A, L, S) s(0), s(0), [x1]
#else
#define LDOP .inst 0x38200020 + OPN + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(LDNM))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(LDOP) " \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(OP) "     " FREESTANDING_LGRT_ASM(s(tmp1)) ", " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp2)) ", " FREESTANDING_LGRT_ASM(s(tmp1)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp2)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(LDNM))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef LDNM
#undef OP
#undef OPN
#undef LDOP
#undef L_ldclr
#undef SIZE
#undef MODEL
#define L_ldclr
#define SIZE 1
#define MODEL 2
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S b
#define UXT uxtb
#define B 0x00000000
#define SUFF _acq
#define A a
#define L
#define M 0x400000
#define N 0x800000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) w(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#define LDNM ldclr
#define OP bic
#define OPN 0x1000
#ifdef HAS_ASM_LSE
#define LDOP GLUE4(LDNM, A, L, S) s(0), s(0), [x1]
#else
#define LDOP .inst 0x38200020 + OPN + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(LDNM))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(LDOP) " \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(OP) "     " FREESTANDING_LGRT_ASM(s(tmp1)) ", " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp2)) ", " FREESTANDING_LGRT_ASM(s(tmp1)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp2)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(LDNM))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef LDNM
#undef OP
#undef OPN
#undef LDOP
#undef L_ldclr
#undef SIZE
#undef MODEL
#define L_ldclr
#define SIZE 1
#define MODEL 3
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S b
#define UXT uxtb
#define B 0x00000000
#define SUFF _rel
#define A
#define L l
#define M 0x008000
#define N 0x400000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) w(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#define LDNM ldclr
#define OP bic
#define OPN 0x1000
#ifdef HAS_ASM_LSE
#define LDOP GLUE4(LDNM, A, L, S) s(0), s(0), [x1]
#else
#define LDOP .inst 0x38200020 + OPN + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(LDNM))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(LDOP) " \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(OP) "     " FREESTANDING_LGRT_ASM(s(tmp1)) ", " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp2)) ", " FREESTANDING_LGRT_ASM(s(tmp1)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp2)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(LDNM))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef LDNM
#undef OP
#undef OPN
#undef LDOP
#undef L_ldclr
#undef SIZE
#undef MODEL
#define L_ldclr
#define SIZE 1
#define MODEL 4
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S b
#define UXT uxtb
#define B 0x00000000
#define SUFF _acq_rel
#define A a
#define L l
#define M 0x408000
#define N 0xc00000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) w(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#define LDNM ldclr
#define OP bic
#define OPN 0x1000
#ifdef HAS_ASM_LSE
#define LDOP GLUE4(LDNM, A, L, S) s(0), s(0), [x1]
#else
#define LDOP .inst 0x38200020 + OPN + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(LDNM))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(LDOP) " \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(OP) "     " FREESTANDING_LGRT_ASM(s(tmp1)) ", " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp2)) ", " FREESTANDING_LGRT_ASM(s(tmp1)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp2)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(LDNM))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef LDNM
#undef OP
#undef OPN
#undef LDOP
#undef L_ldclr
#undef SIZE
#undef MODEL
#define L_ldclr
#define SIZE 1
#define MODEL 5
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S b
#define UXT uxtb
#define B 0x00000000
#define SUFF _sync
#define A a
#define L l
#define M 0x408000
#define N 0xc00000
#define BARRIER dmb ish
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) w(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE3(ld, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#define LDNM ldclr
#define OP bic
#define OPN 0x1000
#ifdef HAS_ASM_LSE
#define LDOP GLUE4(LDNM, A, L, S) s(0), s(0), [x1]
#else
#define LDOP .inst 0x38200020 + OPN + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(LDNM))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(LDOP) " \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(OP) "     " FREESTANDING_LGRT_ASM(s(tmp1)) ", " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp2)) ", " FREESTANDING_LGRT_ASM(s(tmp1)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp2)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(LDNM))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef LDNM
#undef OP
#undef OPN
#undef LDOP
#undef L_ldclr
#undef SIZE
#undef MODEL
#define L_ldclr
#define SIZE 2
#define MODEL 1
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S h
#define UXT uxth
#define B 0x40000000
#define SUFF _relax
#define A
#define L
#define M 0x000000
#define N 0x000000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) w(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#define LDNM ldclr
#define OP bic
#define OPN 0x1000
#ifdef HAS_ASM_LSE
#define LDOP GLUE4(LDNM, A, L, S) s(0), s(0), [x1]
#else
#define LDOP .inst 0x38200020 + OPN + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(LDNM))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(LDOP) " \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(OP) "     " FREESTANDING_LGRT_ASM(s(tmp1)) ", " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp2)) ", " FREESTANDING_LGRT_ASM(s(tmp1)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp2)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(LDNM))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef LDNM
#undef OP
#undef OPN
#undef LDOP
#undef L_ldclr
#undef SIZE
#undef MODEL
#define L_ldclr
#define SIZE 2
#define MODEL 2
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S h
#define UXT uxth
#define B 0x40000000
#define SUFF _acq
#define A a
#define L
#define M 0x400000
#define N 0x800000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) w(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#define LDNM ldclr
#define OP bic
#define OPN 0x1000
#ifdef HAS_ASM_LSE
#define LDOP GLUE4(LDNM, A, L, S) s(0), s(0), [x1]
#else
#define LDOP .inst 0x38200020 + OPN + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(LDNM))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(LDOP) " \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(OP) "     " FREESTANDING_LGRT_ASM(s(tmp1)) ", " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp2)) ", " FREESTANDING_LGRT_ASM(s(tmp1)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp2)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(LDNM))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef LDNM
#undef OP
#undef OPN
#undef LDOP
#undef L_ldclr
#undef SIZE
#undef MODEL
#define L_ldclr
#define SIZE 2
#define MODEL 3
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S h
#define UXT uxth
#define B 0x40000000
#define SUFF _rel
#define A
#define L l
#define M 0x008000
#define N 0x400000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) w(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#define LDNM ldclr
#define OP bic
#define OPN 0x1000
#ifdef HAS_ASM_LSE
#define LDOP GLUE4(LDNM, A, L, S) s(0), s(0), [x1]
#else
#define LDOP .inst 0x38200020 + OPN + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(LDNM))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(LDOP) " \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(OP) "     " FREESTANDING_LGRT_ASM(s(tmp1)) ", " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp2)) ", " FREESTANDING_LGRT_ASM(s(tmp1)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp2)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(LDNM))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef LDNM
#undef OP
#undef OPN
#undef LDOP
#undef L_ldclr
#undef SIZE
#undef MODEL
#define L_ldclr
#define SIZE 2
#define MODEL 4
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S h
#define UXT uxth
#define B 0x40000000
#define SUFF _acq_rel
#define A a
#define L l
#define M 0x408000
#define N 0xc00000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) w(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#define LDNM ldclr
#define OP bic
#define OPN 0x1000
#ifdef HAS_ASM_LSE
#define LDOP GLUE4(LDNM, A, L, S) s(0), s(0), [x1]
#else
#define LDOP .inst 0x38200020 + OPN + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(LDNM))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(LDOP) " \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(OP) "     " FREESTANDING_LGRT_ASM(s(tmp1)) ", " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp2)) ", " FREESTANDING_LGRT_ASM(s(tmp1)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp2)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(LDNM))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef LDNM
#undef OP
#undef OPN
#undef LDOP
#undef L_ldclr
#undef SIZE
#undef MODEL
#define L_ldclr
#define SIZE 2
#define MODEL 5
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S h
#define UXT uxth
#define B 0x40000000
#define SUFF _sync
#define A a
#define L l
#define M 0x408000
#define N 0xc00000
#define BARRIER dmb ish
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) w(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE3(ld, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#define LDNM ldclr
#define OP bic
#define OPN 0x1000
#ifdef HAS_ASM_LSE
#define LDOP GLUE4(LDNM, A, L, S) s(0), s(0), [x1]
#else
#define LDOP .inst 0x38200020 + OPN + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(LDNM))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(LDOP) " \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(OP) "     " FREESTANDING_LGRT_ASM(s(tmp1)) ", " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp2)) ", " FREESTANDING_LGRT_ASM(s(tmp1)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp2)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(LDNM))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef LDNM
#undef OP
#undef OPN
#undef LDOP
#undef L_ldclr
#undef SIZE
#undef MODEL
#define L_ldclr
#define SIZE 4
#define MODEL 1
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S
#define UXT mov
#define B 0x80000000
#define SUFF _relax
#define A
#define L
#define M 0x000000
#define N 0x000000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) w(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#define LDNM ldclr
#define OP bic
#define OPN 0x1000
#ifdef HAS_ASM_LSE
#define LDOP GLUE4(LDNM, A, L, S) s(0), s(0), [x1]
#else
#define LDOP .inst 0x38200020 + OPN + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(LDNM))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(LDOP) " \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(OP) "     " FREESTANDING_LGRT_ASM(s(tmp1)) ", " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp2)) ", " FREESTANDING_LGRT_ASM(s(tmp1)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp2)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(LDNM))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef LDNM
#undef OP
#undef OPN
#undef LDOP
#undef L_ldclr
#undef SIZE
#undef MODEL
#define L_ldclr
#define SIZE 4
#define MODEL 2
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S
#define UXT mov
#define B 0x80000000
#define SUFF _acq
#define A a
#define L
#define M 0x400000
#define N 0x800000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) w(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#define LDNM ldclr
#define OP bic
#define OPN 0x1000
#ifdef HAS_ASM_LSE
#define LDOP GLUE4(LDNM, A, L, S) s(0), s(0), [x1]
#else
#define LDOP .inst 0x38200020 + OPN + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(LDNM))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(LDOP) " \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(OP) "     " FREESTANDING_LGRT_ASM(s(tmp1)) ", " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp2)) ", " FREESTANDING_LGRT_ASM(s(tmp1)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp2)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(LDNM))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef LDNM
#undef OP
#undef OPN
#undef LDOP
#undef L_ldclr
#undef SIZE
#undef MODEL
#define L_ldclr
#define SIZE 4
#define MODEL 3
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S
#define UXT mov
#define B 0x80000000
#define SUFF _rel
#define A
#define L l
#define M 0x008000
#define N 0x400000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) w(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#define LDNM ldclr
#define OP bic
#define OPN 0x1000
#ifdef HAS_ASM_LSE
#define LDOP GLUE4(LDNM, A, L, S) s(0), s(0), [x1]
#else
#define LDOP .inst 0x38200020 + OPN + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(LDNM))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(LDOP) " \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(OP) "     " FREESTANDING_LGRT_ASM(s(tmp1)) ", " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp2)) ", " FREESTANDING_LGRT_ASM(s(tmp1)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp2)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(LDNM))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef LDNM
#undef OP
#undef OPN
#undef LDOP
#undef L_ldclr
#undef SIZE
#undef MODEL
#define L_ldclr
#define SIZE 4
#define MODEL 4
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S
#define UXT mov
#define B 0x80000000
#define SUFF _acq_rel
#define A a
#define L l
#define M 0x408000
#define N 0xc00000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) w(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#define LDNM ldclr
#define OP bic
#define OPN 0x1000
#ifdef HAS_ASM_LSE
#define LDOP GLUE4(LDNM, A, L, S) s(0), s(0), [x1]
#else
#define LDOP .inst 0x38200020 + OPN + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(LDNM))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(LDOP) " \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(OP) "     " FREESTANDING_LGRT_ASM(s(tmp1)) ", " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp2)) ", " FREESTANDING_LGRT_ASM(s(tmp1)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp2)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(LDNM))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef LDNM
#undef OP
#undef OPN
#undef LDOP
#undef L_ldclr
#undef SIZE
#undef MODEL
#define L_ldclr
#define SIZE 4
#define MODEL 5
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S
#define UXT mov
#define B 0x80000000
#define SUFF _sync
#define A a
#define L l
#define M 0x408000
#define N 0xc00000
#define BARRIER dmb ish
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) w(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE3(ld, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#define LDNM ldclr
#define OP bic
#define OPN 0x1000
#ifdef HAS_ASM_LSE
#define LDOP GLUE4(LDNM, A, L, S) s(0), s(0), [x1]
#else
#define LDOP .inst 0x38200020 + OPN + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(LDNM))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(LDOP) " \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(OP) "     " FREESTANDING_LGRT_ASM(s(tmp1)) ", " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp2)) ", " FREESTANDING_LGRT_ASM(s(tmp1)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp2)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(LDNM))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef LDNM
#undef OP
#undef OPN
#undef LDOP
#undef L_ldclr
#undef SIZE
#undef MODEL
#define L_ldclr
#define SIZE 8
#define MODEL 1
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S
#define UXT mov
#define B 0xc0000000
#define SUFF _relax
#define A
#define L
#define M 0x000000
#define N 0x000000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) x(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#define LDNM ldclr
#define OP bic
#define OPN 0x1000
#ifdef HAS_ASM_LSE
#define LDOP GLUE4(LDNM, A, L, S) s(0), s(0), [x1]
#else
#define LDOP .inst 0x38200020 + OPN + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(LDNM))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(LDOP) " \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(OP) "     " FREESTANDING_LGRT_ASM(s(tmp1)) ", " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp2)) ", " FREESTANDING_LGRT_ASM(s(tmp1)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp2)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(LDNM))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef LDNM
#undef OP
#undef OPN
#undef LDOP
#undef L_ldclr
#undef SIZE
#undef MODEL
#define L_ldclr
#define SIZE 8
#define MODEL 2
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S
#define UXT mov
#define B 0xc0000000
#define SUFF _acq
#define A a
#define L
#define M 0x400000
#define N 0x800000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) x(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#define LDNM ldclr
#define OP bic
#define OPN 0x1000
#ifdef HAS_ASM_LSE
#define LDOP GLUE4(LDNM, A, L, S) s(0), s(0), [x1]
#else
#define LDOP .inst 0x38200020 + OPN + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(LDNM))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(LDOP) " \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(OP) "     " FREESTANDING_LGRT_ASM(s(tmp1)) ", " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp2)) ", " FREESTANDING_LGRT_ASM(s(tmp1)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp2)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(LDNM))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef LDNM
#undef OP
#undef OPN
#undef LDOP
#undef L_ldclr
#undef SIZE
#undef MODEL
#define L_ldclr
#define SIZE 8
#define MODEL 3
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S
#define UXT mov
#define B 0xc0000000
#define SUFF _rel
#define A
#define L l
#define M 0x008000
#define N 0x400000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) x(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#define LDNM ldclr
#define OP bic
#define OPN 0x1000
#ifdef HAS_ASM_LSE
#define LDOP GLUE4(LDNM, A, L, S) s(0), s(0), [x1]
#else
#define LDOP .inst 0x38200020 + OPN + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(LDNM))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(LDOP) " \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(OP) "     " FREESTANDING_LGRT_ASM(s(tmp1)) ", " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp2)) ", " FREESTANDING_LGRT_ASM(s(tmp1)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp2)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(LDNM))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef LDNM
#undef OP
#undef OPN
#undef LDOP
#undef L_ldclr
#undef SIZE
#undef MODEL
#define L_ldclr
#define SIZE 8
#define MODEL 4
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S
#define UXT mov
#define B 0xc0000000
#define SUFF _acq_rel
#define A a
#define L l
#define M 0x408000
#define N 0xc00000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) x(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#define LDNM ldclr
#define OP bic
#define OPN 0x1000
#ifdef HAS_ASM_LSE
#define LDOP GLUE4(LDNM, A, L, S) s(0), s(0), [x1]
#else
#define LDOP .inst 0x38200020 + OPN + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(LDNM))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(LDOP) " \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(OP) "     " FREESTANDING_LGRT_ASM(s(tmp1)) ", " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp2)) ", " FREESTANDING_LGRT_ASM(s(tmp1)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp2)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(LDNM))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef LDNM
#undef OP
#undef OPN
#undef LDOP
#undef L_ldclr
#undef SIZE
#undef MODEL
#define L_ldclr
#define SIZE 8
#define MODEL 5
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S
#define UXT mov
#define B 0xc0000000
#define SUFF _sync
#define A a
#define L l
#define M 0x408000
#define N 0xc00000
#define BARRIER dmb ish
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) x(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE3(ld, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#define LDNM ldclr
#define OP bic
#define OPN 0x1000
#ifdef HAS_ASM_LSE
#define LDOP GLUE4(LDNM, A, L, S) s(0), s(0), [x1]
#else
#define LDOP .inst 0x38200020 + OPN + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(LDNM))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(LDOP) " \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(OP) "     " FREESTANDING_LGRT_ASM(s(tmp1)) ", " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp2)) ", " FREESTANDING_LGRT_ASM(s(tmp1)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp2)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(LDNM))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef LDNM
#undef OP
#undef OPN
#undef LDOP
#undef L_ldclr
#undef SIZE
#undef MODEL
#define L_ldeor
#define SIZE 1
#define MODEL 1
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S b
#define UXT uxtb
#define B 0x00000000
#define SUFF _relax
#define A
#define L
#define M 0x000000
#define N 0x000000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) w(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#define LDNM ldeor
#define OP eor
#define OPN 0x2000
#ifdef HAS_ASM_LSE
#define LDOP GLUE4(LDNM, A, L, S) s(0), s(0), [x1]
#else
#define LDOP .inst 0x38200020 + OPN + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(LDNM))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(LDOP) " \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(OP) "     " FREESTANDING_LGRT_ASM(s(tmp1)) ", " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp2)) ", " FREESTANDING_LGRT_ASM(s(tmp1)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp2)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(LDNM))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef LDNM
#undef OP
#undef OPN
#undef LDOP
#undef L_ldeor
#undef SIZE
#undef MODEL
#define L_ldeor
#define SIZE 1
#define MODEL 2
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S b
#define UXT uxtb
#define B 0x00000000
#define SUFF _acq
#define A a
#define L
#define M 0x400000
#define N 0x800000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) w(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#define LDNM ldeor
#define OP eor
#define OPN 0x2000
#ifdef HAS_ASM_LSE
#define LDOP GLUE4(LDNM, A, L, S) s(0), s(0), [x1]
#else
#define LDOP .inst 0x38200020 + OPN + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(LDNM))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(LDOP) " \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(OP) "     " FREESTANDING_LGRT_ASM(s(tmp1)) ", " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp2)) ", " FREESTANDING_LGRT_ASM(s(tmp1)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp2)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(LDNM))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef LDNM
#undef OP
#undef OPN
#undef LDOP
#undef L_ldeor
#undef SIZE
#undef MODEL
#define L_ldeor
#define SIZE 1
#define MODEL 3
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S b
#define UXT uxtb
#define B 0x00000000
#define SUFF _rel
#define A
#define L l
#define M 0x008000
#define N 0x400000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) w(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#define LDNM ldeor
#define OP eor
#define OPN 0x2000
#ifdef HAS_ASM_LSE
#define LDOP GLUE4(LDNM, A, L, S) s(0), s(0), [x1]
#else
#define LDOP .inst 0x38200020 + OPN + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(LDNM))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(LDOP) " \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(OP) "     " FREESTANDING_LGRT_ASM(s(tmp1)) ", " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp2)) ", " FREESTANDING_LGRT_ASM(s(tmp1)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp2)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(LDNM))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef LDNM
#undef OP
#undef OPN
#undef LDOP
#undef L_ldeor
#undef SIZE
#undef MODEL
#define L_ldeor
#define SIZE 1
#define MODEL 4
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S b
#define UXT uxtb
#define B 0x00000000
#define SUFF _acq_rel
#define A a
#define L l
#define M 0x408000
#define N 0xc00000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) w(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#define LDNM ldeor
#define OP eor
#define OPN 0x2000
#ifdef HAS_ASM_LSE
#define LDOP GLUE4(LDNM, A, L, S) s(0), s(0), [x1]
#else
#define LDOP .inst 0x38200020 + OPN + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(LDNM))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(LDOP) " \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(OP) "     " FREESTANDING_LGRT_ASM(s(tmp1)) ", " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp2)) ", " FREESTANDING_LGRT_ASM(s(tmp1)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp2)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(LDNM))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef LDNM
#undef OP
#undef OPN
#undef LDOP
#undef L_ldeor
#undef SIZE
#undef MODEL
#define L_ldeor
#define SIZE 1
#define MODEL 5
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S b
#define UXT uxtb
#define B 0x00000000
#define SUFF _sync
#define A a
#define L l
#define M 0x408000
#define N 0xc00000
#define BARRIER dmb ish
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) w(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE3(ld, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#define LDNM ldeor
#define OP eor
#define OPN 0x2000
#ifdef HAS_ASM_LSE
#define LDOP GLUE4(LDNM, A, L, S) s(0), s(0), [x1]
#else
#define LDOP .inst 0x38200020 + OPN + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(LDNM))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(LDOP) " \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(OP) "     " FREESTANDING_LGRT_ASM(s(tmp1)) ", " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp2)) ", " FREESTANDING_LGRT_ASM(s(tmp1)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp2)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(LDNM))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef LDNM
#undef OP
#undef OPN
#undef LDOP
#undef L_ldeor
#undef SIZE
#undef MODEL
#define L_ldeor
#define SIZE 2
#define MODEL 1
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S h
#define UXT uxth
#define B 0x40000000
#define SUFF _relax
#define A
#define L
#define M 0x000000
#define N 0x000000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) w(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#define LDNM ldeor
#define OP eor
#define OPN 0x2000
#ifdef HAS_ASM_LSE
#define LDOP GLUE4(LDNM, A, L, S) s(0), s(0), [x1]
#else
#define LDOP .inst 0x38200020 + OPN + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(LDNM))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(LDOP) " \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(OP) "     " FREESTANDING_LGRT_ASM(s(tmp1)) ", " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp2)) ", " FREESTANDING_LGRT_ASM(s(tmp1)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp2)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(LDNM))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef LDNM
#undef OP
#undef OPN
#undef LDOP
#undef L_ldeor
#undef SIZE
#undef MODEL
#define L_ldeor
#define SIZE 2
#define MODEL 2
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S h
#define UXT uxth
#define B 0x40000000
#define SUFF _acq
#define A a
#define L
#define M 0x400000
#define N 0x800000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) w(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#define LDNM ldeor
#define OP eor
#define OPN 0x2000
#ifdef HAS_ASM_LSE
#define LDOP GLUE4(LDNM, A, L, S) s(0), s(0), [x1]
#else
#define LDOP .inst 0x38200020 + OPN + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(LDNM))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(LDOP) " \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(OP) "     " FREESTANDING_LGRT_ASM(s(tmp1)) ", " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp2)) ", " FREESTANDING_LGRT_ASM(s(tmp1)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp2)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(LDNM))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef LDNM
#undef OP
#undef OPN
#undef LDOP
#undef L_ldeor
#undef SIZE
#undef MODEL
#define L_ldeor
#define SIZE 2
#define MODEL 3
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S h
#define UXT uxth
#define B 0x40000000
#define SUFF _rel
#define A
#define L l
#define M 0x008000
#define N 0x400000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) w(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#define LDNM ldeor
#define OP eor
#define OPN 0x2000
#ifdef HAS_ASM_LSE
#define LDOP GLUE4(LDNM, A, L, S) s(0), s(0), [x1]
#else
#define LDOP .inst 0x38200020 + OPN + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(LDNM))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(LDOP) " \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(OP) "     " FREESTANDING_LGRT_ASM(s(tmp1)) ", " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp2)) ", " FREESTANDING_LGRT_ASM(s(tmp1)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp2)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(LDNM))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef LDNM
#undef OP
#undef OPN
#undef LDOP
#undef L_ldeor
#undef SIZE
#undef MODEL
#define L_ldeor
#define SIZE 2
#define MODEL 4
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S h
#define UXT uxth
#define B 0x40000000
#define SUFF _acq_rel
#define A a
#define L l
#define M 0x408000
#define N 0xc00000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) w(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#define LDNM ldeor
#define OP eor
#define OPN 0x2000
#ifdef HAS_ASM_LSE
#define LDOP GLUE4(LDNM, A, L, S) s(0), s(0), [x1]
#else
#define LDOP .inst 0x38200020 + OPN + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(LDNM))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(LDOP) " \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(OP) "     " FREESTANDING_LGRT_ASM(s(tmp1)) ", " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp2)) ", " FREESTANDING_LGRT_ASM(s(tmp1)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp2)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(LDNM))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef LDNM
#undef OP
#undef OPN
#undef LDOP
#undef L_ldeor
#undef SIZE
#undef MODEL
#define L_ldeor
#define SIZE 2
#define MODEL 5
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S h
#define UXT uxth
#define B 0x40000000
#define SUFF _sync
#define A a
#define L l
#define M 0x408000
#define N 0xc00000
#define BARRIER dmb ish
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) w(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE3(ld, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#define LDNM ldeor
#define OP eor
#define OPN 0x2000
#ifdef HAS_ASM_LSE
#define LDOP GLUE4(LDNM, A, L, S) s(0), s(0), [x1]
#else
#define LDOP .inst 0x38200020 + OPN + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(LDNM))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(LDOP) " \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(OP) "     " FREESTANDING_LGRT_ASM(s(tmp1)) ", " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp2)) ", " FREESTANDING_LGRT_ASM(s(tmp1)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp2)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(LDNM))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef LDNM
#undef OP
#undef OPN
#undef LDOP
#undef L_ldeor
#undef SIZE
#undef MODEL
#define L_ldeor
#define SIZE 4
#define MODEL 1
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S
#define UXT mov
#define B 0x80000000
#define SUFF _relax
#define A
#define L
#define M 0x000000
#define N 0x000000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) w(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#define LDNM ldeor
#define OP eor
#define OPN 0x2000
#ifdef HAS_ASM_LSE
#define LDOP GLUE4(LDNM, A, L, S) s(0), s(0), [x1]
#else
#define LDOP .inst 0x38200020 + OPN + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(LDNM))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(LDOP) " \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(OP) "     " FREESTANDING_LGRT_ASM(s(tmp1)) ", " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp2)) ", " FREESTANDING_LGRT_ASM(s(tmp1)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp2)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(LDNM))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef LDNM
#undef OP
#undef OPN
#undef LDOP
#undef L_ldeor
#undef SIZE
#undef MODEL
#define L_ldeor
#define SIZE 4
#define MODEL 2
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S
#define UXT mov
#define B 0x80000000
#define SUFF _acq
#define A a
#define L
#define M 0x400000
#define N 0x800000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) w(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#define LDNM ldeor
#define OP eor
#define OPN 0x2000
#ifdef HAS_ASM_LSE
#define LDOP GLUE4(LDNM, A, L, S) s(0), s(0), [x1]
#else
#define LDOP .inst 0x38200020 + OPN + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(LDNM))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(LDOP) " \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(OP) "     " FREESTANDING_LGRT_ASM(s(tmp1)) ", " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp2)) ", " FREESTANDING_LGRT_ASM(s(tmp1)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp2)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(LDNM))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef LDNM
#undef OP
#undef OPN
#undef LDOP
#undef L_ldeor
#undef SIZE
#undef MODEL
#define L_ldeor
#define SIZE 4
#define MODEL 3
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S
#define UXT mov
#define B 0x80000000
#define SUFF _rel
#define A
#define L l
#define M 0x008000
#define N 0x400000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) w(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#define LDNM ldeor
#define OP eor
#define OPN 0x2000
#ifdef HAS_ASM_LSE
#define LDOP GLUE4(LDNM, A, L, S) s(0), s(0), [x1]
#else
#define LDOP .inst 0x38200020 + OPN + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(LDNM))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(LDOP) " \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(OP) "     " FREESTANDING_LGRT_ASM(s(tmp1)) ", " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp2)) ", " FREESTANDING_LGRT_ASM(s(tmp1)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp2)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(LDNM))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef LDNM
#undef OP
#undef OPN
#undef LDOP
#undef L_ldeor
#undef SIZE
#undef MODEL
#define L_ldeor
#define SIZE 4
#define MODEL 4
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S
#define UXT mov
#define B 0x80000000
#define SUFF _acq_rel
#define A a
#define L l
#define M 0x408000
#define N 0xc00000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) w(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#define LDNM ldeor
#define OP eor
#define OPN 0x2000
#ifdef HAS_ASM_LSE
#define LDOP GLUE4(LDNM, A, L, S) s(0), s(0), [x1]
#else
#define LDOP .inst 0x38200020 + OPN + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(LDNM))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(LDOP) " \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(OP) "     " FREESTANDING_LGRT_ASM(s(tmp1)) ", " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp2)) ", " FREESTANDING_LGRT_ASM(s(tmp1)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp2)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(LDNM))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef LDNM
#undef OP
#undef OPN
#undef LDOP
#undef L_ldeor
#undef SIZE
#undef MODEL
#define L_ldeor
#define SIZE 4
#define MODEL 5
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S
#define UXT mov
#define B 0x80000000
#define SUFF _sync
#define A a
#define L l
#define M 0x408000
#define N 0xc00000
#define BARRIER dmb ish
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) w(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE3(ld, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#define LDNM ldeor
#define OP eor
#define OPN 0x2000
#ifdef HAS_ASM_LSE
#define LDOP GLUE4(LDNM, A, L, S) s(0), s(0), [x1]
#else
#define LDOP .inst 0x38200020 + OPN + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(LDNM))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(LDOP) " \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(OP) "     " FREESTANDING_LGRT_ASM(s(tmp1)) ", " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp2)) ", " FREESTANDING_LGRT_ASM(s(tmp1)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp2)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(LDNM))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef LDNM
#undef OP
#undef OPN
#undef LDOP
#undef L_ldeor
#undef SIZE
#undef MODEL
#define L_ldeor
#define SIZE 8
#define MODEL 1
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S
#define UXT mov
#define B 0xc0000000
#define SUFF _relax
#define A
#define L
#define M 0x000000
#define N 0x000000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) x(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#define LDNM ldeor
#define OP eor
#define OPN 0x2000
#ifdef HAS_ASM_LSE
#define LDOP GLUE4(LDNM, A, L, S) s(0), s(0), [x1]
#else
#define LDOP .inst 0x38200020 + OPN + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(LDNM))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(LDOP) " \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(OP) "     " FREESTANDING_LGRT_ASM(s(tmp1)) ", " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp2)) ", " FREESTANDING_LGRT_ASM(s(tmp1)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp2)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(LDNM))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef LDNM
#undef OP
#undef OPN
#undef LDOP
#undef L_ldeor
#undef SIZE
#undef MODEL
#define L_ldeor
#define SIZE 8
#define MODEL 2
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S
#define UXT mov
#define B 0xc0000000
#define SUFF _acq
#define A a
#define L
#define M 0x400000
#define N 0x800000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) x(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#define LDNM ldeor
#define OP eor
#define OPN 0x2000
#ifdef HAS_ASM_LSE
#define LDOP GLUE4(LDNM, A, L, S) s(0), s(0), [x1]
#else
#define LDOP .inst 0x38200020 + OPN + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(LDNM))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(LDOP) " \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(OP) "     " FREESTANDING_LGRT_ASM(s(tmp1)) ", " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp2)) ", " FREESTANDING_LGRT_ASM(s(tmp1)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp2)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(LDNM))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef LDNM
#undef OP
#undef OPN
#undef LDOP
#undef L_ldeor
#undef SIZE
#undef MODEL
#define L_ldeor
#define SIZE 8
#define MODEL 3
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S
#define UXT mov
#define B 0xc0000000
#define SUFF _rel
#define A
#define L l
#define M 0x008000
#define N 0x400000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) x(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#define LDNM ldeor
#define OP eor
#define OPN 0x2000
#ifdef HAS_ASM_LSE
#define LDOP GLUE4(LDNM, A, L, S) s(0), s(0), [x1]
#else
#define LDOP .inst 0x38200020 + OPN + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(LDNM))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(LDOP) " \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(OP) "     " FREESTANDING_LGRT_ASM(s(tmp1)) ", " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp2)) ", " FREESTANDING_LGRT_ASM(s(tmp1)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp2)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(LDNM))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef LDNM
#undef OP
#undef OPN
#undef LDOP
#undef L_ldeor
#undef SIZE
#undef MODEL
#define L_ldeor
#define SIZE 8
#define MODEL 4
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S
#define UXT mov
#define B 0xc0000000
#define SUFF _acq_rel
#define A a
#define L l
#define M 0x408000
#define N 0xc00000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) x(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#define LDNM ldeor
#define OP eor
#define OPN 0x2000
#ifdef HAS_ASM_LSE
#define LDOP GLUE4(LDNM, A, L, S) s(0), s(0), [x1]
#else
#define LDOP .inst 0x38200020 + OPN + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(LDNM))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(LDOP) " \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(OP) "     " FREESTANDING_LGRT_ASM(s(tmp1)) ", " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp2)) ", " FREESTANDING_LGRT_ASM(s(tmp1)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp2)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(LDNM))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef LDNM
#undef OP
#undef OPN
#undef LDOP
#undef L_ldeor
#undef SIZE
#undef MODEL
#define L_ldeor
#define SIZE 8
#define MODEL 5
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S
#define UXT mov
#define B 0xc0000000
#define SUFF _sync
#define A a
#define L l
#define M 0x408000
#define N 0xc00000
#define BARRIER dmb ish
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) x(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE3(ld, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#define LDNM ldeor
#define OP eor
#define OPN 0x2000
#ifdef HAS_ASM_LSE
#define LDOP GLUE4(LDNM, A, L, S) s(0), s(0), [x1]
#else
#define LDOP .inst 0x38200020 + OPN + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(LDNM))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(LDOP) " \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(OP) "     " FREESTANDING_LGRT_ASM(s(tmp1)) ", " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp2)) ", " FREESTANDING_LGRT_ASM(s(tmp1)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp2)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(LDNM))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef LDNM
#undef OP
#undef OPN
#undef LDOP
#undef L_ldeor
#undef SIZE
#undef MODEL
#define L_ldset
#define SIZE 1
#define MODEL 1
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S b
#define UXT uxtb
#define B 0x00000000
#define SUFF _relax
#define A
#define L
#define M 0x000000
#define N 0x000000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) w(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#define LDNM ldset
#define OP orr
#define OPN 0x3000
#ifdef HAS_ASM_LSE
#define LDOP GLUE4(LDNM, A, L, S) s(0), s(0), [x1]
#else
#define LDOP .inst 0x38200020 + OPN + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(LDNM))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(LDOP) " \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(OP) "     " FREESTANDING_LGRT_ASM(s(tmp1)) ", " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp2)) ", " FREESTANDING_LGRT_ASM(s(tmp1)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp2)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(LDNM))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef LDNM
#undef OP
#undef OPN
#undef LDOP
#undef L_ldset
#undef SIZE
#undef MODEL
#define L_ldset
#define SIZE 1
#define MODEL 2
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S b
#define UXT uxtb
#define B 0x00000000
#define SUFF _acq
#define A a
#define L
#define M 0x400000
#define N 0x800000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) w(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#define LDNM ldset
#define OP orr
#define OPN 0x3000
#ifdef HAS_ASM_LSE
#define LDOP GLUE4(LDNM, A, L, S) s(0), s(0), [x1]
#else
#define LDOP .inst 0x38200020 + OPN + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(LDNM))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(LDOP) " \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(OP) "     " FREESTANDING_LGRT_ASM(s(tmp1)) ", " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp2)) ", " FREESTANDING_LGRT_ASM(s(tmp1)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp2)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(LDNM))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef LDNM
#undef OP
#undef OPN
#undef LDOP
#undef L_ldset
#undef SIZE
#undef MODEL
#define L_ldset
#define SIZE 1
#define MODEL 3
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S b
#define UXT uxtb
#define B 0x00000000
#define SUFF _rel
#define A
#define L l
#define M 0x008000
#define N 0x400000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) w(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#define LDNM ldset
#define OP orr
#define OPN 0x3000
#ifdef HAS_ASM_LSE
#define LDOP GLUE4(LDNM, A, L, S) s(0), s(0), [x1]
#else
#define LDOP .inst 0x38200020 + OPN + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(LDNM))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(LDOP) " \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(OP) "     " FREESTANDING_LGRT_ASM(s(tmp1)) ", " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp2)) ", " FREESTANDING_LGRT_ASM(s(tmp1)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp2)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(LDNM))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef LDNM
#undef OP
#undef OPN
#undef LDOP
#undef L_ldset
#undef SIZE
#undef MODEL
#define L_ldset
#define SIZE 1
#define MODEL 4
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S b
#define UXT uxtb
#define B 0x00000000
#define SUFF _acq_rel
#define A a
#define L l
#define M 0x408000
#define N 0xc00000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) w(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#define LDNM ldset
#define OP orr
#define OPN 0x3000
#ifdef HAS_ASM_LSE
#define LDOP GLUE4(LDNM, A, L, S) s(0), s(0), [x1]
#else
#define LDOP .inst 0x38200020 + OPN + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(LDNM))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(LDOP) " \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(OP) "     " FREESTANDING_LGRT_ASM(s(tmp1)) ", " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp2)) ", " FREESTANDING_LGRT_ASM(s(tmp1)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp2)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(LDNM))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef LDNM
#undef OP
#undef OPN
#undef LDOP
#undef L_ldset
#undef SIZE
#undef MODEL
#define L_ldset
#define SIZE 1
#define MODEL 5
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S b
#define UXT uxtb
#define B 0x00000000
#define SUFF _sync
#define A a
#define L l
#define M 0x408000
#define N 0xc00000
#define BARRIER dmb ish
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) w(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE3(ld, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#define LDNM ldset
#define OP orr
#define OPN 0x3000
#ifdef HAS_ASM_LSE
#define LDOP GLUE4(LDNM, A, L, S) s(0), s(0), [x1]
#else
#define LDOP .inst 0x38200020 + OPN + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(LDNM))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(LDOP) " \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(OP) "     " FREESTANDING_LGRT_ASM(s(tmp1)) ", " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp2)) ", " FREESTANDING_LGRT_ASM(s(tmp1)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp2)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(LDNM))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef LDNM
#undef OP
#undef OPN
#undef LDOP
#undef L_ldset
#undef SIZE
#undef MODEL
#define L_ldset
#define SIZE 2
#define MODEL 1
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S h
#define UXT uxth
#define B 0x40000000
#define SUFF _relax
#define A
#define L
#define M 0x000000
#define N 0x000000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) w(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#define LDNM ldset
#define OP orr
#define OPN 0x3000
#ifdef HAS_ASM_LSE
#define LDOP GLUE4(LDNM, A, L, S) s(0), s(0), [x1]
#else
#define LDOP .inst 0x38200020 + OPN + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(LDNM))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(LDOP) " \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(OP) "     " FREESTANDING_LGRT_ASM(s(tmp1)) ", " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp2)) ", " FREESTANDING_LGRT_ASM(s(tmp1)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp2)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(LDNM))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef LDNM
#undef OP
#undef OPN
#undef LDOP
#undef L_ldset
#undef SIZE
#undef MODEL
#define L_ldset
#define SIZE 2
#define MODEL 2
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S h
#define UXT uxth
#define B 0x40000000
#define SUFF _acq
#define A a
#define L
#define M 0x400000
#define N 0x800000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) w(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#define LDNM ldset
#define OP orr
#define OPN 0x3000
#ifdef HAS_ASM_LSE
#define LDOP GLUE4(LDNM, A, L, S) s(0), s(0), [x1]
#else
#define LDOP .inst 0x38200020 + OPN + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(LDNM))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(LDOP) " \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(OP) "     " FREESTANDING_LGRT_ASM(s(tmp1)) ", " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp2)) ", " FREESTANDING_LGRT_ASM(s(tmp1)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp2)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(LDNM))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef LDNM
#undef OP
#undef OPN
#undef LDOP
#undef L_ldset
#undef SIZE
#undef MODEL
#define L_ldset
#define SIZE 2
#define MODEL 3
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S h
#define UXT uxth
#define B 0x40000000
#define SUFF _rel
#define A
#define L l
#define M 0x008000
#define N 0x400000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) w(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#define LDNM ldset
#define OP orr
#define OPN 0x3000
#ifdef HAS_ASM_LSE
#define LDOP GLUE4(LDNM, A, L, S) s(0), s(0), [x1]
#else
#define LDOP .inst 0x38200020 + OPN + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(LDNM))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(LDOP) " \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(OP) "     " FREESTANDING_LGRT_ASM(s(tmp1)) ", " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp2)) ", " FREESTANDING_LGRT_ASM(s(tmp1)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp2)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(LDNM))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef LDNM
#undef OP
#undef OPN
#undef LDOP
#undef L_ldset
#undef SIZE
#undef MODEL
#define L_ldset
#define SIZE 2
#define MODEL 4
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S h
#define UXT uxth
#define B 0x40000000
#define SUFF _acq_rel
#define A a
#define L l
#define M 0x408000
#define N 0xc00000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) w(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#define LDNM ldset
#define OP orr
#define OPN 0x3000
#ifdef HAS_ASM_LSE
#define LDOP GLUE4(LDNM, A, L, S) s(0), s(0), [x1]
#else
#define LDOP .inst 0x38200020 + OPN + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(LDNM))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(LDOP) " \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(OP) "     " FREESTANDING_LGRT_ASM(s(tmp1)) ", " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp2)) ", " FREESTANDING_LGRT_ASM(s(tmp1)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp2)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(LDNM))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef LDNM
#undef OP
#undef OPN
#undef LDOP
#undef L_ldset
#undef SIZE
#undef MODEL
#define L_ldset
#define SIZE 2
#define MODEL 5
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S h
#define UXT uxth
#define B 0x40000000
#define SUFF _sync
#define A a
#define L l
#define M 0x408000
#define N 0xc00000
#define BARRIER dmb ish
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) w(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE3(ld, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#define LDNM ldset
#define OP orr
#define OPN 0x3000
#ifdef HAS_ASM_LSE
#define LDOP GLUE4(LDNM, A, L, S) s(0), s(0), [x1]
#else
#define LDOP .inst 0x38200020 + OPN + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(LDNM))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(LDOP) " \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(OP) "     " FREESTANDING_LGRT_ASM(s(tmp1)) ", " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp2)) ", " FREESTANDING_LGRT_ASM(s(tmp1)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp2)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(LDNM))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef LDNM
#undef OP
#undef OPN
#undef LDOP
#undef L_ldset
#undef SIZE
#undef MODEL
#define L_ldset
#define SIZE 4
#define MODEL 1
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S
#define UXT mov
#define B 0x80000000
#define SUFF _relax
#define A
#define L
#define M 0x000000
#define N 0x000000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) w(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#define LDNM ldset
#define OP orr
#define OPN 0x3000
#ifdef HAS_ASM_LSE
#define LDOP GLUE4(LDNM, A, L, S) s(0), s(0), [x1]
#else
#define LDOP .inst 0x38200020 + OPN + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(LDNM))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(LDOP) " \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(OP) "     " FREESTANDING_LGRT_ASM(s(tmp1)) ", " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp2)) ", " FREESTANDING_LGRT_ASM(s(tmp1)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp2)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(LDNM))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef LDNM
#undef OP
#undef OPN
#undef LDOP
#undef L_ldset
#undef SIZE
#undef MODEL
#define L_ldset
#define SIZE 4
#define MODEL 2
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S
#define UXT mov
#define B 0x80000000
#define SUFF _acq
#define A a
#define L
#define M 0x400000
#define N 0x800000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) w(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#define LDNM ldset
#define OP orr
#define OPN 0x3000
#ifdef HAS_ASM_LSE
#define LDOP GLUE4(LDNM, A, L, S) s(0), s(0), [x1]
#else
#define LDOP .inst 0x38200020 + OPN + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(LDNM))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(LDOP) " \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(OP) "     " FREESTANDING_LGRT_ASM(s(tmp1)) ", " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp2)) ", " FREESTANDING_LGRT_ASM(s(tmp1)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp2)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(LDNM))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef LDNM
#undef OP
#undef OPN
#undef LDOP
#undef L_ldset
#undef SIZE
#undef MODEL
#define L_ldset
#define SIZE 4
#define MODEL 3
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S
#define UXT mov
#define B 0x80000000
#define SUFF _rel
#define A
#define L l
#define M 0x008000
#define N 0x400000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) w(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#define LDNM ldset
#define OP orr
#define OPN 0x3000
#ifdef HAS_ASM_LSE
#define LDOP GLUE4(LDNM, A, L, S) s(0), s(0), [x1]
#else
#define LDOP .inst 0x38200020 + OPN + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(LDNM))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(LDOP) " \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(OP) "     " FREESTANDING_LGRT_ASM(s(tmp1)) ", " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp2)) ", " FREESTANDING_LGRT_ASM(s(tmp1)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp2)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(LDNM))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef LDNM
#undef OP
#undef OPN
#undef LDOP
#undef L_ldset
#undef SIZE
#undef MODEL
#define L_ldset
#define SIZE 4
#define MODEL 4
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S
#define UXT mov
#define B 0x80000000
#define SUFF _acq_rel
#define A a
#define L l
#define M 0x408000
#define N 0xc00000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) w(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#define LDNM ldset
#define OP orr
#define OPN 0x3000
#ifdef HAS_ASM_LSE
#define LDOP GLUE4(LDNM, A, L, S) s(0), s(0), [x1]
#else
#define LDOP .inst 0x38200020 + OPN + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(LDNM))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(LDOP) " \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(OP) "     " FREESTANDING_LGRT_ASM(s(tmp1)) ", " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp2)) ", " FREESTANDING_LGRT_ASM(s(tmp1)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp2)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(LDNM))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef LDNM
#undef OP
#undef OPN
#undef LDOP
#undef L_ldset
#undef SIZE
#undef MODEL
#define L_ldset
#define SIZE 4
#define MODEL 5
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S
#define UXT mov
#define B 0x80000000
#define SUFF _sync
#define A a
#define L l
#define M 0x408000
#define N 0xc00000
#define BARRIER dmb ish
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) w(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE3(ld, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#define LDNM ldset
#define OP orr
#define OPN 0x3000
#ifdef HAS_ASM_LSE
#define LDOP GLUE4(LDNM, A, L, S) s(0), s(0), [x1]
#else
#define LDOP .inst 0x38200020 + OPN + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(LDNM))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(LDOP) " \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(OP) "     " FREESTANDING_LGRT_ASM(s(tmp1)) ", " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp2)) ", " FREESTANDING_LGRT_ASM(s(tmp1)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp2)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(LDNM))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef LDNM
#undef OP
#undef OPN
#undef LDOP
#undef L_ldset
#undef SIZE
#undef MODEL
#define L_ldset
#define SIZE 8
#define MODEL 1
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S
#define UXT mov
#define B 0xc0000000
#define SUFF _relax
#define A
#define L
#define M 0x000000
#define N 0x000000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) x(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#define LDNM ldset
#define OP orr
#define OPN 0x3000
#ifdef HAS_ASM_LSE
#define LDOP GLUE4(LDNM, A, L, S) s(0), s(0), [x1]
#else
#define LDOP .inst 0x38200020 + OPN + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(LDNM))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(LDOP) " \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(OP) "     " FREESTANDING_LGRT_ASM(s(tmp1)) ", " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp2)) ", " FREESTANDING_LGRT_ASM(s(tmp1)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp2)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(LDNM))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef LDNM
#undef OP
#undef OPN
#undef LDOP
#undef L_ldset
#undef SIZE
#undef MODEL
#define L_ldset
#define SIZE 8
#define MODEL 2
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S
#define UXT mov
#define B 0xc0000000
#define SUFF _acq
#define A a
#define L
#define M 0x400000
#define N 0x800000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) x(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#define LDNM ldset
#define OP orr
#define OPN 0x3000
#ifdef HAS_ASM_LSE
#define LDOP GLUE4(LDNM, A, L, S) s(0), s(0), [x1]
#else
#define LDOP .inst 0x38200020 + OPN + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(LDNM))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(LDOP) " \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(OP) "     " FREESTANDING_LGRT_ASM(s(tmp1)) ", " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp2)) ", " FREESTANDING_LGRT_ASM(s(tmp1)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp2)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(LDNM))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef LDNM
#undef OP
#undef OPN
#undef LDOP
#undef L_ldset
#undef SIZE
#undef MODEL
#define L_ldset
#define SIZE 8
#define MODEL 3
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S
#define UXT mov
#define B 0xc0000000
#define SUFF _rel
#define A
#define L l
#define M 0x008000
#define N 0x400000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) x(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#define LDNM ldset
#define OP orr
#define OPN 0x3000
#ifdef HAS_ASM_LSE
#define LDOP GLUE4(LDNM, A, L, S) s(0), s(0), [x1]
#else
#define LDOP .inst 0x38200020 + OPN + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(LDNM))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(LDOP) " \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(OP) "     " FREESTANDING_LGRT_ASM(s(tmp1)) ", " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp2)) ", " FREESTANDING_LGRT_ASM(s(tmp1)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp2)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(LDNM))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef LDNM
#undef OP
#undef OPN
#undef LDOP
#undef L_ldset
#undef SIZE
#undef MODEL
#define L_ldset
#define SIZE 8
#define MODEL 4
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S
#define UXT mov
#define B 0xc0000000
#define SUFF _acq_rel
#define A a
#define L l
#define M 0x408000
#define N 0xc00000
#define BARRIER
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) x(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE4(ld, A, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#define LDNM ldset
#define OP orr
#define OPN 0x3000
#ifdef HAS_ASM_LSE
#define LDOP GLUE4(LDNM, A, L, S) s(0), s(0), [x1]
#else
#define LDOP .inst 0x38200020 + OPN + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(LDNM))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(LDOP) " \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(OP) "     " FREESTANDING_LGRT_ASM(s(tmp1)) ", " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp2)) ", " FREESTANDING_LGRT_ASM(s(tmp1)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp2)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(LDNM))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef LDNM
#undef OP
#undef OPN
#undef LDOP
#undef L_ldset
#undef SIZE
#undef MODEL
#define L_ldset
#define SIZE 8
#define MODEL 5
__asm__(".pushsection .text\n");
#if defined(__aarch64__)
#ifdef HAS_ASM_LSE
__asm__(
    ".arch_extension lse\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(HIDDEN(__aarch64_have_lse_atomics)) "\n"
);
#define S
#define UXT mov
#define B 0xc0000000
#define SUFF _sync
#define A a
#define L l
#define M 0x408000
#define N 0xc00000
#define BARRIER dmb ish
#define x(N) GLUE2(x, N)
#define w(N) GLUE2(w, N)
#define s(N) x(N)
#define NAME(BASE) GLUE4(__aarch64_, BASE, SIZE, SUFF)
#define LDXR GLUE3(ld, xr, S)
#define STXR GLUE4(st, L, xr, S)
#define tmp0 16
#define tmp1 17
#define tmp2 15
__asm__(
    ".macro JUMP_IF_NOT_LSE label\n"
    "        adrp    " FREESTANDING_LGRT_ASM(x(tmp0)) ", __aarch64_have_lse_atomics\n"
    "        ldrb    " FREESTANDING_LGRT_ASM(w(tmp0)) ", [" FREESTANDING_LGRT_ASM(x(tmp0)) ", :lo12:__aarch64_have_lse_atomics]\n"
    "        cbz     " FREESTANDING_LGRT_ASM(w(tmp0)) ", \\label\n"
    ".endm\n"
);
#define LDNM ldset
#define OP orr
#define OPN 0x3000
#ifdef HAS_ASM_LSE
#define LDOP GLUE4(LDNM, A, L, S) s(0), s(0), [x1]
#else
#define LDOP .inst 0x38200020 + OPN + B + N
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OUTLINE_FUNCTION_UNMANGLED(NAME(LDNM))) "\n"
    "        JUMP_IF_NOT_LSE 8f\n"
    "        " FREESTANDING_LGRT_ASM(LDOP) " \n"
    "        ret\n"
    "8:\n"
    "        mov    " FREESTANDING_LGRT_ASM(s(tmp0)) ", " FREESTANDING_LGRT_ASM(s(0)) "\n"
    "0:\n"
    "        " FREESTANDING_LGRT_ASM(LDXR) "   " FREESTANDING_LGRT_ASM(s(0)) ", [x1]\n"
    "        " FREESTANDING_LGRT_ASM(OP) "     " FREESTANDING_LGRT_ASM(s(tmp1)) ", " FREESTANDING_LGRT_ASM(s(0)) ", " FREESTANDING_LGRT_ASM(s(tmp0)) "\n"
    "        " FREESTANDING_LGRT_ASM(STXR) "   " FREESTANDING_LGRT_ASM(w(tmp2)) ", " FREESTANDING_LGRT_ASM(s(tmp1)) ", [x1]\n"
    "        cbnz   " FREESTANDING_LGRT_ASM(w(tmp2)) ", 0b\n"
    "        " FREESTANDING_LGRT_ASM(BARRIER) "\n"
    "        ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_OUTLINE_FUNCTION(NAME(LDNM))) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
    FREESTANDING_LGRT_ASM(GNU_PROPERTY_BTI_PAC_GCS) "\n"
);
#endif 
__asm__(".popsection\n");
__asm__(".purgem JUMP_IF_NOT_LSE\n");
#undef S
#undef UXT
#undef B
#undef SUFF
#undef A
#undef L
#undef M
#undef N
#undef BARRIER
#undef x
#undef w
#undef s
#undef NAME
#undef LDXR
#undef STXR
#undef tmp0
#undef tmp1
#undef tmp2
#undef LDNM
#undef OP
#undef OPN
#undef LDOP
#undef L_ldset
#undef SIZE
#undef MODEL
#endif
#if defined(__arm__) && (!defined(__thumb__) || defined(__thumb2__) || __ARM_ARCH >= 6)
__asm__(".pushsection .text\n");
__asm__(
    "        .syntax unified\n"
    "        .text\n"
    "        " FREESTANDING_LGRT_ASM(DEFINE_CODE_STATE) "\n"
    "        .p2align 2\n"
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_FUNCTION(__aeabi_idivmod)) "\n"
);
#if defined(USE_THUMB_1)
__asm__(
    "        push    {r0, r1, lr}\n"
    "        bl      " FREESTANDING_LGRT_ASM(SYMBOL_NAME(__divsi3)) "\n"
    "        pop     {r1, r2, r3} \n"
    "        muls    r2, r0, r2   \n"
    "        subs    r1, r1, r2\n"
    "        " FREESTANDING_LGRT_ASM(JMP     (r3)) "\n"
);
#else  
__asm__(
    "        " FREESTANDING_LGRT_ASM(PACBTI_LANDING) "\n"
);
#if defined(__ARM_FEATURE_PAC_DEFAULT)
__asm__(
    "        push    { r12, lr }\n"
);
#else
__asm__(
    "        push    { lr }\n"
);
#endif
__asm__(
    "        sub     sp, sp, #4\n"
    "        mov     r2, sp\n"
    "        bl      " FREESTANDING_LGRT_ASM(SYMBOL_NAME(__divmodsi4)) "\n"
    "        ldr     r1, [sp]\n"
    "        add     sp, sp, #4\n"
);
#if defined(__ARM_FEATURE_PAC_DEFAULT)
__asm__(
    "        pop     { r12, lr }\n"
    "        " FREESTANDING_LGRT_ASM(PAC_RETURN) "\n"
);
#else
__asm__(
    "        POP_PC\n"
);
#endif
#endif 
__asm__(
    FREESTANDING_LGRT_ASM(END_COMPILERRT_FUNCTION(__aeabi_idivmod)) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
);
__asm__(".popsection\n");
#endif
#if defined(__arm__) && (!defined(__thumb__) || defined(__thumb2__) || __ARM_ARCH >= 6)
__asm__(".pushsection .text\n");
__asm__(
    "        .syntax unified\n"
    "        .p2align 2\n"
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_FUNCTION(__aeabi_ldivmod)) "\n"
    "        " FREESTANDING_LGRT_ASM(PACBTI_LANDING) "\n"
);
#if defined(__ARM_FEATURE_PAC_DEFAULT)
__asm__(
    "        push    {r6, r12, lr}\n"
);
#else
__asm__(
    "        push    {r6, lr}\n"
);
#endif
__asm__(
    "        sub     sp, sp, #16\n"
    "        add     r6, sp, #8\n"
    "        str     r6, [sp]\n"
    "        bl      " FREESTANDING_LGRT_ASM(SYMBOL_NAME(__divmoddi4)) "\n"
    "        ldr     r2, [sp, #8]\n"
    "        ldr     r3, [sp, #12]\n"
    "        add     sp, sp, #16\n"
);
#if defined(__ARM_FEATURE_PAC_DEFAULT)
__asm__(
    "        pop     {r6, r12, lr}\n"
    "        " FREESTANDING_LGRT_ASM(PAC_RETURN) "\n"
);
#else
__asm__(
    "        POP_PC_WITH_REGS r6\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(END_COMPILERRT_FUNCTION(__aeabi_ldivmod)) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
);
__asm__(".popsection\n");
#endif
#if defined(__arm__) && (!defined(__thumb__) || defined(__thumb2__) || __ARM_ARCH >= 6)
__asm__(".pushsection .text\n");
__asm__(
    "        .syntax unified\n"
    "        .p2align 2\n"
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_FUNCTION(__aeabi_memcmp)) "\n"
);
#ifdef USE_THUMB_1
__asm__(
    "        push    {r7, lr}\n"
    "        bl      memcmp\n"
    "        POP_PC_WITH_REGS r7\n"
);
#else
#if defined(__ARM_FEATURE_BTI_DEFAULT)
__asm__(
    "        bti\n"
);
#endif
__asm__(
    "        b       memcmp\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(END_COMPILERRT_FUNCTION(__aeabi_memcmp)) "\n"
    FREESTANDING_LGRT_ASM(DEFINE_AEABI_FUNCTION_ALIAS(__aeabi_memcmp4, __aeabi_memcmp)) "\n"
    FREESTANDING_LGRT_ASM(DEFINE_AEABI_FUNCTION_ALIAS(__aeabi_memcmp8, __aeabi_memcmp)) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
);
__asm__(".popsection\n");
#endif
#if defined(__arm__) && (!defined(__thumb__) || defined(__thumb2__) || __ARM_ARCH >= 6)
__asm__(".pushsection .text\n");
__asm__(
    "        .syntax unified\n"
    "        .p2align 2\n"
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_FUNCTION(__aeabi_memcpy)) "\n"
);
#ifdef USE_THUMB_1
__asm__(
    "        push    {r7, lr}\n"
    "        bl      memcpy\n"
    "        POP_PC_WITH_REGS r7\n"
);
#else
#if defined(__ARM_FEATURE_BTI_DEFAULT)
__asm__(
    "        bti\n"
);
#endif
__asm__(
    "        b       memcpy\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(END_COMPILERRT_FUNCTION(__aeabi_memcpy)) "\n"
    FREESTANDING_LGRT_ASM(DEFINE_AEABI_FUNCTION_ALIAS(__aeabi_memcpy4, __aeabi_memcpy)) "\n"
    FREESTANDING_LGRT_ASM(DEFINE_AEABI_FUNCTION_ALIAS(__aeabi_memcpy8, __aeabi_memcpy)) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
);
__asm__(".popsection\n");
#endif
#if defined(__arm__) && (!defined(__thumb__) || defined(__thumb2__) || __ARM_ARCH >= 6)
__asm__(".pushsection .text\n");
__asm__(
    "        .p2align 2\n"
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_FUNCTION(__aeabi_memmove)) "\n"
);
#ifdef USE_THUMB_1
__asm__(
    "        push    {r7, lr}\n"
    "        bl      memmove\n"
    "        POP_PC_WITH_REGS r7\n"
);
#else
#if defined(__ARM_FEATURE_BTI_DEFAULT)
__asm__(
    "        bti\n"
);
#endif
__asm__(
    "        b       memmove\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(END_COMPILERRT_FUNCTION(__aeabi_memmove)) "\n"
    FREESTANDING_LGRT_ASM(DEFINE_AEABI_FUNCTION_ALIAS(__aeabi_memmove4, __aeabi_memmove)) "\n"
    FREESTANDING_LGRT_ASM(DEFINE_AEABI_FUNCTION_ALIAS(__aeabi_memmove8, __aeabi_memmove)) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
);
__asm__(".popsection\n");
#endif
#if defined(__arm__) && (!defined(__thumb__) || defined(__thumb2__) || __ARM_ARCH >= 6)
__asm__(".pushsection .text\n");
__asm__(
    "        .syntax unified\n"
    "        .p2align 2\n"
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_FUNCTION(__aeabi_memset)) "\n"
);
#if defined(__ARM_FEATURE_BTI_DEFAULT)
__asm__(
    "        bti\n"
);
#endif
__asm__(
    "        mov     r3, r1\n"
    "        mov     r1, r2\n"
    "        mov     r2, r3\n"
);
#ifdef USE_THUMB_1
__asm__(
    "        push    {r7, lr}\n"
    "        bl      memset\n"
    "        POP_PC_WITH_REGS r7\n"
);
#else
__asm__(
    "        b       memset\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(END_COMPILERRT_FUNCTION(__aeabi_memset)) "\n"
    FREESTANDING_LGRT_ASM(DEFINE_AEABI_FUNCTION_ALIAS(__aeabi_memset4, __aeabi_memset)) "\n"
    FREESTANDING_LGRT_ASM(DEFINE_AEABI_FUNCTION_ALIAS(__aeabi_memset8, __aeabi_memset)) "\n"
    "        .p2align 2\n"
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_FUNCTION(__aeabi_memclr)) "\n"
);
#if defined(__ARM_FEATURE_BTI_DEFAULT)
__asm__(
    "        bti\n"
);
#endif
__asm__(
    "        mov     r2, r1\n"
    "        movs    r1, #0\n"
);
#ifdef USE_THUMB_1
__asm__(
    "        push    {r7, lr}\n"
    "        bl      memset\n"
    "        POP_PC_WITH_REGS r7\n"
);
#else
__asm__(
    "        b       memset\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(END_COMPILERRT_FUNCTION(__aeabi_memclr)) "\n"
    FREESTANDING_LGRT_ASM(DEFINE_AEABI_FUNCTION_ALIAS(__aeabi_memclr4, __aeabi_memclr)) "\n"
    FREESTANDING_LGRT_ASM(DEFINE_AEABI_FUNCTION_ALIAS(__aeabi_memclr8, __aeabi_memclr)) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
);
__asm__(".popsection\n");
#endif
#if defined(__arm__) && (!defined(__thumb__) || defined(__thumb2__) || __ARM_ARCH >= 6)
__asm__(".pushsection .text\n");
__asm__(
    "        .syntax unified\n"
    "        .text\n"
    "        " FREESTANDING_LGRT_ASM(DEFINE_CODE_STATE) "\n"
    "        .p2align 2\n"
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_FUNCTION(__aeabi_uidivmod)) "\n"
);
#if defined(USE_THUMB_1)
__asm__(
    "        cmp     r0, r1\n"
    "        bcc     " FREESTANDING_LGRT_ASM(LOCAL_LABEL(case_denom_larger)) "\n"
    "        push    {r0, r1, lr}\n"
    "        bl      " FREESTANDING_LGRT_ASM(SYMBOL_NAME(__aeabi_uidiv)) "\n"
    "        pop     {r1, r2, r3}\n"
    "        muls    r2, r0, r2 \n"
    "        subs    r1, r1, r2\n"
    "        " FREESTANDING_LGRT_ASM(JMP     (r3)) "\n"
    FREESTANDING_LGRT_ASM(LOCAL_LABEL(case_denom_larger)) ":\n"
    "        movs    r1, r0\n"
    "        movs    r0, #0\n"
    "        " FREESTANDING_LGRT_ASM(JMP     (lr)) "\n"
);
#else 
__asm__(
    "        " FREESTANDING_LGRT_ASM(PACBTI_LANDING) "\n"
);
#if defined(__ARM_FEATURE_PAC_DEFAULT)
__asm__(
    "        push    { r12, lr }\n"
);
#else
__asm__(
    "        push    { lr }\n"
);
#endif
__asm__(
    "        sub     sp, sp, #4\n"
    "        mov     r2, sp\n"
    "        bl      " FREESTANDING_LGRT_ASM(SYMBOL_NAME(__udivmodsi4)) "\n"
    "        ldr     r1, [sp]\n"
    "        add     sp, sp, #4\n"
);
#if defined(__ARM_FEATURE_PAC_DEFAULT)
__asm__(
    "        pop     { r12, lr }\n"
    "        " FREESTANDING_LGRT_ASM(PAC_RETURN) "\n"
);
#else
__asm__(
    "        POP_PC\n"
);
#endif
#endif
__asm__(
    FREESTANDING_LGRT_ASM(END_COMPILERRT_FUNCTION(__aeabi_uidivmod)) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
);
__asm__(".popsection\n");
#endif
#if defined(__arm__) && (!defined(__thumb__) || defined(__thumb2__) || __ARM_ARCH >= 6)
__asm__(".pushsection .text\n");
__asm__(
    "        .syntax unified\n"
    "        .p2align 2\n"
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_FUNCTION(__aeabi_uldivmod)) "\n"
    "        " FREESTANDING_LGRT_ASM(PACBTI_LANDING) "\n"
);
#if defined(__ARM_FEATURE_PAC_DEFAULT)
__asm__(
    "        push    {r6, r12, lr}\n"
);
#else
__asm__(
    "        push    {r6, lr}\n"
);
#endif
__asm__(
    "        sub\tsp, sp, #16\n"
    "        add\tr6, sp, #8\n"
    "        str\tr6, [sp]\n"
    "        bl\t" FREESTANDING_LGRT_ASM(SYMBOL_NAME(__udivmoddi4)) "\n"
    "        ldr\tr2, [sp, #8]\n"
    "        ldr\tr3, [sp, #12]\n"
    "        add\tsp, sp, #16\n"
);
#if defined(__ARM_FEATURE_PAC_DEFAULT)
__asm__(
    "        pop     {r6, r12, lr}\n"
    "        " FREESTANDING_LGRT_ASM(PAC_RETURN) "\n"
);
#else
__asm__(
    "        POP_PC_WITH_REGS r6\n"
);
#endif
__asm__(
    FREESTANDING_LGRT_ASM(END_COMPILERRT_FUNCTION(__aeabi_uldivmod)) "\n"
    FREESTANDING_LGRT_ASM(NO_EXEC_STACK_DIRECTIVE) "\n"
);
__asm__(".popsection\n");
#endif
#if defined(__riscv) && __riscv_xlen == 64
__asm__(".pushsection .text\n");
#if __riscv_xlen == 64
#define __mulxi3 __muldi3
#ifndef __mulxi3
#error "__mulxi3 must be defined to use this generic implementation"
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_FUNCTION(__mulxi3)) "\n"
    "  mv     a2, a0\n"
    "  mv     a0, zero\n"
    FREESTANDING_LGRT_ASM(LOCAL_LABEL(loop)) ":\n"
    "  andi   a3, a1, 1\n"
    "  beqz   a3, " FREESTANDING_LGRT_ASM(LOCAL_LABEL(cond_add)) "\n"
    "  add    a0, a0, a2\n"
    FREESTANDING_LGRT_ASM(LOCAL_LABEL(cond_add)) ":\n"
    "  srli   a1, a1, 1\n"
    "  slli   a2, a2, 1\n"
    "  bnez   a1, " FREESTANDING_LGRT_ASM(LOCAL_LABEL(loop)) "\n"
    "  ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_FUNCTION(__mulxi3)) "\n"
);
#endif
__asm__(".popsection\n");
#undef __mulxi3
#endif
#if defined(__riscv) && __riscv_xlen == 32
__asm__(".pushsection .text\n");
#if __riscv_xlen == 32
#define __mulxi3 __mulsi3
#ifndef __mulxi3
#error "__mulxi3 must be defined to use this generic implementation"
#endif
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_FUNCTION(__mulxi3)) "\n"
    "  mv     a2, a0\n"
    "  mv     a0, zero\n"
    FREESTANDING_LGRT_ASM(LOCAL_LABEL(loop)) ":\n"
    "  andi   a3, a1, 1\n"
    "  beqz   a3, " FREESTANDING_LGRT_ASM(LOCAL_LABEL(cond_add)) "\n"
    "  add    a0, a0, a2\n"
    FREESTANDING_LGRT_ASM(LOCAL_LABEL(cond_add)) ":\n"
    "  srli   a1, a1, 1\n"
    "  slli   a2, a2, 1\n"
    "  bnez   a1, " FREESTANDING_LGRT_ASM(LOCAL_LABEL(loop)) "\n"
    "  ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_FUNCTION(__mulxi3)) "\n"
);
#endif
__asm__(".popsection\n");
#undef __mulxi3
#endif
#if defined(__riscv)
__asm__(".pushsection .text\n");
__asm__(
    FREESTANDING_LGRT_ASM(TEXT_SECTION) "\n"
);
#define DEFINE_COMPILERRT_OVERLAPPING_FUNCTION(name)   DEFINE_CODE_STATE   .globl FUNC_SYMBOL(SYMBOL_NAME(name)) SEPARATOR   SYMBOL_IS_FUNC(SYMBOL_NAME(name)) SEPARATOR   HIDDEN(SYMBOL_NAME(name)) SEPARATOR   DECLARE_FUNC_ENCODING   FUNC_SYMBOL(SYMBOL_NAME(name)):
#if __riscv_xlen == 32
#ifndef __riscv_abi_rve
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OVERLAPPING_FUNCTION(__riscv_restore_12)) "\n"
    "  lw      s11, 12(sp)\n"
    "  addi    sp, sp, 16\n"
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OVERLAPPING_FUNCTION(__riscv_restore_11)) "\n"
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_FUNCTION_ALIAS(__riscv_restore_10, __riscv_restore_11)) "\n"
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_FUNCTION_ALIAS(__riscv_restore_9,  __riscv_restore_11)) "\n"
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_FUNCTION_ALIAS(__riscv_restore_8,  __riscv_restore_11)) "\n"
    "  lw      s10, 0(sp)\n"
    "  lw      s9,  4(sp)\n"
    "  lw      s8,  8(sp)\n"
    "  lw      s7,  12(sp)\n"
    "  addi    sp, sp, 16\n"
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OVERLAPPING_FUNCTION(__riscv_restore_7)) "\n"
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_FUNCTION_ALIAS(__riscv_restore_6, __riscv_restore_7)) "\n"
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_FUNCTION_ALIAS(__riscv_restore_5, __riscv_restore_7)) "\n"
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_FUNCTION_ALIAS(__riscv_restore_4, __riscv_restore_7)) "\n"
);
__asm__(
    "  lw      s6,  0(sp)\n"
    "  lw      s5,  4(sp)\n"
    "  lw      s4,  8(sp)\n"
    "  lw      s3,  12(sp)\n"
    "  addi    sp, sp, 16\n"
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OVERLAPPING_FUNCTION(__riscv_restore_3)) "\n"
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_FUNCTION_ALIAS(__riscv_restore_2, __riscv_restore_3)) "\n"
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_FUNCTION_ALIAS(__riscv_restore_1, __riscv_restore_3)) "\n"
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_FUNCTION_ALIAS(__riscv_restore_0, __riscv_restore_3)) "\n"
    "  lw      s2,  0(sp)\n"
    "  lw      s1,  4(sp)\n"
    "  lw      s0,  8(sp)\n"
    "  lw      ra,  12(sp)\n"
    "  addi    sp, sp, 16\n"
    "  ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_FUNCTION(__riscv_restore_12)) "\n"
);
__asm__(
    FREESTANDING_LGRT_ASM(END_COMPILERRT_FUNCTION(__riscv_restore_11)) "\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_FUNCTION(__riscv_restore_7)) "\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_FUNCTION(__riscv_restore_3)) "\n"
);
#else
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OVERLAPPING_FUNCTION(__riscv_restore_2)) "\n"
    "  lw      s1, 0(sp)\n"
    "  addi    sp, sp, 4\n"
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OVERLAPPING_FUNCTION(__riscv_restore_1)) "\n"
    "  lw      s0, 0(sp)\n"
    "  addi    sp, sp, 4\n"
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OVERLAPPING_FUNCTION(__riscv_restore_0)) "\n"
    "  lw      ra, 0(sp)\n"
    "  addi    sp, sp, 4\n"
    "  ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_FUNCTION(__riscv_restore_2)) "\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_FUNCTION(__riscv_restore_1)) "\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_FUNCTION(__riscv_restore_0)) "\n"
);
#endif
#elif __riscv_xlen == 64
#ifndef __riscv_abi_rve
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OVERLAPPING_FUNCTION(__riscv_restore_12)) "\n"
    "  ld      s11, 8(sp)\n"
    "  addi    sp, sp, 16\n"
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OVERLAPPING_FUNCTION(__riscv_restore_11)) "\n"
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_FUNCTION_ALIAS(__riscv_restore_10, __riscv_restore_11)) "\n"
    "  ld      s10, 0(sp)\n"
    "  ld      s9,  8(sp)\n"
    "  addi    sp, sp, 16\n"
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OVERLAPPING_FUNCTION(__riscv_restore_9)) "\n"
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_FUNCTION_ALIAS(__riscv_restore_8, __riscv_restore_9)) "\n"
    "  ld      s8,  0(sp)\n"
    "  ld      s7,  8(sp)\n"
    "  addi    sp, sp, 16\n"
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OVERLAPPING_FUNCTION(__riscv_restore_7)) "\n"
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_FUNCTION_ALIAS(__riscv_restore_6, __riscv_restore_7)) "\n"
    "  ld      s6,  0(sp)\n"
);
__asm__(
    "  ld      s5,  8(sp)\n"
    "  addi    sp, sp, 16\n"
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OVERLAPPING_FUNCTION(__riscv_restore_5)) "\n"
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_FUNCTION_ALIAS(__riscv_restore_4, __riscv_restore_5)) "\n"
    "  ld      s4,  0(sp)\n"
    "  ld      s3,  8(sp)\n"
    "  addi    sp, sp, 16\n"
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OVERLAPPING_FUNCTION(__riscv_restore_3)) "\n"
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_FUNCTION_ALIAS(__riscv_restore_2, __riscv_restore_3)) "\n"
    "  ld      s2,  0(sp)\n"
    "  ld      s1,  8(sp)\n"
    "  addi    sp, sp, 16\n"
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OVERLAPPING_FUNCTION(__riscv_restore_1)) "\n"
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_FUNCTION_ALIAS(__riscv_restore_0, __riscv_restore_1)) "\n"
    "  ld      s0,  0(sp)\n"
    "  ld      ra,  8(sp)\n"
);
__asm__(
    "  addi    sp, sp, 16\n"
    "  ret\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_FUNCTION(__riscv_restore_12)) "\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_FUNCTION(__riscv_restore_11)) "\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_FUNCTION(__riscv_restore_9)) "\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_FUNCTION(__riscv_restore_7)) "\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_FUNCTION(__riscv_restore_5)) "\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_FUNCTION(__riscv_restore_3)) "\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_FUNCTION(__riscv_restore_1)) "\n"
);
#else
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OVERLAPPING_FUNCTION(__riscv_restore_2)) "\n"
    "  ld      s1, 0(sp)\n"
    "  addi    sp, sp, 8\n"
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OVERLAPPING_FUNCTION(__riscv_restore_1)) "\n"
    "  ld      s0, 0(sp)\n"
    "  addi    sp, sp, 8\n"
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OVERLAPPING_FUNCTION(__riscv_restore_0)) "\n"
    "  ld      ra, 0(sp)\n"
    "  addi    sp, sp, 8\n"
    "  ret\n"
);
#endif
#else
# error "xlen must be 32 or 64 for save-restore implementation"
#endif
__asm__(".popsection\n");
#undef DEFINE_COMPILERRT_OVERLAPPING_FUNCTION
#endif
#if defined(__riscv)
__asm__(".pushsection .text\n");
__asm__(
    FREESTANDING_LGRT_ASM(TEXT_SECTION) "\n"
);
#define DEFINE_COMPILERRT_OVERLAPPING_FUNCTION(name)   DEFINE_CODE_STATE   .globl FUNC_SYMBOL(SYMBOL_NAME(name)) SEPARATOR   SYMBOL_IS_FUNC(SYMBOL_NAME(name)) SEPARATOR   HIDDEN(SYMBOL_NAME(name)) SEPARATOR   DECLARE_FUNC_ENCODING   FUNC_SYMBOL(SYMBOL_NAME(name)):
#if __riscv_xlen == 32
#ifndef __riscv_abi_rve
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OVERLAPPING_FUNCTION(__riscv_save_12)) "\n"
    "  addi   sp, sp, -64\n"
    "  mv     t1, zero\n"
    "  sw     s11, 12(sp)\n"
    "  j      " FREESTANDING_LGRT_ASM(LOCAL_LABEL(riscv_save_11_8)) "\n"
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OVERLAPPING_FUNCTION(__riscv_save_11)) "\n"
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_FUNCTION_ALIAS(__riscv_save_10, __riscv_save_11)) "\n"
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_FUNCTION_ALIAS(__riscv_save_9,  __riscv_save_11)) "\n"
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_FUNCTION_ALIAS(__riscv_save_8,  __riscv_save_11)) "\n"
    "  addi   sp, sp, -64\n"
    "  li     t1, 16\n"
    FREESTANDING_LGRT_ASM(LOCAL_LABEL(riscv_save_11_8)) ":\n"
    "  sw     s10, 16(sp)\n"
    "  sw     s9,  20(sp)\n"
    "  sw     s8,  24(sp)\n"
    "  sw     s7,  28(sp)\n"
);
__asm__(
    "  j      " FREESTANDING_LGRT_ASM(LOCAL_LABEL(riscv_save_7_4)) "\n"
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OVERLAPPING_FUNCTION(__riscv_save_7)) "\n"
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_FUNCTION_ALIAS(__riscv_save_6, __riscv_save_7)) "\n"
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_FUNCTION_ALIAS(__riscv_save_5, __riscv_save_7)) "\n"
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_FUNCTION_ALIAS(__riscv_save_4, __riscv_save_7)) "\n"
    "  addi   sp, sp, -64\n"
    "  li     t1, 32\n"
    FREESTANDING_LGRT_ASM(LOCAL_LABEL(riscv_save_7_4)) ":\n"
    "  sw     s6, 32(sp)\n"
    "  sw     s5, 36(sp)\n"
    "  sw     s4, 40(sp)\n"
    "  sw     s3, 44(sp)\n"
    "  sw     s2, 48(sp)\n"
    "  sw     s1, 52(sp)\n"
    "  sw     s0, 56(sp)\n"
    "  sw     ra, 60(sp)\n"
);
__asm__(
    "  add    sp, sp, t1\n"
    "  jr     t0\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_FUNCTION(__riscv_save_12)) "\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_FUNCTION(__riscv_save_11)) "\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_FUNCTION(__riscv_save_7)) "\n"
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OVERLAPPING_FUNCTION(__riscv_save_3)) "\n"
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_FUNCTION_ALIAS(__riscv_save_2, __riscv_save_3)) "\n"
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_FUNCTION_ALIAS(__riscv_save_1, __riscv_save_3)) "\n"
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_FUNCTION_ALIAS(__riscv_save_0, __riscv_save_3)) "\n"
    "  addi    sp, sp, -16\n"
    "  sw      s2,  0(sp)\n"
    "  sw      s1,  4(sp)\n"
    "  sw      s0,  8(sp)\n"
    "  sw      ra,  12(sp)\n"
    "  jr      t0\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_FUNCTION(__riscv_save_3)) "\n"
);
#else
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_FUNCTION(__riscv_save_2)) "\n"
    "  addi    sp, sp, -12\n"
    "  sw      s1,  0(sp)\n"
    "  sw      s0,  4(sp)\n"
    "  sw      ra,  8(sp)\n"
    "  jr      t0\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_FUNCTION(__riscv_save_2)) "\n"
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_FUNCTION(__riscv_save_1)) "\n"
    "  addi    sp, sp, -8\n"
    "  sw      s0,  0(sp)\n"
    "  sw      ra,  4(sp)\n"
    "  jr      t0\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_FUNCTION(__riscv_save_1)) "\n"
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_FUNCTION(__riscv_save_0)) "\n"
    "  addi    sp, sp, -4\n"
    "  sw      ra,  0(sp)\n"
);
__asm__(
    "  jr      t0\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_FUNCTION(__riscv_save_0)) "\n"
);
#endif
#elif __riscv_xlen == 64
#ifndef __riscv_abi_rve
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OVERLAPPING_FUNCTION(__riscv_save_12)) "\n"
    "  addi   sp, sp, -112\n"
    "  mv     t1, zero\n"
    "  sd     s11, 8(sp)\n"
    "  j      " FREESTANDING_LGRT_ASM(LOCAL_LABEL(riscv_save_11_10)) "\n"
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OVERLAPPING_FUNCTION(__riscv_save_11)) "\n"
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_FUNCTION_ALIAS(__riscv_save_10, __riscv_save_11)) "\n"
    "  addi   sp, sp, -112\n"
    "  li     t1, 16\n"
    FREESTANDING_LGRT_ASM(LOCAL_LABEL(riscv_save_11_10)) ":\n"
    "  sd     s10, 16(sp)\n"
    "  sd     s9,  24(sp)\n"
    "  j      " FREESTANDING_LGRT_ASM(LOCAL_LABEL(riscv_save_9_8)) "\n"
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OVERLAPPING_FUNCTION(__riscv_save_9)) "\n"
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_FUNCTION_ALIAS(__riscv_save_8, __riscv_save_9)) "\n"
    "  addi   sp, sp, -112\n"
);
__asm__(
    "  li     t1, 32\n"
    FREESTANDING_LGRT_ASM(LOCAL_LABEL(riscv_save_9_8)) ":\n"
    "  sd     s8,  32(sp)\n"
    "  sd     s7,  40(sp)\n"
    "  j      " FREESTANDING_LGRT_ASM(LOCAL_LABEL(riscv_save_7_6)) "\n"
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OVERLAPPING_FUNCTION(__riscv_save_7)) "\n"
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_FUNCTION_ALIAS(__riscv_save_6, __riscv_save_7)) "\n"
    "  addi   sp, sp, -112\n"
    "  li     t1, 48\n"
    FREESTANDING_LGRT_ASM(LOCAL_LABEL(riscv_save_7_6)) ":\n"
    "  sd     s6,  48(sp)\n"
    "  sd     s5,  56(sp)\n"
    "  j      " FREESTANDING_LGRT_ASM(LOCAL_LABEL(riscv_save_5_4)) "\n"
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OVERLAPPING_FUNCTION(__riscv_save_5)) "\n"
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_FUNCTION_ALIAS(__riscv_save_4, __riscv_save_5)) "\n"
    "  addi   sp, sp, -112\n"
);
__asm__(
    "  li     t1, 64\n"
    FREESTANDING_LGRT_ASM(LOCAL_LABEL(riscv_save_5_4)) ":\n"
    "  sd     s4, 64(sp)\n"
    "  sd     s3, 72(sp)\n"
    "  j      " FREESTANDING_LGRT_ASM(LOCAL_LABEL(riscv_save_3_2)) "\n"
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OVERLAPPING_FUNCTION(__riscv_save_3)) "\n"
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_FUNCTION_ALIAS(__riscv_save_2, __riscv_save_3)) "\n"
    "  addi   sp, sp, -112\n"
    "  li     t1, 80\n"
    FREESTANDING_LGRT_ASM(LOCAL_LABEL(riscv_save_3_2)) ":\n"
    "  sd     s2, 80(sp)\n"
    "  sd     s1, 88(sp)\n"
    "  sd     s0, 96(sp)\n"
    "  sd     ra, 104(sp)\n"
    "  add    sp, sp, t1\n"
    "  jr     t0\n"
);
__asm__(
    FREESTANDING_LGRT_ASM(END_COMPILERRT_FUNCTION(__riscv_save_12)) "\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_FUNCTION(__riscv_save_11)) "\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_FUNCTION(__riscv_save_9)) "\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_FUNCTION(__riscv_save_7)) "\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_FUNCTION(__riscv_save_5)) "\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_FUNCTION(__riscv_save_3)) "\n"
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_OVERLAPPING_FUNCTION(__riscv_save_1)) "\n"
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_FUNCTION_ALIAS(__riscv_save_0, __riscv_save_1)) "\n"
    "  addi   sp, sp, -16\n"
    "  sd     s0, 0(sp)\n"
    "  sd     ra, 8(sp)\n"
    "  jr     t0\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_FUNCTION(__riscv_save_1)) "\n"
);
#else
__asm__(
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_FUNCTION(__riscv_save_2)) "\n"
    "  addi    sp, sp, -24\n"
    "  sd      s1, 0(sp)\n"
    "  sd      s0, 8(sp)\n"
    "  sd      ra, 16(sp)\n"
    "  jr      t0\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_FUNCTION(__riscv_save_2)) "\n"
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_FUNCTION(__riscv_save_1)) "\n"
    "  addi    sp, sp, -16\n"
    "  sd      s0, 0(sp)\n"
    "  sd      ra, 8(sp)\n"
    "  jr      t0\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_FUNCTION(__riscv_save_1)) "\n"
    FREESTANDING_LGRT_ASM(DEFINE_COMPILERRT_FUNCTION(__riscv_save_0)) "\n"
    "  addi    sp, sp, -8\n"
    "  sd      ra,  0(sp)\n"
);
__asm__(
    "  jr      t0\n"
    FREESTANDING_LGRT_ASM(END_COMPILERRT_FUNCTION(__riscv_save_0)) "\n"
);
#endif
#else
# error "xlen must be 32 or 64 for save-restore implementation"
#endif
__asm__(".popsection\n");
#undef DEFINE_COMPILERRT_OVERLAPPING_FUNCTION
#endif

#undef FREESTANDING_LGRT_ASM_STR
#undef FREESTANDING_LGRT_ASM

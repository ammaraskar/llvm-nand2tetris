//===-- HackCallingConv.td - Calling Conventions for Hack ----*- tablegen -*-=//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
// This describes the calling conventions for Hack architecture.
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
// Hack Return Value Calling Convention
//===----------------------------------------------------------------------===//

// Special return value calling convention for runtime functions.
def RetCC_Hack : CallingConv
<[
  CCIfType<[i8], CCAssignToReg<[D]>>,
  CCIfType<[i16], CCAssignToReg<[D]>>
]>;

//===----------------------------------------------------------------------===//
// Hack Argument Calling Conventions
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
// Callee-saved register lists.
//===----------------------------------------------------------------------===//

def CSR : CalleeSavedRegs<(add)>;

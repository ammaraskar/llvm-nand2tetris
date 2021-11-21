//===-- HackMCTargetDesc.h - Hack Target Descriptions -----------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file provides Hack specific target descriptions.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_HACK_MCTARGET_DESC_H
#define LLVM_HACK_MCTARGET_DESC_H

#include "llvm/Support/TargetRegistry.h"

namespace llvm {

extern Target TheHackTarget;

} // end namespace llvm

#define GET_REGINFO_ENUM
#include "HackGenRegisterInfo.inc"

#define GET_INSTRINFO_ENUM
#include "HackGenInstrInfo.inc"

#define GET_SUBTARGETINFO_ENUM
#include "HackGenSubtargetInfo.inc"

#endif // LLVM_HACK_MCTARGET_DESC_H

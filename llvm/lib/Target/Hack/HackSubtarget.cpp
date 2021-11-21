//===-- HackSubtarget.cpp - Hack Subtarget Information --------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements the Hack specific subclass of TargetSubtargetInfo.
//
//===----------------------------------------------------------------------===//

#include "HackSubtarget.h"

#include "llvm/Support/TargetRegistry.h"

#include "Hack.h"
#include "HackTargetMachine.h"
#include "MCTargetDesc/HackMCTargetDesc.h"

#define DEBUG_TYPE "hack-subtarget"

#define GET_SUBTARGETINFO_TARGET_DESC
#define GET_SUBTARGETINFO_CTOR
#include "HackGenSubtargetInfo.inc"

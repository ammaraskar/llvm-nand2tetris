//===-- HackFrameLowering.cpp - Hack Frame Information --------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file contains the AVR implementation of TargetFrameLowering class.
//
//===----------------------------------------------------------------------===//

#include "HackFrameLowering.h"

#include "Hack.h"

namespace llvm {

HackFrameLowering::HackFrameLowering()
    : TargetFrameLowering(TargetFrameLowering::StackGrowsDown, Align(1), 0) {}

void HackFrameLowering::emitPrologue(MachineFunction &MF,
                                     MachineBasicBlock &MBB) const {
}

void HackFrameLowering::emitEpilogue(MachineFunction &MF,
                                     MachineBasicBlock &MBB) const {
}

bool HackFrameLowering::hasFP(const MachineFunction &MF) const {
  return true;
}

} // end of namespace llvm

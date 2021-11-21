//===-- HackInstrInfo.cpp - Hack Instruction Information ------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file contains the Hack implementation of the TargetInstrInfo class.
//
//===----------------------------------------------------------------------===//

#include "HackInstrInfo.h"

#define GET_INSTRINFO_CTOR_DTOR
#include "HackGenInstrInfo.inc"

namespace llvm {

void HackInstrInfo::copyPhysReg(MachineBasicBlock &MBB,
                                MachineBasicBlock::iterator MI,
                                const DebugLoc &DL, MCRegister DestReg,
                                MCRegister SrcReg, bool KillSrc) const {
  if (SrcReg == Hack::A && DestReg == Hack::D) {
    BuildMI(MBB, MI, DL, get(Hack::MOV_A_TO_D));
  } else if (SrcReg == Hack::D && DestReg == Hack::A) {
    BuildMI(MBB, MI, DL, get(Hack::MOV_D_TO_A));
  } else {
    llvm_unreachable("Unknown register in reg-to-reg copy");
  }
}

void HackInstrInfo::storeRegToStackSlot(MachineBasicBlock &MBB,
                                        MachineBasicBlock::iterator MI,
                                        Register SrcReg, bool isKill,
                                        int FrameIndex,
                                        const TargetRegisterClass *RC,
                                        const TargetRegisterInfo *TRI) const {
  DebugLoc DL;
  if (MI != MBB.end()) {
    DL = MI->getDebugLoc();
  }

  // Spill the register onto the stack.
  if (SrcReg != Hack::D) {
    // Move the data into register D first.
    BuildMI(MBB, MI, DL, get(Hack::MOV_A_TO_D));
  }

  // Put frame pointer location in A.
  BuildMI(MBB, MI, DL, get(Hack::AInstr)).addImm(16);
  // Store D to pointer at A.
  BuildMI(MBB, MI, DL, get(Hack::STORE_D));
}

void HackInstrInfo::loadRegFromStackSlot(MachineBasicBlock &MBB,
                                         MachineBasicBlock::iterator MI,
                                         Register DestReg, int FrameIndex,
                                         const TargetRegisterClass *RC,
                                         const TargetRegisterInfo *TRI) const {
  DebugLoc DL;
  if (MI != MBB.end()) {
    DL = MI->getDebugLoc();
  }

  // Put frame pointer location in A.
  BuildMI(MBB, MI, DL, get(Hack::AInstr)).addImm(16);
  // Load D from pointer in A.
  BuildMI(MBB, MI, DL, get(Hack::LOAD_D));

  if (DestReg != Hack::D) {
    // Move the data into register A.
    BuildMI(MBB, MI, DL, get(Hack::MOV_D_TO_A));
  }
}

}

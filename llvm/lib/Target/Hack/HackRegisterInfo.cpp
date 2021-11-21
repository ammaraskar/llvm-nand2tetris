//===-- HackRegisterInfo.cpp - Hack Register Information --------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file contains the Hack implementation of the TargetRegisterInfo class.
//
//===----------------------------------------------------------------------===//

#include "HackRegisterInfo.h"

#include "llvm/ADT/BitVector.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"
#include "llvm/IR/Function.h"
#include "llvm/CodeGen/TargetFrameLowering.h"

#include "Hack.h"
#include "HackInstrInfo.h"
#include "HackTargetMachine.h"
#include "MCTargetDesc/HackMCTargetDesc.h"

#define GET_REGINFO_TARGET_DESC
#include "HackGenRegisterInfo.inc"

namespace llvm {

const uint16_t* HackRegisterInfo::getCalleeSavedRegs(const MachineFunction *MF) const {
  return CSR_SaveList;
}

BitVector HackRegisterInfo::getReservedRegs(const MachineFunction &MF) const {
  BitVector Reserved(getNumRegs());
  // No reserved registers.
  return Reserved;
}

void HackRegisterInfo::eliminateFrameIndex(MachineBasicBlock::iterator II,
                                           int SPAdj, unsigned FIOperandNum,
                                           RegScavenger *RS) const {
}

Register HackRegisterInfo::getFrameRegister(const MachineFunction &MF) const {
  return Hack::A;
}

} // end of namespace llvm

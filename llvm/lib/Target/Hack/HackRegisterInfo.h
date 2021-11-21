//===-- HackRegisterInfo.h - Hack Register Information Impl -------*- C++ -*-===//
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

#ifndef LLVM_HACK_REGISTER_INFO_H
#define LLVM_HACK_REGISTER_INFO_H

#include "llvm/CodeGen/TargetRegisterInfo.h"

#define GET_REGINFO_HEADER
#include "HackGenRegisterInfo.inc"

namespace llvm {

/// Utilities relating to Hack registers.
class HackRegisterInfo : public HackGenRegisterInfo {
public:
  HackRegisterInfo() : HackGenRegisterInfo(0) {}


  const uint16_t* getCalleeSavedRegs(const MachineFunction *MF = 0) const override;

  BitVector getReservedRegs(const MachineFunction &MF) const override;

  void eliminateFrameIndex(MachineBasicBlock::iterator MI, int SPAdj,
                           unsigned FIOperandNum,
                           RegScavenger *RS = NULL) const override;

  Register getFrameRegister(const MachineFunction &MF) const override;
};

} // end namespace llvm

#endif // LLVM_HACK_REGISTER_INFO_H

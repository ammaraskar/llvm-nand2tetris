//===-- HackInstrInfo.h - Hack Instruction Information ----------*- C++ -*-===//
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

#ifndef LLVM_HACK_INSTR_INFO_H
#define LLVM_HACK_INSTR_INFO_H

#include "llvm/CodeGen/TargetInstrInfo.h"

#include "HackRegisterInfo.h"
#include "MCTargetDesc/HackMCTargetDesc.h"

#define GET_INSTRINFO_HEADER
#include "HackGenInstrInfo.inc"
#undef GET_INSTRINFO_HEADER

namespace llvm {

/// Utilities related to the Hack instruction set.
class HackInstrInfo : public HackGenInstrInfo {
public:
  explicit HackInstrInfo() {}

  const HackRegisterInfo &getRegisterInfo() const { return RI; }

  void copyPhysReg(MachineBasicBlock &MBB, MachineBasicBlock::iterator MI,
                   const DebugLoc &DL, MCRegister DestReg, MCRegister SrcReg,
                   bool KillSrc) const override;

  void storeRegToStackSlot(MachineBasicBlock &MBB,
                           MachineBasicBlock::iterator MI, Register SrcReg,
                           bool isKill, int FrameIndex,
                           const TargetRegisterClass *RC,
                           const TargetRegisterInfo *TRI) const override;

  void loadRegFromStackSlot(MachineBasicBlock &MBB,
                            MachineBasicBlock::iterator MI, Register DestReg,
                            int FrameIndex, const TargetRegisterClass *RC,
                            const TargetRegisterInfo *TRI) const override;

private:
  const HackRegisterInfo RI;
};

} // end namespace llvm

#endif // LLVM_HACK_INSTR_INFO_H

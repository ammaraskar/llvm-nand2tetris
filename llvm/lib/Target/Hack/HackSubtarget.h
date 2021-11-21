//===-- HackSubtarget.h - Define Subtarget for the Hack ---------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file declares the Hack specific subclass of TargetSubtargetInfo.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_HACK_SUBTARGET_H
#define LLVM_HACK_SUBTARGET_H

#include "llvm/CodeGen/TargetSubtargetInfo.h"
#include "llvm/IR/DataLayout.h"
#include "llvm/Target/TargetMachine.h"

#include "Hack.h"
#include "HackFrameLowering.h"
#include "HackInstrInfo.h"
#include "HackISelLowering.h"

#define GET_SUBTARGETINFO_HEADER
#include "HackGenSubtargetInfo.inc"

namespace llvm {

/// A specific Hack target MCU.
class HackSubtarget : public HackGenSubtargetInfo {
public:
  //! Creates an Hack subtarget.
  //! \param TT  The target triple.
  //! \param CPU The CPU to target.
  //! \param FS  The feature string.
  //! \param TM  The target machine.
  HackSubtarget(const Triple &TT, const std::string &CPU, const std::string &FS,
                const HackTargetMachine &TM)
    : HackGenSubtargetInfo(TT, CPU, /*TuneCPU*/CPU, FS),
      InstrInfo(),
      FrameLowering(),
      TLInfo(TM) {}

  const HackInstrInfo *getInstrInfo() const override { return &InstrInfo; }
  const TargetFrameLowering *getFrameLowering() const override { return &FrameLowering; }
  const HackTargetLowering *getTargetLowering() const override { return &TLInfo; }
  const HackRegisterInfo *getRegisterInfo() const override { return &InstrInfo.getRegisterInfo(); }

  void ParseSubtargetFeatures(StringRef CPU, StringRef TuneCPU, StringRef FS);

private:
  HackInstrInfo InstrInfo;
  HackFrameLowering FrameLowering;
  HackTargetLowering TLInfo;
};

} // end namespace llvm

#endif // LLVM_HACK_SUBTARGET_H

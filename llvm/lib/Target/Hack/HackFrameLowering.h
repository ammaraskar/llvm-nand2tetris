//===-- HackFrameLowering.h - Define frame lowering for Hack ----*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_HACK_FRAME_LOWERING_H
#define LLVM_HACK_FRAME_LOWERING_H

#include "llvm/CodeGen/TargetFrameLowering.h"

namespace llvm {

/// Utilities for creating function call frames.
class HackFrameLowering : public TargetFrameLowering {
public:
  explicit HackFrameLowering();

public:
  void emitPrologue(MachineFunction &MF, MachineBasicBlock &MBB) const override;
  void emitEpilogue(MachineFunction &MF, MachineBasicBlock &MBB) const override;
  bool hasFP(const MachineFunction &MF) const override;
};

} // end namespace llvm

#endif // LLVM_HACK_FRAME_LOWERING_H

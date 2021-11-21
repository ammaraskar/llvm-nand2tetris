//===-- HackTargetMachine.h - Define TargetMachine for Hack -----*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file declares the Hack specific subclass of TargetMachine.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_HACK_TARGET_MACHINE_H
#define LLVM_HACK_TARGET_MACHINE_H

#include "llvm/Target/TargetMachine.h"

#include "HackSubtarget.h"

namespace llvm {

class HackTargetMachine : public LLVMTargetMachine {
public:
  HackTargetMachine(const Target &T, const Triple &TT, StringRef CPU,
                    StringRef FS, const TargetOptions &Options,
                    Optional<Reloc::Model> RM,
                    Optional<CodeModel::Model> CM,
                    CodeGenOpt::Level OL, bool JIT);

  TargetLoweringObjectFile *getObjFileLowering() const override {
    return this->TLOF.get();
  }

  const HackSubtarget *getSubtargetImpl() const {
    return &SubTarget;
  };
  const HackSubtarget *getSubtargetImpl(const Function &) const override {
    return &SubTarget;
  };

  TargetPassConfig *createPassConfig(PassManagerBase &PM) override;

private:
  std::unique_ptr<TargetLoweringObjectFile> TLOF;
  HackSubtarget SubTarget;
};

} // end namespace llvm

#endif // LLVM_HACK_TARGET_MACHINE_H

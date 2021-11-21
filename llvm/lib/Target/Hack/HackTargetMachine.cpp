//===-- HackTargetMachine.cpp - Define TargetMachine for Hack -------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file defines the Hack specific subclass of TargetMachine.
//
//===----------------------------------------------------------------------===//

#include "HackTargetMachine.h"

#include "llvm/CodeGen/TargetPassConfig.h"
#include "llvm/Support/CodeGen.h"
#include "llvm/Support/Compiler.h"
#include "llvm/Support/TargetRegistry.h"

#include "Hack.h"
#include "HackTargetObjectFile.h"
#include "TargetInfo/HackTargetInfo.h"

namespace llvm {

// E      - Big Endian
// P1     - Harvard Architecture with program space 1
// p:16:8 - Pointers are 16 bit-sized and 16-bit (ABI) aligned.
// n16    - Native integers are 16 bits.
static const char *HackDataLayout = "E-P1-p:16:16-n16";

HackTargetMachine::HackTargetMachine(const Target &T, const Triple &TT,
                                     StringRef CPU, StringRef FS,
                                     const TargetOptions &Options,
                                     Optional<Reloc::Model> RM,
                                     Optional<CodeModel::Model> CM,
                                     CodeGenOpt::Level OL, bool JIT)
    : LLVMTargetMachine(T, HackDataLayout, TT, /*CPU=*/"generic", FS, Options,
                        /*RelocModel=*/Reloc::Static,
                        getEffectiveCodeModel(CM, CodeModel::Small), OL), 
      SubTarget(TT, std::string(CPU), std::string(FS), *this) {
  this->TLOF = std::make_unique<HackTargetObjectFile>();
  initAsmInfo();
}

namespace {
/// Hack Code Generator Pass Configuration Options.
class HackPassConfig : public TargetPassConfig {
public:
  HackPassConfig(HackTargetMachine &TM, PassManagerBase &PM)
      : TargetPassConfig(TM, PM) {}

  HackTargetMachine &getHackTargetMachine() const {
    return getTM<HackTargetMachine>();
  }

  bool addInstSelector() override;
};

//===----------------------------------------------------------------------===//
// Pass Pipeline Configuration
//===----------------------------------------------------------------------===//

bool HackPassConfig::addInstSelector() {
  // Install an instruction selector.
  addPass(createHackISelDag(getHackTargetMachine(), getOptLevel()));
  return false;
}

} // namespace

TargetPassConfig *HackTargetMachine::createPassConfig(PassManagerBase &PM) {
  return new HackPassConfig(*this, PM);
}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeHackTarget() {
  // Register the target.
  RegisterTargetMachine<HackTargetMachine> X(getTheHackTarget());
}

} // end namespace llvm

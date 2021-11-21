//===-- HackMCTargetDesc.cpp - Hack Target Descriptions -------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file provides Hack specific target descriptions.
//
//===----------------------------------------------------------------------===//

#include "HackMCTargetDesc.h"
#include "HackMCAsmInfo.h"
#include "HackInstPrinter.h"
#include "TargetInfo/HackTargetInfo.h"

#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/Support/TargetRegistry.h"

#define GET_INSTRINFO_MC_DESC
#include "HackGenInstrInfo.inc"

#define GET_SUBTARGETINFO_MC_DESC
#include "HackGenSubtargetInfo.inc"

#define GET_REGINFO_MC_DESC
#include "HackGenRegisterInfo.inc"

using namespace llvm;

MCInstrInfo *createHackMCInstrInfo() {
  MCInstrInfo *X = new MCInstrInfo();
  InitHackMCInstrInfo(X);
  return X;
}

MCRegisterInfo *createHackMCRegisterInfo(const Triple &TT) {
  MCRegisterInfo *X = new MCRegisterInfo();
  InitHackMCRegisterInfo(X, 0);
  return X;
}

MCSubtargetInfo *createHackMCSubtargetInfo(const Triple &TT,
                                                 StringRef CPU, StringRef FS) {
  return createHackMCSubtargetInfoImpl(TT, CPU, /*TuneCPU*/ CPU, FS);
}

static MCInstPrinter *createHackMCInstPrinter(const Triple &T,
                                             unsigned SyntaxVariant,
                                             const MCAsmInfo &MAI,
                                             const MCInstrInfo &MII,
                                             const MCRegisterInfo &MRI) {
  if (SyntaxVariant == 0) {
    return new HackInstPrinter(MAI, MII, MRI);
  }

  return nullptr;
}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeHackTargetMC() {
  // Register the MC asm info.
  RegisterMCAsmInfo<HackMCAsmInfo> X(getTheHackTarget());

  // Register the MC instruction info.
  TargetRegistry::RegisterMCInstrInfo(getTheHackTarget(), createHackMCInstrInfo);

  // Register the MC register info.
  TargetRegistry::RegisterMCRegInfo(getTheHackTarget(), createHackMCRegisterInfo);

  // Register the MC subtarget info.
  TargetRegistry::RegisterMCSubtargetInfo(getTheHackTarget(),
                                          createHackMCSubtargetInfo);

  // Register the MCInstPrinter.
  TargetRegistry::RegisterMCInstPrinter(getTheHackTarget(),
                                        createHackMCInstPrinter);
}

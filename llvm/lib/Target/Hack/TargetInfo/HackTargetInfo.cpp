//===-- HackTargetInfo.cpp - Hack Target Implementation -------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "llvm/Support/TargetRegistry.h"

namespace llvm {

Target &getTheHackTarget() {
  static Target TheHackTarget;
  return TheHackTarget;
}

} // end namespace llvm

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeHackTargetInfo() {
  llvm::RegisterTarget<llvm::Triple::hack> X(llvm::getTheHackTarget(), "hack",
                                            "Hack (Nand2Teris) Computer", "Hack");
}

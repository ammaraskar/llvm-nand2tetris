//===-- Hack.h - Top-level interface for Hack representation ----*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file contains the entry points for global functions defined in the LLVM
// Hack back-end.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_HACK_H
#define LLVM_HACK_H

#include "llvm/CodeGen/SelectionDAGNodes.h"
#include "llvm/Target/TargetMachine.h"

namespace llvm {

class HackTargetMachine;
class FunctionPass;

FunctionPass *createHackISelDag(HackTargetMachine &TM,
                                CodeGenOpt::Level OptLevel);

} // end namespace llvm

#endif // LLVM_HACK_H
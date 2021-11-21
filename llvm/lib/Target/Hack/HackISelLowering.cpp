//===-- HackISelLowering.cpp - Hack DAG Lowering Implementation -----------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file defines the interfaces that Hack uses to lower LLVM code into a
// selection DAG.
//
//===----------------------------------------------------------------------===//

#include "HackISelLowering.h"

#include "HackTargetMachine.h"
#include "MCTargetDesc/HackMCTargetDesc.h"

namespace llvm {

HackTargetLowering::HackTargetLowering(const HackTargetMachine &TM)
    : TargetLowering(TM) {
  // Set up the register classes.
  addRegisterClass(MVT::i16, &Hack::GPRRegClass);

  // Compute derived properties from the register classes.
  computeRegisterProperties(TM.getSubtargetImpl()->getRegisterInfo());
}

//===----------------------------------------------------------------------===//
//             Formal Arguments Calling Convention Implementation
//===----------------------------------------------------------------------===//

#include "HackGenCallingConv.inc"

SDValue HackTargetLowering::LowerFormalArguments(
    SDValue Chain, CallingConv::ID CallConv, bool isVarArg,
    const SmallVectorImpl<ISD::InputArg> &Ins, const SDLoc &dl,
    SelectionDAG &DAG, SmallVectorImpl<SDValue> &InVals) const {

  llvm::errs() << "HackTargetLowering::LowerFormalArguments\n";
  llvm::errs() << "  Chain: "; Chain.dump();
  llvm::errs() << "  DAG: "; DAG.dump();
  llvm::errs() << "  CallConv: " << CallConv << "\n";

  // Assign locations to all of the incoming arguments.
  SmallVector<CCValAssign, 16> ArgLocs;
  CCState CCInfo(CallConv, isVarArg, DAG.getMachineFunction(), ArgLocs,
                 *DAG.getContext());
  CCInfo.AnalyzeFormalArguments(Ins, RetCC_Hack);

  return Chain;
}

SDValue HackTargetLowering::LowerReturn(
    SDValue Chain, CallingConv::ID CallConv, bool IsVarArg,
    const SmallVectorImpl<ISD::OutputArg> &Outs,
    const SmallVectorImpl<SDValue> &OutVals,
    const SDLoc &DL, SelectionDAG &DAG) const {

  llvm::errs() << "HackTargetLowering::LowerReturn\n";
  llvm::errs() << "  Chain: "; Chain.dump();
  llvm::errs() << "  DAG: "; DAG.dump();
  llvm::errs() << "  CallConv: " << CallConv << "\n";

  // CCValAssign - represent the assignment of the return value to locations.
  SmallVector<CCValAssign, 16> RVLocs;

  // CCState - Info about the registers and stack slot.
  CCState CCInfo(CallConv, IsVarArg, DAG.getMachineFunction(), RVLocs,
                 *DAG.getContext());

  return Chain;
}

}

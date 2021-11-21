//===-- Hack.td - Describe the Hack Target Machine --------*- tablegen -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===---------------------------------------------------------------------===//
// This is the top level entry point for the Hack target.
//===---------------------------------------------------------------------===//

//===---------------------------------------------------------------------===//
// Target-independent interfaces which we are implementing
//===---------------------------------------------------------------------===//

include "llvm/Target/Target.td"

//===---------------------------------------------------------------------===//
// Hack Device Definitions
//===---------------------------------------------------------------------===//

class Proc<string Name, list<SubtargetFeature> Features>
  : Processor<Name, NoItineraries, Features>;

def : Proc<"generic", []>;

//===---------------------------------------------------------------------===//
// Register File Description
//===---------------------------------------------------------------------===//

include "HackRegisterInfo.td"

//===---------------------------------------------------------------------===//
// Instruction Descriptions
//===---------------------------------------------------------------------===//

include "HackInstrInfo.td"

def HackInstrInfo : InstrInfo;

//===---------------------------------------------------------------------===//
// Calling Conventions
//===---------------------------------------------------------------------===//

include "HackCallingConv.td"

//===---------------------------------------------------------------------===//
// Target Declaration
//===---------------------------------------------------------------------===//

def Hack : Target {
  let InstructionSet = HackInstrInfo;
}

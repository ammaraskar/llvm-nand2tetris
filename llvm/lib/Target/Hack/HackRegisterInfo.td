//===-- HackRegisterInfo.td - Hack Register defs -----------*- tablegen -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
//  Declarations that describe the Hack register file
//===----------------------------------------------------------------------===//

class HackReg<string name>
  : Register<name>
{
  let Namespace = "Hack";
}

//===----------------------------------------------------------------------===//
//  16-bit general purpose registers
//===----------------------------------------------------------------------===//

def A  : HackReg<"A">,  DwarfRegNum<[0]>;
def D  : HackReg<"D">,  DwarfRegNum<[1]>;

//===----------------------------------------------------------------------===//
// Register Classes
//===----------------------------------------------------------------------===//

// Main 16-bit register class.
def GPR : RegisterClass<"Hack", [i16], 16,
  (
    add A, D
  )>;

// A separate class for registers that can be used for memory access (only A).
def PTRREGS : RegisterClass<"Hack", [i16], 16,
  (
    add A
  )>;

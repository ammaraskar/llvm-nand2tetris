//===-- HackInstrInfo.td - Hack Instruction defs -----------*- tablegen -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file describes the Hack instructions in TableGen format.
//
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
// A-type instructions: <|1|iiiiiiiiiiiiiii|>
// i = immediate = 15 bits
//===----------------------------------------------------------------------===//
def uimm15 : PatLeaf<(imm), [{ return isUInt<15>(N->getZExtValue()); }]>;

class ATypeInstruction : Instruction {
  let Namespace = "Hack";
  let isMoveImm = true;
  let hasSideEffects = false;

  bits<15> val;
  // Take an ui15 immediate in, output is not dynamic (always goes into reg A)
  // so we use Defs there.
  let InOperandList = (ins i16imm:$val);
  let OutOperandList = (outs);
  let Defs = [A];

  // ASM and semantics.
  let AsmString = "A := $val";
  let Pattern = [(set A, uimm15:$val)];

  // Instruction encoding.
  field bits<16> Inst;
  let Size = 2;

  let Inst{15} = 1;
  let Inst{14-0} = val{14-0};
}

def AInstr : ATypeInstruction;


class CTypeInstruction<bits<7> opcode, bits<3> assignment_code, bits<3> jumpcode,
                       dag outs, dag ins,
                       string asmstr, list<dag> pattern> : Instruction {
  let Namespace = "Hack";

  dag OutOperandList = outs;
  dag InOperandList = ins;
  let AsmString = asmstr;
  let Pattern = pattern;

  field bits<16> Inst;
  let Size = 2;
  let Inst{15-13} = 0b111;
  let Inst{12-6} = opcode;
  let Inst{5-3} = assignment_code;
  let Inst{2-0} = jumpcode;
}

// Store to memory from register.
let mayStore = 1,
    hasSideEffects = 0,
    Uses = [D] in
def STORE_D: CTypeInstruction<0b0001100, 0b010, 0b000,
                              (outs), (ins),
                              "*A = D",
                              [(store D, A)]>;

// Load to register from memory.
let mayLoad = 1,
    hasSideEffects = 0,
    Uses = [A],
    Defs = [D] in
def LOAD_D: CTypeInstruction<0b1110000, 0b010, 0b000,
                             (outs), (ins),
                             "D = *A",
                             [(set D, (load A))]>;

// Load to register from memory.
let mayLoad = 1,
    hasSideEffects = 0,
    Uses = [A],
    Defs = [A] in
def LOAD_A: CTypeInstruction<0b1110000, 0b100, 0b000,
                             (outs), (ins),
                             "D = *A",
                             [(set D, (load A))]>;

// Move from A to D
let isMoveReg = 1,
    Uses = [A],
    Defs = [D] in
def MOV_A_TO_D: CTypeInstruction<0b0110000, 0b010, 0b000,
                                 (outs), (ins),
                                 "D = A",
                                 [(set D, A)]>;

// Move from D to A
let isMoveReg = 1,
    Uses = [D],
    Defs = [A] in
def MOV_D_TO_A: CTypeInstruction<0b0001100, 0b100, 0b000,
                                 (outs), (ins),
                                 "A = D",
                                 [(set A, D)]>;

// Unconditional jump: `0; jmp`
let Uses = [A],
    isBarrier = 1,
    isBranch = 1,
    isTerminator = 1 in
def JMP: CTypeInstruction<0b0101010, 0b000, 0b111,
                          (outs), (ins),
                          "0; jmp",
                          []>;

// Return instruction implemented as an unconditional jump.
let isBarrier = 1,
    isReturn = 1,
    isTerminator = 1 in
def RET: CTypeInstruction<0b0101010, 0b000, 0b111,
                          (outs), (ins),
                          "0; jmp",
                          []>;


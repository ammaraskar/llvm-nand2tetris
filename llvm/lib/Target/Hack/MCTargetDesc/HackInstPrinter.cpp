//===-- HackInstPrinter.cpp - Convert Hack MCInst to assembly syntax --------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This class prints an Hack MCInst to a .s file.
//
//===----------------------------------------------------------------------===//

#include "HackInstPrinter.h"

#include "MCTargetDesc/HackMCTargetDesc.h"

#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCInstrDesc.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/FormattedStream.h"

#include <cstring>

#define DEBUG_TYPE "asm-printer"

namespace llvm {

// Include the auto-generated portion of the assembly writer.
#define PRINT_ALIAS_INSTR
#include "HackGenAsmWriter.inc"

void HackInstPrinter::printInst(const MCInst *MI, uint64_t Address,
                                StringRef Annot, const MCSubtargetInfo &STI,
                                raw_ostream &O) {
  printInstruction(MI, Address, O);
}

const char *HackInstPrinter::getPrettyRegisterName(unsigned RegNum,
                                                  MCRegisterInfo const &MRI) {
  return getRegisterName(RegNum);
}

void HackInstPrinter::printOperand(const MCInst *MI, unsigned OpNo,
                                   raw_ostream &O) {
  const MCOperand &mo = MI->getOperand(OpNo);

  if (mo.isReg()) {
    printRegName(O, mo.getReg());
    return;
  } else if (mo.isImm()) {
    O << (int) mo.getImm();
    return;
  }
  
  assert(mo.isExpr() && "Unknown operand kind in printOperand");
  mo.getExpr()->print(O, &MAI);
}

} // end of namespace llvm


//===-- HackMCAsmInfo.cpp - Hack asm properties -----------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file contains the declarations of the HackMCAsmInfo properties.
//
//===----------------------------------------------------------------------===//

#include "HackMCAsmInfo.h"

#include "llvm/ADT/Triple.h"

namespace llvm {

HackMCAsmInfo::HackMCAsmInfo(const Triple &TT, const MCTargetOptions &Options) {
  CodePointerSize = 2;
  CommentString = "//";
  SupportsDebugInformation = false;
}

} // end of namespace llvm

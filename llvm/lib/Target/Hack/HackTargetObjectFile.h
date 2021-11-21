//===-- HackTargetObjectFile.h - Hack Object Info ---------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_HACK_TARGET_OBJECT_FILE_H
#define LLVM_HACK_TARGET_OBJECT_FILE_H

#include "llvm/CodeGen/TargetLoweringObjectFileImpl.h"

namespace llvm {

/// Lowering for an Hack ELF32 object file.
class HackTargetObjectFile : public TargetLoweringObjectFileELF {
};

} // end namespace llvm

#endif // LLVM_HACK_TARGET_OBJECT_FILE_H

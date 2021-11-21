add_llvm_component_group(Hack)

set(LLVM_TARGET_DEFINITIONS Hack.td)

tablegen(LLVM HackGenAsmWriter.inc -gen-asm-writer)
tablegen(LLVM HackGenCallingConv.inc -gen-callingconv)
tablegen(LLVM HackGenDAGISel.inc -gen-dag-isel)
tablegen(LLVM HackGenRegisterInfo.inc -gen-register-info)
tablegen(LLVM HackGenInstrInfo.inc -gen-instr-info)
tablegen(LLVM HackGenSubtargetInfo.inc -gen-subtarget)

add_public_tablegen_target(HackCommonTableGen)

add_llvm_target(HackCodeGen
  HackTargetMachine.cpp
  HackAsmPrinter.cpp
  HackFrameLowering.cpp
  HackInstrInfo.cpp
  HackISelDAGToDAG.cpp
  HackISelLowering.cpp
  HackRegisterInfo.cpp
  HackSubtarget.cpp

  LINK_COMPONENTS
  AsmPrinter
  CodeGen
  SelectionDAG
  Support
  Target

  ADD_TO_COMPONENT
  Hack
)

add_subdirectory(TargetInfo)
add_subdirectory(MCTargetDesc)

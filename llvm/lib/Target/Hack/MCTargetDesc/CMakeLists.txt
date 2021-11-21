add_llvm_component_library(LLVMHackDesc
  HackMCTargetDesc.cpp
  HackMCAsmInfo.cpp
  HackInstPrinter.cpp

  LINK_COMPONENTS
  MC
  HackInfo
  Support

  ADD_TO_COMPONENT
  Hack
)

add_dependencies(LLVMHackDesc HackCommonTableGen)

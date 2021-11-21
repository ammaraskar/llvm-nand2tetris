add_llvm_component_library(LLVMHackInfo
  HackTargetInfo.cpp

  LINK_COMPONENTS
  Support

  ADD_TO_COMPONENT
  Hack
)

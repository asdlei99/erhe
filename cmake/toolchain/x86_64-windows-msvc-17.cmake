set(CMAKE_CXX_FLAGS "/fp:fast")
set(CMAKE_EXE_LINKER_FLAGS_DEBUG "/DEBUG /INCREMENTAL:NO")
set(CMAKE_SHARED_LINKER_FLAGS_DEBUG "/DEBUG /INCREMENTAL:NO")
set(CMAKE_MODULE_LINKER_FLAGS_DEBUG "/DEBUG /INCREMENTAL:NO")
set(CMAKE_STATIC_LINKER_FLAGS_DEBUG "")
set(CMAKE_EXE_LINKER_FLAGS_PROFILE "/OPT:REF /OPT:ICF=2 /DEBUG /INCREMENTAL:NO")
set(CMAKE_SHARED_LINKER_FLAGS_PROFILE "/OPT:REF /OPT:ICF=2 /DEBUG /INCREMENTAL:NO")
set(CMAKE_MODULE_LINKER_FLAGS_PROFILE "/OPT:REF /OPT:ICF=2 /DEBUG /INCREMENTAL:NO")
set(CMAKE_STATIC_LINKER_FLAGS_PROFILE "")
set(CMAKE_EXE_LINKER_FLAGS_RELEASE "/OPT:REF /OPT:ICF=2 /INCREMENTAL:NO")
set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "/OPT:REF /OPT:ICF=2 /INCREMENTAL:NO")
set(CMAKE_MODULE_LINKER_FLAGS_RELEASE "/OPT:REF /OPT:ICF=2 /INCREMENTAL:NO")
set(CMAKE_STATIC_LINKER_FLAGS_RELEASE "")

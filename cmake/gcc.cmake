# This file was automatically generated by RASC

# Get the configuration settings generated by RASC
include(cmake/GeneratedCfg.cmake)

# Get the user configuration settings
# this file should define path for toolchain binary path
include(${CMAKE_CURRENT_LIST_DIR}/../Config.cmake)
# It can be used to specify the target environment location
# e.g compiler's location. This variable is most useful when crosscompiling.
#(Should avoid spaces in the path or have to escape them)
if (NOT CMAKE_FIND_ROOT_PATH)
message(FATAL_ERROR "Toolchain path not defined. Please set CMAKE_FIND_ROOT_PATH variable in Config.cmake file to set the toolchain's bin folder")
endif()

# set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)

# Use add_library() with the STATIC option to name the source file in the generated project. 
# This avoids running the linker and is intended for use with cross-compiling toolchains that 
# cannot link without custom flags or linker scripts
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# find_program(CMAKE_C_COMPILER NAMES arm-none-eabi-gcc arm-none-eabi-gcc.exe PATHS ${CMAKE_FIND_ROOT_PATH} REQUIRED)
# find_program(CMAKE_CXX_COMPILER NAMES arm-none-eabi-g++ arm-none-eabi-g++.exe PATHS ${CMAKE_FIND_ROOT_PATH} REQUIRED)
# find_program(CMAKE_ASM_COMPILER NAMES arm-none-eabi-gcc arm-none-eabi-gcc.exe PATHS ${CMAKE_FIND_ROOT_PATH} REQUIRED)
# find_program(CMAKE_AR NAMES arm-none-eabi-gcc-ar arm-none-eabi-gcc-ar.exe PATHS ${CMAKE_FIND_ROOT_PATH} REQUIRED)
# find_program(CMAKE_CXX_COMPILER_AR NAMES arm-none-eabi-gcc-ar arm-none-eabi-gcc-ar.exe PATHS ${CMAKE_FIND_ROOT_PATH} REQUIRED)
# find_program(CMAKE_C_COMPILER_AR NAMES arm-none-eabi-gcc-ar arm-none-eabi-gcc-ar.exe PATHS ${CMAKE_FIND_ROOT_PATH} REQUIRED)
# find_program(CMAKE_LINKER NAMES arm-none-eabi-g++ arm-none-eabi-g++.exe PATHS ${CMAKE_FIND_ROOT_PATH} REQUIRED)
# find_program(CMAKE_OBJCOPY NAMES arm-none-eabi-objcopy arm-none-eabi-objcopy.exe PATHS ${CMAKE_FIND_ROOT_PATH} REQUIRED)

if (CMAKE_HOST_WIN32 )
  SET(BINARY_FILE_EXT ".exe")
else()
  SET(BINARY_FILE_EXT "")
endif()

# CMake variables for compiler, assembler, native build system
# Specify the C compiler
SET(CMAKE_C_COMPILER ${CMAKE_FIND_ROOT_PATH}/arm-none-eabi-gcc${BINARY_FILE_EXT})
SET(CMAKE_C_COMPILER_ID CCRX)
SET(CMAKE_C_COMPILER_ID_RUN TRUE)
SET(CMAKE_C_COMPILER_FORCED TRUE)
# Specify the CPP compiler
SET(CMAKE_CXX_COMPILER ${CMAKE_FIND_ROOT_PATH}/arm-none-eabi-g++${BINARY_FILE_EXT})
SET(CMAKE_CXX_COMPILER_ID CCRX)
SET(CMAKE_CXX_COMPILER_ID_RUN TRUE)
SET(CMAKE_CXX_COMPILER_FORCED TRUE)
# Specify the ASM compiler
SET(CMAKE_ASM_COMPILER ${CMAKE_FIND_ROOT_PATH}/arm-none-eabi-gcc${BINARY_FILE_EXT})
SET(CMAKE_ASM_COMPILER_FORCED TRUE)
# Specify the linker
SET(CMAKE_LINKER ${CMAKE_FIND_ROOT_PATH}/arm-none-eabi-gcc${BINARY_FILE_EXT})

SET(CMAKE_CXX_FLAGS ${RASC_CMAKE_CXX_FLAGS})
SET(CMAKE_ASM_FLAGS ${RASC_CMAKE_ASM_FLAGS})
SET(FLAGS ${CMAKE_ASM_FLAGS} ${CMAKE_CXX_FLAGS})
SET(CMAKE_C_FLAGS ${RASC_CMAKE_C_FLAGS})
SET(CMAKE_C_COMPILE_OBJECT "${CMAKE_C_COMPILER} ${CMAKE_C_FLAGS} -c -o <OBJECT> -x c <SOURCE>")
SET(CMAKE_CXX_COMPILE_OBJECT "${CMAKE_CXX_COMPILER} ${CMAKE_CXX_FLAGS} -c -o <OBJECT> -x c <SOURCE>")
SET(CMAKE_EXE_LINKER_FLAGS ${RASC_CMAKE_EXE_LINKER_FLAGS})
SET(CMAKE_C_LINK_EXECUTABLE "${CMAKE_LINKER} ${CMAKE_EXE_LINKER_FLAGS} -Wl,--start-group <OBJECTS> -Wl,--end-group")
SET(CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_LINKER} ${CMAKE_EXE_LINKER_FLAGS} -Wl,--start-group <OBJECTS> -Wl,--end-group")
SET(ASM_FILES ${RASC_ASM_FILES})

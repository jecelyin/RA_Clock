# You can call cmake from command line by toolchain file argument   use `-DCMAKE_TOOLCHAIN_FILE=cmake/gcc.cmake`

# Project minimum required CMake version
cmake_minimum_required(VERSION 3.16.4)


# specify cross compilers and tools
#set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_C_COMPILER cc)
#set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_CXX_COMPILER g++)
#set(CMAKE_ASM_COMPILER  arm-none-eabi-gcc)
set(CMAKE_ASM_COMPILER  cc)
set(CMAKE_AR arm-none-eabi-ar)
set(CMAKE_OBJCOPY arm-none-eabi-objcopy)
set(CMAKE_OBJDUMP arm-none-eabi-objdump)
set(SIZE arm-none-eabi-size)
set(CMAKE_OSX_ARCHITECTURES "" CACHE STRING "Build architectures for Mac OS X" FORCE)
#set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# Project configuration
project(RA_Clock
	VERSION 1.0.0
	LANGUAGES C CXX ASM)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)
#add_compile_options(-mcpu=cortex-m4 -mthumb -mthumb-interwork)
add_compile_options(-ffunction-sections -fdata-sections -fno-common -fmessage-length=0)

# uncomment to mitigate c++17 absolute addresses warnings
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-register")

# Enable assembler files preprocessing
add_compile_options($<$<COMPILE_LANGUAGE:ASM>:-x$<SEMICOLON>assembler-with-cpp>)

include(${CMAKE_CURRENT_LIST_DIR}/cmake/GeneratedSrc.cmake)

# This file was automatically generated by RASC

set(RASC_EXE_PATH "C:/Users/jecelyin/AppData/Local/Programs/Renesas/RA/sc_v2023-04_fsp_v4.5.0/eclipse/rasc.exe")
set(RASC_TARGET_DEVICE R7FA2E1A7)
set(RASC_TARGET_ARCH cortex-m23)
set(RASC_PROJECT_NAME RA_Clock)
SET(RASC_TOOLCHAIN_NAME, ARMv6)
SET(RASC_CMAKE_CXX_FLAGS "              ")
SET(RASC_CMAKE_ASM_FLAGS "              ")
SET(RASC_CMAKE_C_FLAGS "              ")
SET(RASC_CMAKE_EXE_LINKER_FLAGS "       ")
SET(RASC_ASM_FILES "${CMAKE_CURRENT_SOURCE_DIR}/ra_gen/*.asm")

# Custom targets are defined below
include_guard()

# Create platform-specific command line for running Smart Configurator as a backgrounded
# process, which avoids blocking any calling IDEs
file(TO_NATIVE_PATH "${RASC_EXE_PATH}" RASC_EXE_NATIVE_PATH)
if(CMAKE_HOST_WIN32)
    set(RASC_COMMAND start "" /b "${RASC_EXE_NATIVE_PATH}" configuration.xml)
else()
    set(RASC_COMMAND sh -c \"${RASC_EXE_NATIVE_PATH} configuration.xml &\")
endif()

# Make target for opening the FSP Configuration in Smart Configurator
add_custom_target(rasc
    COMMAND ${RASC_COMMAND}
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
    COMMENT "FSP Smart Configurator"
)
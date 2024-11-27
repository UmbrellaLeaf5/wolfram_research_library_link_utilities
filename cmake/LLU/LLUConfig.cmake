# LLUConfig file
# Inspired by https://pabloariasal.github.io/2018/02/19/its-time-to-do-cmake-right/
# Author: Rafal Chojna - rafalc@wolfram.com

get_filename_component(LLU_CMAKE_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
include(CMakeFindDependencyMacro)

# Include cmake script with utility functions
include(${LLU_CMAKE_DIR}/Wolfram/Common.cmake)

# Include cmake script with utility functions
include(${LLU_CMAKE_DIR}/Wolfram/PacletUtilities.cmake)

list(APPEND CMAKE_MODULE_PATH ${LLU_CMAKE_DIR})

find_package(WolframLanguage 12.0 QUIET COMPONENTS WolframLibrary WSTP OPTIONAL_COMPONENTS wolframscript)

find_dependency(WolframLibrary 5)
find_dependency(WSTP 4.25)

if(NOT TARGET LLU::LLU)
	include("${LLU_CMAKE_DIR}/LLUTargets.cmake")
endif()

set(LLU_LIBRARIES LLU::LLU)

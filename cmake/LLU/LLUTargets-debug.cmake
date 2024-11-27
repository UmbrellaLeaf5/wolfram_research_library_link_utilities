#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "LLU::LLU" for configuration "Debug"
set_property(TARGET LLU::LLU APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(LLU::LLU PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libLLU.a"
  )

list(APPEND _cmake_import_check_targets LLU::LLU )
list(APPEND _cmake_import_check_files_for_LLU::LLU "${_IMPORT_PREFIX}/lib/libLLU.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)

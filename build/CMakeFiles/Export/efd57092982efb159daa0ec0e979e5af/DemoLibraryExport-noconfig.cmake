#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "DemoLibrary::DemoLibrary" for configuration ""
set_property(TARGET DemoLibrary::DemoLibrary APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(DemoLibrary::DemoLibrary PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NOCONFIG "C"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libDemoLibrary.a"
  )

list(APPEND _cmake_import_check_targets DemoLibrary::DemoLibrary )
list(APPEND _cmake_import_check_files_for_DemoLibrary::DemoLibrary "${_IMPORT_PREFIX}/lib/libDemoLibrary.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)

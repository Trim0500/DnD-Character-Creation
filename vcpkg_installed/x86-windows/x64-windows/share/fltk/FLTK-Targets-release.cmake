#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "fluid" for configuration "Release"
set_property(TARGET fluid APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(fluid PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/tools/fltk/fluid.exe"
  )

list(APPEND _cmake_import_check_targets fluid )
list(APPEND _cmake_import_check_files_for_fluid "${_IMPORT_PREFIX}/tools/fltk/fluid.exe" )

# Import target "fltk" for configuration "Release"
set_property(TARGET fltk APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(fltk PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C;CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/fltk.lib"
  )

list(APPEND _cmake_import_check_targets fltk )
list(APPEND _cmake_import_check_files_for_fltk "${_IMPORT_PREFIX}/lib/fltk.lib" )

# Import target "fltk_forms" for configuration "Release"
set_property(TARGET fltk_forms APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(fltk_forms PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/fltk_forms.lib"
  )

list(APPEND _cmake_import_check_targets fltk_forms )
list(APPEND _cmake_import_check_files_for_fltk_forms "${_IMPORT_PREFIX}/lib/fltk_forms.lib" )

# Import target "fltk_images" for configuration "Release"
set_property(TARGET fltk_images APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(fltk_images PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/fltk_images.lib"
  )

list(APPEND _cmake_import_check_targets fltk_images )
list(APPEND _cmake_import_check_files_for_fltk_images "${_IMPORT_PREFIX}/lib/fltk_images.lib" )

# Import target "fltk_gl" for configuration "Release"
set_property(TARGET fltk_gl APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(fltk_gl PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/fltk_gl.lib"
  )

list(APPEND _cmake_import_check_targets fltk_gl )
list(APPEND _cmake_import_check_files_for_fltk_gl "${_IMPORT_PREFIX}/lib/fltk_gl.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)

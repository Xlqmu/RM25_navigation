# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_opennav_docking_core_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED opennav_docking_core_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(opennav_docking_core_FOUND FALSE)
  elseif(NOT opennav_docking_core_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(opennav_docking_core_FOUND FALSE)
  endif()
  return()
endif()
set(_opennav_docking_core_CONFIG_INCLUDED TRUE)

# output package information
if(NOT opennav_docking_core_FIND_QUIETLY)
  message(STATUS "Found opennav_docking_core: 1.3.1 (${opennav_docking_core_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'opennav_docking_core' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT ${opennav_docking_core_DEPRECATED_QUIET})
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(opennav_docking_core_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "ament_cmake_export_include_directories-extras.cmake;ament_cmake_export_dependencies-extras.cmake;ament_cmake_export_targets-extras.cmake")
foreach(_extra ${_extras})
  include("${opennav_docking_core_DIR}/${_extra}")
endforeach()
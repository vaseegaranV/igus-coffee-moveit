# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_igus_rebel_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED igus_rebel_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(igus_rebel_FOUND FALSE)
  elseif(NOT igus_rebel_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(igus_rebel_FOUND FALSE)
  endif()
  return()
endif()
set(_igus_rebel_CONFIG_INCLUDED TRUE)

# output package information
if(NOT igus_rebel_FIND_QUIETLY)
  message(STATUS "Found igus_rebel: 0.0.0 (${igus_rebel_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'igus_rebel' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT igus_rebel_DEPRECATED_QUIET)
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(igus_rebel_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "")
foreach(_extra ${_extras})
  include("${igus_rebel_DIR}/${_extra}")
endforeach()

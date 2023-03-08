# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_predictor_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED predictor_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(predictor_FOUND FALSE)
  elseif(NOT predictor_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(predictor_FOUND FALSE)
  endif()
  return()
endif()
set(_predictor_CONFIG_INCLUDED TRUE)

# output package information
if(NOT predictor_FIND_QUIETLY)
  message(STATUS "Found predictor: 0.0.0 (${predictor_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'predictor' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT ${predictor_DEPRECATED_QUIET})
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(predictor_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "")
foreach(_extra ${_extras})
  include("${predictor_DIR}/${_extra}")
endforeach()

# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_video_recorder_pkg_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED video_recorder_pkg_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(video_recorder_pkg_FOUND FALSE)
  elseif(NOT video_recorder_pkg_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(video_recorder_pkg_FOUND FALSE)
  endif()
  return()
endif()
set(_video_recorder_pkg_CONFIG_INCLUDED TRUE)

# output package information
if(NOT video_recorder_pkg_FIND_QUIETLY)
  message(STATUS "Found video_recorder_pkg: 0.0.1 (${video_recorder_pkg_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'video_recorder_pkg' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT ${video_recorder_pkg_DEPRECATED_QUIET})
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(video_recorder_pkg_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "")
foreach(_extra ${_extras})
  include("${video_recorder_pkg_DIR}/${_extra}")
endforeach()

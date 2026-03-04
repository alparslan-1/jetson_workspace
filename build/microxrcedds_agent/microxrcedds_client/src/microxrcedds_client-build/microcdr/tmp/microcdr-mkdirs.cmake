# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/root/bridges/jetson_workspace/build/microxrcedds_agent/microxrcedds_client/src/microxrcedds_client-build/microcdr/src/microcdr"
  "/root/bridges/jetson_workspace/build/microxrcedds_agent/microxrcedds_client/src/microxrcedds_client-build/microcdr/src/microcdr-build"
  "/root/bridges/jetson_workspace/build/microxrcedds_agent/microxrcedds_client/src/microxrcedds_client-build/temp_install"
  "/root/bridges/jetson_workspace/build/microxrcedds_agent/microxrcedds_client/src/microxrcedds_client-build/microcdr/tmp"
  "/root/bridges/jetson_workspace/build/microxrcedds_agent/microxrcedds_client/src/microxrcedds_client-build/microcdr/src/microcdr-stamp"
  "/root/bridges/jetson_workspace/build/microxrcedds_agent/microxrcedds_client/src/microxrcedds_client-build/microcdr/src"
  "/root/bridges/jetson_workspace/build/microxrcedds_agent/microxrcedds_client/src/microxrcedds_client-build/microcdr/src/microcdr-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/root/bridges/jetson_workspace/build/microxrcedds_agent/microxrcedds_client/src/microxrcedds_client-build/microcdr/src/microcdr-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/root/bridges/jetson_workspace/build/microxrcedds_agent/microxrcedds_client/src/microxrcedds_client-build/microcdr/src/microcdr-stamp${cfgdir}") # cfgdir has leading slash
endif()

# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/root/bridges/jetson_workspace/src/Micro-XRCE-DDS-Agent"
  "/root/bridges/jetson_workspace/build/microxrcedds_agent"
  "/root/bridges/jetson_workspace/build/microxrcedds_agent/uagent-prefix"
  "/root/bridges/jetson_workspace/build/microxrcedds_agent/uagent-prefix/tmp"
  "/root/bridges/jetson_workspace/build/microxrcedds_agent/uagent-prefix/src/uagent-stamp"
  "/root/bridges/jetson_workspace/build/microxrcedds_agent/uagent-prefix/src"
  "/root/bridges/jetson_workspace/build/microxrcedds_agent/uagent-prefix/src/uagent-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/root/bridges/jetson_workspace/build/microxrcedds_agent/uagent-prefix/src/uagent-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/root/bridges/jetson_workspace/build/microxrcedds_agent/uagent-prefix/src/uagent-stamp${cfgdir}") # cfgdir has leading slash
endif()

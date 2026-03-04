# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/root/bridges/jetson_workspace/build/microxrcedds_agent/spdlog/src/spdlog"
  "/root/bridges/jetson_workspace/build/microxrcedds_agent/spdlog/src/spdlog-build"
  "/root/bridges/jetson_workspace/build/microxrcedds_agent/temp_install/spdlog-1.9.2"
  "/root/bridges/jetson_workspace/build/microxrcedds_agent/spdlog/tmp"
  "/root/bridges/jetson_workspace/build/microxrcedds_agent/spdlog/src/spdlog-stamp"
  "/root/bridges/jetson_workspace/build/microxrcedds_agent/spdlog/src"
  "/root/bridges/jetson_workspace/build/microxrcedds_agent/spdlog/src/spdlog-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/root/bridges/jetson_workspace/build/microxrcedds_agent/spdlog/src/spdlog-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/root/bridges/jetson_workspace/build/microxrcedds_agent/spdlog/src/spdlog-stamp${cfgdir}") # cfgdir has leading slash
endif()

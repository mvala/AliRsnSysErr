project(zmqtm)
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
#set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -pedantic")


set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")

find_package(ROOT REQUIRED)
include(kdevelop-utils)
KDevelopSettings()

add_subdirectory(RsnSysErr)

include(CPack)

# uninstall
CONFIGURE_FILE(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake/cmake_uninstall.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
  IMMEDIATE @ONLY)

ADD_CUSTOM_TARGET(uninstall
  "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake")


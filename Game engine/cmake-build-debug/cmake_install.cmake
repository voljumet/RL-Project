# Install script for directory: /Users/peshangalo/Documents/Master/First_Year/Second Semester/RL/RL-Project/Game engine

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/Library/Developer/CommandLineTools/usr/bin/objdump")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/json/allocator.h;/json/assertions.h;/json/config.h;/json/forwards.h;/json/json.h;/json/json_features.h;/json/reader.h;/json/value.h;/json/version.h;/json/writer.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/json" TYPE FILE FILES
    "/Users/peshangalo/Documents/Master/First_Year/Second Semester/RL/RL-Project/Game engine/json/allocator.h"
    "/Users/peshangalo/Documents/Master/First_Year/Second Semester/RL/RL-Project/Game engine/json/assertions.h"
    "/Users/peshangalo/Documents/Master/First_Year/Second Semester/RL/RL-Project/Game engine/json/config.h"
    "/Users/peshangalo/Documents/Master/First_Year/Second Semester/RL/RL-Project/Game engine/json/forwards.h"
    "/Users/peshangalo/Documents/Master/First_Year/Second Semester/RL/RL-Project/Game engine/json/json.h"
    "/Users/peshangalo/Documents/Master/First_Year/Second Semester/RL/RL-Project/Game engine/json/json_features.h"
    "/Users/peshangalo/Documents/Master/First_Year/Second Semester/RL/RL-Project/Game engine/json/reader.h"
    "/Users/peshangalo/Documents/Master/First_Year/Second Semester/RL/RL-Project/Game engine/json/value.h"
    "/Users/peshangalo/Documents/Master/First_Year/Second Semester/RL/RL-Project/Game engine/json/version.h"
    "/Users/peshangalo/Documents/Master/First_Year/Second Semester/RL/RL-Project/Game engine/json/writer.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/Users/peshangalo/Documents/Master/First_Year/Second Semester/RL/RL-Project/Game engine/cmake-build-debug/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")

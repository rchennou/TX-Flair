# Install script for directory: /home/rafik/flair/flair-src/lib/FlairMeta

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
    set(CMAKE_INSTALL_CONFIG_NAME "")
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

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/rafik/flair/flair-bin/lib/arm/libFlairMeta.a")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/rafik/flair/flair-bin/lib/arm" TYPE STATIC_LIBRARY FILES "/home/rafik/flair/flair-src/lib/FlairMeta/build_arm/bin/libFlairMeta.a")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/rafik/flair/flair-dev/include/FlairMeta/HdsX8.h;/home/rafik/flair/flair-dev/include/FlairMeta/MetaDualShock3.h;/home/rafik/flair/flair-dev/include/FlairMeta/MetaUsRangeFinder.h;/home/rafik/flair/flair-dev/include/FlairMeta/MetaVrpnObject.h;/home/rafik/flair/flair-dev/include/FlairMeta/SimuX4.h;/home/rafik/flair/flair-dev/include/FlairMeta/SimuX8.h;/home/rafik/flair/flair-dev/include/FlairMeta/Uav.h;/home/rafik/flair/flair-dev/include/FlairMeta/UavFactory.h;/home/rafik/flair/flair-dev/include/FlairMeta/UavStateMachine.h;/home/rafik/flair/flair-dev/include/FlairMeta/XAir.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/rafik/flair/flair-dev/include/FlairMeta" TYPE FILE FILES
    "/home/rafik/flair/flair-src/lib/FlairMeta/src/HdsX8.h"
    "/home/rafik/flair/flair-src/lib/FlairMeta/src/MetaDualShock3.h"
    "/home/rafik/flair/flair-src/lib/FlairMeta/src/MetaUsRangeFinder.h"
    "/home/rafik/flair/flair-src/lib/FlairMeta/src/MetaVrpnObject.h"
    "/home/rafik/flair/flair-src/lib/FlairMeta/src/SimuX4.h"
    "/home/rafik/flair/flair-src/lib/FlairMeta/src/SimuX8.h"
    "/home/rafik/flair/flair-src/lib/FlairMeta/src/Uav.h"
    "/home/rafik/flair/flair-src/lib/FlairMeta/src/UavFactory.h"
    "/home/rafik/flair/flair-src/lib/FlairMeta/src/UavStateMachine.h"
    "/home/rafik/flair/flair-src/lib/FlairMeta/src/XAir.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/rafik/flair/flair-src/lib/FlairMeta/build_arm/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")

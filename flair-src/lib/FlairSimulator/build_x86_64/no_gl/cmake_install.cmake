# Install script for directory: /home/rafik/flair/flair-src/lib/FlairSimulator/no_gl

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
   "/home/rafik/flair/flair-bin/lib/x86_64/unix/libFlairSimulator_nogl.a")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/rafik/flair/flair-bin/lib/x86_64/unix" TYPE STATIC_LIBRARY FILES "/home/rafik/flair/flair-src/lib/FlairSimulator/build/bin/libFlairSimulator_nogl.a")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/rafik/flair/flair-dev/include/FlairSimulator/Blade.h;/home/rafik/flair/flair-dev/include/FlairSimulator/Castle.h;/home/rafik/flair/flair-dev/include/FlairSimulator/DiscreteTimeVariable.h;/home/rafik/flair/flair-dev/include/FlairSimulator/FixedCamera.h;/home/rafik/flair/flair-dev/include/FlairSimulator/Gui.h;/home/rafik/flair/flair-dev/include/FlairSimulator/Man.h;/home/rafik/flair/flair-dev/include/FlairSimulator/MeshSceneNode.h;/home/rafik/flair/flair-dev/include/FlairSimulator/Model.h;/home/rafik/flair/flair-dev/include/FlairSimulator/Parser.h;/home/rafik/flair/flair-dev/include/FlairSimulator/SensorGL.h;/home/rafik/flair/flair-dev/include/FlairSimulator/SimuCameraGL.h;/home/rafik/flair/flair-dev/include/FlairSimulator/SimuLaserGL.h;/home/rafik/flair/flair-dev/include/FlairSimulator/SimuUsGL.h;/home/rafik/flair/flair-dev/include/FlairSimulator/Simulator.h;/home/rafik/flair/flair-dev/include/FlairSimulator/VisualizationCamera.h;/home/rafik/flair/flair-dev/include/FlairSimulator/X4.h;/home/rafik/flair/flair-dev/include/FlairSimulator/X8.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/rafik/flair/flair-dev/include/FlairSimulator" TYPE FILE FILES
    "/home/rafik/flair/flair-src/lib/FlairSimulator/no_gl/../src/Blade.h"
    "/home/rafik/flair/flair-src/lib/FlairSimulator/no_gl/../src/Castle.h"
    "/home/rafik/flair/flair-src/lib/FlairSimulator/no_gl/../src/DiscreteTimeVariable.h"
    "/home/rafik/flair/flair-src/lib/FlairSimulator/no_gl/../src/FixedCamera.h"
    "/home/rafik/flair/flair-src/lib/FlairSimulator/no_gl/../src/Gui.h"
    "/home/rafik/flair/flair-src/lib/FlairSimulator/no_gl/../src/Man.h"
    "/home/rafik/flair/flair-src/lib/FlairSimulator/no_gl/../src/MeshSceneNode.h"
    "/home/rafik/flair/flair-src/lib/FlairSimulator/no_gl/../src/Model.h"
    "/home/rafik/flair/flair-src/lib/FlairSimulator/no_gl/../src/Parser.h"
    "/home/rafik/flair/flair-src/lib/FlairSimulator/no_gl/../src/SensorGL.h"
    "/home/rafik/flair/flair-src/lib/FlairSimulator/no_gl/../src/SimuCameraGL.h"
    "/home/rafik/flair/flair-src/lib/FlairSimulator/no_gl/../src/SimuLaserGL.h"
    "/home/rafik/flair/flair-src/lib/FlairSimulator/no_gl/../src/SimuUsGL.h"
    "/home/rafik/flair/flair-src/lib/FlairSimulator/no_gl/../src/Simulator.h"
    "/home/rafik/flair/flair-src/lib/FlairSimulator/no_gl/../src/VisualizationCamera.h"
    "/home/rafik/flair/flair-src/lib/FlairSimulator/no_gl/../src/X4.h"
    "/home/rafik/flair/flair-src/lib/FlairSimulator/no_gl/../src/X8.h"
    )
endif()


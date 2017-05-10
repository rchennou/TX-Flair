# Install script for directory: /home/rafik/flair/flair-src/lib/FlairFilter

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
   "/home/rafik/flair/flair-bin/lib/arm/libFlairFilter.a")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/rafik/flair/flair-bin/lib/arm" TYPE STATIC_LIBRARY FILES "/home/rafik/flair/flair-src/lib/FlairFilter/build_arm/bin/libFlairFilter.a")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/rafik/flair/flair-dev/include/FlairFilter/Ahrs.h;/home/rafik/flair/flair-dev/include/FlairFilter/AhrsComplementaryFilter.h;/home/rafik/flair/flair-dev/include/FlairFilter/AhrsKalman.h;/home/rafik/flair/flair-dev/include/FlairFilter/ButterworthLowPass.h;/home/rafik/flair/flair-dev/include/FlairFilter/ControlLaw.h;/home/rafik/flair/flair-dev/include/FlairFilter/EulerDerivative.h;/home/rafik/flair/flair-dev/include/FlairFilter/Gx3_25_ahrs.h;/home/rafik/flair/flair-dev/include/FlairFilter/JoyReference.h;/home/rafik/flair/flair-dev/include/FlairFilter/LowPassFilter.h;/home/rafik/flair/flair-dev/include/FlairFilter/NestedSat.h;/home/rafik/flair/flair-dev/include/FlairFilter/Pid.h;/home/rafik/flair/flair-dev/include/FlairFilter/PidThrust.h;/home/rafik/flair/flair-dev/include/FlairFilter/SimuAhrs.h;/home/rafik/flair/flair-dev/include/FlairFilter/TrajectoryGenerator1D.h;/home/rafik/flair/flair-dev/include/FlairFilter/TrajectoryGenerator2DCircle.h;/home/rafik/flair/flair-dev/include/FlairFilter/TrajectoryGenerator2DLine.h;/home/rafik/flair/flair-dev/include/FlairFilter/TrajectoryGenerator2DSquare.h;/home/rafik/flair/flair-dev/include/FlairFilter/UavMultiplex.h;/home/rafik/flair/flair-dev/include/FlairFilter/X4X8Multiplex.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/rafik/flair/flair-dev/include/FlairFilter" TYPE FILE FILES
    "/home/rafik/flair/flair-src/lib/FlairFilter/src/Ahrs.h"
    "/home/rafik/flair/flair-src/lib/FlairFilter/src/AhrsComplementaryFilter.h"
    "/home/rafik/flair/flair-src/lib/FlairFilter/src/AhrsKalman.h"
    "/home/rafik/flair/flair-src/lib/FlairFilter/src/ButterworthLowPass.h"
    "/home/rafik/flair/flair-src/lib/FlairFilter/src/ControlLaw.h"
    "/home/rafik/flair/flair-src/lib/FlairFilter/src/EulerDerivative.h"
    "/home/rafik/flair/flair-src/lib/FlairFilter/src/Gx3_25_ahrs.h"
    "/home/rafik/flair/flair-src/lib/FlairFilter/src/JoyReference.h"
    "/home/rafik/flair/flair-src/lib/FlairFilter/src/LowPassFilter.h"
    "/home/rafik/flair/flair-src/lib/FlairFilter/src/NestedSat.h"
    "/home/rafik/flair/flair-src/lib/FlairFilter/src/Pid.h"
    "/home/rafik/flair/flair-src/lib/FlairFilter/src/PidThrust.h"
    "/home/rafik/flair/flair-src/lib/FlairFilter/src/SimuAhrs.h"
    "/home/rafik/flair/flair-src/lib/FlairFilter/src/TrajectoryGenerator1D.h"
    "/home/rafik/flair/flair-src/lib/FlairFilter/src/TrajectoryGenerator2DCircle.h"
    "/home/rafik/flair/flair-src/lib/FlairFilter/src/TrajectoryGenerator2DLine.h"
    "/home/rafik/flair/flair-src/lib/FlairFilter/src/TrajectoryGenerator2DSquare.h"
    "/home/rafik/flair/flair-src/lib/FlairFilter/src/UavMultiplex.h"
    "/home/rafik/flair/flair-src/lib/FlairFilter/src/X4X8Multiplex.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/rafik/flair/flair-src/lib/FlairFilter/build_arm/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")

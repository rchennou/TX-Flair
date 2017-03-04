# Install script for directory: /home/rafik/flair/flair-src/lib/FlairSensorActuator

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
   "/home/rafik/flair/flair-bin/lib/arm/libFlairSensorActuator.a")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/rafik/flair/flair-bin/lib/arm" TYPE STATIC_LIBRARY FILES "/home/rafik/flair/flair-src/lib/FlairSensorActuator/build_arm/bin/libFlairSensorActuator.a")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/rafik/flair/flair-dev/include/FlairSensorActuator/AfroBldc.h;/home/rafik/flair/flair-dev/include/FlairSensorActuator/BatteryMonitor.h;/home/rafik/flair/flair-dev/include/FlairSensorActuator/BlCtrlV2.h;/home/rafik/flair/flair-dev/include/FlairSensorActuator/BlCtrlV2_x4_speed.h;/home/rafik/flair/flair-dev/include/FlairSensorActuator/Bldc.h;/home/rafik/flair/flair-dev/include/FlairSensorActuator/Camera.h;/home/rafik/flair/flair-dev/include/FlairSensorActuator/Controller.h;/home/rafik/flair/flair-dev/include/FlairSensorActuator/EmulatedController.h;/home/rafik/flair/flair-dev/include/FlairSensorActuator/Gx3_25_imu.h;/home/rafik/flair/flair-dev/include/FlairSensorActuator/HokuyoUTM30Lx.h;/home/rafik/flair/flair-dev/include/FlairSensorActuator/HostEthController.h;/home/rafik/flair/flair-dev/include/FlairSensorActuator/Imu.h;/home/rafik/flair/flair-dev/include/FlairSensorActuator/LaserRangeFinder.h;/home/rafik/flair/flair-dev/include/FlairSensorActuator/Mb800.h;/home/rafik/flair/flair-dev/include/FlairSensorActuator/NmeaGps.h;/home/rafik/flair/flair-dev/include/FlairSensorActuator/Novatel.h;/home/rafik/flair/flair-dev/include/FlairSensorActuator/Ps3Eye.h;/home/rafik/flair/flair-dev/include/FlairSensorActuator/RadioReceiver.h;/home/rafik/flair/flair-dev/include/FlairSensorActuator/SimuBldc.h;/home/rafik/flair/flair-dev/include/FlairSensorActuator/SimuCamera.h;/home/rafik/flair/flair-dev/include/FlairSensorActuator/SimuGps.h;/home/rafik/flair/flair-dev/include/FlairSensorActuator/SimuImu.h;/home/rafik/flair/flair-dev/include/FlairSensorActuator/SimuLaser.h;/home/rafik/flair/flair-dev/include/FlairSensorActuator/SimuUs.h;/home/rafik/flair/flair-dev/include/FlairSensorActuator/Srf08.h;/home/rafik/flair/flair-dev/include/FlairSensorActuator/TargetController.h;/home/rafik/flair/flair-dev/include/FlairSensorActuator/TargetEthController.h;/home/rafik/flair/flair-dev/include/FlairSensorActuator/UsRangeFinder.h;/home/rafik/flair/flair-dev/include/FlairSensorActuator/V4LCamera.h;/home/rafik/flair/flair-dev/include/FlairSensorActuator/VrpnClient.h;/home/rafik/flair/flair-dev/include/FlairSensorActuator/VrpnObject.h;/home/rafik/flair/flair-dev/include/FlairSensorActuator/XBldc.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/rafik/flair/flair-dev/include/FlairSensorActuator" TYPE FILE FILES
    "/home/rafik/flair/flair-src/lib/FlairSensorActuator/src/AfroBldc.h"
    "/home/rafik/flair/flair-src/lib/FlairSensorActuator/src/BatteryMonitor.h"
    "/home/rafik/flair/flair-src/lib/FlairSensorActuator/src/BlCtrlV2.h"
    "/home/rafik/flair/flair-src/lib/FlairSensorActuator/src/BlCtrlV2_x4_speed.h"
    "/home/rafik/flair/flair-src/lib/FlairSensorActuator/src/Bldc.h"
    "/home/rafik/flair/flair-src/lib/FlairSensorActuator/src/Camera.h"
    "/home/rafik/flair/flair-src/lib/FlairSensorActuator/src/Controller.h"
    "/home/rafik/flair/flair-src/lib/FlairSensorActuator/src/EmulatedController.h"
    "/home/rafik/flair/flair-src/lib/FlairSensorActuator/src/Gx3_25_imu.h"
    "/home/rafik/flair/flair-src/lib/FlairSensorActuator/src/HokuyoUTM30Lx.h"
    "/home/rafik/flair/flair-src/lib/FlairSensorActuator/src/HostEthController.h"
    "/home/rafik/flair/flair-src/lib/FlairSensorActuator/src/Imu.h"
    "/home/rafik/flair/flair-src/lib/FlairSensorActuator/src/LaserRangeFinder.h"
    "/home/rafik/flair/flair-src/lib/FlairSensorActuator/src/Mb800.h"
    "/home/rafik/flair/flair-src/lib/FlairSensorActuator/src/NmeaGps.h"
    "/home/rafik/flair/flair-src/lib/FlairSensorActuator/src/Novatel.h"
    "/home/rafik/flair/flair-src/lib/FlairSensorActuator/src/Ps3Eye.h"
    "/home/rafik/flair/flair-src/lib/FlairSensorActuator/src/RadioReceiver.h"
    "/home/rafik/flair/flair-src/lib/FlairSensorActuator/src/SimuBldc.h"
    "/home/rafik/flair/flair-src/lib/FlairSensorActuator/src/SimuCamera.h"
    "/home/rafik/flair/flair-src/lib/FlairSensorActuator/src/SimuGps.h"
    "/home/rafik/flair/flair-src/lib/FlairSensorActuator/src/SimuImu.h"
    "/home/rafik/flair/flair-src/lib/FlairSensorActuator/src/SimuLaser.h"
    "/home/rafik/flair/flair-src/lib/FlairSensorActuator/src/SimuUs.h"
    "/home/rafik/flair/flair-src/lib/FlairSensorActuator/src/Srf08.h"
    "/home/rafik/flair/flair-src/lib/FlairSensorActuator/src/TargetController.h"
    "/home/rafik/flair/flair-src/lib/FlairSensorActuator/src/TargetEthController.h"
    "/home/rafik/flair/flair-src/lib/FlairSensorActuator/src/UsRangeFinder.h"
    "/home/rafik/flair/flair-src/lib/FlairSensorActuator/src/V4LCamera.h"
    "/home/rafik/flair/flair-src/lib/FlairSensorActuator/src/VrpnClient.h"
    "/home/rafik/flair/flair-src/lib/FlairSensorActuator/src/VrpnObject.h"
    "/home/rafik/flair/flair-src/lib/FlairSensorActuator/src/XBldc.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/rafik/flair/flair-src/lib/FlairSensorActuator/build_arm/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")

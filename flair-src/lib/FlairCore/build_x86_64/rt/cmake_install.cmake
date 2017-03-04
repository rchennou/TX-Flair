# Install script for directory: /home/rafik/flair/flair-src/lib/FlairCore/rt

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
   "/home/rafik/flair/flair-bin/lib/x86_64/unix/libFlairCore_rt.a")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/rafik/flair/flair-bin/lib/x86_64/unix" TYPE STATIC_LIBRARY FILES "/home/rafik/flair/flair-src/lib/FlairCore/build/bin/libFlairCore_rt.a")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/rafik/flair/flair-dev/include/FlairCore/AhrsData.h;/home/rafik/flair/flair-dev/include/FlairCore/Box.h;/home/rafik/flair/flair-dev/include/FlairCore/CheckBox.h;/home/rafik/flair/flair-dev/include/FlairCore/ComboBox.h;/home/rafik/flair/flair-dev/include/FlairCore/ConditionVariable.h;/home/rafik/flair/flair-dev/include/FlairCore/ConnectedSocket.h;/home/rafik/flair/flair-dev/include/FlairCore/DataPlot.h;/home/rafik/flair/flair-dev/include/FlairCore/DataPlot1D.h;/home/rafik/flair/flair-dev/include/FlairCore/DataPlot2D.h;/home/rafik/flair/flair-dev/include/FlairCore/DoubleSpinBox.h;/home/rafik/flair/flair-dev/include/FlairCore/Euler.h;/home/rafik/flair/flair-dev/include/FlairCore/FrameworkManager.h;/home/rafik/flair/flair-dev/include/FlairCore/GeoCoordinate.h;/home/rafik/flair/flair-dev/include/FlairCore/GpsData.h;/home/rafik/flair/flair-dev/include/FlairCore/GridLayout.h;/home/rafik/flair/flair-dev/include/FlairCore/GroupBox.h;/home/rafik/flair/flair-dev/include/FlairCore/I2cPort.h;/home/rafik/flair/flair-dev/include/FlairCore/IODataElement.h;/home/rafik/flair/flair-dev/include/FlairCore/IODevice.h;/home/rafik/flair/flair-dev/include/FlairCore/ImuData.h;/home/rafik/flair/flair-dev/include/FlairCore/Label.h;/home/rafik/flair/flair-dev/include/FlairCore/Layout.h;/home/rafik/flair/flair-dev/include/FlairCore/LayoutPosition.h;/home/rafik/flair/flair-dev/include/FlairCore/ListWidget.h;/home/rafik/flair/flair-dev/include/FlairCore/Map.h;/home/rafik/flair/flair-dev/include/FlairCore/Mutex.h;/home/rafik/flair/flair-dev/include/FlairCore/Object.h;/home/rafik/flair/flair-dev/include/FlairCore/OneAxisRotation.h;/home/rafik/flair/flair-dev/include/FlairCore/Picture.h;/home/rafik/flair/flair-dev/include/FlairCore/PushButton.h;/home/rafik/flair/flair-dev/include/FlairCore/Quaternion.h;/home/rafik/flair/flair-dev/include/FlairCore/RTDM_I2cPort.h;/home/rafik/flair/flair-dev/include/FlairCore/RTDM_SerialPort.h;/home/rafik/flair/flair-dev/include/FlairCore/RangeFinderPlot.h;/home/rafik/flair/flair-dev/include/FlairCore/RotationMatrix.h;/home/rafik/flair/flair-dev/include/FlairCore/SendData.h;/home/rafik/flair/flair-dev/include/FlairCore/SerialPort.h;/home/rafik/flair/flair-dev/include/FlairCore/SharedMem.h;/home/rafik/flair/flair-dev/include/FlairCore/Socket.h;/home/rafik/flair/flair-dev/include/FlairCore/SpinBox.h;/home/rafik/flair/flair-dev/include/FlairCore/Tab.h;/home/rafik/flair/flair-dev/include/FlairCore/TabWidget.h;/home/rafik/flair/flair-dev/include/FlairCore/TcpSocket.h;/home/rafik/flair/flair-dev/include/FlairCore/TextEdit.h;/home/rafik/flair/flair-dev/include/FlairCore/Thread.h;/home/rafik/flair/flair-dev/include/FlairCore/UdtSocket.h;/home/rafik/flair/flair-dev/include/FlairCore/Unix_I2cPort.h;/home/rafik/flair/flair-dev/include/FlairCore/Unix_SerialPort.h;/home/rafik/flair/flair-dev/include/FlairCore/Vector2D.h;/home/rafik/flair/flair-dev/include/FlairCore/Vector3D.h;/home/rafik/flair/flair-dev/include/FlairCore/Vector3DSpinBox.h;/home/rafik/flair/flair-dev/include/FlairCore/Vector3Ddata.h;/home/rafik/flair/flair-dev/include/FlairCore/Watchdog.h;/home/rafik/flair/flair-dev/include/FlairCore/Widget.h;/home/rafik/flair/flair-dev/include/FlairCore/cvimage.h;/home/rafik/flair/flair-dev/include/FlairCore/cvmatrix.h;/home/rafik/flair/flair-dev/include/FlairCore/cvmatrix_descriptor.h;/home/rafik/flair/flair-dev/include/FlairCore/io_data.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/rafik/flair/flair-dev/include/FlairCore" TYPE FILE FILES
    "/home/rafik/flair/flair-src/lib/FlairCore/rt/../src/AhrsData.h"
    "/home/rafik/flair/flair-src/lib/FlairCore/rt/../src/Box.h"
    "/home/rafik/flair/flair-src/lib/FlairCore/rt/../src/CheckBox.h"
    "/home/rafik/flair/flair-src/lib/FlairCore/rt/../src/ComboBox.h"
    "/home/rafik/flair/flair-src/lib/FlairCore/rt/../src/ConditionVariable.h"
    "/home/rafik/flair/flair-src/lib/FlairCore/rt/../src/ConnectedSocket.h"
    "/home/rafik/flair/flair-src/lib/FlairCore/rt/../src/DataPlot.h"
    "/home/rafik/flair/flair-src/lib/FlairCore/rt/../src/DataPlot1D.h"
    "/home/rafik/flair/flair-src/lib/FlairCore/rt/../src/DataPlot2D.h"
    "/home/rafik/flair/flair-src/lib/FlairCore/rt/../src/DoubleSpinBox.h"
    "/home/rafik/flair/flair-src/lib/FlairCore/rt/../src/Euler.h"
    "/home/rafik/flair/flair-src/lib/FlairCore/rt/../src/FrameworkManager.h"
    "/home/rafik/flair/flair-src/lib/FlairCore/rt/../src/GeoCoordinate.h"
    "/home/rafik/flair/flair-src/lib/FlairCore/rt/../src/GpsData.h"
    "/home/rafik/flair/flair-src/lib/FlairCore/rt/../src/GridLayout.h"
    "/home/rafik/flair/flair-src/lib/FlairCore/rt/../src/GroupBox.h"
    "/home/rafik/flair/flair-src/lib/FlairCore/rt/../src/I2cPort.h"
    "/home/rafik/flair/flair-src/lib/FlairCore/rt/../src/IODataElement.h"
    "/home/rafik/flair/flair-src/lib/FlairCore/rt/../src/IODevice.h"
    "/home/rafik/flair/flair-src/lib/FlairCore/rt/../src/ImuData.h"
    "/home/rafik/flair/flair-src/lib/FlairCore/rt/../src/Label.h"
    "/home/rafik/flair/flair-src/lib/FlairCore/rt/../src/Layout.h"
    "/home/rafik/flair/flair-src/lib/FlairCore/rt/../src/LayoutPosition.h"
    "/home/rafik/flair/flair-src/lib/FlairCore/rt/../src/ListWidget.h"
    "/home/rafik/flair/flair-src/lib/FlairCore/rt/../src/Map.h"
    "/home/rafik/flair/flair-src/lib/FlairCore/rt/../src/Mutex.h"
    "/home/rafik/flair/flair-src/lib/FlairCore/rt/../src/Object.h"
    "/home/rafik/flair/flair-src/lib/FlairCore/rt/../src/OneAxisRotation.h"
    "/home/rafik/flair/flair-src/lib/FlairCore/rt/../src/Picture.h"
    "/home/rafik/flair/flair-src/lib/FlairCore/rt/../src/PushButton.h"
    "/home/rafik/flair/flair-src/lib/FlairCore/rt/../src/Quaternion.h"
    "/home/rafik/flair/flair-src/lib/FlairCore/rt/../src/RTDM_I2cPort.h"
    "/home/rafik/flair/flair-src/lib/FlairCore/rt/../src/RTDM_SerialPort.h"
    "/home/rafik/flair/flair-src/lib/FlairCore/rt/../src/RangeFinderPlot.h"
    "/home/rafik/flair/flair-src/lib/FlairCore/rt/../src/RotationMatrix.h"
    "/home/rafik/flair/flair-src/lib/FlairCore/rt/../src/SendData.h"
    "/home/rafik/flair/flair-src/lib/FlairCore/rt/../src/SerialPort.h"
    "/home/rafik/flair/flair-src/lib/FlairCore/rt/../src/SharedMem.h"
    "/home/rafik/flair/flair-src/lib/FlairCore/rt/../src/Socket.h"
    "/home/rafik/flair/flair-src/lib/FlairCore/rt/../src/SpinBox.h"
    "/home/rafik/flair/flair-src/lib/FlairCore/rt/../src/Tab.h"
    "/home/rafik/flair/flair-src/lib/FlairCore/rt/../src/TabWidget.h"
    "/home/rafik/flair/flair-src/lib/FlairCore/rt/../src/TcpSocket.h"
    "/home/rafik/flair/flair-src/lib/FlairCore/rt/../src/TextEdit.h"
    "/home/rafik/flair/flair-src/lib/FlairCore/rt/../src/Thread.h"
    "/home/rafik/flair/flair-src/lib/FlairCore/rt/../src/UdtSocket.h"
    "/home/rafik/flair/flair-src/lib/FlairCore/rt/../src/Unix_I2cPort.h"
    "/home/rafik/flair/flair-src/lib/FlairCore/rt/../src/Unix_SerialPort.h"
    "/home/rafik/flair/flair-src/lib/FlairCore/rt/../src/Vector2D.h"
    "/home/rafik/flair/flair-src/lib/FlairCore/rt/../src/Vector3D.h"
    "/home/rafik/flair/flair-src/lib/FlairCore/rt/../src/Vector3DSpinBox.h"
    "/home/rafik/flair/flair-src/lib/FlairCore/rt/../src/Vector3Ddata.h"
    "/home/rafik/flair/flair-src/lib/FlairCore/rt/../src/Watchdog.h"
    "/home/rafik/flair/flair-src/lib/FlairCore/rt/../src/Widget.h"
    "/home/rafik/flair/flair-src/lib/FlairCore/rt/../src/cvimage.h"
    "/home/rafik/flair/flair-src/lib/FlairCore/rt/../src/cvmatrix.h"
    "/home/rafik/flair/flair-src/lib/FlairCore/rt/../src/cvmatrix_descriptor.h"
    "/home/rafik/flair/flair-src/lib/FlairCore/rt/../src/io_data.h"
    )
endif()


PROJECT(FlairSimulator)
cmake_minimum_required(VERSION 2.8)
include($ENV{FLAIR_ROOT}/flair-dev/cmake-modules/GlobalCmakeFlair.cmake)

find_package(LibXml2 REQUIRED)

execute_process(COMMAND ${CMAKE_C_COMPILER} -dumpversion
                OUTPUT_VARIABLE GCC_VERSION)

if (GCC_VERSION VERSION_GREATER 4.3 OR GCC_VERSION VERSION_EQUAL 4.3)
	if (GCC_VERSION VERSION_GREATER 4.7 OR GCC_VERSION VERSION_EQUAL 4.7)
		ADD_DEFINITIONS("-std=c++11")
	else()
		ADD_DEFINITIONS("-std=c++0x")
	endif()
else()
	message(STATUS "GCC version < 4.3, c+11 is not supported!")
endif()

INCLUDE_DIRECTORIES(
      	${LIBXML2_INCLUDE_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/src
	${CMAKE_CURRENT_SOURCE_DIR}/src/unexported
	${CMAKE_CURRENT_SOURCE_DIR}/../FlairCore/src
	${CMAKE_CURRENT_SOURCE_DIR}/../FlairSensorActuator/src
	${CMAKE_SYSROOT}/usr/include/vrpn
	${CMAKE_SYSROOT}/usr/include/opencv
	${CMAKE_SYSROOT}/usr/include/irrlicht
)

FILE(GLOB SIMU_SRC "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

add_custom_target(
	compile_info
	COMMAND $ENV{FLAIR_ROOT}/flair-dev/scripts/compile_info.sh ${CMAKE_C_COMPILER} ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/src/unexported/compile_info.h
)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/no_gl)
add_dependencies(FlairSimulator_nogl compile_info)
if("${CMAKE_SYSTEM_PROCESSOR}" MATCHES "i686" OR "${CMAKE_SYSTEM_PROCESSOR}" MATCHES "i586" OR "${CMAKE_SYSTEM_PROCESSOR}" MATCHES "x86_64")
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/gl)
add_dependencies(FlairSimulator_gl compile_info)
endif()

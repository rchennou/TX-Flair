PROJECT(FlairBebop)
cmake_minimum_required(VERSION 2.8)
include($ENV{FLAIR_ROOT}/flair-dev/cmake-modules/GlobalCmakeFlair.cmake)

if("${CMAKE_SYSTEM_PROCESSOR}" MATCHES "arm")

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
	$ENV{FLAIR_ROOT}/flair-src/lib/FlairSensorActuator/src
	$ENV{FLAIR_ROOT}/flair-src/lib/FlairCore/src
	$ENV{FLAIR_ROOT}/flair-src/lib/FlairMeta/src
	$ENV{FLAIR_ROOT}/flair-src/lib/FlairFilter/src
	${CMAKE_SYSROOT}/usr/include/opencv
)

FILE(GLOB SENSOR_SRC "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

ADD_LIBRARY(${PROJECT_NAME}
	${SENSOR_SRC}
)

INSTALL(TARGETS ${PROJECT_NAME}
	LIBRARY DESTINATION $ENV{FLAIR_ROOT}/flair-hds/bin/lib/${ARCH_DIR}
	ARCHIVE DESTINATION $ENV{FLAIR_ROOT}/flair-hds/bin/lib/${ARCH_DIR}
)

FILE(GLOB files "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h")
INSTALL(FILES ${files} DESTINATION $ENV{FLAIR_ROOT}/flair-hds/dev/include/${PROJECT_NAME})

add_custom_target(
	compile_info
	COMMAND $ENV{FLAIR_ROOT}/flair-dev/scripts/compile_info.sh ${CMAKE_C_COMPILER} ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/src/unexported/compile_info.h
)

add_dependencies(${PROJECT_NAME} compile_info)

else()
warn("${PROJECT_NAME} will not be built for ${CMAKE_SYSTEM_PROCESSOR} architecture")
endif()

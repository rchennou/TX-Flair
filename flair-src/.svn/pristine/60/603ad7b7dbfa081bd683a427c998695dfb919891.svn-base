PROJECT(FlairFilter)
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
	${CMAKE_CURRENT_SOURCE_DIR}/../FlairCore/src
	${CMAKE_CURRENT_SOURCE_DIR}/../FlairSensorActuator/src
	${CMAKE_CURRENT_SOURCE_DIR}/src/unexported
	${CMAKE_CURRENT_SOURCE_DIR}/src/
	${CMAKE_SYSROOT}/usr/include/opencv
	${CMAKE_SYSROOT}/usr/include/iir
)

FILE(GLOB SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

ADD_LIBRARY(${PROJECT_NAME}
	${SRC_FILES}
)

INSTALL(TARGETS ${PROJECT_NAME}
	LIBRARY DESTINATION $ENV{FLAIR_ROOT}/flair-bin/lib/${ARCH_DIR}
	ARCHIVE DESTINATION $ENV{FLAIR_ROOT}/flair-bin/lib/${ARCH_DIR}
)

#copie des entetes
FILE(GLOB HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h")
INSTALL(FILES ${HEADER_FILES} DESTINATION $ENV{FLAIR_ROOT}/flair-dev/include/${PROJECT_NAME})

SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

add_custom_target(
	compile_info
	COMMAND $ENV{FLAIR_ROOT}/flair-dev/scripts/compile_info.sh ${CMAKE_C_COMPILER} ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/src/unexported/compile_info.h
)

add_dependencies(${PROJECT_NAME} compile_info)

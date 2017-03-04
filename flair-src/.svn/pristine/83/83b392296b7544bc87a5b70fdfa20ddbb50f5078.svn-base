PROJECT(FlairCore)
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

FILE(GLOB FLAIRCORE_SRC "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
message(${CMAKE_C_COMPILER})
INCLUDE_DIRECTORIES(
	${LIBXML2_INCLUDE_DIR}
	${CMAKE_SYSROOT}/usr/include/opencv
	${CMAKE_SYSROOT}/usr/include/udt
	${CMAKE_CURRENT_SOURCE_DIR}/src
	${CMAKE_CURRENT_SOURCE_DIR}/src/unexported
)

SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/nrt)
if(NOT WIN32)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/rt)
endif()

add_custom_target(
	compile_info
	COMMAND $ENV{FLAIR_ROOT}/flair-dev/scripts/compile_info.sh ${CMAKE_C_COMPILER} ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/src/unexported/compile_info.h
)

add_dependencies(FlairCore_rt compile_info)
add_dependencies(FlairCore_nrt compile_info)

PROJECT(nettee)
cmake_minimum_required(VERSION 2.8)
include($ENV{IGEP_ROOT}/uav_dev/cmake_modules/GlobalCmakeUAV.cmake)

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
ADD_DEFINITIONS("-pthread")

INCLUDE_DIRECTORIES(
	${CMAKE_SYSROOT}/usr/include/udt
	${CMAKE_CURRENT_SOURCE_DIR}/src
        ${FRAMEWORK_INCLUDE_DIR}
)

ADD_EXECUTABLE(${PROJECT_NAME}
	src/SocketManager.cpp
	src/main.cpp
)

TARGET_LINK_LIBRARIES(${PROJECT_NAME} udt pthread ${FRAMEWORK_LIBRARIES_NRT})

INSTALL(TARGETS ${PROJECT_NAME}
	RUNTIME DESTINATION $ENV{IGEP_ROOT}/uav_dev/bin/${ARCH_DIR}
)

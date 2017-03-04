PROJECT(dbt2csv)
cmake_minimum_required(VERSION 2.8)
include($ENV{FLAIR_ROOT}/flair-dev/cmake-modules/GlobalCmakeFlair.cmake)

if("${CMAKE_SYSTEM_PROCESSOR}" MATCHES "i686" OR "${CMAKE_SYSTEM_PROCESSOR}" MATCHES "i586" OR "${CMAKE_SYSTEM_PROCESSOR}" MATCHES "x86_64")

SET(PROJECT_SOURCE_FILES
	src/main.cpp
	../FlairGCS/src/file_ui.cpp
)

SET(FILES_TO_MOC
	../FlairGCS/src/file_ui.h
)

FIND_PACKAGE(Qt4 REQUIRED)
SET(QT_USE_QTGUI TRUE)
SET(QT_USE_QTMAIN TRUE)
INCLUDE(${QT_USE_FILE})

QT4_WRAP_CPP(MOC_SOURCES ${FILES_TO_MOC})

ADD_DEFINITIONS(${QT_DEFINITIONS})

include_directories(
	${CMAKE_SOURCE_DIR}/src
	../FlairGCS/src/
	${QT_INCLUDE_DIR}
)

LINK_DIRECTORIES (
	${QT_LIBRARY_DIR}
)

ADD_EXECUTABLE(${PROJECT_NAME} ${PROJECT_SOURCE_FILES} ${MOC_SOURCES} ${RCC_SOURCES})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${QT_LIBRARIES} FileLib)

INSTALL(
	TARGETS ${PROJECT_NAME}
	RUNTIME DESTINATION $ENV{FLAIR_ROOT}/flair-bin/tools/${ARCH_DIR}
)

add_custom_target(
	compile_info
	COMMAND $ENV{FLAIR_ROOT}/flair-dev/scripts/compile_info.sh ${CMAKE_C_COMPILER} ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/src/unexported/compile_info.h
)

add_dependencies(${PROJECT_NAME} compile_info)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

else()
warn("${PROJECT_NAME} will not be built for ${CMAKE_SYSTEM_PROCESSOR} architecture")
endif()

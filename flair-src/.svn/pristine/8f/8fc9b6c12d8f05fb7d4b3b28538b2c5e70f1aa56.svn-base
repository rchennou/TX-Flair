PROJECT(flairgcs)
cmake_minimum_required(VERSION 2.8)
include($ENV{FLAIR_ROOT}/flair-dev/cmake-modules/GlobalCmakeFlair.cmake)

if("${CMAKE_SYSTEM_PROCESSOR}" MATCHES "i686" OR "${CMAKE_SYSTEM_PROCESSOR}" MATCHES "i586" OR "${CMAKE_SYSTEM_PROCESSOR}" MATCHES "x86_64")

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

FILE(GLOB PROJECT_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

SET(FILES_TO_MOC
	src/UdtSocket.h
	src/RangeFinderPlot.h
	src/DataPlot2D.h
	src/Picture.h
	src/Manager.h
	src/file_ui.h
	src/Vector3DSpinBox.h
	src/DoubleSpinBox.h
	src/SpinBox.h
	src/CheckBox.h
	src/ComboBox.h
	src/PushButton.h
	src/mapwidget.h
	src/Map.h
	src/XmlWidget.h
	src/ConnectionLayout.h
	src/ListWidget.h
)

FIND_PACKAGE(Qt4 REQUIRED)
SET(QT_USE_QTGUI TRUE)
SET(QT_USE_QTMAIN TRUE)
SET(QT_USE_QTXML TRUE)
SET(QT_USE_QTNETWORK TRUE)
INCLUDE(${QT_USE_FILE})

QT4_WRAP_CPP(MOC_SOURCES ${FILES_TO_MOC})

# generate rules for building source files from the resources
QT4_ADD_RESOURCES(RCC_SOURCES "src/ressources.qrc")

ADD_DEFINITIONS(${QT_DEFINITIONS})
ADD_DEFINITIONS(-DQT_THREAD_SUPPORT -DQT_NO_DEBUG)

include_directories(
	${CMAKE_SOURCE_DIR}/src
	${CMAKE_SOURCE_DIR}/../../lib/FlairCore/src/unexported
	${QT_INCLUDE_DIR}
	${CMAKE_SYSROOT}/usr/include/udt
	${CMAKE_SYSROOT}/usr/include/qwt
	${CMAKE_SYSROOT}/usr/include/QwtDataViewer
	${CMAKE_SYSROOT}/usr/include/qt4/QtMobility
	${CMAKE_SYSROOT}/usr/include/qt4/QtLocation
)

LINK_DIRECTORIES (
	${QT_LIBRARY_DIR}
)

ADD_EXECUTABLE(${PROJECT_NAME} ${PROJECT_SOURCE_FILES} ${MOC_SOURCES} ${RCC_SOURCES})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${QT_LIBRARIES} qwt QwtDataViewer udt QtLocation FileLib z)

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

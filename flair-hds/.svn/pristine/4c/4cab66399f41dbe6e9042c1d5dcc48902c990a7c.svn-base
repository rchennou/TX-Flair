PROJECT(LineFollower)
cmake_minimum_required(VERSION 2.8)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
SET(FLAIR_USE_FILTER TRUE)
SET(FLAIR_USE_VISION_FILTER TRUE)
SET(FLAIR_USE_SENSOR_ACTUATOR TRUE)
SET(FLAIR_USE_META TRUE)

include($ENV{FLAIR_ROOT}/flair-dev/cmake-modules/GlobalCmakeFlair.cmake)
include(${FLAIR_USE_FILE})

SET(SRC_FILES
	${CMAKE_SOURCE_DIR}/src/main.cpp
	${CMAKE_SOURCE_DIR}/src/DemoFollowLine.cpp
	$ENV{FLAIR_ROOT}/flair-src/demos/OpticalFlow/uav/src/DemoOpticalFlow.cpp
)

INCLUDE_DIRECTORIES(
	${FLAIR_INCLUDE_DIR}
	$ENV{FLAIR_ROOT}/flair-src/demos/OpticalFlow/uav/src
)

#real time executable
ADD_EXECUTABLE(${PROJECT_NAME}_rt
	${SRC_FILES}
)

TARGET_LINK_LIBRARIES(${PROJECT_NAME}_rt ${FLAIR_LIBRARIES_RT})

#non real time executable
ADD_EXECUTABLE(${PROJECT_NAME}_nrt
	${SRC_FILES}
)

TARGET_LINK_LIBRARIES(${PROJECT_NAME}_nrt ${FLAIR_LIBRARIES_NRT})


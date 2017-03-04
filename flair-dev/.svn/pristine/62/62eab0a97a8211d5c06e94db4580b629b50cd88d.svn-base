find_package(LibXml2 REQUIRED)
find_package(Xenomai QUIET)

if(NOT XENOMAI_FOUND)
	warn("Xenomai not found, you will not be able to link a real time program")
endif()

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

SET(FLAIR_INCLUDE_DIR	
	${LIBXML2_INCLUDE_DIR}	
	${CMAKE_SYSROOT}/usr/include/opencv
	${FLAIR_DEV}/include/FlairCore
)
SET(FLAIR_LIBRARY_DIR
	${FLAIR_BIN}/lib/${ARCH_DIR}
)

SET(FLAIR_LIBRARIES	
	${LIBXML2_LIBRARIES}
	udt pthread cv cxcore highgui FileLib rt z
)

#VRPN for motion capture
IF (FLAIR_USE_VRPN)
	SET(FLAIR_LIBRARIES vrpn ${FLAIR_LIBRARIES})
ENDIF (FLAIR_USE_VRPN)

#nmea for GPS
IF (FLAIR_USE_GPS)
	SET(FLAIR_LIBRARIES nmea ${FLAIR_LIBRARIES})
ENDIF (FLAIR_USE_GPS)

#core, will be replace by rt or nrt version at the end
SET(FLAIR_LIBRARIES FlairCore ${FLAIR_LIBRARIES})

#sensor and actuator lib
IF (FLAIR_USE_SENSOR_ACTUATOR)
	SET(FLAIR_INCLUDE_DIR ${FLAIR_INCLUDE_DIR} ${FLAIR_DEV}/include/FlairSensorActuator)
	SET(FLAIR_LIBRARIES ${FLAIR_LIBRARY_DIR}/libFlairSensorActuator.a ${FLAIR_LIBRARIES})
ENDIF (FLAIR_USE_SENSOR_ACTUATOR)

#filter lib
IF (FLAIR_USE_FILTER)
	SET(FLAIR_INCLUDE_DIR ${FLAIR_INCLUDE_DIR} ${FLAIR_DEV}/include/FlairFilter)
	SET(FLAIR_LIBRARIES ${FLAIR_LIBRARY_DIR}/libFlairFilter.a iir ${FLAIR_LIBRARIES})
ENDIF (FLAIR_USE_FILTER)

#meta lib
IF (FLAIR_USE_META)
	SET(FLAIR_INCLUDE_DIR ${FLAIR_INCLUDE_DIR} ${FLAIR_DEV}/include/FlairMeta)
	SET(FLAIR_LIBRARIES ${FLAIR_LIBRARY_DIR}/libFlairMeta.a ${FLAIR_LIBRARIES})
ENDIF (FLAIR_USE_META)

#simulator lib
IF (FLAIR_USE_SIMULATOR)
	if("${CMAKE_SYSTEM_PROCESSOR}" MATCHES "arm")
		SET(FLAIR_USE_SIMULATOR_GL FALSE)
	endif()
	SET(FLAIR_INCLUDE_DIR ${FLAIR_INCLUDE_DIR}
		${FLAIR_DEV}/include/FlairSimulator
		${CMAKE_SYSROOT}/usr/include/irrlicht
		${FLAIR_DEV}/include/FlairSensorActuator
		${CMAKE_SYSROOT}/usr/include/vrpn
		)
	
	SET(SIMU_LIBRARY ${FLAIR_LIBRARY_DIR}/libFlairSensorActuator.a)
	IF (FLAIR_USE_SIMULATOR_GL)
		ADD_DEFINITIONS("-DGL")
		SET(FLAIR_LIBRARIES ${FLAIR_LIBRARY_DIR}/libFlairSimulator_gl.a
			 ${SIMU_LIBRARY} GL vrpn ${FLAIR_LIBRARIES} Irrlicht Xxf86vm)
	else()
		SET(FLAIR_LIBRARIES ${FLAIR_LIBRARY_DIR}/libFlairSimulator_nogl.a ${SIMU_LIBRARY} vrpn ${FLAIR_LIBRARIES})
	endif()
ENDIF (FLAIR_USE_SIMULATOR)

#set RT or NRT specific libraries
set(FLAIR_LIBRARIES_RT ${FLAIR_LIBRARIES} ${XENOMAI_LIBRARIES})

list(FIND FLAIR_LIBRARIES_RT "FlairCore" POS)
if(POS GREATER -1)
	list(REMOVE_AT FLAIR_LIBRARIES_RT ${POS})
	list(INSERT FLAIR_LIBRARIES_RT ${POS} "${FLAIR_LIBRARY_DIR}/libFlairCore_rt.a")
endif()

set(FLAIR_LIBRARIES_NRT ${FLAIR_LIBRARIES})

list(FIND FLAIR_LIBRARIES_NRT "FlairCore" POS)
if(POS GREATER -1)
	list(REMOVE_AT FLAIR_LIBRARIES_NRT ${POS})
	list(INSERT FLAIR_LIBRARIES_NRT ${POS} "${FLAIR_LIBRARY_DIR}/libFlairCore_nrt.a")
endif()

#check if we have a flair-hds directory
if (IS_DIRECTORY $ENV{FLAIR_ROOT}/flair-hds )
	message("found flair-hds directory")
	SET(FLAIRHDS_LIBRARY_DIR
		$ENV{FLAIR_ROOT}/flair-hds/bin/lib/${ARCH_DIR}
	)	

	if(FLAIR_USE_FILTER)
		SET(FLAIR_INCLUDE_DIR ${FLAIR_INCLUDE_DIR} $ENV{FLAIR_ROOT}/flair-hds/dev/include/VisionFilter)
		SET(FLAIR_LIBRARIES_NRT ${FLAIRHDS_LIBRARY_DIR}/libVisionFilter.a ${FLAIRHDS_LIBRARY_DIR}/libdspcv_gpp.a ${FLAIR_LIBRARIES_NRT})
		SET(FLAIR_LIBRARIES_RT ${FLAIRHDS_LIBRARY_DIR}/libVisionFilter.a ${FLAIRHDS_LIBRARY_DIR}/libdspcv_gpp.a ${FLAIR_LIBRARIES_RT})
	endif()

	if(FLAIR_USE_META AND "${CMAKE_SYSTEM_PROCESSOR}" MATCHES "arm")	
		SET (ARDRONE2_LIB -Wl,--whole-archive ${FLAIRHDS_LIBRARY_DIR}/libFlairArdrone2.a -Wl,--no-whole-archive)
		set(FLAIR_LIBRARIES_NRT ${ARDRONE2_LIB}  ${FLAIR_LIBRARIES_NRT} nmea)
	endif()
endif()

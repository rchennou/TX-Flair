if(NOT DEFINED ENV{FLAIR_ROOT})
	message(FATAL_ERROR  "variable FLAIR_ROOT not defined")
endif()

include($ENV{FLAIR_ROOT}/flair-dev/cmake-modules/ColoredMessage.cmake)

if(NOT DEFINED ENV{FLAIR_ROOT})
	err("variable FLAIR_ROOT not defined")
endif()

if(NOT FLAIR_DEV)
	IF(FLAIR_DEV_TAG)
		warn("Configuring flair-dev and flair-bin for tag ${FLAIR_DEV_TAG}")
		SET(FLAIR_DEV $ENV{FLAIR_ROOT}/flair-dev_svn/tags/${FLAIR_DEV_TAG})
		SET(FLAIR_BIN $ENV{FLAIR_ROOT}/flair-bin_svn/tags/${FLAIR_DEV_TAG})
		if(EXISTS "${FLAIR_DEV}/cmake-modules/GlobalCmakeUAV.cmake")
			UNSET(FLAIR_DEV_TAG)
			include(${FLAIR_DEV}/cmake-modules/GlobalCmakeUAV.cmake)
			return()
		else()
		   	err("File not found ${FLAIR_DEV}/cmake-modules/GlobalCmakeUAV.cmake Please check that ${FLAIR_DEV} is up to date")
		endif()
	ELSE()
		SET(FLAIR_DEV $ENV{FLAIR_ROOT}/flair-dev)
		SET(FLAIR_BIN $ENV{FLAIR_ROOT}/flair-bin)
	ENDIF()
ENDIF()

include(${FLAIR_DEV}/cmake-modules/ArchDir.cmake)

list(APPEND CMAKE_MODULE_PATH ${FLAIR_DEV}/cmake-modules/)

#framework
SET(FLAIR_USE_FILE ${FLAIR_DEV}/cmake-modules/FlairUseFile.cmake)

#default executable ouput paths
if(NOT DEFINED EXECUTABLE_OUTPUT_PATH)
	SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
endif()
if(NOT DEFINED TARGET_EXECUTABLE_OUTPUT_PATH)
	SET(TARGET_EXECUTABLE_OUTPUT_PATH bin/arm)
endif()

#reimplement add executable to add a custom target for delivery (only on ARM)
#delivery are read from ssh config file
function(ADD_EXECUTABLE)
	if("${CMAKE_SYSTEM_PROCESSOR}" MATCHES "arm" AND EXISTS "$ENV{HOME}/.ssh/config")
		file(STRINGS $ENV{HOME}/.ssh/config TEST)
		foreach(f ${TEST})
			string(FIND ${f} "Host " POS)#cherche ligne host
			if(${POS} GREATER -1)
				string(REPLACE Host "" TARGET_NAME ${f})#enleve Host
				string(STRIP ${TARGET_NAME} TARGET_NAME)#enleve les espaces
			endif()
			string(FIND ${f} HostName POS)#cherche hostname
			if(${POS} GREATER -1)
				string(FIND ${f} "192.168." POS)#cherche addresse
				if(${POS} GREATER 0)#garde que les adresses en 192.168.6.x
					string(REPLACE HostName "" ADDRESS ${f})#enleve Hostname
					string(STRIP ${ADDRESS} ADDRESS)#enleve les espaces
					message("adding delivery target for " ${ARGV0} " (" ${ADDRESS} ")")
					string(REPLACE "/" "_" TARGET_PATH ${TARGET_EXECUTABLE_OUTPUT_PATH})#les / ne sont pas acceptés
					add_custom_target(
					    delivery_root@${ADDRESS}_${TARGET_PATH}_${ARGV0}
					    COMMAND make
					    COMMAND scp ${EXECUTABLE_OUTPUT_PATH}/${ARGV0} root@${ADDRESS}:${TARGET_EXECUTABLE_OUTPUT_PATH}
					)
				endif()
			endif()
		endforeach(f) 
	endif()
	#call original function
	_ADD_EXECUTABLE(${ARGV})
endfunction()

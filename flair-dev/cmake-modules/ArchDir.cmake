if("${CMAKE_SYSTEM_PROCESSOR}" MATCHES "arm")
        SET(ARCH_DIR "arm")
elseif("${CMAKE_SYSTEM_PROCESSOR}" MATCHES "powerpc")
	  SET(ARCH_DIR "powerpc")
else()
	if(WIN32)
		if(MINGW)
			if (CMAKE_SIZEOF_VOID_P MATCHES "8")#64 bits
				SET(ARCH_DIR "x86_64/win")
			else()#32 bits
				SET(ARCH_DIR "x86/win")
				ADD_DEFINITIONS(-D__MINGW__)
			endif()
		else()
			message(FATAL_ERROR,"only supports mingw compiler")
	    	endif()
	else()	
		if (CMAKE_SIZEOF_VOID_P MATCHES "8")#64 bits
			SET(ARCH_DIR "x86_64/unix")
		else()#32 bits
			SET(ARCH_DIR "i686/unix")
		endif()
	endif()
endif()

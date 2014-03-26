#
# Try to find GLFW3 library and include path.
# Once done this will define
#
# LIBOVR_FOUND
# LIBOVR_INCLUDE_PATH
# LIBOVR_LIBRARY
# 

IF (MINGW)
	FIND_PATH( LIBOVR_INCLUDE_PATH OVR.h
		${DEPENDENCIES_PATH}/LibOVR/Include 
	)
	message(${LIBOVR_INCLUDE_PATH})

    FIND_LIBRARY( OVR_LIBRARY
        NAMES libovr
        PATHS
        ${DEPENDENCIES_PATH}/LibOVR/lib/lib_mingw
    )

ELSEIF (MSVC)
    FIND_PATH( LIBOVR_INCLUDE_PATH OVR.h
        ${DEPENDENCIES_PATH}/LibOVR/Include 
    )
    FIND_LIBRARY( OVR_LIBRARY
        NAMES libovr 
        PATHS
        ${DEPENDENCIES_PATH}/LibOVR/lib/lib_vs
    )

ELSEIF(APPLE)

	FIND_PATH(LIBOVR_INCLUDE_PATH OVR.h
	${DEPENDENCIES_PATH}/LibOVR_OSX/Include)
	
    FIND_LIBRARY( LIBOVR_LIBRARY
        NAMES libovr.a
        PATHS ${DEPENDENCIES_PATH}/LibOVR_OSX/Lib/MacOS
    )
	
	
	
ELSE()
	FIND_PATH(LIBOVR_INCLUDE_PATH OVR.h)
	FIND_LIBRARY(LIBOVR_LIBRARY
        NAMES libovr
	PATH_SUFFIXES dynamic) 
ENDIF ()



SET(LIBOVR_FOUND "NO")
IF (LIBOVR_INCLUDE_PATH AND LIBOVR_LIBRARY)
	SET(LIBOVR_LIBRARIES ${LIBOVR_LIBRARY})
	SET(LIBOVR_FOUND "YES")
    message("EXTERNAL LIBRARY 'LIBOVR' FOUND")
    message("LIBOVR_INCLUDE_PATH: " ${LIBOVR_INCLUDE_PATH})
ELSE()
    message("ERROR: EXTERNAL LIBRARY 'LIBOVR' NOT FOUND")

ENDIF (LIBOVR_INCLUDE_PATH AND LIBOVR_LIBRARY)

#
# Try to find OpenNI library and include path.
# Once done this will define
#
# OPENNI_FOUND
# OPENNI_INCLUDE_PATH
# OPENNI_LIBRARY

# 
IF (MSVC)
    FIND_PATH( OPENNI_INCLUDE_PATH OpenNI.h
        ${DEPENDENCIES_PATH}/OpenNI/Include/
    )

    FIND_LIBRARY( OPENNI_LIBRARY
        NAMES OpenNI2
        PATHS
        ${DEPENDENCIES_PATH}/OpenNI/Lib
    )

    foreach (CONFIGURATION_TYPE ${CMAKE_CONFIGURATION_TYPES})
        execute_process(COMMAND ${CMAKE_COMMAND}  -E  copy_if_different
            ${DEPENDENCIES_PATH}/OpenNI/Redist/OpenNI2.dll
            ${PROJECT_BINARY_DIR}/bin/${CONFIGURATION_TYPE}/OpenNI2.dll
        )
    endforeach()

ELSE()
	FIND_PATH(OPENNI_INCLUDE_PATH OpenNI.h)
	FIND_LIBRARY(OPENNI_LIBRARY
        NAMES OpenNI2
	PATH_SUFFIXES dynamic) 
ENDIF ()



SET(OPENNI_FOUND "NO")
IF (OPENNI_INCLUDE_PATH AND OPENNI_LIBRARY)
	SET(OPENNI_LIBRARIES ${OPENNI_LIBRARY})
	SET(OPENNI_FOUND "YES")
    message("EXTERNAL LIBRARY 'OPENNI' FOUND")
    message("OPENNI_LIBRARY: " ${OPENNI_LIBRARY})
    message("OPENNI_INCLUDE_PATH: " ${OPENNI_INCLUDE_PATH})
ELSE()
    message("ERROR: EXTERNAL LIBRARY 'OPENNI' NOT FOUND")
ENDIF (OPENNI_INCLUDE_PATH AND OPENNI_LIBRARY)
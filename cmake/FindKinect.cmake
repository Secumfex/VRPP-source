#
# Try to find KindectSDK library and include path.
# Once done this will define
#
# KINECTSDK_FOUND
# KINECT_INCLUDE_PATH
# KINECT_LIBRARY

# 
IF (MSVC)
    FIND_PATH( KINECT_INCLUDE_PATH NuiApi.h
        ${DEPENDENCIES_PATH}/Kinect/v1.8/inc/
		
    )
message("nuiapiblaa " ${KINECT_INCLUDE_PATH})
    FIND_LIBRARY( KINECT_LIBRARY
        NAMES Kinect10
        PATHS
        ${DEPENDENCIES_PATH}/Kinect/v1.8/lib/x86
    )

    foreach (CONFIGURATION_TYPE ${CMAKE_CONFIGURATION_TYPES})
        execute_process(COMMAND ${CMAKE_COMMAND}  -E  copy_if_different
            ${DEPENDENCIES_PATH}/Kinect/v1.8/Assemblies/Microsoft.Kinect.dll
            ${PROJECT_BINARY_DIR}/bin/${CONFIGURATION_TYPE}/Microsoft.Kinect.dll
        )
    endforeach()

ELSE()
	FIND_PATH(KINECT_INCLUDE_PATH NuiApi.h)
	FIND_LIBRARY(KINECT_LIBRARY
        NAMES Kinect10
	PATH_SUFFIXES dynamic) 
ENDIF ()



SET(KINECT_FOUND "NO")
IF (KINECT_INCLUDE_PATH AND KINECT_LIBRARY)
	SET(KINECT_LIBRARIES ${KINECT_LIBRARY})
	SET(KINECT_FOUND "YES")
    message("EXTERNAL LIBRARY 'KINECT' FOUND")
    message("KINECT_LIBRARY: " ${KINECT_LIBRARY})
    message("KINECT_INCLUDE_PATH: " ${KINECT_INCLUDE_PATH})
ELSE()
    message("ERROR: EXTERNAL LIBRARY 'KINECT' NOT FOUND")
ENDIF (KINECT_INCLUDE_PATH AND KINECT_LIBRARY)
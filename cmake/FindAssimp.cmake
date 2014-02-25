#
# Try to find GLFW3 library and include path.
# Once done this will define
#
# ASSIMP_FOUND
# ASSIMP_INCLUDE_PATH
# ASSIMP_LIBRARY
# 

IF (MINGW)
	FIND_PATH( ASSIMP_INCLUDE_PATH assimp/ai_assert.h
		${DEPENDENCIES_PATH}/assimp/include/
	)

    FIND_LIBRARY( ASSIMP_LIBRARY
        NAMES assimp.dll
        PATHS
        ${DEPENDENCIES_PATH}/assimp/mingw/lib/
    )

    FIND_LIBRARY( ZLIB_LIBRARY
        NAMES zlibstatic
        PATHS
        ${DEPENDENCIES_PATH}/assimp/mingw/lib/
    )

    SET(ASSIMP_LIBRARY ${ZLIB_LIBRARY} ${ASSIMP_LIBRARY})
    execute_process(COMMAND ${CMAKE_COMMAND}  -E  copy_if_different
        ${DEPENDENCIES_PATH}/assimp/mingw/bin/libassimp.dll
        ${PROJECT_BINARY_DIR}/bin/libassimp.dll
    )

ELSEIF (MSVC)
    FIND_PATH( ASSIMP_INCLUDE_PATH assimp/ai_assert.h
        ${DEPENDENCIES_PATH}/assimp/include/
    )

    FIND_LIBRARY( ASSIMP_LIBRARY
        NAMES assimp
        PATHS
        ${DEPENDENCIES_PATH}/assimp/lib/x86
    )

    foreach (CONFIGURATION_TYPE ${CMAKE_CONFIGURATION_TYPES})
        execute_process(COMMAND ${CMAKE_COMMAND}  -E  copy_if_different
            ${DEPENDENCIES_PATH}/assimp/bin/x86/Assimp32.dll
            ${PROJECT_BINARY_DIR}/bin/${CONFIGURATION_TYPE}/Assimp32.dll
        )
    endforeach()

ELSEIF(APPLE)

	FIND_PATH(ASSIMP_INCLUDE_PATH assimp.h
	${DEPENDENCIES_PATH}/assimp_OSX/include)
	
	FIND_LIBRARY( ASSIMP_LIBRARY
        NAMES libassimpd.dylib
  		PATHS ${DEPENDENCIES_PATH}/assimp_OSX/lib/Debug
	)

ELSE()
	FIND_PATH(ASSIMP_INCLUDE_PATH assimp.h)
	FIND_LIBRARY(ASSIMP_LIBRARY
        NAMES assimp
	PATH_SUFFIXES dynamic) 
ENDIF ()



SET(ASSIMP_FOUND "NO")
IF (ASSIMP_INCLUDE_PATH AND ASSIMP_LIBRARY)
	SET(ASSIMP_LIBRARIES ${ASSIMP_LIBRARY})
	SET(ASSIMP_FOUND "YES")
    message("EXTERNAL LIBRARY 'ASSIMP' FOUND")
    message("ASSIMP_LIBRARY: " ${ASSIMP_LIBRARY})
    message("ASSIMP_INCLUDE_PATH: " ${ASSIMP_INCLUDE_PATH})
ELSE()
    message("ERROR: EXTERNAL LIBRARY 'ASSIMP' NOT FOUND")
ENDIF (ASSIMP_INCLUDE_PATH AND ASSIMP_LIBRARY)
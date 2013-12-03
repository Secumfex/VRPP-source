#
# Try to find GLFW3 library and include path.
# Once done this will define
#
# BULLET_FOUND
# BULLET_INCLUDE_PATH
# BULLET_LIBRARY
# 

IF (MINGW)
	FIND_PATH( BULLET_INCLUDE_PATH BULLET/bullet.h
		${DEPENDENCIES_PATH}/bullet/src 
	)

    FIND_LIBRARY( BULLET_LIBRARY
        NAMES libBulletCollision libBulletDynamics libBulletFileLoader libBulletSoftBody libBulletWorldImporter libBulletXmlWorldImporter libConvexDecomposition libGIMPACTUtils libHACD libLinearMath libOpenGLSupport 
        PATHS
        ${DEPENDENCIES_PATH}/bullet/lib_mingw
    )

ELSEIF (MSVC)
	FIND_PATH( BULLET_INCLUDE_PATH BULLET/bullet.h
		${DEPENDENCIES_PATH}/bullet/src 
	)

    FIND_LIBRARY( BULLET_LIBRARY
        NAMES libBulletCollision libBulletDynamics 	libBulletFileLoader libBulletMuliThreaded 	libBulletSoftBody libBulletWorldImporter libBulletXmlWorldImporter libConvexDecomposition libGIMPACTUtils libHACD MiniCL
        PATHS
        ${DEPENDENCIES_PATH}/bullet/lib_vs
    )

    foreach (CONFIGURATION_TYPE ${CMAKE_CONFIGURATION_TYPES})
        execute_process(COMMAND ${CMAKE_COMMAND}  -E  copy_if_different
            ${DEPENDENCIES_PATH}/glfw-3.0.2.bin.WIN32/lib-msvc110/glfw3.dll
            ${PROJECT_BINARY_DIR}/bin/${CONFIGURATION_TYPE}/
        )
    endforeach()

ELSEIF(APPLE)

	FIND_PATH(GLFW3_INCLUDE_PATH GLFW/glfw3.h
	${DEPENDENCIES_PATH}/glfw-3.0.3_OSX/include)
	
	FIND_LIBRARY( GLFW3_LIBRARY
        NAMES libglfw3.a
  		PATHS ${DEPENDENCIES_PATH}/glfw-3.0.3_OSX/build/src)

ELSE()
	FIND_PATH(BULLET_INCLUDE_PATH BULLET/bullet.h)
	FIND_LIBRARY(BULLET_LIBRARY
        NAMES bullet
	PATH_SUFFIXES dynamic) 
ENDIF ()



SET(BULLET_FOUND "NO")
IF (BULLET_INCLUDE_PATH AND BULLET_LIBRARY)
	SET(BULLET_LIBRARIES ${BULLET_LIBRARY})
	SET(BULLET_FOUND "YES")
    message("EXTERNAL LIBRARY 'GLFW3' FOUND")
    message("BULLET_LIBRARY: " ${BULLET_LIBRARY})
    message("BULLET_INCLUDE_PATH: " ${BULLET_INCLUDE_PATH})
ELSE()
    message("ERROR: EXTERNAL LIBRARY 'BULLET' NOT FOUND")
ENDIF (BULLET_INCLUDE_PATH AND BULLET_LIBRARY)
#
# Try to find GLFW3 library and include path.
# Once done this will define
#
# BULLET_FOUND
# BULLET_INCLUDE_PATH
# BULLET_LIBRARY
# 

IF (MINGW)
	FIND_PATH( BULLET_INCLUDE_PATH bullet.h
		${DEPENDENCIES_PATH}/bullet/src 
	)
    FIND_LIBRARY( BULLET_LIBRARY
        NAMES libBulletFileLoader  libBulletXmlWorldImporter libConvexDecomposition libGIMPACTUtils libHACD libOpenGLSupport libBulletWorldImporter libBulletSoftBody libBulletDynamics libBulletCollision libLinearMath 
        PATHS
        ${DEPENDENCIES_PATH}/bullet/lib_mingw
    )

ELSEIF (MSVC)
	FIND_PATH( BULLET_INCLUDE_PATH bullet.h
		${DEPENDENCIES_PATH}/bullet/src 
	)

    FIND_LIBRARY( BULLET_LIBRARY
        NAMES ConvexDecomposition GIMPACTUtils BulletFileLoader BulletMuliThreaded MiniCL BulletWorldImporter BulletXmlWorldImporter BulletSoftBody BulletSoftBodySolvers_OpenCL_MiniHACD BulletDynamics BulletCollision LinearMath
        PATHS
        ${DEPENDENCIES_PATH}/bullet/lib_vs
    )


ELSEIF(APPLE)

	FIND_PATH(BULLET_INCLUDE_PATH bullet.h
	${DEPENDENCIES_PATH}/bullet_osx/src)
	
	FIND_LIBRARY( BULLET_LIBRARY
        NAMES libBulletDynamics libBulletCollision libLinearMath
  		PATHS ${DEPENDENCIES_PATH}/bullet-osx/lib)

ELSE()
	FIND_PATH(BULLET_INCLUDE_PATH bullet.h)
	FIND_LIBRARY(BULLET_LIBRARY
        NAMES bullet
	PATH_SUFFIXES dynamic) 
ENDIF ()



SET(BULLET_FOUND "NO")
IF (BULLET_INCLUDE_PATH AND BULLET_LIBRARY)
	SET(BULLET_LIBRARIES ${BULLET_LIBRARY})
	SET(BULLET_FOUND "YES")
    message("EXTERNAL LIBRARY 'BULLET' FOUND")
    message("BULLET_LIBRARY: " ${BULLET_LIBRARY})
    message("BULLET_INCLUDE_PATH: " ${BULLET_INCLUDE_PATH})
ELSE()
    message("ERROR: EXTERNAL LIBRARY 'BULLET' NOT FOUND")
ENDIF (BULLET_INCLUDE_PATH AND BULLET_LIBRARY)
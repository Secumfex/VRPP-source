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
    FIND_LIBRARY( l1
        NAMES libBulletFileLoader 
        PATHS
        ${DEPENDENCIES_PATH}/bullet/lib_mingw
    )

    FIND_LIBRARY( l2
        NAMES  libBulletXmlWorldImporter 
        PATHS
        ${DEPENDENCIES_PATH}/bullet/lib_mingw
    )

    FIND_LIBRARY( l3
        NAMES  libConvexDecomposition 
        PATHS
        ${DEPENDENCIES_PATH}/bullet/lib_mingw
    )

    FIND_LIBRARY( l4
        NAMES  libBulletWorldImporter 
        PATHS
        ${DEPENDENCIES_PATH}/bullet/lib_mingw
    )

    FIND_LIBRARY( l5
        NAMES  libBulletSoftBody
        PATHS
        ${DEPENDENCIES_PATH}/bullet/lib_mingw
    )

    FIND_LIBRARY( l6
        NAMES  libOpenGLSupport 
        PATHS
        ${DEPENDENCIES_PATH}/bullet/lib_mingw
    )

    FIND_LIBRARY( l7
        NAMES  libBulletDynamics 
        PATHS
        ${DEPENDENCIES_PATH}/bullet/lib_mingw
    )

    FIND_LIBRARY( l8
        NAMES  libBulletCollision 
        PATHS
        ${DEPENDENCIES_PATH}/bullet/lib_mingw
    )

    FIND_LIBRARY( l9
        NAMES  libLinearMath 
        PATHS
        ${DEPENDENCIES_PATH}/bullet/lib_mingw
    )

    set(BULLET_LIBRARY ${l1} ${l2} ${l3} ${l4} ${l5} ${l6} ${l7} ${l8} ${l9})

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

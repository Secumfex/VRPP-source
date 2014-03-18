#ifndef	NOASSIMPVIRTUALOBJECTFACTORY_H
#define NOASSIMPVIRTUALOBJECTFACTORY_H

#include "Visuals/VirtualObject.h"

/** \brief a workaround class which is able to create a generic cube Virtual Object without relying on Assimp libraries, for testing or trouble-shooting purposes
 *
 */
class NoAssimpVirtualObjectFactory{
private:
	/** \brief create a VAO from Cube Geometry
	 *
	 * @return GLuint
	 */
	GLuint createCubeVAO();

	/** \brief create mesh by creating a VAO from Cube Geometry
	 *
	 * @return cubeMesh
	 */
	Mesh* createCubeMesh();
	
	/** \brief create material by loading some textures
	 *
	 * @return cubeMaterial
	 */
	Material* createCubeMaterial();
	
public:
	/** \brief create a Cube VirtualObject
	 *
	 * @param mass defines the behavior of the rigid body in the physics world
	 * @return a virtual object
	 */
	VirtualObject* createCubeObject(float mass = 0.0);
};

#endif

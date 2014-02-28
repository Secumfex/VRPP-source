#ifndef	NOASSIMPVIRTUALOBJECTFACTORY_H
#define NOASSIMPVIRTUALOBJECTFACTORY_H

#include "Visuals/VirtualObject.h"

/// a workaround class which is able to create a generic cube Virtual Object without relying on Assimp libraries, for testing or trouble-shooting purposes
class NoAssimpVirtualObjectFactory{
private:
	GLuint createCubeVAO();		//!< create a VAO from Cube Geometry
	
	Mesh* createCubeMesh();		//!< create mesh by creating a VAO from Cube Geometry
	Material* createCubeMaterial(); //!< create material by loading some textures 
	
public:
	VirtualObject* createCubeObject();	//!< create a Cube VirtualObject
};

#endif
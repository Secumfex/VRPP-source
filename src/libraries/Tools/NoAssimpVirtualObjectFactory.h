#ifndef	NOASSIMPVIRTUALOBJECTFACTORY_H
#define NOASSIMPVIRTUALOBJECTFACTORY_H

#include "Visuals/VirtualObject.h"

class NoAssimpVirtualObjectFactory{
private:
	GLuint createCubeVAO();		//!< create a VAO from Cube Geometry
	
	Mesh* createCubeMesh();		//!< create mesh by creating a VAO from Cube Geometry
	Material* createCubeMaterial(); //!< create material by loading some textures 
	
public:
	VirtualObject* createCubeObject();	//!< create a Cube VirtualObject
};

#endif
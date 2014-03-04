#ifndef	NOASSIMPVIRTUALOBJECTFACTORY_H
#define NOASSIMPVIRTUALOBJECTFACTORY_H

#include "Visuals/VirtualObject.h"


class NoAssimpVirtualObjectFactory{
private:
	GLuint createCubeVAO();		//!< create a VAO from Cube Geometry
	GLuint createSphereVAO();		//!< create a VAO from Cube Geometry
	
	Mesh* createCubeMesh();		//!< create mesh by creating a VAO from Cube Geometry
	Mesh* createSphereMesh();		//!< create mesh by creating a VAO from Cube Geometry
	Material* createCubeMaterial(); //!< create material by loading some textures 
	

	vector<int > indices;
	vector<glm::vec3> vertices;
	vector<glm::vec3> normals;
	vector<glm::vec3> tangents;
	vector<glm::vec2> uvs;


	float radius;
	float diameter;
	float pi;
	int steps;

public:
	VirtualObject* createCubeObject();	//!< create a Cube VirtualObject
	VirtualObject* createSphereObject();	//!< create a Sphere VirtualObject
};

#endif

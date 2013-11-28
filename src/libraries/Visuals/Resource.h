#ifndef RESOURCE_H_
#define RESOURCE_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <glm/glm.hpp>
//#include "stb_image.h"
#include "Tools/glm.h"
#include <assimp/Importer.hpp>

#include <iostream>
#include <fstream>

using namespace std;


class Resource{

	//---------------MEMBER FUNCTIONS--------------------
public:

	virtual void streamToVRAM();
	virtual void getResource(char* filename);

	virtual void setName(char* name);
	//---------------MEMBER VARIABLES--------------------
private:
	char* mName;

public:
	GLuint VBO;

};

class Texture : public Resource {

	//---------------MEMBER FUNCTIONS--------------------
public:
	Texture ();
	~Texture ();
	void streamToVRAM();
	void getResource(char* filename);

	//---------------MEMBER VARIABLES--------------------
};

class Mesh : public Resource{

	//---------------MEMBER FUNCTIONS--------------------
public:
	Mesh();
	~Mesh();
	void streamToVRAM();
	void getResource(char* filename);
    vector<glm::vec3> returnMesh();//return the vertices of mesh data
	vector<GLfloat> getVertices();
	vector<GLuint> getIndices();
	vector<GLfloat> getNormals();
	vector<GLfloat> getUVs();

	//---------------MEMBER VARIABLES--------------------
private:
	GLfloat* mVertices;
	GLuint* mIndices;
	GLfloat* mNormals;
	GLfloat* mUVs;
    vector<glm::vec3> meshVertices;//to store all 3D model face vertices

};

#endif

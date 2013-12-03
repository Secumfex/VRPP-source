#ifndef RESOURCE_H_
#define RESOURCE_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <glm/glm.hpp>
//#include "stb_image.h"
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
	GLuint mHandle;

};

class Material : public Resource {

	//---------------MEMBER FUNCTIONS--------------------
public:
	Material ();
	~Material ();
	void streamToVRAM();
	void getResource(char* filename);

	//---------------MEMBER VARIABLES--------------------

	string* textures;

};

class Mesh : public Resource{

	//---------------MEMBER FUNCTIONS--------------------
public:
	Mesh();
	~Mesh();
	void streamToVRAM();
	void getResource(char* filename);
	vector<glm::vec3> returnMesh();

	//---------------MEMBER VARIABLES--------------------
private:


};

#endif /* RESOURCE_H */

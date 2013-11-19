#ifndef RESOURCE_H_
#define RESOURCE_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <glm/glm.hpp>

#include <iostream>
#include <fstream>

using namespace std;


class Resource{

	//---------------MEMBER FUNCTIONS--------------------
public:

	virtual void streamToVRAM();
	virtual void getResource(const char* filename);

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
	void getResource(const char* filename);

	//---------------MEMBER VARIABLES--------------------
};

class Mesh : public Resource{

	//---------------MEMBER FUNCTIONS--------------------
public:
	Mesh();
	~Mesh();
	void streamToVRAM();
	void getResource(const char* filename);
    vector<glm::vec3> returnMesh();//return the vertices of mesh data
	vector<float> getVertices();
	vector<float> getIndices();
	vector<float> getNormals();
	vector<float> getUVs();

	//---------------MEMBER VARIABLES--------------------
private:
	vector<glm::vec3> mVertices;
	vector<int> mIndices;
	vector<float> mNormals;
	vector<float> mUVs;
    vector<glm::vec3> meshVertices;//to store all 3D model face vertices

};

#endif

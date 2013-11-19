#ifndef RESOURCE_H_
#define RESOURCE_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <glm/glm.hpp>
<<<<<<< HEAD
#include <iostream>
#include <fstream>
=======


<<<<<<< HEAD
>>>>>>> 60d3bb6c9f47411894c4c4880de7d1065b5225d5
=======
>>>>>>> 60d3bb6c9f47411894c4c4880de7d1065b5225d5
using namespace std;


class Resource{

	//---------------MEMBER FUNCTIONS--------------------
public:
<<<<<<< HEAD
	//virtual void streamToVRAM();
	//virtual void getResource(const char* filename);
=======
	virtual void streamToVRAM();
	virtual void getResource(const char* filename);
	virtual void setName(char* name);
	//---------------MEMBER VARIABLES--------------------
private:
	char* mName;

public:
	GLuint VBO;
<<<<<<< HEAD
>>>>>>> 60d3bb6c9f47411894c4c4880de7d1065b5225d5
=======
>>>>>>> 60d3bb6c9f47411894c4c4880de7d1065b5225d5

};

class Texture : public Resource {

	//---------------MEMBER FUNCTIONS--------------------
public:
	Texture ();
	void streamToVRAM();
	void getResource(const char* filename);

	//---------------MEMBER VARIABLES--------------------
};

class Mesh : public Resource{

	//---------------MEMBER FUNCTIONS--------------------
public:
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

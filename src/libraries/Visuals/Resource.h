#ifndef RESOURCE_H_
#define RESOURCE_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <glm/glm.hpp>


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
	void streamToVRAM();
	void getResource(const char* filename);

	//---------------MEMBER VARIABLES--------------------
};

class Mesh : public Resource{

	//---------------MEMBER FUNCTIONS--------------------
public:
	void streamToVRAM();
	void getResource(const char* filename);
	vector<float> getVertices();
	vector<float> getIndices();
	vector<float> getNormals();
	vector<float> getUVs();

	//---------------MEMBER VARIABLES--------------------
private:
	vector<float> mVertices;
	vector<unsigned int> mIndices;
	vector<float> mNormals;
	vector<float> mUVs;

};

#endif

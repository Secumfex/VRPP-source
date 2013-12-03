#ifndef RESOURCE_H_
#define RESOURCE_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <glm/glm.hpp>
#include <assimp/Importer.hpp>
#include <Visuals/Shader.h>


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

	string matName;
	string mTextures[3];

	Shader* mDefaultShader;

	glm::vec3 mAmbColor;
	glm::vec3 mDiffColor;
	glm::vec3 mSpecColor;
	GLfloat mSpecCoeff;




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

#endif

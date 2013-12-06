#ifndef RESOURCE_H_
#define RESOURCE_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <glm/glm.hpp>
#include <assimp/Importer.hpp>
#include <vector>
class Shader;

#include <iostream>
#include <fstream>

using namespace std;


class Resource{

	//---------------MEMBER FUNCTIONS--------------------
public:

	virtual void streamToVRAM();
	//---------------MEMBER VARIABLES--------------------
private:

public:

};

class Material : public Resource {

	//---------------MEMBER FUNCTIONS--------------------
public:
	Material ();
	~Material ();
	void streamToVRAM();

	void setName(char* name);
	void setShader(Shader shader);
	void setAmbient(glm::vec3 ambient);
	void setDiffuse(glm::vec3 diffuse);
	void setSpecular(glm::vec3 specular);
	void setSpecularTerm(GLfloat term);
	void setTexture(int index, GLuint handle);

	Shader getShader();
	glm::vec3* getAmbient();
	glm::vec3* getDiffuse();
	glm::vec3* getSpecular();
	GLfloat getSpecularTerm();
	//---------------MEMBER VARIABLES--------------------

	char* mName;
	vector<GLuint> mTextures;

	Shader* mShader;

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
	void setVAO(GLuint vao);
	GLuint getVAO();

	//---------------MEMBER VARIABLES--------------------
private:
GLuint mVaoHandle;

};

#endif /* RESOURCE_H */

#ifndef RESOURCE_H_
#define RESOURCE_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <glm/glm.hpp>
#include <assimp/Importer.hpp>
#include <vector>
#include <Visuals/Texture.h>


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

	void setName(std::string name);
	void setAmbient(glm::vec3 ambient);
	void setDiffuse(glm::vec3 diffuse);
	void setSpecular(glm::vec3 specular);
	void setSpecularTerm(GLfloat term);

	void setAmbientMap(Texture* tex);
	void setDiffuseMap(Texture* tex);
	void setSpecularMap(Texture* tex);
	void setNormalMap(Texture* tex);
	void setHeightMap(Texture* tex);
	void setShadowMap(Texture* tex);

	Texture* getAmbientMap();
	Texture* getDiffuseMap();
	Texture* getSpecularMap();
	Texture* getNormalMap();
	Texture* getHeightMap();
	Texture* getShadowMap();

	glm::vec3* getAmbient();
	glm::vec3* getDiffuse();
	glm::vec3* getSpecular();
	GLfloat getSpecularTerm();

	//---------------MEMBER VARIABLES--------------------
private:
	std::string mName;
	vector<Texture*> mTextures;

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

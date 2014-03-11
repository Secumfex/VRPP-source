#ifndef RESOURCE_H_
#define RESOURCE_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <glm/glm.hpp>

// #include "assimp/Importer.hpp"
// #include "assimp/postprocess.h"
// #include "assimp/scene.h"

#include <vector>
#include <Visuals/Texture.h>

#include <iostream>
#include <fstream>

using namespace std;


class Resource{

	//---------------MEMBER FUNCTIONS--------------------
public:

	//---------------MEMBER VARIABLES--------------------
private:

public:

};

class Material : public Resource {

	//---------------MEMBER FUNCTIONS--------------------
public:
	Material ();
	~Material ();



	void setName(std::string name);
	void setAmbient(glm::vec3 ambient);
	void setDiffuse(glm::vec3 diffuse);
	void setSpecular(glm::vec3 specular);
	void setEmission(glm::vec3 emission);
	void setShininess(GLfloat term);
	void setReflectivity(GLfloat term);
    void setTransparency(GLfloat term);

	void setAmbientMap(Texture* tex);
	void setDiffuseMap(Texture* tex);
	void setEmissiveMap(Texture* tex);
	void setNormalMap(Texture* tex);
	void setHeightMap(Texture* tex);
	void setOpacityMap(Texture* tex);

	void setSpecularMap(Texture* tex);
	void setReflectionMap(Texture* tex);
	void setShininessMap(Texture* tex);
	void setDisplacementMap(Texture* tex);
	void setLightMap(Texture* tex);

	Texture* getAmbientMap();
	Texture* getDiffuseMap();
	Texture* getEmissiveMap();
	Texture* getNormalMap();
	Texture* getHeightMap();
	Texture* getOpacityMap();


	Texture* getSpecularMap();
	Texture* getReflectionMap();
	Texture* getShininessMap();
	Texture* getDisplacementMap();
	Texture* getLightMap();

	glm::vec3 getAmbient();
	glm::vec3 getDiffuse();
	glm::vec3 getSpecular();
	glm::vec3 getEmission();
	GLfloat getShininess();
    GLfloat getTransparency();

	std::string getName();

	bool hasNormalTexture();
	bool hasDiffuseTexture();
	bool hasAmbientTexture();
	bool hasEmissiveTexture();
	bool hasHeightTexture();
	bool hasOpacityTexture();
	bool hasSpecularTexture();
	bool hasReflectionTexture();
	bool hasShininessTexture();
	bool hasDisplacementTexture();
	bool hasLightTexture();


	//---------------MEMBER VARIABLES--------------------
private:
	std::string mName;
	vector<Texture*> mTextures;

	glm::vec3 mAmbColor;
	glm::vec3 mDiffColor;
	glm::vec3 mSpecColor;
	glm::vec3 mEmissColor;

	GLfloat mShininess;
    GLfloat mTransparency;

};

class Mesh : public Resource{

	//---------------MEMBER FUNCTIONS--------------------
public:
	Mesh();
	~Mesh();


	void setVAO(GLuint vao);
	GLuint getVAO();

	void setNumFaces(int faces);
	int getNumFaces();

	void setNumVertices(int verts);
	int getNumVertices();

	void setNumIndices(int verts);
	int getNumIndices();

	void setVertexPosition(std::vector<glm::vec3> position);
	std::vector<glm::vec3> getVertices();

	void addBoneWeight(GLuint boneweight);


	//---------------MEMBER VARIABLES--------------------
private:

		GLuint mVaoHandle;  //gleiche wie unten "vao",  also noch anpassen. (wurde jetzt gel�scht)

		int mNumFaces;
		int mNumVerts;
		int mNumIndices;

		std::vector<glm::vec3> mVertexPositions;

		std::vector<GLuint> mBoneWeights;



};

#endif /* RESOURCE_H */

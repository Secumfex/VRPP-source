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



	void setName(std::string name);//sets name
	void setAmbient(glm::vec3 ambient);//sets ambient color
	void setDiffuse(glm::vec3 diffuse);//sets diffuse color
	void setSpecular(glm::vec3 specular);//sets specular color
	void setEmission(glm::vec3 emission);//sets emissive color
	void setShininess(GLfloat term);//sets shininess
    void setTransparency(GLfloat term);//sets amount of transparancy

	void setAmbientMap(Texture* tex);//sets ambient texture
	void setDiffuseMap(Texture* tex);//sets diffuse texture
	void setEmissiveMap(Texture* tex);//sets emissive texture
	void setNormalMap(Texture* tex);//sets normal texture
	void setHeightMap(Texture* tex);//sets height texture
	void setOpacityMap(Texture* tex);//sets opacity texture
	void setSpecularMap(Texture* tex);//sets specular texture
	void setReflectionMap(Texture* tex);
	void setShininessMap(Texture* tex);
	void setDisplacementMap(Texture* tex);
	void setLightMap(Texture* tex);

	Texture* getAmbientMap();//returns ambient texture
	Texture* getDiffuseMap();//returns diffuse texture
	Texture* getEmissiveMap();//returns emissive texture
	Texture* getNormalMap();//returns normal texture
	Texture* getHeightMap();//returns height texture
	Texture* getOpacityMap();//returns opacity texture
	Texture* getSpecularMap();//returns specular texture
	Texture* getReflectionMap();//returns reflection texture
	Texture* getShininessMap();
	Texture* getDisplacementMap();
	Texture* getLightMap();

	glm::vec3 getAmbient();//returns ambient color
	glm::vec3 getDiffuse();//returns diffuse color
	glm::vec3 getSpecular();//returns specular color
	glm::vec3 getEmission();//returns emissive color
	GLfloat getShininess();//returns shininess value
    GLfloat getTransparency();//returns transparancy value

	std::string getName();//returns name

	bool hasNormalTexture();//checks wheather there's a normal texture or not
	bool hasDiffuseTexture();//checks wheather there's a diffuse texture or not
	bool hasAmbientTexture();//checks wheather there's a ambient texture or not
	bool hasEmissiveTexture();//checks wheather there's a emissive texture or not
	bool hasHeightTexture();//checks wheather there's a height texture or not
	bool hasOpacityTexture();//checks wheather there's a opacity texture or not
	bool hasSpecularTexture();//checks wheather there's a specular texture or not
	bool hasReflectionTexture();//checks wheather there's a reflection texture or not
	bool hasShininessTexture();//checks wheather there's a shininess texture or not
	bool hasDisplacementTexture();//checks wheather there's a displacement texture or not
	bool hasLightTexture();//checks wheather there's a light texture or not


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


	void setVAO(GLuint vao);//sets VAO
	GLuint getVAO();//returns VAO

	void setNumFaces(int faces);//sets number of faces
	int getNumFaces();//returns number of faces

	void setNumVertices(int verts);//sets number of vertices
	int getNumVertices();//returns number of vertices

	void setNumIndices(int verts);//sets number of indices
	int getNumIndices();//returns number of indices

	void setVertexPosition(std::vector<glm::vec3> position);//sets an array of vertex positions
	std::vector<glm::vec3> getVertices();//returns list of vertices

	void addBoneWeight(GLuint boneweight);//list of bufferhandles for bone weights


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

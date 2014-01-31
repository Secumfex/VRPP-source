#include "Resource.h"
#include <string>
#include <sstream>
#include <cstdlib>
#include <GLFW/glfw3.h>




//---------------RESOURCE SCOPE--------------------


//---------------TEXTURE SCOPE--------------------

	Material :: Material(){
	Texture* tex = new Texture();
	mTextures.push_back(tex);
	mTextures.push_back(tex);
	mTextures.push_back(tex);
	mTextures.push_back(tex);
	mTextures.push_back(tex);
	mTextures.push_back(tex);
		mAmbColor = glm::vec3(1,1,1);
		mDiffColor = glm::vec3(1,1,1);
		mName = "";
		mSpecCoeff = 0;
		mEmissColor = mAmbColor;
}
	Material :: ~Material(){}

void Material ::setAmbientMap(Texture* tex){
	mTextures[0] = tex;
}
void Material ::setDiffuseMap(Texture* tex){
	mTextures[1] = tex;
}
void Material ::setSpecularMap(Texture* tex){
	mTextures[2] = tex;
}
void Material ::setNormalMap(Texture* tex){
	mTextures[3] = tex;
}
void Material ::setHeightMap(Texture* tex){
	mTextures[4] = tex;
}
void Material ::setShadowMap(Texture* tex){
	mTextures[5] = tex;
}

void Material :: setName(std::string name){
	mName = name;
}
void Material :: setAmbient(glm::vec3 ambient){
	mAmbColor = ambient;
}
void Material :: setDiffuse(glm::vec3 diffuse){
	mDiffColor = diffuse;
}
void Material :: setSpecular(glm::vec3 specular){
	mSpecColor = specular;
}
void Material :: setEmission(glm::vec3 emission){}
void Material :: setShininess(GLfloat term){}

Texture* Material ::getAmbientMap(){
	return mTextures[0];
}
Texture* Material ::getDiffuseMap(){
	return mTextures[1];
}
Texture* Material ::getSpecularMap(){
	return mTextures[2];
}
Texture* Material ::getNormalMap(){
	return mTextures[3];
}
Texture* Material ::getHeightMap(){
	return mTextures[4];
}
Texture* Material ::getShadowMap(){
	return mTextures[5];
}

glm::vec3 Material ::getAmbient(){
	return mAmbColor;
}
glm::vec3 Material ::getDiffuse(){
	return mDiffColor;
}
glm::vec3 Material ::getSpecular(){
	return mSpecColor;
}
glm::vec3 Material ::getEmission(){
	return mEmissColor;
}

//---------------MESH SCOPE--------------------

	Mesh::Mesh() {
	mNumFaces = 0;
	mNumIndices = 0;
	mVaoHandle = 0;
	mNumVerts = 0;
	}
	Mesh::~Mesh() { }

	void Mesh :: setVAO(GLuint vao){
		mVaoHandle=vao;}

	GLuint Mesh :: getVAO(){
	return mVaoHandle;
}

	void Mesh::setNumFaces (int faces){
	mNumFaces=faces;}

	int Mesh::getNumFaces(){
		return mNumFaces;
	}


	void Mesh::setNumVertices (int verts){
		mNumVerts = verts;
	}

	int Mesh::getNumVertices(){
		return mNumVerts;
	}

	void Mesh::setNumIndices (int indices){
		mNumIndices = indices;
	}

	int Mesh::getNumIndices(){
		return mNumIndices;
}

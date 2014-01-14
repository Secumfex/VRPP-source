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

void Material :: setName(std::string name){}
void Material :: setAmbient(glm::vec4 ambient){}
void Material :: setDiffuse(glm::vec4 diffuse){}
void Material :: setSpecular(glm::vec4 specular){}
void Material :: setEmission(glm::vec4 specular){}
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


//---------------MESH SCOPE--------------------

Mesh::Mesh() { }
Mesh::~Mesh() { }

void Mesh :: setVAO(GLuint vao){
mVaoHandle=vao;}

GLuint Mesh :: getVAO(){
	return mVaoHandle;
}

void Mesh::setUniformBlockIndex(GLuint ind){
	uniformBlockIndex=ind;}

	GLuint Mesh::getUniformBlockIndex(){
		return uniformBlockIndex;}

	void Mesh::setNumFaces (int faces){
	numFaces=faces;}

	int Mesh::getNumFaces(){
		return numFaces;
	}

	void Mesh::setTexIndex(int index){
	texIndex=index;}
	
	
	int Mesh::getTexIndex(){
	return texIndex;
	}


#include "Resource.h"
#include <string>
#include <sstream>
#include <cstdlib>
#include <GLFW/glfw3.h>




//---------------RESOURCE SCOPE--------------------


void Resource :: streamToVRAM(){ }

//---------------TEXTURE SCOPE--------------------

void Material :: Material(){
	Texture* tex = new Texture();
	mTextures.push_back(tex);
	mTextures.push_back(tex);
	mTextures.push_back(tex);
	mTextures.push_back(tex);
	mTextures.push_back(tex);
	mTextures.push_back(tex);

}

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

void Mesh :: streamToVRAM(){
}

void Mesh :: setVAO(GLuint vao){}
GLuint Mesh :: getVAO(){
	return mVaoHandle;
}


Mesh::Mesh() { }
Mesh::~Mesh() { }

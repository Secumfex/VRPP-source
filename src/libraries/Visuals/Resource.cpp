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
	mShininess = 0;
	mEmissColor = mAmbColor;
    mTransparency = 0.0f;
}
Material :: ~Material(){}

void Material ::setAmbientMap(Texture* tex){ //ändern
	mTextures[0] = tex;
}
void Material ::setDiffuseMap(Texture* tex){
	mTextures[1] = tex;
}
void Material ::setEmissiveMap(Texture* tex){  //ändern
	mTextures[2] = tex;
}
void Material ::setNormalMap(Texture* tex){
	mTextures[3] = tex;
}
void Material ::setHeightMap(Texture* tex){
	mTextures[4] = tex;
}
void Material ::setOpacityMap(Texture* tex){
	mTextures[5] = tex;
}
void Material ::setSpecularMap(Texture* tex){
	mTextures[6] = tex;
}
void Material ::setReflectionMap(Texture* tex){
	mTextures[7] = tex;
}
void Material ::setShininessMap(Texture* tex){
	mTextures[8] = tex;
}
void Material ::setDisplacementMap(Texture* tex){
	mTextures[9] = tex;
}
void Material ::setLightMap(Texture* tex){
	mTextures[10] = tex;
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
void Material :: setEmission(glm::vec3 emission){
    mEmissColor = emission;
}
void Material :: setShininess(GLfloat term){
	mShininess = term;
}
void Material:: setTransparency(GLfloat term){
    mTransparency = term;
}

void Material:: setTransparency(GLfloat term){
    mTransparency = term;
}

Texture* Material ::getAmbientMap(){
	return mTextures[0];
}
Texture* Material ::getDiffuseMap(){
	return mTextures[1];
}
Texture* Material ::getEmissiveMap(){
	return mTextures[2];
}
Texture* Material ::getNormalMap(){
	return mTextures[3];
}
Texture* Material ::getHeightMap(){
	return mTextures[4];
}
Texture* Material ::getOpacityMap(){
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
GLfloat Material::getShininess(){
	return mShininess;
}

GLfloat Material::getTransparency(){
	return mTransparency;
}
GLfloat Material::getReflectivity(){
	return mReflectivity;

}

Texture* Material ::getSpecularMap(){
	return mTextures[6];
}
Texture* Material ::getReflectionMap(){
	return mTextures[7];
}
Texture* Material ::getShininessMap(){
	return mTextures[8];
}
Texture* Material ::getDisplacementMap(){
	return mTextures[9];
}
Texture* Material ::getLightMap(){
	return mTextures[10];
}


std::string Material::getName(){
	return mName;
}


bool Material::hasNormalTexture(){
Texture *tex = new Texture();
return getNormalMap()->getTextureHandle() != tex->getTextureHandle();
}
bool Material::hasDiffuseTexture(){
Texture *tex = new Texture();
return getDiffuseMap()->getTextureHandle() != tex->getTextureHandle();
}
bool Material::hasAmbientTexture(){
Texture *tex = new Texture();
return getAmbientMap()->getTextureHandle() != tex->getTextureHandle();
}
bool Material::hasEmissiveTexture(){
Texture *tex = new Texture();
return getEmissiveMap()->getTextureHandle() != tex->getTextureHandle();
}
bool Material::hasHeightTexture(){
Texture *tex = new Texture();
return getHeightMap()->getTextureHandle() != tex->getTextureHandle();
}
bool Material::hasOpacityTexture(){
Texture *tex = new Texture();
return getOpacityMap()->getTextureHandle() != tex->getTextureHandle();
}
bool Material::hasSpecularTexture(){
Texture *tex = new Texture();
return getSpecularMap()->getTextureHandle() != tex->getTextureHandle();
}
bool Material::hasReflectionTexture(){
Texture *tex = new Texture();
return getReflectionMap()->getTextureHandle() != tex->getTextureHandle();
}
bool Material::hasShininessTexture(){
Texture *tex = new Texture();
return getShininessMap()->getTextureHandle() != tex->getTextureHandle();
}
bool Material::hasDisplacementTexture(){
Texture *tex = new Texture();
return getDisplacementMap()->getTextureHandle() != tex->getTextureHandle();
}
bool Material::hasLightTexture(){
Texture *tex = new Texture();
return getLightMap()->getTextureHandle() != tex->getTextureHandle();

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
	mVaoHandle=vao;
}

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

void Mesh::setVertexPosition(std::vector<glm::vec3> position){
	mVertexPositions = position;
}

void Mesh::addBoneWeight(GLuint boneweight){
	mBoneWeights.push_back(boneweight);
}
std::vector<glm::vec3> Mesh::getVertices(){

	return mVertexPositions;
}

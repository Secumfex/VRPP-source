/*
 * Texture.cpp
 *
 *  Created on: 06.12.2013
 *      Author: Raphimulator
 */

#include <Visuals/Texture.h>

Texture::Texture(std::string filename) {
	mFilename = filename;
	mTexManager = TextureManager::getInstance();
	mTexManager->createTextureHandle(filename);
}
Texture::Texture() {
	mFilename = RESOURCES_PATH "/checkers.jpg";
	mTexManager = TextureManager::getInstance();
	mTexManager->createTextureHandle(RESOURCES_PATH "/checkers.jpg");
}
Texture::~Texture() {

}

std::string Texture::getTexName(){
	return mFilename;
}

GLuint Texture::getTextureHandle(){
	return mTexManager->getTextureHandle(mFilename);
}

void Texture:: bindTexture(){
    glBindTexture(GL_TEXTURE_2D, getTextureHandle());
}
void Texture:: unbindTexture(){
    glBindTexture(GL_TEXTURE_2D, 0);
}

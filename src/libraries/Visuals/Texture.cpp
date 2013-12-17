/*
 * Texture.cpp
 *
 *  Created on: 06.12.2013
 *      Author: Raphimulator
 */

#include <Visuals/Texture.h>

Texture::Texture(string filename) {
	mFilename = filename;
	mTexManager = TextureManager::getInstance();
	mTexManager->createTextureHandle(filename);
}

Texture::~Texture() {

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

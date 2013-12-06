/*
 * Texture.cpp
 *
 *  Created on: 06.12.2013
 *      Author: Raphimulator
 */

#include <Visuals/Texture.h>

Texture::Texture(std::string filename) {
	// TODO Auto-generated constructor stub
createTextureHandle(filename);
}

Texture::~Texture() {
	// TODO Auto-generated destructor stub
}

GLuint Texture::getTextureHandle(){
	return mTextureHandles[mFilename];
}
void Texture::createTextureHandle(std::string filename){

	if(mTextureHandles.find(filename)==mTextureHandles.end()){
		GLuint newHandle = TextureTools::loadTexture(filename);
        glBindTexture(GL_TEXTURE_2D, newHandle);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGBA, GL_FLOAT, 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

        mTextureHandles.insert(std::pair<char*, GLuint>(filename, newHandle));
	}

	mFilename = filename;
	 glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture:: bindTexture(){
    glBindTexture(GL_TEXTURE_2D, getTextureHandle());
}
void Texture:: unbindTexture(){
    glBindTexture(GL_TEXTURE_2D, 0);
}

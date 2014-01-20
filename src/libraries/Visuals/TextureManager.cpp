/*
 * TextureManager.cpp
 *
 *  Created on: 17.12.2013
 *      Author: Raphimulator
 */

#include <Visuals/TextureManager.h>

TextureManager::TextureManager() {
}

TextureManager::~TextureManager() {
}

bool TextureManager::createTextureHandle(string filename){

	if(mTextureHandles.find(filename)==mTextureHandles.end()){
		GLuint newHandle = TextureTools::loadTexture(filename);
		if(newHandle == -1){
            return false;}
        mTextureHandles.insert(pair<string, GLuint>(filename, newHandle));
	}
	 glBindTexture(GL_TEXTURE_2D, 0);
	 return true;
}

GLuint TextureManager::getTextureHandle(string filename){
	if(mTextureHandles.find(filename) == mTextureHandles.end())
		return 0;
	else
	return mTextureHandles[filename];
}

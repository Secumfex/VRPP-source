/*
 * TextureManager.h
 *
 *  Created on: 17.12.2013
 *      Author: Raphimulator
 */

#ifndef TEXTUREMANAGER_H_
#define TEXTUREMANAGER_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <map>
#include <Tools/TextureTools.h>
#include <Patterns/Singleton.h>

using namespace std;

class TextureManager : public Singleton<TextureManager>{
public:
	friend class Singleton<TextureManager>;
	TextureManager();
	virtual ~TextureManager();
	bool createTextureHandle(string filename);//creates a Texture and inserts a texture handle into a map
	GLuint getTextureHandle(string filename);//returns the desired Texture by its name

protected:
	map<string, GLuint> mTextureHandles;

};

#endif /* TEXTUREMANAGER_H_ */

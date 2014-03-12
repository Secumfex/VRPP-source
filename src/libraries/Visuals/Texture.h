/*
 * Texture.h
 *
 *  Created on: 06.12.2013
 *      Author: Raphimulator
 */

#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <map>
#include <Visuals/TextureManager.h>
#include <string>



class Texture {
	//-----------------MEMBER FUNCTIONS-----------------
public:
	/** Man macht die Textur direkt mit dem Dateinamen */
	Texture(std::string filename);
	Texture();
	virtual ~Texture();
	std::string getTexName();

	/** returns the Texture's handle */
	GLuint getTextureHandle();
	/** binds Texture*/
	void bindTexture();
	/** unbinds Texture*/
	void unbindTexture();

	//-----------------MEMBER VARIABLES-----------------
protected:

	string mFilename;

	TextureManager* mTexManager;
};

#endif /* TEXTURE_H_ */

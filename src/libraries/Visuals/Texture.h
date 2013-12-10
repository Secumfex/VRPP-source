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
#include <Tools/TextureTools.h>
#include <string>

class Texture {
	//-----------------MEMBER FUNCTIONS-----------------
public:
	/** Man macht die Textur direkt mit dem Dateinamen */
	Texture(std::string filename = "checkers.jpg");
	virtual ~Texture();
	/** Das Handle wird übergeben */
	GLuint getTextureHandle();
	/** Textur wird gebunden*/
	void bindTexture();
	/** Textur wird entbunden*/
	void unbindTexture();

private:
	void createTextureHandle(std::string filename);
	//-----------------MEMBER VARIABLES-----------------
private:
	/** hier werden alle nötigen Handles gespeichert, mehr nicht*/
	static std::map<std::string, GLuint> mTextureHandles;
	/** damit is der DateiPfad gemeint wie zB Wurst.jpg oder Pictures/Hallo.png */
	std::string mFilename;
	/** Format */
	int height;
	int width;
};

#endif /* TEXTURE_H_ */

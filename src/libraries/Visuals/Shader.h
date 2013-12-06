/*
 * Shader.h
 *
 *  Created on: 03.12.2013
 *      Author: Raphimulator
 */

#ifndef SHADER_H_
#define SHADER_H_

#include <Visuals/Resource.h>
#include <string>

class Shader {

	//-----------------MEMBER FUNCTIONS-----------------
public:
	Shader();
	virtual ~Shader();
	virtual void fillShader(Material* mat);
//	void setShaderPath(char*);
	char* getShaderPath();
	void setShaderHandle(GLuint handle);
	GLuint getShaderHandle();

	//-----------------MEMBER VARIABLES-----------------
private:

	char* mShaderPath;
	GLuint mShaderHandle;
};

#endif /* SHADER_H_ */

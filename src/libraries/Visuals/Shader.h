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
#include "Tools/ShaderTools.h"

class Shader {

	//-----------------MEMBER FUNCTIONS-----------------
private:
	Shader();
public:
	virtual ~Shader();
	virtual void fillShader(Material* mat, Mesh* mesh);
	std::string getShaderName();
	void setProgramHandle(GLuint handle);
	GLuint getProgramHandle();

	//-----------------MEMBER VARIABLES-----------------
private:

	std::string mShaderName;
	GLuint mProgramHandle;
};

class Phong : public Shader{
public:
	Phong();
	void fillShader(Material* mat, Mesh* mesh);

private:
	GLfloat ambient;
	GLfloat diffuse;
	GLfloat specular;
	GLfloat specularTerm;


};

#endif /* SHADER_H_ */

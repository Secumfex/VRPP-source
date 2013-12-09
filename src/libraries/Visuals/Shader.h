/*
 * Shader.h
 *
 *  Created on: 03.12.2013
 *      Author: Raphimulator
 */

#ifndef SHADER_H_
#define SHADER_H_

#include <Visuals/GraphicsComponent.h>
#include <string>
#include "Tools/ShaderTools.h"
#include <vector>

using namespace std;

class Shader {

	//-----------------MEMBER FUNCTIONS-----------------
private:
	Shader();
public:
	virtual ~Shader();
	virtual void uploadUniforms(GraphicsComponent* graphcomp);
	virtual void uploadUniforms(glm::mat4 modelMatrix, glm::mat4 viewMatrix, glm::mat4 projectionMatrix);
	std::string getShaderName();
	void setProgramHandle(GLuint handle);
	GLuint getProgramHandle();
	static void setLights(vector<glm:: vec3> sources, vector<glm:: vec3> colors);
	static void setMatrix(glm::mat4 matrix, int index);

	//-----------------MEMBER VARIABLES-----------------
private:
	vector<glm:: vec3> mLightsource;
	vector<glm:: vec3> mLightcolor;
	std::string mShaderName;
	GLuint mProgramHandle;
	vector<glm::mat4> mMatrizes;
};

class Phong : public Shader{
public:
	Phong();
	void uploadUniforms(GraphicsComponent* graphcomp);
	void uploadUniforms(glm::mat4 modelMatrix, glm::mat4 viewMatrix, glm::mat4 projectionMatrix);

private:
	GLuint modelHandle;
	GLuint viewHandle;
	GLuint inverseHandle;
	GLuint projectionHandle;


};

#endif /* SHADER_H_ */

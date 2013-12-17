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
#include <glm/gtc/type_ptr.hpp>

using namespace std;

class Shader {

	//-----------------MEMBER FUNCTIONS-----------------
public:

	Shader(string vertexShader, string fragmentShader);
	virtual ~Shader();
	void setShaderName(string name);
	virtual void uploadUniforms(GraphicsComponent* graphcomp);
	virtual void uploadUniforms(glm::mat4 modelMatrix, glm::mat4 viewMatrix, glm::mat4 projectionMatrix);
	std::string getShaderName();
	GLuint getProgramHandle();

	void uploadModelMatrix(glm::mat4 modelMatrix);
	void uploadViewMatrix(glm::mat4 viewMatrix);
	void uploadProjectionMatrix(glm::mat4 projectionMatrix);
	void uploadInverseMatrix (glm::mat4 modelMatrix, glm::mat4 viewMatrix);

	static void setLights(vector<glm:: vec3> sources, vector<glm:: vec3> colors);

private:
	void makeShader(string vert, string frag);

	//-----------------MEMBER VARIABLES-----------------
protected:
	std::string mShaderName;
	GLuint mProgramHandle;
};

#endif /* SHADER_H_ */

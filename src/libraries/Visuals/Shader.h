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
#include "Visuals/UploadUniformListeners.h"
#include "Patterns/Subject.h"
#include "VirtualObject.h"



class Shader : public Subject{

	//-----------------MEMBER FUNCTIONS-----------------
public:


	Shader(std::string vertexShader, std::string fragmentShader);
	virtual ~Shader();
	void setShaderName(std::string name);
	void uploadAllUniforms();

	std::string getShaderName();//returns shader name
	GLuint getProgramHandle();//return program handle


	bool uploadUniform(glm::mat4 uniformMatrix, std::string uniformName);//this uploads a single uniform to this shader program
	bool uploadUniform(glm::vec3 uniformVector, std::string uniformName);//this uploads a single uniform to this shader program
	bool uploadUniform(GLfloat uniformVariable, std::string uniformName);//this uploads a single uniform to this shader program
	bool uploadUniform(GLint uniformVariable, std::string uniformName);//this uploads a single uniform to this shader program

	bool hasUniform(std::string uniformName);//checks on wheather the shader program owns a certain uniform variable

	std::vector<std::string> getUniformNames();



	void useProgram();//binds the shader program

	void render(GraphicsComponent *gc);//renders a GraphicsComponent

	void attachUniformListener(std::string uniform);//attaches UniformListeners to our Shader

	void setBlurStrength(int strength);//TODO: this will be moved out of this class
	GLint getBlurStrength();//TODO: this will be moved out of this class

private:
	void makeShader(std::string vert, std::string frag); //

	//-----------------MEMBER VARIABLES-----------------
protected:


	std::map<std::string, GLuint> mUniformHandles;

	std::vector<std::string> mUniformNames;

	std::string mShaderName;

	GLuint mProgramHandle;

	GLint blurStrength;

};

#endif /* SHADER_H_ */

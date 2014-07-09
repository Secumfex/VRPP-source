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

	/** \brief constructor
	 *
	 * @param shaders list of uncompiled shaderprograms
	 */
	Shader(std::vector<const char*> shaders);
	/** \brief constructor
	 *
	 * @param vertexShader
	 * @param fragmentShader
	 */
	Shader(std::string vertexShader, std::string fragmentShader);

	/** \brief destructor
	 *
	 */
	virtual ~Shader();

	/** \brief setter
	 *
	 * sets/changes mShaderName
	 * @param name
	 */
	void setShaderName(std::string name);

	/** \brief !docu pls!
	 *
	 */
	void uploadAllUniforms();

	/** \brief getter
	 *
	 * @return shader name
	 */
	std::string getShaderName();

	/** \brief getter
	 *
	 * @return program handle
	 */
	GLuint getProgramHandle();


	/** \brief this uploads a single uniform to this shader program
	 *
	 * @param uniformMatrix
	 * @param uniformName
	 */
	bool uploadUniform(glm::mat4 uniformMatrix, std::string uniformName);

	/** \brief this uploads a single uniform to this shader program
	 *
	 * @param uniformVector
	 * @param uniformName
	 */
	bool uploadUniform(glm::vec3 uniformVector, std::string uniformName);

	/** \brief this uploads a single uniform to this shader program
	 *
	 * @param uniformVariable as GLfloat
	 * @param uniformName
	 */
	bool uploadUniform(GLfloat uniformVariable, std::string uniformName);

	/** \brief this uploads a single uniform to this shader program
	 *
	 * @param uniformVariable as GLuint
	 * @param uniformName
	 */
	bool uploadUniform(GLint uniformVariable, std::string uniformName);


	/** \brief checks on wheather the shader program owns a certain uniform variable
	 *
	 * @param uniformName
	 * @return true or false
	 */
	bool hasUniform(std::string uniformName);

	/** \brief getter
	 *
	 *@return vector of uniform names
	 */
	std::vector<std::string> getUniformNames();


	/** \brief binds the shader program
	 *
	 */
	void useProgram();

	/** \brief renders a GraphicsComponent
	 *
	 * @param gc
	 */
	void render(GraphicsComponent *gc);
    // void render(VirtualObject *vo);

	/** \brief attach listener
	 *
	 * attaches UniformListeners to our Shader
	 * @param uniform
	 */
	void attachUniformListener(std::string uniform);

	void setBlurStrength(int strength);//TODO: this will be moved out of this class
	GLint getBlurStrength();//TODO: this will be moved out of this class

private:
	/** \brief !docu pls!
	 *
	 * @param vert
	 * @param frag
	 */
	void makeShader(std::string vert, std::string frag); //

	void getShaderInfo();

	void useMinimalColorOutput();

	//-----------------MEMBER VARIABLES-----------------
protected:

	std::vector<std::string> mOutputs;

	std::map<std::string, GLuint> mUniformHandles;	/**< !docu pls! */

	std::vector<std::string> mUniformNames;			/**< !docu pls! */

	std::string mShaderName;						/**< !docu pls! */

	GLuint mProgramHandle;							/**< !docu pls! */

	GLint blurStrength;								/**< !docu pls! */

	// some maps to keep track of what is active and only upload new stuff when necessary
	std::map<std::string, GLint> mActiveUniformsInt;
	std::map<std::string, GLfloat> mActiveUniformsFloat;
	std::map<std::string, glm::vec3> mActiveUniformsVec3;
	std::map<std::string, glm::mat4> mActiveUniformsMat4;
};

#endif /* SHADER_H_ */

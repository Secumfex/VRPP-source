/*
 * ShaderManager.cpp
 *
 *  Created on: 09.12.2013
 *      Author: Raphimulator
 */

#include <Visuals/ShaderManager.h>

ShaderManager :: ShaderManager() {
}

ShaderManager :: ~ShaderManager() {
}
void ShaderManager :: addShader(Shader* shader){
	mShaders.push_back(shader);
}
Shader* ShaderManager :: getShader(std::string shaderName){
	for (unsigned int i = 0; i < sizeof(mShaders) ; ++i) {
		if(mShaders[i]->getShaderName() == shaderName)
			return mShaders[i];
	}
	return 0;
}


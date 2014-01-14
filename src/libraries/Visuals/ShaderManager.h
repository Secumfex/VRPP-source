/*
 * ShaderManager.h
 *
 *  Created on: 09.12.2013
 *      Author: Raphimulator
 */

#ifndef SHADERMANAGER_H_
#define SHADERMANAGER_H_

#include <vector>
#include <Visuals/Shader.h>

using namespace std;

class ShaderManager {
public:
	ShaderManager();
	virtual ~ShaderManager();

	vector<Shader*> mShaders;

	Shader* getShader(std::string shaderName);
	void addShader(Shader* shader);

};

#endif /* SHADERMANAGER_H_ */

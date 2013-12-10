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

	static vector<Shader> shaders;
};

#endif /* SHADERMANAGER_H_ */

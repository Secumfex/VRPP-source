/*
 * StreamManager.h
 *
 *  Created on: 29.11.2013
 *      Author: Raphimulator
 */

#ifndef STREAMMANAGER_H_
#define STREAMMANAGER_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <vector>
#include "GraphicsComponent.h"

using namespace std;

class StreamManager {
public:
	StreamManager();
	virtual ~StreamManager();
	//---------------MEMBER VARIABLES--------------------
private:
	GLuint currentProgramHandle;
	vector<glm:: vec3> mLightsource;
	vector<glm:: vec3> mLightcolor;

	//---------------MEMBER FUNCTIONS--------------------
	void setLights(vector<glm:: vec3> sources, vector<glm:: vec3> colors);

	void stream(GraphicsComponent graphic);

};

#endif /* STREAMMANAGER_H_ */

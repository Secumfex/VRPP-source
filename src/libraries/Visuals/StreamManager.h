/*
 * StreamManager.h
 *
 *  Created on: 29.11.2013
 *      Author: Raphimulator
 */

#ifndef STREAMMANAGER_H_
#define STREAMMANAGER_H_

#include <glm/glm.hpp>
#include <vector>

using namespace std;

class StreamManager {
public:
	StreamManager();
	virtual ~StreamManager();
	//---------------MEMBER VARIABLES--------------------
	vector<glm:: vec3> mLightsource;
	vector<glm:: vec3> mLightcolor;

	//---------------MEMBER FUNCTIONS--------------------
	void setLights(int i);

};

#endif /* STREAMMANAGER_H_ */

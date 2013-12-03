/*
 * StreamManager.cpp
 *
 *  Created on: 29.11.2013
 *      Author: Raphimulator
 */

#include <Visuals/StreamManager.h>


StreamManager::StreamManager() {
	// TODO Auto-generated constructor stub

}

StreamManager::~StreamManager() {
	// TODO Auto-generated destructor stub
}

void StreamManager::setLights(vector<glm:: vec3> sources, vector<glm:: vec3> colors){}

void StreamManager::stream(GraphicsComponent graphic){

	//TODO:Check what shaderprogram is on the GPU

	//TODO:Compare with graphic required shader
	//TODO:bind or not

	//TODO:check ConcreteMaterial
	//TODO:upload if required
	graphic.getMaterial().streamToVRAM();

	//TODO:check for Mesh
	//TODO:upload Mesh
	graphic.getMesh().streamToVRAM();

	//TODO:get Modelmatrix
	//TODO:upload if required


}

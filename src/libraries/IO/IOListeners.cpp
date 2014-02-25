#include "IOListeners.h"

UpdateCameraPositionListener::UpdateCameraPositionListener(Camera* cam){
 	this->cam = cam;
}

void UpdateCameraPositionListener::update(){
	cam->updatePosition(0.01);	// assumed delta time: 10ms
}

ComputeFrameTimeListener::ComputeFrameTimeListener(){
}

void ComputeFrameTimeListener::update(){
	IOManager::getInstance()->computeFrameTimeDifference();	//compute Frame time in Manager
}
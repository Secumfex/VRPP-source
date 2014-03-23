#include "IOListeners.h"

UpdateCameraPositionListener::UpdateCameraPositionListener(Camera* cam, float* delta_time_source){
 	this->cam = cam;
 	if(delta_time_source != 0){
 		this->delta_time_source = delta_time_source;
 	}
}

void UpdateCameraPositionListener::update(){
	float d_t = 0.01;
	if (delta_time_source != 0){	//there is a source to get the actual delta_time from
		d_t = *delta_time_source;	//overwrite
	}
	cam->updatePosition(d_t);	// update with provided delta_time
}

ComputeFrameTimeListener::ComputeFrameTimeListener(){
}

void ComputeFrameTimeListener::update(){
	IOManager::getInstance()->computeFrameTimeDifference();	//compute Frame time in Manager
}

UpdateWindowTimeListener::UpdateWindowTimeListener(){
}

void UpdateWindowTimeListener::update(){
	IOManager::getInstance()->updateWindowTime();	//compute Frame time in Manager
}

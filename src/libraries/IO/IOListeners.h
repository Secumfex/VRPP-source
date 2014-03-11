#ifndef IOLISTENERS_H
#define IOLISTENERS_H

#include "Patterns/Listener.h"
#include "IOManager.h"
#include "Camera.h"

/// @brief Listener which calls Camera::updatePosition(float d_t) on every update 
class UpdateCameraPositionListener : public Listener{
private:
	Camera* cam;
	float* delta_time_source;
public:
	/*! @param cam : Camera Opject supposed to update
	*   @param delta_time_source : a pointer to a float variable (optional)
	*/
	UpdateCameraPositionListener(Camera* cam, float* delta_time_source = 0);
	void update();
};

/// @brief Listener which calls IOManager::computeFrameTimeDifference() on every update
class ComputeFrameTimeListener : public Listener{
public:
	ComputeFrameTimeListener();
	void update();
};

#endif
#ifndef IOLISTENERS_H
#define IOLISTENERS_H

#include "Patterns/Listener.h"
#include "IOManager.h"
#include "Camera.h"

class UpdateCameraPositionListener : public Listener{
private:
	Camera* cam;
	float* delta_time_source;
public:
	UpdateCameraPositionListener(Camera* cam, float* delta_time_source = 0);
	void update();
};

class ComputeFrameTimeListener : public Listener{
public:
	ComputeFrameTimeListener();
	void update();
};

#endif
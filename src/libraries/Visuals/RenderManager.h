#ifndef RENDERMANAGER_H
#define RENDERMANAGER_H
#include "IO/IOManager.h"
#include "Visuals/RenderQueue.h"

class RenderManager{
public:
	RenderQueue renderQueue;
	IOManager iOManager;
	void renderLoop();
};

#endif

#ifndef STATE_H
#define STATE_H

#include "Visuals/RenderQueue.h"

class State{
	
};

class VRState : public State
{
public:
	void initPhysics();
	void initRenderer();
	void initScene();	//Virtual Objects
};

#endif

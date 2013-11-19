#ifndef STATE_H
#define STATE_H

#include "Visuals/RenderQueue.h"

class State{
public:
	virtual void printType();
	virtual ~State();
};

class VRState : public State
{
public:
	void initPhysics();
	void initRenderer();
	void initScene();	//Virtual Objects

	void printType();
};

#endif

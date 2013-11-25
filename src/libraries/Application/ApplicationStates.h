#ifndef APPLICATIONSTATES_H
#define APPLICATIONSTATES_H

#include "Patterns/State.h"

class ApplicationContext;

class ApplicationState : public State{
protected:
	virtual void setState(State* state, Context* context);
};

class IdleState : public ApplicationState {
};

class VRState : public ApplicationState {
protected:
	virtual void setState(State* state, Context* context);
public:
	void initRenderer();
	void initPhysics();
	void initScene();
};
#endif
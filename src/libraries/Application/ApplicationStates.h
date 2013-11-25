#ifndef APPLICATIONSTATES_H
#define APPLICATIONSTATES_H

#include "Patterns/State.h"

class ApplicationState : public State{

};

class IdleState : public ApplicationState {

};

class VRState : public ApplicationState {
public:
	void initRenderer();
	void initPhysics();
	void initScene();
};
#endif
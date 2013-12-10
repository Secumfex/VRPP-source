#ifndef APPLICATIONSTATES_H
#define APPLICATIONSTATES_H

#include "Patterns/State.h"
//Base class of States specifically for the Application-Class
class ApplicationState : public State{
public:
	virtual void activate();
};

class IdleState : public ApplicationState {
};

class MenuState : public ApplicationState {
public:
	MenuState(std::string name = "");
};

class VRState : public ApplicationState {
public:
	VRState(std::string name = "");

	void activate();

	void initRenderer();
	void initPhysics();
	void initScene();
};
#endif
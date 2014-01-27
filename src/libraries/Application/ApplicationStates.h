#ifndef APPLICATIONSTATES_H
#define APPLICATIONSTATES_H

#include "Patterns/State.h"
#include "Patterns/Subject.h"
/// Base class of States specifically for the Application-Class
class ApplicationState : public State, public Subject{

protected: 
	virtual void bindObjects(); //!< bind objects to RenderManager, IOManager, PhysicsWorld etc.
public:
	virtual void activate(); //!< activation of state --> binding objects

	/*Application State Listeners*/
	void attachListenerOnActivation(Listener* listener); //!< attach Listener on Activation
	void attachListenerOnBindingObjects(Listener* listener); //!< attach Listener on binding objects 
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
};
#endif
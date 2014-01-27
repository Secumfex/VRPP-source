#ifndef APPLICATIONSTATES_H
#define APPLICATIONSTATES_H

#include <string.h>
#include <glm/glm.hpp>

#include "Patterns/State.h"
#include "Patterns/Subject.h"

class Camera; class RenderQueue; class VirtualObject;

/// Base class of States specifically for the Application-Class
class ApplicationState : public State, public Subject{


protected: 
	/*Member variables*/
	Camera* camera;
	RenderQueue* renderQueue;
//	InputHandler* InputHandler;
	glm::mat4 projectionMatrix;

	virtual void bindObjects(); //!< bind objects to RenderManager, IOManager, PhysicsWorld etc.
public:
	ApplicationState();

	virtual void activate(); //!< activation of state --> binding objects

	VirtualObject* createVirtualObject(std::string path); //!< create Object from path and add it to renderQueue

	/*Application State Listeners*/
	void attachListenerOnActivation(Listener* listener); //!< attach Listener on Activation
	void attachListenerOnBindingObjects(Listener* listener); //!< attach Listener on binding objects 
	void attachListenerOnCreatingVirtualObject(Listener* listener); //!< attach Listener on creating a new object
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
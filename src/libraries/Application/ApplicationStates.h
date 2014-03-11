#ifndef APPLICATIONSTATES_H
#define APPLICATIONSTATES_H

#include <string.h>
#include <glm/glm.hpp>

#include "Patterns/State.h"
#include "Patterns/Subject.h"
#include "IO/IOHandler.h"
#include "Visuals/Frustum.h"

class Camera; class RenderQueue; class VirtualObject;

/// Base class of States specifically for the Application-Class
class ApplicationState : public State{


protected: 
	/*Member variables*/
	Frustum* frustum;
	Camera* camera;
	RenderQueue* renderQueue;
	IOHandler* iOHandler;
	glm::mat4 perspectiveMatrix;

	virtual void bindObjects(); //!< bind objects to RenderManager, IOManager, PhysicsWorld etc.
public:
	ApplicationState();

	Frustum*		getFrustum();
	Camera* 		getCamera();
	RenderQueue* 	getRenderQueue();
	IOHandler* 		getIOHandler();
	glm::mat4 		getPerspectiveMatrix();

	virtual void activate(); //!< activation of state --> binding objects

	VirtualObject* createVirtualObject(std::string path); //!< create Object from path and add it to renderQueue
	void addVirtualObject(VirtualObject* vo); //!< add existing VO to renderQueue

	/*Application State Listeners*/
	void attachListenerOnActivation(Listener* listener); //!< attach Listener on Activation
	void attachListenerOnBindingObjects(Listener* listener); //!< attach Listener on binding objects 
	void attachListenerOnCreatingVirtualObject(Listener* listener); //!< attach Listener on creating a new object
	void attachListenerOnAddingVirtualObject(Listener* listener); //!< attach Listener on adding a new object
	void attachListenerOnButton(Listener* listener); //!< attach Listener on button press or button release
	void attachListenerOnBeginningProgramCycle(Listener* listener); //!< attach Listener on beginning Program Cycle
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

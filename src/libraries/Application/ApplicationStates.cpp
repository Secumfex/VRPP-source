#include "ApplicationStates.h"

#include <iostream>
using namespace std;

#include "Visuals/RenderManager.h"

void ApplicationState::activate(){
	State::activate();
	bindObjects();	

	notify("ACTIVATION_LISTENER");
}

void ApplicationState::bindObjects(){
	// RenderManager* rm = RenderManager::getInstance();
	
	// rm->setProjectionMatrix(projectionMatrix);
	// rm->setRenderQueue(renderQueue);

	// IOManager* io = IOManager::getInstance();
	// io->setCamera(camera);
	// io->setInputType(inputType);

	notify("BINDING_OBJECTS_LISTENER");
}

VRState::VRState(std::string name){
	setName(name);
}

void VRState::activate(){

	//bind Input-Object, RenderQueue-Object, Camera-Object, Projectionmatrix 
	ApplicationState::activate();
	
}

MenuState::MenuState(std::string name){
	setName(name);
}

/*Application States Listeners*/
void ApplicationState::attachListenerOnActivation(Listener* listener){
	listener->setName("ACTIVATION_LISTENER");
	attach(listener);
}

void ApplicationState::attachListenerOnBindingObjects(Listener* listener){
	listener->setName("BINDING_OBJECTS_LISTENER");
	attach(listener);
}
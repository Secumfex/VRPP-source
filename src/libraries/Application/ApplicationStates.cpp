#include "ApplicationStates.h"

#include <iostream>

#include <glm/gtc/matrix_transform.hpp>

using namespace std;

#include "Visuals/RenderManager.h"
#include "Visuals/VirtualObjectFactory.h"
#include "IO/IOManager.h"

ApplicationState::ApplicationState(){
	camera = new Camera();
	renderQueue = new RenderQueue();
//	InputHandler = new InputHandler();
	projectionMatrix = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.f);
}

void ApplicationState::activate(){
	State::activate();
	bindObjects();	

	notify("ACTIVATION_LISTENER");
}

void ApplicationState::bindObjects(){
	RenderManager* rm = RenderManager::getInstance();
	
	rm->setProjectionMatrix(projectionMatrix);
	rm->setRenderQueue(renderQueue);

	// @todo IOManager muss window Pointer kennen usw sonst NULL-Pointer im Konstruktor 
	// IOManager* io = IOManager::getInstance();
	// io->setCameraObject(camera);
	// io->setInputHandler(inputHandler);

	notify("BINDING_OBJECTS_LISTENER");
}

VirtualObject* ApplicationState::createVirtualObject(std::string path){
	VirtualObject* vo = VirtualObjectFactory::getInstance()->createVirtualObject(path);
	renderQueue->addVirtualObject(vo);

	notify("CREATE_VIRTUAL_OBJECT_LISTENER");	//in case someone cares
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

void ApplicationState::attachListenerOnCreatingVirtualObject(Listener* listener){
	listener->setName("CREATE_VIRTUAL_OBJECT_LISTENER");
	attach(listener);
}

void ApplicationState::attachListenerOnButton(Listener* listener){
	listener->setName("BUTTON_LISTENER");
	attach(listener);
}


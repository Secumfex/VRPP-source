#include "ApplicationStates.h"

#include <iostream>

#include <glm/gtc/matrix_transform.hpp>

using namespace std;

#include "Visuals/RenderManager.h"

#include "Visuals/VirtualObjectFactory.h"

#include "IO/IOManager.h"
#include "IO/IngameHandler.h"
#include "IO/IOListeners.h"

ApplicationState::ApplicationState(){
	camera = new Camera();
	renderQueue = new RenderQueue();
	iOHandler = new IngameHandler();
	frustum = new Frustum(camera);
	iOHandler->setCameraObject(camera);
	attachListenerOnBeginningProgramCycle(	new UpdateCameraPositionListener(camera, IOManager::getInstance()->getDeltaTimePointer()));
	

	perspectiveMatrix = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.f);
}

Frustum* ApplicationState::getFrustum(){
	return frustum;
}

Camera* ApplicationState::getCamera(){
	return camera;
}

RenderQueue* ApplicationState::getRenderQueue(){
	return renderQueue;
}

IOHandler* ApplicationState::getIOHandler(){
	return iOHandler;
}

glm::mat4 ApplicationState::getPerspectiveMatrix(){
	return perspectiveMatrix;
}

void ApplicationState::setRenderQueue(		RenderQueue* renderQueue){
	this->renderQueue = renderQueue;
}

void ApplicationState::setIOHandler(			IOHandler* iOHandler){
	this->iOHandler = iOHandler;
	this->iOHandler->setCameraObject(camera);
}
void ApplicationState::setPerspectiveMatrix(	glm::mat4 perspectiveMatrix){
	this->perspectiveMatrix = perspectiveMatrix;
}

void ApplicationState::setCamera(				Camera* camera){
	this->camera = camera;
	this->iOHandler->setCameraObject(camera);
	attachListenerOnBeginningProgramCycle(	new UpdateCameraPositionListener(camera, IOManager::getInstance()->getDeltaTimePointer()));
}

void ApplicationState::activate(){
	State::activate();
	bindObjects();	

	notify("ACTIVATION_LISTENER");
}

void ApplicationState::bindObjects(){
	RenderManager* rm = RenderManager::getInstance();
	
	rm->setCamera(camera);
	rm->setCurrentFrustum(frustum);
	rm->setPerspectiveMatrix(45.0f, 4.0f / 3.0f, 0.1f, 100.f);
	rm->setRenderQueue(renderQueue);

	IOManager* io = IOManager::getInstance();
	io->setCurrentIOHandler(iOHandler);

	notify("BINDING_OBJECTS_LISTENER");
}


VirtualObject* ApplicationState::createVirtualObject(std::string path, VirtualObjectFactory::BodyType bodyType, float mass, int collisionFlag){
	VirtualObject* vo = VirtualObjectFactory::getInstance()->createVirtualObject(path, bodyType, mass, collisionFlag);
	renderQueue->addVirtualObject(vo);


	notify("CREATE_VIRTUAL_OBJECT_LISTENER");	//in case someone cares

	return vo;
}

void ApplicationState::addVirtualObject(VirtualObject* vo){
	renderQueue->addVirtualObject(vo);
	notify("ADD_VIRTUAL_OBJECT_LISTENER");	//in case someone cares
}

VRState::VRState(std::string name){
	setName(name);
}

void VRState::activate(){

	//bind Input-Object, RenderQueue-Object, Camera-Object, Perspectivematrix
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


void ApplicationState::attachListenerOnAddingVirtualObject(Listener* listener){
	listener->setName("ADD_VIRTUAL_OBJECT_LISTENER");
	attach(listener);
}

void ApplicationState::attachListenerOnBeginningProgramCycle(Listener* listener){
	listener->setName("BEGINNINGPROGRAMCYCLELISTENER");
	attach(listener);
}

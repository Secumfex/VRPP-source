#include "ApplicationStates.h"

#include <iostream>
using namespace std;

#include "Visuals/RenderManager.h"

void ApplicationState::activate(){
	State::activate();
	bindObjects();	
}

void ApplicationState::bindObjects(){
	// RenderManager* rm = RenderManager::getInstance();
	
	// rm->setProjectionMatrix(projectionMatrix);
	// rm->setRenderQueue(renderQueue);

	// IOManager* io = IOManager::getInstance();
	// io->setCamera(camera);
	// io->setInputType(inputType);
}

VRState::VRState(std::string name){
	setName(name);
}

void VRState::activate(){
	//TODO let this only be called once at all by having a boolean variable or something
	initRenderer();
	initPhysics();
	initScene();

	//bind Input-Object, RenderQueue-Object, Camera-Object, Projectionmatrix 
	ApplicationState::activate();
	
}

void VRState::initRenderer(){
	cout<<"initializing Renderer..."<<endl;
	//TODO call RenderManager::initlibs which opens window, binds callbackfuncs, etc. 
}

void VRState::initPhysics(){
	cout<<"initializing Physics..."<<endl;
	//TODO find a Way to init Bullet library
}

void VRState::initScene(){
	cout<<"initializing Scene..."<<endl;
}

MenuState::MenuState(std::string name){
	setName(name);
}
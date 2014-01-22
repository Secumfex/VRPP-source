#include "ApplicationListeners.h"
#include "Application.h"
ActivateStateListener::ActivateStateListener(Application* application){
	this->application = application;
}

void ActivateStateListener::update(){
	application->getState()->activate();
}

SetStateListener::SetStateListener(Application* application, std::string state){
	this->state = state;
	this->application = application;
}

void SetStateListener::update(){
	application->setState(state);
}
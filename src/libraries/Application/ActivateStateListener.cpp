#include "ActivateStateListener.h"

ActivateStateListener::ActivateStateListener(Application* application){
	this->application = application;
}

void ActivateStateListener::update(){
	application->getState()->activate();
}
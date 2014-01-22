#include "ApplicationListeners.h"
#include "Application.h"

#include <iostream>

ApplicationListener::ApplicationListener(Application* application){
	this->application = application;
}

void ApplicationListener::update(){	
}

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

TerminateApplicationListener::TerminateApplicationListener(Application* application){
	this->application = application;
}

void TerminateApplicationListener::update(){
	application->terminate();
}
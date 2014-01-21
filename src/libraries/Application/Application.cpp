#include "Application.h"

#include <iostream>

#include "ApplicationListeners.h"
//Application starts in the Idle State
Application::Application(std::string label){
	this->label = label;
	currentState = 0;
	attachStateChangeListener(new ActivateStateListener(this));
}

void Application::setLabel(std::string label){
	this->label = label;
}

std::string Application::getLabel(){
	return label;
}

bool Application::setState(State* state){
	if (StateMachine::setState(state)){
		notify("STATECHANGELISTENER");
		return true;
	}
	return false;
}

bool Application::setState(std::string state){
	if (StateMachine::setState(state)){
		notify("STATECHANGELISTENER");
		return true;
	}
	return false;
}

void Application::attachStateChangeListener(Listener* listener){
	listener->setName("STATECHANGELISTENER");
	attach(listener);
}
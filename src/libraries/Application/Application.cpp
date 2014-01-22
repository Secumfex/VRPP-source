#include "Application.h"

#include <iostream>

#include "Visuals/RenderManager.h"

#include "ApplicationListeners.h"
//Application starts in the Idle State
Application::Application(std::string label){
	shouldTerminate = false;
	this->label = label;
	currentState = 0;
	attachListenerOnStateChange(new ActivateStateListener(this));
}

void Application::setLabel(std::string label){
	this->label = label;
}

void Application::terminate(){
	shouldTerminate = true;
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

void Application::run(){
	if(currentState == 0){	// no state set: terminate immediately 
		terminate();
	}

	while (!shouldTerminate){
		notify("BEGINNINGPROGRAMCYCLELISTENER");	// notify listeners of beginning program cycle

// @todo enable states to notify listeners (make subject of some sort)
//		currentState->notify("BEGINNINGPROGRAMCYCLELISTENER");		// notify listeners of active state of beginning program cycle

		RenderManager::getInstance()->renderLoop();
	}

	notify("PROGRAMTERMINATIONLISTENER");
}

//**** LISTENER INTERFACES ****//
void Application::attachListenerOnStateChange(Listener* listener){
	listener->setName("STATECHANGELISTENER");
	attach(listener);
}

void Application::attachListenerOnBeginningProgramCycle(Listener* listener){
	listener->setName("BEGINNINGPROGRAMCYCLELISTENER");
	attach(listener);
}

void Application::attachListenerOnProgramTermination(Listener* listener){
	listener->setName("PROGRAMTERMINATIONLISTENER");
	attach(listener);
}

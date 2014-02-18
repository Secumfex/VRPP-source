#include "Application.h"

#include <iostream>

#include "Visuals/RenderManager.h"
#include "IO/IOManager.h"

#include "ApplicationListeners.h"
//Application starts in the Idle State
Application::Application(std::string label){
	initialized = false;
	shouldTerminate = false;

	this->label = label;
	currentState = 0;

	// Init RenderManager and open window
	RenderManager* rm = RenderManager::getInstance();
	rm->libInit();

}

void Application::setLabel(std::string label){
	this->label = label;
	glfwSetWindowTitle(RenderManager::getInstance()->getWindow(),label.c_str());
}

void Application::initialize(){
	RenderManager* rm 	= RenderManager::getInstance();
	rm->manageShaderProgram();	// compile default Shader Program

	IOManager* io 		= IOManager::getInstance();
	io->setWindow(rm->getWindow());	// set window reference of IO Manager
	io->bindCallbackFuncs();		// bind callback methods

	rm->attachListenerOnWindowShouldClose(new TerminateApplicationListener(this));	//Application will close when Window is closed

	attachListenerOnStateChange(new ActivateStateListener(this));	// a new state will be activated upon being set
	
	if (currentState != 0){
		currentState->activate();	//activate the current state
	}

	notify("PROGRAMINITIALIZATIONLISTENER");
	
	initialized = true;
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
		currentState->notify("STATECHANGELISTENER");
		return true;
	}
	return false;
}

bool Application::setState(std::string state){
	if (StateMachine::setState(state)){
		notify("STATECHANGELISTENER");
		currentState->notify("STATECHANGELISTENER");
		return true;
	}
	return false;
}

void Application::run(){
	if(currentState == 0){	// no state set: terminate immediately 
		terminate();
	}
	
	if(!initialized){
		initialize();	//to ensure the RenderManager has been initialized and a window exists
	}

	while (!shouldTerminate){
		notify("BEGINNINGPROGRAMCYCLELISTENER");	// notify listeners of beginning program cycle

		currentState->notify("BEGINNINGPROGRAMCYCLELISTENER");		// notify listeners of active state of beginning program cycle

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

void Application::attachListenerOnProgramInitialization(Listener* listener){
	listener->setName("PROGRAMINITIALIZATIONLISTENER");
	attach(listener);
}

void Application::attachListenerOnRenderManagerFrameLoop(Listener* listener){
	RenderManager::getInstance()->attachListenerOnNewFrame(listener);
}

#include "UtilityListeners.h"

#include "Patterns/StateMachine.h"

#include <iostream>
PrintMessageListener::PrintMessageListener(std::string message){
	this->message = message;
}

void PrintMessageListener::update(){
	std::cout<< message << std::endl;
}

void PrintMessageListener::setMessage(std::string message){
	this->message = message;
}

std::string PrintMessageListener::getMessage(){
	return message;
}

PrintCurrentStateListener::PrintCurrentStateListener(StateMachine* stateMachine){
	this->stateMachine = stateMachine;
}

void PrintCurrentStateListener::update(){
	std::cout << "current State : " << stateMachine->getState()->getName() << std::endl;
}

TimedTriggerListener::TimedTriggerListener(Listener* target, float milliseconds){
	this->milliseconds = milliseconds;
	this->target = target;

	running = false;
	listener_triggered = false;
	current_time = 0.0;
}

void TimedTriggerListener::update(){
	 if (!running){	//not yet started
	 	running = true;
	 	last_clock_call = clock();
	 }
	 else{ //timer running
	 	if (!listener_triggered){ //target not yet triggered 
	 		clock_t current_clocks = clock();	//get current clock_time
			float d_t = ( ( (float)current_clocks - (float) last_clock_call ) / (float)CLOCKS_PER_SEC) * 1000.0; //time in ms since last call = (current time - last call) / clocks per sec * 1000.0
	 		current_time += d_t;
	 		last_clock_call = current_clocks;

			if (current_time >= milliseconds){	//target should be called
				target->update(); //call target
				listener_triggered = true;
			}
	 	}
	 }
}

PrintValueListener::PrintValueListener(float* value, std::string message){
	this->value = value;
	this->message = message;
}

void PrintValueListener::update(){
	std::cout << message << *value << std::endl;
}

#include "IO/Camera.h"

PrintCameraStatusListener::PrintCameraStatusListener(Camera* cam){
	this->cam = cam;
}

void PrintCameraStatusListener::update(){
	glm::vec3 pos 	= cam->getPosition();
	glm::vec3 dir 	= cam->getViewDirection();
	float phi 		= cam->getPhi();
	float theta		= cam->getTheta();

	std::cout << "Cam pos : "      << pos.x << " , " << pos.y << " , "    << pos.z << std::endl;
	std::cout << "Cam dir : "      << dir.x << " , " << dir.y << " , "    << dir.z << std::endl;
	std::cout << "rotation phi : " << phi   << " , pitch theta : " 		  << theta << std::endl;
}
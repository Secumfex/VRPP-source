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

PrintVec3Listener::PrintVec3Listener(glm::vec3* vector, std::string message){
	this->vector = vector;
	this->message = message;
}

void PrintVec3Listener::update(){
	std::cout << message << (*vector).x << ", " << (*vector).y << ", " << (*vector).z << std::endl;
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

SetFloatValueListener::SetFloatValueListener(float* target, float* source){
	this->source = source;
	this->target = target;
}

SetFloatValueListener::SetFloatValueListener(float* target, float source){
	this->target = target;
	this->source = new float(source);
}

void SetFloatValueListener::update(){
	*target = *source;
}

SetVec3ValuesListener::SetVec3ValuesListener(glm::vec3* target, glm::vec3* source){
	this->source = source;
	this->target = target;
}

SetVec3ValuesListener::SetVec3ValuesListener(glm::vec3* target, glm::vec3 source){
	this->target = target;
	this->source = new glm::vec3(source);
}

void SetVec3ValuesListener::update(){
	*target = *source;
}

bool DirtyFlagListener::getDirtyFlag() const {
	return dirtyFlag;
}

void DirtyFlagListener::setDirtyFlag(bool dirtyFlag) {
	this->dirtyFlag = dirtyFlag;
}

DirtyFlagListener::DirtyFlagListener() {
	dirtyFlag = false;
}

void DirtyFlagListener::update() {
	dirtyFlag = true;
}

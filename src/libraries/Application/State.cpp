#include "State.h"

#include <iostream>

void State::printType(){
	std::cout<< "State" <<std::endl;
}

State::~State(){ }
void VRState::initPhysics(){

}
void VRState::initRenderer(){

}
void VRState::initScene(){

}

void VRState::printType(){
	std::cout<< "VR State" <<std::endl;
}

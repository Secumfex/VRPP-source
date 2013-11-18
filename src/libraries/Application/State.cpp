#include "State.h"
#include <iostream>

void State::printType(){
	std::cout<< "State" <<std::endl;
}

State::~State(){ }

void VRState::initPhysics(){
	std::cout<<"initiating Physics..."<<std::endl;
}

void VRState::initRenderer(){
	std::cout<<"initiating Renderer..."<<std::endl;
}

void VRState::initScene(){
	std::cout<<"initiating Scene..."<<std::endl;
}

void VRState::printType(){
	std::cout<< "VR State" <<std::endl;
}

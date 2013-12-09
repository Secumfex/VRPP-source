#include "ApplicationStates.h"

#include <iostream>
using namespace std;

VRState::VRState(std::string name){
	setName(name);
}

void VRState::activate(){
	State::activate();
	initRenderer();
	initPhysics();
	initScene();
}

void VRState::initRenderer(){
	cout<<"initializing Renderer..."<<endl;
}

void VRState::initPhysics(){
	cout<<"initializing Physics..."<<endl;
}

void VRState::initScene(){
	cout<<"initializing Scene..."<<endl;
}

MenuState::MenuState(std::string name){
	setName(name);
}
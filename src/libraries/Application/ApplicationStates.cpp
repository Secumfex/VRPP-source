#include "ApplicationStates.h"

#include <iostream>
using namespace std;

void VRState::initRenderer(){
	cout<<"initializing Renderer..."<<endl;
}

void VRState::initPhysics(){
	cout<<"initializing Physics..."<<endl;
}

void VRState::initScene(){
	cout<<"initializing Scene..."<<endl;
}
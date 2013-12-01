#include "ApplicationStates.h"

#include <iostream>
using namespace std;

//By default, an ApplicationState get enter any state
void ApplicationState::setState(State* state, Context* context){
	State::setState(state,context);
}

//VR State cannot change to any other state
void VRState::setState(State* state, Context* context){
	//The State will not be changed, no matter the desired state
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
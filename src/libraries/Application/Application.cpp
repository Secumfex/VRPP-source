#include "Application.h"

#include <iostream>

Application::Application(){
	VRState vr;
	state = vr;
	std::cout<<"initiating VRState..."<<std::endl;
	vr.initPhysics();
	vr.initRenderer();
	vr.initScene();
}

void Application::setState(State to){
	state = to;
}

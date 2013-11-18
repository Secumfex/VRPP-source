#include "Application.h"

#include <iostream>
#include <typeinfo>

Application::Application(){
	VRState vr;
	state = vr;
	std::cout<<"initiating VRState..."<<std::endl;
	vr.initPhysics();
	vr.initRenderer();
	vr.initScene();
}

void Application::setState(State* to){
	std::cout<< "entering state : " ;
	to->printType();
	std::cout<<std::endl;
	state = *to;
}

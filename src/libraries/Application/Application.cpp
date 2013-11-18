#include "Application.h"

#include <iostream>
#include <typeinfo>

Application::Application(){
}

void Application::setState(State* to){
	std::cout<< "entering state : " ;
	to->printType();
	std::cout<<std::endl;
	state = *to;
}

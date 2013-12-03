#include "Application.h"

#include <iostream>

//Application starts in the Idle State
Application::Application(std::string label){
	this->label = label;
}

void Application::setLabel(std::string label){
	this->label = label;
}

std::string Application::getLabel(){
	return label;
}
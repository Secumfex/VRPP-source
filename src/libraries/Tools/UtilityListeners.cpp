#include "UtilityListeners.h"

#include <iostream>
PrintMessageListener::PrintMessageListener(std::string message){
	this->message = message;
}

void PrintMessageListener::update(){
	std::cout<<message;
}

void PrintMessageListener::setMessage(std::string message){
	this->message = message;
}

std::string PrintMessageListener::getMessage(){
	return message;
}
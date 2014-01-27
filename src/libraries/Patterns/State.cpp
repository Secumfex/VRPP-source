#include "State.h"

#include <iostream>
void State::activate(){
	//	std::cout<< name << " state active."<<std::endl;
}

std::string State::getName(){
	return name;
}

State::State(std::string name){
	this->name = name;
}
void State::setName(std::string name){
	this->name = name;
}
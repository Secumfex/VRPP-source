#include <Patterns/StateMachine.h>

void StateMachine::setState(string stateName){
	currentState = states.
}

void StateMachine::addState(State* state){
	states.insert(std::pair<char*, State*>(&(char)state->name), state);
}

State* StateMachine::getState(){
	return currentState;
}

#include <Patterns/StateMachine.h>

void StateMachine::setState(State* state){
	currentState = states[state->getName()];
}

void StateMachine::addState(State* state){
	states.insert(std::pair<const char*, State*>(state->getName(),state));
}

State* StateMachine::getState(){
	return currentState;
}

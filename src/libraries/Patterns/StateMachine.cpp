#include <Patterns/StateMachine.h>

void StateMachine::setState(State* state){
	if(states.find(state->getName()) != states.end()){
		currentState = states[state->getName()];
		}
	}

void StateMachine::addState(State* state){
	states.insert(std::pair<std::string, State*>(state->getName(),state));
}

State* StateMachine::getState(){
	return currentState;
}

StateMachine::~StateMachine(){}
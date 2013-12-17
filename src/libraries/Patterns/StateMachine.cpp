#include <Patterns/StateMachine.h>

bool StateMachine::setState(State* state){
	if(states.find(state->getName()) != states.end()){ 				//exists
		if(currentState != 0){
			if (currentState->getName().compare(state->getName()) == 0){	//already active
				return false;
			}
		}
		currentState = states[state->getName()];	
		return true;												//state change successful
	}
	return false;													//state change unsuccessful
}

bool StateMachine::setState(std::string state){
	if(states.find(state) != states.end()) 				//exists
	{
		if(currentState != 0){
			if (currentState->getName().compare(state) == 0){	//already active
				return false;
			}
		}
		currentState = states[state];	
		return true;												//state change successful
	}
	return false;													//state change unsuccessful
	}

void StateMachine::addState(State* state){
	states.insert(std::pair<std::string, State*>(state->getName(),state));
}

State* StateMachine::getState(){
	return currentState;
}

StateMachine::~StateMachine(){}

#include <Patterns/StateMachine.h>

bool StateMachine::setState(State* state){
	if(states.find(state->getName()) != states.end()){ 				//exists
		if(currentState != 0){
			if (currentState->getName().compare(state->getName()) == 0){	//already active
				return false;
			}
		}
		if(checkStateTransitionConstraint(state)){
			currentState = states[state->getName()];
			return true;												//state change successful
		}
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
		if(checkStateTransitionConstraint(state)){
			currentState = states[state];	
			return true;												//state change successful
		}
	}
	return false;													//state change unsuccessful
	}

void StateMachine::addState(State* state){

	if (states.size() == 0){							// initial state is first added state
		currentState = state;		
	}
	allowAllStateTransitionsTo(state);
	states.insert(std::pair<std::string, State*>(state->getName(),state));
}

State* StateMachine::getState(){
	return currentState;
}


State* StateMachine::getCurrentState(){
	return currentState;
}

std::list <State* >StateMachine::getStatesList(){
	std::list<State* > result;
	for (std::map<std::string , State* >::iterator it = states.begin(); it != states.end(); ++it ){
		result.push_back(it->second);
	}
	return result;
}

std::map<std::string, State* > StateMachine::getStatesMap(){
	return states;
}

StateMachine::~StateMachine(){}

StateMachine::StateMachine(){
	currentState = 0;
}

void StateMachine::forbidStateTransitionFromTo(State* 	 from, State*  	   to){
	stateTransitionConstraints.remove(std::pair<State*,State* >(from,to));
}
void StateMachine::forbidStateTransitionFromTo(std::string from, std::string to){
	for (std::list<std::pair<State*, State*> >::iterator it = stateTransitionConstraints.begin(); it != stateTransitionConstraints.end(); it++){
		if ((*it).first->getName().compare(from) == 0 && (*it).second->getName().compare(to) == 0){
			stateTransitionConstraints.erase(it);
		}
	}
} 
void StateMachine::allowStateTransitionFromTo (State* 	 from, State*  	   to){
	stateTransitionConstraints.push_back(std::pair<State*,State*>(from , to));
}
void StateMachine::allowStateTransitionFromTo (std::string from, std::string to) {
	if (states.find(from) != states.end() && states.find(to) != states.end() ){
		stateTransitionConstraints.push_back(std::pair<State*, State*> ( states[from], states[to]));
	}
}
void StateMachine::forbidAllStateTransitionsTo(State* to){
	 for (std::list<std::pair<State*, State*> >::iterator it = stateTransitionConstraints.begin(); it != stateTransitionConstraints.end(); it++){
		if ((*it).second->getName() == to->getName()){
			stateTransitionConstraints.erase(it);
		}
		
	}
}		
void StateMachine::forbidAllStateTransitionsFrom(State* from){
	 for (std::list<std::pair<State*, State*> >::iterator it = stateTransitionConstraints.begin(); it != stateTransitionConstraints.end(); it++){
		if ((*it).first->getName() == from->getName()){
			stateTransitionConstraints.erase(it);
		}
		
	}

}

void StateMachine::allowAllStateTransitionsTo(State* to){
	 for (std::map<std::string , State* >::iterator it = states.begin(); it != states.end(); ++it ){
		if ((*it).second != to){
			stateTransitionConstraints.push_back(std::pair<State*, State*> ((*it).second , to));
			stateTransitionConstraints.push_back(std::pair<State*, State*> (to,(*it).second));	
		}
	}
}

bool StateMachine::checkStateTransitionConstraint(State* to){
	for (std::list<std::pair<State*, State*> > :: iterator it = stateTransitionConstraints.begin(); it != stateTransitionConstraints.end();it++){
		if (std::pair<State*, State* > (currentState , to) == (*it)){
			return true;
		}
	}
	return false;
}

bool StateMachine::checkStateTransitionConstraint(std::string to){
	if (states.find(to) != states.end()){ 	//state exist
		return checkStateTransitionConstraint(states[to]);		//check via other function
	}
	else{
		return false;	//target state does not exist
	}
}
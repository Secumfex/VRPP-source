#ifndef STATEMACHINE_H_
#define STATEMACHINE_H_
#include "State.h"
#include <map>
#include <list>

class StateMachine {		//the new Context
friend class State;

protected:
	State* currentState;

private:
	std::map<std::string, State*> states;

public:
	virtual ~StateMachine();
	StateMachine();

	virtual bool setState(State* 		state);		//!< attempt to change state
	virtual bool setState(std::string 	state);		//!< attempt to change state
	virtual void addState(State* 		state);		//!< add new state to states pool

	State* getState();								//!< get current state
	State* getCurrentState(); 						//!< get current state

	std::map  <std::string, State* > getStatesMap() ; 
	std::list <State* 			  > getStatesList(); //!< get list of all possible states
};

#endif /* STATEMACHINE_H_ */

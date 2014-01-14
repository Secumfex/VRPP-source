#ifndef STATEMACHINE_H_
#define STATEMACHINE_H_
#include "State.h"
#include <map>

class StateMachine {		//the new Context
friend class State;

protected:
	State* currentState;

private:
	std::map<std::string, State*> states;

public:
	virtual ~StateMachine();

	virtual bool setState(State* state);
	virtual bool setState(std::string state);
	virtual void addState(State* state);
	State* getState();

	bool setInitialState(State* state);
	bool setInitialState(std::string state);

	
};

#endif /* STATEMACHINE_H_ */

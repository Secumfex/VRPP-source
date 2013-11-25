#ifndef CONTEXT_H
#define CONTEXT_H
#include "State.h"

class Context{		//a context
friend class State;
private:
	State* mState;	//is in a certain state
public:
	virtual void setState(State* state);	//can be set into a certain state
};
	
#endif
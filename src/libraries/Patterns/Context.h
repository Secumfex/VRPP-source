#ifndef CONTEXT_H
#define CONTEXT_H
#include "State.h"

class Context{		//a context
friend class State;
protected:
	State* mState;	//is in a certain state
public:
	virtual void setState(State* state);	//Tell the State Machine to change States to desired state
	State* getState();
};
	
#endif
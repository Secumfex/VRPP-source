#ifndef CONTEXT_H
#define CONTEXT_H

class State;

class Context{		//a context
private:
	State* mState;	//is in a certain state
public:
	virtual void setState(State* state);	//can be set into a certain state
};
	
#endif
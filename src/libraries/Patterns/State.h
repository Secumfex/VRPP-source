#ifndef STATE_H
#define STATE_H

class Context;
class State{	//a state of a context
	virtual void setState(State* state, Context* context);		//Depending on the State-Transistion-Model only some state changes are accepted
};

#endif

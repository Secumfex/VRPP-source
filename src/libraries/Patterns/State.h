#ifndef STATE_H
#define STATE_H

class Context;

class State{	//a state of a context

friend class Context;

protected:
	virtual void setState(State* state, Context* context);		//Depending on the State-Transistion-Model only some state changes are accepted

private:
	const char* name;

public:
	const char* getName();
};

#endif

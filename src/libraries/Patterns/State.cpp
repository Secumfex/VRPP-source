#include "State.h"

#include "Context.h"
//any state change is accepted by default
void State::setState(State* state, Context* context){ 
	context->mState = state;
}

const char* State::getName(){
	return name;
}

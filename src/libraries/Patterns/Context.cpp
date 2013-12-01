#include "Context.h"

void Context::setState(State* state){ 
	if(mState != 0){ 					//if old state is not NULL
		mState->setState(state,this);	//try to change from old state to the new state 
	}
}
State* Context::getState(){
	return mState;
}
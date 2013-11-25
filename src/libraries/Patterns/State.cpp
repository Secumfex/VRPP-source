#include "State.h"

#include "Context.h"
void State::setState(State* state, Context* context){ context->mState = state;}
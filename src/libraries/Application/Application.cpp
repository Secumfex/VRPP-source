#include "Application.h"

#include <iostream>

//Application starts in the Idle State
Application::Application(){
	mState = new IdleState();
}
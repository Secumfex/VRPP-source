#include "Application.h"

#include <iostream>

//Application starts in the Idle State
Application::Application(){
	setState(new IdleState());
}
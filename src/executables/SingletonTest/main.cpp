#include <iostream>
#include <string.h>

#include "Patterns/Singleton.h"
#include "Application/Application.h"

int main() {

	Application* app = Application::instance();
	app->setState(VRState());
};

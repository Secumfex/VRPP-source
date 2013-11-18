#include <iostream>
#include <string.h>

#include "Patterns/Singleton.h"
#include "Application/Application.h"

int main() {

	Application* app = Application::getInstance();
	app->setState(new VRState());

	ConcreteSingleton::getInstance()->helloWorld();

	while (true){

	}
	return 0;
};

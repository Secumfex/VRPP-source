#ifndef ACTIVATESTATELISTENER_H
#define ACTIVATESTATELISTENER_H

#include "Patterns/Listener.h"
#include "Application.h"

/*Activates the Application's current state*/
class ActivateStateListener : public Listener{
private:
	Application* application;
public:
	ActivateStateListener(Application* application);
	void update();
};

#endif

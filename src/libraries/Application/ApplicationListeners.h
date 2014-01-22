#ifndef APPLICATIONLISTENERS_H
#define APPLICATIONLISTENERS_H

/// This header contains various Application class related Listeners

#include "Patterns/Listener.h"
class Application;

/// base class for application listeners, has no functionality
class ApplicationListener : public Listener {
protected:	
	Application* application;
public:
	ApplicationListener(Application* application = 0);
	virtual void update();	
};

/// Activates the Application's current state
class ActivateStateListener : public ApplicationListener{
private:
	Application* application;
public:
	ActivateStateListener(Application* application);
	void update();
};

/// sets the Application State to whatever (think about buttons)
class SetStateListener : public ApplicationListener{
private:
	std::string state;
public:
	SetStateListener(Application* application, std::string state);
	void update();
};

/// terminates the Application (breaks the program cycle loop)
class TerminateApplicationListener : public ApplicationListener{
private:
	Application* application;
public:
	TerminateApplicationListener(Application* application);
	void update();
};

#endif

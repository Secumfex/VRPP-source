#ifndef APPLICATION_H
#define APPLICATION_H

#include "Patterns/StateMachine.h"
#include "Patterns/Singleton.h"

#include <string>

//Application is a Singleton State Machine (ApplicationContext) 
class Application : public Singleton<Application>, public StateMachine{
friend class Singleton<Application>;

private:
	string label;

public:
	void setState(State* state);
	Application(std::string label = "");
	void setLabel(std::string label);
	std::string getLabel();
};

#endif

#ifndef APPLICATION_H
#define APPLICATION_H

#include "ApplicationContext.h"
#include "Patterns/Singleton.h"

#include <string>

//Application is a Singleton State Machine (ApplicationContext) 
class Application : public Singleton<Application>, public ApplicationContext{
friend class Singleton<Application>;

private:
	string label;

public:
Application(std::string label = "");
	void setLabel(std::string label);
	std::string getLabel();
};

#endif

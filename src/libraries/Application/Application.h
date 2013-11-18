#ifndef APPLICATION_H
#define APPLICATION_H

#include "State.h"
#include "Patterns/Singleton.h"

class Application : public Singleton<Application>{

friend class Singleton<Application>;

private:
State state;
protected:
	Application();
public:
	void setState(State* to);
};

#endif

#ifndef APPLICATION_H
#define APPLICATION_H

#include "State.h"

class Application{
private:
State state;

public:
	void setState(State to);
};

#endif

#ifndef STATE_H
#define STATE_H

#include <string>

class State{	//a state of a context

protected:

private:
	std::string name;

public:
	std::string getName();
	virtual void activate();
};

#endif

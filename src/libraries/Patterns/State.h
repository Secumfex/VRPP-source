#ifndef STATE_H
#define STATE_H

#include <string>

class State{	//a state of a context

protected:

private:
	std::string name;

public:
	State(std::string name = "");
	std::string getName();
	void setName(std::string name);
	virtual void activate();
};

#endif

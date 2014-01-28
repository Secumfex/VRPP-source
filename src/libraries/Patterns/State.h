#ifndef STATE_H
#define STATE_H

#include <string>
#include "Subject.h"

class State : public Subject{	//a state of a context

protected:

private:
	std::string name;

public:
	virtual ~State(){};
	State(std::string name = "");
	std::string getName();
	void setName(std::string name);
	virtual void activate();
};

#endif

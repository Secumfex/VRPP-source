#ifndef LISTENER_H
#define LISTENER_H
#include <string>

using namespace std;

class Listener{
private:
	string name;

public:
	virtual ~Listener(){}			//!< Platzhalter, damit der Error verschwindet
	virtual void update() = 0;		//!< abstract method which must be defined by every concrete Listener class
	string getName();
	void setName(string name);
};

#endif

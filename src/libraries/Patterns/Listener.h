#ifndef LISTENER_H
#define LISTENER_H

class Listener{
public:
	virtual ~Listener(){}
	virtual void update() = 0;		//abstract method which must be defined by every concrete Listener class
};

#endif

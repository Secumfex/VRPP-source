#ifndef FRAMELISTENER_H
#define FRAMELISTENER_H

#include "Patterns/Listener.h"

class FrameListener : public Listener {
public:
	void update();		//abstract method which must be defined by every concrete Listener class
};

#endif /* FRAMELISTENER_H */
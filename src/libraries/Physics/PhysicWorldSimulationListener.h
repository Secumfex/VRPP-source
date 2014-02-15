#ifndef PHYSICWORLDSIMULATIONLISTENER_H_
#define PHYSICWORLDSIMULATIONLISTENER_H_

#include "Patterns/Listener.h"
class PhysicWorld;

class PhysicWorldSimulationListener : public Listener {

public:
	PhysicWorldSimulationListener();
	void update();

};


#endif /* PHYSICWORLDSIMULATIONLISTENER_H_ */

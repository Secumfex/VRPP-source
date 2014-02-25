#ifndef PHYSICWORLDSIMULATIONLISTENER_H_
#define PHYSICWORLDSIMULATIONLISTENER_H_

#include "Patterns/Listener.h"

class PhysicWorld;

class PhysicWorldSimulationListener : public Listener {

public:

	/** \brief listener
	 *
	 * currently not used
	 */
	PhysicWorldSimulationListener();

	/** \brief update
	 *
	 * executes the stepSimulation method for the physics world
	 */
	void update();

};


#endif /* PHYSICWORLDSIMULATIONLISTENER_H_ */

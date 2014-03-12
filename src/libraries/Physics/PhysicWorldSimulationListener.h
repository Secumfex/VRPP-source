#ifndef PHYSICWORLDSIMULATIONLISTENER_H_
#define PHYSICWORLDSIMULATIONLISTENER_H_

#include "Patterns/Listener.h"

class PhysicWorld;

class PhysicWorldSimulationListener : public Listener {
private:
	float* delta_time_source;	/**< fps, speed in which the physic simulation should run */
public:

	/** \brief listener constructor
	 *
	 * @param delta_time_source speed in which the physic simulation should run
	 */
	PhysicWorldSimulationListener(float* delta_time_source = 0);

	/** \brief update
	 *
	 * executes the stepSimulation method for the physics world
	 */
	void update();

};


#endif /* PHYSICWORLDSIMULATIONLISTENER_H_ */

#ifndef UPDATEPHYSICSCOMPONENTLISTENER_H
#define UPDATEPHYSICSCOMPONENTLISTENER_H

#include "Patterns/Listener.h"

class PhysicsComponent;

class UpdatePhysicsComponentListener : public Listener {
protected:
	PhysicsComponent* physicsComponent;		/**< pointer to the physics component of the VO */
public:

	/** \brief listener
	 *
	 * sets the physicComponent
	 */
	UpdatePhysicsComponentListener(PhysicsComponent* physicsComponent);

	/** \brief update
	 *
	 * updates the model matrix of the physicComponent
	 */
	void update();
};

#endif

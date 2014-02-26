#ifndef UPDATEPHYSICSCOMPONENTLISTENER_H
#define UPDATEPHYSICSCOMPONENTLISTENER_H

#include "Patterns/Listener.h"

class VirtualObject;

class UpdatePhysicsComponentListener : public Listener {

protected:

	VirtualObject* vo;

public:

	/** \brief listener
	 *
	 * sets the physicComponent
	 */
	UpdatePhysicsComponentListener(VirtualObject* vo);

	/** \brief update
	 *
	 * updates the model matrix of the physicComponent
	 */
	void update();
};

#endif

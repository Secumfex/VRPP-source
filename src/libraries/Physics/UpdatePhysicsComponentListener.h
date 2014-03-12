#ifndef UPDATEPHYSICSCOMPONENTLISTENER_H
#define UPDATEPHYSICSCOMPONENTLISTENER_H

#include "Patterns/Listener.h"

class VirtualObject;

class UpdatePhysicsComponentListener : public Listener {

protected:

	VirtualObject* vo;		/**< virtual object reference */

public:

	/** \brief listener constructor
	 *
	 * sets the physicComponent
	 * @param vo reference to virtual object from which this function is called
	 */
	UpdatePhysicsComponentListener(VirtualObject* vo);

	/** \brief update
	 *
	 * updates the model matrix of the physicComponent
	 */
	void update();
};

#endif

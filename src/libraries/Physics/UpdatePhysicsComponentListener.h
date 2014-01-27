#ifndef UPDATEPHYSICSCOMPONENTLISTENER_H
#define UPDATEPHYSICSCOMPONENTLISTENER_H

#include "Patterns/Listener.h"
class PhysicsComponent;

class UpdatePhysicsComponentListener : public Listener {
protected:
	PhysicsComponent* physicsComponent;
public:
	UpdatePhysicsComponentListener(PhysicsComponent* physicsComponent);
	void update();
};

#endif

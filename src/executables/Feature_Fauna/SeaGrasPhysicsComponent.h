/*
 * SeaGrasPhysicsComponent.h
 *
 *  Created on: 10.04.2014
 *      Author: Dirk Diggler
 */

#ifndef SEAGRASPHYSICSCOMPONENT_H_
#define SEAGRASPHYSICSCOMPONENT_H_

#include "Physics/PhysicsComponent.h"
#include "Visuals/VirtualObjectFactory.h"
#include <vector>

class SeaGrasPhysicsComponent {

	vector<VirtualObject*> vecCatMull;
	vector<btGeneric6DofSpringConstraint*> vecConstraints;

public:
	SeaGrasPhysicsComponent();
	virtual ~SeaGrasPhysicsComponent();
};

#endif /* SEAGRASPHYSICSCOMPONENT_H_ */

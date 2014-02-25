/*
 * Frustum.h
 *
 *  Created on: 25.02.2014
 *      Author: Dr.M
 */

#ifndef FRUSTUM_H_
#define FRUSTUM_H_

#include "IO/Camera.h"
#include "btBulletDynamicsCommon.h"

class Frustum {
public:
	Frustum();
	virtual ~Frustum();

	Camera *cam;
	btCollisionShape *frustum;
};

#endif /* FRUSTUM_H_ */

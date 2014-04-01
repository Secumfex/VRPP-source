#ifndef SEETANG_H_
#define SEETANG_H_
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include "btBulletDynamicsCommon.h"
#include "BulletDynamics\Dynamics\btRigidBody.h"
#include "Physics\PhysicsComponent.h"
#include "btBulletDynamicsCommon.h"




class Seetang {
private:


public:
	vector<VirtualObject*> mVOVec;
	float x;
	float y;
	float z;

	Seetang();
   // VirtualObject SetUpGroundTarget();
    VirtualObject SetUpFurtherTarget();

};

#endif /* SEETANG_H_ */

#ifndef SEETANG_H_
#define SEETANG_H_
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include "btBulletDynamicsCommon.h"
#include "BulletDynamics\Dynamics\btRigidBody.h"
#include "Physics\PhysicsComponent.h"
#include "btBulletDynamicsCommon.h"
#include "../libraries/Feature_Fauna/Seetang.h"
#include "BulletDynamics/Dynamics/btRigidBody.h"
#include "IO/IOManager.h"
#include "IO/PlayerCamera.h"
#include "Physics/UpdatePhysicsComponentListener.h"
#include "Physics/PhysicWorld.h"
#include "Physics/PhysicWorldSimulationListener.h"
#include "BulletDynamics/ConstraintSolver/btPoint2PointConstraint.h"
#include "BulletDynamics/ConstraintSolver/btGeneric6DofConstraint.h"




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

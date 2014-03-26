#ifndef SEETANG_H_
#define SEETANG_H_
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include "btBulletDynamicsCommon.h"
#include "BulletDynamics\Dynamics\btRigidBody.h"
#include "Physics\PhysicsComponent.h"
#include "btBulletDynamicsCommon.h"
#include "../Physics/CatmullRomeSpline.h"
#include "../IO/Camera.h"

class Seetang {
private:
	glm::mat4 mViewMatrix;
public:
	Seetang();
	btRigidBody* addSphere(float radius, float x, float y, float z, float mass);
	btRigidBody *rigidBody;
	vector<btRigidBody*> spheres;
	glm::mat4 getViewMatrix();
	void MVMultiplikation();
    btRigidBody* getRigidBody();

};

#endif /* SEETANG_H_ */

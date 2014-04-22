#include <iostream>
#include "Seetang.h"
using namespace std;

Seetang::Seetang() {

}

vector<btRigidBody*> rb_vec;
vector<btTransform> transform_vec;
vector<btGeneric6DofSpringConstraint*> constraint_vec_Input;
btGeneric6DofSpringConstraint* constraint_tmp_Input;
btTransform transform_tmp_Input;

//SetUpGroundTarget(50, 200, 50, 0, 0, 0, 0, 1);
VirtualObject* SetUpGroundTarget(float width, float height, float depth, float x, float y, float z, float mass, int collisionFlag) {
	VirtualObject* baseSeaGras = new VirtualObject(width, height, depth, x, y, z, mass, collisionFlag);
	/*	VirtualObject::VirtualObject(float width, float height, float depth, float x, float y, float z, float mass, int collisionFlag){
	 physicsComponent = new PhysicsComponent(width, height, depth, x, y, z, mass, collisionFlag);
	 physicsComponent->update(this);		*/

//TODO Das mesh drüber ziehen ?!
	baseSeaGras->addGraphicsComponent(new GraphicsComponent());

	float tmp_height = 20;	//Hilfsvariable zum erstellen der Rigidboys
	int iterator = 0;


	while (tmp_height < height-20) {
		//btScalar mass, btMotionState *motionState, btCollisionShape *collisionShape, const btVector3 &localInertia
		btCollisionShape* cShape = new btStaticPlaneShape(btVector3(0,1,0),0);
		btDefaultMotionState* ms = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,-4,5)));
		btRigidBody::btRigidBodyConstructionInfo rbCI(0,ms,cShape,btVector3(0,0,0));

		btRigidBody* rb_tmp = new btRigidBody(rbCI);
		//btRigidBody* rb_tmp = new btRigidBody(0, btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,tmp_height,0))), 0, btVector3(0, 0, 0));
		rb_tmp->applyForce(btVector3(10, 30, 0), btVector3(0, 0, 0));
		rb_tmp->setDamping(.1, .1);
		rb_tmp->setGravity((rb_tmp->getGravity()) + btVector3(0, 30, 0));
		rb_tmp->setFriction(btScalar(250));
		rb_tmp->setActivationState(DISABLE_DEACTIVATION);
		rb_vec.push_back(rb_tmp);


		transform_tmp_Input = btTransform::getIdentity();
		transform_tmp_Input.setOrigin(	btVector3(btScalar(0.), btScalar(tmp_height), btScalar(0.)));
		transform_vec.push_back(transform_tmp_Input);

		constraint_tmp_Input = new btGeneric6DofSpringConstraint( *rb_vec[iterator - 1], *rb_vec[iterator], transform_vec[iterator - 1], transform_vec[iterator], true);
		constraint_tmp_Input->setLinearUpperLimit(btVector3(0., 10., 0.));
		constraint_tmp_Input->setDamping(.1, .1);
		constraint_vec_Input.push_back(constraint_tmp_Input);

		PhysicWorld::getInstance()->dynamicsWorld->addRigidBody(rb_tmp);
		PhysicWorld::getInstance()->dynamicsWorld->addConstraint( constraint_vec_Input[iterator-1], true);

		tmp_height += 20;
		iterator ++;
	}

	return baseSeaGras;
}


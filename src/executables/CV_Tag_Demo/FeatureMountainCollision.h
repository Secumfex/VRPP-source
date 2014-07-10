/*
 * FeatureMountainCollision.h
 *
 *  Created on: 10.07.2014
 *      Author: Raphimulator
 */

#ifndef FEATUREMOUNTAINCOLLISION_H_
#define FEATUREMOUNTAINCOLLISION_H_

#include <Physics/PhysicsComponent.h>

namespace MountainCollision{

void makeSphereApproximationOfMountain(){
	PhysicsComponent* phynununu = new PhysicsComponent(8.35f, 3.343f, 5.636f, -19.96708f, 0.0f, 8);

	btRigidBody* rb = phynununu->addSphere(8.35f, 16.79f, 2.95f, -10.77737f, 0.0f);
	rb->setCollisionFlags(8);
	PhysicWorld::getInstance()->dynamicsWorld->addRigidBody(rb);

	rb = phynununu->addSphere(8.35f, 10.48937f, 2.26498f, -16.02432f, 0.0f);
	rb->setCollisionFlags(8);
	PhysicWorld::getInstance()->dynamicsWorld->addRigidBody(rb);

	rb = phynununu->addSphere(8.35f, 3.34283, 1.84027f, -18.776f, 0.0f);
	rb->setCollisionFlags(8);
	PhysicWorld::getInstance()->dynamicsWorld->addRigidBody(rb);

	rb = phynununu->addSphere(7.2395f, -3.67117, 1.80318f, -18.79019, 0.0f);
	rb->setCollisionFlags(8);
	PhysicWorld::getInstance()->dynamicsWorld->addRigidBody(rb);

	rb = phynununu->addSphere(7.2395f, 6.92295, 11.4187f, -19.41677, 0.0f);
	rb->setCollisionFlags(8);
	PhysicWorld::getInstance()->dynamicsWorld->addRigidBody(rb);

	rb = phynununu->addSphere(6.205f, 20.88744, 3.21339f, 5.55383, 0.0f);
	rb->setCollisionFlags(8);
	PhysicWorld::getInstance()->dynamicsWorld->addRigidBody(rb);

	rb = phynununu->addSphere(6.205f, 15.3509, 10.91024f, -13.28551, 0.0f);
	rb->setCollisionFlags(8);
	PhysicWorld::getInstance()->dynamicsWorld->addRigidBody(rb);

	rb = phynununu->addSphere(6.205f, 17.84353f, 0.716f, 15.79448f, 0.0f);
	rb->setCollisionFlags(8);
	PhysicWorld::getInstance()->dynamicsWorld->addRigidBody(rb);

	rb = phynununu->addSphere(6.205f, 19.06276f, 2.33225f, -2.02402f, 0.0f);
	rb->setCollisionFlags(8);
	PhysicWorld::getInstance()->dynamicsWorld->addRigidBody(rb);

	rb = phynununu->addSphere(4.5025, 12.63914f, 2.18755f, 24.45164f, 0.0f);
	rb->setCollisionFlags(8);
	PhysicWorld::getInstance()->dynamicsWorld->addRigidBody(rb);

	rb = phynununu->addSphere(4.5025, 8.12452f, 3.29704f, 30.02452f, 0.0f);
	rb->setCollisionFlags(8);
	PhysicWorld::getInstance()->dynamicsWorld->addRigidBody(rb);

	rb = phynununu->addSphere(4.5025, -6.19373f, 0.76336f, 22.7438f, 0.0f);
	rb->setCollisionFlags(8);
	PhysicWorld::getInstance()->dynamicsWorld->addRigidBody(rb);

	rb = phynununu->addSphere(4.5025, -11.23388f, 2.12242f, 20.02025f, 0.0f);
	rb->setCollisionFlags(8);
	PhysicWorld::getInstance()->dynamicsWorld->addRigidBody(rb);

	rb = phynununu->addSphere(4.5025, -14.25011f, 4.0926f, 17.12416f, 0.0f);
	rb->setCollisionFlags(8);
	PhysicWorld::getInstance()->dynamicsWorld->addRigidBody(rb);

	rb = phynununu->addSphere(4.5025, -18.57984f, 3.09726f, 10.83907f, 0.0f);
	rb->setCollisionFlags(8);
	PhysicWorld::getInstance()->dynamicsWorld->addRigidBody(rb);

	rb = phynununu->addSphere(3.574f, 3.27769f, 3.72963f, 33.9483f, 0.0f);
	rb->setCollisionFlags(8);
	PhysicWorld::getInstance()->dynamicsWorld->addRigidBody(rb);

	rb = phynununu->addSphere(3.574f, 14.38504f, 3.45126f, 20.73453f, 0.0f);
	rb->setCollisionFlags(8);
	PhysicWorld::getInstance()->dynamicsWorld->addRigidBody(rb);

	rb = phynununu->addSphere(3.574f, 16.65704f, 7.21576f, 20.03441f, 0.0f);
	rb->setCollisionFlags(8);
	PhysicWorld::getInstance()->dynamicsWorld->addRigidBody(rb);

	rb = phynununu->addSphere(3.574f, 8.95662f, 8.07886f, 28.91147f, 0.0f);
	rb->setCollisionFlags(8);
	PhysicWorld::getInstance()->dynamicsWorld->addRigidBody(rb);

	rb = phynununu->addSphere(3.574f, 2.08274f, 12.73818f, -15.12243f, 0.0f);
	rb->setCollisionFlags(8);
	PhysicWorld::getInstance()->dynamicsWorld->addRigidBody(rb);

	rb = phynununu->addSphere(3.574f, 9.16816f, 10.17976f, -13.902f, 0.0f);
	rb->setCollisionFlags(8);
	PhysicWorld::getInstance()->dynamicsWorld->addRigidBody(rb);

	rb = phynununu->addSphere(3.574f, -9.47944f, 1.64867f, -14.52347f, 0.0f);
	rb->setCollisionFlags(8);
	PhysicWorld::getInstance()->dynamicsWorld->addRigidBody(rb);

	rb = phynununu->addSphere(3.574f, -13.6495f, 0.37557f, -11.55486f, 0.0f);
	rb->setCollisionFlags(8);
	PhysicWorld::getInstance()->dynamicsWorld->addRigidBody(rb);

	rb = phynununu->addSphere(3.574f, -16.5181f, -0.31027f, -6.37127f, 0.0f);
	rb->setCollisionFlags(8);
	PhysicWorld::getInstance()->dynamicsWorld->addRigidBody(rb);

	rb = phynununu->addSphere(3.574f, -17.77361f, 0.47863f, -0.02873f, 0.0f);
	rb->setCollisionFlags(8);
	PhysicWorld::getInstance()->dynamicsWorld->addRigidBody(rb);

	rb = phynununu->addSphere(3.574f, -19.5747f, 2.91936f, 4.69996f, 0.0f);
	rb->setCollisionFlags(8);
	PhysicWorld::getInstance()->dynamicsWorld->addRigidBody(rb);

	rb = phynununu->addSphere(3.1965f, 6.59312f, 5.15599f, 31.65337f, 0.0f);
	rb->setCollisionFlags(8);
	PhysicWorld::getInstance()->dynamicsWorld->addRigidBody(rb);

	rb = phynununu->addSphere(3.1965f, 1.89864f, 0.90115f, 35.94381f, 0.0f);
	rb->setCollisionFlags(8);
	PhysicWorld::getInstance()->dynamicsWorld->addRigidBody(rb);

//	rb = phynununu->addSphere(0.5f, 7.65356f, 3.53054f, 12.64749f, 0.0f);
//	rb->setCollisionFlags(8);
//	PhysicWorld::getInstance()->dynamicsWorld->addRigidBody(rb);
//
//	rb = phynununu->addSphere(0.5f, 7.65356f, 3.63585f, 11.76353f, 0.0f);
//	rb->setCollisionFlags(8);
//	PhysicWorld::getInstance()->dynamicsWorld->addRigidBody(rb);
//
//	rb = phynununu->addSphere(0.5f, 7.65356f, 3.4016f, 11.44513f, 0.0f);
//	rb->setCollisionFlags(8);
//	PhysicWorld::getInstance()->dynamicsWorld->addRigidBody(rb);
//
//	rb = phynununu->addSphere(0.425f, 7.10831f, 3.4016f, 11.44513f, 0.0f);
//	rb->setCollisionFlags(8);
//	PhysicWorld::getInstance()->dynamicsWorld->addRigidBody(rb);





}

}


#endif /* FEATUREMOUNTAINCOLLISION_H_ */

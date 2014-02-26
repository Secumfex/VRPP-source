/*
 * Frustum.cpp
 *
 *  Created on: 25.02.2014
 *      Author: Dr.M
 */

#include "Visuals/Frustum.h"
#include "Visuals/RenderManager.h"

Frustum::Frustum() {

	setCamera(RenderManager::getInstance()->getCamera());
	makeRigidBody();
	setProjectionMatrix(40.0f, 1.0f, 0.1f, 100.f);

}

Frustum::Frustum(Camera *cam) {
	setCamera(cam);
	makeRigidBody();
	setProjectionMatrix(40.0f, 1.0f, 0.1f, 100.f);

}

Frustum::~Frustum() {
	// TODO Auto-generated destructor stub
}

void Frustum::setCamera(Camera *cam){
	mCam = cam;
}

void Frustum::makeRigidBody(){
	btTransform t;
	t.setIdentity();
	btMotionState* motion = new btDefaultMotionState(t);
	btConvexHullShape *shape = new btConvexHullShape();
	btRigidBody::btRigidBodyConstructionInfo info(0.0,motion,shape);
	mFrustumVolume = new btRigidBody(info);
}

void Frustum::setProjectionMatrix(float fovy, float aspect, float near, float far){

	mProjectionMatrix = glm::perspective(fovy, aspect, near, far);

	float fovx = fovy / aspect;

	float nfovy = (fovy * near) / far ;
	float nfovx = (fovx * near) / far ;


	btVector3 *n_d_l = new btVector3(-nfovx/2, -nfovy/2, near);
	btVector3 *n_d_r = new btVector3(nfovx/2, -nfovy/2, near);
	btVector3 *n_u_l = new btVector3(-nfovx/2, nfovy/2, near);
	btVector3 *n_u_r = new btVector3(nfovx/2, nfovy/2, near);
	btVector3 *f_d_l = new btVector3(-fovx/2, -fovy/2, far);
	btVector3 *f_d_r = new btVector3(fovx/2, -fovy/2, far);
	btVector3 *f_u_l = new btVector3(-fovx/2, fovy/2, far);
	btVector3 *f_u_r = new btVector3(fovx/2, fovy/2, far);


	btConvexHullShape *shape = new btConvexHullShape();
	shape->addPoint(*n_d_l,false);
	shape->addPoint(*n_d_r,false);
	shape->addPoint(*n_u_l,false);
	shape->addPoint(*n_u_r,false);
	shape->addPoint(*f_d_l,false);
	shape->addPoint(*f_d_r,false);
	shape->addPoint(*f_u_l,false);
	shape->addPoint(*f_u_r,false);

	mFrustumVolume->setCollisionShape(shape);
	mFrustumVolume->setCollisionFlags(4);




}

bool Frustum::inFrustum(GraphicsComponent *gc){


	glm::vec3 temp = gc->getBoundingBox_Max() - gc->getPivot();
	btVector3 *halfExtends = new btVector3(temp.x, temp.y, temp.z);

	btBoxShape *box = new btBoxShape(*halfExtends);
	RenderManager *rm = RenderManager::getInstance();

	btTransform t;

	glm:: mat4 glmmatt = rm->getCurrentVO()->getPhysicsComponent()->getModelMatrix();
	float *mat = glm::value_ptr(glmmatt);

	t.setFromOpenGLMatrix(mat);

	btMotionState* motion = new btDefaultMotionState(t);
	btRigidBody::btRigidBodyConstructionInfo info(0.0,motion,box);
	btRigidBody *tempBox = new btRigidBody(info);

	mFrustumVolume->checkCollideWith(tempBox);

	return true;
}

glm::mat4 Frustum::getProjectionMatrix(){
	return mProjectionMatrix;
}

void Frustum::updateModelMatrix(){
	glm::mat4 matrix = glm::inverse(mCam->getViewMatrix());
	btTransform *t;
	float *mat = glm::value_ptr(matrix);
	t->setFromOpenGLMatrix(mat);
	mFrustumVolume->setWorldTransform(*t);
}

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
#include "Physics/PhysicsComponent.h"
#include "Visuals/GraphicsComponent.h"
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_inverse.hpp>

class RenderManager;

class Frustum {
public:
	/** \brief default constructor
	 *
	 */
	Frustum();

	/** \brief constructor
	 *
	 * @param cam
	 */
	Frustum(Camera *cam);

	/** \brief destructor
	 *
	 */
	virtual ~Frustum();

	/** \brief return wheather or not a GC is (partially) inside of this frustum
	 *
	 * @param gc graphic component reference
	 * @return true or false
	 */
	bool inFrustum(GraphicsComponent *gc);

	/** \brief setter
	 *
	 * sets the perspective matrix
	 * @param fovy,aspect,near,far
	 */
	void setPerspectiveMatrix(GLfloat fovy, GLfloat aspect, GLfloat near, GLfloat far);

	/** \brief getter
	 *
	 * @return the perspective matrix
	 */
	glm::mat4 getPerspectiveMatrix();

	/** \brief updates the model matrix of the frustum from the camera
	 *
	 */
	void updateModelMatrix();

	/** \brief setter
	 *
	 * sets a camera, the frustum takes it physical appearance from
	 * @param cam
	 */
	void setCamera(Camera *cam);

protected:

	Camera *mCam;					/**< !docu pls! */
	btGhostObject *mFrustumVolume;	/**< !docu pls! */
	glm::mat4 mPerspectiveMatrix;	/**< !docu pls! */
};

#endif /* FRUSTUM_H_ */

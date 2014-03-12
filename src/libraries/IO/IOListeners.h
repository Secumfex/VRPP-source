#ifndef IOLISTENERS_H
#define IOLISTENERS_H

#include "Patterns/Listener.h"
#include "IOManager.h"
#include "Camera.h"

/** \brief Listener which calls Camera::updatePosition(float d_t) on every update
 *
 */
class UpdateCameraPositionListener : public Listener{
private:
	Camera* cam;				/**< !docu pls! */
	float* delta_time_source;	/**< !docu pls! */
public:
	/** \brief listener constructor
	 *
	* @param cam : Camera Opject supposed to update
	* @param delta_time_source : a pointer to a float variable (optional)
	*/
	UpdateCameraPositionListener(Camera* cam, float* delta_time_source = 0);

	/** \brief update
	 *
	 * updates the camera position
	 */
	void update();
};

/** \brief Listener which calls IOManager::computeFrameTimeDifference() on every update
 *
 */
class ComputeFrameTimeListener : public Listener{
public:

	/** \brief listener constructor
	 *
	 */
	ComputeFrameTimeListener();

	/** \brief update
	 *
	 * updates the frame time
	 */
	void update();
};

#endif

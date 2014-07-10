#ifndef OCULUSCAMERA_H_
#define OCULUSCAMERA_H_

#include <IO/Camera.h>
#include <IO/Oculus.h>

/** @brief an Oculus enabled Camera.
 *	an Oculus Camera is a derived Camera which will rotate it's view matrix with
 *	the Oculus' orientation before passing it on */
class OculusCamera: public Camera {
protected:
	Oculus* oculus;		/**< Oculus Object */
	glm::mat4 accumulatedViewMatrix;	/**< the accumulated view matrix which holds the base view matrix multiplied with the Oculus orientation quaternion */

	OVR::Util::Render::StereoEye eye;	/**< the eye for which this camera is currently set */
public:
	OculusCamera(Oculus* oculus);
	virtual ~OculusCamera();

	glm::mat4 getViewMatrix(); /**< returns the accumulated view matrix */
	glm::mat4* getViewMatrixPointer() /**< returns the accumulated view matrix pointer */;

	void setEye(OVR::Util::Render::StereoEye eye);
	OVR::Util::Render::StereoEye getEye();
};

#endif

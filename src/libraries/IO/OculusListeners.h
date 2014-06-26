#ifndef OCULUSLISTENERS_H_
#define OCULUSLISTENERS_H_

#include <Patterns/Listener.h>
#include <IO/Oculus.h>
#include <IO/OculusCamera.h>

/// Listener which will set the view port for an eye.
/** Oculus' StereoConfig will be queried to read display settings and render the scene in the corresponding viewport of that eye ( i.e. half the screen )*/
class SetStereoViewportListener: public Listener {
private:
	Oculus* oculus;
	OVR::Util::Render::StereoEye eye;
public:
	SetStereoViewportListener(Oculus* oculus, OVR::Util::Render::StereoEye eye);
	void update();
};

/// Listener which will set the oculus perspective matrix.
/** Oculus' StereoConfig will be queried to read display settings and set the corresponding perspective matrix of that eye ( i.e. with a tiny offset )*/
class SetStereoPerspectiveListener: public Listener {
private:
	Oculus* oculus;
	OVR::Util::Render::StereoEye eye;
public:
	SetStereoPerspectiveListener(Oculus* oculus, OVR::Util::Render::StereoEye eye);
	void update();
};

/// Listener which will offset the oculus view matrix.
/** Oculus' StereoConfig will be queried to read display settings and set the corresponding perspective matrix of that eye ( i.e. with a tiny offset )*/
class SetOculusCameraEyeListener: public Listener {
private:
	OculusCamera* cam;
	OVR::Util::Render::StereoEye eye;
public:
	SetOculusCameraEyeListener(OculusCamera* cam, OVR::Util::Render::StereoEye eye);
	void update();
};

#endif /* OCULUSLISTENERS_H_ */

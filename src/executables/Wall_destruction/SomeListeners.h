#include "Patterns/Listener.h"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <cmath>

/// Listener which changes the ClearColor by a tiny bit on every update
class AnimateClearColorListener : public Listener{
private:
	float t;
public:
	AnimateClearColorListener();
	void update();
};

#include "Visuals/RenderManager.h"

/// Listener which renders a frame by using current Instance pointers of RenderManager
class AlternativeRenderloopListener : public Listener{
private:
	RenderManager* rm;
	RenderQueue* currentRenderQueue;
	list<VirtualObject* > voList;
	Shader* currentShader;
	vector<GraphicsComponent* > currentGCs;
public:
	AlternativeRenderloopListener();
	
	void update();
};

/// Listener which sets the Phong_Test Shader as the RenderManagers current Shader
class SetAlternativeDefaultRenderManagerPointersListener : public Listener{
private:
	RenderManager* rm;
public:
	SetAlternativeDefaultRenderManagerPointersListener();
	void update();
};

/// Listener which sets the glClearColor
class SetClearColorListener : public Listener {
private:
	float r, g, b, a;
public:
	SetClearColorListener(float r = 0.0, float g = 0.0, float b = 0.0, float a = 1.0);
	void update();
};

/// Listener which rotates the Model Matrix by a tiny bit on every update
class AnimateRotatingModelMatrixListener : public Listener{
private:
	VirtualObject* vo;
	float angle;
public:
	AnimateRotatingModelMatrixListener(VirtualObject* vo);
	void update();
};

/// Listener which moves the Model Matrix on a sinus curve by a tiny bit on every update
class AnimateSinusModelMatrixListener : public Listener{
private:
	VirtualObject* vo;
	float old_sinus;
	float t;
public:
	AnimateSinusModelMatrixListener(VirtualObject* vo);
	void update();
};

// Listener which sets the direction of the given Camera Object
class SetCameraDirectionListener : public Listener {
private:
	Camera* 	cam;
	glm::vec3 	direction;
public:
	SetCameraDirectionListener(Camera* cam, glm::vec3 direction);
	void update();
};

//Listener which turns the LookAt-Position of the given Camera Object
class TurnCameraListener : public Listener {
private:
	Camera* 	cam;
	float theta; // inlcination step
	float phi;   // rotation step
public:
	TurnCameraListener(Camera* cam, float phi, float theta);
	void update();
};

#include "Physics/PhysicWorld.h"
//Listener which starts the ray-picking test
class PickRayListener : public Listener {
private:
	Camera* cam;
	PhysicWorld* phWorld;

public:
	PickRayListener(Camera* cam);
	void update();
};


#include "Application/ApplicationStates.h"
/// Listener which shoots a sphere out of the camera
class ShootSphereListener : public Listener {
private:
	Camera* cam;
	VRState* state;
public:
	ShootSphereListener(Camera* cam, VRState* state);
	void update();
};

/// Listener which applies an impulse to a rigid body in direction of the provided cam
class ApplyForceOnSelectedPhysicsComponentInCameraViewDirectionListener : public Listener {
private:
	SelectionHandler* selectionHandler;
	Camera* cam;
	float strength;
public:
	ApplyForceOnSelectedPhysicsComponentInCameraViewDirectionListener(SelectionHandler* selectionHandler, Camera* cam, float strength = 100.0f);
	void update();
};

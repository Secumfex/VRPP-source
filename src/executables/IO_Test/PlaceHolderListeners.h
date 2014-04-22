#include "Patterns/Listener.h"
#include "IO/Kinect2.h"
/*
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <cmath>

#include "Visuals/RenderManager.h"
#include "Visuals/Shader.h"
#include "IO/SelectionHandler.h"
#include "IO/PlayerCamera.h"
*/






/// Listener which renders a frame by using current Instance pointers of RenderManager
class RenderloopPlaceHolderListener : public Listener{
private:
	RenderManager* rm;
	RenderQueue* currentRenderQueue;
	list<VirtualObject* > voList;
	Shader* currentShader;
	vector<GraphicsComponent* > currentGCs;
public:
	RenderloopPlaceHolderListener();
	void update();
};

/// Listener which sets the Phont_Test Shader as the RenderManagers current Shader
class SetDefaultShaderListener : public Listener{
private:
	RenderManager* rm;
	Shader* shader;
public:
	SetDefaultShaderListener(Shader* shader);
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



/// Listener which sets the direction of the given Camera Object
class TurnCameraListener : public Listener {
private:
	Camera* 	cam;
	float delta_theta; // inlcination step
	float delta_phi;   // rotation step
public:
	TurnCameraListener(Camera* cam, float delta_phi, float delta_theta);
	void update();
};

/// Listener which sets the Position of the given Camera Object
class SetCameraPositionListener : public Listener {
private:
	Camera* 	cam;
	glm::vec3 position;
public:
	SetCameraPositionListener(Camera* cam, glm::vec3 position);
	void update();
};

class ApplyForceOnCameraListener : public Listener {
private:
	Kinect* kinect;
	PlayerCamera* cam;
	float* strength;
public:
	ApplyForceOnCameraListener(PlayerCamera* cam,Kinect* kinect, float* strength);
	void update();
};

class ApplyForceOnSelectedPhysicsComponentInCameraViewDirectionListener : public Listener {
private:
	SelectionHandler* selectionHandler;
	Camera* cam;
	float strength;
public:
	ApplyForceOnSelectedPhysicsComponentInCameraViewDirectionListener(SelectionHandler* selectionHandler, Camera* cam, float strength = 100.0f);
	void update();
};

/// Listener which updates the VirtualObject Modelmatrix by reading the PhysicsComponent Modelmatrix
class UpdateVirtualObjectModelMatrixListener : public Listener{
private:
	VirtualObject* vo;
public:
	UpdateVirtualObjectModelMatrixListener(VirtualObject* vo);
	void update();
};

class btRigidBody; class btVector3;

class ApplyLinearImpulseOnRigidBody : public Listener{
private:
	btRigidBody* rigidBody;
	glm::vec3 force;
public:
	ApplyLinearImpulseOnRigidBody(btRigidBody* rigidBody, glm::vec3 force);
	void update();
};

class SwimCam : public PlayerCamera
{
public:
	void updatePosition(float deltaTime);
};
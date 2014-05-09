#include "Patterns/Listener.h"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <cmath>

#include "Visuals/RenderManager.h"
#include "Visuals/Shader.h"
/// Listener which changes the ClearColor by a tiny bit on every update
class AnimateClearColorListener : public Listener{
private:
	float t;
	float* delta_time_source;
public:
	AnimateClearColorListener(float* delta_time_source = 0);
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

/// Listener which updates the VirtualObject Modelmatrix by reading the PhysicsComponent Modelmatrix
class UpdateVirtualObjectModelMatrixListener : public Listener{
private:
	VirtualObject* vo;
public:
	UpdateVirtualObjectModelMatrixListener(VirtualObject* vo);
	void update();
};

/// Listener which updates the PhysicsWorld on every update
class UpdatePhysicsWorldListener : public Listener {
private:
public:
	UpdatePhysicsWorldListener();
	void update();
};


/// Listener which sets the direction of the given Camera Object
class SetCameraDirectionListener : public Listener {
private:
	Camera* 	cam;
	glm::vec3 	direction;
public:
	SetCameraDirectionListener(Camera* cam, glm::vec3 direction);
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

#include "Application/ApplicationStates.h"
/// Listener which creates a Virtual Object at the provided position in the provided state
class CreateVirtualObjectListener : public Listener {
private:
	ApplicationState* state;
	glm::vec3 	position;
	std::string path;
	float random_offset;
	VirtualObjectFactory::BodyType bodyType;
	float mass;
public:
	CreateVirtualObjectListener(string path, glm::vec3 position, ApplicationState* state, float random_offset = 0.0f, VirtualObjectFactory::BodyType bodyType= VirtualObjectFactory::OTHER, float mass = 2.0f);
	void update();
};

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

class ApplyLinearImpulseOnRigidBody : public Listener{
private:
	btRigidBody* rigidBody;
	glm::vec3 force;
public:
	ApplyLinearImpulseOnRigidBody(btRigidBody* rigidBody, glm::vec3 force);
	void update();
};

/// listener to upload a custom Uniform Vec3
class UploadUniformVOListener : public Listener {
private:
	VirtualObject* vo;
	std::string uniform_name;
public:
	UploadUniformVOListener(std::string name = std::string("UNIFORMUPLOADLISTENER"), VirtualObject* vo=0, std::string uniform_name = "custom_uniform");
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

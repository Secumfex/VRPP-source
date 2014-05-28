#include <GL/glew.h>
#include <glm/glm.hpp>
#include <cmath>
#include <stdlib.h>
#include <time.h>

#include "Patterns/Listener.h"
#include "Visuals/RenderManager.h"
#include "IO/PlayerCamera.h"
#include "Application/ApplicationStates.h"
#include "Physics/PhysicWorld.h"
#include "Physics/UpdatePhysicsComponentListener.h"

// Listener which renders a frame by using current Instance pointers of RenderManager
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

// Listener which sets the Phong_Test Shader as the RenderManagers current Shader
class SetAlternativeDefaultRenderManagerPointersListener : public Listener{
private:
	RenderManager* rm;
public:
	SetAlternativeDefaultRenderManagerPointersListener();
	void update();
};

// Listener which sets custom Shaders
class SetCurrentShaderListener : public Listener{
private:
	RenderManager* rm;
	Shader* shader;
public:
	SetCurrentShaderListener(Shader* shader);
	void update();
};

// Listener which sets the glClearColor
class SetClearColorListener : public Listener {
private:
	float r, g, b, a;
public:
	SetClearColorListener(float r = 0.0, float g = 0.0, float b = 0.0, float a = 1.0);
	void update();
};

// Listener which rotates the Model Matrix
/* ... and opens the treasure chest as well ... */
class AnimateRotatingModelMatrixListener : public Listener{
private:
	VirtualObject* vo;
	float angle;
public:
	AnimateRotatingModelMatrixListener(VirtualObject* vo);
	void update();
};

// my Listener for animate a GraphicComponent (not used)
class AnimateGraphicComponentListener : public Listener{
private:
    GraphicsComponent* gc;
    VirtualObject* vo;
    float angle;
public:
    AnimateGraphicComponentListener(GraphicsComponent* gc, VirtualObject* vo);
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

// Listener which turns the LookAt-Position of the given Camera Object
class TurnCameraListener : public Listener {
private:
	Camera* 	cam;
	float theta; // inlcination step
	float phi;   // rotation step
public:
	TurnCameraListener(Camera* cam, float phi, float theta);
	void update();
};

// Listener which moves the PlayerCamera
/* it also 'calculates the collision between the camera and other objects */
class MovePlayerCameraListener : public Listener {
private:
    Camera* pcam;
    float x_pos;
    float y_pos;
    float z_pos;
    VirtualObject* vo_1;
    VirtualObject* vo_2;
    btRigidBody* camBody;
public:
    MovePlayerCameraListener(Camera* pcam, float x_pos, float y_pos, float z_pos, VirtualObject* vo_1, VirtualObject* vo_2, btRigidBody* camBody);
    void update();
};

// Listener which creates a Virtual Object at the provided position in the provided state
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

// Sets the current FrameBufferObject
class SetFrameBufferObjectListener : public Listener {
private:
	FrameBufferObject* fbo;
public:
	SetFrameBufferObjectListener( FrameBufferObject* fbo);
	void update();
};

// Unbinds the current FrameBufferObject
class UnbindFrameBufferObjectListener : public Listener {
public:
	UnbindFrameBufferObjectListener();
	void update();
};

// Renders a single GraphicsComponent
class RenderGraphicsComponentListener : public Listener{
protected:
	GraphicsComponent* gc;
public:
	RenderGraphicsComponentListener(GraphicsComponent* gc = 0);
	virtual void update();
};

// Renders a Screen Filling Triangle
class RenderScreenFillingTriangleListener : public RenderGraphicsComponentListener{
public:
	RenderScreenFillingTriangleListener();
	void update();
};

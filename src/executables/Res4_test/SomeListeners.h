#include "Patterns/Listener.h"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <cmath>

#include "Visuals/RenderManager.h"
#include "IO/PlayerCamera.h"

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

/// Listener which sets the Phont_Test Shader as the RenderManagers current Shader
class SetCurrentShaderListener : public Listener{
private:
	RenderManager* rm;
	Shader* shader;
public:
	SetCurrentShaderListener(Shader* shader);
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

/// my Listener for animate a GraphicComponent
class AnimateGraphicComponentListener : public Listener{
private:
    GraphicsComponent* gc;
    float angle;
public:
    AnimateGraphicComponentListener(GraphicsComponent* gc);
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

// Listener which updates the PhysicsWorld on every update
class UpdatePhysicsWorldListener : public Listener {
private:
public:
	UpdatePhysicsWorldListener();
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

//Listener which moves the PlayerCamera
class MovePlayerCameraListener : public Listener {
private:
    Camera* pcam;
    float x_pos;
    float y_pos;
    float z_pos;
public:
    MovePlayerCameraListener(Camera* pcam, float x_pos, float y_pos, float z_pos);
    void update();
};

#include "Application/ApplicationStates.h"
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

/// Sets the current FrameBufferObject
class SetFrameBufferObjectListener : public Listener {
private:
	FrameBufferObject* fbo;
public:
	SetFrameBufferObjectListener( FrameBufferObject* fbo);
	void update();
};


/// Unbinds the current FrameBufferObject
class UnbindFrameBufferObjectListener : public Listener {
public:
	UnbindFrameBufferObjectListener();
	void update();
};


/// Listener which uses an FBO as Render Target, activates certain camera, and ignores the water_object
class ReflectionMapRenderPass : public Listener{
public:
	RenderManager* rm;
	RenderQueue* currentRenderQueue;
	list<VirtualObject* > voList;
	Shader* currentShader;
	vector<GraphicsComponent* > currentGCs;
    
	/*außerdem*/
	FrameBufferObject* fbo; // reflectionmap target

    
	ReflectionMapRenderPass(FrameBufferObject* fbo);
	void update();
};

/// Renders a single GraphicsComponent
class RenderGraphicsComponentListener : public Listener{
protected:
	GraphicsComponent* gc;
public:
	RenderGraphicsComponentListener(GraphicsComponent* gc = 0);
	virtual void update();
};


/// Renders a Screen Filling Triangle
class RenderScreenFillingTriangleListener : public RenderGraphicsComponentListener{
public:
	RenderScreenFillingTriangleListener();
	void update();
};


#include "Patterns/Listener.h"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <cmath>

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

// Listener which prints the current configuration of the given Camera Object
class PrintCameraStatusListener : public Listener {
private:
	Camera* cam;
public:
	PrintCameraStatusListener(Camera* cam);
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

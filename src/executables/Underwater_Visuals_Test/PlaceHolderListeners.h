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

/// Listener which renders a frame by using current Instance pointers of RenderManager
class RenderloopPlaceHolderListener : public Listener{
private:
	RenderManager* rm;
	RenderQueue* currentRenderQueue;
	list<VirtualObject* > voList;
	Shader* currentShader;
	vector<GraphicsComponent* > currentGCs;

public:
	VirtualObject* water_object;
	RenderloopPlaceHolderListener(VirtualObject* water_object = 0);
	void update();
};

class ReflectionMapRenderPass : public Listener{
public:
	RenderManager* rm;
	RenderQueue* currentRenderQueue;
	list<VirtualObject* > voList;
	Shader* currentShader;
	vector<GraphicsComponent* > currentGCs;

	/*außerdem*/
	FrameBufferObject* fbo; // reflectionmap target
	Camera* reflectedCamera;	// mirrored Camera
	VirtualObject* water_object;

	ReflectionMapRenderPass(FrameBufferObject* fbo, Camera* reflectedCam, VirtualObject* water_object);
	void update();
};

class RenderVirtualObjectWithShaderListener : public Listener{
private: 
	VirtualObject* vo;
	Shader* shader;
public:
	RenderVirtualObjectWithShaderListener(VirtualObject* vo, Shader* shader);
	void update();
};

class RenderWaterObjectWithShaderAndReflectionMapListener : public Listener{
private: 
	VirtualObject* vo;
	Shader* shader;
	FrameBufferObject* fbo; // reflectionmap target
public:
	RenderWaterObjectWithShaderAndReflectionMapListener(VirtualObject* vo, Shader* shader, FrameBufferObject* fbo);
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

/// listener on above or under water
class UnderOrAboveWaterListener : public Listener{
private:
	Camera* cam;
	bool underwater;
	float sea_level_y;
	Listener* EnterWaterListener;
	Listener* ExitWaterListener;
public:
	UnderOrAboveWaterListener(Camera* cam, float sea_level_y = 0.0f, Listener* EnterWaterListener = 0, Listener* ExitWaterListener = 0);
	void update();
};

class RecompileAndSetShaderListener : public Listener{
private:
	std::string vertex_shader;
	std::string fragment_shader;
public:
	RecompileAndSetShaderListener(std::string vertex_shader, std::string fragment_shader);
	void update();
};

class UpdateReflectedCameraPositionListener : public Listener{
private:
	Camera* cam_source;
	Camera* cam_target;
	float* water_height;
public:
	UpdateReflectedCameraPositionListener(Camera* cam, Camera* cam_target, float* water_height);
	UpdateReflectedCameraPositionListener(Camera* cam, Camera* cam_target, float water_height);
	void update();
};
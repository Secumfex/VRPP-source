#include "Patterns/Listener.h"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <cmath>

#include "Visuals/RenderManager.h"
#include "Visuals/VirtualObjectFactory.h"
#include "Visuals/Shader.h"
#include "ParticleSystem.h"
#include "HUDSystem.h"

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
	Camera* reflectedCamera;	// mirrored Camera
	VirtualObject* water_object;

	ReflectionMapRenderPass(FrameBufferObject* fbo, Camera* reflectedCam, VirtualObject* water_object);
	void update();
};


/// Listener which uses an FBO as Render Target and renders volumetric godrays
class GodRaysRenderPass : public Listener{
public:
	RenderManager* rm;
	RenderQueue* currentRenderQueue;
	list<VirtualObject* > voList;
	Shader* currentShader;
	vector<GraphicsComponent* > currentGCs;

	/*außerdem*/
	FrameBufferObject* fbo; // reflectionmap target

	GodRaysRenderPass(FrameBufferObject* fbo);
	void update();
};


/// Listener which uses an FBO as Render Target and renders volumetric godrays
class ParticlesRenderPass : public Listener{
public:
	RenderManager* rm;

	FrameBufferObject* fbo; // particles target
	ParticleSystem* particleSystem;
	GraphicsComponent* particleGC;
	GLint vao;

	ParticlesRenderPass(FrameBufferObject* fbo, ParticleSystem* particleSystem, GLint vao);
	void update();
};

/// Listener for rendering HUD elements
class HUDAirRenderPass : public Listener{
public:
	RenderManager* rm;

	FrameBufferObject* fbo;
	HUDSystem* hudSystem;
	GLint vao;

	HUDAirRenderPass(FrameBufferObject* fbo, HUDSystem* hudSystem, GLint vao);
	void update();
};

/// Listener for rendering HUD elements
class StaticHUDElementRenderPass : public Listener{
public:
	RenderManager* rm;

	FrameBufferObject* fbo;
	HUDSystem* hudSystem;
	GLint vao;

	StaticHUDElementRenderPass(FrameBufferObject* fbo, HUDSystem* hudSystem, GLint vao);
	void update();
};

/// Listener for rendering HUD elements
class HUDMarkerRenderPass : public Listener{
public:
	RenderManager* rm;

	FrameBufferObject* fbo;
	HUDSystem* hudSystem;
	GLint vao;

	HUDMarkerRenderPass(FrameBufferObject* fbo, HUDSystem* hudSystem, GLint vao);
	void update();
};

/// Listener which uses an FBO as Render Target and ignores the water_object
class RefractionMapRenderPass : public Listener{
public:
	RenderManager* rm;
	RenderQueue* currentRenderQueue;
	list<VirtualObject* > voList;
	Shader* currentShader;
	vector<GraphicsComponent* > currentGCs;

	/*außerdem*/
	FrameBufferObject* fbo; // reflectionmap target
	VirtualObject* water_object;

	RefractionMapRenderPass(FrameBufferObject* fbo, VirtualObject* water_object);
	void update();
};


/// Renders a single VirtualObject with a certain shader
class RenderVirtualObjectWithShaderListener : public Listener{
private: 
	VirtualObject* vo;
	Shader* shader;
public:
	RenderVirtualObjectWithShaderListener(VirtualObject* vo, Shader* shader);
	void update();
};


/// Renders a single Virtual Object
class RenderVirtualObjectListener : public Listener{
private: 
	VirtualObject* vo;
public:
	RenderVirtualObjectListener(VirtualObject* vo);
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


/// Renders the water object
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
	glm::vec3* clearColorVec3;
	glm::vec4* clearColorVec4;
	float a;
public:
	SetClearColorListener( float r = 0.0, float g = 0.0, float b = 0.0, float a = 1.0 );
	SetClearColorListener( glm::vec3* clearColor, float a = 1.0 );
	SetClearColorListener( glm::vec4* clearColor );
	void update();
};


/// Listener which calls a certain Listener when camera enters or exits the water
class UnderOrAboveWaterListener : public Listener{
private:
	Camera* cam;
	bool underwater;
	float* sea_level_y;
	Listener* EnterWaterListener;
	Listener* ExitWaterListener;
public:
	UnderOrAboveWaterListener(Camera* cam, float* sea_level_y = new float( 0.0f ), Listener* EnterWaterListener = 0, Listener* ExitWaterListener = 0);
	void update();
};


/// Compiles a shader and sets it as the current Shader
class RecompileAndSetShaderListener : public Listener{
private:
	std::string vertex_shader;
	std::string fragment_shader;
public:
	RecompileAndSetShaderListener(std::string vertex_shader, std::string fragment_shader);
	void update();
};


/// Updates a target camera to the reflected position and view direction of a source camera, given a certain waterheight
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


/// Uploads a sinus value
class UploadUniformSinusWaveListener : public Listener{
private:
	float* t;
	float frequency;
	float phase;
	std::string uniform_name;
public:
	UploadUniformSinusWaveListener(std::string name, float* t, float frequency, float phase, std::string uniform_name);
	UploadUniformSinusWaveListener(std::string name, float t, float frequency, float phase, std::string uniform_name);
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


class UpdateParticleSystemListener : public Listener {
private:
	ParticleSystem* particleSystem;
	float* t;
public:
	UpdateParticleSystemListener(ParticleSystem* particleSystem, float* t);
	void update();
};

class UpdateHUDSystemListener : public Listener {
private:
	HUDSystem* hudSystem;
	float* t;
public:
	UpdateHUDSystemListener(HUDSystem* hudSystem, float* t);
	void update();
};

static void createSquare();


/// listener to upload a Float to keep the air left in sight
#include "IO/IOManager.h"
#include "Visuals/RenderManager.h"
class UploadUniformAirListener : public Listener {
private:
	float airLeft, maxAir;
	glm::vec3* camPosition;
	float* windowTime;
	std::string uniform_name;
	float timeUnderWater, startTime, timeElapsed;
public:
	UploadUniformAirListener(std::string name = std::string("UNIFORMUPLOADLISTENER"), std::string uniform_name = "custom_uniform", float maxAir = 120.0);
	void update();
};

/// listener to upload a Float to keep the depth left in sight
#include "IO/IOManager.h"
#include "Visuals/RenderManager.h"
class UploadUniformDepthListener : public Listener {
private:
	float uniformDepth;
	glm::vec3 * camPosition;
	std::string uniform_name;
public:
	UploadUniformDepthListener(glm::vec3* camPosition, std::string name = std::string("UNIFORMUPLOADLISTENER"), std::string uniform_name = "custom_uniform");
	void update();
};



#include "Patterns/Listener.h"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <cmath>

#include "Visuals/RenderManager.h"
<<<<<<< HEAD
=======
#include "Visuals/VirtualObjectFactory.h"
>>>>>>> master
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

<<<<<<< HEAD
=======

>>>>>>> master
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

<<<<<<< HEAD
=======

class GodRaysRenderPass : public Listener{
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

	GodRaysRenderPass(FrameBufferObject* fbo);
	void update();
};


>>>>>>> master
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

<<<<<<< HEAD
=======

>>>>>>> master
class RenderVirtualObjectWithShaderListener : public Listener{
private: 
	VirtualObject* vo;
	Shader* shader;
public:
	RenderVirtualObjectWithShaderListener(VirtualObject* vo, Shader* shader);
	void update();
};

<<<<<<< HEAD
=======

>>>>>>> master
class RenderVirtualObjectListener : public Listener{
private: 
	VirtualObject* vo;
public:
	RenderVirtualObjectListener(VirtualObject* vo);
	void update();
};

<<<<<<< HEAD
=======

class RenderGraphicsComponentListener : public Listener{
protected: 
	GraphicsComponent* gc;
public:
	RenderGraphicsComponentListener(GraphicsComponent* gc = 0);
	virtual void update();
};

class RenderScreenFillingTriangleListener : public RenderGraphicsComponentListener{
public:
	RenderScreenFillingTriangleListener();
	void update();
};

>>>>>>> master
class RenderWaterObjectWithShaderAndReflectionMapListener : public Listener{
private: 
	VirtualObject* vo;
	Shader* shader;
	FrameBufferObject* fbo; // reflectionmap target
public:
	RenderWaterObjectWithShaderAndReflectionMapListener(VirtualObject* vo, Shader* shader, FrameBufferObject* fbo);
	void update();
};

<<<<<<< HEAD
=======

>>>>>>> master
/// Listener which sets the Phont_Test Shader as the RenderManagers current Shader
class SetCurrentShaderListener : public Listener{
private:
	RenderManager* rm;
	Shader* shader;
public:
	SetCurrentShaderListener(Shader* shader);
	void update();
};

<<<<<<< HEAD
/// Listener which sets the glClearColor
class SetClearColorListener : public Listener {
private:
	float r, g, b, a;
public:
	SetClearColorListener(float r = 0.0, float g = 0.0, float b = 0.0, float a = 1.0);
	void update();
};

=======

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


>>>>>>> master
/// listener on above or under water
class UnderOrAboveWaterListener : public Listener{
private:
	Camera* cam;
	bool underwater;
<<<<<<< HEAD
	float sea_level_y;
	Listener* EnterWaterListener;
	Listener* ExitWaterListener;
public:
	UnderOrAboveWaterListener(Camera* cam, float sea_level_y = 0.0f, Listener* EnterWaterListener = 0, Listener* ExitWaterListener = 0);
	void update();
};

=======
	float* sea_level_y;
	Listener* EnterWaterListener;
	Listener* ExitWaterListener;
public:
	UnderOrAboveWaterListener(Camera* cam, float* sea_level_y = new float( 0.0f ), Listener* EnterWaterListener = 0, Listener* ExitWaterListener = 0);
	void update();
};


>>>>>>> master
class RecompileAndSetShaderListener : public Listener{
private:
	std::string vertex_shader;
	std::string fragment_shader;
public:
	RecompileAndSetShaderListener(std::string vertex_shader, std::string fragment_shader);
	void update();
};

<<<<<<< HEAD
=======

>>>>>>> master
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

<<<<<<< HEAD
=======

>>>>>>> master
class UploadUniformSinusWaveListener : public Listener{
private:
	float* t;
	float frequency;
	std::string uniform_name;
public:
	UploadUniformSinusWaveListener(std::string name, float* t, float frequency, std::string uniform_name);
	UploadUniformSinusWaveListener(std::string name, float t, float frequency, std::string uniform_name);
	void update();
};
<<<<<<< HEAD
=======


class SetFrameBufferObjectListener : public Listener {
private: 
	FrameBufferObject* fbo;
public:
	SetFrameBufferObjectListener( FrameBufferObject* fbo);
	void update();
};


class UnbindFrameBufferObjectListener : public Listener {
public:
	UnbindFrameBufferObjectListener();
	void update();
};
>>>>>>> master

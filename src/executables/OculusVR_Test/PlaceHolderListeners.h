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

#include "IO/Oculus.h"
/// Listener which prints the Oculus Orientation on update
class PrintOculusOrientationListener : public Listener
{
private:
	Oculus* oculus;
public:
	PrintOculusOrientationListener(Oculus* oculus);
	void update();
};

/// Listener which updates the Oculus Orientation variables on update
class UpdateOculusOrientationListener : public Listener
{
private:
	Oculus* oculus;
public:
	UpdateOculusOrientationListener(Oculus* oculus = 0);
	void update();
};

/// Listener which binds the Oculus' FBO image
class BindOculusFrameBufferObjectListener : public Listener
{
private:
	Oculus* oculus;
public:
	BindOculusFrameBufferObjectListener(Oculus* oculus = 0);
	void update();
};


/// Listener which unbinds the Oculus' FBO image
class UnbindOculusFrameBufferObjectListener : public Listener
{
private:
	Oculus* oculus;
public:
	UnbindOculusFrameBufferObjectListener(Oculus* oculus = 0);
	void update();
};

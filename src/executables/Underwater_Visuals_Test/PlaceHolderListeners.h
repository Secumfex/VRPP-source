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

/// listener to upload a UniformVec3
class UploadUniformVec3Listener : public Listener {
private:
	glm::vec3 vector;
	std::string uniform_name;
public:		
	UploadUniformVec3Listener(std::string name = std::string("UNIFORMUPLOADLISTENER"), glm::vec3 vector = glm::vec3(0.0f,0.0f,0.0f), std::string uniform_name = "custom_uniform");
	void update();	
};

class UploadUniformFloatListener : public Listener {
private:
	float value;
	std::string uniform_name;
public:
	UploadUniformFloatListener(std::string name = std::string("UNIFORMUPLOADLISTENER"), float value = 0.0f, std::string uniform_name = "custom_uniform");
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
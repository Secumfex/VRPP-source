#ifndef RENDERMANAGER_H
#define RENDERMANAGER_H
//#include "IO/IOManager.h"   @todo problem due to multiple includes of glfw and stuff
#include "Visuals/RenderQueue.h"
#include "Patterns/Singleton.h"
#include "Patterns/Subject.h"
#include "IO/Camera.h"
#include "Visuals/Shader.h"
#include "Visuals/FrameBufferObject.h"
#include "Visuals/Frustum.h"


// RenderManager is a Singleton and can be called by getInstance(), it is also a Subject
class RenderManager : public Singleton<RenderManager>, public Subject{
	friend class Singleton <RenderManager>;  //nötig damit Singleton Zugriff auf private und protected Membervariablen von RenderManager hat
protected:
	RenderManager();
public:
    ~RenderManager ();
	//RenderQueue renderQueue;

	void setRenderQueue(RenderQueue* currentRQ);
	void setCamera(Camera* camera);
	void setCurrentGC(GraphicsComponent* gc);
	void setCurrentShader(Shader* shader);
	void setCurrentFBO(FrameBufferObject* fbo);
	void setProjectionMatrix(float fovy, float aspect, float near, float far);
	void setDefaultProjectionMatrix();
	void setCurrentFrustum(Frustum* frustum);
	void setLightPosition (glm::vec3 pos, int index);

	VirtualObject* getCurrentVO();
	GraphicsComponent* getCurrentGC();
	Shader* getCurrentShader();
	Camera* getCamera();
	FrameBufferObject* getCurrentFBO();
	GLFWwindow* getWindow();
	RenderQueue* getRenderQueue();
	Frustum* getCurrentFrustum();
	glm::mat4 getProjectionMatrix();
	glm::mat4 getLightProjectionMatrix(int index);


	void libInit();
	void manageShaderProgram();
	void renderLoop();
	void attachListenerOnNewFrame(Listener* listener);	        //!< attach a listener that will be called at the beginning of a frameloop
	void attachListenerOnWindowShouldClose(Listener* listener); //!< attach a listener that will be called at the closure of the GLFW window


private:

	void createFourLightsources();

	GLuint vbo;
	GLuint MVPHandle;
	GLuint shaderProgramHandle;

	GLFWwindow* window;

	Frustum *mFrustum;
	Camera* mCamera;
	RenderQueue* mRenderqueue;
	Shader* mCurrentShader;
	GraphicsComponent* mCurrentGC;
	VirtualObject* mCurrentVO;
	FrameBufferObject* mCurrentFBO;
	vector<glm::vec3> mLightPositions;

};

#endif /* RENDERMANAGER_H */

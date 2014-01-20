#ifndef RENDERMANAGER_H
#define RENDERMANAGER_H
#include "IO/IOManager.h"
#include "Visuals/RenderQueue.h"
#include "Patterns/Singleton.h"
#include "Patterns/Subject.h"

// RenderManager is a Singleton and can be called by getInstance(), it is also a Subject
class RenderManager : public Singleton<RenderManager>, public Subject{
	friend class Singleton <RenderManager>;  //nötig damit Singleton Zugriff auf private und protected Membervariablen von RenderManager hat
protected:
	RenderManager();
public:
    ~RenderManager ();
	//RenderQueue renderQueue;
	void setRenderQueue();
	void libInit();
	void manageShaderProgram();
	void renderLoop();
	void attachFrameListener(Listener* listener);	//attach a listener that will be called at the beginning of a frameloop
	glm::mat4 getProjectionMatrix();
	void setProjectionMatrix(glm::mat4 _projectionMatrix);
	void setDefaultProjectionMatrix();
};

#endif /* RENDERMANAGER_H */

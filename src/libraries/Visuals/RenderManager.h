#ifndef RENDERMANAGER_H
#define RENDERMANAGER_H
#include "IO/IOManager.h"
#include "Visuals/RenderQueue.h"
#include "Patterns/Singleton.h"
#include "Patterns/ConcreteSubject.h"

// RenderManager is a Singleton and can be called by getInstance(), it is also a Subject
class RenderManager : public Singleton<RenderManager>, public ConcreteSubject{
	friend class Singleton <RenderManager>;  //nötig damit Singleton Zugriff auf private und protected Membervariablen von RenderManager hat
private:

protected:
	RenderManager() {}
public:
    ~RenderManager () {}
	RenderQueue renderQueue;
	IOManager iOManager;
	void renderLoop();
};

#endif

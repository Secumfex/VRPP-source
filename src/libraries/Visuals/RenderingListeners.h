#ifndef RENDERINGLISTENERS_H_
#define RENDERINGLISTENERS_H_

#include <Visuals/VirtualObjectFactory.h>
#include <Visuals/RenderManager.h>


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
	virtual void update();
};

#endif

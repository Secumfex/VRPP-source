#include <Visuals/RenderingListeners.h>

RenderVirtualObjectListener::RenderVirtualObjectListener(VirtualObject* vo){
	this->vo = vo;
}

void RenderVirtualObjectListener::update(){
	std::vector<GraphicsComponent* > gcs = vo->getGraphicsComponent();

	for (unsigned int j = 0; j < gcs.size(); j++){
		RenderManager::getInstance()->setCurrentGC(gcs[j]);
		RenderManager::getInstance()->getCurrentShader()->uploadAllUniforms();
		RenderManager::getInstance()->getCurrentShader()->render(gcs[j]);
	}
}

RenderGraphicsComponentListener::RenderGraphicsComponentListener(GraphicsComponent* gc){
	this->gc = gc;
}

void RenderGraphicsComponentListener::update(){
	if( gc != 0){
		RenderManager::getInstance()->setCurrentGC(gc);
		RenderManager::getInstance()->getCurrentShader()->uploadAllUniforms();
		RenderManager::getInstance()->getCurrentShader()->render(gc);
	}
}

RenderScreenFillingTriangleListener::RenderScreenFillingTriangleListener(){
	this->gc = VirtualObjectFactory::getInstance()->getTriangle();
}

void RenderScreenFillingTriangleListener::update(){
	glDisable(GL_DEPTH_TEST);
	RenderGraphicsComponentListener::update();
	glEnable(GL_DEPTH_TEST);

}

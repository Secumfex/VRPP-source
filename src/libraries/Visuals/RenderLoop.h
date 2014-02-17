/*
 * RenderLoop.h
 *
 *  Created on: 11.02.2014
 *      Author: Dirk Diggler
 */

#ifndef RENDERLOOP_H_
#define RENDERLOOP_H_

#include "Visuals/RenderManager.h"

class RenderLoop {
public:
	RenderLoop();
	virtual ~RenderLoop();
	void fillLoop();
	void setCurrentRenderQueue(RenderQueue* rq);
	void setCurrentRenderManager(RenderManager* rm);
private:
	RenderQueue* mRenderQueue;
	RenderManager* mRenderManager;

};

#endif /* RENDERLOOP_H_ */

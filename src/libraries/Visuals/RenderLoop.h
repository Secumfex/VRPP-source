/*
 * RenderLoop.h
 *
 *  Created on: 11.02.2014
 *      Author: Dirk Diggler
 */

#ifndef RENDERLOOP_H_
#define RENDERLOOP_H_

class RenderLoop {
public:
	RenderLoop();
	virtual ~RenderLoop();
	void fillLoop();
	void setCurrentRenderQueue(RenderQueue* rq);
private:
	RenderQueue* mRenderQueue;

};

#endif /* RENDERLOOP_H_ */

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
	/** \brief default constructor
	 *
	 */
	RenderLoop();

	/** \brief destructor
	 *
	 */
	virtual ~RenderLoop();

	/** \brief !docu pls!
	 *
	 */
	void fillLoop();
private:
	RenderQueue* mRenderQueue;		/**< !docu pls! */
	RenderManager* mRenderManager;	/**< !docu pls! */
};

#endif /* RENDERLOOP_H_ */

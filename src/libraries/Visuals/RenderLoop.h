#ifndef RENDERLOOP_H_
#define RENDERLOOP_H_

#include "Visuals/RenderPass.h"

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

	/** \brief render a loop iteration
	 *
	 */
	virtual	void render();

	void addRenderPass( RenderPass* renderPass);

	std::vector<RenderPass* > getRenderPasses();
private:
	std::vector<RenderPass* > mRenderPasses;
};

#endif

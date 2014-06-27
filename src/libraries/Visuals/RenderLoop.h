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

	/** \brief add a renderpass before another renderpass
	 *
	 *	if beforeRenderPass does not exist in RenderPasses vector,
	 *	method will return false
	 *
	 * @param addRenderPass		to be inserted
	 * @param beforeRenderPass  to be searched for
	 * @return whether the render pass could be inserted at the correct position
	 */
	bool addRenderPassBefore ( RenderPass* addRenderPass, RenderPass* beforeRenderPass);

	/** \brief add a renderpass after another renderpass
	 *
	 *	if afterRenderPass does not exist in RenderPasses vector,
	 *	method will return false
	 *
	 * @param addRenderPass		to be inserted
	 * @param afterRenderPass  to be searched for
	 * @return whether the render pass could be inserted at the correct position
	 */
	bool addRenderPassAfter ( RenderPass* addRenderPass, RenderPass* afterRenderPass);

	std::vector<RenderPass* > getRenderPasses();
private:
	std::vector<RenderPass* > mRenderPasses;
};

#endif

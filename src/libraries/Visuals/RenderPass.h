/*
 * RenderPass.h
 *
 *  Created on: 11.02.2014
 *      Author: Dirk Diggler
 */

#ifndef RENDERPASS_H_
#define RENDERPASS_H_

class RenderPass {
public:
	RenderPass();
	virtual ~RenderPass();
	void addRenderPass(Shader shader);
};

#endif /* RENDERPASS_H_ */

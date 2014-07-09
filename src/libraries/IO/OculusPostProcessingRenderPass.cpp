#include "IO/OculusPostProcessingRenderPass.h"

OculusPostProcessingRenderPass::OculusPostProcessingRenderPass(
		Oculus* oculus, FrameBufferObject* fbo){
		this->oculus = oculus;
		mFBO = fbo;
}

void OculusPostProcessingRenderPass::activate() {
	if (mFBO)
	{
		mFBO->bindFBO();
	}

	glViewport( 0, 0, oculus->getRenderBuffer()->getWidth(), oculus->getRenderBuffer()->getHeight() );

}

void OculusPostProcessingRenderPass::render() {
	// just draw this on the active FBO
	oculus->PresentFbo(Oculus::PostProcess_Distortion, RiftDistortionParams());
}

void OculusPostProcessingRenderPass::deactivate() {
	if( mFBO )
	{
		mFBO->unbindFBO();
	}
}

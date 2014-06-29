#ifndef OCULUSPOSTPROCESSINGRENDERPASS_H
#define OCULUSPOSTPROCESSINGRENDERPASS_H

#include "IO/Oculus.h"
#include "Visuals/RenderPass.h"

/// Renderpass to apply PostProcessing on Renderbuffer-Image of Oculus instance and write into provided FBO or Screen
class OculusPostProcessingRenderPass : public RenderPass
{
private:
	Oculus* oculus;	/**< Oculus instance whose renderbuffer will be used to apply post processing on */
public:
	OculusPostProcessingRenderPass( Oculus* oculus, FrameBufferObject* fbo = 0);
	void activate();	/**< bind fbo if any, set viewport */
	void render();		/**< call Oculus::PresentFbo( ... )*/
	void deactivate();	/**< unbind fbo if any */
};

#endif

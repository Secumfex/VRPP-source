#ifndef UPLOADUNIFORMLISTENERS_H_
#define UPLOADUNIFORMLISTENERS_H_

#include "Patterns/Listener.h"



	/*
	 * This class provides a number of Listeners for our Shaders.
	 * These Listeners are able to upload uniform variables
	 * from our OpenGL program to our GLSL program.
	 * The Shader class creates them, directly after compiling
	 * the shader, in order to just notify them. This way, we
	 * don't have to upload every uniform variable seperately,
	 * but they can get all they need by themselves.
	 */

class UploadUniformModelMatrixListener : public Listener{

 	public:
 		UploadUniformModelMatrixListener(std::string name);
 	 	void update();
 };

 class UploadUniformViewMatrixListener : public Listener{

 	public:
 		UploadUniformViewMatrixListener(std::string name);
 	 	void update();
 };

 class UploadUniformPerspectiveMatrixListener : public Listener{

 	public:
 		UploadUniformPerspectiveMatrixListener(std::string name);
 	 	void update();
 };

 class UploadUniformInverseModelViewMatrixListener : public Listener{

 	public:
 		UploadUniformInverseModelViewMatrixListener(std::string name);
 	 	void update();
 };

 class UploadUniformLightPerspectiveMatrixListener : public Listener{

 	public:
	 UploadUniformLightPerspectiveMatrixListener(std::string name);
 	 	void update();
 };

 class UploadUniformPositionMapListener : public Listener{

 	public:
 		UploadUniformPositionMapListener(std::string name);
 	 	void update();
 };

 class UploadUniformNormalMapListener : public Listener{

 	public:
 		UploadUniformNormalMapListener(std::string name);
 	 	void update();
 };

 class UploadUniformColorMapListener : public Listener{

 	public:
 		UploadUniformColorMapListener(std::string name);
 	 	void update();
 };

 class UploadUniformShadowMapListener : public Listener{

 	public:
 		UploadUniformShadowMapListener(std::string name);
 	 	void update();
 };

 class UploadUniformDepthMapListener : public Listener{

 	public:
	 UploadUniformDepthMapListener(std::string name);
 	 	void update();
 };

 class UploadUniformDiffuseTextureListener : public Listener{

  	public:
	 UploadUniformDiffuseTextureListener(std::string name);
  	 	void update();
  };

 class UploadUniformNormalTextureListener : public Listener{

  	public:
	 UploadUniformNormalTextureListener(std::string name);
  	 	void update();
  };

 class UploadUniformSpecularMapListener : public Listener{

  	public:
	 UploadUniformSpecularMapListener(std::string name);
  	 	void update();
  };

 class UploadUniformShininessListener : public Listener{

  	public:
	 UploadUniformShininessListener(std::string name);
  	 	void update();
  };

class UploadUniformTransparencyListener : public Listener{
    
public:
    UploadUniformTransparencyListener(std::string name);
    void update();
};

 class UploadUniformDiffuseColorListener : public Listener{

  	public:
	 UploadUniformDiffuseColorListener(std::string name);
  	 	void update();
  };

 class UploadUniformAmbientColorListener : public Listener{

  	public:
	 UploadUniformAmbientColorListener(std::string name);
  	 	void update();
  };

 class UploadUniformSpecularColorListener : public Listener{

  	public:
	 UploadUniformSpecularColorListener(std::string name);
  	 	void update();
  };
 class UploadUniformEmissiveColorListener : public Listener{

  	public:
	 UploadUniformEmissiveColorListener(std::string name);
  	 	void update();
  };
 class UploadUniformBlurStrengthListener : public Listener{

  	public:
	 UploadUniformBlurStrengthListener(std::string name);
  	 	void update();
  };
 class UploadUniformResolutionXListener : public Listener{

  	public:
	 UploadUniformResolutionXListener(std::string name);
  	 	void update();
  };
 class UploadUniformResolutionYListener : public Listener{

  	public:
	 UploadUniformResolutionYListener(std::string name);
  	 	void update();
  };

#endif /* UPLOADUNIFORMLISTENERS_H_ */

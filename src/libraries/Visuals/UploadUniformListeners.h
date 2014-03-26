#ifndef UPLOADUNIFORMLISTENERS_H_
#define UPLOADUNIFORMLISTENERS_H_

#include "Patterns/Listener.h"
#include <sstream>



/** \brief This class provides a number of Listeners for our Shaders.
 *
 * These Listeners are able to upload uniform variables
 * from our OpenGL program to our GLSL program.
 * The Shader class creates them, directly after compiling
 * the shader, in order to just notify them. This way, we
 * don't have to upload every uniform variable seperately,
 * but they can get all they need by themselves.
 */

class UploadUniformModelMatrixListener : public Listener{

 	public:
		///constructor @param name
 		UploadUniformModelMatrixListener(std::string name);
 		///
 	 	void update();
 };

 class UploadUniformViewMatrixListener : public Listener{

 	public:
		///constructor @param name
 		UploadUniformViewMatrixListener(std::string name);
 	 	///
 		void update();
 };

 class UploadUniformPerspectiveMatrixListener : public Listener{

 	public:
	 	///constructor @param name
 		UploadUniformPerspectiveMatrixListener(std::string name);
 	 	///
 		void update();
 };

 class UploadUniformInverseModelViewMatrixListener : public Listener{

 	public:
	 	///constructor @param name
 		UploadUniformInverseModelViewMatrixListener(std::string name);
 	 	///
 		void update();
 };

 class UploadUniformLightPerspectiveMatrixListener : public Listener{

 	public:
	 	///constructor @param name
	 	UploadUniformLightPerspectiveMatrixListener(std::string name);
	 	///
	 	void update();
 };

 class UploadUniformPositionMapListener : public Listener{

 	public:
	 	///constructor @param name
 		UploadUniformPositionMapListener(std::string name);
 	 	///
 		void update();
 };

 class UploadUniformNormalMapListener : public Listener{

 	public:
	 	///constructor @param name
 		UploadUniformNormalMapListener(std::string name);
 	 	///
 		void update();
 };

 class UploadUniformColorMapListener : public Listener{

 	public:
	 	///constructor @param name
 		UploadUniformColorMapListener(std::string name);
 	 	///
 		void update();
 };

 class UploadUniformShadowMapListener : public Listener{

 	public:
	 	///constructor @param name
 		UploadUniformShadowMapListener(std::string name);
 	 	///
 		void update();
 };

 class UploadUniformDepthMapListener : public Listener{

 	public:
	 	///constructor @param name
	 	UploadUniformDepthMapListener(std::string name);
 	 	///
	 	void update();
 };

 class UploadUniformDiffuseTextureListener : public Listener{

  	public:
	 ///constructor @param name
	 UploadUniformDiffuseTextureListener(std::string name);
  	 ///
	 void update();
  };

 class UploadUniformNormalTextureListener : public Listener{

  	public:
	 ///constructor @param name
	 UploadUniformNormalTextureListener(std::string name);
  	 ///
	 void update();
  };

 class UploadUniformSpecularMapListener : public Listener{

  	public:

	 ///constructor @param name
	 UploadUniformSpecularMapListener(std::string name);
	 ///
  	 void update();

  };

 class UploadUniformShininessListener : public Listener{

  	public:
	 ///constructor @param name
	 UploadUniformShininessListener(std::string name);
  	 ///
	 void update();
  };

class UploadUniformTransparencyListener : public Listener{
    
public:

	 ///constructor @param name
    UploadUniformTransparencyListener(std::string name);


    void update();
};

 class UploadUniformDiffuseColorListener : public Listener{

  	public:
	 ///constructor @param name
	 UploadUniformDiffuseColorListener(std::string name);
  	 ///
	 void update();
  };

 class UploadUniformAmbientColorListener : public Listener{

  	public:
	 ///constructor @param name
	 UploadUniformAmbientColorListener(std::string name);
  	 ///
	 void update();
  };

 class UploadUniformSpecularColorListener : public Listener{

  	public:
	 ///constructor @param name
	 UploadUniformSpecularColorListener(std::string name);
  	 ///
	 void update();
  };
 class UploadUniformEmissiveColorListener : public Listener{

  	public:
	 ///constructor @param name
	 UploadUniformEmissiveColorListener(std::string name);
  	 ///
	 void update();
  };
 class UploadUniformBlurStrengthListener : public Listener{

  	public:
	 ///constructor @param name
	 UploadUniformBlurStrengthListener(std::string name);
  	 ///
	 void update();
  };
 class UploadUniformResolutionXListener : public Listener{

  	public:
	 ///constructor @param name
	 UploadUniformResolutionXListener(std::string name);
  	 ///
	 void update();
  };
 class UploadUniformResolutionYListener : public Listener{

  	public:
	 ///constructor @param name
	 UploadUniformResolutionYListener(std::string name);
  	 ///
	 void update();
  };
 class UploadUniformBoneTransformationListener : public Listener{

  	public:
	 ///constructor @param name
	 UploadUniformBoneTransformationListener(std::string name, std::string boneName);
  	 ///
	 void update();

	 int index;
  };

#endif /* UPLOADUNIFORMLISTENERS_H_ */

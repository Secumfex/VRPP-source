#ifndef UPLOADUNIFORMLISTENERS_H_
#define UPLOADUNIFORMLISTENERS_H_

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Patterns/Listener.h"

class FrameBufferObject;

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
 private:
 	FrameBufferObject* mSourceFBO;
 public:
	 	///constructor @param name @param source_fbo
 		UploadUniformPositionMapListener(std::string name, FrameBufferObject* source_fbo = 0);
 	 	///
 		void update();
 };

 class UploadUniformNormalMapListener : public Listener{
 private:
 	FrameBufferObject* mSourceFBO;
 	public:
	 	///constructor @param name @param source_fbo
 		UploadUniformNormalMapListener(std::string name, FrameBufferObject* source_fbo = 0);
 	 	///
 		void update();
 };

 class UploadUniformColorMapListener : public Listener{
 private:
 	FrameBufferObject* mSourceFBO;
 	public:
	 	///constructor @param name @param source_fbo
 		UploadUniformColorMapListener(std::string name, FrameBufferObject* source_fbo = 0);
 	 	///
 		void update();
 };

 class UploadUniformShadowMapListener : public Listener{
 private:
 	FrameBufferObject* mSourceFBO;
 	public:
	 	///constructor @param name
 		UploadUniformShadowMapListener(std::string name, FrameBufferObject* source_fbo = 0);
 	 	///
 		void update();
 };

 class UploadUniformDepthMapListener : public Listener{
 private:
 	FrameBufferObject* mSourceFBO;
 	public:
	 	///constructor @param name @param source_fbo
	 	UploadUniformDepthMapListener(std::string name, FrameBufferObject* source_fbo = 0);
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
 private:
 	FrameBufferObject* mSourceFBO;
  	public:

	 ///constructor @param name
	 UploadUniformSpecularMapListener(std::string name, FrameBufferObject* source_fbo = 0);
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
 class UploadUniformWindowTimeListener : public Listener{
 public:
	 //constructor @param name
	 UploadUniformWindowTimeListener(std::string name);
	 ///upload current window time to "uniformTime"
	 void update();

 };


/******************** CUSTOM UNIFORM UPLOAD LISTENERS ***********************/	

	/// listener to upload a custom Uniform Vec3
	class UploadUniformVec3Listener : public Listener {
	private:
		glm::vec3* vector;
		std::string uniform_name;
	public:		
		UploadUniformVec3Listener(std::string name = std::string("UNIFORMUPLOADLISTENER"), glm::vec3 vector = glm::vec3(0.0f,0.0f,0.0f), std::string uniform_name = "custom_uniform");
		UploadUniformVec3Listener(std::string name, glm::vec3* vector, std::string uniform_name);
		void update();	
	};

	/// listener to upload a custom Uniform Float
	class UploadUniformFloatListener : public Listener {
	private:
		float* value;
		std::string uniform_name;
	public:
		UploadUniformFloatListener(std::string name = std::string("UNIFORMUPLOADLISTENER"), float value = 0.0f, std::string uniform_name = "custom_uniform");
		UploadUniformFloatListener(std::string name, float* value, std::string uniform_name);
		void update();
	};

		/// listener to upload a custom Uniform mat4
	class UploadUniformMat4Listener : public Listener {
	private:
		glm::mat4* matrix;
		std::string uniform_name;
	public:		
		UploadUniformMat4Listener(std::string name = std::string("UNIFORMUPLOADLISTENER"), glm::mat4 matrix = glm::mat4(1.0f), std::string uniform_name = "custom_uniform");
		UploadUniformMat4Listener(std::string name, glm::mat4* matrix, std::string uniform_name);
		void update();	
	};

	/// listener to upload a custom Uniform GLint
	class UploadUniformIntListener : public Listener {
	private:
		GLint* value;
		std::string uniform_name;
	public:		
		UploadUniformIntListener(std::string name = std::string("UNIFORMUPLOADLISTENER"), GLint value = 0, std::string uniform_name = "custom_uniform");
		UploadUniformIntListener(std::string name, GLint* value, std::string uniform_name);
		void update();	
	};

	/// listener to bind texture to a GL_TEXTURE unit and upload this unit to a uniform sampler 2D variable
	class UploadUniformTextureListener : public Listener {
	private:
		GLint unit;
		GLuint texture_handle;
		std::string uniform_name;
	public:		
		void setTextureHandle(GLuint texture_handle);
		void setTextureUnit(GLint unit);
		void setUniformName(std::string uniform_name);

		UploadUniformTextureListener(std::string name = std::string("UNIFORMUPLOADLISTENER"), GLint unit = 0, std::string uniform_name = "custom_uniform", GLuint texture_handle = 0);
		void update();	
	};

    /// listener to upload a custom Uniform boolean
    class UploadUniformBooleanListener : public Listener {
    private:
        bool* value;
        std::string uniform_name;
    public:
        UploadUniformBooleanListener(std::string name = std::string("UNIFORMUPLOADLISTENER"), bool value = false, std::string uniform_name = "custom_uniform");
        UploadUniformBooleanListener(std::string name, bool* value, std::string uniform_name);
    void update();
    };



#endif /* UPLOADUNIFORMLISTENERS_H_ */

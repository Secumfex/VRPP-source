#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string.h>

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_inverse.hpp>

#include "Tools/ShaderTools.h"
#include "Tools/TextureTools.h"

#include "Visuals/Shader.h"
#include "Visuals/FrameBufferObject.h"
#include "Visuals/VirtualObjectFactory.h"
#include "Visuals/RenderManager.h"


int main() {

	// render window
	glfwInit();

#ifdef __APPLE__
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glewExperimental= GL_TRUE;
#endif

	GLFWwindow* window = glfwCreateWindow(800, 800, "Compositing", NULL, NULL);
	glfwMakeContextCurrent(window);
	glClearColor(1,1,1,0);

	// get framebuffer size
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);

	//init opengl 3 extension
	glewInit();

	// print out some info about the graphics drivers
	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
	std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;



	//load, compile and link simple texture rendering program for a screen filling plane

	Shader *simpleTexShader = new Shader(SHADERS_PATH "/GBuffer_clone/screenFill.vert",
			SHADERS_PATH "/GBuffer_clone/simpleTexture.frag");

	Shader *finalCompShader = new Shader(	SHADERS_PATH "/GBuffer_clone/screenFill.vert",
			SHADERS_PATH "/GBuffer_clone/finalCompositing.frag");

	Shader *gbufferShader = new Shader(		SHADERS_PATH "/GBuffer_clone/GBuffer.vert",
			SHADERS_PATH "/GBuffer_clone/GBuffer.frag");

//	Shader *gbufferShader = new Shader();

	Shader *gbuffer_normalMap_Shader = new Shader(		SHADERS_PATH "/GBuffer_clone/GBuffer.vert",
			SHADERS_PATH "/GBuffer_clone/GBuffer_normalTexture.frag");

	RenderQueue* rq = new RenderQueue();
	RenderManager* rm = RenderManager::getInstance();
	Camera* cam = new Camera();
	Frustum* frustum = new Frustum(cam);


	//--------------------------------------------//
	//        Create a Vertex Array Object        //
	//         containing several buffers         //
	//             to render a cube               //
	//--------------------------------------------//

	VirtualObjectFactory *voFactory = VirtualObjectFactory::getInstance();

	VirtualObject *object03 = voFactory->createVirtualObject(RESOURCES_PATH "/barrel.obj");
	VirtualObject *object02 = voFactory->createVirtualObject(RESOURCES_PATH "/cow.obj");
	VirtualObject *object01 = voFactory->createVirtualObject(RESOURCES_PATH "/cube.obj");

	GraphicsComponent* triangle = voFactory->getTriangle();


	//--------------------------------------------//
	//         Create a Framebuffer Object        //
	//--------------------------------------------//

	FrameBufferObject *fbo = new FrameBufferObject(width, height);

	fbo->bindFBO();

	fbo->createPositionTexture();
	fbo->createNormalTexture();
	fbo->createColorTexture();
	fbo->createMaterialTexture();

	//set the list of draw buffers.
	fbo->makeDrawBuffers();

	//rotation of the cube
	float angle = 0.0f;
	float rotationSpeed = 1.0f;

	//Statisches "binden" unserer Uniforms/Objekte
	//Muss man also nur einmal machen

	gbufferShader->setBlurStrength(0);
	gbuffer_normalMap_Shader->setBlurStrength(0);

	rq->addVirtualObject(object01);
	rq->addVirtualObject(object02);
	rq->addVirtualObject(object03);


	rm->setRenderQueue(rq);
	rm->setCurrentFBO(fbo);
	rm->setCamera(cam);
	rm->setCurrentFrustum(frustum);
	rm->setProjectionMatrix(40.0f, 1.0f, 0.1f, 100.f);

	cam->setPosition(glm::vec3(0.0f, 1.0f, -6.0f));
	cam->setCenter(glm::vec3(1.0f, 3.0f, 1.0f));

	frustum->updateModelMatrix();

	while(!glfwWindowShouldClose(window)) {

		glfwMakeContextCurrent(window);

		int newwidth, newheight;
		glfwGetFramebufferSize(window, &newwidth, &newheight);
		if(newwidth != width || newheight != height){
			fbo->resize(newwidth, newheight);
			//		rm->setProjectionMatrix(glm::perspective(40.0f, (newwidth * 1.0f) / newheight , 0.1f, 100.f));
			width = newwidth;
			height = newheight;
		}

		using namespace glm;

		glEnable(GL_DEPTH_TEST);

		//rotation angle
		angle = fmod((float)(angle+rotationSpeed*glfwGetTime()), (float)(pi<float>()*2.0f));
		glfwSetTime(0.0);

		//scale a cube into a flat plane
		mat4 modelMatrix01 = scale(translate(mat4(1.0f), vec3(0.0f, -1.0f, 0.0f)), vec3(2.5f, 0.2f, 2.5f));

		//nice rotation of a small cube
		mat4 modelMatrix02 = scale(translate(rotate(mat4(1.0f), degrees(angle), vec3(1.0f, 1.0f, 0.0f)), vec3(0.0f, 0.5f, -0.5f)), vec3(0.9f, 0.9f, 0.9f));

		mat4 modelMatrix03 = scale(translate(rotate(mat4(1.0f), degrees(angle), vec3(0.0f, 1.0f, 1.0f)), vec3(0.0f, 0.5f, -0.5f)), vec3(0.3f, 0.3f, 0.3f));

		object01->setModelMatrix(modelMatrix01);
		object02->setModelMatrix(modelMatrix02);
		object03->setModelMatrix(modelMatrix03);

		//--------------------------------------------//
		//        Render the scene into the FBO       //
		//--------------------------------------------//

		fbo->bindFBO();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		        glViewport(0, 0, width, (height/4)*3);

		gbufferShader->useProgram();
		rm->setCurrentShader(gbufferShader);
		//----------------------------------------------------------------------------------------//
		//        This is da Main-Renderloop. Hier werden alle GC für den GBuffer gerendert       //
		//----------------------------------------------------------------------------------------//

		list<VirtualObject*> vo_list = rm->getRenderQueue()->getVirtualObjectList();
		unsigned int i= 0;
		while (!vo_list.empty()) {
			unsigned int j= 0;
			VirtualObject* vo_temp = vo_list.front();
			vo_list.pop_front();
			for (j = 0; j < vo_temp->getGraphicsComponent().size(); ++j) {
				GraphicsComponent *gc_temp = vo_temp->getGraphicsComponent()[j];
				rm->setCurrentGC(gc_temp);

				if(frustum->inFrustum(gc_temp))
					std::cout << gc_temp->getMaterial()->getName() << "ES KOLLIDIERT" << std:: endl;

				if(gc_temp->getMaterial()->hasNormalTexture()){
					gbuffer_normalMap_Shader->useProgram();
					rm->setCurrentShader(gbuffer_normalMap_Shader);
					gbuffer_normalMap_Shader->uploadAllUniforms();
				}else{
					gbufferShader->useProgram();
					rm->setCurrentShader(gbufferShader);
					gbufferShader->uploadAllUniforms();
				}

				if(gc_temp->getGhostObject()->getNumOverlappingObjects() > 0)
				std::cout << gc_temp->getGhostObject()->getNumOverlappingObjects() << " SO VIELE ÜBERSCHNEIDUNGEN BEI" << gc_temp->getMaterial()->getName() << endl;

				gbufferShader->render(gc_temp);
			}
		}

		fbo->unbindFBO();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glDisable(GL_DEPTH_TEST);


		//--------------------------------------------//
		//       Take the textures from the FBO       //
		//      to compose them on an image plane     //
		//--------------------------------------------//

		//      Hier findet das Compositing statt :) ist schon einiges kürzer, nicht wahr?

		finalCompShader->useProgram();
		rm->setCurrentShader(finalCompShader);

				glViewport(0, 0, width, height);

		finalCompShader->uploadAllUniforms();
		finalCompShader->render(triangle);

		fbo->unbindAllTextures();

		//--------------------------------------------//
		//       Render small views at the top to     //
		//      show all the components of the FBO    //
		//--------------------------------------------//

		        glBindVertexArray(triangle->getMesh()->getVAO());
		        simpleTexShader->useProgram();
		        rm->setCurrentShader(simpleTexShader);

		        glViewport(0, (height/4)*3, width/4, height/4);
		        glBindTexture(GL_TEXTURE_2D, fbo->getPositionTextureHandle());
		        glDrawArrays(GL_TRIANGLES, 0, 3);

		        glViewport(width/4, (height/4)*3, width/4, height/4);
		        glBindTexture(GL_TEXTURE_2D, fbo->getNormalTextureHandle());
		        glDrawArrays(GL_TRIANGLES, 0, 3);

		        glViewport((width/4)*2, (height/4)*3, width/4, height/4);
		        glBindTexture(GL_TEXTURE_2D, fbo->getColorTextureHandle());
		        glDrawArrays(GL_TRIANGLES, 0, 3);

		        glViewport((width/4)*3, (height/4)*3, width/4, height/4);
		        glBindTexture(GL_TEXTURE_2D, fbo->getMaterialTextureHandle());
		        glDrawArrays(GL_TRIANGLES, 0, 3);

		//show what's been drawn
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;

};

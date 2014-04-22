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
#include "Application/Application.h"
#include "Application/ApplicationStates.h"
#include "Tools/UtilityListeners.h"
#include "Application/ApplicationListeners.h"

Application *myApp;

int mainTemp() {

	// render window
	myApp = Application::getInstance();

	myApp->setLabel("GBUFFER_CLONE_extreme");


	GLFWwindow* window = RenderManager::getInstance()->getWindow();

	VRState *myVRState = new VRState("EFFECTS AND LASERS AND SHIT");
	IOHandler*   	inputHandler = myVRState->getIOHandler();
	inputHandler->attachListenerOnKeyPress(		new TerminateApplicationListener(myApp), GLFW_KEY_ESCAPE);
	myApp->run();

	glClearColor(1,1,1,1);


	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	RenderQueue* rq = myVRState->getRenderQueue();
	RenderManager* rm = RenderManager::getInstance();
	Camera* cam = myVRState->getCamera();
	Frustum* frustum = myVRState->getFrustum();

	//load, compile and link simple texture rendering program for a screen filling plane 

	Shader *simpleTexShader = new Shader(SHADERS_PATH "/Postprocessing/screenFill.vert",
			SHADERS_PATH "/Postprocessing/simpleTexture.frag");

	Shader *finalCompShader = new Shader(	SHADERS_PATH "/Postprocessing/screenFill.vert",
			SHADERS_PATH "/Postprocessing/finalCompositing.frag");

	Shader *gbufferShader = new Shader(		SHADERS_PATH "/Postprocessing/GBuffer.vert",
			SHADERS_PATH "/Postprocessing/GBuffer.frag");

	Shader *gbuffer_normalMap_Shader = new Shader(		SHADERS_PATH "/Postprocessing/GBuffer.vert",
			SHADERS_PATH "/Postprocessing/GBuffer_normalTexture.frag");

	Shader *postprocessShader = new Shader( 	SHADERS_PATH "/Postprocessing/screenFill.vert",
			SHADERS_PATH "/Postprocessing/glow.frag");

	rq->addShader(gbufferShader);
	rq->addShader(gbuffer_normalMap_Shader);
	rq->addCompositingShader(simpleTexShader);
	rq->addCompositingShader(finalCompShader);



	//--------------------------------------------//
	//        Create a Vertex Array Object        //
	//         containing several buffers         //
	//             to render a cube               //
	//--------------------------------------------//

	VirtualObjectFactory *voFactory = VirtualObjectFactory::getInstance();

	VirtualObject *object03 = voFactory->createVirtualObject(RESOURCES_PATH "/barrel.obj", VirtualObjectFactory::OTHER);
	VirtualObject *object02 = voFactory->createVirtualObject(RESOURCES_PATH "/cow.obj", VirtualObjectFactory::OTHER);
	VirtualObject *object01 = voFactory->createVirtualObject(RESOURCES_PATH "/cube.obj", VirtualObjectFactory::CUBE);

	GraphicsComponent* triangle = voFactory->getTriangle();

	MaterialManager::getInstance()->makeMaterial("polished_chrome", object02->getGraphicsComponent());

	//--------------------------------------------//
	//         Create a Framebuffer Object        //
	//--------------------------------------------//

	//GLuint fbo_texture;
	  /*/* Texture */
	  /*glActiveTexture(GL_TEXTURE0);
	  glGenTextures(1, &fbo_texture);
	  glBindTexture(GL_TEXTURE_2D, fbo_texture);
	  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	  glBindTexture(GL_TEXTURE_2D, 0);*/

	FrameBufferObject *fbo = new FrameBufferObject(width, height);

	fbo->bindFBO();

	fbo->createPositionTexture();
	fbo->createNormalTexture();
	fbo->createColorTexture();
	fbo->createSpecularTexture();
	fbo->createShadowMap();

	//set the list of draw buffers.
	fbo->makeDrawBuffers();

	FrameBufferObject *fbo2 = new FrameBufferObject(width, height);

	fbo2->bindFBO();

	fbo2->createPositionTexture();
	fbo2->createNormalTexture();
	fbo2->createColorTexture();
	fbo2->createSpecularTexture();
	fbo2->createShadowMap();

	//set the list of draw buffers.
	fbo2->makeDrawBuffers();

	fbo2->unbindFBO();

	//Listener* postprocess= new UploadUniformTextureListener	("UNIFORMUPLOADLISTENER", 12, "postprocessTexture", fbo_texture);

	//rotation of the cube
	float angle = 0.0f;
	float rotationSpeed = 1.0f;

	//Statisches "binden" unserer Uniforms/Objekte
	//Muss man also nur einmal machen

	rq->addVirtualObject(object01);
	rq->addVirtualObject(object02);
	rq->addVirtualObject(object03);


	rm->setRenderQueue(rq);
	rm->setCurrentFBO(fbo);
	rm->setCamera(cam);
	rm->setCurrentFrustum(frustum);
	rm->setPerspectiveMatrix(40.0f, 1.0f, 0.1f, 100.f);
	rm->setLightPosition(glm::vec3(5,2,-2),0);

	cam->setPosition(glm::vec3(0.0f, 1.0f, -6.0f));
	cam->setCenter(glm::vec3(0.0f, 0.0f, 0.0f));

	frustum->updateModelMatrix();

	rq->sortByAttributes();

	//system("cls");

	while(!glfwWindowShouldClose(window)) {

		glfwMakeContextCurrent(window);

		int newwidth, newheight;
		glfwGetFramebufferSize(window, &newwidth, &newheight);
		if(newwidth != width || newheight != height){
			fbo->resize(newwidth, newheight);
			//		rm->setPerspectiveMatrix(glm::perspective(40.0f, (newwidth * 1.0f) / newheight , 0.1f, 100.f));
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
		//        This is da Main-Renderloop. Hier werden alle GC fï¿½r den GBuffer gerendert       //
		//----------------------------------------------------------------------------------------//

		list<VirtualObject*> vo_list = rm->getRenderQueue()->getVirtualObjectList();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		vo_list = rm->getRenderQueue()->getVirtualObjectList();

		while (!vo_list.empty()) {
			unsigned int j= 0;
			VirtualObject* vo_temp = vo_list.front();
			vo_list.pop_front();
			for (j = 0; j < vo_temp->getGraphicsComponent().size(); ++j) {
				GraphicsComponent *gc_temp = vo_temp->getGraphicsComponent()[j];
				rm->setCurrentGC(gc_temp);

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

		fbo2->bindFBO();

		//      Hier findet das Compositing statt :) ist schon einiges kï¿½rzer, nicht wahr?

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

		fbo2->unbindFBO();

				glDisable(GL_DEPTH_TEST);

				glBindVertexArray(triangle->getMesh()->getVAO());
		        postprocessShader->useProgram();
		        rm->setCurrentShader(postprocessShader);
		        postprocessShader->uploadAllUniforms();

		        glViewport(0,0, width, height);

		        glActiveTexture(GL_TEXTURE30);
		        glBindTexture(GL_TEXTURE_2D, fbo2->getNormalTextureHandle());
		        glUniform1i(glGetUniformLocation( postprocessShader->getProgramHandle(), "preGlowTexure" ), 30);

		        glDrawArrays(GL_TRIANGLES, 0, 3);


		        glActiveTexture(GL_TEXTURE0);
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
		        glBindTexture(GL_TEXTURE_2D, fbo->getSpecularTextureHandle());
		        glDrawArrays(GL_TRIANGLES, 0, 3);

		//show what's been drawn
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;

};

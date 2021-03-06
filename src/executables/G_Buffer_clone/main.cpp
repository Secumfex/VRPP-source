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

#include "Animation/Flock.h"
#include "Visuals/Shader.h"
#include "Visuals/FrameBufferObject.h"
#include "Visuals/VirtualObjectFactory.h"
#include "Visuals/RenderManager.h"
#include "Application/Application.h"
#include "Application/ApplicationStates.h"
#include "Tools/ShaderFactory.h"

Application *myApp;

int main() {


	// render window
	myApp = Application::getInstance();

	myApp->setLabel("GBUFFER_CLONE_extreme");


	GLFWwindow* window = RenderManager::getInstance()->getWindow();

	VRState *myVRState = new VRState("LET IT SNOW");

	glClearColor(1,1,1,0);


	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	RenderQueue* rq = myVRState->getRenderQueue();
	RenderManager* rm = RenderManager::getInstance();
	Camera* cam = myVRState->getCamera();
	Frustum* frustum = myVRState->getFrustum();

	//--------------------------------------------//
	//        Create a Vertex Array Object        //
	//         containing several buffers         //
	//             to render a cube               //
	//--------------------------------------------//

	VirtualObjectFactory *voFactory = VirtualObjectFactory::getInstance();

	VirtualObject *object02 = voFactory->createVirtualObject(RESOURCES_PATH "/animation_test/Fish_bones.dae", VirtualObjectFactory::OTHER);
	VirtualObject *object03 = voFactory->createVirtualObject(RESOURCES_PATH "/animation_test/piranha.dae", VirtualObjectFactory::OTHER);
	VirtualObject *object01 = voFactory->createVirtualObject(RESOURCES_PATH "/animation_test/tentacle.dae", VirtualObjectFactory::CUBE);

	VirtualObject *object10 = voFactory->createVirtualObject(RESOURCES_PATH "/animation_test/fish.dae", VirtualObjectFactory::OTHER);


	GraphicsComponent* triangle = voFactory->getTriangle();

	Flock* myFlock = new Flock();

	glm::mat4 trans = glm::rotate(glm::mat4(), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f)) * glm::rotate(glm::mat4(), 90.0f, glm::vec3(1.0f, 0.0f, 0.0f)) * glm::scale(glm::mat4(), glm::vec3(0.25f));

	myFlock->addBoid(object02, trans);

	unsigned int i;
	for (i = 0; i < 50; ++i) {
		VirtualObject *object13 = new VirtualObject(object10);
		float size_difference = ((i % 8) * 0.01f) - 0.04f;
		trans = glm::scale(glm::mat4(), glm::vec3(0.25f + size_difference));
		myFlock->addBoid(object13, trans);
		rq->addVirtualObject(object13);
	}

	myFlock->initializeStartPositions(5.0f, glm::vec3(0.0f, 0.0f, 0.0f));


	//----------------------------//
	//        SHADERS BABY        //
	//----------------------------//

	Shader *simpleTexShader = new Shader(SHADERS_PATH "/GBuffer_clone/screenFill.vert",
			SHADERS_PATH "/GBuffer_clone/simpleTexture.frag");

	Shader *finalCompShader = new Shader(	SHADERS_PATH "/GBuffer_clone/screenFill.vert",
			SHADERS_PATH "/GBuffer_clone/finalCompositing.frag");

	Shader *gbufferShader = ShaderFactory::getInstance()->createGBuffer(object03->getGraphicsComponent()[0]);

	Shader *gbuffer_normalMap_Shader = ShaderFactory::getInstance()->createGBuffer(object01->getGraphicsComponent()[0]);


	rq->addShader(gbufferShader);
	rq->addShader(gbuffer_normalMap_Shader);
	rq->addCompositingShader(simpleTexShader);
	rq->addCompositingShader(finalCompShader);


	//--------------------------------------------//
	//         Create a Framebuffer Object        //
	//--------------------------------------------//

	FrameBufferObject *fbo = new FrameBufferObject(width, height);

	fbo->bindFBO();

	fbo->createPositionTexture();
	fbo->createNormalTexture();
	fbo->createColorTexture();
	fbo->createSpecularTexture();
	fbo->createShadowMap();

	//set the list of draw buffers.
	fbo->makeDrawBuffers();

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


	frustum->updateModelMatrix();

	float animation_time = 0.0f;
	glm::vec3 piranha_place = glm::vec3(0.0f, 0.0f, 2.0f);


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

		animation_time += glfwGetTime();

		object03->getAnimation()->updateNodes(animation_time);
		object01->getAnimation()->updateNodes(animation_time);
		myFlock->update(animation_time);
		myFlock->setPlaceToGo(vec3(sin(angle) * 10.0f, 0.0f, cos(angle) * 5.0f));
		myFlock->setPlaceToAvoid(piranha_place);


		cam->setPosition(glm::vec3(0.0f, 2.0f, -8.0f));
				cam->setCenter(glm::vec3(0.0f, 0.0f, 0.0f));


		glfwSetTime(0.0);

		//scale a cube into a flat plane
		mat4 modelMatrix01 = translate(mat4(1.0f), vec3(0.0f, -4.0f, 0.0f)) * rotate(mat4(), 90.0f, vec3(0.0f, 1.0f, 0.0f)) *scale(mat4(), vec3(0.5f, 0.5f, 0.5f));;

		//nice rotation of a small cube

		mat4 modelMatrix03 = translate(mat4(), piranha_place) * rotate(mat4(), 90.0f + (45.0f * sin(2 * angle)), vec3(-0.2f, 1.0f, 0.0f)) * scale(mat4(), vec3(0.5f, 0.5f, 0.5f));

		object01->setModelMatrix(modelMatrix01);
		object03->setModelMatrix(modelMatrix03);

		//--------------------------------------------//
		//        Render the scene into the FBO       //
		//--------------------------------------------//

		fbo->bindFBO();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glViewport(0, 0, width, (height/4)*3);

		//----------------------------------------------------------------------------------------//
		//        This is da Main-Renderloop. Hier werden alle GC f�r den GBuffer gerendert       //
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

				Shader* renderShader = ShaderFactory::getInstance()->createGBuffer(gc_temp);

				renderShader->useProgram();
				rm->setCurrentShader(renderShader);
				renderShader->uploadAllUniforms();

				renderShader->render(gc_temp);
			}
		}

		fbo->unbindFBO();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glDisable(GL_DEPTH_TEST);


		//--------------------------------------------//
		//       Take the textures from the FBO       //
		//      to compose them on an image plane     //
		//--------------------------------------------//

		//      Hier findet das Compositing statt :) ist schon einiges k�rzer, nicht wahr?

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

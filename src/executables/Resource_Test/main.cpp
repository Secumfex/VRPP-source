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

	RenderManager* rm = RenderManager::getInstance();
    RenderQueue* rq = new RenderQueue();
    Camera* cam = new Camera();
    
    
    rm->libInit();
    GLFWwindow* window=rm->getWindow();

	//load, compile and link simple texture rendering program for a screen filling plane

	Shader *simpleTexShader = new Shader(SHADERS_PATH "/Resource_Test/screenFill.vert",
			SHADERS_PATH "/Resource_Test/simpleTexture.frag");

	Shader *finalCompShader = new Shader(	SHADERS_PATH "/Resource_Test/screenFill.vert",
			SHADERS_PATH "/Resource_Test/finalCompositing.frag");

	Shader *gbufferShader = new Shader(		SHADERS_PATH "/Resource_Test/GBuffer.vert",
			SHADERS_PATH "/Resource_Test/GBuffer.frag");

	Shader *gbuffer_normalMap_Shader = new Shader(		SHADERS_PATH "/Resource_Test/GBuffer.vert",
			SHADERS_PATH "/Resource_Test/GBuffer_normalTexture.frag");
    

	//--------------------------------------------//
	//        Create a Vertex Array Object        //
	//         containing several buffers         //
	//             to render a cube               //
	//--------------------------------------------//

	VirtualObjectFactory *voFactory = VirtualObjectFactory::getInstance();

	VirtualObject *object01 = voFactory->createVirtualObject(RESOURCES_PATH "/soda_can1.obj");
	VirtualObject *object02 = voFactory->createVirtualObject(RESOURCES_PATH "/barrel.obj");
	VirtualObject *object03 = voFactory->createVirtualObject(RESOURCES_PATH "/cube.obj");
    VirtualObject *object04 = voFactory->createVirtualObject(RESOURCES_PATH "/untitled.dae");

	GraphicsComponent* triangle = voFactory->getTriangle();

	//--------------------------------------------//
	//         Create a Framebuffer Object        //
	//--------------------------------------------//

    
	//glfwGetFramebufferSize(window, &width, &height);
	FrameBufferObject *fbo = new FrameBufferObject();
    int height=fbo->getHeight();
    int width=fbo->getWidth();

	fbo->bindFBO();

	fbo->createPositionTexture();
	fbo->createNormalTexture();
	fbo->createColorTexture();
	fbo->createSpecularTexture();

	//set the list of draw buffers.
	fbo->makeDrawBuffers();

	//rotation of the cube
	float angle = 0.0f;
	float rotationSpeed = 1.0f;

	//Statisches "binden" unserer Uniforms/Objekte
	//Muss man also nur einmal machen

	gbufferShader->setBlurStrength(0.5);
	gbuffer_normalMap_Shader->setBlurStrength(0);

	rq->addVirtualObject(object01);
	rq->addVirtualObject(object02);
    rq->addVirtualObject(object04);
	rq->addVirtualObject(object03);
    


	rm->setRenderQueue(rq);
	rm->setCurrentFBO(fbo);
	rm->setProjectionMatrix(glm::perspective(45.0f, 1.0f, 0.1f, 100.f));
	rm->setCamera(cam);

	cam->setPosition(glm::vec3(0.0f, 1.0f, -6.0f));
	cam->setCenter(glm::vec3(0.0f, 0.0f, 0.0f));


	while(!glfwWindowShouldClose(window)) {

		glfwMakeContextCurrent(window);

		int newwidth, newheight;
		glfwGetFramebufferSize(window, &newwidth, &newheight);
		if(newwidth != width || newheight != height){
			fbo->resize(newwidth, newheight);
					rm->setProjectionMatrix(glm::perspective(45.0f, (newwidth * 1.0f) / newheight , 0.1f, 100.f));
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
		mat4 modelMatrix02 = scale(translate(rotate(mat4(1.0f), degrees(angle), vec3(1.0f, 1.0f, 0.0f)), vec3(2.0f, 0.8f, -0.5f)), vec3(0.9f, 0.9f, 0.9f));

		mat4 modelMatrix03 = scale(translate(rotate(mat4(1.0f), degrees(angle), vec3(0.0f, 1.0f, 1.0f)), vec3(-2.0f, 0.2f, -0.5f)), vec3(0.3f, 0.3f, 0.3f));
        modelMatrix03=scale(mat4(1.0f), vec3(0.5f,0.5f,0.5f))*modelMatrix03;
        mat4 modelMatrix04 = scale(translate(rotate(mat4(1.0f), degrees(angle), vec3(1.0f, 0.0f, 1.0f)), vec3(0.7f)),vec3(2.5f));

		object03->setModelMatrix(modelMatrix01);
		object02->setModelMatrix(modelMatrix02);
		object01->setModelMatrix(modelMatrix03);
        object04->setModelMatrix(modelMatrix04);

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
		//unsigned int i= 0;
		while (!vo_list.empty()) {
			unsigned int j= 0;
			VirtualObject* vo_temp = vo_list.front();
			vo_list.pop_front();
			for (j = 0; j < vo_temp->getGraphicsComponent().size(); ++j) {
				GraphicsComponent *gc_temp = vo_temp->getGraphicsComponent()[j];
				rm->setCurrentGC(gc_temp);

//				if(gc_temp->getMaterial()->hasNormalMap()){
//					gbuffer_normalMap_Shader->useProgram();
//					rm->setCurrentShader(gbuffer_normalMap_Shader);
//					gbuffer_normalMap_Shader->uploadAllUniforms();
//				}else{
					gbufferShader->useProgram();
					rm->setCurrentShader(gbufferShader);
					gbufferShader->uploadAllUniforms();
			//	}

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

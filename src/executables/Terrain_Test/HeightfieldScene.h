
#ifndef HEIGHTFIELDSCENE_H_
#define HEIGHTFIELDSCENE_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Application/ApplicationStates.h"
#include "PlaceHolderListeners.h"

namespace HeightfieldScene{

	//VOs
	VirtualObject* terrain;
	VirtualObject* test;

	//FBOs
	FrameBufferObject* fboGround;
	//FrameBufferObject* fboNormals;
	//FrameBufferObject* fboGloss;


	GLuint fboTexture;
	GLuint fboColor;
	GLuint fboNormals;
	GLuint fboSpecular;
	GLuint depthrenderbuffer;


	//Camera
	Camera* camera;

	//Tesxtures
	Texture* ground1;
	Texture* ground2;
	Texture* mask;

	Texture* normals1;	//normalmaps
	Texture* normals2;

	Texture* specular1;	//glossmaps
	Texture* specular2;

	static void createScene(ApplicationState* state){

		//VOs
		//terrain = state->createVirtualObject(RESOURCES_PATH"/Heightfield/terrainTest.obj",VirtualObjectFactory::TERRAIN);
		test = state->createVirtualObject(RESOURCES_PATH "/demo_scene/demo_scene_ground.dae", VirtualObjectFactory::OTHER, 0.0f, 1, true);

		//FBOs
		fboGround = new FrameBufferObject(800,600);
		fboGround->bindFBO();
		fboGround->createPositionTexture();


		glGenTextures(1,&fboTexture);
		glBindTexture(GL_TEXTURE_2D,fboTexture);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA16F,800,600,0,GL_RGBA,GL_FLOAT,0);

		//glGenTEsxtures();
		glBindTexture(GL_TEXTURE_2D,fboColor);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA16F,800,600,0,GL_RGBA,GL_FLOAT,0);

		//glGenTextures();
		glBindTexture(GL_TEXTURE_2D,fboNormals);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA16F,800,600,0,GL_RGBA,GL_FLOAT,0);

		//glGenTextures();
		glBindTexture(GL_TEXTURE_2D,fboSpecular);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA16F,800,600,0,GL_RGBA,GL_FLOAT,0);


		glGenRenderbuffers(1, &depthrenderbuffer);
		glBindRenderbuffer(GL_RENDERBUFFER, depthrenderbuffer);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 1024, 768);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthrenderbuffer);



		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, fboTexture, 0);
		GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
		glDrawBuffers(1, DrawBuffers);


		//fboGround->makeDrawBuffers();
		fboGround->unbindFBO();

		/*
		fboNormals = new FrameBufferObject(800,600);
		fboNormals->bindFBO();
		fboNormals->createNormalTexture();
		fboNormals->makeDrawBuffers();
		fboNormals->unbindFBO();
		*/

		//fboGloss = new FrameBufferObject(800,600);
		//...

		//Textures
		ground1 = new Texture(RESOURCES_PATH"/Heightfield/seamlessSandTest.jpg");
		ground2 = new Texture(RESOURCES_PATH"/Heightfield/seamlessStonesTest.jpg");
		mask = new Texture(RESOURCES_PATH"/Heightfield/terrainTest.png");

		/*
		normals1 = new Texture(RESOURCES_PATH"/Heightfield/seamlessSandTestNormal.jpg");	//normalmaps
		normals2 = new Texture(RESOURCES_PATH"/Heightfield/seamlessStonesTestNormal.jpg");

		specular1 = new Texture(RESOURCES_PATH"/Heightfield/seamlessSandTestSpecular.jpg");	//glossmaps
		specular2 = new Texture(RESOURCES_PATH"/Heightfield/seamlessStonesTestSpecular.jpg");
		*/

		//Camera

	}

	static void configInputHandling(ApplicationState* state){

		IOHandler* io = state->getIOHandler();
	}
}


#endif /* HEIGHTFIELDSCENE_H_ */

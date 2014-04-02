
#ifndef HEIGHTFIELDSCENE_H_
#define HEIGHTFIELDSCENE_H_

#include "Application/ApplicationStates.h"
#include "PlaceHolderListeners.h"

namespace HeightfieldScene{

	//VOs
	VirtualObject* terrain;

	//FBOs
	FrameBufferObject* fboGround;

	//Camera
	Camera* camera;

	//Tesxtures
	Texture* ground1;
	Texture* ground2;
	Texture* mask;

	static void createScene(ApplicationState* state){

		//VOs
		terrain = state->createVirtualObject(RESOURCES_PATH"/Heightfield/terrainTest.obj",VirtualObjectFactory::TERRAIN);

		//FBOs
		fboGround = new FrameBufferObject(800,600);
		fboGround->bindFBO();
		fboGround->createPositionTexture();
		fboGround->makeDrawBuffers();
		fboGround->unbindFBO();

		//Textures
		ground1 = new Texture(RESOURCES_PATH"/Heightfield/seamlessSandTest.jpg");
		ground2 = new Texture(RESOURCES_PATH"/Heightfield/seamlessStonesTest.jpg");
		mask = new Texture(RESOURCES_PATH"/Heightfield/terrainTest.png");

		//Camera

	}

	static void configInputHandling(ApplicationState* state){

		IOHandler* io = state->getIOHandler();
	}
}


#endif /* HEIGHTFIELDSCENE_H_ */

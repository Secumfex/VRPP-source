#include <iostream>
#include <string.h>

#include "SomeListeners.h"
#include "Visuals/RenderManager.h"

#include <typeinfo>

int main() {

	//RenderManager Pointer via Singleton
	RenderManager* rm = RenderManager::getInstance();

	//AnimateClearColorListener als FrameListener anhängen
	rm->attachFrameListener(new AnimateClearColorListener());

	rm->libInit();
	rm->manageShaderProgram();
	rm->renderLoop();

	return 0;
};

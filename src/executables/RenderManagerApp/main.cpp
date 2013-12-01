#include <iostream>
#include <string.h>

#include "Visuals/RenderManager.h"
#include "Patterns/Listener.h"

//Test if the RenderManager is being accessed properly
int main() {

	//RenderManager Pointer via Singleton
	RenderManager* rm = RenderManager::getInstance();

	rm->libInit();
	rm->manageShaderProgram();
	rm->renderLoop();

	return 0;
};

#include <iostream>
#include <string.h>

#include "Visuals/RenderManager.h"

//Test if the RenderManager is being accessed properly
int main() {

	RenderManager* rm = RenderManager::getInstance();
	rm->renderLoop();

	return 0;
};

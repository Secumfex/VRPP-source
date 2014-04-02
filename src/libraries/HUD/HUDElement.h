#include <glm/glm.hpp>
#include "Visuals/GraphicsComponent.h"
#ifndef HUDELEMENT_H_
#define HUDELEMENT_H_

class HUDElement {

private:
	glm::vec2 position;
	glm::vec2 size;
	GraphicsComponent* gc;

public:
	HUDElement();
	~HUDElement();
	HUDElement(GraphicsComponent* cg, glm::vec2 position, glm::vec2 psize);
	HUDElement(GraphicsComponent* cg, int x, int y, int sizeX, int sizeY);

};

#endif /* GUIELEMENT_H_ */

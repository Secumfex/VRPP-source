#include "GUIElement.h"

GUIElement::GUIElement() {

}

GUIElement::GUIElement(unsigned int width, unsigned int height,
		unsigned int posX, unsigned int posY) {

	position.x = posX;
	position.y = posY;

	size.x = width;
	size.y = height;
}

GUIElement::GUIElement(glm::vec2 position, glm::vec2 size){
	this->position = position;
	this->size = size;
}

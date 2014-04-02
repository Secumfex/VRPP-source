#include "HUDElement.h"


HUDElement::HUDElement(){
	position.x = 10;
	position.x = 10;
	size.x = 10;
	size.y = 10;
	gc = new GraphicsComponent();

	}

HUDElement::HUDElement(GraphicsComponent* gc, glm::vec2 position, glm::vec2 psize){
	this->position = position;
	this->size = size;
	this->gc = gc;

	}

HUDElement::HUDElement(GraphicsComponent* gc, int x, int y, int sizeX, int sizeY){
	position.x = x;
	position.y = y;
	size.x = sizeX;
	size.y = sizeY;
	this->gc = gc;
	}





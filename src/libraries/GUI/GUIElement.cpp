#include "GuiElement.h"


GuiElement::GuiElement(){
	position.x = 10;
	position.x = 10;
	size.x = 10;
	size.y = 10;

	}

GuiElement::GuiElement(glm::vec2 position, glm::vec2 psize){
	this->position = position;
	this->size = size;

	}

GuiElement::GuiElement(int x, int y, int sizeX, int sizeY){
	position.x = x;
	position.y = y;
	size.x = sizeX;
	size.y = sizeY;
	}





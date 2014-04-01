#include <glm/glm.hpp>
#ifndef GUIELEMENT_H_
#define GUIELEMENT_H_

class GuiElement {

private:
	glm::vec2 position;
	glm::vec2 size;


public:
	GuiElement();
	~GuiElement();
	GuiElement(glm::vec2 position, glm::vec2 psize);
	GuiElement(int x, int y, int sizeX, int sizeY);

};





#endif /* GUIELEMENT_H_ */

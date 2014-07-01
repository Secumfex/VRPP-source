#include <glm/glm.hpp>

#ifndef GUIELEMENT_H_
#define GUIELEMENT_H_

class GUIElement{

private:
	glm::vec2 position;
	glm::vec2 size;

public:
	GUIElement();
	~GUIElement();
	GUIElement(unsigned int width, unsigned int height, unsigned int posX, unsigned int posY);
	GUIElement(glm::vec2 position, glm::vec2 size);



};
#endif /* GUIELEMENT_H_ */

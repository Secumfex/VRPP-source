#include <glm/glm.hpp>
#ifndef GUIELEMENT_H_
#define GUIELEMENT_H_

class GUIElement {

private:
	glm::vec2 position;
	glm::vec2 size;


public:
	GUIElement();
	~GUIElement();
	GUIElement(glm::vec2 position, glm::vec2 psize);
	GUIElement(int x, int y, int sizeX, int sizeY);

};





#endif /* GUIELEMENT_H_ */

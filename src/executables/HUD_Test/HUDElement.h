#ifndef HUDElement_H
#define HUDElement_H

#include <glm/glm.hpp>

class HUDElement {
private:
	glm::vec3 position;
	glm::vec3 offset;
	float scale;

public:
	HUDElement(glm::vec3 pos = glm::vec3(0.0, 0.0, 0.0), glm::vec3 offset = glm::vec3(0.0, 0.0, 0.0), float scale = 1.0f);
	~HUDElement();

	void setPosition(glm::vec3 pos);
	glm::vec3 getPosition();
	void setOffset(glm::vec3 offset);
	void setOffset(float x, float y);
	void setScale(float scale);
	glm::vec3 getOffset();
	float getScale();
};

#endif

#ifndef HUDElement_H
#define HUDElement_H

#include <glm/glm.hpp>
#include "Visuals/Texture.h"

class HUDElement {
private:
	glm::vec3 position;
	glm::vec3 offset;
	float scale;

	Texture* HUD_texture;

public:
	HUDElement(glm::vec3 pos = glm::vec3(0.0, 0.0, 0.0), glm::vec3 offset = glm::vec3(0.0, 0.0, 0.0), float scale = 1.0f);
	~HUDElement();

	void setTexture(Texture* texture);
	Texture* getTexture();
	void setPosition(glm::vec3 pos);
	glm::vec3 getPosition();
	void setOffset(glm::vec3 offset);
	void setOffset(float x, float y);
	void setScale(float scale);
	glm::vec3 getOffset();
	float getScale();
};

#endif

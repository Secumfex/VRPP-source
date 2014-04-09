#ifndef HUDElement_H
#define HUDElement_H

#include <glm/glm.hpp>

using namespace std;

class HUDElement {
private:
	glm::vec3 position;
public:
	HUDElement(glm::vec3 pos);
	~HUDElement();

	void setPosition(glm::vec3 pos);
	glm::vec3 getPosition();
};

#endif

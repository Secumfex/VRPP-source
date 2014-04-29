#ifndef HUDSYSTEM_H
#define HUDSYSTEM_H

#include <vector>
#include <glm/glm.hpp>
#include <Patterns/Subject.h>

#include "HUDElement.h"

class HUDSystem : public Subject{
private:
	std::vector<HUDElement*> HUDElements;

public:
	HUDSystem();
	HUDSystem(std::vector<HUDElement*> hudElements);
	~HUDSystem();

	void addHUDElement(HUDElement* hudElement);
	void removeHUDElement(HUDElement* hudElement);
	std::vector<HUDElement*> getHUDElements();

};

#endif

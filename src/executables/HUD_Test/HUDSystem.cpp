#include "HUDSystem.h"

HUDSystem::HUDSystem(){
}

HUDSystem::HUDSystem(std::vector<HUDElement*> hudElements){
	HUDElements = hudElements;
}

HUDSystem::~HUDSystem(){

}

void HUDSystem::addHUDElement(HUDElement* hudElement){
	HUDElements.push_back(hudElement);
}

std::vector<HUDElement*> HUDSystem::getHUDElements(){
	return HUDElements;
}

void HUDSystem::removeHUDElement(HUDElement* element){
	std::vector< HUDElement* > elementsTemp;
	for ( unsigned int i = 0; i < HUDElements.size(); i++ ){
		if (HUDElements[i] == element){
			continue;
		}else{
			elementsTemp.push_back( HUDElements[i] );
		}
	}
	HUDElements = elementsTemp;
}

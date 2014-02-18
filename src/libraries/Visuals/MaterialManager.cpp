/*
 * MaterialManager.cpp
 *
 *  Created on: 17.02.2014
 *      Author: Dr.M
 */

#include "Visuals/MaterialManager.h"

MaterialManager::MaterialManager() {
	// TODO Auto-generated constructor stub

}

MaterialManager::~MaterialManager() {
	// TODO Auto-generated destructor stub
}
void MaterialManager::makeMaterial(std:: string matName, GraphicsComponent* cg){

	cg->setShadow(true);
	cg->setTransparency(false);

	if(matName.find("genericMaterial") != std::string::npos)
		makeMaterial_generic(cg);
	else if(matName.find("wood") != std::string::npos)
		makeMaterial_wood(cg);
}
void MaterialManager::makeMaterial_generic(GraphicsComponent* cg){

}
void MaterialManager::makeMaterial_wood(GraphicsComponent* cg){

}

/*
 * MaterialManager.h
 *
 *  Created on: 17.02.2014
 *      Author: Dr.M
 */

#ifndef MATERIALMANAGER_H_
#define MATERIALMANAGER_H_

#include "Visuals/GraphicsComponent.h"
#include <string>

class MaterialManager : public Singleton<MaterialManager> {
friend class Singleton<MaterialManager>;
protected:
	MaterialManager();
public:
	virtual ~MaterialManager();

	void makeMaterial(std:: string matName, GraphicsComponent* cg);

private:
	void makeMaterial_generic(GraphicsComponent* cg);
	void makeMaterial_wood(GraphicsComponent* cg);
	void makeMaterial_metal(GraphicsComponent* cg);

};

#endif /* MATERIALMANAGER_H_ */

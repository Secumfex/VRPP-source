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

	void makeMaterial(std:: string matName, GraphicsComponent* gc);

private:
	void makeMaterial_generic(GraphicsComponent* gc);
	void makeMaterial_wood(GraphicsComponent* gc);
	void makeMaterial_metal(GraphicsComponent* gc);
    void makeMaterial_glas(GraphicsComponent* gc);
    void makeMaterial_plastic(GraphicsComponent* gc);
    void makeMaterial_brass(GraphicsComponent* gc);
    
    void makeMaterial_bronze(GraphicsComponent* gc);
    void makeMaterial_chrome(GraphicsComponent* gc);
    void makeMaterial_copper(GraphicsComponent* gc);
    void makeMaterial_gold(GraphicsComponent* gc);
    void makeMaterial_silver(GraphicsComponent* gc);
    void makeMaterial_rubber(GraphicsComponent* gc);
    
    //==================================
    void makaMaterial_shiny(GraphicsComponent* gc, std::string amount);
    void makeMaterial_transparency(GraphicsComponent* gc, std::string amount);
    void makeMaterial_black(GraphicsComponent* gc);

};

#endif /* MATERIALMANAGER_H_ */

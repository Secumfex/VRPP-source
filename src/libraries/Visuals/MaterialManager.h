/*
 * MaterialManager.h
 *
 *  Created on: 17.02.2014
 *      Author: Dr.M
 */

#ifndef MATERIALMANAGER_H_
#define MATERIALMANAGER_H_

#include "Visuals/GraphicsComponent.h"
#include "TextureManager.h"
#include <string>

class MaterialManager : public Singleton<MaterialManager> {
friend class Singleton<MaterialManager>;
protected:
	MaterialManager();
public:
	virtual ~MaterialManager();

	GraphicsComponent* makeMaterial(std:: string matName, GraphicsComponent* gc);

private:
    
	void makeMaterial_generic(GraphicsComponent* gc);
    /*
	void makeMaterial_wood(GraphicsComponent* gc);

     */
    GraphicsComponent* makeMaterial_brass(GraphicsComponent* gc);
    GraphicsComponent* makeMaterial_bronze(GraphicsComponent* gc);
    GraphicsComponent* makeMaterial_chrome(GraphicsComponent* gc);
    GraphicsComponent* makeMaterial_copper(GraphicsComponent* gc);
    GraphicsComponent* makeMaterial_gold(GraphicsComponent* gc);
    GraphicsComponent* makeMaterial_silver(GraphicsComponent* gc);
    GraphicsComponent* makeMaterial_glass(GraphicsComponent* gc);

    //==================================
    /*
    void makeMaterial_shiny(GraphicsComponent* gc, std::string amount);
    void makeMaterial_transparency(GraphicsComponent* gc, std::string amount);
    void makeMaterial_black(GraphicsComponent* gc);
     */

};

#endif /* MATERIALMANAGER_H_ */

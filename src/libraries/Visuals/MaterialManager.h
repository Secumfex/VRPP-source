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

	void makeMaterial(std:: string matName, GraphicsComponent* gc);

private:
    
    /*
	void makeMaterial_wood(GraphicsComponent* gc);

     */

	//basic material
	void makeMaterial_plastic(GraphicsComponent* gc);
	void makeMaterial_wood(GraphicsComponent* gc);
	void makeMaterial_stone(GraphicsComponent* gc);
	void makeMaterial_metal(GraphicsComponent* gc);
	void makeMaterial_brass(GraphicsComponent* gc);
    void makeMaterial_bronze(GraphicsComponent* gc);
    void makeMaterial_chrome(GraphicsComponent* gc);
    void makeMaterial_copper(GraphicsComponent* gc);
    void makeMaterial_gold(GraphicsComponent* gc);
    void makeMaterial_silver(GraphicsComponent* gc);
    void makeMaterial_glass(GraphicsComponent* gc);

    void makeMaterial_genericMaterial(GraphicsComponent* gc);


    //color material
    void makeMaterial_none(GraphicsComponent* gc);
    void makeMaterial_brighter(GraphicsComponent* gc);
    void makeMaterial_darker(GraphicsComponent* gc);
    void makeMaterial_black(GraphicsComponent* gc);
    void makeMaterial_white(GraphicsComponent* gc);
    void makeMaterial_red(GraphicsComponent* gc);
    void makeMaterial_blue(GraphicsComponent* gc);
    void makeMaterial_green(GraphicsComponent* gc);
    void makeMaterial_yellow(GraphicsComponent* gc);

    void makeMaterial_genericColor(GraphicsComponent* gc);

    //specification material
    void makeMaterial_polished(GraphicsComponent* gc);
    void makeMaterial_rough(GraphicsComponent* gc);
    void makeMaterial_mat(GraphicsComponent* gc);

    void makeMaterial_genericSpecific(GraphicsComponent* gc);


    //==================================
    /*
    void makeMaterial_shiny(GraphicsComponent* gc, std::string amount);
    void makeMaterial_transparency(GraphicsComponent* gc, std::string amount);
    void makeMaterial_black(GraphicsComponent* gc);
     */

};

#endif /* MATERIALMANAGER_H_ */

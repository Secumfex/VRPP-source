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
	/** \brief constructor
	 *
	 */
	MaterialManager();
public:
	/** \brief destructor
	 *
	 */
	virtual ~MaterialManager();


	/** \brief !docu pls!
	 *
	 * @param matName
	 * @param gc
	 */
	void makeMaterial(std:: string matName, GraphicsComponent* gc);

	/** \brief !docu pls!
	 *
	 * @param matName
	 * @param gc
	 */

	void makeMaterial(std:: string matName, vector<GraphicsComponent*> gc);

private:

    /*
	void makeMaterial_wood(GraphicsComponent* gc);

     */

	//basic material

	///sets the material properties of a graphic component to plastic
	void makeMaterial_plastic(GraphicsComponent* gc);
	///sets the material properties of a graphic component to wood
	void makeMaterial_wood(GraphicsComponent* gc);
	///sets the material properties of a graphic component to stone
	void makeMaterial_stone(GraphicsComponent* gc);
	///sets the material properties of a graphic component to metal
	void makeMaterial_metal(GraphicsComponent* gc);
	///sets the material properties of a graphic component to brass
	void makeMaterial_brass(GraphicsComponent* gc);
	///sets the material properties of a graphic component to bronze
	void makeMaterial_bronze(GraphicsComponent* gc);
	///sets the material properties of a graphic component to chrome
	void makeMaterial_chrome(GraphicsComponent* gc);
	///sets the material properties of a graphic component to copper
	void makeMaterial_copper(GraphicsComponent* gc);
	///sets the material properties of a graphic component to gold
	void makeMaterial_gold(GraphicsComponent* gc);
	///sets the material properties of a graphic component to silver
	void makeMaterial_silver(GraphicsComponent* gc);
	///sets the material properties of a graphic component to glass
	void makeMaterial_glass(GraphicsComponent* gc);
	///sets the material properties of a graphic component to a generic material
    void makeMaterial_genericMaterial(GraphicsComponent* gc);

    //color material
    ///sets the color of a graphic component to none
    void makeMaterial_none(GraphicsComponent* gc);
    ///sets the color of a graphic component to brighter
    void makeMaterial_brighter(GraphicsComponent* gc);
    ///sets the color of a graphic component to darker
    void makeMaterial_darker(GraphicsComponent* gc);
    ///sets the color of a graphic component to black
    void makeMaterial_black(GraphicsComponent* gc);
    ///sets the color of a graphic component to white
    void makeMaterial_white(GraphicsComponent* gc);
    ///sets the color of a graphic component to red
    void makeMaterial_red(GraphicsComponent* gc);
    ///sets the color of a graphic component to blue
    void makeMaterial_blue(GraphicsComponent* gc);
    ///sets the color of a graphic component to green
    void makeMaterial_green(GraphicsComponent* gc);
    ///sets the color of a graphic component to yellow
    void makeMaterial_yellow(GraphicsComponent* gc);
    ///sets the color of a graphic component to a generic color
    void makeMaterial_genericColor(GraphicsComponent* gc);

    //specification material
    ///sets the material properties of a graphic component to polished
    void makeMaterial_polished(GraphicsComponent* gc);
    ///sets the material properties of a graphic component to rough
    void makeMaterial_rough(GraphicsComponent* gc);
    ///sets the material properties of a graphic component to mat
    void makeMaterial_mat(GraphicsComponent* gc);
    ///sets the material properties of a graphic component to generic
    void makeMaterial_genericSpecific(GraphicsComponent* gc);
    //==================================
    /*
    void makeMaterial_shiny(GraphicsComponent* gc, std::string amount);
    void makeMaterial_transparency(GraphicsComponent* gc, std::string amount);
    void makeMaterial_black(GraphicsComponent* gc);
     */



};

#endif /* MATERIALMANAGER_H_ */

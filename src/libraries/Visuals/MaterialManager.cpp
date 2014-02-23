/*
 * MaterialManager.cpp
 *
 *  Created on: 17.02.2014
 *      Author: Dr.M
 */

#include "MaterialManager.h"

MaterialManager::MaterialManager() {
	// TODO Auto-generated constructor stub

}

MaterialManager::~MaterialManager() {
	// TODO Auto-generated destructor stub
}
void MaterialManager::makeMaterial(std:: string matName, GraphicsComponent* gc){

	//gc->setShadow(true);
	//gc->setTransparency(false);

	if(matName.find("genericMaterial") != std::string::npos)
		makeMaterial_generic(gc);
	if(matName.find("wood") != std::string::npos)
		makeMaterial_wood(gc);
    // brass - Messing
    if(matName.find("brass") != std::string::npos)
		makeMaterial_brass(gc);
//    bronze - Bronze
    if(matName.find("bronze") != std::string::npos)
		makeMaterial_bronze(gc);
//    chrome - Chrom
    if(matName.find("chrome") != std::string::npos)
		makeMaterial_chrome(gc);
//    copper - Kupfer
    if(matName.find("copper") != std::string::npos)
		makeMaterial_copper(gc);
//    gold - Gold
    if(matName.find("gold") != std::string::npos)
		makeMaterial_gold(gc);
//    silver - Silber
    if(matName.find("silver") != std::string::npos)
		makeMaterial_silver(gc);
    if(matName.find("glas") != std::string::npos)
		makeMaterial_glas(gc);
//    plastic - Plastik
    if(matName.find("plastic") != std::string::npos)
		makeMaterial_plastic(gc);
//    rubber - Gummi
    if(matName.find("rubber") != std::string::npos)
		makeMaterial_rubber(gc);
    
    
    //=================================================
    if(matName.find("shiny") != std::string::npos)
		makaMaterial_shiny(gc,matName);
    if(matName.find("transparency") != std::string::npos)
		makeMaterial_transparency(gc,matName);
    if(matName.find("black") != std::string::npos)
        makeMaterial_black(gc);
    
    //    emerald - Smaragd(grün)
    
    //    jade - Jade (grün)
    //    obsidian - Obsidian (schwarz)
    //    pearl - Perle
    
    
    //    ruby - Rubin (rot)
    
    //    turquoise - Türkis
    
}
void MaterialManager::makeMaterial_generic(GraphicsComponent* gc){

}
void MaterialManager::makeMaterial_wood(GraphicsComponent* gc){

}

void MaterialManager::makeMaterial_glas(GraphicsComponent* gc){
    
}
void MaterialManager::makeMaterial_plastic(GraphicsComponent* gc){
    
}

// Messing
void MaterialManager::makeMaterial_brass(GraphicsComponent* gc){
    gc->setEmission(false);
    gc->setShadow(true);
    gc->setTransparency(false);
    gc->getMaterial()->setAmbient(glm::vec3(0.329412f,0.223529f,0.027451f));
    gc->getMaterial()->setDiffuse(glm::vec3(0.780392f,0.568627f,0.113725f));
    gc->getMaterial()->setSpecular(glm::vec3(0.992157f,0.941176f,0.807843f));
    gc->getMaterial()->setShininess(27.89743616f);
}

// Bronze
void MaterialManager::makeMaterial_bronze(GraphicsComponent* gc){
    gc->setEmission(false);
    gc->setShadow(true);
    gc->setTransparency(false);
    gc->getMaterial()->setAmbient(glm::vec3(0.2125f,0.1275f,0.054f));
    gc->getMaterial()->setDiffuse(glm::vec3(0.714f,0.4284f,0.18144f));
    gc->getMaterial()->setSpecular(glm::vec3(0.393548f,0.271906f,0.166721f));
    gc->getMaterial()->setShininess(25.6f);
}

// Chrom
void MaterialManager::makeMaterial_chrome(GraphicsComponent* gc){
    gc->setEmission(false);
    gc->setShadow(true);
    gc->setTransparency(false);
    gc->getMaterial()->setAmbient(glm::vec3(0.25f,0.25f,0.25f));
    gc->getMaterial()->setDiffuse(glm::vec3(0.4f,0.4f,0.4f));
    gc->getMaterial()->setSpecular(glm::vec3(0.774597f,0.774597f,0.774597f));
    gc->getMaterial()->setShininess(76.8f);
}

// Kupfer
void MaterialManager::makeMaterial_copper(GraphicsComponent* gc){
    gc->setEmission(false);
    gc->setShadow(true);
    gc->setTransparency(false);
    gc->getMaterial()->setAmbient(glm::vec3(0.19125f,0.0735f,0.0225f));
    gc->getMaterial()->setDiffuse(glm::vec3(0.7038f,0.27048f,0.0828f));
    gc->getMaterial()->setSpecular(glm::vec3(0.256777f,0.137622f,0.086014f));
    gc->getMaterial()->setShininess(12.8f);
}

// Gold
void MaterialManager::makeMaterial_gold(GraphicsComponent* gc){
    gc->setEmission(false);
    gc->setShadow(true);
    gc->setTransparency(false);
    gc->getMaterial()->setAmbient(glm::vec3(0.24725f,0.1995f,0.0745f));
    gc->getMaterial()->setDiffuse(glm::vec3(0.75164f,0.60648f,0.22648f));
    gc->getMaterial()->setSpecular(glm::vec3(0.628281f,0.555802f,0.366065f));
    gc->getMaterial()->setShininess(51.2f);
}

// Silber
void MaterialManager::makeMaterial_silver(GraphicsComponent* gc){
    gc->setEmission(false);
    gc->setShadow(true);
    gc->setTransparency(false);
    gc->getMaterial()->setAmbient(glm::vec3(0.19225f,0.19225f,0.19225f));
    gc->getMaterial()->setDiffuse(glm::vec3(0.50754f,0.50754f,0.50754f));
    gc->getMaterial()->setSpecular(glm::vec3(0.508273f,0.508273f,0.508273f));
    gc->getMaterial()->setShininess(51.2f);
}

// Gummi
void MaterialManager::makeMaterial_rubber(GraphicsComponent* gc){
    gc->setEmission(false);
    gc->setShadow(true);
    gc->setTransparency(false);
    gc->getMaterial()->setShininess(10.0f);
    std::cout<<"\nMaterial 'rubber' set";
}

// Schwarz
void MaterialManager::makeMaterial_black(GraphicsComponent* gc){
    gc->getMaterial()->setAmbient(glm::vec3(0.02f,0.02f,0.02f));
    gc->getMaterial()->setDiffuse(glm::vec3(0.01f,0.01f,0.01f));
    gc->getMaterial()->setSpecular(glm::vec3(0.4f,0.4f,0.4f));
    std::cout<<"\nColor 'black' set";
}


/*	std::string satz = "hallo peter du oller kneter";
 size_t found01 = satz.find("peter");
 size_t found02 = satz.find("abudabi");
 
 if (found01!=std::string::npos)
 std::cout << "find01: " << found01 << std::endl ;
 if (found02!=std::string::npos)
 std:: cout << "find02: " << found02 << std::endl;
 */
/*
 * MaterialManager.cpp
 *
 *  Created on: 17.02.2014
 *      Author: Dr.M
 */

#include "MaterialManager.h"

MaterialManager::MaterialManager() {
    
    }

MaterialManager::~MaterialManager() {
    
	}

GraphicsComponent* MaterialManager::makeMaterial(std:: string matName, GraphicsComponent* gc){

    // TODO: _custom_ -> do nothing!
    
    
	if(matName.find("genericMaterial") != std::string::npos){
		makeMaterial_generic(gc);
        return NULL;}
   /*
	if(matName.find("wood") != std::string::npos)
		makeMaterial_wood(gc);
    */
    
    // brass - Messing
    if(matName.find("brass") != std::string::npos)
		return makeMaterial_brass(gc);
    // bronze - Bronze
    if(matName.find("bronze") != std::string::npos)
		return makeMaterial_bronze(gc);
    // chrome - Chrom
    if(matName.find("chrome") != std::string::npos)
		return makeMaterial_chrome(gc);
    // copper - Kupfer
    if(matName.find("copper") != std::string::npos)
		return makeMaterial_copper(gc);
    // gold - Gold
    if(matName.find("gold") != std::string::npos)
		return makeMaterial_gold(gc);
    // silver - Silber
    if(matName.find("silver") != std::string::npos)
		return makeMaterial_silver(gc);
    // glass - Glas
    if(matName.find("glass") != std::string::npos)
		return makeMaterial_glass(gc);

    //=================================================
   /* if(matName.find("shiny") != std::string::npos)
		makeMaterial_shiny(gc,matName);
    if(matName.find("transparency") != std::string::npos)
	    makeMaterial_transparency(gc,matName);
    
    */
    
    //    emerald - Smaragd(grün)
    
    //    jade - Jade (grün)
    //    obsidian - Obsidian (schwarz)
    //    pearl - Perl
    //    ruby - Rubin (rot)
    //    turquoise - Türkis
    return NULL;
}

void MaterialManager::makeMaterial_generic(GraphicsComponent* gc){
    
}
/*
void MaterialManager::makeMaterial_wood(GraphicsComponent* gc){

}
*/

// Messing
GraphicsComponent* MaterialManager::makeMaterial_brass(GraphicsComponent* gc){
    gc->setEmission(false);
    gc->setShadow(true);
    gc->setTransparency(false);
    gc->getMaterial()->setAmbient(glm::vec3(0.329412f,0.223529f,0.027451f));
    gc->getMaterial()->setDiffuse(glm::vec3(0.780392f,0.568627f,0.113725f));
    gc->getMaterial()->setSpecular(glm::vec3(0.992157f,0.941176f,0.807843f));
    gc->getMaterial()->setShininess(27.89743616f/1000.0f);
    std::cout<<"\n'brass' set"<<endl;
    return gc;
}

// Bronze
GraphicsComponent* MaterialManager::makeMaterial_bronze(GraphicsComponent* gc){
    gc->setEmission(false);
    gc->setShadow(true);
    gc->setTransparency(false);
    gc->getMaterial()->setAmbient(glm::vec3(0.2125f,0.1275f,0.054f));
    gc->getMaterial()->setDiffuse(glm::vec3(0.714f,0.4284f,0.18144f));
    gc->getMaterial()->setSpecular(glm::vec3(0.393548f,0.271906f,0.166721f));
    gc->getMaterial()->setShininess(25.6f/1000.0f);

    Texture *tex_temp = new Texture();
    tex_temp = new Texture(RESOURCES_PATH "/bronze.jpg");
    gc->getMaterial()->setDiffuseMap(tex_temp);
    std::cout<<"\n'bronze' set"<<endl;
    return gc;
}

// Chrom
GraphicsComponent* MaterialManager::makeMaterial_chrome(GraphicsComponent* gc){
    gc->setEmission(false);
    gc->setShadow(true);
    gc->setTransparency(false);
    gc->getMaterial()->setAmbient(glm::vec3(0.25f,0.25f,0.25f));
    gc->getMaterial()->setDiffuse(glm::vec3(0.4f,0.4f,0.4f));
    gc->getMaterial()->setSpecular(glm::vec3(0.774597f,0.774597f,0.774597f));
    gc->getMaterial()->setShininess(76.8f/1000.0f);
    std::cout<<"\n'chrome' set"<<endl;
    return gc;
}

// Kupfer
GraphicsComponent* MaterialManager::makeMaterial_copper(GraphicsComponent* gc){
    gc->setEmission(false);
    gc->setShadow(true);
    gc->setTransparency(false);
    gc->getMaterial()->setAmbient(glm::vec3(0.19125f,0.0735f,0.0225f));
    gc->getMaterial()->setDiffuse(glm::vec3(0.7038f,0.27048f,0.0828f));
    gc->getMaterial()->setSpecular(glm::vec3(0.256777f,0.137622f,0.086014f));
    gc->getMaterial()->setShininess(12.8f);
    std::cout<<"\n'copper' set"<<endl;
    return gc;
}

// Gold
GraphicsComponent* MaterialManager::makeMaterial_gold(GraphicsComponent* gc){
    gc->setEmission(false);
    gc->setShadow(true);
    gc->setTransparency(false);
    gc->getMaterial()->setAmbient(glm::vec3(0.24725f,0.1995f,0.0745f));
    gc->getMaterial()->setDiffuse(glm::vec3(0.75164f,0.60648f,0.22648f));
    gc->getMaterial()->setSpecular(glm::vec3(0.628281f,0.555802f,0.366065f));
    gc->getMaterial()->setShininess(51.2f);
    std::cout<<"\n'gold' set"<<endl;
    return gc;
}

// Silber
GraphicsComponent* MaterialManager::makeMaterial_silver(GraphicsComponent* gc){
    gc->setEmission(false);
    gc->setShadow(true);
    gc->setTransparency(false);
    gc->getMaterial()->setAmbient(glm::vec3(0.19225f,0.19225f,0.19225f));
    gc->getMaterial()->setDiffuse(glm::vec3(0.50754f,0.50754f,0.50754f));
    gc->getMaterial()->setSpecular(glm::vec3(0.508273f,0.508273f,0.508273f));
    gc->getMaterial()->setShininess(51.2f);
    std::cout<<"\n'silver' set"<<endl;
    return gc;
}

// Glas
GraphicsComponent* MaterialManager::makeMaterial_glass(GraphicsComponent* gc){
    gc->setEmission(false);
    gc->setShadow(false);
    gc->setTransparency(false);
    gc->getMaterial()->setAmbient(glm::vec3(0.0f));
    gc->getMaterial()->setDiffuse(glm::vec3(0.588235f,0.670588f,0.729412f));
    gc->getMaterial()->setSpecular(glm::vec3(0.9f));
    gc->getMaterial()->setShininess(150.0f/1000.0f);
    std::cout<<"\n'glass' set"<<endl;
    return gc;
}


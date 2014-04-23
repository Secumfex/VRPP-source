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


void MaterialManager::makeMaterial(std:: string matName, GraphicsComponent* gc){


 //first round - basic search for material


	// brass - Messing
	if(matName.find("brass") != std::string::npos){
		 makeMaterial_brass(gc);}

	// bronze - Bronze
    else if(matName.find("bronze") != std::string::npos){
		 makeMaterial_bronze(gc);}

    // chrome - Chrom
    else if(matName.find("chrome") != std::string::npos){
		 makeMaterial_chrome(gc);}

    // copper - Kupfer
    else if(matName.find("copper") != std::string::npos){
		 makeMaterial_copper(gc);}

	// gold - Gold
    else if(matName.find("gold") != std::string::npos){
		 makeMaterial_gold(gc);}

	// silver - Silber
    else if(matName.find("silver") != std::string::npos){
		 makeMaterial_silver(gc);
		 return;}

	// glass - Glas
    else if(matName.find("glass") != std::string::npos){
		 makeMaterial_glass(gc);}

	// plastic - Plastik
	    else if(matName.find("plastic") != std::string::npos){
			 makeMaterial_plastic(gc);}

	// wood - Holz
	    else if(matName.find("wood") != std::string::npos){
			 makeMaterial_wood(gc);}

	// stone - Stein
	    else if(matName.find("stone") != std::string::npos){
			 makeMaterial_stone(gc);}

	// metal - Metall
	    else if(matName.find("metal") != std::string::npos){
			 makeMaterial_metal(gc);}

   //if nothing is found
    else {makeMaterial_genericMaterial(gc);}


//second round - color of material


	if(matName.find("black") != std::string::npos){
			 makeMaterial_black(gc);}

	else if(matName.find("white") != std::string::npos){
		makeMaterial_white(gc);
	}

	else if(matName.find("darker") != std::string::npos){
			makeMaterial_darker(gc);
		}

	else if(matName.find("brighter") != std::string::npos){
			makeMaterial_brighter(gc);
		}

	else if(matName.find("red") != std::string::npos){
			makeMaterial_red(gc);
		}

	else if(matName.find("green") != std::string::npos){
			makeMaterial_green(gc);
		}

	else if(matName.find("yellow") != std::string::npos){
			makeMaterial_yellow(gc);
		}

	else if(matName.find("blue") != std::string::npos){
			makeMaterial_blue(gc);
		}

	else if(matName.find("none") != std::string::npos){
            makeMaterial_none(gc);
			}

	else{ makeMaterial_genericColor(gc);}



	//third round -  specific definition of material

	if(matName.find("polished") != std::string::npos){
            makeMaterial_polished(gc);
    }

	else if(matName.find("rough") != std::string::npos){
            makeMaterial_rough(gc);
	}

	else if(matName.find("matted") != std::string::npos){
            makeMaterial_mat(gc);
    }

	else if(matName.find("none") != std::string::npos){
            makeMaterial_none(gc);}


	else {makeMaterial_genericSpecific(gc);}
}



//basic

	void MaterialManager::makeMaterial_plastic(GraphicsComponent* gc){
    gc->setEmission(false);
    gc->setShadow(true);
    gc->setTransparency(false);
    gc->getMaterial()->setSpecular(glm::vec3(0.992157f,0.941176f,0.807843f));
    gc->getMaterial()->setShininess(27.89743616f/1000.0f);
    gc->getMaterial()->setName("Plastic");
    std::cout<<"\n'plastic' set"<<endl;
	}

	void MaterialManager::makeMaterial_wood(GraphicsComponent* gc){
	    gc->setEmission(false);
	    gc->setShadow(true);
	    gc->setTransparency(false);

	    gc->getMaterial()->setAmbient(glm::vec3(0.329412f,0.223529f,0.027451f));
	    gc->getMaterial()->setDiffuse(glm::vec3(0.54f,0.26f,0.07f));

	    gc->getMaterial()->setSpecular(glm::vec3(0.992157f,0.941176f,0.807843f));
	    gc->getMaterial()->setShininess(27.89743616f/1000.0f);
	    gc->getMaterial()->setName("Wood");
	    std::cout<<"'wood' set"<<endl;
		}

	void MaterialManager::makeMaterial_stone(GraphicsComponent* gc){
	    gc->setEmission(false);
	    gc->setShadow(true);
	    gc->setTransparency(false);

	    gc->getMaterial()->setAmbient(glm::vec3(0.329412f,0.223529f,0.027451f));
	    gc->getMaterial()->setDiffuse(glm::vec3(0.48f,0.48f,0.48f));

	    gc->getMaterial()->setSpecular(glm::vec3(0.992157f,0.941176f,0.807843f));
	    gc->getMaterial()->setShininess(27.89743616f/1000.0f);
	    gc->getMaterial()->setName("Stone");
	    std::cout<<"'stone' set"<<endl;
		}

	void MaterialManager::makeMaterial_metal(GraphicsComponent* gc){
	    gc->setEmission(false);
	    gc->setShadow(true);
	    gc->setTransparency(false);
	    gc->getMaterial()->setSpecular(glm::vec3(0.992157f,0.941176f,0.807843f));
	    gc->getMaterial()->setShininess(27.89743616f/1000.0f);
	    gc->getMaterial()->setName("Metal");
	    std::cout<<"'metal' set"<<endl;
		}


// Messing
	void MaterialManager::makeMaterial_brass(GraphicsComponent* gc){
    gc->setEmission(false);
    gc->setShadow(true);
    gc->setTransparency(false);
    gc->getMaterial()->setAmbient(glm::vec3(0.329412f,0.223529f,0.027451f));
    gc->getMaterial()->setDiffuse(glm::vec3(0.780392f,0.568627f,0.113725f));
    gc->getMaterial()->setSpecular(glm::vec3(0.992157f,0.941176f,0.807843f));
    gc->getMaterial()->setShininess(27.89743616f/1000.0f);
    gc->getMaterial()->setName("Brass");
    std::cout<<"'brass' set"<<endl;

}



// Bronze
	void MaterialManager::makeMaterial_bronze(GraphicsComponent* gc){
    gc->setEmission(false);
    gc->setShadow(true);
    gc->setTransparency(false);
    gc->getMaterial()->setAmbient(glm::vec3(0.2125f,0.1275f,0.054f));
    gc->getMaterial()->setDiffuse(glm::vec3(0.714f,0.4284f,0.18144f));
    gc->getMaterial()->setSpecular(glm::vec3(0.393548f,0.271906f,0.166721f));
    gc->getMaterial()->setShininess(25.6f/1000.0f);
    gc->getMaterial()->setName("Bronze");



    /*
    Texture *tex_temp = new Texture();
    tex_temp = new Texture(RESOURCES_PATH "/bronze.jpg");
    gc->getMaterial()->setDiffuseMap(tex_temp);

     */
    std::cout<<"'bronze' set"<<endl;
}

// Chrom
	void MaterialManager::makeMaterial_chrome(GraphicsComponent* gc){
    gc->setEmission(false);
    gc->setShadow(true);
    gc->setTransparency(false);
    gc->getMaterial()->setAmbient(glm::vec3(0.25f,0.25f,0.25f));

    gc->getMaterial()->setDiffuse(glm::vec3(0.4f,0.4f,0.4f));

    gc->getMaterial()->setSpecular(glm::vec3(0.774597f,0.774597f,0.774597f));
    gc->getMaterial()->setShininess(76.8f/1000.0f);
    gc->getMaterial()->setName("Chrome");
    std::cout<<"'chrome' set"<<endl;
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
    gc->getMaterial()->setName("Copper");
    std::cout<<"'copper' set"<<endl;

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
    gc->getMaterial()->setName("Gold");
    std::cout<<"'gold' set"<<endl;

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
    gc->getMaterial()->setName("Silver");
    std::cout<<"'silver' set"<<endl;

}

// Glas
	void MaterialManager::makeMaterial_glass(GraphicsComponent* gc){
    gc->setEmission(false);
    gc->setShadow(false);
    gc->setTransparency(true);
    gc->getMaterial()->setAmbient(glm::vec3(0.01f));
    gc->getMaterial()->setDiffuse(glm::vec3(0.588235f,0.670588f,0.729412f));
    gc->getMaterial()->setSpecular(glm::vec3(0.9f));
    gc->getMaterial()->setShininess(150.0f/1000.0f);
    gc->getMaterial()->setName("Glass");
    std::cout<<"'glass' set"<<endl;

}

//Generisch
	void MaterialManager::makeMaterial_genericMaterial(GraphicsComponent* gc){
    gc->setEmission(false);
    gc->setShadow(true);
    gc->setTransparency(false);
    gc->getMaterial()->setAmbient(glm::vec3(0.1f));
    gc->getMaterial()->setDiffuse(glm::vec3(0.01f,0.01f,0.01f));

    gc->getMaterial()->setSpecular(glm::vec3(0.0f,0.3f,0.9f));

    gc->getMaterial()->setShininess(32.0f);
    gc->getMaterial()->setName("Generic");
    std::cout<<"'generic material' set"<<endl;

}
//for second round

	void MaterialManager::makeMaterial_none(GraphicsComponent* gc){
		    std::cout<<"'none' set"<<endl;
		}


	void MaterialManager::makeMaterial_darker(GraphicsComponent* gc){
	    gc->getMaterial()->setAmbient(glm::vec3(gc->getMaterial()->getAmbient()) * 0.7f);

	    gc->getMaterial()->setDiffuse(glm::vec3(gc->getMaterial()->getDiffuse()) *0.7f);
	    gc->getMaterial()->setSpecular(glm::vec3(0.3f));
	  	gc->getMaterial()->setShininess((gc->getMaterial()->getShininess())/1000.0f*0.7f);

	    std::cout<<"'darker' set"<<endl;
	}

	void MaterialManager::makeMaterial_brighter(GraphicsComponent* gc){
		    gc->getMaterial()->setAmbient(glm::vec3(gc->getMaterial()->getAmbient()) * 1.3f);
		    gc->getMaterial()->setDiffuse(glm::vec3(gc->getMaterial()->getDiffuse()) * 1.3f);

		 //   gc->getMaterial()->setSpecular(glm::vec3(0.3f));
		  	//gc->getMaterial()->setShininess((gc->getMaterial()->getShininess())/1000.0f*1.3f);

		    std::cout<<"'brighter' set"<<endl;
		}

	void MaterialManager::makeMaterial_black(GraphicsComponent* gc){
    gc->getMaterial()->setAmbient(glm::vec3(0.01f));
    gc->getMaterial()->setDiffuse(glm::vec3(0.01f,0.01f,0.01f));
    std::cout<<"'black' set"<<endl;

	}


	void MaterialManager::makeMaterial_white(GraphicsComponent* gc){
	    gc->getMaterial()->setAmbient(glm::vec3(0.9f));
	    gc->getMaterial()->setDiffuse(glm::vec3(0.9f,0.9f,0.9f));
	    std::cout<<"'white' set"<<endl;
	}

	void MaterialManager::makeMaterial_red(GraphicsComponent* gc){
		    gc->getMaterial()->setAmbient(glm::vec3(0.9f));
		    gc->getMaterial()->setDiffuse(glm::vec3(0.9f,0.01f,0.01f));
		    std::cout<<"'red' set"<<endl;
		}

	void MaterialManager::makeMaterial_green(GraphicsComponent* gc){
		    gc->getMaterial()->setAmbient(glm::vec3(0.9f));
		    gc->getMaterial()->setDiffuse(glm::vec3(0.01f,0.9f,0.01f));
		    std::cout<<"'green' set"<<endl;
		}

	void MaterialManager::makeMaterial_blue(GraphicsComponent* gc){
		    gc->getMaterial()->setAmbient(glm::vec3(0.9f));
		    gc->getMaterial()->setDiffuse(glm::vec3(0.01f,0.01f,0.9f));
		    std::cout<<"'blue' set"<<endl;
		}

	void MaterialManager::makeMaterial_yellow(GraphicsComponent* gc){
		    gc->getMaterial()->setAmbient(glm::vec3(0.9f));
		    gc->getMaterial()->setDiffuse(glm::vec3(0.9f,0.9f,0.01f));
		    std::cout<<"'yellow' set"<<endl;
		}

	void MaterialManager::makeMaterial_genericColor(GraphicsComponent* gc){

	    gc->getMaterial()->setAmbient(glm::vec3(0.5f));
	    gc->getMaterial()->setDiffuse(glm::vec3(0.02f,0.02f,0.02f));
	    gc->getMaterial()->setSpecular(glm::vec3(0.3f));
	    gc->getMaterial()->setShininess(20.0f);

	    std::cout<<"'generic color' set"<<endl;
	}


	//for third round

	void MaterialManager::makeMaterial_polished(GraphicsComponent* gc){
	 //   gc->getMaterial()->setAmbient(glm::vec3(0.01f));
	//    gc->getMaterial()->setDiffuse(glm::vec3(0.01f,0.01f,0.01f));
	    gc->getMaterial()->setSpecular(glm::vec3(0.75f));

	    gc->getMaterial()->setShininess(50.0f/1000.0f);

	    std::cout<<"'polished' set"<<endl;
	}

	void MaterialManager::makeMaterial_rough(GraphicsComponent* gc){
//		    gc->getMaterial()->setAmbient(glm::vec3(0.01f));
//		    gc->getMaterial()->setDiffuse(glm::vec3(0.01f,0.01f,0.01f));

		    gc->getMaterial()->setSpecular(glm::vec3(0.1f));
		    gc->getMaterial()->setShininess(1000.0f/1000.0f);

		    std::cout<<"'rough' set"<<endl;
		}

	void MaterialManager::makeMaterial_mat(GraphicsComponent* gc){
			  //  gc->getMaterial()->setAmbient(glm::vec3(0.01f));
			 //   gc->getMaterial()->setDiffuse(glm::vec3(0.01f,0.01f,0.01f));

			    gc->getMaterial()->setSpecular(gc->getMaterial()->getDiffuse());
			    gc->getMaterial()->setShininess(15.0f/1000.f);

			    std::cout<<"'mat' set"<<endl;
			}

	void MaterialManager::makeMaterial_genericSpecific(GraphicsComponent* gc){
//		    gc->getMaterial()->setAmbient(glm::vec3(0.01f));
//		    gc->getMaterial()->setDiffuse(glm::vec3(0.01f,0.01f,0.01f));
//		    gc->getMaterial()->setSpecular(glm::vec3(0.5f));
//		    gc->getMaterial()->setShininess(32.0f);
		    std::cout<<"'generic specification' set"<<endl;
		}


	void MaterialManager::makeMaterial(std:: string matName, vector<GraphicsComponent*> gc){




		for(vector<GraphicsComponent*>::iterator it = gc.begin();it != gc.end(); ++it){
			MaterialManager::makeMaterial(matName,*it);
		}
	}



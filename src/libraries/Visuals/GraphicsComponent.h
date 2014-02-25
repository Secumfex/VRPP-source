#ifndef GRAPHICSCOMPONENT_H
#define GRAPHICSCOMPONENT_H
#include <vector>
#include "Visuals/Resource.h"

/*! @brief GraphicsComponent .
 *
 *	@todo detailed description please
 */
class GraphicsComponent{
public:

	void setMesh(Mesh* mesh);	//!< @todo description please use "[at]param" to describe which constraints exist to the parameter
	void setMaterial(Material* material);	//!< @todo description please use "[at]param" to describe which constraints exist to the parameter
	Mesh* getMesh();
	Material* getMaterial();

	void setDynamic(bool value);
	bool isDynamic();

	void setModelMatrixGc(glm::mat4 matrix);
	glm::mat4 getModelMatrix();

	void setPivot();
	glm::vec3 getPivot();

<<<<<<< HEAD
<<<<<<< HEAD
	void setEmission(bool value);
	void setShadow(bool value);
	void setTransparency(bool value);
=======
=======
>>>>>>> origin/Resource3.0_ira
	void setEmission(bool value);	//!< turns the emission either "on" or "off" @todo default value? @todo which value means what? Please use [at]param
	void setShadow(bool value);		//!< turns the the ability to cast shadows of this component either "on" or "off" @todo default value? @todo which value means what? Please use [at]param
	void setTransparency(bool value);	//!< sets if the component is transparent or not @todo default value? @todo which value means what? Please use [at]param

<<<<<<< HEAD
>>>>>>> origin/Resource3.0_ira
=======
>>>>>>> origin/Resource3.0_ira

	bool hasEmission();	//!< @return 1 if component has emission turned on @return 0 if it has emission turned off
	bool hasShadow();	//!< @return 1 if component casts shadows @return 0 if component has shadows turned off
	bool hasTransparency();	//!< @return 1 if component is transparent @return 0 if component is not transparent

	void setBoundingBox(glm::vec3 min, glm::vec3 max);
	glm::vec3 getBoundingBox_Min();
	glm::vec3 getBoundingBox_Max();

<<<<<<< HEAD
<<<<<<< HEAD

	GraphicsComponent();
=======
	GraphicsComponent();		//!< default constructor without parameters

>>>>>>> origin/Resource3.0_ira
=======
	GraphicsComponent();		//!< default constructor without parameters

>>>>>>> origin/Resource3.0_ira
	GraphicsComponent(Mesh* mesh, Material* material);

private:
	Mesh *mMesh;
	Material *mMaterial;
<<<<<<< HEAD
<<<<<<< HEAD
	

	glm::mat4 modelMatrixGc;
	glm::vec3 pivot;
	
=======
=======
>>>>>>> origin/Resource3.0_ira


	glm::mat4 modelMatrixGc;
	glm::vec3 pivot;

<<<<<<< HEAD
>>>>>>> origin/Resource3.0_ira
=======
>>>>>>> origin/Resource3.0_ira
	glm::vec3 mAABB_Min;
	glm::vec3 mAABB_Max;


	bool mDynamic;
	bool mEmission;
	bool mShadow;
	bool mTranparency;


};


#endif /* GRAPHICSCOMPONENT_H */

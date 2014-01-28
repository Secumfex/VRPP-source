#ifndef GRAPHICSCOMPONENT_H
#define GRAPHICSCOMPONENT_H
#include <vector>
#include "Visuals/Resource.h"

class GraphicsComponent{
public:
	void setMesh(Mesh* mesh);
	void setMaterial(Material* material);
	Mesh* getMesh();
	Material* getMaterial();

	void setDynamic(bool dyn);
	bool getDynamic();

	void setModelMatrixGc(glm::mat4 matrix);
	glm::mat4 getModelMatrix();

	void setPivot(glm::vec3);
	glm::vec3 getPivot();

	void setEmission(bool value);
	void setShadow(bool value);
	void setTransparency(bool value);

	bool hasEmission();
	bool hasShadow();
	bool hasTransparency();

	void setBoundingBox(glm::vec3 min, glm::vec3 max);
	glm::vec3 getBoundingBox_Min();
	glm::vec3 getBoundingBox_Max();


	GraphicsComponent();
	GraphicsComponent(Mesh* mesh, Material* material);

private:
	Mesh *mMesh;
	Material *mMaterial;
	
	bool dynamic;
	glm::mat4 modelMatrixGc;
	glm::vec3 pivot;
	
	glm::vec3 mAABB_Min;
	glm::vec3 mAABB_Max;

	bool mEmission;
	bool mShadow;
	bool mTranparency;


	};


#endif /* GRAPHICSCOMPONENT_H */

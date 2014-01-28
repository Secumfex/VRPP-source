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

	GraphicsComponent();
	GraphicsComponent(Mesh* mesh, Material* material);

private:
	Mesh *mMesh;
	Material *mMaterial;
	
	bool dynamic;
	glm::mat4 modelMatrixGc;
	glm::vec3 pivot;
	

	};


#endif /* GRAPHICSCOMPONENT_H */

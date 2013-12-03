#ifndef GRAPHICSCOMPONENT_H
#define GRAPHICSCOMPONENT_H
#include <vector>
#include "Visuals/Resource.h"

class GraphicsComponent{
public:
	void setMesh(Mesh mesh);
	void setMaterial(Material material);
	Mesh getMesh();
	Material getMaterial();

	GraphicsComponent();

private:
	Mesh *mMesh;
	Material *mMaterial;


	};


#endif /* GRAPHICSCOMPONENT_H */

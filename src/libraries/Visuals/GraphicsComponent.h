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

	void setEmission(bool value);
	void setShadow(bool value);
	void setTransparency(bool value);

	bool hasEmission();
	bool hasShadow();
	bool hasTransparency();


	GraphicsComponent();
	GraphicsComponent(Mesh* mesh, Material* material);

private:
	Mesh *mMesh;
	Material *mMaterial;

	bool mEmission;
	bool mShadow;
	bool mTranparency;


	};


#endif /* GRAPHICSCOMPONENT_H */

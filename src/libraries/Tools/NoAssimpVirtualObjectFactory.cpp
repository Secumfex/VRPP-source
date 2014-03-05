#include "NoAssimpVirtualObjectFactory.h"

#include "Tools/Geometry.h"
#include "Visuals/Texture.h"

Material* NoAssimpVirtualObjectFactory::createCubeMaterial(){
	Material* cubeMaterial = new Material();	//default-Material-Settings ( white )

	//load some textures
	cubeMaterial->setDiffuseMap(new Texture(RESOURCES_PATH "/cubeTexture.jpg"));
	cubeMaterial->setNormalMap(new Texture(RESOURCES_PATH "/cubeTexture_NRM.jpg"));

	return cubeMaterial;
}

GLuint NoAssimpVirtualObjectFactory::createCubeVAO(){
	//--------------------------------------------//
	//        Create a Vertex Array Object        //
	//         containing several buffers         //
	//             to render a cube               //
	//--------------------------------------------//

	GLuint cubeVertexArrayHandle;
	{
		glGenVertexArrays(1, &cubeVertexArrayHandle);
		glBindVertexArray(cubeVertexArrayHandle);

		//we generate multiple buffers at a time
		GLuint vertexBufferHandles[5];
		glGenBuffers(4, vertexBufferHandles);

		int indices[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
						10,	11, 12, 13, 14, 15, 16, 17, 18, 19,
						20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
						30, 31, 32, 33, 34, 35};

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexBufferHandles[3]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferHandles[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(CubeGeometry::positions), CubeGeometry::positions, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferHandles[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(CubeGeometry::uvCoordinates), CubeGeometry::uvCoordinates, GL_STATIC_DRAW);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferHandles[2]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(CubeGeometry::normals), CubeGeometry::normals, GL_STATIC_DRAW);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferHandles[4]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(CubeGeometry::normals), CubeGeometry::tangents, GL_STATIC_DRAW);
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, 0);
	}

	return cubeVertexArrayHandle;
}

Mesh* NoAssimpVirtualObjectFactory::createCubeMesh(){
	Mesh* cubeMesh = new Mesh();

	cubeMesh->setVAO(createCubeVAO());
	cubeMesh->setNumFaces(12);
	cubeMesh->setNumVertices(12 * 3); // ???
	cubeMesh->setNumIndices(12*3); // ???

	return cubeMesh;
}

VirtualObject* NoAssimpVirtualObjectFactory::createCubeObject(){
	// create Virtual Object Instance with default PhysicsComponent
	VirtualObject* cube = new VirtualObject(); 

	//create GraphicsComponent
	GraphicsComponent* cube_gc = new GraphicsComponent(createCubeMesh(),createCubeMaterial());
	cube_gc->setGhostObject(glm::vec3((-1.0) * CubeGeometry::size,(-1.0) *CubeGeometry::size,(-1.0) *CubeGeometry::size) ,glm::vec3(CubeGeometry::size,CubeGeometry::size,CubeGeometry::size));
	cube->addGraphicsComponent(cube_gc);	//add GraphicsComponent

	cube->setPhysicsComponent(glm::vec3((-1.0) * CubeGeometry::size,(-1.0) *CubeGeometry::size,(-1.0) *CubeGeometry::size) ,glm::vec3(CubeGeometry::size,CubeGeometry::size,CubeGeometry::size));

	//return cube
	return cube;

}

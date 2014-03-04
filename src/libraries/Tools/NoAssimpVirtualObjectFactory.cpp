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
GLuint NoAssimpVirtualObjectFactory::createSphereVAO(){
	//--------------------------------------------//
	//        Create a Vertex Array Object        //
	//         containing several buffers         //
	//             to render a shere              //
	//--------------------------------------------//

	GLuint sphereVertexArrayHandle;
	{
		glGenVertexArrays(1, &sphereVertexArrayHandle);
		glBindVertexArray(sphereVertexArrayHandle);

		//we generate multiple buffers at a time
		GLuint vertexBufferHandles[5];
		glGenBuffers(4, vertexBufferHandles);

		radius = 1.0;
		diameter = 2 * radius;
		pi = 3.14159265359;
		steps = 20;


		float i = 0;
		for (i = 0; i < diameter; i += diameter/steps) {
			float j = 0;
			for (j = 0; j < 2 * pi; j+= pi/steps) {
				float x = sin(j) * sin(i * pi);
				float z = cos(j) * sin(i * pi);
				glm::vec3 vertex = glm::vec3(x, i, z);

				vertices.push_back(vertex);
				uvs.push_back(glm::vec2(i/diameter, j/(2 * pi)));
			}

		}

		int k = 0;
		for (k = 0; k < vertices.size(); ++k) {

			indices.push_back(k);

		int next = (k + 1 ) % vertices.size();
		normals.push_back(glm::normalize(glm::cross(vertices[k], vertices[next])));
		tangents.push_back(glm::normalize(vertices[next] - vertices[k]));
		}

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexBufferHandles[3]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferHandles[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferHandles[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), &uvs[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferHandles[2]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(normals), &normals[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferHandles[4]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(tangents), &tangents[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, 0);
	}

	return sphereVertexArrayHandle;
}

Mesh* NoAssimpVirtualObjectFactory::createCubeMesh(){
	Mesh* cubeMesh = new Mesh();

	cubeMesh->setVAO(createCubeVAO());
	cubeMesh->setNumFaces(12);
	cubeMesh->setNumVertices(12 * 3); // ???
	cubeMesh->setNumIndices(12*3); // ???

	return cubeMesh;
}
Mesh* NoAssimpVirtualObjectFactory::createSphereMesh(){
	Mesh* cubeMesh = new Mesh();

	cubeMesh->setVAO(createSphereVAO());
	cubeMesh->setNumFaces(indices.size()/3);
	cubeMesh->setNumVertices(vertices.size()); // ???
	cubeMesh->setNumIndices(indices.size()); // ???

	return cubeMesh;
}

VirtualObject* NoAssimpVirtualObjectFactory::createCubeObject(){
	// create Virtual Object Instance with default PhysicsComponent
	VirtualObject* cube = new VirtualObject(); 

	//create GraphicsComponent
	GraphicsComponent* cube_gc = new GraphicsComponent(createCubeMesh(),createCubeMaterial());
	cube_gc->setBoundingBox(glm::vec3((-1.0) * CubeGeometry::size,(-1.0) *CubeGeometry::size,(-1.0) *CubeGeometry::size) ,glm::vec3(CubeGeometry::size,CubeGeometry::size,CubeGeometry::size));
	//TODO:VertexListe uebergeben
	cube->addGraphicsComponent(cube_gc);	//add GraphicsComponent

	cube->setPhysicsComponent(cube_gc->getBoundingBox_Min(), cube_gc->getBoundingBox_Max());

	//return cube
	return cube;

}
VirtualObject* NoAssimpVirtualObjectFactory::createSphereObject(){
	// create Virtual Object Instance with default PhysicsComponent
	VirtualObject* sphere = new VirtualObject();

	//create GraphicsComponent
	GraphicsComponent* cube_gc = new GraphicsComponent(createSphereMesh(),createCubeMaterial());
	cube_gc->setBoundingBox(glm::vec3(-radius, -radius, -radius) ,glm::vec3(radius, radius, radius));
	sphere->addGraphicsComponent(cube_gc);	//add GraphicsComponent

	sphere->setPhysicsComponent(cube_gc->getBoundingBox_Min(), cube_gc->getBoundingBox_Max());

	//return cube
	return sphere;

}

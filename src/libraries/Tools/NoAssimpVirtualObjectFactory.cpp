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
        GLuint vertexBufferHandles[3];
        glGenBuffers(3, vertexBufferHandles);
        
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
	cube_gc->setBoundingBox(glm::vec3((-1.0) * CubeGeometry::size,(-1.0) *CubeGeometry::size,(-1.0) *CubeGeometry::size) ,glm::vec3(CubeGeometry::size,CubeGeometry::size,CubeGeometry::size));
	cube->addGraphicsComponent(cube_gc);	//add GraphicsComponent

	// @todo comment in when Bullet_2 branch is merged
	// cube->setPhysicsComponent(cube_gc->getBoundingBox_Min(), cube_gc->getBoundingBox_Max());

	//return cube
	return cube;

}
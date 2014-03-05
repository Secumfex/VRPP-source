#define GLEW_NO_GLU // damit Header von GLU gar nicht erst inkludiert wird
#define GLFW_NO_GLU // damit Header von GLU gar nicht erst inkludiert wird

#include "ShaderTool.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "bunny.h"



GLFWwindow* window;
GLuint bunnyVAO;
GLuint bunnyVBO;
GLuint bunnyIBO;

GLfloat speed=1.0f;
GLfloat angle=0.0f;


void MakeBunny(GLuint programID){
    
	GLfloat values[NUM_POINTS*3+NUM_POINTS*3];
    
	for(int i = 0; i < (NUM_POINTS) ; i++){
		values[i*6+0] = bunny[i*3+0];
		values[i*6+1] = bunny[i*3+1];
		values[i*6+2] = bunny[i*3+2];
        values[i*6+3] = normals[i*3+0];
		values[i*6+4] = normals[i*3+1];
		values[i*6+5] = normals[i*3+2];
	}
    
	glGenBuffers(1, &bunnyVBO);
	glBindBuffer(GL_ARRAY_BUFFER, bunnyVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(values), values, GL_STATIC_DRAW);
    
    glGenBuffers(1, &bunnyIBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bunnyIBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(triangles), triangles, GL_STATIC_DRAW);
    
    
    
    // "Variablen" im Shader binden
	glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 24,0);
	glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,3, GL_FLOAT, GL_FALSE, 24, (GLvoid*)(sizeof(float)*3));
	glEnableVertexAttribArray(1);
    
    
    // unbind all
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}


void OpenGL_OSX (){
    //generate a vertex array object (VAO)
    //GLuint vertexArrayHandle;
    glGenVertexArrays(1, &bunnyVAO);
    
    //specify the vertex data of the bound VBO and store it in the bound VAO
    glBindVertexArray(bunnyVAO);
}

int createWindow(int width, int height, const char* name){
    
    // Framework initialisieren,
    // mit Abfrage, wenn etwas schief geht
    if(glfwInit()== GL_FALSE)
    {
        cerr<<"GLFW FAILED";
        return 1;
    }
    // dem Framework mitteilen, welche OpenGL-Version verwendet wird
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    
    // das Core-Profile unterstüzt neue, aktuelle OpenGL-Befehle
    // damit wird festgelget, dass das "neue Profil" benutzt werden soll
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // das Framework erlaubt nicht, OpenGL-Befehle zu verwenden, die als "veraltet" markiert sind
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    // Fenster erstellen
    window = glfwCreateWindow(width, height, name, 0, 0);
    glfwSetWindowPos(window, 600, 50);
    glfwMakeContextCurrent(window);
    
    // Hintergrundfarbe
    glClearColor(0.7, 0.8, 1, 1);
    
    
    //Extensions vom Treiber laden (init opengl 3 extensions)
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) // glewInit() gibt GLEW_OK aus, wenn im Treiber kein Fehler aufgetaucht ist
    {
        cerr<<"GLEW FAILED";
        return 1;
    }
    
    OpenGL_OSX();
    return 0;
}

int main()
{
    /*
     initialize window
     */
    createWindow(800,600,"OpenGL Tutorial");
    
    
    /* 
     load files with shaders
     */
    const char *shadernames[2] = {SHADERS_PATH "/test_Phong/test_phong.vert", SHADERS_PATH "/test_Phong/test_phong.frag"};
    GLint programID=ShaderTool::doShaderThings(shadernames);
 
    GLuint modelview=glGetUniformLocation(programID,"modelviewMatrix");
    GLuint projection=glGetUniformLocation(programID,"projectionMatrix");
    /*struct LightInfo {
        vec4 pos;
        vec4 ambient;
        vec4 diffuse;
        vec4 specular;
	};
	
    uniform LightInfo Light;
    
    struct MaterialInfo {
        vec4 ambient;
        vec4 diffuse;
        vec4 specular;
        float shininess;
	};
	
    uniform MaterialInfo Material;
    uniform vec4 sceneAmbient;
     */
    // Lichtquelle
    GLuint light_loc1 = glGetUniformLocation(programID, "Light.pos");
    GLuint light_loc2 = glGetUniformLocation(programID, "Light.ambient");
    GLuint light_loc3 = glGetUniformLocation(programID, "Light.diffuse");
    GLuint light_loc4 = glGetUniformLocation(programID, "Light.specular");
    
    // Material
    GLuint mat_loc1 = glGetUniformLocation(programID, "Material.ambient");
    GLuint mat_loc2 = glGetUniformLocation(programID, "Material.diffuse");
    GLuint mat_loc3 = glGetUniformLocation(programID, "Material.specular");
    GLuint mat_loc4 = glGetUniformLocation(programID, "Material.shininess");
    
    // ambientes Licht
    GLuint sceneAmbient = glGetUniformLocation(programID, "sceneAmbient");
    
    
    /** binden der Uniforms **/
    glUniform4f(light_loc1, 5.0f,5.0f,5.0f,1.0f);
    glUniform4f(light_loc2, 0.8f,0.8f,0.8f,1.0f);
    glUniform4f(light_loc3, 0.8f,0.8f,0.8f,1.0f);
    glUniform4f(light_loc4, 0.8f,0.8f,0.8f,1.0f);
    
    /*
    // Material - Gold
    glUniform4f(mat_loc1, 0.25f,0.20f,0.07f, 1.0f);
    glUniform4f(mat_loc2, 0.75f,0.61f,0.23f, 1.0f);
    glUniform4f(mat_loc3, 0.63f,0.56f,0.37f, 1.0f);
    glUniform1f(mat_loc4, 51.0f);
    */
    
    // Material - Silber
    glUniform4f(mat_loc1, 0.19, 0.19, 0.19, 1.0f);
    glUniform4f(mat_loc2, 0.51, 0.51, 0.51, 1.0f);
    glUniform4f(mat_loc3, 0.51, 0.51, 0.51, 1.0f);
    glUniform1f(mat_loc4, 51.0f);
    
    glUniform1f(sceneAmbient, 0.3);

    /** Matritzen definieren **/
    glm::mat4 viewMatrix = glm::lookAt(glm::vec3(-0.3f, 0.3f, -0.3f), glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 projectionMatrix = glm::perspective(45.0f, (float) 800/600, 0.1f, 50.0f);
    glm::mat4 modelMatrix = glm::mat4(1.0f);

     glEnable(GL_DEPTH_TEST);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //renderloop
    while(!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

        angle += 0.5f * speed;
        modelMatrix = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 0.7f, 0.0f));
        viewMatrix=viewMatrix*modelMatrix;
        /*
         draw me the result
         */
        MakeBunny(programID);
        if (bunnyVAO != 0) {
            
            //std::cout<<"true";
            glUniformMatrix4fv(modelview,1,GL_FALSE,&viewMatrix[0][0]);
            glUniformMatrix4fv(projection,1,GL_FALSE,&projectionMatrix[0][0]);
            glBindVertexArray(bunnyVAO);
            glDrawElements(GL_TRIANGLES, NUM_POINTS*6, GL_UNSIGNED_INT, 0);
        }
        viewMatrix = glm::lookAt(glm::vec3(-0.3f, 0.3f, -0.3f), glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        
        MakeBunny(programID);
        modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.1f,-0.2f,0.0f));
        viewMatrix=viewMatrix*modelMatrix;

        if (bunnyVAO != 0) {
            
            //std::cout<<"true";
            glUniformMatrix4fv(modelview,1,GL_FALSE,&viewMatrix[0][0]);
            glUniformMatrix4fv(projection,1,GL_FALSE,&projectionMatrix[0][0]);
            glBindVertexArray(bunnyVAO);
            glDrawElements(GL_TRIANGLES, NUM_POINTS*6, GL_UNSIGNED_INT, 0);
        }
        viewMatrix = glm::lookAt(glm::vec3(-0.3f, 0.3f, -0.3f), glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

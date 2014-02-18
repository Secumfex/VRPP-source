#include <string>
#include <cstring>
#include <iostream>
#include <fstream>

#include "ShaderTools.h"

namespace ShaderTools {
    void checkShader(GLuint shaderHandle) {
        GLint status;
        glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &status);

        if (status == GL_FALSE) {
            GLint infoLogLength;
            glGetShaderiv(shaderHandle, GL_INFO_LOG_LENGTH, &infoLogLength);

            GLchar* infoLog = new GLchar[infoLogLength + 1];
            glGetShaderInfoLog(shaderHandle, infoLogLength, NULL, infoLog);

            std::cout << "ERROR: Unable to compile shader" << std::endl << infoLog << std::endl;
            delete[] infoLog;
        } else {
            std::cout << "SUCCESS: Shader compiled" << std::endl;
        }
    }

    void loadShaderSource(GLint shaderHandle, const char* fileName) {
        std::string fileContent;
        std::string line;

        //open file and "parse" input
        std::ifstream file(fileName);
        if (file.is_open()) {
            while (!file.eof()){
                getline (file, line);
                fileContent += line + "\n";
            }
            file.close();
            std::cout << "SUCCESS: Opened file " << fileName << std::endl;
        }
        else
            std::cout << "ERROR: Unable to open file " << fileName << std::endl;

        const char* source = fileContent.c_str();
        const GLint source_size = strlen(source);
        
        glShaderSource(shaderHandle, 1, &source, &source_size);
    }

    GLuint makeShaderProgram(const char* vertexShaderName, const char* fragmentShaderName) {
        //compile vertex shader
        GLuint vertexShaderHandle = glCreateShader(GL_VERTEX_SHADER);
        loadShaderSource(vertexShaderHandle, vertexShaderName);
        glCompileShader(vertexShaderHandle);
        checkShader(vertexShaderHandle);

        //compile fragment shader
        GLuint fragmentShaderHandle = glCreateShader(GL_FRAGMENT_SHADER);
        loadShaderSource(fragmentShaderHandle, fragmentShaderName);
        glCompileShader(fragmentShaderHandle);
        checkShader(fragmentShaderHandle);

        //link shader programs
        GLuint programHandle = glCreateProgram();
        glAttachShader(programHandle, vertexShaderHandle);
        glAttachShader(programHandle, fragmentShaderHandle);
        glLinkProgram(programHandle);

        return programHandle;
    }
    GLuint makeShaderProgram() {

    	//compile vertex shader
        GLuint vertexShaderHandle = glCreateShader(GL_VERTEX_SHADER);

    	const char *vertexShader ="\
    	//		#version 330 core \n\
    	//		\
    	//layout(location = 0) in vec4 positionAttribute;\
    	//layout(location = 1) in vec2 uvCoordAttribute;\
    	//layout(location = 2) in vec4 normalAttribute;\
    	//layout(location = 3) in vec4 tangentAttribute;\
    	//\
    	//uniform mat4 uniformModel;\
    	//uniform mat4 uniformView;\
    	//uniform mat4 uniformProjection;\
    	//\
    	//out vec4 passPosition;\
    	//out vec2 passUVCoord;\
    	//out vec3 passNormal;\
    	//out vec3 passTangent;\
    	//\
    	//void main(){\
    	//    passUVCoord = uvCoordAttribute;\
    	//\
    	//    passPosition = uniformView * uniformModel * positionAttribute;\
    	//    gl_Position =  uniformProjection * uniformView * uniformModel * positionAttribute;\
    	//\
    	//    passNormal = vec3(transpose(inverse(uniformView * uniformModel)) * normalAttribute);\
    	//    passTangent = vec3(transpose(inverse(uniformView * uniformModel)) * tangentAttribute);\
    	}";

    	const GLint source_size01 = strlen(vertexShader);

    	glShaderSource(vertexShaderHandle, 1, &vertexShader, &source_size01);

        glCompileShader(vertexShaderHandle);
        checkShader(vertexShaderHandle);

        //compile fragment shader
        GLuint fragmentShaderHandle = glCreateShader(GL_FRAGMENT_SHADER);

        const char *fragmentShader ="\
    	//		#version 330 core\n\
    	//\
    	////incoming data for the single textures\
    	//in vec4 passPosition;\
    	//in vec2 passUVCoord;\
    	//in vec3 passNormal;\
    	//\
    	//uniform float shininess;\
    	//\
    	//uniform sampler2D diffuseTexture;\
    	//\
    	////writable textures for deferred screen space calculations\
    	//layout(location = 0) out vec4 positionOutput;\
    	//layout(location = 1) out vec4 normalOutput;\
    	//layout(location = 2) out vec4 colorOutput;\
    	//layout(location = 3) out vec4 materialOutput;\
    	// \
    	//void main(){  \
    	//    positionOutput = passPosition;\
    	//    normalOutput = vec4(normalize(passNormal), 0);\
    	//    colorOutput = texture(diffuseTexture, passUVCoord);\
    	//    materialOutput = vec4(shininess, 0.0, 0.0, 0.0);\
    	}";

        const GLint source_size02 = strlen(fragmentShader);
    	glShaderSource(fragmentShaderHandle, 1, &fragmentShader, &source_size02);

        glCompileShader(fragmentShaderHandle);
        checkShader(fragmentShaderHandle);

        //link shader programs
        GLuint programHandle = glCreateProgram();
        glAttachShader(programHandle, vertexShaderHandle);
        glAttachShader(programHandle, fragmentShaderHandle);
        glLinkProgram(programHandle);

        return programHandle;
    }
}

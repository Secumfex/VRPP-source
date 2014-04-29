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
}

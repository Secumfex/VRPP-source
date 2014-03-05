//
//  ShaderTool.h
//  OpenGLProject
//
//  Created by Irina on 24.01.14.
//
//
#include <GL/glew.h> // Render-Library
#include <GLFW/glfw3.h> // OpenGL-Framework
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#ifndef OpenGLProject_ShaderTool_h
#define OpenGLProject_ShaderTool_h

namespace ShaderTool {
    int loadShader(const char* shaderSource,int GL_SHADER_BIT);
    int checkShader (int shader);
    void checkLinkedProgram(int program_ID);
    int doShaderThings(const char** shaderSource);
    
}

#endif

#include "ShaderTool.h"

namespace ShaderTool {
    
int loadShader(const char* shaderSource,int GL_SHADER_BIT){
    
    /** ** am Ende muss man einen char-Pointer auf den Quellcode des Shaders haben!!! ** **/
    
    // Shaderobjekt wird erstellt
    GLuint shader=glCreateShader(GL_SHADER_BIT); // mit Shader-Typ (z.B.: GL_VERTEX_SHADER oder GL_FRAGMENT_SHADER)
    
    string fileContent;
    string line;
    
    //open file and "parse" input
    ifstream file(shaderSource);
    if (file.is_open()) {
        while (!file.eof()){
            getline (file, line);
            fileContent += line + "\n";
        }
        file.close();
        cout << "SUCCESS: Opened file " <<shaderSource<< endl;
    }
    else
        cout << "ERROR: Unable to open file " <<shaderSource<< endl;
    
    const char* source = fileContent.c_str(); // hier ist der char-Pointer zum Quellcode
    cout<<"Pointer: "<<&source<<endl; // -> der Pointer "source" zeigt auf den ganzen Quellcode des Shaders
                                        // hier wird dementsprechend der Shader als Text gespeichert/ausgegeben
    cout<<"... SHADER loaded ...\n... POINTER created ..."<<endl;
    cout<<"Show imported SHADER: \n"<<fileContent.data()<< endl;
    
    // Quellcode des Shaders an das Shaderobjekt übermittlen
    glShaderSource(shader, 1, &source, 0);  // Shaderobjekt,
                                            // Anzahl der Elemnte im Array - falls der Quellcode zeilenweise gespeichert wurde,
                                            // der Pointer auf das Array mit Quellcode des Shaders
                                            // Länge - jedoch sollte OpenGL bei einem Zeiger die Länge automatisch ermitteln
    
    // kompiliert das Shaderobjekt
    // OpenGL besitzt einen Shader-Compiler
    glCompileShader(shader);
    
    
    // gibt das Shaderobjekt zurück
    return shader;
}

int checkShader (int shader){
    
    /** Fehleranalyse im Shader **/
    
    GLint compile_ok;   // checkt, ob der Shader korrekt kompiliert wurde
    GLint errlength;    // ermittelt die Läge der Error-Message
    GLchar* errmsg;     // char-Pointer, der auf die Fehler-Message zeigt
    
    glGetShaderiv(shader,GL_COMPILE_STATUS,&compile_ok); // in 'compile_ok' wird entweder '0' oder '1' reingeschrieben
     //cerr<<compile_ok<<"\n"; // -> '0' bei Fehler; '1' bei OK
    if (compile_ok==GL_FALSE){
        
        glGetShaderiv(shader,GL_INFO_LOG_LENGTH,&errlength); // wie lange ist die Error-Message
        errmsg=new GLchar[errlength]; // char-Pointer reserviert Platz, abhänging von der Länge der Nachricht
        glGetShaderInfoLog(shader,errlength,&errlength,errmsg); // Error-Message in 'errmsg' laden
                                            // * Referenz auf die Länge
        cerr<<"Ein Fehler im Shader ist aufgetreten => "<<errmsg;
        return 1;
    }
    
    return 0;
}

void checkLinkedProgram(int program_ID){
    // testen ob Shader gelinkt sind
    GLint status;
    glGetProgramiv(program_ID, GL_LINK_STATUS, &status);
    if (status == GL_FALSE) {
        GLint infoLogLength;
        glGetProgramiv(program_ID, GL_INFO_LOG_LENGTH, &infoLogLength);
        
        GLchar* infoLog = new GLchar[infoLogLength + 1];
        glGetShaderInfoLog(program_ID, infoLogLength, NULL, infoLog);
        
        std::cout << "ERROR: Unable to link shader" << std::endl << infoLog << std::endl;
        delete[] infoLog;
    } else {
        std::cout << "SUCCESS: shader linked" << std::endl;
    }
    
}

int doShaderThings(const char** shaderSource){
    
    GLint vertexshader=loadShader(shaderSource[0],GL_VERTEX_SHADER);
    checkShader(vertexshader);
    
    GLint fragmentshader=loadShader(shaderSource[1],GL_FRAGMENT_SHADER);
    checkShader(fragmentshader);
    
    
    /** ** Shader bereit für die Grafikkarte machen ** **/
    /**    -> geschieht über ein 'Program'             **/
    
    GLuint program = glCreateProgram();
    
    // Shaders zum 'Program' hinzufügen
    glAttachShader(program,vertexshader);
    glAttachShader(program,fragmentshader);
    // 'Program' linken, damit es bereit zum Einsatz ist
    glLinkProgram(program);
    
    checkLinkedProgram(program);
    
      //glBindAttribLocation(program, 0, "position");
    // glDeleteShader(vertexshader); // ???
    // glDeleteShader(fragmentshader);  //???
    
    // gibt das einsatzbereite 'Program' zurück (mit eingebundenen Shaders)
    
    // use the shadow program
    glUseProgram(program);
    return program;
}
}
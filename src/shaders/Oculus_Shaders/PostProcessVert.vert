#version 330

    uniform mat4 View;
    uniform mat4 Texm;
    
    layout(location = 0) in vec4 Position;
	layout(location = 1) in vec2 TexCoord;
	
    out vec2 oTexCoord;
    
    void main()
    {
       gl_Position = View * Position;
//    	gl_Position = Position;
       oTexCoord = vec2(Texm * vec4(TexCoord,0,1) );
       oTexCoord.y = oTexCoord.y;
    }
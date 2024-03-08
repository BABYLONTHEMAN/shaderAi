#version 410

in vec3 TexCoord;
out vec4 FragColor;

uniform samplerCube skybox;

void main()
{ 
   FragColor = texture(skybox, TexCoord);
    }
//
//#version 410
//out vec4 FragColor;
//
//in vec3 TexCoord;
//
//uniform samplerCube skybox;
//
//void main()
//{    
//    FragColor = texture(skybox, TexCoord);
//}
//
//
//
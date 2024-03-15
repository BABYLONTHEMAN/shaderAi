#version 410

layout (location = 0) in vec3 aPos;

out vec3 TexCoords;

uniform mat4 projectionSky;
uniform mat4 viewSky;
uniform mat4 modelSky;

void main()
{
    TexCoords = aPos;
    vec4 pos = projectionSky * viewSky * vec4(aPos,1.0);
    gl_Position = pos.xyww;
}




//#version 410
//layout (location = 0) in vec3 aPos;
//
//out vec3 TexCoord;
//uniform mat4 modelSky;
//
//uniform mat4 projection;
//uniform mat4 view;
//
//void main()
//{
//    TexCoord = aPos;
//    vec4 pos = projection *modelSky* view * vec4(aPos, 1.0);
//    gl_Position = pos.xyww;
//}  
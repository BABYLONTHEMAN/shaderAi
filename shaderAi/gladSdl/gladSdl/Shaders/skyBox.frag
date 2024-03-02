#version 410
out vec4 FragColor;
uniform mat4 modelSky;
in vec3 TexCoords;

uniform samplerCube skybox;

void main()
{    
    FragColor = texture(skybox, TexCoords);
}
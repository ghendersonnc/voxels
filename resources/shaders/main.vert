#version 330
layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec2 inTextureCoordinates;

out vec3 color;
out vec2 textureCoordinates;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() 
{
    gl_Position = projection * view * model * vec4(inPosition, 1.0);
   
    color = vec3(0.0,0.0,0.0);
    textureCoordinates = inTextureCoordinates;

}
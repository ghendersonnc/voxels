#version 330
layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec2 inTextureCoordinates;
layout (location = 2) in vec3 inColorMultiplier;

out vec2 textureCoordinates;
out vec4 colorMultiplier;

uniform float textureSingleColumn;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() 
{
    
    gl_Position = projection * view * model * vec4(inPosition, 1.0);
    textureCoordinates = inTextureCoordinates * textureSingleColumn;
    colorMultiplier = vec4(inColorMultiplier, 1.0);
}
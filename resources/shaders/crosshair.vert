#version 330
layout (location = 0) in vec2 inPosition;
layout (location =1 ) in vec2 inTextureCoordinates;

out vec2 textureCoordinates;

void main() {
    
    gl_Position = vec4(inPosition, 0.f, 1.0f);
    textureCoordinates = inTextureCoordinates;
}
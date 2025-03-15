#version 330
out vec4 FragColor;

in vec2 textureCoordinates;
in vec4 colorMultiplier;

uniform sampler2D textureImage;

void main() {

    FragColor = texture(textureImage, textureCoordinates) * colorMultiplier;
}
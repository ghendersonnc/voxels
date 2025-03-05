#version 330
out vec4 FragColor;
in vec3 color;
in vec2 textureCoordinates;

uniform sampler2D textureImage;

void main() {
    FragColor = texture(textureImage, textureCoordinates);
}
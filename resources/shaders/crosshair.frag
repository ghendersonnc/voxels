#version 330
out vec4 FragColor;

in vec2 textureCoordinates;

uniform sampler2D textureImage;

void main() {
    FragColor = texture(textureImage, textureCoordinates) * vec4(1.0f, 1.f, 1.f, .9f);

}
#version 330
layout (location = 0) in vec2 inPosition;

void main() {
    gl_Position = vec4(inPosition, 0.f, 1.f);
}
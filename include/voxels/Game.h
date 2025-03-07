#pragma once

#include <string>
#include <unordered_map>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "Camera.h"
#include "Shader.h"
#include "enums.h"

namespace Voxels 
{
    class Game {
    public:
        GLFWwindow* window;
        Camera camera;
        std::unordered_map<ShaderProgram, Shader> shaders;
        float deltaTime;
        float lastX;
        float lastY;
        bool firstMouse;
        Game();
        bool init();
        void run();
    private:
        bool mFailure;
        std::string mRenderer;
        void _processInput();
        void _processMouse();
        void _createShaders();
    };
}

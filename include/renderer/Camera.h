#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>

namespace Voxels 
{
    class Camera {
    public:
        glm::vec3 position;
        glm::vec3 front;
        glm::vec3 right;
        glm::vec3 up;
        glm::vec3 worldUp;

        float yaw;
        float pitch;
        float fov;
        float mouseSens;

        Camera();

        void move(uint8_t direction, const float& deltaTime);
        void processMouse(float xoffset, float yoffset, bool constrainPitch = true);
        void toggleZoom(bool zoomIn, float zoomAmount);
        void updateVectors();
    };
}
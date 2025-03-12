#include "Camera.h"

#include <algorithm>
#include <iostream>

#include "Definitions.h"

namespace Voxels
{
    Camera::Camera()
    {
        cameraSpeed = 15;
        position = glm::vec3(0.0f, 32.0f, 0.0f);
        worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
        front = glm::vec3(0.0f, 0.0f, -1.0f);
        yaw = 45.0f;
        pitch = 0.0f;
        fov = 45.0f;
        mouseSens = 0.1f;
        right = glm::normalize(glm::cross(right, front));
        front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        front.y = sin(glm::radians(pitch));
        front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        front = glm::normalize(front);
        right = glm::normalize(glm::cross(front, worldUp));
        up = glm::normalize(glm::cross(right, front));
    }
    /*
    * 1 = forward
    * 2 = right
    * 3 = backward
    * 4 = left
    * 5 = up
    * 6 = down
    */
    void Camera::move(uint8_t direction, const float& deltaTime)
    {
        float speed = static_cast<float>(cameraSpeed * deltaTime);
        if (direction == 1)
            position += speed * front;
        if (direction == 3)
            position -= speed * front;
        if (direction == 2)
            position += glm::normalize(glm::cross(front, up)) * speed;
        if (direction == 4)
            position -= glm::normalize(glm::cross(front, up)) * speed;
        if (direction == 5)
            position += speed * glm::vec3(0.0f, 1.f, 0.f);
        if (direction == 6)
            position -= speed * glm::vec3(0.0f, 1.f, 0.f);

    }

    void Camera::processMouse(float xoffset, float yoffset, bool constrainPitch)
    {
        xoffset *= mouseSens;
        yoffset *= mouseSens;

        yaw += xoffset;
        pitch -= yoffset;

        if (constrainPitch)
        {
            pitch = std::min(pitch, 89.0f);
            pitch = std::max(pitch, -89.0f);
        }

        updateVectors();

    }

    void Camera::toggleZoom(bool zoomIn, float zoomAmount)
    {
        if (zoomIn)
        {
            fov -= zoomAmount;
            fov = std::max(fov, 10.f);
        }
        else if (!zoomIn)
        {
            fov += zoomAmount;
            fov = std::min(fov, 45.f);
        }
    }

    void Camera::toggleBoost(bool boost)
    {
        if (boost)
            cameraSpeed = 60;
        else if (!boost)
            cameraSpeed = 15;
    }

    void Camera::updateVectors()
    {
        front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        front.y = sin(glm::radians(pitch));
        front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        front = glm::normalize(front);

        right = glm::normalize(glm::cross(front, worldUp));
        up = glm::normalize(glm::cross(right, front));
    }

}





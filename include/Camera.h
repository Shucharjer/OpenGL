#pragma once
#include "glm/glm.hpp"

class Camera
{
    public:

    float sensivity;

    float fov;

    float pitch;
    float yaw;
    float roll;

    glm::vec3 pos;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;

    Camera(
        glm::vec3 pos = glm::vec3(0.0f), float fov = 70.0f,
        float sensivity = 1.0f,
        glm::vec3 front = glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
        float pitch = 0, float yaw = 0, float roll = 0
    );
    ~Camera();

    glm::mat4 GetViewMatrix() const;
};
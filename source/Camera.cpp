#include "Camera.h"
#include "glm/gtc/matrix_transform.hpp"

Camera::Camera(glm::vec3 pos, float fov, float sensivity, glm::vec3 front, glm::vec3 up, float pitch, float yaw, float roll)
    : pos(pos), fov(fov), sensivity(sensivity),
    front(front), up(up),
    pitch(pitch), yaw(yaw), roll(roll)
{

}

Camera::~Camera()
{

}

glm::mat4 Camera::GetViewMatrix() const
{
    return glm::lookAt(pos, pos + front, up);
}

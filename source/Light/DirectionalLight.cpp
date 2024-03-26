#include "Light/DirectionalLight.h"
#include "Light/BaseLight.h"
#include "Render/Shader/ShaderProgram.h"

DirectionalLight::DirectionalLight(glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, bool visibility)
    : BaseLight(ambient, diffuse, specular, visibility)
{
    this->direction = direction;
}
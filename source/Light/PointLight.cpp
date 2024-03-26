#include "Light/PointLight.h"

PointLight::PointLight(glm::vec3 position,
    glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular,
    float constant, float linear, float quadratic,
    bool visibility)
    : BaseLight(ambient, diffuse, specular, visibility)
{
    this->position = position;
    this->constant = constant;
    this->linear = linear;
    this->quadratic = quadratic;
}

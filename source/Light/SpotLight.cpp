#include "Light/SpotLight.h"
#include "Light/BaseLight.h"

SpotLight::SpotLight(glm::vec3 position, glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular,
    float constant, float linear, float quadratic,
    float cutoffAngle, float outerCutoffAngle,
    bool visibility) : BaseLight(ambient, diffuse, specular, visibility)
{
    this->position = position;
    this->direction = direction;
    this->constant = constant;
    this->linear = linear;
    this->quadratic = quadratic;
    this->cutoffAngle = cutoffAngle;
    this->outerCutoffAngle = outerCutoffAngle;
}
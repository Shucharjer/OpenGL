#pragma once
#include "Light/BaseLight.h"

class SpotLight : public BaseLight
{
public:
    float cutoffAngle;
    float outerCutoffAngle;

    float constant;
    float linear;
    float quadratic;
    SpotLight(glm::vec3 position, glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular,
        float constant = 1.0f, float linear = 0.09f, float quadratic = 0.032f,
        float cutoffAngle = 30.0f, float outerCutoffAngle = 35.0f,
        bool visibility = true);
    ~SpotLight() {};
};
#pragma once
#include "BaseLight.h"

class PointLight : public BaseLight
{
public:
    float constant;
    float linear;
    float quadratic;
    PointLight(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular,
        float constant = 1.0f, float linear = 0.09f, float quadratic = 0.032f,
        bool visibility = true);
    ~PointLight() {};
};

#pragma once
#include "BaseLight.h"

class DirectionalLight : public BaseLight
{

public:
    DirectionalLight(glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, bool visibility = true);
    ~DirectionalLight() {};
};

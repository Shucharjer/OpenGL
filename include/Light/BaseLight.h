#pragma once
#include "Render/Shader/ShaderProgram.h"
#include "glm/glm.hpp"

class BaseLight
{
protected:

public:
    bool visibility;

    glm::vec3 position;
    glm::vec3 direction;

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

    BaseLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, bool visibility);
    ~BaseLight() {};
};
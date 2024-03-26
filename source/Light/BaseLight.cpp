#include "Light/BaseLight.h"

BaseLight::BaseLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, bool visibility)
    : ambient(ambient), diffuse(diffuse), specular(specular), visibility(visibility)
{

}

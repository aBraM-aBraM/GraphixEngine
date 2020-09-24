#pragma once
#include "../Light.h"
class DirectionalLight :
    public Light
{
public:
    glm::vec3 direction;

    DirectionalLight(const std::string& name, glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);
};


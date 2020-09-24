#pragma once
#include <glm/glm.hpp>
#include "../Light.h"

class SpotLight : public Light
{
public:
    glm::vec3 position;
    glm::vec3 direction;
    float cutOff;
    float outerCutOff;

    SpotLight(const std::string& name, glm::vec3 position, glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse,
        glm::vec3 specular, float cutOff, float outerCutOff);

 
};


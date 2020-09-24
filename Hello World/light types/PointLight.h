#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../Light.h"

class PointLight : public Light
{

public:
	glm::vec3 position;
	float constant;
	float linear;
	float quadratic;

	PointLight(const std::string& name, glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic);
	
};


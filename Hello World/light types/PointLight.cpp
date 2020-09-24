#include "PointLight.h"

PointLight::PointLight(const std::string& name, glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic)
	:Light(name, ambient, diffuse, specular)
{
	this->position = position;
	this->constant = constant;
	this->linear = linear;
	this->quadratic = quadratic;
}

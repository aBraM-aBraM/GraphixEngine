#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(const std::string& name, glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
	:Light(name, ambient, diffuse, specular)
{
	this->direction = direction;
}
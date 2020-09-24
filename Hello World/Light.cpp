#include "Light.h"

Light::Light(const std::string& name, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
{
	this->name = name;
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
}

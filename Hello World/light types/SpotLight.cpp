#include "SpotLight.h"

SpotLight::SpotLight(const std::string& name, glm::vec3 position, glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float cutOff, float outerCutOff)
	:Light(name, ambient, diffuse, specular)
{
	this->position = position;
	this->direction = direction;
	this->cutOff = cos(cutOff);
	this->outerCutOff = cos(outerCutOff);
}

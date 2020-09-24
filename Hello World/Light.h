#pragma once
#include<glm/glm.hpp>
#include<iostream>

class Light
{
	// WHY DO PEOPLE USE STRING& WHAT DOES IT MEAN
public:
	std::string name;
	glm::mat4 view;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	Light(const std::string& name, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);
};


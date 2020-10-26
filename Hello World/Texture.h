#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Texture
{
public:
	unsigned int id;
	std::string type;
	std::string path;  // we store the path of the texture to compare with other textures
};


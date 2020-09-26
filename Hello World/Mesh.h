#pragma once

#include "Vertex.h"
#include "Texture.h"
#include "Shader.h"
#include <vector>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Mesh
{
public:
    // mesh data
    
    std::vector<Vertex>       vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture>      textures;

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
    void Draw(Shader& shader);
private:
    //  render data
    unsigned int VAO, VBO, EBO;

    void setupMesh();
};
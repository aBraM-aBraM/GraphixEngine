

#ifndef SHADER_H
    #define SHADER_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glad/glad.h>

#include "light types/PointLight.h"
#include "light types/SpotLight.h"
#include "light types/DirectionalLight.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

// ONE DAY WE GON' CREATE AN ARRAY OF LIGHTS AND STORE THEM CREATE AN ADDLIGHT() METHOD WHICH WILL BE LIT

class Shader
{
public:
    unsigned int ID;
    // constructor generates the shader on the fly
    // ------------------------------------------------------------------------
    Shader(const char* vertexPath, const char* fragmentPath);
    // activate the shader
    // ------------------------------------------------------------------------
    void use();
    // utility uniform functions
    // ------------------------------------------------------------------------
    void setBool(const std::string& name, bool value) const;
    // ------------------------------------------------------------------------
    void setInt(const std::string& name, int value) const;
    // ------------------------------------------------------------------------
    void setFloat(const std::string& name, float value) const;
    // ------------------------------------------------------------------------
    void setVec3(const std::string& name, float x, float y, float z);
    // ------------------------------------------------------------------------
    void setMaterial(const std::string& name, float ambientX, float ambientY, float ambientZ, float diffuseX, float diffuseY, float diffuseZ, float specularX, float specularY, float specularZ, float shininess);
    void setMaterial(const std::string& name, float PosX, float PosY, float PosZ, float ambientX, float ambientY, float ambientZ, float diffuseX, float diffuseY, float diffuseZ, float specularX, float specularY, float specularZ);

    void setVec3(const std::string& name, glm::vec3 vector);
    void setMaterial(const std::string& name, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess);
    // Light Set Functions
    void setLight(SpotLight spotLight);
    void setLight(PointLight pointLight);
    void setLight(DirectionalLight dirLight);


    // ------------------------------------------------------------------------
    void setMat4(const std::string& name, glm::mat4 matrix);
private:
    // utility function for checking shader compilation/linking errors.
    // ------------------------------------------------------------------------
    void checkCompileErrors(unsigned int shader, std::string type);
};
#endif


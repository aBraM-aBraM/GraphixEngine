#include "Shader.h"


    unsigned int ID;
    // constructor generates the shader on the fly
    // ------------------------------------------------------------------------
    Shader::Shader(const char* vertexPath, const char* fragmentPath)
    {
        // 1. retrieve the vertex/fragment source code from filePath
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        // ensure ifstream objects can throw exceptions:
        vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try
        {
            // open files
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);
            std::stringstream vShaderStream, fShaderStream;
            // read file's buffer contents into streams
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();
            // close file handlers
            vShaderFile.close();
            fShaderFile.close();
            // convert stream into string
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        }
        catch (std::ifstream::failure& e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        }
        const char* vShaderCode = vertexCode.c_str();
        const char* fShaderCode = fragmentCode.c_str();
        // 2. compile shaders
        unsigned int vertex, fragment;
        // vertex shader
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        checkCompileErrors(vertex, "VERTEX");
        // fragment Shader
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        checkCompileErrors(fragment, "FRAGMENT");
        // shader Program
        ID = glCreateProgram();
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        glLinkProgram(ID);
        checkCompileErrors(ID, "PROGRAM");
        // delete the shaders as they're linked into our program now and no longer necessary
        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }
    // activate the shader
    // ------------------------------------------------------------------------
    void Shader::use()
    {
        glUseProgram(ID);
    }
    // utility uniform functions
    // ------------------------------------------------------------------------
    void Shader::setBool(const std::string& name, bool value) const
    {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
    }
    // ------------------------------------------------------------------------
    void Shader::setInt(const std::string& name, int value) const
    {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    }
    // ------------------------------------------------------------------------
    void Shader::setFloat(const std::string& name, float value) const
    {
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
    }
    // ------------------------------------------------------------------------
    void Shader::setVec3(const std::string& name, float x, float y, float z)
    {
        glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
    }
    // ------------------------------------------------------------------------
    void Shader::setMaterial(const std::string& name, float ambientX, float ambientY, float ambientZ, float diffuseX, float diffuseY, float diffuseZ, float specularX, float specularY, float specularZ, float shininess)
    {
        setVec3(name + ".ambient", ambientX, ambientY, ambientZ);
        setVec3(name + ".diffuse", diffuseX, diffuseY, diffuseZ);
        setVec3(name + ".specular", specularX, specularY, specularZ);
        setFloat(name + ".shininess", shininess);
    }
    void Shader::setMaterial(const std::string& name, float PosX, float PosY, float PosZ, float ambientX, float ambientY, float ambientZ, float diffuseX, float diffuseY, float diffuseZ, float specularX, float specularY, float specularZ)
    {
        setVec3(name + ".position", PosX, PosY, PosZ);
        setVec3(name + ".ambient", ambientX, ambientY, ambientZ);
        setVec3(name + ".diffuse", diffuseX, diffuseY, diffuseZ);
        setVec3(name + ".specular", specularX, specularY, specularZ);
    }

    void Shader::setVec3(const std::string& name, glm::vec3 vector)
    {
        setVec3(name, vector.x, vector.y, vector.z);
    }
    void Shader::setMaterial(const std::string& name, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess)
    {
        setVec3(name + ".ambient", ambient);
        setVec3(name + ".diffuse", diffuse);
        setVec3(name + ".specular", specular);
        setFloat(name + ".shininess", shininess);
    }
    // this functions could use the utility functions
    // but would just create an uneeded function wrappers
    void Shader::setLight(SpotLight spotLight)
    {
        glUniform3f(glGetUniformLocation(ID, (spotLight.name + ".position").c_str()), spotLight.position.x, spotLight.position.y, spotLight.position.z);
        glUniform3f(glGetUniformLocation(ID, (spotLight.name + ".direction").c_str()), spotLight.direction.x, spotLight.direction.y, spotLight.direction.z);
        glUniform3f(glGetUniformLocation(ID, (spotLight.name + ".ambient").c_str()), spotLight.ambient.x, spotLight.ambient.y, spotLight.ambient.z);
        glUniform3f(glGetUniformLocation(ID, (spotLight.name + ".diffuse").c_str()), spotLight.diffuse.x, spotLight.diffuse.y, spotLight.diffuse.z);
        glUniform3f(glGetUniformLocation(ID, (spotLight.name + ".specular").c_str()), spotLight.specular.x, spotLight.specular.y, spotLight.specular.z);
        glUniform1f(glGetUniformLocation(ID, (spotLight.name + ".cutOff").c_str()), spotLight.cutOff);
        glUniform1f(glGetUniformLocation(ID, (spotLight.name + ".outerCutOff").c_str()), spotLight.outerCutOff);
    }
    void Shader::setLight(PointLight pointLight)
    {
        glUniform3f(glGetUniformLocation(ID, (pointLight.name + ".position").c_str()), pointLight.position.x, pointLight.position.y, pointLight.position.z);
        glUniform3f(glGetUniformLocation(ID, (pointLight.name + ".ambient").c_str()), pointLight.ambient.x, pointLight.ambient.y, pointLight.ambient.z);
        glUniform3f(glGetUniformLocation(ID, (pointLight.name + ".diffuse").c_str()), pointLight.diffuse.x, pointLight.diffuse.y, pointLight.diffuse.z);
        glUniform3f(glGetUniformLocation(ID, (pointLight.name + ".specular").c_str()), pointLight.specular.x, pointLight.specular.y, pointLight.specular.z);
        glUniform1f(glGetUniformLocation(ID, (pointLight.name + ".constant").c_str()), pointLight.constant);
        glUniform1f(glGetUniformLocation(ID, (pointLight.name + ".linear").c_str()), pointLight.linear);
        glUniform1f(glGetUniformLocation(ID, (pointLight.name + ".quadratic").c_str()), pointLight.quadratic);
    }
    void Shader::setLight(DirectionalLight dirLight)
    {
        glUniform3f(glGetUniformLocation(ID, (dirLight.name + ".direction").c_str()), dirLight.direction.x, dirLight.direction.y, dirLight.direction.z);
        glUniform3f(glGetUniformLocation(ID, (dirLight.name + ".ambient").c_str()), dirLight.ambient.x, dirLight.ambient.y, dirLight.ambient.z);
        glUniform3f(glGetUniformLocation(ID, (dirLight.name + ".diffuse").c_str()), dirLight.diffuse.x, dirLight.diffuse.y, dirLight.diffuse.z);
        glUniform3f(glGetUniformLocation(ID, (dirLight.name + ".specular").c_str()), dirLight.specular.x, dirLight.specular.y, dirLight.specular.z);
    }
    // ------------------------------------------------------------------------
    void Shader::setMat4(const std::string& name, glm::mat4 matrix)
    {
        glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
    }

    // utility function for checking shader compilation/linking errors.
    // ------------------------------------------------------------------------
    void Shader::checkCompileErrors(unsigned int shader, std::string type)
    {
        int success;
        char infoLog[1024];
        if (type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
    }



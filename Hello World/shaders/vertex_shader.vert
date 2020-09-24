#version 330 core
layout(location = 0) in vec3 aPos;   // the position variable has attribute position 0
layout (location = 1) in vec3 aNormal; // normal
layout (location = 2) in vec2 aTexCoords; // texture coordinates

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 viewPos;

out vec3 Normal;
out vec3 FragPos;
out vec2 TexCoords;
out vec3 ViewPos;

void main()
{
    gl_Position =  projection * view * model * vec4(aPos, 1.0);
    FragPos =  vec3(view * model * vec4(aPos, 1.0)); // send World Coordinates of vertex
    Normal =  mat3(transpose(inverse(view * model))) * aNormal; // multiply by vector matrix
    ViewPos = vec3(view * vec4(viewPos, 1.0)); // send world coordinates 
    TexCoords = aTexCoords;
}
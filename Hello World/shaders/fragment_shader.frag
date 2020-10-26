#version 330 core

out vec4 FragColor; // default frag color out

// world coordinates
in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;
in vec3 ViewPos;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
}; 
struct SpotLight {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
struct PointLight {    
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;  

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};  
struct DirLight {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};


#define NR_POINT_LIGHTS 4  
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform DirLight dirLight;
uniform SpotLight spotLight;

uniform mat4 view;
uniform Material material;
uniform sampler2D texture_diffuse1;

// prototype functions
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir, mat4 view);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, mat4 view);  
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir, mat4 view); 
float LinearizeDepth(float depth);

// OPTIMIZATIONS | SPECULAR 

 float near = 0.1; 
 float far  = 100.0; 
 

void main()
{
    float depth = LinearizeDepth(gl_FragCoord.z) / far; // divide by far for demonstration
    FragColor = vec4(vec3(depth), 1.0);
    return;
    //FragColor = texture(texture_diffuse1, TexCoords);
    //return;
//    // properties
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(-FragPos);

    // phase 1: Directional lighting
    vec3 result = CalcDirLight(dirLight, norm, viewDir, view);
    // phase 2: Point lights
    for(int i = 0; i < NR_POINT_LIGHTS; i++)
        result += CalcPointLight(pointLights[i], norm, FragPos, viewDir, view);    
    //phase 3: Spot light
    
    result += CalcSpotLight(spotLight, norm, FragPos, viewDir, view);    
    
    FragColor = vec4(result, 1.0);
 
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir, mat4 view)
{   
    // change to world coordinates
    vec3 _lightDir = vec3(view * vec4(light.direction, 0.0));

    vec3 lightDir = normalize(-_lightDir);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // combine results
    vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
    return (ambient + diffuse + specular);
} 

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, mat4 view)
{
    // change to world coordinates
    vec3 _lightPos = vec3(view * vec4(light.position, 1.0));

    vec3 lightDir = normalize(_lightPos - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance    = length(_lightPos - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + 
  			     light.quadratic * (distance * distance));    
    // combine results
    vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
    // apply attenuation
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
} 

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir, mat4 view)
{
    // change to world coordinates
    vec3 _lightPos = vec3(view * vec4(light.position,1.0));
    vec3 _spotDir = vec3(view * vec4(light.direction, 0.0));

    // diffuse shading
    vec3 lightDir = normalize(_lightPos - FragPos);  
    float diff = max(dot(normal, lightDir), 0.0);

    // specular light    
    vec3 reflectDir = reflect(-lightDir, normal); 
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    // spotlight 
    float theta = dot(lightDir, - _spotDir);
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);    

    // combine results
    vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse  = intensity * light.diffuse  * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = intensity * light.specular * spec * vec3(texture(material.specular, TexCoords));
    
    return (ambient + diffuse + specular);
}
 
float LinearizeDepth(float depth) 
{
    float z = depth * 2.0 - 1.0; // back to NDC 
    return (2.0 * near * far) / (far + near - z * (far - near));	
}

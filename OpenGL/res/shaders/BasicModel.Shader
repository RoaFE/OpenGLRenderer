#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;


out vec2 TexCoords;
out vec3 FragPos;
out vec3 Normal;
out mat4 ViewMat;



uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

void main()
{
	gl_Position = u_Projection * u_View * u_Model * vec4(position, 1.0);
    FragPos = vec3(u_View * u_Model * vec4(position, 1.0));
	TexCoords = aTexCoords;
	//Costly and the inverse of the model should be passed instead of calculated
    Normal = mat3(transpose(inverse(u_View * u_Model))) * aNormal;
    //ViewMat = u_View;
}

#shader fragment
#version 330 core
struct DirLight {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform DirLight dirLight;

struct PointLight {
    vec3 position;
    float constant;
    vec3 ambient;
    float linear;
    vec3 diffuse;
    float quadratic;
    vec3 specular;
};
#define NR_POINT_LIGHTS 4 
uniform PointLight pointLights[NR_POINT_LIGHTS];

struct Material
{
    sampler2D diffuse1;
    sampler2D specular1;
    float shininess1;
};


out vec4 FragColor;

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;
//in mat4 ViewMat;
uniform vec3 viewPos;


uniform Material material;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{
    //properties
	vec3 normal = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    //vec3 lightPos = vec3(ViewMat * vec4(light.position, 1.0));
	
    // phase1: Directional lighting
    vec3 result = CalcDirLight(dirLight, normal, viewDir);
    // phase2: Point lights
    for (int i = 0; i < NR_POINT_LIGHTS; i++)
        result += CalcPointLight(pointLights[i], normal, FragPos, viewDir);
    // phase3: Spot light
    //result += CalcSpotLight(spotLight, norm, FragPos, viewDir);
	
    FragColor = vec4(result, 1.0);
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(light.direction);
    //diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    //specular Shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess1);
    //combine results
    vec3 ambient = light.ambient * vec3(texture(material.diffuse1, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse1, TexCoords));
    vec3 specular = vec3(texture(material.specular1, TexCoords)) * spec * light.specular;
    return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    //diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    //specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess1);
    //attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    //combine results
    vec3 ambient = light.ambient * vec3(texture(material.diffuse1, TexCoords));
    vec3 diffuse = light.diffuse * diff* vec3(texture(material.diffuse1, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular1, TexCoords));

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    return (ambient + diffuse + specular);
}

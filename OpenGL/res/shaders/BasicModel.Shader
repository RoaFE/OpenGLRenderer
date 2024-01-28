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
    ViewMat = u_View;
}

#shader fragment
#version 330 core
struct Light
{
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
struct Material
{
    sampler2D diffuse1;
    sampler2D specular1;
    float shininess;
};


out vec4 FragColor;

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;
in mat4 ViewMat;

uniform Light light;

uniform Material material;



void main()
{
    vec3 lightPos = vec3(ViewMat * vec4(light.position, 1.0));
	
    //ambient
    vec3 ambient = light.ambient * vec3(texture(material.diffuse1, TexCoords));
    
    //diffuse
	vec3 normal = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse1, TexCoords));
	
    vec3 viewDir = normalize(-FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
	
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = vec3(texture(material.specular1, TexCoords)) * spec * light.specular;
	
    vec3 result = (ambient + diffuse + specular);
	
    FragColor = vec4(result, 1.0);
}
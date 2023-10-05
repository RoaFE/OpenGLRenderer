#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;

out vec2 TexCoords;
out vec3 WorldPos;
out vec3 Normal;

uniform mat4 u_MVP;
uniform mat4 u_Model;

void main()
{
	gl_Position = u_MVP * vec4(position, 1.0);
	TexCoords = aTexCoords;
	WorldPos = vec3(u_Model * vec4(position,1.0));
	//Costly and the inverse of the model should be passed instead of calculated
    Normal = mat3(transpose(inverse(u_Model))) * aNormal;
}

#shader fragment
#version 330 core

out vec4 FragColor;

in vec2 TexCoords;
in vec3 WorldPos;
in vec3 Normal;
uniform sampler2D texture_diffuse1;
uniform vec3 u_viewPos;
uniform vec3 u_LightColour;
uniform vec4 u_AmbientColour;
uniform vec3 u_LightPos;

float specularStrength = 0.5f;


void main()
{
	
    vec4 colour = texture(texture_diffuse1, TexCoords);
	
	vec3 normal = normalize(Normal);
	vec3 lightDir = normalize(u_LightPos - WorldPos);
	
	float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = u_LightColour * diff;
	
    vec3 viewDir = normalize(u_viewPos - WorldPos);
    vec3 reflectDir = reflect(-lightDir, normal);
	
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * u_LightColour;
	
    vec3 ambient = (u_AmbientColour.xyz) * u_AmbientColour.a;
    vec3 lightColour = (ambient + diffuse + specular);
	
    FragColor = vec4(lightColour, 1.0) * colour;
}
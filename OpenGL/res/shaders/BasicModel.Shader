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
	Normal = aNormal;
}

#shader fragment
#version 330 core

out vec4 FragColor;

in vec2 TexCoords;
in vec3 WorldPos;
in vec3 Normal;
uniform sampler2D texture_diffuse1;
uniform vec3 u_LightColour;
uniform vec4 u_AmbientColour;
uniform vec3 u_LightPos;


void main()
{
	vec3 normal = normalize(Normal);
	vec3 lightDir = normalize(u_LightPos - WorldPos);
	float diff = max(dot(normal, lightDir), 1.0);

	vec4 lightColour = (vec4(u_LightColour, 1.0) * diff) + (vec4(u_AmbientColour.xyz, 1.0) * u_AmbientColour.a);
	FragColor = texture(texture_diffuse1, TexCoords) * lightColour;
}
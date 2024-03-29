#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;

out vec2 v_TexCoord;



uniform mat4 u_MVP;

void main()
{
	gl_Position = u_MVP * position;
	v_TexCoord = texCoord;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 colour;

in vec2 v_TexCoord;
out vec4 FragColour;
uniform vec4 u_Colour;
void main()
{
	FragColour = u_Colour;
};
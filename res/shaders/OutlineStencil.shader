#shader vertex
#version 330 core

layout(location = 0) in vec4 position;

uniform mat4 u_MVP;

void main()
{
	gl_Position = u_MVP * position;
};

#shader fragment
#version 330 core

uniform vec4 u_Colour;

out vec4 FragColour;


void main()
{
	FragColour = u_Colour;
}
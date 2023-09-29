#shader vertex
#version 330 core

layout(location = 0) in vec4 vertex; // <vec2 pos, vec2 tex>

out vec2 TexCoords;

uniform mat4 u_MVP;

void main()
{
	gl_Position = u_MVP * vec4(vertex.xy, 0.0, 1.0);
	TexCoords = vertex.zw;
}

#shader fragment
#version 330 core

in vec2 TexCoords;
out vec4 colour;

uniform sampler2D text;
uniform vec3 textColour;

void main()
{
	vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);
	colour = vec4(textColour, 1.0) * sampled;
}
#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;

out vec2 TexCoords;

uniform mat4 u_MVP;
uniform float u_Time;


void main()
{
    gl_Position = u_MVP * vec4(position, 1.0);
    gl_Position.y = gl_Position.y + sin(u_Time + position.y);
    TexCoords = aTexCoords;
}

#shader fragment
#version 330 core

out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture_diffuse1;


void main()
{
    FragColor = texture(texture_diffuse1, TexCoords);
}
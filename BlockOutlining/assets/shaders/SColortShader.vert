#version 330 core

layout(location  = 0) in vec3 aPos;
//layout(location  = 1) in vec3 aNormal;
layout(location  = 1) in vec2 aTexPos;

out vec2 TexPos;
out vec3 Normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
	TexPos = aTexPos;
	//Normal = aNormal;
	gl_Position = proj * view * model * vec4(aPos, 1.0);
}
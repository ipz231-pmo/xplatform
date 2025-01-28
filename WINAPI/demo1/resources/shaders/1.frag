#version 330 core

// Uniforms block
uniform vec3 Color;

// Out block
out vec4 FragColor;


void main()
{
	FragColor = vec4(Color, 1.0f);
}
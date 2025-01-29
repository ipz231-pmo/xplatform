#version 330 core


// Uniforms block
//uniform mat4 model;
//uniform mat4 view;
//uniform mat4 proj;


// Input block
layout(location  = 0) in vec3 aPos;
//layout(location  = 1) in vec2 aTexPos;


// Output block
//out vec2 TexPos;
//out vec3 Normal;


void main()
{
	//TexPos = aTexPos;
	//Normal = aNormal;
	//gl_Position = proj * view * model * vec4(aPos, 1.0);
	

	gl_Position = vec4(aPos, 1.0);
}
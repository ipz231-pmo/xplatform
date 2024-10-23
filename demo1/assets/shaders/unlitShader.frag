#version 330 core

in vec2 TexPos;

uniform sampler2D tex0;

out vec4 FragColor;

void main()
{
	vec4 texColor = texture(tex0, TexPos);
	//if (texColor.w < 0.99)
	//	discard;
	FragColor = vec4(texColor.xyz, 1.0);
}
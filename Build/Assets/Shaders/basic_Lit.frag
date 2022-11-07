#version 430 core

in vec2 uV;
in vec3 color;

out vec4 fcolor;

uniform sampler2D textureSampler;

void main()
{
	//fcolor = vec4(color * tint, 1.0);
	fcolor = texture(textureSampler, uV) * vec4(color, 1);
}

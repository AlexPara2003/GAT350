#version 430 core

in vec3 color;
in vec2 texcoord;

out vec4 fcolor;

uniform sampler2D textureSampler;

void main()
{
	fcolor = texture(textureSampler, texcoord) * vec4(color, 1);
}
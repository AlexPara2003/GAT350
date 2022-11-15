#version 430 core

in vec3 color;
in vec2 texcoord;

out vec4 fcolor;

uniform vec3 tint;
uniform sampler2D textureSampler;

void main()
{
	fcolor = texture(textureSampler, texcoord) * vec4(1, 1, 1, 1);
}
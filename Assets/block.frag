#version 410

out vec4 fColour;
in vec2 outTextureCoord;

uniform sampler2D textureSampler;

void main()
{
	fColour = texture(textureSampler, outTextureCoord);
}
#version 410

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 textureCoord;

uniform mat4 modelViewProjection;

out vec2 outTextureCoord;

void main()
{
	gl_Position = modelViewProjection * vec4(position, 1.0f);
	outTextureCoord = textureCoord;
}
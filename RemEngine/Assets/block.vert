#version 410

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 textureCoord;
layout (location = 2) in mat4 instanceModel;

uniform mat4 viewProjection;

out vec2 outTextureCoord;

void main()
{
	gl_Position = viewProjection * instanceModel * vec4(position, 1.0f);
	outTextureCoord = textureCoord;
}
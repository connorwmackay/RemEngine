#version 410

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 textureCoord;
layout (location = 2) in vec3 instancePos;

uniform mat4 viewProjection;

out vec2 outTextureCoord;

void main()
{
	mat4 model;
	model[0][0] = 1;
	model[1][1] = 1;
	model[2][2] = 1;
	model[3] = vec4(instancePos, 1.0);

	gl_Position = viewProjection * model * vec4(position, 1.0f);
	outTextureCoord = textureCoord;
}
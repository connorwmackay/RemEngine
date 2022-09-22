#version 410 core

out vec4 fColour;

uniform vec3 customColour;

void main() {
	fColour = vec4(customColour, 1.0f);
}
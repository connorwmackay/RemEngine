#pragma once
#include <glad/glad.h>
#include <vector>
#include <glm/glm.hpp>

#include "shader.h"
#include "textureAtlas.h"

struct Transform
{
	glm::vec3 translation;
	glm::vec3 rotation;
	glm::vec3 scale;
};

struct Mesh
{
	GLuint vao;
	ShaderProgram shaderProgram;
	GLint numVertices;
	bool isUsingIndices;
};

Mesh createColouredCube(glm::vec3 colour);
Mesh createTexturedBlock(TextureAtlas& textureAtlas, const BlockType& blockType);
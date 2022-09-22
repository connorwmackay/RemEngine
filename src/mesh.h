#pragma once
#include <glad/gl.h>
#include <vector>
#include <glm/glm.hpp>

#include "shader.h"
#include "textureAtlas.h"

// Old Mesh stuff

struct Mesh
{
	GLuint vao;
	ShaderProgram shaderProgram;
	GLint numVertices;
	bool isUsingIndices;
};

Mesh createColouredCube(glm::vec3 colour);
Mesh createTexturedBlock(TextureAtlas& textureAtlas, const BlockType& blockType);
#pragma once
#include "block.h"
#include "textureAtlas.h"

/*
 * An instance of this class should only be created after an OpenGL context has been created
 */
class Renderer
{
protected:
	TextureAtlas textureAtlas;
	GLuint blockPositionsBuffer;
public:
	Renderer(TextureAtlas& textureAtlas);
	void Draw(glm::mat4 viewProjection);
};
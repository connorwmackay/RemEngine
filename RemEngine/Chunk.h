#pragma once
#include <vector>

#include "block.h"

#define CHUNK_SIZE glm::vec3(16, 16, 16)

class Chunk
{
protected:
	TextureAtlas textureAtlas;
	Block grass;
	Block dirt;
	Block stone;
	glm::vec3 position;
public:
	Chunk(TextureAtlas& textureAtlas, glm::vec3 position);

	void draw(glm::mat4 viewProjection);
	void replace(glm::vec3 pos);
	void release();

	void getChunkBounds(glm::vec3& position, glm::vec3& size);
};
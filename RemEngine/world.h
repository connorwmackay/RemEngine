#pragma once
#include "block.h"
#include <boost/multi_array.hpp>

#include "Chunk.h"

struct ChunkPosElem
{
	glm::vec3 pos;
	bool isNull;
};

class World
{
protected:
	TextureAtlas textureAtlas;
	glm::vec3 prevCameraPos;
	std::vector<Chunk> chunks;

	glm::vec3 chunkPositions[11][11];
public:
	World();
	World(TextureAtlas& textureAtlas);

	// Update in line with the player position
	void update(glm::vec3 cameraPos);

	void draw(TextureAtlas& textureAtlas, glm::mat4 viewProjection);
};


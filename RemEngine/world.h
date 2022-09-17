#pragma once
#include "block.h"
#include <boost/multi_array.hpp>

#include "Chunk.h"

class World
{
protected:
	TextureAtlas textureAtlas;
	glm::vec3 prevCameraPos;
	std::vector<Chunk> chunks;
public:
	World();
	World(TextureAtlas& textureAtlas);

	// Update in line with the player position
	void update(glm::vec3 cameraPos);

	void draw(TextureAtlas& textureAtlas, glm::mat4 viewProjection);
};


#pragma once
#include "block.h"
#include <boost/multi_array.hpp>

#define Y_BLOCKS 40
#define Z_BLOCKS 192
#define X_BLOCKS 192

#define RENDER_X_DISTANCE 192
#define RENDER_Z_DISTANCE 192

class World
{
protected:
	boost::multi_array<BlockType, 3> blockGrid { boost::extents[Y_BLOCKS][Z_BLOCKS][X_BLOCKS] };

	TextureAtlas textureAtlas;

	Block grass;
	Block dirt;
	Block stone;

	bool hasAddedNewStoneBlock;
public:
	World();
	World(bool useless);

	void create();

	// Update in line with the player position
	void update(glm::vec3 cameraPos);

	void draw(TextureAtlas& textureAtlas, glm::mat4 viewProjection);
};


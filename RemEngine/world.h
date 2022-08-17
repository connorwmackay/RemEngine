#pragma once
#include "block.h"
#include <boost/multi_array.hpp>

#define Y_BLOCKS 20
#define Z_BLOCKS 100
#define X_BLOCKS 100

class World
{
protected:
	boost::multi_array<BlockType, 3> blockGrid { boost::extents[Y_BLOCKS][Z_BLOCKS][X_BLOCKS] };

	TextureAtlas textureAtlas;

	Block grass;
	Block dirt;
	Block stone;
public:
	World();
	World(bool useless);

	void update();
	void draw(TextureAtlas& textureAtlas, glm::mat4 viewProjection);
};


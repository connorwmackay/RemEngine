#pragma once
#include "block.h"
#include <boost/multi_array.hpp>

#define RENDER_Y_DISTANCE 40
#define RENDER_X_DISTANCE 100
#define RENDER_Z_DISTANCE 100

class World
{
protected:
	TextureAtlas textureAtlas;

	Block grass;
	Block dirt;
	Block stone;

	int prevStartX, prevEndX;
	int prevStartZ, prevEndZ;

	glm::vec3 prevCameraPos;

	bool hasAddedNewStoneBlock;
public:
	World();
	World(bool useless);

	void updateWithRenderDistance(glm::vec3 cameraPos);

	// Update in line with the player position
	void update(glm::vec3 cameraPos);

	void draw(TextureAtlas& textureAtlas, glm::mat4 viewProjection);
};


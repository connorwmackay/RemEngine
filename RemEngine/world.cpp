#include "world.h"

#include <GLFW/glfw3.h>

World::World()
{
	
}

World::World(bool useless)
	: textureAtlas(TextureAtlas(false)), grass(textureAtlas, BlockType::Grass),
	dirt(textureAtlas, BlockType::Dirt), stone(textureAtlas, BlockType::Stone),
	hasAddedNewStoneBlock(false), prevCameraPos(glm::vec3(-10.0f, -10.0f, -10.0)),
	prevStartX(0), prevEndX(0), prevStartZ(0), prevEndZ(0)
{

}

void World::updateWithRenderDistance(glm::vec3 cameraPos)
{
	if (glm::floor(cameraPos) == glm::floor(prevCameraPos))
	{
		return;
	}

	prevCameraPos = cameraPos;

	printf("==========\n");
	double startTimeTaken = glfwGetTime();

	int startZ = (int) glm::floor(cameraPos.z - (RENDER_Z_DISTANCE / 2));
	int startX = (int) glm::floor(cameraPos.x - (RENDER_X_DISTANCE / 2));

	int endZ = (int) glm::floor(cameraPos.z + (RENDER_Z_DISTANCE / 2));
	int endX = (int) glm::floor(cameraPos.x + (RENDER_X_DISTANCE / 2));

	grass.removeOutsideBounds(startX, endX, startZ, endZ);
	dirt.removeOutsideBounds(startX, endX, startZ, endZ);
	stone.removeOutsideBounds(startX, endX, startZ, endZ);

	double endTimeTaken = glfwGetTime();
	printf("End Removing instances time: %fms\n", (endTimeTaken - startTimeTaken) * 1000);

	int numBlocksAdded = 0;
	for (int y = RENDER_Y_DISTANCE -1; y >= 0; y--)
	{
		for (int z = startZ; z <= endZ; z++)
		{
			for (int x = startX; x <= endX; x++)
			{
				bool shouldAddBlockInstance = false;

				if (x > prevEndX || z > prevEndZ || x < prevStartX || z < prevStartZ)
				{
					shouldAddBlockInstance = true;
				}

				if (shouldAddBlockInstance)
				{
					if (y == (40 - 1) / 2)
					{
						numBlocksAdded++;
						grass.placeBlock(glm::vec3(x, y, z), false);
					}
				}
			}
		}
	}
	endTimeTaken = glfwGetTime();
	printf("End Adding instances time: %fms\n", (endTimeTaken - startTimeTaken) * 1000);

	printf("Num Blocks Added: %d\n", numBlocksAdded);

	/*
	 * Update the Matrix Models
	 */
	if (!grass.getBlockModels().empty()) {
		grass.updateBlockInstanceModels(UpdateType::AddMultipleElements);
	}

	if (!dirt.getBlockModels().empty()) {
		dirt.updateBlockInstanceModels(UpdateType::AddMultipleElements);
	}

	if (!stone.getBlockModels().empty()) {
		stone.updateBlockInstanceModels(UpdateType::AddMultipleElements);
	}
	
	endTimeTaken = glfwGetTime();
	printf("Update world time time: %fms\n", (endTimeTaken - startTimeTaken) * 1000);

	prevStartX = startX;
	prevEndX = endX;
	prevStartZ = startZ;
	prevEndZ = endZ;
}

void World::update(glm::vec3 cameraPos)
{
	if (!hasAddedNewStoneBlock)
	{
		stone.placeBlock(
			glm::vec3(0, 50, 0),
			true
		);

		hasAddedNewStoneBlock = true;
	}
}

void World::draw(TextureAtlas& textureAtlas, glm::mat4 viewProjection)
{
	grass.drawAll(textureAtlas, viewProjection);
	dirt.drawAll(textureAtlas, viewProjection);
	stone.drawAll(textureAtlas, viewProjection);
}

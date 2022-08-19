#include "world.h"

World::World()
{
	
}

World::World(bool useless)
	: textureAtlas(TextureAtlas(false)), grass(textureAtlas, BlockType::Grass),
	dirt(textureAtlas, BlockType::Dirt), stone(textureAtlas, BlockType::Stone),
	hasAddedNewStoneBlock(false)
{
	// Fill the block grid
	for (int y = Y_BLOCKS-1; y >= 0; y--)
	{
		for (int z=0; z < Z_BLOCKS; z++)
		{
			for (int x=0; x < X_BLOCKS; x++)
			{
				if (y > Y_BLOCKS / 2) {
					blockGrid[y][z][x] = BlockType::Air;
				}
				else if (y == (Y_BLOCKS / 2)) {
					blockGrid[y][z][x] = BlockType::Grass;
				}
				else if (y < (Y_BLOCKS /2) && y > (Y_BLOCKS / 2)-6)
				{
					blockGrid[y][z][x] = BlockType::Dirt;
				}
				else
				{
					blockGrid[y][z][x] = BlockType::Stone;
				}
			}
		}
	}

	// Add the block instances
	create();
}

void World::create()
{
	// TODO: Only add block instances that have at least one adjacent air tile
	for (int y = Y_BLOCKS - 1; y >= 0; y--)
	{
		for (int z = 0; z < Z_BLOCKS; z++)
		{
			for (int x = 0; x < X_BLOCKS; x++)
			{
				BlockType blockType = blockGrid[y][z][x];

				bool isAirBlockAdjacent = false;
				for (int adjY = y + 1; adjY >= y - 1; adjY--)
				{
					for (int adjZ = z - 1; adjZ <= z + 1; adjZ++)
					{
						for (int adjX = x - 1; adjX <= x + 1; adjX++)
						{
							if (adjY > 0 && adjY < Y_BLOCKS-1 &&
								adjZ > 0 && adjZ < Z_BLOCKS-1 &&
								adjX > 0 && adjX < X_BLOCKS-1)
							{
								if (blockGrid[adjY][adjZ][adjX] == BlockType::Air)
								{
									isAirBlockAdjacent = true;
									break;
								}
							}
							else if (adjX == 0 || adjZ == 0 || y == 0 || adjX == X_BLOCKS-1 || adjZ == Z_BLOCKS-1)
							{
								isAirBlockAdjacent = true;
							}
						}
					}
				}

				if (blockType != BlockType::Air && isAirBlockAdjacent) {
					Transform transform = Transform(glm::vec3(x, y, z), glm::vec3(0.0f), glm::vec3(1.0f), true);
					BlockInstance instance = createBlockInstance(transform);

					if (blockType == BlockType::Grass)
					{
						grass.addBlockInstance(instance, false);
					}
					else if (blockType == BlockType::Dirt)
					{
						dirt.addBlockInstance(instance, false);
					}
					else if (blockType == BlockType::Stone)
					{
						stone.addBlockInstance(instance, false);
					}
				}
			}
		}
	}

	grass.updateBlockInstanceModels(UpdateType::AddMultipleElements);
	dirt.updateBlockInstanceModels(UpdateType::AddMultipleElements);
	stone.updateBlockInstanceModels(UpdateType::AddMultipleElements);
}

void World::update(glm::vec3 cameraPos)
{
	if (!hasAddedNewStoneBlock)
	{
		BlockInstance stoneBlock = createBlockInstance(
			Transform(glm::vec3(0, 50, 0), glm::vec3(0.0f), glm::vec3(1.0f), true)
		);

		stone.addBlockInstance(
			stoneBlock,
			true
		);

		dirt.addBlockInstance(
			createBlockInstance(
				Transform(glm::vec3(1, 50, 0), glm::vec3(0.0f), glm::vec3(1.0f), true)
			),
			true
		);

		stoneBlock.transform.translationSet(glm::vec3(0.0f, 51.0f, 0.0f));
		stone.updateBlockInstance(stoneBlock, true);
		hasAddedNewStoneBlock = true;
	}
}

void World::draw(TextureAtlas& textureAtlas, glm::mat4 viewProjection)
{
	grass.drawAll(textureAtlas, viewProjection);
	dirt.drawAll(textureAtlas, viewProjection);
	stone.drawAll(textureAtlas, viewProjection);
}

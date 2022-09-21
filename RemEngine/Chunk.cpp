#include "Chunk.h"

Chunk::Chunk(TextureAtlas& textureAtlas, glm::vec3 position)
	: textureAtlas(textureAtlas), grass(textureAtlas, BlockType::Grass),
	dirt(textureAtlas, BlockType::Dirt), stone(textureAtlas, BlockType::Stone),
	position(position)
{
	for (int y = position.y; y >= position.y-CHUNK_SIZE.y; y--)
	{
		for (int z=position.z; z < position.z + CHUNK_SIZE.z; z++)
		{
			for (int x=position.x; x < position.x + CHUNK_SIZE.x; x++)
			{
				glm::vec3 actualPosition = glm::vec3(x, y, z);

				if (y == 0) {
					grass.placeBlock(actualPosition, false);
				} else if (y < 0 && y > -5)
				{
					dirt.placeBlock(actualPosition, false);
				}
				else if (y <= -5)
				{
					stone.placeBlock(actualPosition, false);
				}

			}
		}
	}

	grass.updateBlockInstanceModels(UpdateType::AddMultipleElements);
	dirt.updateBlockInstanceModels(UpdateType::AddMultipleElements);
	stone.updateBlockInstanceModels(UpdateType::AddMultipleElements);
}

void Chunk::replace(glm::vec3 pos)
{
	position = pos;
	grass.resetBlocks();
	dirt.resetBlocks();
	stone.resetBlocks();

	for (int y = pos.y; y >= pos.y - CHUNK_SIZE.y; y--)
	{
		for (int z = pos.z; z < pos.z + CHUNK_SIZE.z; z++)
		{
			for (int x = pos.x; x < pos.x + CHUNK_SIZE.x; x++)
			{
				glm::vec3 actualPosition = glm::vec3(x, y, z);

				if (y == 0) {
					grass.placeBlock(actualPosition, false);
				}
				else if (y < 0 && y > -5)
				{
					dirt.placeBlock(actualPosition, false);
				}
				else if (y <= -5)
				{
					stone.placeBlock(actualPosition, false);
				}

			}
		}
	}

	grass.updateBlockInstanceModels(UpdateType::AddMultipleElements);
	dirt.updateBlockInstanceModels(UpdateType::AddMultipleElements);
	stone.updateBlockInstanceModels(UpdateType::AddMultipleElements);
}


void Chunk::draw(glm::mat4 viewProjection)
{
	grass.drawAll(textureAtlas, viewProjection);
	dirt.drawAll(textureAtlas, viewProjection);
	stone.drawAll(textureAtlas, viewProjection);
}

void Chunk::release()
{
	grass.release();
	dirt.release();
	stone.release();
}

void Chunk::getChunkBounds(glm::vec3& position, glm::vec3& size)
{
	position = this->position;
	size = CHUNK_SIZE;
}
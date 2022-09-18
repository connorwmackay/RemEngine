#include "world.h"

#include <GLFW/glfw3.h>

int findClosestNumber(int val, int multiple)
{
	int quotient = val / multiple;

	int option1 = multiple * quotient;
	int option2 = multiple * (quotient + 1);

	if (abs(val - option1) < abs(val - option2))
	{
		return option1;
	}

	return option2;
}

World::World()
{
	
}

World::World(TextureAtlas& textureAtlas)
	: textureAtlas(textureAtlas),
	prevCameraPos(glm::vec3(.0f, 1, 0.0)),
	chunks(std::vector<Chunk>())
{
	
}

void World::update(glm::vec3 cameraPos)
{
	glm::vec3 chunkPositions[11][11];

	glm::vec3 middleChunkPos = glm::vec3(
		findClosestNumber(cameraPos.x, 16),
		findClosestNumber(cameraPos.y, 16),
		findClosestNumber(cameraPos.z, 16)
	);

	glm::vec3 firstChunkPos = glm::vec3(
		middleChunkPos.x - (5 * 16),
		middleChunkPos.y,
		middleChunkPos.z - (5 * 16)
	);

	// Find each chunk position
	glm::vec3 *chunksNotLoaded[11][11];
	for (int z=0; z < 11; z++)
	{
		for (int x=0; x < 11; x++)
		{
			glm::vec3 chunkPos = glm::vec3(
				findClosestNumber(firstChunkPos.x + x * 16, 16),
				0,
				findClosestNumber(firstChunkPos.z + z * 16, 16)
			);

			chunkPositions[z][x] = chunkPos;
			chunksNotLoaded[z][x] = &chunkPositions[z][x];
		}
	}
	
	for (int i=0; i < chunks.size(); i++)
	{
		glm::vec3 chunkPos;
		glm::vec3 chunkSize;

		chunks.at(i).getChunkBounds(chunkPos, chunkSize);

		bool isChunkOutOfBounds = true;
		for (int z = 0; z < 11; z++)
		{
			for (int x = 0; x < 11; x++)
			{
				if (chunkPositions[z][x] == chunkPos)
				{
					isChunkOutOfBounds = false;
					chunksNotLoaded[z][x] = nullptr;
				}
			}
		}

		if (isChunkOutOfBounds) {
			chunks.at(i).release();
			chunks.erase(chunks.begin() + i);
		}
	}

	for (int z = 0; z < 11; z++)
	{
		for (int x = 0; x < 11; x++)
		{
			if (chunksNotLoaded[z][x] != nullptr) {
				glm::vec3 notLoadedPos = *chunksNotLoaded[z][x];
				chunks.emplace_back(Chunk(textureAtlas, notLoadedPos));
			}
		}
	}
}

void World::draw(TextureAtlas& textureAtlas, glm::mat4 viewProjection)
{
	for (Chunk& chunk : chunks)
	{
		chunk.draw(viewProjection);
	}
}

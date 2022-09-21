#include "world.h"

#include <future>
#include <thread>
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
	chunks(std::vector<Chunk>()),
	cameraPos(0, 0, 0)
{
	fnSimplex = FastNoise::New<FastNoise::Simplex>();
	fnFractal = FastNoise::New<FastNoise::FractalFBm>();

	fnFractal->SetSource(fnSimplex);
	fnFractal->SetOctaveCount(2);
}

void World::asyncUpdate()
{
	
}

void World::update(glm::vec3 cameraPos)
{
	this->cameraPos = cameraPos;
	std::vector<glm::vec3> chunkPositions = std::vector<glm::vec3>();
	std::vector<int> indexesToRemove = std::vector<int>();

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
	for (int z = 0; z < 11; z++)
	{
		for (int x = 0; x < 11; x++)
		{
			glm::vec3 chunkPos = glm::vec3(
				findClosestNumber(firstChunkPos.x + x * 16, 16),
				0,
				findClosestNumber(firstChunkPos.z + z * 16, 16)
			);

			chunkPositions.push_back(chunkPos);
		}
	}

	for (int i = 0; i < chunks.size(); i++)
	{
		glm::vec3 chunkPos;
		glm::vec3 chunkSize;

		chunks.at(i).getChunkBounds(chunkPos, chunkSize);

		bool isOutOfBounds = true;
		for (int i = 0; i < chunkPositions.size(); i++)
		{
			if (chunkPos == chunkPositions.at(i))
			{
				isOutOfBounds = false;
				chunkPositions.erase(chunkPositions.begin() + i);
			}
		}

		if (isOutOfBounds)
		{
			indexesToRemove.push_back(i);
		}
	}

	for (glm::vec3 chunkPos : chunkPositions)
	{
		if (!indexesToRemove.empty()) {
			Chunk& chunk = chunks.at(indexesToRemove.at(0));

			chunk.setChunkPosition(chunkPos);
			chunk.replace();
			indexesToRemove.erase(indexesToRemove.begin());
		}
		else
		{
			chunks.push_back(Chunk(textureAtlas, fnSimplex, fnFractal, chunkPos));
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

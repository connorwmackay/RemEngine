#include "Chunk.h"

#include <FastNoise/FastNoise.h>
#include <cstdlib>

float GetGrassYValFromNoise(glm::vec3 chunkPosition, float noise)
{
	float yVal = 0.0f;

	float yMax = 16;
	float yMin = 0;

	yVal = abs(floor(noise * (yMax - yMin) + yMin));

	return yVal;
}

Chunk::Chunk()
{
	
}

Chunk::Chunk(TextureAtlas& textureAtlas, FastNoise::SmartNode<FastNoise::Simplex> simplex, FastNoise::SmartNode<FastNoise::FractalFBm> fractal, glm::vec3 position)
	: textureAtlas(textureAtlas),
	fnSimplex(simplex),
	fnFractal(fractal),
	position(position),
	updateFuture(std::shared_future<bool>())
{
	std::vector<float> noise(CHUNK_SIZE.x * CHUNK_SIZE.z);
	fnFractal->GenUniformGrid2D(
		noise.data(),
		position.x, position.z,
		CHUNK_SIZE.x, CHUNK_SIZE.z,
		0.01f, rand() % 1000000
	);

	for (float& noiseVal : noise)
	{
		GetGrassYValFromNoise(position, noiseVal);
	}

	float noiseIndex = 0;
	for (int z = position.z; z < position.z + CHUNK_SIZE.z; z++)
	{
		for (int x = position.x; x < position.x + CHUNK_SIZE.x; x++)
		{
			float grassYVal = GetGrassYValFromNoise(position, noise.at(noiseIndex)) + position.y;

			for (int y = position.y; y <= position.y + CHUNK_SIZE.y; y++)
			{
				glm::vec3 actualPosition = glm::vec3(x, y, z);

				if (y == (int)grassYVal) {
					//grass.placeBlock(actualPosition, false);
				}
				else if (y < grassYVal && y > grassYVal-5)
				{
					//dirt.placeBlock(actualPosition, false);
				}
				else if (y <= grassYVal - 5)
				{
					//stone.placeBlock(actualPosition, false);
				}
			}

			noiseIndex++;
		}
	}

    //grass.useOnlyBlocksExposedToAir();
    //dirt.useOnlyBlocksExposedToAir();
    //stone.useOnlyBlocksExposedToAir();

	//grass.updateBlockInstanceModels(UpdateType::AddMultipleElements);
	//dirt.updateBlockInstanceModels(UpdateType::AddMultipleElements);
	//stone.updateBlockInstanceModels(UpdateType::AddMultipleElements);
}

bool Chunk::asyncReplace()
{
	//grass.resetBlocks();
	//dirt.resetBlocks();
	//stone.resetBlocks();

	std::vector<float> noise(CHUNK_SIZE.x * CHUNK_SIZE.z);
	fnFractal->GenUniformGrid2D(
		noise.data(),
		position.x, position.z,
		CHUNK_SIZE.x, CHUNK_SIZE.z,
		0.01f, rand() % 1000000
	);

	for (float& noiseVal : noise)
	{
		GetGrassYValFromNoise(position, noiseVal);
	}

	float noiseIndex = 0;
	for (int z = position.z; z < position.z + CHUNK_SIZE.z; z++)
	{
		for (int x = position.x; x < position.x + CHUNK_SIZE.x; x++)
		{
			float grassYVal = GetGrassYValFromNoise(position, noise.at(noiseIndex)) + position.y;

			for (int y = position.y; y <= position.y + CHUNK_SIZE.y; y++)
			{
				glm::vec3 actualPosition = glm::vec3(x, y, z);

				if (y == (int)grassYVal) {
					//grass.placeBlock(actualPosition, false);
				}
				else if (y < grassYVal && y > grassYVal - 5)
				{
					//dirt.placeBlock(actualPosition, false);
				}
				else if (y <= grassYVal - 5)
				{
					//stone.placeBlock(actualPosition, false);
				}
			}

			noiseIndex++;
		}
	}

    //grass.useOnlyBlocksExposedToAir();
    //dirt.useOnlyBlocksExposedToAir();
    //stone.useOnlyBlocksExposedToAir();

	isBeingUpdated = true;
	return true;
}

bool Chunk::replace()
{
	updateFuture = std::async(std::launch::async, &Chunk::asyncReplace, this);
	return true;
}

void Chunk::updateBlocks()
{
	//grass.updateBlockInstanceModels(UpdateType::AddMultipleElements);
	//dirt.updateBlockInstanceModels(UpdateType::AddMultipleElements);
	//stone.updateBlockInstanceModels(UpdateType::AddMultipleElements);
	isBeingUpdated = false;
}

void Chunk::setChunkPosition(glm::vec3 pos)
{
	position = pos;
}

void Chunk::draw(glm::mat4 viewProjection)
{

	if (updateFuture.valid()) {
		updateBlocks();
	}

	//grass.drawAll(textureAtlas, viewProjection);
	//dirt.drawAll(textureAtlas, viewProjection);
	//stone.drawAll(textureAtlas, viewProjection);
}

void Chunk::release()
{
	//grass.release();
	//dirt.release();
	//stone.release();
}

void Chunk::getChunkBounds(glm::vec3& position, glm::vec3& size)
{
	position = this->position;
	size = CHUNK_SIZE;
}
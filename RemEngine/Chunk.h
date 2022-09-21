#pragma once
#include <vector>
#include <FastNoise/FastNoise.h>

#include "block.h"

#define CHUNK_SIZE glm::vec3(16, 16, 16)

class Chunk
{
protected:
	TextureAtlas textureAtlas;
	Block grass;
	Block dirt;
	Block stone;

	FastNoise::SmartNode<FastNoise::Simplex> fnSimplex;
	FastNoise::SmartNode<FastNoise::FractalFBm> fnFractal;

	glm::vec3 position;
public:
	Chunk(TextureAtlas& textureAtlas, FastNoise::SmartNode<FastNoise::Simplex> simplex, FastNoise::SmartNode<FastNoise::FractalFBm> fractal, glm::vec3 position);

	void draw(glm::mat4 viewProjection);
	void setChunkPosition(glm::vec3 pos);
	void replace();
	void release();

	void updateBlocks();

	bool isBeingUpdated;

	void getChunkBounds(glm::vec3& position, glm::vec3& size);
};
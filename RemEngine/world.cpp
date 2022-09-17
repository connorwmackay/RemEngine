#include "world.h"

#include <GLFW/glfw3.h>

World::World()
{
	
}

World::World(TextureAtlas& textureAtlas)
	: textureAtlas(textureAtlas),
	prevCameraPos(glm::vec3(.0f, 1, 0.0)),
	chunks(std::vector<Chunk>())
{
	chunks.emplace_back(Chunk(textureAtlas, glm::vec3(0, 0, 0)));
	chunks.emplace_back(Chunk(textureAtlas, glm::vec3(16, 0, 0)));
	chunks.emplace_back(Chunk(textureAtlas, glm::vec3(0, 0, 16)));
	chunks.emplace_back(Chunk(textureAtlas, glm::vec3(16, 0, 16)));
}

void World::update(glm::vec3 cameraPos)
{
	// TODO: Get the 12x12 chunk positions
	// TODO: Delete chunks that aren't one of the positions
	// TODO: Add the new chunks to be loaded in


}

void World::draw(TextureAtlas& textureAtlas, glm::mat4 viewProjection)
{
	for (Chunk& chunk : chunks)
	{
		chunk.draw(viewProjection);
	}
}

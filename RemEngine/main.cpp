#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cassert>
#include <vector>
#include <glm/glm.hpp>

#include "GameInstance.h"
#include "gameObject.h"
#include "mesh.h"
#include "shader.h"
#include "world.h"

int main(int argc, char **argv)
{
	GameInstance gameInstance = GameInstance(45.0f, "Rem Engine", 1280, 720);
	TextureAtlas textureAtlas = gameInstance.getTextureAtlas();

	// Create plane of blocks...
	for (int y = 0; y > -10; y--) {
		BlockType blockType;

		if (y == 0)
		{
			blockType = BlockType::Grass;
		}
		else if (y < 0 && y > -4)
		{
			blockType = BlockType::Dirt;
		}
		else
		{
			blockType = BlockType::Stone;
		}

		for (int z = -10; z < 0; z++) {
			for (int x = -5; x <= 5; x++)
			{
				Mesh cube = createTexturedBlock(textureAtlas, blockType);
				Transform transform = { glm::vec3(x, y, z), glm::vec3(0.0f), glm::vec3(1.0f) };
				GameObject gameObject = GameObject(cube, transform, gameInstance.getViewProjection());
				gameInstance.addGameObject(gameObject);
			}
		}
	}

	gameInstance.runGameLoop();
	return 0;
}
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cassert>
#include <vector>
#include <glm/glm.hpp>

#include "block.h"
#include "gameInstance.h"
#include "mesh.h"
#include "shader.h"
#include "world.h"

int main(int argc, char **argv)
{
	GameInstance gameInstance = GameInstance(45.0f, "Rem Engine", 1280, 720);
	gameInstance.runGameLoop();
	return 0;
}
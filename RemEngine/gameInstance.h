#pragma once
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

#include "block.h"
#include "spectator.h"
#include "textureAtlas.h"
#include "world.h"

void GLAPIENTRY
MessageCallback(GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	const void* userParam);

class GameInstance
{
protected:
	GLFWwindow* window;
	glm::mat4 projection;
	glm::mat4 view;
	glm::mat4 viewProjection;

	float fieldOfView;

	glm::vec2 mouseOffset;

	TextureAtlas textureAtlas;

	glm::vec2 lastKnownWindowSize;

	double frameTimeElapsed;

	Spectator spectator;

	Block grass, dirt, stone;

	// Update all Game Objects etc...
	void update(double deltaTime);

	// Perform all the draw calls etc..
	void render();

	void handleWindowResize();

	// Free any resources...
	void cleanup();
public:
	GameInstance(float fieldOfView, const char* title, unsigned int width, unsigned int height);

	TextureAtlas getTextureAtlas();

	void runGameLoop();

	glm::mat4 getViewProjection() const;
};


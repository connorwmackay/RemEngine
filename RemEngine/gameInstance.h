#pragma once
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

#include "gameObject.h"
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

	TextureAtlas textureAtlas;

	std::vector<GameObject> gameObjects;

	// Update all Game Objects etc...
	void update();

	// Perform all the draw calls etc..
	void render();

	// Free any resources...
	void cleanup();
public:
	GameInstance(float fieldOfView, const char* title, unsigned int width, unsigned int height);

	TextureAtlas getTextureAtlas();

	void runGameLoop();

	void addGameObject(const GameObject& gameObject);
	void removeGameObject(int index);

	glm::mat4 getViewProjection() const;
};


#include "GameInstance.h"

void GLAPIENTRY
MessageCallback(GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	const void* userParam)
{
	fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
		(type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
		type, severity, message);
}

GameInstance::GameInstance(float fieldOfView, const char* title, unsigned int width, unsigned int height)
{
	assert(glfwInit());

	//  GLFW settings
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

	// Window creation
	window = glfwCreateWindow(width, height, title, nullptr, nullptr);
	glfwMakeContextCurrent(window);

	// OpenGL Setup
	assert(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress));
	glViewport(0, 0, width, height);

	// OpenGL Settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(MessageCallback, 0);

	// Matrices
	projection = createPerspective(width, height, fieldOfView);
	view = createView(glm::vec3(0.0f, 0.0f, -10.0f), glm::vec3(30.0f, 0.0f, 0.0f));
	viewProjection = projection * view;

	gameObjects = std::vector<GameObject>();
	textureAtlas = TextureAtlas(false);
}

void GameInstance::update()
{
	// TODO: Update projection / view if relavent changes have occured
	viewProjection = projection * view;

	for (GameObject& gameObject : gameObjects)
	{
		gameObject.update(viewProjection);
	}
}

void GameInstance::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Clear to Black

	for (GameObject& gameObject : gameObjects)
	{
		gameObject.draw(textureAtlas);
	}
}

void GameInstance::cleanup()
{
	GLuint texture = textureAtlas.getTexture();
	glDeleteTextures(1, &texture);
	glfwDestroyWindow(window);
	glfwTerminate();
}

void GameInstance::runGameLoop()
{
	while (!glfwWindowShouldClose(window))
	{
		update();
		render();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	cleanup();
}

void GameInstance::addGameObject(const GameObject& gameObject)
{
	gameObjects.push_back(gameObject);
}

void GameInstance::removeGameObject(int index)
{
	gameObjects.erase(std::begin(gameObjects) + index);
}
glm::mat4 GameInstance::getViewProjection() const
{
	return viewProjection;
}

TextureAtlas GameInstance::getTextureAtlas()
{
	return textureAtlas;
}
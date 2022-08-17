#include "gameInstance.h"

void GLAPIENTRY
MessageCallback(GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	const void* userParam)
{
	if (severity != 0x9147 && severity != 0x826b) {
		fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
			(type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
			type, severity, message);
	}
}

GameInstance::GameInstance(float fieldOfView, const char* title, unsigned int width, unsigned int height)
	: projection(glm::mat4(1.0f)),
    view(glm::mat4(1.0f)),
	viewProjection(glm::mat4(1.0f)),
	fieldOfView(fieldOfView),
	mouseOffset(glm::vec2(0.0f, 0.0f)),
	textureAtlas(TextureAtlas()),
	gameObjects(std::vector<GameObject>()),
	lastKnownWindowSize(glm::vec2(width, height)),
	frameTimeElapsed(0.0),
	spectator(12.0f, 0.2f, Transform(glm::vec3(0.0f, 2.0f, -10.0f), glm::vec3(45.0f, 0.0f, 0.0f), glm::vec3(1.0f), true))
{
	assert(glfwInit());

	//  GLFW settings
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

	// Window creation
	window = glfwCreateWindow(width, height, title, nullptr, nullptr);
	glfwMakeContextCurrent(window);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// OpenGL Setup
	assert(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress));

	// OpenGL Settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(MessageCallback, 0);

	// Setup projection
	projection = createPerspective(width, height, fieldOfView);

	// Setup the view
	view = glm::lookAt(
		spectator.getTransform().translationGet(),
		spectator.getTransform().translationGet() + spectator.getTransform().getForwardVector(),
		spectator.getTransform().getUpVector()
	);

	viewProjection = projection * view;

	// Setup the textureAtlas
	textureAtlas = TextureAtlas(false);
}

void GameInstance::update(double deltaTime)
{
	handleWindowResize();

	// Keyboard Input
	float moveSpeed = 12.0f * (float) deltaTime;

	spectator.checkInput(window, deltaTime, mouseOffset);

	// Update the view to the current cameraTransform
	view = glm::lookAt(
		spectator.getTransform().translationGet(),
		spectator.getTransform().translationGet() + spectator.getTransform().getForwardVector(),
		spectator.getTransform().getUpVector()
	);

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

		double startFrameTimeElapsed = glfwGetTime();
		double mouseStartX, mouseStartY;
		glfwGetCursorPos(window, &mouseStartX, &mouseStartY);

		update(frameTimeElapsed);
		render();
		glfwSwapBuffers(window);
		glfwPollEvents();

		double mouseEndX, mouseEndY;
		glfwGetCursorPos(window, &mouseEndX, &mouseEndY);
		mouseOffset = glm::vec2(mouseStartX - mouseEndX, mouseEndY - mouseStartY);

		double endFrameTimeElapsed = glfwGetTime();
		frameTimeElapsed = endFrameTimeElapsed - startFrameTimeElapsed;
		printf("FPS: %f\n", (1 / frameTimeElapsed));
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

void GameInstance::handleWindowResize()
{
	// Resize the OpenGL viewport if the window size has changed...
	int newWindowWidth, newWindowHeight;
	glfwGetWindowSize(window, &newWindowWidth, &newWindowHeight);

	if (newWindowWidth > 0 && newWindowWidth != (int)lastKnownWindowSize.x ||
		newWindowHeight > 0 && newWindowHeight != (int)lastKnownWindowSize.y)
	{
		glViewport(0, 0, newWindowWidth, newWindowHeight);
		lastKnownWindowSize = glm::vec2(newWindowWidth, newWindowHeight);

		projection = createPerspective(newWindowWidth, newWindowHeight, fieldOfView);
		viewProjection = projection * view;
	}
}
#include "spectator.h"

Spectator::Spectator(float moveSpeed, float mouseSensitivity, const Transform& transform)
	: moveSpeed(moveSpeed), mouseSensitivity(mouseSensitivity), transform(transform)
{
	
}

void Spectator::checkInput(GLFWwindow* window, double deltaTime, glm::vec2 mouseOffset)
{
	float deltaMoveSpeed = moveSpeed * deltaTime;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		transform.translationApplyOffset(transform.getForwardVector() * deltaMoveSpeed);
	}
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		transform.translationApplyOffset(transform.getForwardVector() * -deltaMoveSpeed);
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		transform.translationApplyOffset(transform.getRightVector() * -deltaMoveSpeed);
	}
	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		transform.translationApplyOffset(transform.getRightVector() * deltaMoveSpeed);
	}

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
	{
		transform.translationApplyOffset(glm::vec3(0.0f, deltaMoveSpeed, 0.0f));
	}
	else if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		transform.translationApplyOffset(glm::vec3(0.0f, -deltaMoveSpeed, 0.0f));
	}

	// Mouse Input
	transform.rotationApplyXOffset(mouseOffset.x * mouseSensitivity * (float)deltaTime);
	transform.rotationApplyYOffset(mouseOffset.y * mouseSensitivity * (float)deltaTime);
}

Transform Spectator::getTransform() const
{
	return transform;
}
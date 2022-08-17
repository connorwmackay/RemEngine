#pragma once
#include <GLFW/glfw3.h>

#include "transform.h"

class Spectator
{
protected:
	float moveSpeed;
	float mouseSensitivity;
	Transform transform;
public:
	Spectator(float moveSpeed, float mouseSensitivity, const Transform& transform);

	Transform getTransform() const;

	void checkInput(GLFWwindow* window, double deltaTime, glm::vec2 mouseOffset);
};


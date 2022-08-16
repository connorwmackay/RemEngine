#include "transform.h"

#include <glm/ext/matrix_transform.hpp>

Transform::Transform(glm::vec3 translation, glm::vec3 rotation, glm::vec3 scale, bool useGlobalTranslation)
	: translation(translation), rotation(rotation), scale(scale), model(glm::mat4(1.0f)),
		isUsingGlobalTranslation(useGlobalTranslation)
{
	updateModelMatrix();
}

/* Translation */
void Transform::translationSet(glm::vec3 translation)
{
	this->translation = translation;
	updateModelMatrix();
}

glm::vec3 Transform::translationGet() const
{
	return translation;
}

void Transform::translationApplyOffset(glm::vec3 offset)
{
	translation.x += offset.x;
	translation.y += offset.y;
	translation.z += offset.z;
	updateModelMatrix();
}

/* Rotation */
void Transform::rotationSet(glm::vec3 rotation)
{
	this->rotation = rotation;
	updateModelMatrix();
}

glm::vec3 Transform::rotationGet() const
{
	return rotation;
}

void Transform::rotationApplyOffset(glm::vec3 offset)
{
	rotation += offset;
	updateModelMatrix();
}

void Transform::rotationApplyXOffset(float xOffset)
{
	rotation.x += xOffset;
	updateModelMatrix();
}

void Transform::rotationApplyYOffset(float yOffset)
{
	rotation.y += yOffset;
	updateModelMatrix();
}

void Transform::rotationApplyZOffset(float zOffset)
{
	rotation.z += zOffset;
	updateModelMatrix();
}

/* Scale */
void Transform::scaleSet(glm::vec3 scale)
{
	this->scale = scale;
	updateModelMatrix();
}

glm::vec3 Transform::scaleGet() const
{
	return scale;
}

/* Model Matrix */
glm::mat4 Transform::modelMatrixGet() const
{
	return model;
}

void Transform::updateModelMatrix()
{
	if (isUsingGlobalTranslation) {
		model = glm::translate(model, translation);
		model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, scale);
	}
	else
	{
		model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::translate(model, translation);
		model = glm::scale(model, scale);
	}
}

glm::vec3 Transform::getForwardVector()
{
	glm::vec3 forward;
	forward.x = glm::cos(rotation.y) * glm::sin(rotation.x);
	forward.y = -glm::sin(rotation.y);
	forward.z = glm::cos(rotation.y) * glm::cos(rotation.x);
	return forward;
}

glm::vec3 Transform::getRightVector()
{
	glm::vec3 right;
	right.x = glm::cos(rotation.x);
	right.y = 0.0f;
	right.z = -glm::sin(rotation.x);
	return right;
}

glm::vec3 Transform::getUpVector()
{
	glm::vec3 forward = getForwardVector();
	glm::vec3 right = getRightVector();

	glm::vec3 up = glm::cross(forward, right);
	return up;
}
#pragma once
#include <glm/glm.hpp>

class Transform
{
protected:
	glm::vec3 translation;
	glm::vec3 rotation;
	glm::vec3 scale;

	glm::mat4 model;

	bool isUsingGlobalTranslation;
	/*
	 * Updates the model matrix to the current translation, rotation and scale values.
	 * Called whenever any of those properties get changed via their public functions.
	 */
	void updateModelMatrix();
public:
	Transform();
	Transform(glm::vec3 translation, glm::vec3 rotation, glm::vec3 scale, bool useGlobalTranslation);

	/* Translation */
	void translationSet(glm::vec3 translation);
	glm::vec3 translationGet() const;

	void translationApplyOffset(glm::vec3 offset);

	/* Direction Vectors */
	glm::vec3 getForwardVector();
	glm::vec3 getRightVector();
	glm::vec3 getUpVector();

	/* Rotation */
	void rotationSet(glm::vec3 rotation);
	glm::vec3 rotationGet() const;

	void rotationApplyOffset(glm::vec3 offset);
	void rotationApplyXOffset(float xOffset);
	void rotationApplyYOffset(float yOffset);
	void rotationApplyZOffset(float zOffset);

	/* Scale */
	void scaleSet(glm::vec3 scale);
	glm::vec3 scaleGet() const;

	/* Model Matrix */
	glm::mat4 modelMatrixGet() const;
};


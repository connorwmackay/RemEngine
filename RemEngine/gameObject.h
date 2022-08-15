#pragma once
#include "mesh.h"

class GameObject
{
protected:
	Transform transform;
	Mesh mesh;
	glm::mat4 model;
	glm::mat4 modelViewProjection;
public:
	GameObject(const Mesh& mesh, const Transform& transform, const glm::mat4& viewProjection);

	// Transform functions
	void setPosition(glm::vec3 position);
	void setRotation(glm::vec3 rotation);
	void setScale(glm::vec3 scale);

	Transform getTransform() const;

	// Update
	void update(const glm::mat4& viewProjection);

	// Draw
	void draw(TextureAtlas& textureAtlas) const;
};

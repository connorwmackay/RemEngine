#pragma once
#include "mesh.h"
#include "transform.h"

class GameObject
{
protected:
	Transform transform;
	Mesh mesh;
	glm::mat4 modelViewProjection;
public:
	GameObject(const Mesh& mesh, const Transform& transform, const glm::mat4& viewProjection);

	Transform getTransform() const;

	// Update
	void update(const glm::mat4& viewProjection);

	// Draw
	void draw(TextureAtlas& textureAtlas) const;
};

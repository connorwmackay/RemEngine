#pragma once
#include <glad/glad.h>
#include "mesh.h"
#include "transform.h"

struct BlockInstance
{
	unsigned int id;
	Transform transform;
};

BlockInstance createBlockInstance(const Transform& transform);

/*
 * A specific type of block i.e. Grass Block, which isn't a game object itself,
 * but stores many instances of the block that are game objects.
 */
class Block
{
protected:
	BlockType type;
	Mesh mesh;
	std::vector<BlockInstance> blockInstances;
	std::vector<glm::mat4> blockInstanceModels;

	GLuint lastModelBuffer;
public:
	Block();
	Block(TextureAtlas& textureAtlas, const BlockType& blockType);

	void updateBlockInstanceModels(bool shouldDeleteLastBuffer);

	void resetInstances();
	void addBlockInstance(const BlockInstance& block, bool shouldUpdateModels);
	void updateBlockInstance(const BlockInstance& block, bool shouldUpdateModels);
	void removeBlockInstance(unsigned int blockInstanceId, bool shouldUpdateModels);

	// Draw all instances of this block
	void drawAll(TextureAtlas& textureAtlas, glm::mat4 viewProjection);
};
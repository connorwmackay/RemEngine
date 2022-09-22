#pragma once
#include <glad/gl.h>
#include "mesh.h"
#include "transform.h"

#define RENDER_Y_DISTANCE 40
#define RENDER_X_DISTANCE 100
#define RENDER_Z_DISTANCE 100

enum class UpdateType
{
	UpdateElement,
	AddElement,
	AddMultipleElements,
	RemoveElement,
	InitElements
};

/*
 * A specific type of block i.e. Grass Block, which isn't a game object itself,
 * but stores many instances of the block that are game objects.
 */
class Block
{
protected:
	BlockType type;
	Mesh mesh;

	GLuint cubeVao;
	GLuint cubeVbo;
	GLuint cubeEbo;
	GLuint textureVbo;

	std::vector<glm::vec3> blockModels;

	GLuint lastModelBuffer;

	// Returns -1 if the block doesn't exist
	int findBlockIndex(const glm::vec3& pos);
	int binarySearch(const glm::vec3& pos, int low, int high);
public:
	Block();
	Block(TextureAtlas& textureAtlas, const BlockType& blockType);

	// Update index is only used if updating an element

	void updateBlockInstanceModels(const UpdateType& updateType, int updateIndex = -1);

	void placeBlock(const glm::vec3& pos, bool shouldUpdateModels);
	void updateBlock(const glm::vec3& pos, bool shouldUpdateModels);
	void deleteBlock(const glm::vec3& pos, bool shouldUpdateModels);
	void resetBlocks();
	bool isBlockAtPos(glm::vec3 pos);

	std::vector<glm::vec3>& getBlockModels();

	void removeOutsideBounds(int startX, int endX, int startZ, int endZ);
	
	// Draw all instances of this block
	void drawAll(TextureAtlas& textureAtlas, glm::mat4 viewProjection);

	void release();
};
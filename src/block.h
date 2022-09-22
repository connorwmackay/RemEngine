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

enum class BlockFaces
{
    Top,
    Bottom,
    Left,
    Right,
    Front,
    Back
};

struct Block
{
    std::vector<BlockFaces> visibleFaces;
    BlockType type;
    glm::vec3 pos;
};

/* Get the mesh information for a particular block face */
std::vector<GLfloat> GetBlockFaceVertices(BlockFaces face);
std::vector<GLint> GetBlockFaceIndices(BlockFaces face, int offset);
std::vector<GLfloat> GetBlockTextureCoordinates(BlockFaces face, BlockType type, TextureAtlas &textureAtlas);

/* Find the faces that aren't facing another block */
void FindVisibleFacesInBlocks(std::vector<Block>& blocks);
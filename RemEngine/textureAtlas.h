#pragma once
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>

enum class BlockType
{
	Grass = 2,
	Dirt = 1,
	Stone = 0,
	Air = 3
};

struct FaceTexture
{
	glm::vec2 position;
	glm::vec2 size;
};

struct BlockTexture
{
	BlockType type;

	struct
	{
		FaceTexture top;
		FaceTexture bottom;
		FaceTexture right;
		FaceTexture left;
		FaceTexture front;
		FaceTexture back;
	} faces;
};

class TextureAtlas
{
protected:
	GLuint texture;
	std::vector<BlockTexture> blockTextureCoordinates;
public:
	TextureAtlas();
	TextureAtlas(bool useless);
	GLuint getTexture();
	BlockTexture getBlockTexture(const BlockType& blockType);
};
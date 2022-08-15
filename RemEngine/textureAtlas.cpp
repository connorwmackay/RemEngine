#include "textureAtlas.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

TextureAtlas::TextureAtlas()
{
	
}

TextureAtlas::TextureAtlas(bool useless)
{
	stbi_set_flip_vertically_on_load(true);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	// Give OpenGL the texture data
	int width, height, numChannels;
	unsigned char* data = stbi_load("Assets/textureAtlas.png", &width, &height, &numChannels, 3);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Determine texture coordinates...
	blockTextureCoordinates = std::vector<BlockTexture>();

	int tileSize = 32;
	int numBlocks = height / tileSize;

	float normalisedTileWidth = ((float)tileSize / (float)width);
	float normalisedTileHeight = ((float)tileSize / (float)height);

	for (int y = 0; y < numBlocks; y++)
	{
		BlockTexture blockTexture{};
		blockTexture.type = static_cast<BlockType>(y);

		for (int x = 0; x < 6; x++)
		{
			glm::vec2 faceTexPos = glm::vec2((float)x * normalisedTileWidth, (float)y * normalisedTileHeight);
			glm::vec2 faceTexSize = glm::vec2(normalisedTileWidth, normalisedTileHeight);
			FaceTexture faceTexture = { faceTexPos, faceTexSize };

			switch (x)
			{
			case 0:
				blockTexture.faces.top = faceTexture;
				break;
			case 1:
				blockTexture.faces.bottom = faceTexture;
				break;
			case 2:
				blockTexture.faces.right = faceTexture;
				break;
			case 3:
				blockTexture.faces.left = faceTexture;
				break;
			case 4:
				blockTexture.faces.front = faceTexture;
				break;
			case 5:
				blockTexture.faces.back = faceTexture;
				break;
			}
		}

		blockTextureCoordinates.push_back(blockTexture);
	}

	stbi_image_free(data);
}

BlockTexture TextureAtlas::getBlockTexture(const BlockType& blockType)
{
	BlockTexture blockTexture = {};

	for (const BlockTexture& bTexture : blockTextureCoordinates)
	{
		if (bTexture.type == blockType)
		{
			blockTexture = bTexture;
			break;
		}
	}

	return blockTexture;
}

GLuint TextureAtlas::getTexture()
{
	return texture;
}
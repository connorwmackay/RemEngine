#include "renderer.h"

Renderer::Renderer(TextureAtlas& textureAtlas)
	: textureAtlas(textureAtlas)
{
	GLsizei blockPositionsSize = 0;
	// TODO: Determine the size of block positions...

	glGenBuffers(1, &blockPositionsBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, blockPositionsBuffer);
	glBufferStorage(GL_ARRAY_BUFFER, blockPositionsSize, nullptr, GL_DYNAMIC_STORAGE_BIT);

	// Sub all the data into the buffer...
}

void Renderer::Draw(glm::mat4 viewProjection)
{

}

#include "block.h"

#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

#include "world_matrices.h"

Block::Block()
{
	
}

Block::Block(TextureAtlas& textureAtlas, const BlockType& blockType)
	: type(blockType), mesh({}), blockModels(std::vector<glm::vec3>())
{
	std::vector<GLfloat> blockVerts = std::vector<GLfloat>();
	blockVerts.assign({
		// Front Face
		0.5f, 0.5f, 0.5f, // Top-Front-Right
		-0.5f, 0.5f, 0.5f, // Top-Front-Left
		0.5f, -0.5f, 0.5f, // Bottom-Front-Right
		-0.5f, -0.5f, 0.5f, // Bottom-Front-Left

		// Back Face
		0.5f, 0.5f, -0.5f, // Top-Back-Right
		-0.5f, 0.5f, -0.5f, // Top-Back-Left
		0.5f, -0.5f, -0.5f, // Bottom-Back-Right
		-0.5f, -0.5f, -0.5f, // Bottom-Back-Left

		// Right Face
		0.5f, 0.5f, 0.5f, // Top-Front-Right
		0.5f, 0.5f, -0.5f,  // Top-Back-Right
		0.5f, -0.5f, 0.5f, // Bottom-Front-Right
		0.5f, -0.5f, -0.5f, // Bottom-Back-Right

		// Left Face
		-0.5f, 0.5f, 0.5f, // Top-Front-Left
		-0.5f, 0.5f, -0.5f, // Top-Back-Left
		-0.5f, -0.5f, 0.5f, // Bottom-Front-Left
		-0.5f, -0.5f, -0.5f, // Bottom-Back-Left

		// Top Face
		0.5f, 0.5f, 0.5f, // Top-Front-Right
		-0.5f, 0.5f, 0.5f, // Top-Front-Left
		0.5f, 0.5f, -0.5f, // Top-Back-Right
		-0.5f, 0.5f, -0.5f, // Top-Back-Left

		// Bottom Face
		0.5f, -0.5f, 0.5f, // Bottom-Front-Right
		-0.5f, -0.5f, 0.5f, // Bottom-Front-Left
		0.5f, -0.5f, -0.5f, // Bottom-Back-Right
		-0.5f, -0.5f, -0.5f, // Bottom-Back-Left
	});

	std::vector<GLint> blockIndices = std::vector<GLint>();
	blockIndices.assign({
		// Front Face
		3, 2, 0, 0, 1, 3,

		// Back Face
		7, 6, 4, 4, 5, 7,

		// Right Face
		8, 9, 11, 11, 10, 8,

		// Left Face
		12, 15, 13, 15, 12, 14,

		// Top Face
		19, 16, 17, 18, 16, 19,

		// Bottom Face
		23, 20, 22, 20, 23, 21
	});

	// Get the texture coordinates...
	std::vector<GLfloat> textureCoordinates = std::vector<GLfloat>();
	BlockTexture blockTexture = textureAtlas.getBlockTexture(blockType);

	// Front
	textureCoordinates.push_back(blockTexture.faces.front.position.x + blockTexture.faces.front.size.x);
	textureCoordinates.push_back(blockTexture.faces.front.position.y + blockTexture.faces.front.size.y);

	textureCoordinates.push_back(blockTexture.faces.front.position.x);
	textureCoordinates.push_back(blockTexture.faces.front.position.y + blockTexture.faces.front.size.y);

	textureCoordinates.push_back(blockTexture.faces.front.position.x + blockTexture.faces.front.size.x);
	textureCoordinates.push_back(blockTexture.faces.front.position.y);

	textureCoordinates.push_back(blockTexture.faces.front.position.x);
	textureCoordinates.push_back(blockTexture.faces.front.position.y);

	// Back
	textureCoordinates.push_back(blockTexture.faces.back.position.x + blockTexture.faces.back.size.x);
	textureCoordinates.push_back(blockTexture.faces.back.position.y + blockTexture.faces.back.size.y);

	textureCoordinates.push_back(blockTexture.faces.back.position.x);
	textureCoordinates.push_back(blockTexture.faces.back.position.y + blockTexture.faces.back.size.y);

	textureCoordinates.push_back(blockTexture.faces.back.position.x + blockTexture.faces.back.size.x);
	textureCoordinates.push_back(blockTexture.faces.back.position.y);

	textureCoordinates.push_back(blockTexture.faces.back.position.x);
	textureCoordinates.push_back(blockTexture.faces.back.position.y);

	// Right
	textureCoordinates.push_back(blockTexture.faces.right.position.x + blockTexture.faces.right.size.x);
	textureCoordinates.push_back(blockTexture.faces.right.position.y + blockTexture.faces.right.size.y);

	textureCoordinates.push_back(blockTexture.faces.right.position.x);
	textureCoordinates.push_back(blockTexture.faces.right.position.y + blockTexture.faces.right.size.y);

	textureCoordinates.push_back(blockTexture.faces.right.position.x + blockTexture.faces.right.size.x);
	textureCoordinates.push_back(blockTexture.faces.right.position.y);

	textureCoordinates.push_back(blockTexture.faces.right.position.x);
	textureCoordinates.push_back(blockTexture.faces.right.position.y);

	// Left
	textureCoordinates.push_back(blockTexture.faces.left.position.x + blockTexture.faces.left.size.x);
	textureCoordinates.push_back(blockTexture.faces.left.position.y + blockTexture.faces.left.size.y);

	textureCoordinates.push_back(blockTexture.faces.left.position.x);
	textureCoordinates.push_back(blockTexture.faces.left.position.y + blockTexture.faces.left.size.y);

	textureCoordinates.push_back(blockTexture.faces.left.position.x + blockTexture.faces.left.size.x);
	textureCoordinates.push_back(blockTexture.faces.left.position.y);

	textureCoordinates.push_back(blockTexture.faces.left.position.x);
	textureCoordinates.push_back(blockTexture.faces.left.position.y);

	// Top
	textureCoordinates.push_back(blockTexture.faces.top.position.x + blockTexture.faces.top.size.x);
	textureCoordinates.push_back(blockTexture.faces.top.position.y + blockTexture.faces.top.size.y);

	textureCoordinates.push_back(blockTexture.faces.top.position.x);
	textureCoordinates.push_back(blockTexture.faces.top.position.y + blockTexture.faces.top.size.y);

	textureCoordinates.push_back(blockTexture.faces.top.position.x + blockTexture.faces.top.size.x);
	textureCoordinates.push_back(blockTexture.faces.top.position.y);

	textureCoordinates.push_back(blockTexture.faces.top.position.x);
	textureCoordinates.push_back(blockTexture.faces.top.position.y);

	// Bottom
	textureCoordinates.push_back(blockTexture.faces.bottom.position.x + blockTexture.faces.bottom.size.x);
	textureCoordinates.push_back(blockTexture.faces.bottom.position.y + blockTexture.faces.bottom.size.y);

	textureCoordinates.push_back(blockTexture.faces.bottom.position.x);
	textureCoordinates.push_back(blockTexture.faces.bottom.position.y + blockTexture.faces.bottom.size.y);

	textureCoordinates.push_back(blockTexture.faces.bottom.position.x + blockTexture.faces.bottom.size.x);
	textureCoordinates.push_back(blockTexture.faces.bottom.position.y);

	textureCoordinates.push_back(blockTexture.faces.bottom.position.x);
	textureCoordinates.push_back(blockTexture.faces.bottom.position.y);

	ShaderProgram blockShader = createShaderProgram("Assets/block.vert", "Assets/block.frag");

	GLuint cubeVao;
	glGenVertexArrays(1, &cubeVao);
	glBindVertexArray(cubeVao);

	GLuint cubeVbo;
	glGenBuffers(1, &cubeVbo);
	glBindBuffer(GL_ARRAY_BUFFER, cubeVbo);
	glBufferData(GL_ARRAY_BUFFER, blockVerts.size() * sizeof(GLfloat), blockVerts.data(), GL_STATIC_DRAW);

	GLuint cubeEbo;
	glGenBuffers(1, &cubeEbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEbo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, blockIndices.size() * sizeof(GLint), blockIndices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);

	GLuint textureVbo;
	glGenBuffers(1, &textureVbo);
	glBindBuffer(GL_ARRAY_BUFFER, textureVbo);
	glBufferData(GL_ARRAY_BUFFER, textureCoordinates.size() * sizeof(GLfloat), textureCoordinates.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(1);

	mesh.vao = cubeVao;
	mesh.shaderProgram = blockShader;
	mesh.isUsingIndices = true;
	mesh.numVertices = blockIndices.size();

	glUseProgram(blockShader);
	GLint textureSamplerLoc = glGetUniformLocation(blockShader, "textureSampler");
	glUniform1i(textureSamplerLoc, 0);

	GLuint modelsBuf;
	glGenBuffers(1, &modelsBuf);
	lastModelBuffer = modelsBuf;
	updateBlockInstanceModels(UpdateType::InitElements);
}

int Block::findBlockIndex(const glm::vec3& pos)
{
	int index = -1;

	for (int i=0; i < blockModels.size(); i++)
	{
		if (blockModels.at(i) == pos)
		{
			index = i;
			break;
		}
	}

	return index;
}

void Block::updateBlockInstanceModels(const UpdateType& updateType, int updateIndex)
{
	glBindBuffer(GL_ARRAY_BUFFER, lastModelBuffer);

	switch(updateType)
	{
	case UpdateType::AddElement:
		{
			GLint size;
			glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);

			if (blockModels.size() * sizeof(glm::vec3) > size)
			{
				glBufferData(
					GL_ARRAY_BUFFER,
					blockModels.size() * sizeof(glm::vec3) + (10000 * sizeof(glm::vec3)),
					NULL,
					GL_STREAM_DRAW
				);
			}

			glBufferSubData(
				GL_ARRAY_BUFFER,
				(blockModels.size() - 1) * sizeof(glm::vec3),
				sizeof(glm::vec3),
				&blockModels.at(blockModels.size() - 1)
			);

			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
		break;
	case UpdateType::AddMultipleElements:
		{
			GLint size;
			glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);

			if (blockModels.size() * sizeof(glm::vec3) > size)
			{
				glBufferData(
					GL_ARRAY_BUFFER,
					blockModels.size() * sizeof(glm::vec3) + (10000 * sizeof(glm::vec3)),
					NULL,
					GL_STREAM_DRAW
				);
			}

			glBufferSubData(
				GL_ARRAY_BUFFER,
				0,
				blockModels.size() * sizeof(glm::vec3),
				blockModels.data()
			);

			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
		break;
	case UpdateType::UpdateElement:
		{
			glBufferSubData(
				GL_ARRAY_BUFFER,
				updateIndex * sizeof(glm::vec3),
				sizeof(glm::vec3),
				&blockModels.at(updateIndex)
			);

			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
		break;
	case UpdateType::RemoveElement:
		{
			GLsizei totalSize = blockModels.size() * sizeof(glm::vec3);
			GLsizei removeSize = totalSize - ((updateIndex) * sizeof(glm::vec3));

			glBufferSubData(
				GL_ARRAY_BUFFER,
				(updateIndex) * sizeof(glm::vec3),
				removeSize,
				blockModels.data() + updateIndex
			);

			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
		break;
	case UpdateType::InitElements:
		{
			glBufferData(
				GL_ARRAY_BUFFER,
				20000 * sizeof(glm::vec3),
				NULL,
				GL_STREAM_DRAW
			);

			glBindVertexArray(mesh.vao);
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
			glVertexAttribDivisor(2, 1);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);

		}
		break;
	}
}

void Block::placeBlock(const glm::vec3& pos, bool shouldUpdateModels)
{
	blockModels.push_back(pos);

	if (shouldUpdateModels)
	{
		updateBlockInstanceModels(UpdateType::AddElement);
	}
}

void Block::updateBlock(const glm::vec3& pos, bool shouldUpdateModels)
{
	int updateIndex = findBlockIndex(pos);

	if (updateIndex != -1) {
		blockModels.at(updateIndex) = pos;

		if (shouldUpdateModels) {
			updateBlockInstanceModels(UpdateType::UpdateElement, updateIndex);
		}
	}
}

void Block::deleteBlock(const glm::vec3& pos, bool shouldUpdateModels)
{
	int indexToDelete = findBlockIndex(pos);

	if (indexToDelete != -1) {
		blockModels.erase(std::begin(blockModels) + indexToDelete);

		if (shouldUpdateModels) {
			updateBlockInstanceModels(UpdateType::RemoveElement, indexToDelete);
		}
	}
}

void Block::drawAll(TextureAtlas& textureAtlas, glm::mat4 viewProjection)
{
	if (!blockModels.empty())
	{
		glUseProgram(mesh.shaderProgram);
		glBindTexture(GL_TEXTURE_2D, textureAtlas.getTexture());
		glBindVertexArray(mesh.vao);

		GLint vpLoc = glGetUniformLocation(mesh.shaderProgram, "viewProjection");
		glUniformMatrix4fv(vpLoc, 1, GL_FALSE, glm::value_ptr(viewProjection));

		glDrawElementsInstanced(GL_TRIANGLES, mesh.numVertices, GL_UNSIGNED_INT, 0, blockModels.size());
	}
}

std::vector<glm::vec3>& Block::getBlockModels()
{
	return blockModels;
}

void Block::removeOutsideBounds(int startX, int endX, int startZ, int endZ)
{
	int numRemoved = 0;
	for (int i=0; i < blockModels.size(); i++)
	{
		glm::vec3& pos = blockModels.at(i);

		if (pos.z < startZ || pos.z > endZ
			|| pos.x < startX || pos.x > endX)
		{
			blockModels.erase(std::begin(blockModels) + i);
			numRemoved++;
		}
	}

	printf("Num Blocks Removed: %d\n", numRemoved);
}
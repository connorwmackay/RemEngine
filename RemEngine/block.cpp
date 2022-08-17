#include "block.h"

#include <glm/gtc/type_ptr.hpp>

BlockInstance createBlockInstance(const Transform& transform)
{
	static unsigned int latestID = 0;

	BlockInstance blockInstance = {
		latestID++,
		transform,
	};

	return blockInstance;
}

Block::Block()
{
	
}

Block::Block(TextureAtlas& textureAtlas, const BlockType& blockType)
	: type(blockType), mesh({}),blockInstances(std::vector<BlockInstance>()),
	blockInstanceModels(std::vector<glm::mat4>())
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
		0, 1, 3, 0, 2, 3,

		// Back Face
		4, 5, 7, 4, 6, 7,

		// Right Face
		8, 11, 10, 9, 8, 11,

		// Left Face
		13, 14, 15, 12, 13, 14,

		// Top Face
		19, 16, 17, 18, 16, 19,

		// Bottom Face
		21, 22, 23, 20, 21, 22
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
}

void Block::updateBlockInstanceModels()
{
	blockInstanceModels = std::vector<glm::mat4>();

	for (const BlockInstance& blockInstance : blockInstances)
	{
		glm::mat4 model = blockInstance.transform.modelMatrixGet();
		blockInstanceModels.push_back(model);
	}

	size_t vec4Size = sizeof(glm::vec4);
	glBindVertexArray(mesh.vao);

	GLuint modelsBuf;
	glGenBuffers(1, &modelsBuf);
	glBindBuffer(GL_ARRAY_BUFFER, modelsBuf);
	glBufferData(GL_ARRAY_BUFFER, blockInstanceModels.size() * sizeof(glm::mat4), &blockInstanceModels[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)0);
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)vec4Size);
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(2 * vec4Size));
	glEnableVertexAttribArray(5);
	glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(3 * vec4Size));

	glVertexAttribDivisor(2, 1);
	glVertexAttribDivisor(3, 1);
	glVertexAttribDivisor(4, 1);
	glVertexAttribDivisor(5, 1);

	glBindVertexArray(0);
}

void Block::addBlockInstance(const BlockInstance& block)
{
	blockInstances.push_back(block);
	updateBlockInstanceModels();
}

void Block::updateBlockInstance(const BlockInstance& block)
{
	for (BlockInstance& blockInstance : blockInstances)
	{
		if (blockInstance.id == block.id) {
			blockInstance = block;
			break;
		}
	}

	updateBlockInstanceModels();
}

void Block::removeBlockInstance(unsigned int blockInstanceId)
{
	int indexToDelete = -1;

	for (int i=0; i < blockInstances.size(); i++)
	{
		if (blockInstances[i].id == blockInstanceId)
		{
			indexToDelete = i;
			break;
		}
	}

	if (indexToDelete != -1)
	{
		blockInstances.erase(std::begin(blockInstances) + indexToDelete);
	}

	updateBlockInstanceModels();
}

void Block::drawAll(TextureAtlas& textureAtlas, glm::mat4 viewProjection)
{
	if (!blockInstances.empty())
	{
		glUseProgram(mesh.shaderProgram);
		glBindTexture(GL_TEXTURE_2D, textureAtlas.getTexture());
		glBindVertexArray(mesh.vao);

		GLint vpLoc = glGetUniformLocation(mesh.shaderProgram, "viewProjection");
		glUniformMatrix4fv(vpLoc, 1, GL_FALSE, glm::value_ptr(viewProjection));

		glDrawElementsInstanced(GL_TRIANGLES, mesh.numVertices, GL_UNSIGNED_INT, 0, blockInstanceModels.size());
	}
}
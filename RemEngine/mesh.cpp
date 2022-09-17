#include "mesh.h"

#include <glm/gtc/type_ptr.hpp>

#include "world.h"
#include <cstddef>

Mesh createColouredCube(glm::vec3 colour)
{
	Mesh mesh{};
	ShaderProgram exampleShader = createShaderProgram("Assets/coloured.vert", "Assets/coloured.frag");

	std::vector<GLfloat> cubeVerts = std::vector<GLfloat>();
	cubeVerts.assign({
		0.5f, 0.5f, 0.5f, // Top-Front-Right
		-0.5f, 0.5f, 0.5f, // Top-Front-Left
		0.5f, -0.5f, 0.5f, // Bottom-Front-Right
		-0.5f, -0.5f, 0.5f, // Bottom-Front-Left

		0.5f, 0.5f, -0.5f, // Top-Back-Right
		-0.5f, 0.5f, -0.5f, // Top-Back-Left
		0.5f, -0.5f, -0.5f, // Bottom-Back-Right
		-0.5f, -0.5f, -0.5f, // Bottom-Back-Left
	});

	std::vector<GLint> cubeIndices = std::vector<GLint>();
	cubeIndices.assign({
		// Front Face
		0, 1, 3, 0, 2, 3,
		// Back Face
		4, 5, 7, 4, 6, 7,
		// Top Face
		0, 1, 4, 1, 5, 4,
		// Bottom Face
		2, 3, 6, 3, 7, 6,
		// Left Side
		1, 5, 3, 3, 7, 5,
		// Right Side
		0, 4, 2, 2, 6, 4
	});

	GLuint cubeVao;
	glGenVertexArrays(1, &cubeVao);
	glBindVertexArray(cubeVao);

	GLuint cubeVbo;
	glGenBuffers(1, &cubeVbo);
	glBindBuffer(GL_ARRAY_BUFFER, cubeVbo);
	glBufferData(GL_ARRAY_BUFFER, cubeVerts.size() * sizeof(GLfloat), cubeVerts.data(), GL_STATIC_DRAW);

	GLuint cubeEbo;
	glGenBuffers(1, &cubeEbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEbo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, cubeIndices.size() * sizeof(GLint), cubeIndices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);

	glUseProgram(exampleShader);
	GLint colourLoc = glGetUniformLocation(exampleShader, "customColour");
	glUniform3fv(colourLoc, 1, glm::value_ptr(colour));

	mesh.vao = cubeVao;
	mesh.shaderProgram = exampleShader;
	mesh.isUsingIndices = true;
	mesh.numVertices = cubeIndices.size();
	return mesh;
}

Mesh createTexturedBlock(TextureAtlas& textureAtlas, const BlockType& blockType)
{
	Mesh block{};

	std::vector<GLfloat> cubeVerts = std::vector<GLfloat>();
	cubeVerts.assign({
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

	std::vector<GLint> cubeIndices = std::vector<GLint>();
	cubeIndices.assign({
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
	glBufferData(GL_ARRAY_BUFFER, cubeVerts.size() * sizeof(GLfloat), cubeVerts.data(), GL_STATIC_DRAW);

	GLuint cubeEbo;
	glGenBuffers(1, &cubeEbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEbo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, cubeIndices.size() * sizeof(GLint), cubeIndices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);

	GLuint textureVbo;
	glGenBuffers(1, &textureVbo);
	glBindBuffer(GL_ARRAY_BUFFER, textureVbo);
	glBufferData(GL_ARRAY_BUFFER, textureCoordinates.size() * sizeof(GLfloat), textureCoordinates.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(1);

	block.vao = cubeVao;
	block.shaderProgram = blockShader;
	block.isUsingIndices = true;
	block.numVertices = cubeIndices.size();

	glUseProgram(blockShader);
	GLint textureSamplerLoc = glGetUniformLocation(blockShader, "textureSampler");
	glUniform1i(textureSamplerLoc, 0);

	return block;
}

AMesh createMesh(std::vector<AVertex> vertices, std::vector<GLuint> indices, std::vector<ATexture> textures)
{
	AMesh mesh{};
	mesh.vertices = vertices;
	mesh.indices = indices;
	mesh.textures = textures;

	glGenVertexArrays(1, &mesh.vao);
	glGenBuffers(1, &mesh.vbo);
	glGenBuffers(1, &mesh.ebo);

	glBindVertexArray(mesh.vao);
	glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);
	glBufferData(GL_ARRAY_BUFFER, mesh.vertices.size() * sizeof(AVertex), &mesh.vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.indices.size() * sizeof(GLuint), &mesh.indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(AVertex), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(AVertex), (void*) offsetof(AVertex, normal));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(AVertex), (void*) offsetof(AVertex, textureCoord));

	glBindVertexArray(0);

	return mesh;
}

void drawMesh(const AMesh& mesh)
{
	GLuint diffuseNum = 1;
	GLuint specularNum = 1;

	for (GLuint i = 0; i < mesh.textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		std::string number;
	}
}
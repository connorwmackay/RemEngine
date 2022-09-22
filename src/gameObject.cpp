#include "gameObject.h"

#include "world.h"
#include <glm/gtc/type_ptr.hpp>

GameObject::GameObject(const Mesh& mesh, const Transform& transform, const glm::mat4& viewProjection)
	: mesh(mesh), transform(transform)
{
	modelViewProjection = viewProjection * transform.modelMatrixGet();
}

Transform GameObject::getTransform() const
{
	return transform;
}

void GameObject::update(const glm::mat4& viewProjection)
{
	modelViewProjection = viewProjection * transform.modelMatrixGet();

	// Pass the modelViewProjection matrix to the shader
	glUseProgram(mesh.shaderProgram);
	GLuint mvpLoc = glGetUniformLocation(mesh.shaderProgram, "modelViewProjection");
	glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, glm::value_ptr(modelViewProjection));
}

void GameObject::draw(TextureAtlas& textureAtlas) const
{
	glUseProgram(mesh.shaderProgram);
	glBindTexture(GL_TEXTURE_2D, textureAtlas.getTexture());
	glBindVertexArray(mesh.vao);

	if (mesh.isUsingIndices) {
		glDrawElements(GL_TRIANGLES, mesh.numVertices, GL_UNSIGNED_INT, 0);
	}
	else
	{
		glDrawArrays(GL_TRIANGLES, 0, mesh.numVertices / 3);
	}
}
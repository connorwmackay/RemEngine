#include "gameObject.h"

#include "world.h"

GameObject::GameObject(const Mesh& mesh, const Transform& transform, const glm::mat4& viewProjection)
	: mesh(mesh), transform(transform)
{
	model = createModel(transform.translation, transform.rotation, transform.scale);
	modelViewProjection = viewProjection * model;
}

void GameObject::setPosition(glm::vec3 position)
{
	transform.translation = position;
	model = createModel(transform.translation, transform.rotation, transform.scale);
}

void GameObject::setRotation(glm::vec3 rotation)
{
	transform.rotation = rotation;
	model = createModel(transform.translation, transform.rotation, transform.scale);
}

void GameObject::setScale(glm::vec3 scale)
{
	transform.scale = scale;
	model = createModel(transform.translation, transform.rotation, transform.scale);
}

Transform GameObject::getTransform() const
{
	return transform;
}

void GameObject::update(const glm::mat4& viewProjection)
{
	modelViewProjection = viewProjection * model;

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
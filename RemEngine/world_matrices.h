#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

inline glm::mat4 createPerspective(GLuint width, GLuint height, GLfloat fieldOfView)
{
	glm::mat4 perspective = glm::mat4(1.0f);
	perspective = glm::perspective(glm::radians(fieldOfView), (GLfloat)((float)width / (float)height), 0.1f, 200.0f);
	return perspective;
}

inline glm::mat4 createOrthographic(GLuint width, GLuint height)
{
	glm::mat4 orthographic = glm::mat4(1.0f);
	orthographic = glm::ortho(0.0f, (GLfloat)width, (GLfloat)height, 0.0f, 0.1f, 100.0f);
	return orthographic;
}

inline glm::mat4 createView(glm::vec3 translation, glm::vec3 rotation)
{
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::translate(view, translation);
	view = glm::rotate(view, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	view = glm::rotate(view, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	view = glm::rotate(view, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	return view;
}

inline glm::mat4 createModel(glm::vec3 translation, glm::vec3 rotation, glm::vec3 scale)
{
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, translation);
	model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, scale);
	return model;
}

inline glm::mat4 createModelViewProjection(glm::mat4 projection, glm::mat4 view, glm::mat4 model)
{
	glm::mat4 modelViewProjection = glm::mat4(1.0f);
	modelViewProjection = projection * view * model;
	return modelViewProjection;
}
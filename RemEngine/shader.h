#pragma once
#include <string>
#include <glad/glad.h>

typedef GLuint ShaderProgram;

ShaderProgram createShaderProgram(const char* vertexFile, const char* fragFile);
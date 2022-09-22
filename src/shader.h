#pragma once
#include <string>
#include <glad/gl.h>

typedef GLuint ShaderProgram;

ShaderProgram createShaderProgram(const char* vertexFile, const char* fragFile);
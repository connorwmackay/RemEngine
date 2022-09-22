#include "shader.h"
#include <vector>

ShaderProgram createShaderProgram(const char* vertexFile, const char* fragFile)
{
	ShaderProgram program = glCreateProgram();

	// Vertex Shader
	std::string vertexData;
	FILE* vFile = nullptr;
	fopen_s(&vFile, vertexFile, "r");

	if (vFile != nullptr)
	{
		uint8_t buf[128];
		size_t numRead = 0;
		while ((numRead = fread_s(buf, 128 * sizeof(uint8_t), sizeof(uint8_t), 128, vFile)) > 0)
		{
			for (int i=0; i < static_cast<int>(numRead); i++)
			{
				vertexData += static_cast<char>(buf[i]);
			}
		}
	}

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	const char* vDataCStr = vertexData.c_str();
	glShaderSource(vertexShader, 1, &vDataCStr, nullptr);
	glCompileShader(vertexShader);

	// TODO: Check for Shader compilation errors...
	GLint success;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		GLchar infoLog[512];
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		printf("Vertex Shader Compilation Error: %s", infoLog);
	}

	// Fragment Shader
	std::string fragData;
	FILE* fFile = nullptr;
	fopen_s(&fFile, fragFile, "r");

	if (fFile != nullptr)
	{
		uint8_t buf[128];
		size_t numRead = 0;
		while ((numRead = fread_s(buf, 128 * sizeof(uint8_t), sizeof(uint8_t), 128, fFile)) > 0)
		{
			for (int i = 0; i < static_cast<int>(numRead); i++)
			{
				fragData += static_cast<char>(buf[i]);
			}
		}
	}

	GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	const char* fDataCStr = fragData.c_str();
	glShaderSource(fragShader, 1, &fDataCStr, nullptr);
	glCompileShader(fragShader);

	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		GLchar infoLog[512];
		glGetShaderInfoLog(fragShader, 512, NULL, infoLog);
		printf("Fragment Shader Compilation Error: %s", infoLog);
	}

	// Attach To & Link Program
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragShader);
	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		GLchar infoLog[512];
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		printf("Program Linking Error: %s", infoLog);
	}

	// Free Resources
	glDeleteShader(vertexShader);
	glDeleteShader(fragShader);
	if (vFile != nullptr) {
		fclose(vFile);
	}

	if (fFile != nullptr) {
		fclose(fFile);
	}

	return program;
}
#include "Shader.h"

uint Shader::CreateShader(uint shaderType, char const* shaderSource)
{
	// создаем шейдер
	uint shader = glCreateShader(shaderType);

	// загружаем исходный код шейдера
	glShaderSource(shader, 1, &shaderSource, NULL);

	return shader;
}

void Shader::Compile(uint shader)
{

	glCompileShader(shader);

	GLint compileStatus;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);

	if (compileStatus != GL_TRUE)
	{
		int length;
		std::string log;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
		log.reserve(static_cast<unsigned long>(length));
		glGetShaderInfoLog(shader, length, &length, &log[0]);

		throw std::runtime_error(log);
	}

}

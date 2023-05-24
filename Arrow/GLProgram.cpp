#include "GLProgram.h"

GLProgram::GLProgram()
{
	program = glCreateProgram();
}

void GLProgram::Link()
{
	glLinkProgram(program);

	GLint linkStatus;
	glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);

	if (linkStatus != GL_TRUE)
	{
		int length;
		std::string log;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
		log.reserve(static_cast<unsigned long>(length));
		glGetProgramInfoLog(program, length, &length, &log[0]);

		throw std::runtime_error(log);
	}

}

void GLProgram::AttachShader(uint shader)
{

	glAttachShader(program, shader);
	shaders.push_back(shader);
}

void GLProgram::Start()
{
	glUseProgram(program);
}

void GLProgram::Stop()
{
	glUseProgram(NULL);
}

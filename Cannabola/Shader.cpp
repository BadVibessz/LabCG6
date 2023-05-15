#include "Shader.h"

Shader::Shader(uint shaderType, char const* shaderSource)
{
	_shaderType = shaderType;
	_shaderSource = shaderSource;

	// ������� ������
	_shader = glCreateShader(_shaderType);

	// ��������� �������� ��� �������
	glShaderSource(_shader, 1, &_shaderSource, NULL);

	// ������� ���������
	_program = glCreateProgram();

	// ��������� ������ � ����������
	glAttachShader(_program, _shader);

	// ����������� ������
	Compile();

	// ��������� ���������
	Link();

	// ��������� ��������� ���������
	Start();
}

void Shader::Compile() const
{
	// ����������� ������
	glCompileShader(_shader);

	// �������� ������ ������������������ �������
	GLint compileStatus;
	glGetShaderiv(_shader, GL_COMPILE_STATUS, &compileStatus);

	if (compileStatus != GL_TRUE)
	{
		glDeleteShader(_shader);
		glDeleteProgram(_program);
		throw std::runtime_error("Cannot compile shader");
	}
}

void Shader::Link() const
{
	// ��������� ���������
	glLinkProgram(_program);

	// ����������� ������ �������� ���������� ���������
	GLint linkStatus;
	glGetProgramiv(_program, GL_LINK_STATUS, &linkStatus);

	if (linkStatus != GL_TRUE)
	{
		glDeleteShader(_shader);
		glDeleteProgram(_program);
		throw std::runtime_error("Cannot link program");
	}
}

Shader::~Shader()
{
	// ������ ����� �������� �� �������� ����� ���������� ���������
	// (� ���� ����� ������������� ��� � ���)
	// �� ����� ������ ����� ����, ��� ����� ���������� �� ���)
	glDeleteShader(_shader);

	// ����� ����, ��� ��������� ������������, ����� ����������� 
	// �� ��� ������, �.�. �� ��� ����� ���� �� ����� �� ����������
	glDetachShader(_program, _shader);
	// ����� ������������ �� ���������, ������ ����� ������, �.�.
	// �� �������� ��� �� �������� ��� ������ glDeleteShader

	// ������� ��������� ���������
	glDeleteProgram(_program);
}

void Shader::Start() const
{
	glUseProgram(_program);
}

void Shader::Stop() const
{
	glUseProgram(NULL);
}

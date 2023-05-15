#include "Shader.h"

Shader::Shader(uint shaderType, char const* shaderSource)
{
	_shaderType = shaderType;
	_shaderSource = shaderSource;

	// создаем шейдер
	_shader = glCreateShader(_shaderType);

	// загружаем исходный код шейдера
	glShaderSource(_shader, 1, &_shaderSource, NULL);

	// создаем программу
	_program = glCreateProgram();

	// свзявыаем шейдер с программой
	glAttachShader(_program, _shader);

	// компилируем шейдер
	Compile();

	// компонуем программу
	Link();

	// запускаем шейдерную программу
	Start();
}

void Shader::Compile() const
{
	// Компилируем шейдер
	glCompileShader(_shader);

	// Получаем статус скомпилированности шейдера
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
	// Компонуем программу
	glLinkProgram(_program);

	// Запрашиваем статус операции компоновки программы
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
	// Шейдер можно пометить на удаление после компоновки программы
	// (и даже после присоединения его к ней)
	// Он будет удален после того, как будет отсоединен от нее)
	glDeleteShader(_shader);

	// После того, как программа скомпонована, можно отсоединить 
	// от нее шейдер, т.к. он был нужен лишь на этапе ее компоновки
	glDetachShader(_program, _shader);
	// После отсоединения от программы, шейдер будет удален, т.к.
	// мы пометили его на удаление при помощи glDeleteShader

	// удаляем созданную программу
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

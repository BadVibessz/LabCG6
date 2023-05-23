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

	// компонуем шейдер
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

	// Задаем параметры шейдерной программы
	// тип входных примитивов: точки
	glProgramParameteri(_program, GL_GEOMETRY_INPUT_TYPE_ARB, GL_POINTS);
	//_program.SetParameter(GL_GEOMETRY_INPUT_TYPE_ARB, GL_POINTS);
	
	// типв выходных примитивов: лента из треугольникков
	//m_program.SetParameter(GL_GEOMETRY_OUTPUT_TYPE_ARB, GL_TRIANGLE_STRIP);
	glProgramParameteri(_program, GL_GEOMETRY_OUTPUT_TYPE_ARB, GL_TRIANGLE_STRIP);

	// Максимальное количество вершин, порождаемых геометрическим шейдером
	// за один вызов. Для ленты из двух треугольников оно равно 4
	//m_program.SetParameter(GL_GEOMETRY_VERTICES_OUT_EXT, 4);
	glProgramParameteri(_program, GL_GEOMETRY_VERTICES_OUT_EXT, 4);



	// Компонуем программу
	glLinkProgram(_program);

	// Запрашиваем статус операции компоновки программы
	GLint linkStatus;
	glGetProgramiv(_program, GL_LINK_STATUS, &linkStatus);

	if (linkStatus != GL_TRUE)
	{
		int length;
		std::string log;
		glGetProgramiv(_program, GL_INFO_LOG_LENGTH, &length);
		log.reserve(static_cast<unsigned long>(length));
		glGetProgramInfoLog(_program, length, &length, &log[0]);

		std::cout << "cannot Link: " << log << std::endl;

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

#include "Window.h"

void Window::OnResizeFunction(GLFWwindow* window, int width, int height)
{
	const float aspectRatio = (float)width / (float)height;
	float scale = 3;


	//glViewport(0, 0, width, height);
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();

	//// умножает текущую матрицу на матрицу перспективы.
	//glFrustum(-aspectRatio * scale, aspectRatio * scale, -scale, scale, scale, 0);

	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();


	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (width > height)
	{
		if (height == 0) return;
		float ratio = ((float)width / height) * scale;
		gluOrtho2D(-ratio, ratio, -scale, scale);
	}
	else
	{
		if (width == 0) return;
		float ratio = ((float)height / width) * scale;
		gluOrtho2D(-scale, scale, -ratio, ratio);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

Window::Window(int width, int height, const char* title,
	std::function<void()> onDisplayFunction)
{
	if (!glfwInit())
		throw "GLFW not initialized";

	_window = glfwCreateWindow(width, height, title, NULL, NULL);
	this->onDisplayFunction = onDisplayFunction;
	_width = width;
	_height = height;

	if (!_window)
	{
		glfwTerminate();
		throw "Window not created";
	}
	glfwMakeContextCurrent(_window);
	glewInit();

	glfwSetWindowSizeCallback(_window, OnResizeFunction);
}

Window::~Window()
{
	glfwDestroyWindow(_window);
}

void Window::Run() const
{
	if (onDisplayFunction == nullptr) throw "Display function not specified";

	OnResizeFunction(_window, _width, _height);

	while (!glfwWindowShouldClose(_window))
	{
		glClearColor(0.8, 0.8, 0.8, 1);

		onDisplayFunction();

		glfwSwapBuffers(_window);
		glfwWaitEvents();
	}

	glfwTerminate();
}

void Window::UseShader(uint shaderType, const char* sourceCode)
{
	_shader = Shader(shaderType, sourceCode);
}

void Window::UseGeometryShader(const char* vertexSourceCode, const char* geomSourceCode)
{
	// создаем шейдер
	uint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	uint geomShader = glCreateShader(GL_GEOMETRY_SHADER);

	// загружаем исходный код шейдера
	glShaderSource(vertexShader, 1, &vertexSourceCode, NULL);
	glShaderSource(geomShader, 1, &geomSourceCode, NULL);

	// создаем программу
	uint program = glCreateProgram();

	// свзявыаем шейдер с программой
	glAttachShader(program, vertexShader);
	glAttachShader(program, geomShader);

	glCompileShader(vertexShader);
	glCompileShader(geomShader);


	GLint compileStatus;
	glGetShaderiv(geomShader, GL_COMPILE_STATUS, &compileStatus);

	if (compileStatus != GL_TRUE)
	{
		throw std::runtime_error("Cannot compile shader");
	}

	// Задаем параметры шейдерной программы
	// тип входных примитивов: точки
	glProgramParameteri(program, GL_GEOMETRY_INPUT_TYPE_ARB, GL_LINES);
	//_program.SetParameter(GL_GEOMETRY_INPUT_TYPE_ARB, GL_POINTS);

	// типв выходных примитивов: лента из треугольникков
	//m_program.SetParameter(GL_GEOMETRY_OUTPUT_TYPE_ARB, GL_TRIANGLE_STRIP);
	glProgramParameteri(program, GL_GEOMETRY_OUTPUT_TYPE_ARB, GL_LINE_STRIP);

	// Максимальное количество вершин, порождаемых геометрическим шейдером
	// за один вызов. Для ленты из двух треугольников оно равно 4
	//m_program.SetParameter(GL_GEOMETRY_VERTICES_OUT_EXT, 4);
	glProgramParameteri(program, GL_GEOMETRY_VERTICES_OUT_EXT, 5);


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

		std::cout << "cannot Link: " << log << std::endl;

		throw std::runtime_error("Cannot link program");
	}

	glUseProgram(program);
}


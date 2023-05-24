#include "Window.h"

void Window::OnResizeFunction(GLFWwindow* window, int width, int height)
{
	const float aspectRatio = (float)width / (float)height;
	float scale = 3;

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

void Window::UseGeometryShader(const char* vertexSourceCode, const char* geomSourceCode)
{
	// создаем шейдер
	uint vertexShader = Shader::CreateShader(GL_VERTEX_SHADER, vertexSourceCode);
	uint geomShader = Shader::CreateShader(GL_GEOMETRY_SHADER, geomSourceCode);

	// создаем программу
	auto program = GLProgram();

	// свзявыаем шейдер с программой
	program.AttachShader(vertexShader);
	program.AttachShader(geomShader);

	// компилируем шейдеры
	Shader::Compile(vertexShader);
	Shader::Compile(geomShader);

	// компонуем программу
	program.Link();

	// запускаем программу
	program.Start();
}


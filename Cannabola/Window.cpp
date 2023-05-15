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
		glClearColor(1, 1, 1, 1);

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


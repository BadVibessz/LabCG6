#pragma once

#include <string>
#include <functional>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Shader.h"
#include "GLProgram.h"

class Window
{
	
private:
	GLFWwindow* _window;
	static void OnResizeFunction(GLFWwindow* window, int width, int height);
	int _width, _height;

public:
	std::function<void(void)> onDisplayFunction = nullptr;

	Window(int width, int height, const char* title,
		std::function<void()> onDisplayFunction);
	~Window();

	void Run() const;

	void UseGeometryShader(const char* vertexSourceCode, const char* geomSourceCode);

};


#include "Window.h"
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Shader.h"
#include "FileManager.h"

#define PI 3.141592653

void onDisplayFunction()
{
	glBegin(GL_QUADS);
	{
		glTexCoord2f(0, 0);
		glVertex2f(-2, -1);

		glTexCoord2f(0, 1);
		glVertex2f(-2, 1);

		glTexCoord2f(2, 1);
		glVertex2f(2, 1);

		glTexCoord2f(2, 1);
		glVertex2f(2, -1);
	}
	glEnd();
}

int main()
{
	//auto vertexShaderSource = FileManager::ReadFile("Shaders/USSRVertexShader.txt");
	auto fragmentShaderSource = FileManager::ReadFile("Shaders/USSRFragmentShader.txt");

	auto window = Window(800, 800, "USSR", &onDisplayFunction);
	//window.UseShader(GL_VERTEX_SHADER, vertexShaderSource.c_str());
	window.UseShader(GL_FRAGMENT_SHADER, fragmentShaderSource.c_str());

	window.Run();
}


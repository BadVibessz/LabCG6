#include "Window.h"
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Shader.h"
#include "FileManager.h"

#define PI 3.141592653

void onDisplayFunction()
{
	//// todo: maybe change sizes
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


	/*float angle = 90;
	float vertices[20];

	vertices[0] = vec2(0, bigRadius);
	for (int i = 1; i < 10; i++)
	{
		vertices[i] = vec2(
			cos(angle) * bigRadius.x + position.x,
			sin(angle) * bigRadius.x + position.y);

		i++;

		vertices[i] = vec2(
			cos(angle + radians(36)) * smallRadius.x + position.x,
			sin(angle + radians(36)) * smallRadius.x + position.y);

		angle += radians(72);

	}*/
}

int main()
{
	auto vertexShaderSource = FileManager::ReadFile("Shaders/USSRVertexShader.txt");
	auto fragmentShaderSource = FileManager::ReadFile("Shaders/USSRFragmentShader.txt");

	auto window = Window(800, 800, "USSR", &onDisplayFunction);
	window.UseShader(GL_VERTEX_SHADER, vertexShaderSource.c_str());
	window.UseShader(GL_FRAGMENT_SHADER, fragmentShaderSource.c_str());

	window.Run();
}


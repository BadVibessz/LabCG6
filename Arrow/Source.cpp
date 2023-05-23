#include "Window.h"
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Shader.h"
#include "FileManager.h"

#define PI 3.141592653

void onDisplayFunction()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glPushMatrix();

	glLineWidth(2);
	glBegin(GL_LINES);

	glColor3f(0, 0, 0);

	float angle = 0;
	for (int i = 0; i < 8; i++)
	{
		glVertex3f(0, 0, 0);
		glVertex3f(cos(angle * PI / 180), sin(angle * PI / 180), 0);

		angle += 45;
	}

	glEnd();
	glPopMatrix();
}

int main()
{
	auto vertexShaderSource = FileManager::ReadFile("Shaders/ArrowVertexShader.txt");
	auto geomShaderSource = FileManager::ReadFile("Shaders/ArrowGeomShader.txt");

	auto window = Window(800, 800, "Arrow", &onDisplayFunction);
	window.UseGeometryShader(vertexShaderSource.c_str(), geomShaderSource.c_str());

	window.Run();
}

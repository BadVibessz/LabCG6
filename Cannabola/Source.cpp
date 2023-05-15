#include "Window.h"
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Shader.h"
#include "FileManager.h"

#define PI 3.141592653

std::vector<float> vert = std::vector<float>();
Shader shader;

void onDisplayFunction()
{
	glColor3f(0, 1, 0);
	glVertexPointer(2, GL_FLOAT, 0, &vert[0]);
	glEnableClientState(GL_VERTEX_ARRAY);
	glDrawArrays(GL_LINE_STRIP, 0, vert.size() / 2);
	glDisableClientState(GL_VERTEX_ARRAY);
}

int main()
{
	float min = 0;
	float max = 2 * PI;
	float step = PI / 1000;
	int count = (int)round((max - min) / step);

	float x = min;
	for (int i = 0; i < count; i++)
	{
		vert.push_back(x);
		vert.push_back(0);

		x += step;
	}

	auto sourceCode = FileManager::ReadFile("Shaders/CannabolVertexShader.txt");

	auto window = Window(800, 800, "Cannabola", &onDisplayFunction);
	window.UseShader(GL_VERTEX_SHADER, sourceCode.c_str());

	window.Run();
}


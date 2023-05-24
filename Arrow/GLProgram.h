#pragma once

#include  <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <stdexcept>
#include <vector>



using uint = unsigned int;

class GLProgram
{

public:
	uint program;
	std::vector<uint> shaders = std::vector<uint>();


	GLProgram();
	void Link();
	void AttachShader(uint shader);
	void Start();
	void Stop();

	

};


#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>

#include  <GL/glew.h>
#include <GLFW/glfw3.h>


using uint = unsigned int;

static class Shader
{
public:
	static uint CreateShader(uint shaderType, char const* shaderSource);
	static void Compile(uint shader);
};


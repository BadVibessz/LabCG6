#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>

#include  <GL/glew.h>
#include <GLFW/glfw3.h>


using uint = unsigned int;

class Shader
{

private:
	uint _shaderType;
	char const *_shaderSource;

	uint _shader;
	uint _program;

public:

	Shader() = default;
	Shader(uint shaderType, char const *shaderSource);
	void Compile() const;
	void Link() const;
	~Shader();

	void Start() const;
	void Stop() const;
};


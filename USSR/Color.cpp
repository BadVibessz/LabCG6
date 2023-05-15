#include "Color.h"

Color::Color(float r, float g, float b)
{
	R = r;
	G = g;
	B = b;
}

Color::Color(int r, int g, int b) : Color(r / 255.f, g / 255.f, b / 255.f)
{
}

#include "Console.h"
#include <sstream>

namespace
{
	int x;
	int y;
}

void Initialize()
{
	x = 0;
	y = 0;
}

std::string ToStringCoordnate()
{
	std::stringstream ss;
	ss << "X: " << x << " Y: " << y << "\n";
	return ss.str();
}

void AddX(int input)
{
	x += input;
}

void AddY(int input)
{
	y += input;
}
#pragma once

class cmGeometry;

namespace cmHelper::Graphics::Geometry2D
{
	// 2Â÷¿ø
	void CreateColoredSquare(cmGeometry* inOutGeometry, float inSize, const std::array<Color, 4>& inColor);
}
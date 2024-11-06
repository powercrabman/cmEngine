#include "pch.h"
#include "cmGeometryHelper.h"
#include "cmGeometry.h"
#include "cmVertexBuffer.h"
#include "cmIndexBuffer.h"

namespace cmHelper::Graphics::Geometry2D
{
	// 2Â÷¿ø
	void CreateColoredSquare(cmGeometry* inOutGeometry, float inSize, const std::array<Color, 4>& inColor)
	{
		std::vector<cmVertexPosColor> vertices = {
			{ { inSize,  inSize, 0.f }, inColor[0]},
			{ { inSize, -inSize, 0.f }, inColor[1]},
			{ { -inSize, -inSize, 0.f }, inColor[2]},
			{ { -inSize,  inSize, 0.f }, inColor[3]},
		};

		std::vector<UINT> indices = {
			0, 1, 2, 0, 2, 3
		};

		inOutGeometry->Create(vertices, indices);
	}
}


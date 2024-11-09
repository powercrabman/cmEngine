#include "pch.h"
#include "cmGeometryHelper.h"
#include "cmGeometry.h"
#include "cmVertexBuffer.h"
#include "cmIndexBuffer.h"
#include "cmMesh.h"

namespace cmHelper::Graphics::Geometry2D
{
	// 2차원
	void CreateColoredQuad(cmGeometry* inOutGeometry, float inSize, const std::array<Color, 4>& inColor)
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
	void CreateTexQuad(cmGeometry* inOutGeometry, float inSize, const std::array<Vector2, 4>& inTexCoord)
	{
		std::vector<cmVertexPosTex> vertices = {
			{ { inSize,  inSize, 0.f }, inTexCoord[0] },
			{ { inSize, -inSize, 0.f }, inTexCoord[1] },
			{ { -inSize, -inSize, 0.f }, inTexCoord[2] },
			{ { -inSize,  inSize, 0.f }, inTexCoord[3] },
		};

		std::vector<UINT> indices = {
			0, 1, 2, 0, 2, 3
		};

		inOutGeometry->Create(vertices, indices);
	}

	// 2차원
	void CreateColoredQuad(cmMesh* inMesh, float inSize, const std::array<Color, 4>& inColor)
	{
		std::vector<cmVertexPosColor> vertices = {
			{ { inSize,  inSize, 0.f }, inColor[0] },
			{ { inSize, -inSize, 0.f }, inColor[1] },
			{ { -inSize, -inSize, 0.f }, inColor[2] },
			{ { -inSize,  inSize, 0.f }, inColor[3] },
		};

		std::vector<UINT> indices = {
			0, 1, 2, 0, 2, 3
		};

		inMesh->Create(vertices, indices);
	}

	void CreateTexQuad(cmMesh* inMesh, float inSize, const std::array<Vector2, 4>& inTexCoord)
	{
		std::vector<cmVertexPosTex> vertices = {
			{ { inSize,  inSize, 0.f }, inTexCoord[0] },
			{ { inSize, -inSize, 0.f }, inTexCoord[1] },
			{ { -inSize, -inSize, 0.f }, inTexCoord[2] },
			{ { -inSize,  inSize, 0.f }, inTexCoord[3] },
		};

		std::vector<UINT> indices = {
			0, 1, 2, 0, 2, 3
		};

		inMesh->Create(vertices, indices);
	}
}

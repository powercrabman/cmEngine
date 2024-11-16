#include "EnginePch.h"
#include "GeometryRenderer.h"

namespace cmEngine
{
	GeometryRenderer::GeometryRenderer()
	{
		mGeometry = MakeScope<Geometry>();
	}
	GeometryRenderer::~GeometryRenderer(){}

	void GeometryRenderer::SetQuadGeometry(const std::array<Color, 4>& inColor)
	{
		static float size = 0.5f;

		std::vector<VertexPosColor> mVertices =
		{
			VertexPosColor{{ size, size,1.f}, inColor[0]},
			VertexPosColor{{ size,-size,1.f}, inColor[1]},
			VertexPosColor{{-size,-size,1.f}, inColor[2]},
			VertexPosColor{{-size, size,1.f}, inColor[3]},
		};

		std::vector<UINT> mIndices =
		{
			0,1,2,0,2,3
		};

		mGeometry->Create(mVertices, mIndices);
		mPipeData.Geometry = mGeometry.get();
	}

	void GeometryRenderer::SetCircleGeometry(const Color& inColor)
	{
		static float	radius = 0.25f;
		static uint32	count = 10;
		static float	step = 360.f / count;

		std::vector<VertexPosColor> mVertices;
		std::vector<UINT>			mIndices;
		mVertices.reserve(count + 1);
		mIndices.reserve(count * 3);

		// Centor
		mVertices.emplace_back(VertexPosColor{ { 0.f, 0.f, 1.f }, inColor });

		// Vertex
		for (float angle = 0.f; angle < 360.f; angle += step)
		{
			float sin, cos;
			Math::GetSinCosDegree(&sin, &cos, angle);
			mVertices.emplace_back(VertexPosColor{ { radius * cos, radius * sin, 1.f }, inColor });
		}

		// Index
		for (uint32_t idx = 1; idx <= count; ++idx)
		{
			mIndices.push_back(0);
			mIndices.push_back(idx);
			mIndices.push_back(idx % count + 1);
		}

		mGeometry->Create(mVertices, mIndices);
		mPipeData.Geometry = mGeometry.get();
	}

	void GeometryRenderer::SetCube(const std::array<Color, 8>& inColor)
	{
		static float size = 0.5f;

		std::vector<VertexPosColor> mVertices =
		{
			VertexPosColor{ { size, size,size }, inColor[0] },
			VertexPosColor{ { size,-size,size }, inColor[1] },
			VertexPosColor{ { -size,-size,size }, inColor[2] },
			VertexPosColor{ { -size, size,size }, inColor[3] },

			VertexPosColor{ { size, size,-size }, inColor[4] },
			VertexPosColor{ { -size, size,-size }, inColor[5] },
			VertexPosColor{ { -size,-size,-size }, inColor[6] },
			VertexPosColor{ { size,-size,-size }, inColor[7] },
		};

		std::vector<UINT> mIndices =
		{
			// Front face
			0, 1, 2, 0, 2, 3,
			// Back face
			4, 5, 6, 4, 6, 7,
			// Left face
			3, 2, 6, 3, 6, 5,
			// Right face
			0, 4, 7, 0, 7, 1,
			// Top face
			0, 3, 5, 0, 5, 4,
			// Bottom face
			1, 7, 6, 1, 6, 2
		};

		mGeometry->Create(mVertices, mIndices);
		mPipeData.Geometry = mGeometry.get();
	}

}

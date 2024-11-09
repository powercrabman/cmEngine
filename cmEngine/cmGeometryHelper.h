#pragma once

class cmGeometry;
class cmMesh;

namespace cmHelper::Graphics::Geometry2D
{
	// 2차원 (레거시)
	void CreateColoredQuad(cmGeometry* inOutGeometry, float inSize, const std::array<Color, 4>& inColor);
	void CreateTexQuad(cmGeometry* inOutGeometry, float inSize, const std::array<Vector2, 4>& inTexCoord);

	// 2차원
	void CreateColoredQuad(cmMesh* inMesh, float inSize, const std::array<Color, 4>& inColor);
	void CreateTexQuad(cmMesh* inMesh, float inSize, const std::array<Vector2, 4>& inTexCoord);

}
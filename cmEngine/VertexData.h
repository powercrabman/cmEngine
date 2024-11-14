#pragma once

#define VERTEX_INPUT_LAYOUT_BODY(...) \
	inline static constexpr D3D11_INPUT_ELEMENT_DESC	InputElements[] = {__VA_ARGS__}; \
	inline static constexpr size_t						InputElementsSize = ARRAYSIZE(InputElements);

namespace cmEngine
{
	INTERFACE IVertexBase {};

	struct VertexPosColor : IMPLEMENTS IVertexBase
	{
		VertexPosColor() = default;
		VertexPosColor(const Vector3& inVector, const SimpleMath::Color& inColor)
			: Position(inVector), Color(inColor) {}

		Vector3				Position;
		SimpleMath::Color	Color;

		VERTEX_INPUT_LAYOUT_BODY(
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_VERTEX_DATA, 0 }
		)
	};

	struct VertexPosTex : IMPLEMENTS IVertexBase
	{
		VertexPosTex() = default;
		VertexPosTex(const Vector3& inVector, const Vector2& inUV)
			: Position(inVector), UV(inUV) {}

		Vector3				Position;
		Vector2				UV;

		VERTEX_INPUT_LAYOUT_BODY(
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_VERTEX_DATA, 0 }
		)
	};
}

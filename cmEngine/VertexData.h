#pragma once

#define VERTEX_INPUT_LAYOUT_BODY(...) \
	inline static constexpr D3D11_INPUT_ELEMENT_DESC	sInputElements[]   = {__VA_ARGS__}; \
	inline static constexpr size_t						sInputElementsSize = ARRAYSIZE(sInputElements)

namespace cmEngine
{
	struct VertexPosColor
	{
		Vector3				Position;
		SimpleMath::Color	Color;

		VERTEX_INPUT_LAYOUT_BODY(
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_VERTEX_DATA, 0 }
		);
	};

	struct VertexPosTex 
	{
		Vector3				Position;
		Vector2				UV;

		VERTEX_INPUT_LAYOUT_BODY(
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT	, 0, D3D11_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_VERTEX_DATA, 0 }
		);
	};
}

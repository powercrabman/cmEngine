#pragma once

struct cmVertexDataBase
{
};

struct cmVertexPosColor : public cmVertexDataBase
{
public:
	cmVertexPosColor() = default;
	cmVertexPosColor(const Vector3& Position, const SimpleMath::Color& Color)
		: Position(Position), Color(Color) {}

	constexpr inline static D3D11_INPUT_ELEMENT_DESC sInputElems[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	constexpr inline static size_t sInputElemsSize = ARRAYSIZE(sInputElems);

public:
	Vector3 Position = Vector3::Zero;
	SimpleMath::Color Color = cmColors::Black;
};

struct cmVertexPosTex : public cmVertexDataBase
{
public:
	cmVertexPosTex() = default;
	cmVertexPosTex(const Vector3& Position, const Vector2& UV)
		: Position(Position), UV(UV) {}

	constexpr inline static D3D11_INPUT_ELEMENT_DESC sInputElems[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	constexpr inline static size_t sInputElemsSize = ARRAYSIZE(sInputElems);

public:
	Vector3 Position = Vector3::Zero;
	Vector2 UV = Vector2::Zero;
};
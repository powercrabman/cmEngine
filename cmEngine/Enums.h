#pragma once

enum class eLogType
{
	None,

	Info,
	Warning,
	Error,

	Count
};

enum class eCalcLayoutPositionX
{
	Left = 0,
	Middle,
	Right
};


enum class eCalcLayoutPositionY
{
	Top = 0,
	Middle,
	Bottom
};

// legacy code (Not Using)
using eConstantBufferApplyFlags = uint32;
enum eConstantBufferApplyFlags_
{
	CONSTANT_BUFFER_APPLY_NONE = 0,
	CONSTANT_BUFFER_APPLY_VERTEXSHADER = 1 << 0,
	CONSTANT_BUFFER_APPLY_PIXELSHADER = 1 << 1,
};

enum class eComponentType
{
	MeshRenderer = 0,
	Transform,
	Camera,

	Count,

	Script, // Script는 특별한 ID를 사용해야만 함
	Undefined
};

enum class eProjectionMode
{
	Perspective = 0,
	Orthographic = 1,
};

enum class eTextureFormat
{
	BMP = 1,
	JPEG,
	PNG,
	TIFF,
	GIF,
	WMP,
	ICO,
	HEIF
};
static_assert((uint32)WICCodecs::WIC_CODEC_BMP == (uint32)eTextureFormat::BMP);
static_assert((uint32)WICCodecs::WIC_CODEC_HEIF == (uint32)eTextureFormat::HEIF);

enum class eSamplerStateFilter
{
	Point = 0,
	Linear,
	LinearAdv,
	Anisotropic,

	Count = 4
};

enum class eSamplerStateAddress
{
	Wrap = 0,
	Mirror,
	Clamp,
	Border,

	Count = 4
};
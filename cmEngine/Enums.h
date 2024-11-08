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

enum class eConstantBufferType
{
	TransformData,
	CameraData,

	Count
};

enum class eProjectionMode
{
	Perspective = 0,
	Orthographic = 1,
};
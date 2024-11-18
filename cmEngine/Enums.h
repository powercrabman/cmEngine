#pragma once

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


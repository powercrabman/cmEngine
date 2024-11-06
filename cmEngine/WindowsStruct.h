#pragma once

struct ScreenSize
{
	ScreenSize() = default;
	ScreenSize(uint32 inWidth, uint32 inHeight)
		: Width(inWidth)
		, Height(inHeight)
	{
	}

	ScreenSize(RECT inRect)
		: Width(inRect.right - inRect.left)
		, Height(inRect.bottom - inRect.top)
	{
	}

	ScreenSize operator*(float scalar) const
	{
		return ScreenSize{
			static_cast<uint32>(Width * scalar),
			static_cast<uint32>(Height * scalar)
		};
	}
	
	ScreenSize operator-(const ScreenSize& other) const
	{
		return ScreenSize{
			Width - other.Width,
			Height - other.Height
		};
	}


	uint32 Width = {};
	uint32 Height = {};
};

struct ScreenPos
{
	ScreenPos() = default;
	ScreenPos(uint32 inX, uint32 inY)
		: X(inX)
		, Y(inY)
	{
	}
	ScreenPos(const ScreenSize& inSize)
		: X(inSize.Width)
		, Y(inSize.Height)
	{
	}

	uint32 X = {};
	uint32 Y = {};
};
#pragma once

class cmWindow;

struct cmViewport final
{
public:
	cmViewport() = default;
	~cmViewport() = default;

	cmViewport(RECT inRect)
		: X((float)inRect.left)
		, Y((float)inRect.top)
		, Width((float)inRect.right)
		, Height((float)inRect.bottom)
		, MinDepth(0.f)
		, MaxDepth(1.f)
	{
	}

	cmViewport(const D3D11_VIEWPORT& inViewport)
		: X(inViewport.TopLeftX)
		, Y(inViewport.TopLeftY)
		, Width(inViewport.Width)
		, Height(inViewport.Height)
		, MinDepth(inViewport.MinDepth)
		, MaxDepth(inViewport.MaxDepth)
	{
	}

	cmViewport(float inTopX, float inTopY, float inWidth, float inHeight, float inMinDepth, float inMaxDepth)
		: X(inTopX)
		, Y(inTopY)
		, Width(inWidth)
		, Height(inHeight)
		, MinDepth(inMinDepth)
		, MaxDepth(inMaxDepth)
	{
	}

	cmViewport(cmWindow* inWindow);
	cmViewport(const ScreenSize& inScreenSize)
		: X(0.f)
		, Y(0.f)
		, Width(inScreenSize.Width)
		, Height(inScreenSize.Height)
		, MinDepth(0.f)
		, MaxDepth(1.f)
	{
	}

	void SetFrom(const ScreenSize& inScreenSize)
	{
		X        = 0.f;
		Y        = 0.f;
		Width    = inScreenSize.Width;
		Height   = inScreenSize.Height;
		MinDepth = 0.f;
		MaxDepth = 1.f;
	}

	void SetFrom(cmWindow* inWindow);

	float AspectRatio() const
	{
		if (Height == 0) { return 0.f; }
		return Width / Height;
	}

	const D3D11_VIEWPORT* GetViewport() const
	{
		return reinterpret_cast<const D3D11_VIEWPORT*>(this);
	}

public:
	float X        = 0.f;
	float Y        = 0.f;
	float Width    = 0.f;
	float Height   = 0.f;
	float MinDepth = 0.f;
	float MaxDepth = 1.f;
};
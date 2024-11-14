#pragma once

namespace cmEngine
{
	struct Viewport
	{
	public:
		Viewport() = default;
		~Viewport() = default;

		Viewport(RECT inRect);
		Viewport(const D3D11_VIEWPORT& inViewport);
		Viewport(float inTopX, float inTopY, float inWidth, float inHeight, float inMinDepth, float inMaxDepth);
		Viewport(const WindowResolution& inScreenSize);

		void SetFrom(const WindowResolution& inScreenSize);

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
		float X = 0.f;
		float Y = 0.f;
		float Width = 0.f;
		float Height = 0.f;
		float MinDepth = 0.f;
		float MaxDepth = 1.f;
	};

	//===================================================
	//                      Inline
	//===================================================


	inline cmEngine::Viewport::Viewport(RECT inRect)
		: X((float)inRect.left)
		, Y((float)inRect.top)
		, Width((float)inRect.right)
		, Height((float)inRect.bottom)
		, MinDepth(0.f)
		, MaxDepth(1.f)
	{
	}

	inline cmEngine::Viewport::Viewport(const D3D11_VIEWPORT& inViewport)
		: X(inViewport.TopLeftX)
		, Y(inViewport.TopLeftY)
		, Width(inViewport.Width)
		, Height(inViewport.Height)
		, MinDepth(inViewport.MinDepth)
		, MaxDepth(inViewport.MaxDepth)
	{
	}

	inline cmEngine::Viewport::Viewport(float inTopX, float inTopY, float inWidth, float inHeight, float inMinDepth, float inMaxDepth)
		: X(inTopX)
		, Y(inTopY)
		, Width(inWidth)
		, Height(inHeight)
		, MinDepth(inMinDepth)
		, MaxDepth(inMaxDepth)
	{
	}

	inline cmEngine::Viewport::Viewport(const WindowResolution& inScreenSize)
		: X(0.f)
		, Y(0.f)
		, Width(inScreenSize.Width)
		, Height(inScreenSize.Height)
		, MinDepth(0.f)
		, MaxDepth(1.f)
	{
	}

	inline void cmEngine::Viewport::SetFrom(const WindowResolution& inScreenSize)
	{
		X = 0.f;
		Y = 0.f;
		Width = inScreenSize.Width;
		Height = inScreenSize.Height;
		MinDepth = 0.f;
		MaxDepth = 1.f;
	}

};
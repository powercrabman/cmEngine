#pragma once

namespace cmEngine
{
	struct WindowResolution
	{
		uint32 Width;
		uint32 Height;
	};

	struct WindowRect
	{
		WindowRect() = default;
		WindowRect(const RECT& inRect)
			: Width(inRect.right - inRect.left)
			, Height(inRect.bottom - inRect.top)
		{}

		uint32 Width;
		uint32 Height;
	};

	// In Monitor Coordination
	struct WindowPosition
	{
		uint32 X;
		uint32 Y;
	};

	// In Window Coordination
	struct ScreenPosition
	{
		uint32 X;
		uint32 Y;
	};

	class GameWindow
	{
		friend class EngineCore;
	public:
		static void ActiveWindow();
		static void ResizeWindow(const WindowResolution& inRes);
		static void RepositionWindow(const WindowPosition& inPos);
		static void SetWindowTitle(std::wstring_view inTitle);

		static WindowResolution GetWindowResolution() { return mWinProp.Resolution; }
		static HWND				GetHwnd() { return mWinProp.Hwnd; }

		static void SetFocus(bool inFocus) { mFocus = inFocus; };
		static bool GetFocus() { return mFocus; }

	private:
		static bool Initialize(
			const WindowResolution& inResoltuion = { 800, 600 },
			const WindowPosition& inPosition = { 0, 0 }
		);

		constexpr inline static wchar_t sClassName[] = L"cmEngine Window";
		constexpr inline static wchar_t sTitleName[] = L"cmEngine";

		struct WindowProp
		{
			HINSTANCE			HInstance = NULL;
			HWND				Hwnd = NULL;

			WindowResolution	Resolution = {};
			WindowRect			WndRect = {};
			WindowPosition		Position = {};
		};

		inline static WindowProp	mWinProp = {};
		inline static bool			mFocus = false;
	};

	//===================================================
	//                      Inline
	//===================================================

	inline void cmEngine::GameWindow::RepositionWindow(const WindowPosition& inPos)
	{
		mWinProp.Position = inPos;
		ActiveWindow();
	}

	inline void GameWindow::SetWindowTitle(std::wstring_view inTitle)
	{
		::SetWindowText(mWinProp.Hwnd, inTitle.data());
	}
}

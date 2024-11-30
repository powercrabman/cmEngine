#pragma once

namespace cmEngine
{
	struct WindowRect
	{
		WindowRect() = default;
		WindowRect(const RECT& inRect)
			: Width(inRect.right - inRect.left)
			, Height(inRect.bottom - inRect.top)
		{
		}

		uint32 Width;
		uint32 Height;
	};

	struct WindowResolution
	{
		uint32 Width;
		uint32 Height;
	};

	// In Monitor Coordination
	struct WindowPosition
	{
		uint32 X;
		uint32 Y;
	};

	// GameWindow Config
	struct GameWindowConfig
	{
		// WindowPosition
		uint32 windowPositionX;
		uint32 windowPositionY;

		// WindowResolution
		uint32 windowResolutionWidth;
		uint32 windowResolutionHeight;

		JSON_STRUCT_BODY(
			GameWindowConfig,
			windowPositionX,
			windowPositionY,
			windowResolutionWidth,
			windowResolutionHeight
		);
	};

	class GameWindow
	{
		SINGLETON(GameWindow);
	public:
		void				ShowWindow();
		void				ResizeWindow(const WindowResolution& inRes);
		void				MoveWindow(const WindowPosition& inPos);
		void				SetWindowTitle(std::wstring_view inTitle);

		WindowResolution	GetWindowResolution() const { return mWinProp.Resolution; }
		float				GetAspectRatio() const { return mWinProp.Resolution.Width / static_cast<float>(mWinProp.Resolution.Height); }
		HWND				GetWindowHandle() const { return mWinProp.Hwnd; }

		bool				GetFocus() const { return mFocus; }

		constexpr inline static wchar_t	sClassName[] = L"cmEngine Window";
		constexpr inline static wchar_t	sConfigName[] = L"EngineConfig.json";

	private:
		GameWindow();
		~GameWindow();

		void				Init(const WindowResolution& inResolution, const WindowPosition& inPosition, std::wstring_view inTitleName);

	private:
		struct WindowProp
		{
			HINSTANCE			HInstance  = NULL;
			HWND				Hwnd       = NULL;

			WindowResolution	Resolution = {};
			WindowPosition		Position   = {};
			WindowRect			WndRect    = {};
		};

		WindowProp		mWinProp    = {};
		bool			mFocus      = false;
		uint32			mWindowFlag = WS_OVERLAPPEDWINDOW;
	};

	//===================================================
	//                      Inline
	//===================================================

	inline void GameWindow::MoveWindow(const WindowPosition& inPos)
	{
		mWinProp.Position = inPos;
		ShowWindow();
	}

	inline void GameWindow::SetWindowTitle(std::wstring_view inTitle)
	{
		::SetWindowText(mWinProp.Hwnd, inTitle.data());
	}
}

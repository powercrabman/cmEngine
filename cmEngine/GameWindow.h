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

	// GameWindow Config
	struct GameWindowConfig : public JsonMetaData
	{
		// WindowPosition
		uint32 windowPositionX;
		uint32 windowPositionY;

		// WindowResoltion
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
			const WindowResolution& inResoltuion,
			const WindowPosition& inPosition
		);

		static void Destroy();

		constexpr inline static wchar_t			sClassName[] = L"cmEngine Window";
		constexpr inline static wchar_t			sTitleName[] = L"cmEngine";
		constexpr inline static const wchar_t	sConfigPath[] = L"EngineConfig.json";

		struct WindowProp
		{
			HINSTANCE			HInstance = NULL;
			HWND				Hwnd = NULL;

			WindowResolution	Resolution = {};
			WindowPosition		Position = {};
			WindowRect			WndRect = {};
		};

		inline static WindowProp	mWinProp = {};
		inline static bool			mFocus = false;
	};

	//===================================================
	//                      Inline
	//===================================================

	inline void GameWindow::RepositionWindow(const WindowPosition& inPos)
	{
		mWinProp.Position = inPos;
		ActiveWindow();
	}

	inline void GameWindow::SetWindowTitle(std::wstring_view inTitle)
	{
		::SetWindowText(mWinProp.Hwnd, inTitle.data());
	}
}

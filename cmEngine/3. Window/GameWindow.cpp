#include "0. cmEngine/cmEngine.h"
#include "GameWindow.h"
#include "WindowProc.h"
#include <fstream>


namespace cmEngine
{
	void GameWindow::ResizeWindow(const WindowResolution& inRes)
	{
		mWinProp.Resolution = inRes;

		// Calc Window Rect
		RECT rect = {};
		FILL_ZERO(rect, RECT);
		rect.right = mWinProp.Resolution.Width;
		rect.bottom = mWinProp.Resolution.Height;

		::AdjustWindowRect(
			&rect,
			mWindowFlag,
			false
		);

		mWinProp.WndRect.Width = rect.right - rect.left;
		mWinProp.WndRect.Height = rect.bottom - rect.top;
		ShowWindow();
	}

	GameWindow::GameWindow()
	{
	}

	GameWindow::~GameWindow()
	{
		GameWindowConfig cf = {};
		cf.windowPositionX = mWinProp.Position.X;
		cf.windowPositionY = mWinProp.Position.Y;
		cf.windowResolutionHeight = mWinProp.Resolution.Height;
		cf.windowResolutionWidth = mWinProp.Resolution.Width;
		JsonSerializer::Ref().SerializeToFileWithTag(cf, sConfigName, "GameWindowConfig");
	}

	void GameWindow::Init(const WindowResolution& inResolution, const WindowPosition& inPosition, std::wstring_view inTitleName)
	{
		// 윈도우 클래스 등록
		{
			WNDCLASS wc = {};
			wc.lpfnWndProc = WindowProc;
			wc.hInstance = mWinProp.HInstance;
			wc.lpszClassName = sClassName;

			ATOM hr = RegisterClass(&wc);

			if (hr == FALSE)
			{
				ENGINE_LOG_FATAL("Window class register fail.");
				ASSERT(false);
				return;
			}
		}

		// 윈도우 생성
		{
			mWinProp.Hwnd = CreateWindowEx(
				0,
				sClassName,
				inTitleName.data(),
				mWindowFlag,
				CW_USEDEFAULT, CW_USEDEFAULT,
				CW_USEDEFAULT, CW_USEDEFAULT,
				NULL,
				NULL,
				mWinProp.HInstance,
				NULL
			);

			if (mWinProp.Hwnd == NULL)
			{
				ENGINE_LOG_FATAL("Window create fail.");
				ASSERT(false);
				return;
			}
		}

		ENGINE_LOG_INFO("Window create success.");

		// Attach Event
		{
			EventDispatcher::Ref().AttachEventHandler<AppShutdownEvent>([](const AppShutdownEvent& e) { Destroy(); });
			EventDispatcher::Ref().AttachEventHandler<WindowOnFocusEvent>([&](const WindowOnFocusEvent& e) {mFocus = true; });
			EventDispatcher::Ref().AttachEventHandler<WindowOffFocusEvent>([&](const WindowOffFocusEvent& e) {mFocus = false; });
			EventDispatcher::Ref().AttachEventHandler<WindowResizeEvent>([&](const WindowResizeEvent& e) {ResizeWindow({ .Width = e.windowWidth, .Height = e.windowHeight }); });
			EventDispatcher::Ref().AttachEventHandler<WindowMoveEvent>([&](const WindowMoveEvent& e) {MoveWindow({ .X = e.windowX, .Y = e.windowY }); });
		}

		// Window Config DeserializeFromFile
		GameWindowConfig cf = {};
		if (JsonSerializer::Ref().DeserializerFromFileWithTag<GameWindowConfig>(cf, sConfigName, "GameWindowConfig"))
		{
			ResizeWindow(WindowResolution{
				.Width = cf.windowResolutionWidth,
				.Height = cf.windowResolutionHeight,
				});

			MoveWindow(WindowPosition{
				.X = cf.windowPositionX,
				.Y = cf.windowPositionY
				});
		}
		else
		{
			ResizeWindow(inResolution);
			MoveWindow(inPosition);
		}
	}

	void GameWindow::ShowWindow()
	{
		::SetWindowPos(
			mWinProp.Hwnd,
			NULL,
			mWinProp.Position.X,
			mWinProp.Position.Y,
			mWinProp.WndRect.Width,
			mWinProp.WndRect.Height,
			SWP_SHOWWINDOW
		);
	}
}

#include "EnginePch.h"
#include "GameWindow.h"
#include "WindowProc.h"
#include <fstream>

namespace cmEngine
{
	bool GameWindow::Initialize(const WindowResolution& inResoltuion, const WindowPosition& inPosition)
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
				return false;
			}
		}

		// 윈도우 생성
		{
			mWinProp.Hwnd = CreateWindowEx(
				0,
				sClassName,
				sTitleName,
				WS_OVERLAPPEDWINDOW,
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
				return false;
			}
		}

		ENGINE_LOG_INFO("Window create success.");

		// 윈도우 세팅 가져오기
		WindowConfig config = {};
		if (ConfigSystem::Load(config))
		{
			// 윈도우 띄우기
			ResizeWindow(config.Resolution);
			RepositionWindow(config.Position);
		}
		else
		{
			ResizeWindow(inResoltuion);
			RepositionWindow(inPosition);
		}

		return true;
	}

	void GameWindow::Destory()
	{
		WindowConfig wc = {};
		wc.Position = mWinProp.Position;
		wc.Resolution = mWinProp.Resolution;
		ConfigSystem::Save(wc);
	}

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
			WS_OVERLAPPEDWINDOW,
			false
		);

		mWinProp.WndRect.Width = rect.right - rect.left;
		mWinProp.WndRect.Height = rect.bottom - rect.top;
		ActiveWindow();
	}

	void GameWindow::ActiveWindow()
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
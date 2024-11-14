#include "EnginePch.h"
#include "GameWindow.h"
#include "WindowProc.h"

bool cmEngine::GameWindow::Initialize(const WindowResolution& inResoltuion, const WindowPosition& inPosition)
{
	// ������ Ŭ���� ���
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

	// ������ ����
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

		if (mWinProp.Hwnd = NULL)
		{
			ENGINE_LOG_FATAL("Window create fail.");
			ASSERT(false);
			return false;
		}
	}

	ENGINE_LOG_INFO("Window create success.");

	// ������ ����
	ResizeWindow(inResoltuion);
	RepositionWindow(inPosition);

	return true;
}

void cmEngine::GameWindow::ResizeWindow(const WindowResolution& inRes)
{
	mWinProp.Resolution = inRes;

	// Calc Window Rect
	RECT rect = {};
	FILL_ZERO(rect, RECT);
	rect.right = inRes.Width;
	rect.bottom = inRes.Height;

	::AdjustWindowRect(
		&rect,
		WS_OVERLAPPEDWINDOW,
		false
	);

	mWinProp.WndRect = WindowRect{ rect };
	ActiveWindow();
}


void cmEngine::GameWindow::ActiveWindow()
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

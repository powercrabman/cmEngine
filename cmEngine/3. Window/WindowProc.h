#pragma once

IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

inline LRESULT WindowProc(HWND hwnd, uint32 uMsg, WPARAM wParam, LPARAM lParam)
{
	using namespace cmEngine;

	if (ImGui_ImplWin32_WndProcHandler(hwnd, uMsg, wParam, lParam))
	{
		return 1;
	}

	// if Engine is not running, use default proc
	if (!EngineCore::Ref().IsRunning())
	{
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	switch (uMsg)
	{
	case WM_DESTROY:
	{
		EventDispatcher::Ref().EventDispatch(AppShutdownEvent{});
		PostQuitMessage(0);
		return 0;
	}

	case WM_SIZE:
	{
		ENGINE_LOG_DEBUG("Main Window Resizing");

		if (wParam == SIZE_MINIMIZED)
		{
			ENGINE_LOG_DEBUG("Window minimized");
			return 0;
		}

		// Resize
		WindowResizeEvent e = {};
		e.windowWidth = max(100, (UINT)LOWORD(lParam));
		e.windowHeight = max(100, (UINT)HIWORD(lParam));

		// Reposition
		{
			RECT rect = {};
			::GetWindowRect(GameWindow::Ref().GetWindowHandle(), &rect);
			WindowMoveEvent e = {};
			e.windowX = rect.left;
			e.windowY = rect.top;
			EventDispatcher::Ref().EventDispatch(e);
		}

		EventDispatcher::Ref().EventDispatch(e);

		return 0;
	}

	case WM_EXITSIZEMOVE:
	{
		ENGINE_LOG_DEBUG("Main Window Repositioning");

		// Reposition
		RECT rect = {};
		::GetWindowRect(GameWindow::Ref().GetWindowHandle(), &rect);
		WindowMoveEvent e = {};
		e.windowX = rect.left;
		e.windowY = rect.top;
		EventDispatcher::Ref().EventDispatch(e);

		return 0;
	}

	case WM_SETFOCUS:
	{
		EventDispatcher::Ref().EventDispatch(WindowOnFocusEvent{});
		return 0;
	}

	case WM_KILLFOCUS:
	{
		EventDispatcher::Ref().EventDispatch(WindowOnFocusEvent{});
		return 0;
	}

	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}
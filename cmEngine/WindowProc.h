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
	if (!EngineCore::Get()->IsRunning())
	{
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	switch (uMsg)
	{

	case WM_DESTROY:
	{
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
		WindowResolution res = {
			max(100, (UINT)LOWORD(lParam)), 
			max(100, (UINT)HIWORD(lParam)) 
		};

		// Reposition
		RECT rect = {};
		::GetWindowRect(GameWindow::GetHwnd(), &rect);

		WindowPosition pos = { rect.left, rect.top};

		GameWindow::RepositionWindow(pos);
		GameWindow::ResizeWindow(res);
		Renderer::OnResize(res);

		return 0;
	}

	case WM_EXITSIZEMOVE:
	{
		ENGINE_LOG_DEBUG("Main Window Repositioning");

		RECT rect = {};
		::GetWindowRect(GameWindow::GetHwnd(), &rect);

		WindowPosition pos = { rect.left, rect.top };

		GameWindow::RepositionWindow(pos);

		return 0;
	}

	case WM_SETFOCUS:
	{
		GameWindow::SetFocus(true);
		ENGINE_LOG_DEBUG("Main Window Activate");
		return 0;
	}

	case WM_KILLFOCUS:
	{
		GameWindow::SetFocus(false);
		ENGINE_LOG_DEBUG("Main Window No Activate");

		return 0;
	}

	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}
#pragma once

IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

inline LRESULT WindowProc(HWND hwnd, uint32 uMsg, WPARAM wParam, LPARAM lParam)
{
	using namespace cmEngine;

	if (ImGui_ImplWin32_WndProcHandler(hwnd, uMsg, wParam, lParam))
	{
		return true;
	}

	/* Common Proc */
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
		if (wParam == SIZE_MINIMIZED)
			return 0;

		WindowResolution res = {};

		res.Width = (UINT)LOWORD(lParam);
		res.Height = (UINT)HIWORD(lParam);

		GameWindow::ResizeWindow(res);
		Renderer::OnResize(res);

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
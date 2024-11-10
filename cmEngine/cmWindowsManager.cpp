#include "pch.h"
#include "cmWindowsManager.h"
#include "cmWindow.h"
#include "cmRenderer.h"
#include "DirectXTK\Keyboard.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CoreProc(HWND hwnd, uint32 uMsg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hwnd, uMsg, wParam, lParam))
		return true;

	/* Common Proc */
	if (!Engine->IsInitialized())
		return DefWindowProc(hwnd, uMsg, wParam, lParam);

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

		ScreenSize size = {};

		size.Width = (UINT)LOWORD(lParam);
		size.Height = (UINT)HIWORD(lParam);

		Engine->GetWindowsManager()->GetMainWindow()->OnResize(size);
		Engine->GetRenderer()->OnResize(size);
		return 0;
	}

	case WM_SETFOCUS:
	{
		Engine->GetWindowsManager()->GetMainWindow()->SetFocus(true);
		LOG_DEBUG("Main Window Activate");
		return 0;
	}

	case WM_KILLFOCUS:
	{
		Engine->GetWindowsManager()->GetMainWindow()->SetFocus(false);
		LOG_DEBUG("Main Window No Activate");

		// 키보드 리셋
		Engine->GetKeyboard()->Reset();

		return 0;
	}

#ifndef CM_ENGINE_USE_KEYBOARD_POLL

	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
		Engine->GetKeyboard()->OnKeyDown(uMsg, wParam, lParam);
		break;

	case WM_KEYUP:
	case WM_SYSKEYUP:
		Engine->GetKeyboard()->OnKeyUp(uMsg, wParam, lParam);
		break;

#endif // !CM_ENGINE_USE_KEYBOARD_POLL

	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	return cmWindowsManager::sWinProc(hwnd, uMsg, wParam, lParam);
}

cmWindowsManager::cmWindowsManager() = default;
cmWindowsManager::~cmWindowsManager() = default;

cmWindow* cmWindowsManager::CreateNamedWindow(std::wstring_view inWindowName, const ScreenSize& inScreenSize)
{
	mMainWindow.reset();
	mMainWindow = std::unique_ptr<cmWindow>{ new cmWindow(this, inWindowName, inScreenSize) };
	return mMainWindow.get();
}

void cmWindowsManager::RegisterWindowApplication() const
{
	WNDCLASS wc = {};
	wc.lpfnWndProc = CoreProc;
	wc.hInstance = mHinst;
	wc.lpszClassName = sClassName;

	ASSERT(RegisterClass(&wc), "Window class register fail.");
	LOG_INFO("Create Main Window.");
}

LRESULT cmWindowsManager::CommonProc(HWND hwnd, uint32 uMsg, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

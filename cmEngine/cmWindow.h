#pragma once

// 윈도우 창을 관리
// 1. 윈도우 핸들
// 2. 윈도우 사이즈

class cmWindowsManager;

class cmWindow
{
	friend class cmWindowsManager;
public:
	virtual ~cmWindow();

	//윈도우 띄우기
	void Activate(const ScreenPos& inScreenPos);
	void Activate() const;

	//윈도우 사이즈 변경
	void OnResize(const ScreenSize& inScreenSize);

	HWND GetHwnd() const { return mHwnd; }
	ScreenSize GetScreenSize() const { return mScreen; }

	bool IsFocused() const { return mFocus; }
	void SetFocus(bool isFocus) { mFocus = isFocus; }

private:
	cmWindow(const cmWindowsManager* inWinMgr, std::wstring_view inWindowName, const ScreenSize& inScreenSize);

private:
	std::wstring mName = {};
	ScreenSize mScreen = {};
	ScreenPos mPosition = {};
	RECT windowRect = {};
	HWND mHwnd = NULL;
	bool mFocus = true;
};


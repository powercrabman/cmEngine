#pragma once

// ������ â�� ����
// 1. ������ �ڵ�
// 2. ������ ������

class cmWindowsManager;

class cmWindow
{
	friend class cmWindowsManager;
public:
	virtual ~cmWindow();

	//������ ����
	void Activate(const ScreenPos& inScreenPos);
	void Activate() const;

	//������ ������ ����
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


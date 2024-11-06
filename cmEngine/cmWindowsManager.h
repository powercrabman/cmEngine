#pragma once
//윈도우 어플리케이션 전반을 초기화 및 관리
//1. 윈도우 초기화
//2. 윈도우 관리
//3. 윈도우 생성

class cmWindow;

//윈도우즈 프록시저
LRESULT CALLBACK CoreProc(HWND hwnd, uint32 uMsg, WPARAM wParam, LPARAM lParam);

class cmWindowsManager
{
	ENGINE_MODULE_BODY();
	using WinProcFn = std::function<LRESULT CALLBACK(HWND, uint32, WPARAM, LPARAM)>;
public:
	~cmWindowsManager();

	// 윈도우 생성
	cmWindow* CreateNamedWindow(std::wstring_view inWindowName, const ScreenSize& inScreenSize);

	HINSTANCE GetWindowsInstance() const;
	cmWindow* GetMainWindow() const;

	void SetCustomWindowProc(const WinProcFn& inProc);

private:
	cmWindowsManager();

	void Initialize();

	void RegisterWindowApplication() const;

	//기본 윈도우 프록시저
	static LRESULT CALLBACK CommonProc(HWND hwnd, uint32 uMsg, WPARAM wParam, LPARAM lParam);

public:
	const inline static wchar_t sClassName[] = L"cmEngine";

	inline static WinProcFn sWinProc = &cmWindowsManager::CommonProc;

private:
	HINSTANCE mHinst = NULL;

	std::unique_ptr<cmWindow> mMainWindow = nullptr;
};

inline HINSTANCE cmWindowsManager::GetWindowsInstance() const
{
	return mHinst;
}

inline cmWindow* cmWindowsManager::GetMainWindow() const
{
	ASSERT(mMainWindow, "메인 윈도우가 존재하지 않습니다.");
	return mMainWindow.get();
}

inline void cmWindowsManager::SetCustomWindowProc(const WinProcFn& inProc)
{
	sWinProc = inProc;
}

inline void cmWindowsManager::Initialize()
{
	RegisterWindowApplication();
}
#pragma once
//������ ���ø����̼� ������ �ʱ�ȭ �� ����
//1. ������ �ʱ�ȭ
//2. ������ ����
//3. ������ ����

class cmWindow;

//�������� ���Ͻ���
LRESULT CALLBACK CoreProc(HWND hwnd, uint32 uMsg, WPARAM wParam, LPARAM lParam);

class cmWindowsManager
{
	ENGINE_MODULE_BODY();
	using WinProcFn = std::function<LRESULT CALLBACK(HWND, uint32, WPARAM, LPARAM)>;
public:
	~cmWindowsManager();

	// ������ ����
	cmWindow* CreateNamedWindow(std::wstring_view inWindowName, const ScreenSize& inScreenSize);

	HINSTANCE GetWindowsInstance() const;
	cmWindow* GetMainWindow() const;

	void SetCustomWindowProc(const WinProcFn& inProc);

private:
	cmWindowsManager();

	void Initialize();

	void RegisterWindowApplication() const;

	//�⺻ ������ ���Ͻ���
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
	ASSERT(mMainWindow, "���� �����찡 �������� �ʽ��ϴ�.");
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
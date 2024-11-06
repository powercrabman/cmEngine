#include "pch.h"
#include "cmWindow.h"
#include "cmWindowsManager.h"

cmWindow::~cmWindow() = default;

void cmWindow::Activate(const ScreenPos& inScreenPos) 
{
    mPosition = inScreenPos;
    Activate();
}

void cmWindow::Activate() const
{
    uint32 w = windowRect.right - windowRect.left;
    uint32 h = windowRect.bottom - windowRect.top;

    ::SetWindowPos(
        mHwnd,
        NULL,
        mPosition.X,
        mPosition.Y,
        w,
        h,
        SWP_SHOWWINDOW
    );
}

//윈도우 사이즈 변경
void cmWindow::OnResize(const ScreenSize& inScreenSize)
{
    RECT rect = {};
    ZeroMemory(&rect, sizeof(rect));
    rect.right = inScreenSize.Width;
    rect.bottom = inScreenSize.Height;

    ::AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);
    windowRect = rect;
    mScreen = inScreenSize;
}

cmWindow::cmWindow(const cmWindowsManager* inWinMgr, std::wstring_view inWindowName, const ScreenSize& inScreenSize)
    : mName(inWindowName)
    , mScreen(inScreenSize)
{
    mHwnd = CreateWindowEx(
        0,
        cmWindowsManager::sClassName,
        inWindowName.data(),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        CW_USEDEFAULT, CW_USEDEFAULT,
        NULL,
        NULL,
        inWinMgr->GetWindowsInstance(),
        NULL
    );

    ASSERT(mHwnd != NULL, "Create Window Fail.");

    OnResize(inScreenSize);
}


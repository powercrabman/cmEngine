#include "pch.h"
#include "cmApplication.h"
#include "EngineModules.h"
#include "cmWindow.h"
#include "cmTimer.h"
#include "cmSceneManager.h"

void cmApplication::Setup(const ScreenSize& inScreenSize, const ScreenPos& inScreenPos)
{
    // 메모리 디버깅 설정
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
    _CrtSetBreakAlloc(0);

    // 엔진 생성 및 초기화
    Engine = Engine->GetOrCreate();
    Engine->Initialize();

    // 메인 윈도우 생성
    cmWindow* win = Engine->GetWindowsManager()->CreateNamedWindow(L"Main Game", inScreenSize);
    win->Activate(inScreenPos);

    // 엔진 초기화 2
    Engine->FinalInitialize();

    // 실행 단위 초기화
    Initialize();
}

void cmApplication::UpdateCore()
{
    //==================================
    //PreUpdate : 시스템 업데이트
    //Update : 오브젝트 좌표 수정과 같은 게임 메인 로직
    //FixUpdate : Update의 결과를 수정
    //Render : 최종적인 오브젝트 상태를 렌더링
    //==================================

    //PreUpdate
    {
        //타이머
        Engine->GetTimer()->Update();

        //Input
        Engine->GetKeyboard()->Update();
    }

    //Update
    {
        //Scene Update
        Engine->GetSceneManager()->UpdateCore();
    }
    
    //Render
    {
        Engine->GetRenderer()->RenderBegin();
        Engine->GetRenderer()->Render();
        Engine->GetRenderer()->RenderEnd();
    }
}

void cmApplication::CleanUpCore()
{
    // Engine Module Clean up
    Engine->GetRenderer()->CleanUp();

    // 어플리케이션 Clean up
    CleanUp();

    // 엔진 삭제
    Engine->Destory();

    // 메모리 릭 검사 후 어플리케이션 종료
    _CrtDumpMemoryLeaks();
}

void cmApplication::Run()
{
    //메인루프
    MSG msg = { };
    while (true)
    {
        if (::PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);

            if (msg.message == WM_QUIT)
            {
                break;
            }
        }
        else
        {
            if (Engine->IsRunning() == false)
            {
                break;
            }
            
            UpdateCore();
        }

    }

    //정리
    CleanUpCore();
}
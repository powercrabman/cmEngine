#include "pch.h"
#include "cmApplication.h"
#include "EngineModules.h"
#include "cmWindow.h"
#include "cmTimer.h"
#include "cmSceneManager.h"

void cmApplication::Setup(const ScreenSize& inScreenSize, const ScreenPos& inScreenPos)
{
    // �޸� ����� ����
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
    _CrtSetBreakAlloc(0);

    // ���� ���� �� �ʱ�ȭ
    Engine = Engine->GetOrCreate();
    Engine->Initialize();

    // ���� ������ ����
    cmWindow* win = Engine->GetWindowsManager()->CreateNamedWindow(L"Main Game", inScreenSize);
    win->Activate(inScreenPos);

    // ���� �ʱ�ȭ 2
    Engine->FinalInitialize();

    // ���� ���� �ʱ�ȭ
    Initialize();
}

void cmApplication::UpdateCore()
{
    //==================================
    //PreUpdate : �ý��� ������Ʈ
    //Update : ������Ʈ ��ǥ ������ ���� ���� ���� ����
    //FixUpdate : Update�� ����� ����
    //Render : �������� ������Ʈ ���¸� ������
    //==================================

    //PreUpdate
    {
        //Ÿ�̸�
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

    // ���ø����̼� Clean up
    CleanUp();

    // ���� ����
    Engine->Destory();

    // �޸� �� �˻� �� ���ø����̼� ����
    _CrtDumpMemoryLeaks();
}

void cmApplication::Run()
{
    //���η���
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

    //����
    CleanUpCore();
}
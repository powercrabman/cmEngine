#include "EnginePch.h"
#include "Application.h"

namespace cmEngine
{
	Application::Application()
	{
		// 메모리 디버깅 설정
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
		_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
		_CrtSetBreakAlloc(0);

		// 로그 생성
		Log::Initialize();
		ENGINE_LOG_INFO("Log Initialize Done.");
	}

	Application::~Application()
	{
		// 메모리 릭 체크
		_CrtDumpMemoryLeaks();
	}

	void Application::Setup(const WindowResolution& inWindowResolution, const WindowPosition& inWindowPosition)
	{
		// 엔진 생성 및 초기화
		EngineCore::Create();
		EngineCore::Get()->Initialize(inWindowResolution, inWindowPosition);

		// User Initialize
		Initialize();
	}

	//	====================================================================================================
	// 
	//		PreUpdate : 시스템 업데이트
	//		Update : 게임 메인 로직		(Update -> FinalUpdate)
	//		Render : 렌더링 로직			(RenderBegin -> PreRender -> Render -> GuiRender -> RenderEnd)
	// 
	//	====================================================================================================

	void Application::UpdateCore()
	{
		// PreUpdate
		{
			Timer::Update();
		}

		// Update
		{
			SceneManager::Update();
		}

		// Render
		{
			Renderer::RenderBegin();
			GuiRenderer::Render();
			Renderer::RenderEnd();
		}
	}

	void Application::CleanUpCore()
	{
		// Application Clean up
		CleanUp();

		// Log
		Log::Destory();

		// Engine Terminate
		EngineCore::Get()->Destroy();
	}

	int Application::Run()
	{
		//Main Loop
		MSG msg = {};
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
				if (!EngineCore::Get()->IsRunning())
				{
					break;
				}

				UpdateCore();
			}
		}

		CleanUpCore();

		return 0;
	}
}
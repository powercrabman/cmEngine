#include "EnginePch.h"
#include "Application.h"

namespace cmEngine
{
	Application::Application()
	{
		// �޸� ����� ����
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
		_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
		_CrtSetBreakAlloc(0);

		// �α� ����
		Log::Initialize();
		ENGINE_LOG_INFO("Log Initialize Done.");
	}

	Application::~Application()
	{
		// �޸� �� üũ
		_CrtDumpMemoryLeaks();
	}

	void Application::Setup(const WindowResolution& inWindowResolution, const WindowPosition& inWindowPosition)
	{
		// ���� ���� �� �ʱ�ȭ
		EngineCore::Create();
		EngineCore::Get()->Initialize(inWindowResolution, inWindowPosition);

		// User Initialize
		Initialize();
	}

	//	====================================================================================================
	// 
	//		PreUpdate : �ý��� ������Ʈ
	//		Update : ���� ���� ����		(Update -> FinalUpdate)
	//		Render : ������ ����			(RenderBegin -> PreRender -> Render -> GuiRender -> RenderEnd)
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
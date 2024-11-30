#include "0. cmEngine/cmEngine.h"

namespace cmEngine
{
	void EngineCore::Init(const ApplicationProp& inWindowProp)
	{
		Log::Ref();
		JsonSerializer::Ref();
		GameWindow::Ref().Init(
			{.Width = inWindowProp.windowResolution.Width, .Height = inWindowProp.windowResolution.Height},
			{.X = inWindowProp.windowPosition.X, .Y = inWindowProp.windowPosition.Y},
			inWindowProp.titleName);
		Timer::Ref();
		Renderer::Ref().Init(GameWindow::Ref().GetWindowResolution());
		GuiRenderer::Ref();
		ResourceManager::Ref();
		SceneManager::Ref();

		mRunning = true;
	}

	int EngineCore::Run() const
	{
		MSG msg = {};
		while (true)
		{
			if (::PeekMessage(&msg, nullptr, NULL, NULL, PM_REMOVE))
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
				// Main Loop
				if (IsRunning())
				{
					// PreUpdate
					Timer::Ref().Update();

					// Update
					SceneManager::Ref().Update();

					// Render
					Renderer::Ref().RenderBegin();
					SceneManager::Ref().Render();
					Renderer::Ref().RenderEnd();
					GuiRenderer::Ref().Render();
					Renderer::Ref().Present();
				}
				else
				{
					break;
				}
			}
		}

		// App Shutdown
		EventDispatcher::Ref().EventDispatch<AppShutdownEvent>(AppShutdownEvent{});

		// Engine Core Destroy
		EventDispatcher::Ref().Destroy();
		Destroy();

		return 0;
	}
}
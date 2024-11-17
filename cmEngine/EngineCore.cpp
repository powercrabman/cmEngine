#include "EnginePch.h"
#include "EngineViewer.h"

namespace cmEngine
{
	void EngineCore::Initialize(const WindowResolution& inResolution, const WindowPosition& inPosition)
	{
		ENGINE_LOG_INFO("Engine Initialize Start.");

		// GameWindow
		GameWindow::Initialize(inResolution, inPosition);

		// Timer
		Timer::Initialize();

		// Renderer
		Renderer::Initialize();
		GuiRenderer::Initialize();

		// ResourceManager
		ResourceManager::Initialize();

		// Editor
		EngineViewer::Initialize();

		mRunning = true;

		ENGINE_LOG_INFO("Engine Initialize Done.");
	}

	EngineCore::~EngineCore()
	{
		ENGINE_LOG_INFO("Engine Terminate Start.");
		
		// SceneManager
		SceneManager::Destroy();

		// ResourceManager
		ResourceManager::Destroy();

		// GuiRenderer
		GuiRenderer::Destroy();
		
		// Renderer
		Renderer::Destroy();

		// GameWindow
		GameWindow::Destory();

		// ConfigSystem
		ConfigEngine::Destroy();

		ENGINE_LOG_INFO("Engine Terminate Done.");
	}
}
#include "EnginePch.h"

namespace cmEngine
{
	EngineCore::EngineCore(const WindowResolution& inResolution, const WindowPosition& inPosition)
	{
		ENGINE_LOG_INFO("Engine Initialize Start.");

		// GameWindow
		GameWindow::Initialize(inResolution, inPosition);

		// Timer
		Timer::Initialize();

		// Renderer
		Renderer::Initialize();

		// ResourceManager
		ResourceManager::Initialize();

		mRunning = true;

		ENGINE_LOG_INFO("Engine Initialize Done.");
	}

	EngineCore::~EngineCore()
	{
		ENGINE_LOG_INFO("Engine Terminate Start.");

		// ResourceManager
		ResourceManager::Destroy();

		// Renderer
		Renderer::Deostroy();

		ENGINE_LOG_INFO("Engine Terminate Done.");
	}
}
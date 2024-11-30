#include "EnginePch.h"
#include "Editor.h"

namespace cmEngine
{
	void EngineCore::Initialize(const WindowResolution& inResolution, const WindowPosition& inPosition)
	{
		ENGINE_LOG_INFO("Engine Initialize Start.");

		// Json Serializer
		JsonSerializer::Initialize();

		// GameWindow
		GameWindow::Initialize(inResolution, inPosition);

		// Timer
		Timer::Initialize();

		// Renderer
		Renderer::Initialize();

		// GuiRenderer
		GuiRenderer::Initialize();

		// ResourceManager
		ResourceManager::Initialize();

		// Editor
		Editor::Initialize();

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
		GameWindow::Destroy();

		// JsonSerializer
		JsonSerializer::Destroy();

		ENGINE_LOG_INFO("Engine Terminate Done.");
	}
}
#include "EnginePch.h"
#include "EngineViewer.h"
#include "EngineVoidPopup.h"
#include "EngineDebugViewer.h"
#include "EngineOverlay.h"
#include "EngineLogViewer.h"

namespace cmEngine
{
	void EngineViewer::Initialize()
	{
		// Editor Popup Context Void 
		GuiRenderer::CreateGuiFrame<EngineVoidPopup>();
		GuiRenderer::CreateGuiFrame<EngineDebugViewer>();
		GuiRenderer::CreateGuiFrame<EngineOverlay>();
		GuiRenderer::CreateGuiFrame<EngineLogViewer>();
	}
}
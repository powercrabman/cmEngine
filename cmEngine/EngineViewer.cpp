#include "EnginePch.h"
#include "EngineViewer.h"
#include "EngineVoidPopup.h"
#include "EngineDebugViewer.h"
#include "EngineOverlay.h"
#include "EngineLogViewer.h"
#include "EngineSceneEditor.h"

namespace cmEngine
{
	void EngineViewer::Initialize()
	{
		GuiRenderer::CreateGuiFrame<EngineDebugViewer>();
		GuiRenderer::CreateGuiFrame<EngineOverlay>();
		GuiRenderer::CreateGuiFrame<EngineLogViewer>();
		GuiRenderer::CreateGuiFrame<EngineSceneEditor>();
		GuiRenderer::CreateGuiFrame<EngineVoidPopup>();
	}
}
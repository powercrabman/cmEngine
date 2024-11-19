#include "EnginePch.h"
#include "Editor.h"
#include "EditorVoidPopup.h"
#include "EditorDebugViewer.h"
#include "EditorOverlay.h"
#include "EditorLogViewer.h"
#include "EditorSceneViewer.h"

namespace cmEngine
{
	void Editor::Initialize()
	{
		GuiRenderer::CreateConcreteGui<EditorDebugViewer>();
		GuiRenderer::CreateConcreteGui<EditorOverlay>();
		GuiRenderer::CreateConcreteGui<EditorLogViewer>();
		GuiRenderer::CreateConcreteGui<EditorSceneViewer>();
		GuiRenderer::CreateConcreteGui<EditorVoidPopup>();
	}
}
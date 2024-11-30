#include "0. cmEditor/cmEditor.h"
#include "EditorCore.h"

#include "4. EditorPanel/Base/MainMenuPanel.h"
#include "4. EditorPanel/Base/DockSpacePanel.h"
#include "4. EditorPanel/Viewport/EditViewport.h"
#include "4. EditorPanel/Debug/PerformancePanel.h"
#include "4. EditorPanel/EntityInspector/EntityInspectorPanel.h"
#include "4. EditorPanel/SceneHierarchy/SceneHierarchyPanel.h"
#include "4. EditorPanel/ResourceBrowser/ResourceBrowser.h"

EditorCore::EditorCore()
{
	//Add Gui
	GuiRenderer::Ref().CreateConcreteGui<MainMenuPanel>();
	GuiRenderer::Ref().CreateConcreteGui<DockSpacePanel>();
	GuiRenderer::Ref().CreateConcreteGui<EditViewport>();
	GuiRenderer::Ref().CreateConcreteGui<PerformancePanel>();
	GuiRenderer::Ref().CreateConcreteGui<SceneHierarchyPanel>();
	GuiRenderer::Ref().CreateConcreteGui<EntityInspectorPanel>();
	GuiRenderer::Ref().CreateConcreteGui<ResourceBrowser>();

	EventDispatcher::Ref().AttachEventHandler<AppShutdownEvent>([](const AppShutdownEvent& e) {Destroy(); });
}

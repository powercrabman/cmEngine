#include "0. cmEditor/cmEditor.h"
#include "MainMenuPanel.h"

#include "4. EditorPanel/Debug/PerformancePanel.h"
#include "4. EditorPanel/EntityInspector/EntityInspectorPanel.h"
#include "4. EditorPanel/SceneHierarchy/SceneHierarchyPanel.h"
#include "4. EditorPanel/Viewport/EditViewport.h"
#include "4. EditorPanel/ResourceBrowser/ResourceBrowser.h"

void MainMenuPanel::RenderGui()
{
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			ImGui::MenuItem("New Project");
			ImGui::MenuItem("Open Project");
			ImGui::Separator();
			if (ImGui::MenuItem("Exit", "Alt+F4")) { EngineCore::Ref().CloseGame(); }
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("View"))
		{
			static Gui* vp = GuiRenderer::Ref().FindConcreteGuiOrNull<EditViewport>();
			static Gui* perform = GuiRenderer::Ref().FindConcreteGuiOrNull<PerformancePanel>();
			static Gui* sceneHie = GuiRenderer::Ref().FindConcreteGuiOrNull<SceneHierarchyPanel>();
			static Gui* entityIns = GuiRenderer::Ref().FindConcreteGuiOrNull<EntityInspectorPanel>();
			static Gui* resBws = GuiRenderer::Ref().FindConcreteGuiOrNull<ResourceBrowser>();

			ImGui::MenuItem("Viewport", ToString(vp->GetHotKey()), vp->GetVisiblePtr());
			ImGui::MenuItem("Performance", ToString(perform->GetHotKey()), perform->GetVisiblePtr());
			ImGui::MenuItem("Scene Hierarchy", ToString(sceneHie->GetHotKey()), sceneHie->GetVisiblePtr());
			ImGui::MenuItem("Entity Inspector", ToString(entityIns->GetHotKey()), entityIns->GetVisiblePtr());
			ImGui::MenuItem("Resource Browser", ToString(resBws->GetHotKey()), resBws->GetVisiblePtr());
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Style"))
		{
			ImGui::Selectable("Fonts");
			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();
	}
}

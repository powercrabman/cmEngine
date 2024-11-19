#include "EnginePch.h"
#include "EditorVoidPopup.h"
#include "EditorSceneViewer.h"
#include "EditorLogViewer.h"
#include "EditorDebugViewer.h"

namespace cmEngine
{
	EditorVoidPopup::EditorVoidPopup()
	{
	}

	void EditorVoidPopup::RenderGui()
	{
		if (mClearColorBit) { DrawClearColor(); }

		if (ImGui::BeginPopupContextVoid())
		{
			ImGui::Text("Hello, cmEngine!");
			ImGui::Separator();
			ImGui::MenuItem("Set clear color", nullptr, &mClearColorBit);
			ImGui::Separator();

			static Gui* sLogView   = GuiRenderer::FindConcreteGuiOrNull<EditorLogViewer>();
			static Gui* sDebugView = GuiRenderer::FindConcreteGuiOrNull<EditorDebugViewer>();
			static Gui* sSceneView = GuiRenderer::FindConcreteGuiOrNull<EditorSceneViewer>();

			ImGui::MenuItem("Log view", ToString(sLogView->GetHotKey()), sLogView->GetVisiblePtr());
			ImGui::MenuItem("Debug view", ToString(sDebugView->GetHotKey()), sDebugView->GetVisiblePtr());
			ImGui::MenuItem("Scene Editor", ToString(sSceneView->GetHotKey()), sSceneView->GetVisiblePtr());

			ImGui::Separator();
			if (ImGui::MenuItem("Close Game")) { EngineCore::Get()->CloseGame(); }
			ImGui::EndPopup();
		}
	}

	void EditorVoidPopup::DrawClearColor()
	{
		ImGui::Begin("Set Clear Color", &mClearColorBit, ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_AlwaysAutoResize);
		ImGui::Text("Adjust clear color");

		static Color color = Renderer::GetClearColor();
		if (ImGui::ColorEdit4("##ClearColor", reinterpret_cast<float*>(&color))) { Renderer::SetClearColor(color); }
		ImGui::End();
	}
}

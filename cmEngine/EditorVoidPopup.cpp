#include "EnginePch.h"
#include "EditorVoidPopup.h"
#include "EditorSceneViewer.h"
#include "EditorLogViewer.h"
#include "EditorDebugViewer.h"
#include "EditorResourceViewer.h"
#include "FileDialog.h"

namespace cmEngine
{
	EditorVoidPopup::EditorVoidPopup()
	{
	}

	void EditorVoidPopup::RenderGui()
	{
		if (mClearColorBit) { DrawClearColor(); }
		static bool sDlgBit = false;

		if (ImGui::BeginPopupContextVoid())
		{
			ImGui::Text("Hello, cmEngine!");
			ImGui::Separator();
			ImGui::MenuItem("Set clear color", nullptr, &mClearColorBit);
			ImGui::Separator();

			static Gui* sLogView      = GuiRenderer::FindConcreteGuiOrNull<EditorLogViewer>();
			static Gui* sDebugView    = GuiRenderer::FindConcreteGuiOrNull<EditorDebugViewer>();
			static Gui* sSceneView    = GuiRenderer::FindConcreteGuiOrNull<EditorSceneViewer>();
			static Gui* sResourceView = GuiRenderer::FindConcreteGuiOrNull<EditorResourceViewer>();

			ImGui::MenuItem("Log view", ToString(sLogView->GetHotKey()), sLogView->GetVisiblePtr());
			ImGui::MenuItem("Debug view", ToString(sDebugView->GetHotKey()), sDebugView->GetVisiblePtr());
			ImGui::MenuItem("Scene Editor", ToString(sSceneView->GetHotKey()), sSceneView->GetVisiblePtr());
			ImGui::MenuItem("Resource Viewer", ToString(sResourceView->GetHotKey()), sResourceView->GetVisiblePtr());

			if (ImGui::MenuItem("Test File Dialog")) { sDlgBit = true; }

			ImGui::Separator();
			if (ImGui::MenuItem("Close Game")) { EngineCore::Get()->CloseGame(); }
			ImGui::EndPopup();
		}
		if (sDlgBit) { static FileDialog fd = {}; fd.Draw(); }
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

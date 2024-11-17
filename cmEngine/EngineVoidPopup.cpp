#include "EnginePch.h"
#include "EngineVoidPopup.h"
#include "EngineLogViewer.h"
#include "EngineDebugViewer.h"
#include "EngineSceneEditor.h"

namespace cmEngine
{
	EngineVoidPopup::EngineVoidPopup() {}
	EngineVoidPopup::~EngineVoidPopup() {}

	void EngineVoidPopup::Initialize()
	{
		logView = GuiRenderer::FindGuiFrameOrNull<EngineLogViewer>()->GetGui();
		debugView = GuiRenderer::FindGuiFrameOrNull<EngineDebugViewer>()->GetGui();
		sceneView = GuiRenderer::FindGuiFrameOrNull<EngineSceneEditor>()->GetGui();
	}

	void EngineVoidPopup::GuiLayout()
	{
		if (mClearColorBit) { DrawClearColor(); }

		if (ImGui::BeginPopupContextVoid())
		{
			ImGui::Text("Hello, cmEngine!");
			ImGui::Separator();
			ImGui::MenuItem("Set clear color", nullptr, &mClearColorBit);
			ImGui::Separator();

			ImGui::MenuItem("Log view", ToString(logView->GetHotKey()), logView->GetVisibleAddr());
			ImGui::MenuItem("Debug view", ToString(debugView->GetHotKey()), debugView->GetVisibleAddr());
			ImGui::MenuItem("Scene Editor", ToString(sceneView->GetHotKey()), sceneView->GetVisibleAddr());
		
			ImGui::Separator();
			if (ImGui::MenuItem("Close Game")) { EngineCore::Get()->CloseGame(); }
			ImGui::EndPopup();
		}
	}

	void EngineVoidPopup::DrawClearColor()
	{
		ImGui::Begin("Set Clear Color", &mClearColorBit, ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_AlwaysAutoResize);
		ImGui::Text("Adjust clear color");

		static Color color = Renderer::GetClearColor();
		if (ImGui::ColorEdit4("##ClearColor", (float*)&color)) { Renderer::SetClearColor(color); }
		ImGui::End();
	}
}

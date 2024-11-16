#include "EnginePch.h"
#include "EngineVoidPopup.h"

namespace cmEngine
{
	void EngineVoidPopup::Initialize()
	{
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
			if (ImGui::Selectable("Close Game")) { EngineCore::Get()->CloseGame(); }
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

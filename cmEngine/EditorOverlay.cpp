#include "EnginePch.h"
#include "EditorOverlay.h"
#include "SystemMonitor.h"

namespace cmEngine
{
	EditorOverlay::EditorOverlay()
	{
		JsonSerializer::DeserializeFromSection(
			mConfig,
			Editor::sEditorConfigPath,
			"EditorOverlay"
		);
		SetVisible(mConfig.visible);
	}

	EditorOverlay::~EditorOverlay()
	{
		mConfig.visible = IsVisible();
		JsonSerializer::SerializeToSection(
			mConfig,
			Editor::sEditorConfigPath,
			"EditorOverlay"
		);
	}

	void EditorOverlay::RenderGui()
	{
		ImGui::SetNextWindowBgAlpha(mConfig.transparency);

		ImGuiWindowFlags additional = mConfig.noMoveBit ? ImGuiWindowFlags_NoMove : ImGuiWindowFlags_None;
		ImGui::Begin("Overlay view",
			(bool*)0,
			ImGuiWindowFlags_AlwaysAutoResize |
			ImGuiWindowFlags_NoDocking |
			ImGuiWindowFlags_NoCollapse |
			ImGuiWindowFlags_NoTitleBar |
			additional
		);

		if (mConfig.frameViewBit)
		{
			ImGui::SeparatorText("Frame");
			ImGui::Text("Total application execution time", Timer::GetTotalTime());
			ImGui::Text("Delta Time : %.3f milli second", Timer::GetDeltaTime() * 1000.f);
			ImGui::Text("Frame per sec : %d update per sec", Timer::GetFPS());
		}

		if (mConfig.memoryViewBit)
		{
			ImGui::SeparatorText("Hardware");
			ImGui::Text("Used memory %d / %d MB", SystemMonitor::GetUsedMemory(), SystemMonitor::GetTotalMemory());
		}

		if (ImGui::BeginPopupContextWindow())
		{
			if (ImGui::BeginMenu("Adjust transparency"))
			{
				ImGui::TextWrapped("adjust the transparency of the overlay by dragging.");
				ImGui::SliderFloat("##Trans", &mConfig.transparency, 0.f, 1.f);
				ImGui::EndMenu();
			}

			ImGui::MenuItem("Frame view", nullptr, &mConfig.frameViewBit);
			ImGui::MenuItem("Memory view", nullptr, &mConfig.memoryViewBit);
			ImGui::Checkbox("No Move", &mConfig.noMoveBit);
			ImGui::EndPopup();
		}

		ImGui::End();
	}
}

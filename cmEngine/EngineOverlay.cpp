#include "EnginePch.h"
#include "EngineOverlay.h"
#include "SystemMonitor.h"

namespace cmEngine
{
	void EngineOverlay::Initialize()
	{
		GetGui()->SetVisible(false);
	}

	void EngineOverlay::GuiLayout()
	{
		ImGui::SetNextWindowBgAlpha(mTransparency);

		ImGuiWindowFlags additional = mNoMoveBit ? ImGuiWindowFlags_NoMove : ImGuiWindowFlags_None;
		ImGui::Begin("Overlay view",
			(bool*)0,
			ImGuiWindowFlags_AlwaysAutoResize |
			ImGuiWindowFlags_NoDocking |
			ImGuiWindowFlags_NoCollapse |
			ImGuiWindowFlags_NoTitleBar |
			additional
		);

		ImGui::SeparatorText("Frame");
		ImGui::Text("Total application execution time", Timer::GetTotalTime());
		ImGui::Text("Delta Time : %.3f milli second", Timer::GetDeltaTime() * 1000.f);
		ImGui::Text("Frame per sec : %d update per sec", Timer::GetFPS());

		ImGui::SeparatorText("Hardware");
		ImGui::Text("Used memory %d / %d MB", SystemMonitor::GetUsedMemory(), SystemMonitor::GetTotalMemory());

		if (ImGui::BeginPopupContextWindow())
		{
			if (ImGui::BeginMenu("Adjust transparency"))
			{
				ImGui::TextWrapped("adjust the transparency of the overlay by dragging.");
				ImGui::SliderFloat("##Trans", &mTransparency, 0.f, 1.f);
				ImGui::EndMenu();
			}

			ImGui::Checkbox("No Move", &mNoMoveBit);
			ImGui::EndPopup();
		}

		ImGui::End();
	}
}

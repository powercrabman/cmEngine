#include "EnginePch.h"
#include "EngineOverlay.h"
#include "SystemMonitor.h"

namespace cmEngine
{
	void EngineOverlay::Initialize()
	{
		GetGui()->SetVisible(mConfig.Visible);
	}

	void EngineOverlay::GuiLayout()
	{
		ImGui::SetNextWindowBgAlpha(mConfig.Transparency);

		ImGuiWindowFlags additional = mConfig.NoMoveBit ? ImGuiWindowFlags_NoMove : ImGuiWindowFlags_None;
		ImGui::Begin("Overlay view",
			(bool*)0,
			ImGuiWindowFlags_AlwaysAutoResize |
			ImGuiWindowFlags_NoDocking |
			ImGuiWindowFlags_NoCollapse |
			ImGuiWindowFlags_NoTitleBar |
			additional
		);

		if (mConfig.FrameViewBit)
		{
			ImGui::SeparatorText("Frame");
			ImGui::Text("Total application execution time", Timer::GetTotalTime());
			ImGui::Text("Delta Time : %.3f milli second", Timer::GetDeltaTime() * 1000.f);
			ImGui::Text("Frame per sec : %d update per sec", Timer::GetFPS());
		}

		if (mConfig.MemoryViewBit)
		{
			ImGui::SeparatorText("Hardware");
			ImGui::Text("Used memory %d / %d MB", SystemMonitor::GetUsedMemory(), SystemMonitor::GetTotalMemory());
		}

		if (ImGui::BeginPopupContextWindow())
		{
			if (ImGui::BeginMenu("Adjust transparency"))
			{
				ImGui::TextWrapped("adjust the transparency of the overlay by dragging.");
				ImGui::SliderFloat("##Trans", &mConfig.Transparency, 0.f, 1.f);
				ImGui::EndMenu();
			}

			ImGui::MenuItem("Frame view", nullptr, &mConfig.FrameViewBit);
			ImGui::MenuItem("Memory view", nullptr, &mConfig.MemoryViewBit);
			ImGui::Checkbox("No Move", &mConfig.NoMoveBit);
			ImGui::EndPopup();
		}

		ImGui::End();
	}
}

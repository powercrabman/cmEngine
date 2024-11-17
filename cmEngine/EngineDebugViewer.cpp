#include "EnginePch.h"
#include "EngineDebugViewer.h"
#include "SystemMonitor.h"
#include "GameEntity.h"
#include "EngineOverlay.h"

namespace cmEngine
{
	void EngineDebugViewer::Initialize()
	{
		GetGui()->SetVisible(mConfig.Visible);
		GetGui()->SetHotKey(eKeyCode::F5);
	}

	EngineDebugViewer::~EngineDebugViewer()
	{
		EngineDebugViwerConfig cf = {};
		cf.Visible = GetGui()->GetVisible();
		ConfigEngine::Save(cf);
	}

	void EngineDebugViewer::GuiLayout()
	{
		ImGui::Begin("Debug Viewer", GetGuiVisibleAddr(), ImGuiWindowFlags_AlwaysAutoResize);

		if (ImGui::BeginTabBar("Test"))
		{
			if (ImGui::BeginTabItem("Performence"))
			{
				DrawPerformenceView();
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem("Input"))
			{
				DrawInputView();
				ImGui::EndTabItem();
			}

			ImGui::EndTabBar();
		}

		if (ImGui::BeginPopupContextWindow())
		{
			if (ImGui::MenuItem("Close")) { GetGui()->SetVisible(false); }

			ImGui::EndPopup();
		}

		ImGui::End();
	}

	void EngineDebugViewer::DrawPerformenceView()
	{
		ImGui::SeparatorText("Frame");
		ImGui::Text("Total application execution time", Timer::GetTotalTime());
		ImGui::Text("Delta Time : %.3f milli second", Timer::GetDeltaTime() * 1000.f);
		ImGui::Text("Frame per sec : %d update per sec", Timer::GetFPS());

		ImGui::SeparatorText("Hardware");
		ImGui::Text("Used memory %d / %d MB", SystemMonitor::GetUsedMemory(), SystemMonitor::GetTotalMemory());

		static GuiFrame* overlayGui = GuiRenderer::FindGuiFrameOrNull<EngineOverlay>();
		ImGui::Checkbox("Enable overlay view", &mConfig.OverlayBit);
		overlayGui->GetGui()->SetVisible(mConfig.OverlayBit);
	}

	void EngineDebugViewer::DrawInputView()
	{
		ImGui::SeparatorText("Mouse");
		auto [mx, my] = Input::GetMousePosition();
		ImGui::Text("Mouse Position : (%.f, %.f)", mx, my);
		ImGui::Text("Left Button Click : %s", Input::IsHold(eKeyCode::MouseLeft) ? "Click" : "None");
		ImGui::Text("Middle Button Click : %s", Input::IsHold(eKeyCode::MouseMiddle) ? "Click" : "None");
		ImGui::Text("Right Button Click : %s", Input::IsHold(eKeyCode::MouseRight) ? "Click" : "None");
	}

}

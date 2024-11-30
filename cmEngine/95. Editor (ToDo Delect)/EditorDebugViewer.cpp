#include "0. cmEngine/cmEngine.h"
#include "EditorDebugViewer.h"
#include "EditorOverlay.h"
#include "97. SystemMonitor/SystemMonitor.h"

namespace cmEngine
{
	EditorDebugViewer::EditorDebugViewer()
	{
		JsonSerializer::Ref().DeserializeFromSection(
			mConfig,
			Editor::sEditorConfigPath,
			"EditorDebugViewer"
		);
		SetVisible(mConfig.visible);
		SetHotKey(eKeyCode::F5);
	}

	EditorDebugViewer::~EditorDebugViewer()
	{
		mConfig.visible = IsVisible();
		JsonSerializer::Ref().SerializeToSection(
			mConfig,
			Editor::sEditorConfigPath,
			"EditorDebugViewer"
		);
	}

	void EditorDebugViewer::RenderGui()
	{
		ImGui::Begin("Debug Viewer", GetVisiblePtr(), ImGuiWindowFlags_AlwaysAutoResize);

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
			if (ImGui::MenuItem("Close")) { SetVisible(false); }

			ImGui::EndPopup();
		}

		ImGui::End();
	}

	void EditorDebugViewer::DrawPerformenceView()
	{
		ImGui::SeparatorText("Frame");
		ImGui::Text("Total application execution time", Timer::Ref().GetTotalTime());
		ImGui::Text("Delta Time : %.3f milli second", Timer::Ref().GetDeltaTime() * 1000.f);
		ImGui::Text("Frame per sec : %d update per sec", Timer::Ref().GetFPS());

		ImGui::SeparatorText("Hardware");
		ImGui::Text("Used memory %d / %d MB", SystemMonitor::GetUsedMemory(), SystemMonitor::GetTotalMemory());

		static Gui* overlayGui = GuiRenderer::Ref().FindConcreteGuiOrNull<EditorOverlay>();
		ImGui::Checkbox("Enable overlay view", overlayGui->GetVisiblePtr());
	}

	void EditorDebugViewer::DrawInputView()
	{
		ImGui::SeparatorText("Mouse");
		auto [mx, my] = Input::GetMousePosition();
		ImGui::Text("Mouse Position : (%.f, %.f)", mx, my);
		ImGui::Text("Left Button Click : %s", Input::IsHold(eKeyCode::MouseLeft) ? "Click" : "None");
		ImGui::Text("Middle Button Click : %s", Input::IsHold(eKeyCode::MouseMiddle) ? "Click" : "None");
		ImGui::Text("Right Button Click : %s", Input::IsHold(eKeyCode::MouseRight) ? "Click" : "None");
	}
}

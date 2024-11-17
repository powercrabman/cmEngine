#include "EnginePch.h"
#include "EngineSceneEditor.h"

namespace cmEngine
{
	EngineSceneEditor::~EngineSceneEditor()
	{
		EngineSceneEditorConfig cf = {};
		cf.Visible = GetGui()->GetVisible();
		ConfigEngine::Save(cf);
	}

	void EngineSceneEditor::Initialize()
	{
		GetGui()->SetVisible(mConfig.Visible);
		GetGui()->SetHotKey(eKeyCode::F7);
	}

	void EngineSceneEditor::GuiLayout()
	{
		ImGui::SetNextWindowSize({ 300,400 }, ImGuiCond_FirstUseEver);
		ImGui::Begin("Scene Editor", GetGuiVisibleAddr());
		Scene* curSc = SceneManager::GetCurrentScene();

		ImGui::SeparatorText("Scene");
		ImGui::Text("Scene Name: %s", curSc->ToString());
		ImGui::Spacing();
		ImGui::SeparatorText("Camera");

		GameEntity* entity = Renderer::GetCurrentCamera()->GetOwner();
		ImGui::Text("Onwer Entity Name : %s", entity->GetName());
		ImGui::Text("Onwer Entity ID : %d", entity->GetObjectID());
		ImGui::Spacing();

		ImGui::SeparatorText("Entity List");
		ImGui::Text("Entity count : %d", curSc->GetEntityCount());

		if (ImGui::BeginChild("Entity Viewer", { 0, -5 -ImGui::GetFrameHeightWithSpacing()}, ImGuiChildFlags_Border))
		{
			for (auto iter = curSc->GetGameEntitiesConstBegin(); iter != curSc->GetGameEntitiesConstEnd(); ++iter)
			{
				GameEntity* e = (*iter);
				auto str = std::format("Entity Name : {}\nEntity ID : {}", e->GetName(), e->GetObjectID());
				ImGui::Selectable(str.c_str());
				ImGui::Separator();
			}
			ImGui::EndChild();
		}

		ImGui::Spacing();
		if (ImGui::Button("Add GameEntity")) { /* Do Something*/ }
		ImGui::End();
	}

	void EngineSceneEditor::DrawEntityEditor()
	{
		if (mTargetEntity->IsValid())
		{
			
		}
		else
		{
			static const char* text = "Do not exist edit entity";
			ImVec2 windowSize = ImGui::GetWindowSize();
			ImVec2 textSize = ImGui::CalcTextSize(text);

			ImVec2 alignPos = {
				(windowSize.x - textSize.x) * 0.5f,  
				(windowSize.y - textSize.y) * 0.5f   
			};

			ImGui::SetCursorPos(alignPos);
			ImGui::Text(text);
		}
	}
}

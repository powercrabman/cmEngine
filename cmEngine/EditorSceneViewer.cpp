#include "EnginePch.h"
#include "EditorSceneViewer.h"

#include "Editor.h"
#include "GuiHelper.h"

namespace cmEngine
{
	EditorSceneViewer::EditorSceneViewer()
	{
		JsonSerializer::DeserializeFromSection(
			mConfig,
			Editor::sEditorConfigPath,
			"EditorSceneViewer"
		);
		SetVisible(mConfig.visible);
		SetHotKey(eKeyCode::F7);
	}

	EditorSceneViewer::~EditorSceneViewer()
	{
		mConfig.visible = IsVisible();
		JsonSerializer::SerializeToSection(
			mConfig,
			Editor::sEditorConfigPath,
			"EditorSceneViewer"
		);
	}

	void EditorSceneViewer::RenderGui()
	{
		ImGui::SetNextWindowSize(ImVec2{ 300, 400 }, ImGuiCond_FirstUseEver);
		ImGui::Begin("Scene Editor", GetVisiblePtr());

		Scene* scene = SceneManager::GetCurrentScene();

		// Scene Information
		{
			ImGui::SeparatorText("Scene");
			ImGui::Text("Scene Name : %s", scene->ToString());
			ImGui::Spacing();

			// Camera
			GameEntity cmrEntity = scene->GetMainCameraEntity();
			ImGui::Text("Current Camera Entity ID : %d", cmrEntity.GetID());

			std::string_view name = "Undefined";
			if (Name* n = cmrEntity.TryFindComponent<Name>()) { name = n->name; }
			ImGui::Text("Current Camera Entity Name : %s", name.data());

			auto [t, cmr] = cmrEntity.FindComponents<Transform, Camera>();
			ImGui::Text("Camera Position : (%.2f, %.2f, %.2f)", t.position.x, t.position.y, t.position.z);
			ImGui::Text("Camera Rotation : (%.2f, %.2f, %.2f)", Math::RadToDeg(t.rotation.x), Math::RadToDeg(t.rotation.y), Math::RadToDeg(t.rotation.z));
			ImGui::Text("Projection Mode : %s", ToString(cmr.mode));
			ImGui::Text("Near, Far : [%.2f, %.2f]", cmr.nearPlane, cmr.farPlane);

			if (cmr.mode == eCameraProjectionMode::Orthographic)
			{
				ImGui::Text("Width, Height : [%.2f, %.2f]", cmr.width, cmr.height);
			}
			else
			{
				ImGui::Text("Field Of View : %.2f", cmr.fov);
			}

			ImGui::Spacing();
		}

		// Entity List
		ImGui::SeparatorText("Scene Game Entity");

		auto	totalEntityView = scene->GetView<entt::entity>();
		auto& reg = SceneManager::GetCurrentScene()->GetRegistry();

		ImGui::Text("Total Game Entity Count : %d", totalEntityView.size<>());

		if (ImGui::BeginChild("Entity List", ImVec2{ 0, -ImGui::GetFrameHeightWithSpacing() }, ImGuiChildFlags_Border))
		{
			ImGuiListClipper clipper;
			clipper.Begin(static_cast<int>(totalEntityView.size<>()));

			while (clipper.Step())
			{
				for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; ++i)
				{
					auto entity = *(totalEntityView.begin() + i);
					GameEntity gameEntity = { &reg, entity };
					std::string_view name = "Undefined";
					if (Name* n = gameEntity.TryFindComponent<Name>()) { name = n->name; }

					if (ImGui::Selectable(std::format("ID : {}, Name : {}", gameEntity.GetID(), name).c_str(), entity == mTargetEntity))
					{
						mTargetEntity = gameEntity;
						mEntityEditorBit = true;
					}

					ImGui::Separator();
				}
			}

			// Popup
			if (ImGui::BeginPopupContextWindow("Popup"))
			{
				if (ImGui::MenuItem("Close")) { SetVisible(false); }
				ImGui::EndPopup();
			}

			ImGui::EndChild();
		}

		// Add Entity
		if (ImGui::Button("Add Entity"))
		{
			scene->CreateGameEntity();
		}

		// Entity Editor
		ImGui::SameLine();
		if (ImGui::Button(mEntityEditorBit ? "Close Entity Editor" : "Open Entity Editor")) { mEntityEditorBit = !mEntityEditorBit; }

		if (mEntityEditorBit)
		{
			DrawEntityEditor();
		}

		// Popup
		if (ImGui::BeginPopupContextWindow("Popup"))
		{
			if (ImGui::MenuItem("Close")) { SetVisible(false); }
			ImGui::EndPopup();
		}

		ImGui::End();
	}

	void EditorSceneViewer::DrawEntityEditor()
	{
		ImGui::Begin("GameEntity Editor", &mEntityEditorBit);

		if (ImGui::BeginPopupContextItem())
		{
			if (ImGui::MenuItem("Close")) { mEntityEditorBit = false; }
			ImGui::EndPopup();
		}

		if (mTargetEntity.IsValid())
		{
			// Add Component
			static bool sAddCompBit = false;
			ImGui::Button("Add Component");
			if (ImGui::BeginPopupContextItem("Add Component", ImGuiPopupFlags_MouseButtonLeft))
			{
				if (ImGui::MenuItem("Name")) { mTargetEntity.TryCreateComponent<Name>(); };
				if (ImGui::MenuItem("Transform")) { mTargetEntity.TryCreateComponent<Transform>(); };
				if (ImGui::MenuItem("Camera")) { mTargetEntity.TryCreateComponent<Camera>(); };
				if (ImGui::MenuItem("FlipbookRender")) { mTargetEntity.TryCreateComponent<FlipbookRender>(); };
				if (ImGui::MenuItem("SpriteRender")) { mTargetEntity.TryCreateComponent<SpriteRender>(); };
				if (ImGui::MenuItem("GeometryRender")) { mTargetEntity.TryCreateComponent<GeometryRender>(); };
				if (ImGui::MenuItem("RenderProfile")) { mTargetEntity.TryCreateComponent<RenderProfile>(); };
				ImGui::EndPopup();
			}

			// Button
			ImGui::SameLine();
			if (ImGui::Button("Delect Entity")) { ImGui::OpenPopup("Alert"); }
			ImGui::SameLine();
			if (ImGui::Button("Clone")) { SceneManager::GetCurrentScene()->CloneGameEntity(mTargetEntity); };

			Editor::RenderEditLayer(mTargetEntity);
				
			// Delect Option
			if (ImGui::BeginPopupModal("Alert", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
			{
				ImGui::Text("Are you sure you want to remove the entity?");
				if (ImGui::Button("Yes"))
				{
					SceneManager::GetCurrentScene()->RemoveGameEntity(mTargetEntity);
					mTargetEntity = GameEntity::NullEntity;
					ImGui::CloseCurrentPopup();
				}
				ImGui::SameLine();
				if (ImGui::Button("No"))
				{
					ImGui::CloseCurrentPopup();
				}

				ImGui::EndPopup();
			}
		}
		else
		{
			mTargetEntity = GameEntity::NullEntity;
			GuiHelper::TextColoredCenterAlign("No GameEntity selected for editing", ToImVec4(Colors::Gray));
		}

		ImGui::End();
	}

}

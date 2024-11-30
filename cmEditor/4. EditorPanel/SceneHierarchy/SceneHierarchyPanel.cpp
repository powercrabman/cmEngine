#include "0. cmEditor/cmEditor.h"
#include "SceneHierarchyPanel.h"

#include "10. Scene/SceneSerializer.h"
#include "2. Editor/EditorCore.h"

SceneHierarchyPanel::SceneHierarchyPanel()
{
	if (JSON_SERIALIZER.DeserializerFromFileWithTag(mConfig, Config::gEditorPanelConfigFileName, sClassName))
	{
		SetVisible(mConfig.visible);
	}
}

SceneHierarchyPanel::~SceneHierarchyPanel()
{
	mConfig.visible = IsVisible();
	JSON_SERIALIZER.SerializeToFileWithTag(mConfig, Config::gEditorPanelConfigFileName, sClassName);
}

void SceneHierarchyPanel::RenderGui()
{
	ImGui::Begin("Scene Hierarchy");

	ImGui::TextUnformatted("Scene :");
	ImGui::SameLine();

	auto [sceneList, sceneListSize] = SCENE_MANAGER.GetSceneNameList();

	if (sceneListSize > 0)
	{
		Scene* editScene = nullptr;
		static int sceneListIndex = -1;

		if (SCENE_MANAGER.TryGetCurrentScene() && SCENE_MANAGER.TryGetCurrentScene() != editScene)
		{
			editScene           = SCENE_MANAGER.TryGetCurrentScene();
			const char* name    = SCENE_MANAGER.TryGetCurrentScene()->GetName();
			for (sceneListIndex = 0; sceneListIndex < sceneListSize; ++sceneListIndex)
			{
				if (std::strcmp(sceneList[sceneListIndex], name) == 0) { break; }
			}
		}
		else if (!editScene)
		{
			sceneListIndex = -1;
		}

		if (ImGui::Combo("##SceneSelector", &sceneListIndex, sceneList, sceneListSize))
		{
			SCENE_MANAGER.ChangeScene(sceneList[sceneListIndex]);
		}
	}
	else
	{
		static int n = 0;
		ImGui::Combo("##DoNotExist", &n, "scene does not exist.", 1);
	}

	if (ImGui::Button("New Scene")) { ImGui::OpenPopup("Create New Scene"); }
	ImGui::SameLine();
	if (ImGui::Button("Delete Scene")) { if (SCENE_MANAGER.TryGetCurrentScene()) { ImGui::OpenPopup("Delete Scene"); } }
	if (ImGui::Button("Save Scene")) { ImGui::OpenPopup("Save Scene"); }
	ImGui::SameLine();
	if (ImGui::Button("Load Scene")) { ImGui::OpenPopup("Load Scene"); }
	ImGui::Separator();

	DrawSceneHierarchy();
	HandleCreateScenePopup();
	HandleDeleteScenePopup();
	HandleSceneSerialize();
	HandleSceneDeserialize();

	mModal.Draw();
	mModalYN.Draw();

	ImGui::End();
}

void SceneHierarchyPanel::HandleCreateScenePopup()
{
	if (ImGui::BeginPopupModal("Create New Scene", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize))
	{
		enum { BUFFER_MAX = 128 };
		enum eErrorFlag { NONE, EMPTY, DUPLICATION };
		static char sceneBuf[BUFFER_MAX];
		static eErrorFlag flag = NONE;
		ImGui::TextUnformatted("Scene Name :");
		ImGui::InputText("##Scene Name", sceneBuf, BUFFER_MAX);

		switch (flag)
		{
		case NONE: ImGui::TextWrapped(""); break;
		case EMPTY: ImGui::TextColored(ToImVec4(Colors::Palevioletred), "Not allowed empty name."); break;
		case DUPLICATION: ImGui::TextColored(ToImVec4(Colors::Palevioletred), "Duplicate scene name"); break;
		}

		if (ImGui::Button("Create"))
		{
			::ImStrTrimBlanks(sceneBuf);
			if (::strlen(sceneBuf) == 0)
			{
				flag = EMPTY;
			}
			else if (SCENE_MANAGER.TryFindScene(sceneBuf))
			{
				flag = DUPLICATION;
			}
			else
			{
				SCENE_MANAGER.ChangeScene(SCENE_MANAGER.CreateScene(sceneBuf));
				flag = NONE;
				ImGui::CloseCurrentPopup();
			}
		}

		ImGui::SameLine();
		if (ImGui::Button("Cancel"))
		{
			flag = NONE;
			ImGui::CloseCurrentPopup();
		}

		ImGui::EndPopup();
	}
}

void SceneHierarchyPanel::HandleDeleteScenePopup()
{
	if (ImGui::BeginPopupModal("Delete Scene", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::Text("Are you sure you want to delete it?");
		if (ImGui::Button("Yes"))
		{
			SCENE_MANAGER.RemoveScene(SCENE_MANAGER.TryGetCurrentScene());
			ImGui::CloseCurrentPopup();
		}
		ImGui::SameLine();
		if (ImGui::Button("No")) { ImGui::CloseCurrentPopup(); }

		ImGui::EndPopup();
	}
}

void SceneHierarchyPanel::DrawSceneHierarchy() const
{
	if (ImGui::BeginChild("Scene Hierarchy", ImVec2{ 0, -5 - ImGui::GetFrameHeightWithSpacing() }, ImGuiChildFlags_Border))
	{
		if (SCENE_MANAGER.TryGetCurrentScene())
		{
			auto view = SCENE_MANAGER.TryGetCurrentScene()->GetView<entt::entity>();
			entt::entity editEntity = EDITOR_CORE.TryGetEditEntity();
			for (auto ent : view)
			{
				std::string_view str;
				if (Name* name = SCENE_MANAGER.TryGetCurrentScene()->GetRegistry().try_get<Name>(ent))
				{
					str = name->name;
				}
				else
				{
					str = "Undefined";
				}

				if (ImGui::Selectable(std::format("ID : {}, Name : {}", static_cast<int>(ent), str).c_str(), ent == editEntity))
				{
					if (editEntity == ent)
					{
						EDITOR_CORE.SetEditEntity(GameEntity::NullEntity);
					}
					else
					{
						EDITOR_CORE.SetEditEntity(GameEntity{ SCENE_MANAGER.TryGetCurrentScene(), ent });
					}
				}
				ImGui::Separator();
			}
		}
		ImGui::EndChild();
	}
	ImGui::Spacing();

	// Create
	if (ImGui::Button("Add Entity"))
	{
		EDITOR_CORE.SetEditEntity(SCENE_MANAGER.TryGetCurrentScene()->CreateGameEntity());
	}
	ImGui::SameLine();

	// Delect
	if (ImGui::Button("Delete Entity"))
	{
		const GameEntity& ge = EDITOR_CORE.TryGetEditEntity();
		if (!ge.IsNull())
		{
			SCENE_MANAGER.TryGetCurrentScene()->RemoveGameEntity(ge);
		}
	}
	ImGui::SameLine();

	// Clone
	if (ImGui::Button("Clone Entity"))
	{
		const GameEntity& ge = EDITOR_CORE.TryGetEditEntity();
		if (!ge.IsNull())
		{
			SCENE_MANAGER.TryGetCurrentScene()->CloneGameEntity(ge);
		}
	}
}

void SceneHierarchyPanel::HandleSceneSerialize()
{
	if (ImGui::BeginPopupModal("Save Scene", nullptr, ImFlag::sModalFlag))
	{
		if (SCENE_MANAGER.TryGetCurrentScene())
		{
			enum { BUFFER_SIZE = 64 };
			static char sBuffer[BUFFER_SIZE] = {};
			static bool sInit = false;
			if (!sInit) { ::strcpy_s(sBuffer, SCENE_MANAGER.TryGetCurrentScene()->GetName()); sInit = true; }
			ImGui::TextUnformatted("Save Scene");
			ImGui::InputText("##Scene name", sBuffer, BUFFER_SIZE);
			if (ImGui::Button("Save"))
			{
				SceneSerializer{}.SerializeSceneToFile(SCENE_MANAGER.TryGetCurrentScene());
				sInit = false;
				ImGui::CloseCurrentPopup();
				ImGui::EndPopup();
				mModal.Open("Save Done.");
				return;
			}

			ImGui::SameLine();
			if (ImGui::Button("Cancel"))
			{
				sInit = false;
				ImGui::CloseCurrentPopup();
			}
		}
		else
		{
			ImGui::CloseCurrentPopup();
			ImGui::EndPopup();
			mModal.Open("Select scene to save.");
			return;
		}
		ImGui::EndPopup();
	}
}

void SceneHierarchyPanel::HandleSceneDeserialize()
{
	if (ImGui::BeginPopupModal("Load Scene", nullptr, ImFlag::sModalFlag))
	{
		enum { BUFFER_SIZE = 64 };
		static char sBuffer[BUFFER_SIZE] = {};
		static bool sInit = false;
		if (!sInit) { sInit = true; }
		ImGui::TextUnformatted("Save Scene");
		ImGui::InputText("##SaveScene", sBuffer, BUFFER_SIZE);

		if (ImGui::Button("Load"))
		{
			// æ¿ ¿Ã∏ß ¡ﬂ∫π
			std::string name = sBuffer;
			if (SCENE_MANAGER.IsExistScene(name.substr(0, name.find('.'))))
			{
				ImGui::EndPopup();
				mModalYN.Open(std::format("{} is already exist scene\nWould you like to overwrite the scene?", sBuffer).c_str(), [&]()
					{
						SceneSerializer{}.DeserializeSceneFromFile(sBuffer);
					});
				return;
			}

			if (!SceneSerializer{}.DeserializeSceneFromFile(sBuffer))
			{
				ImGui::CloseCurrentPopup();
				ImGui::EndPopup();
				mModal.Open("Scene Load Fail.\nInvalid path.");
				return;
			}
		}

		ImGui::SameLine();

		if (ImGui::Button("Cancel"))
		{
			ImGui::CloseCurrentPopup();
		}

		ImGui::EndPopup();
	}
}

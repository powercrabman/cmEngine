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
	ImWindow window{ "Scene Hierarchy" , GetVisiblePtr() };

	// Draw Panel
	DrawSceneSelector();
	DrawSceneHierarchy();

	// Handling
	HandleCreateScenePopup();
	HandleDeleteScenePopup();
	HandleSceneSerialize();
	HandleSceneDeserialize();

	// Modal
	if (ImModal modal = { mSignal })
	{
		modal.DrawWithMessage(mAlertMsg.c_str(), "OK");
	}
}

void SceneHierarchyPanel::HandleCreateScenePopup()
{
	if (ImModal modal = { "Create New Scene" })
	{
		enum { BUFFER_MAX = 128 };
		static char sceneBuf[BUFFER_MAX];

		ImGui::TextUnformatted("Scene Name :");
		ImGui::InputText("##Scene Name", sceneBuf, BUFFER_MAX);

		eImPopupResult ret = modal.DrawOnlyButton("Create", "Cancel");
		if (ret == eImPopupResult::Botton1)
		{
			modal.EndModal();

			// Create
			::ImStrTrimBlanks(sceneBuf);
			if (::strlen(sceneBuf) == 0)
			{
				modal.CloseAndOpenPopup(mSignal);
				mAlertMsg = "Empty name scene is not allow.";
			}
			else if (SCENE_MANAGER.TryFindScene(sceneBuf))
			{
				modal.CloseAndOpenPopup(mSignal);
				mAlertMsg = "duplicated scene name";
			}
			else
			{
				SCENE_MANAGER.ChangeScene(SCENE_MANAGER.CreateScene(sceneBuf));
				modal.CloseAndOpenPopup(mSignal);
				mAlertMsg = "scene create done.";
			}
		}
	}
}

void SceneHierarchyPanel::HandleDeleteScenePopup()
{
	if (ImModal modal = { "Delete Scene" })
	{
		eImPopupResult ret = modal.DrawWithMessage("Are you sure you want to delete it?\n", "Yes", "No");

		if (ret == eImPopupResult::Botton1)
		{
			// Yes
			SCENE_MANAGER.RemoveScene(SCENE_MANAGER.TryGetCurrentScene());
		}
	}
}

void SceneHierarchyPanel::DrawSceneHierarchy() const
{
	if (ImChildWindow window = { "Scene Hierarchy", ImVec2{ 0, -5 - ImGui::GetFrameHeightWithSpacing() }, ImGuiChildFlags_Border })
	{
		Scene* sc = SCENE_MANAGER.TryGetCurrentScene();
		if (sc)
		{
			auto view = sc->GetView<entt::entity>();

			if (ImTreeNode node = { "Scene Inspector" })
			{
				ImGui::Text("Scene Name : %s", sc->GetName());
				GameEntity sceneCmr = sc->TryGetSceneCamera();
				ImGui::Text("Scene Camera ID : %s", sceneCmr.IsValid() ? std::to_string(sceneCmr.GetID()).c_str() : "None");
				ImGui::Text("Total entity count : %d", view->size());
			}

			ImGui::Separator();

			entt::entity editEntity = EDITOR_CORE.TryGetEditEntity();

			ImGuiListClipper clipper;
			clipper.Begin(view->size());

			while (clipper.Step())
			{
				for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; ++i)
				{
					auto ent = *std::next(view.begin(), i);
					std::string_view str;
					if (Name* name = sc->GetRegistry().try_get<Name>(ent))
					{
						str = name->name;
					}
					else
					{
						str = "Undefined";
					}

					if (ImGui::Selectable(std::format("ID : {}, Name : {}", static_cast<int>(ent), str.data()).c_str(), ent == editEntity))
					{
						if (editEntity == ent)
						{
							EDITOR_CORE.SetEditEntity(GameEntity::NullEntity);
						}
						else
						{
							EDITOR_CORE.SetEditEntity(GameEntity{ sc, ent });
						}
					}
					ImGui::Separator();
				}
			}

			clipper.End();
		}
	}
	ImGui::Spacing();

	if (ImGui::Button("Add Entity"))
	{
		Scene* sc = SCENE_MANAGER.TryGetCurrentScene();
		if (sc) { EDITOR_CORE.SetEditEntity(sc->CreateGameEntity()); }
	}
	ImGui::SameLine();

	if (ImGui::Button("Delete Entity"))
	{
		const GameEntity& ge = EDITOR_CORE.TryGetEditEntity();
		if (!ge.IsNull()) { SCENE_MANAGER.TryGetCurrentScene()->RemoveGameEntity(ge); }
	}
	ImGui::SameLine();

	if (ImGui::Button("Clone Entity")) { ImGui::OpenPopup("Clone Popup"); }
	if (ImPopup popup = { "Clone Popup" })
	{
		ImGui::TextUnformatted("How Many?");
		static int sCloneCount = 1;
		ImGui::DragInt("##Clone", &sCloneCount, 1, 1, 10000);

		eImPopupResult ret = popup.DrawOnlyButton("Clone", "Cancel", false);

		// Clone 버튼을 눌렀을 때
		if (ret == eImPopupResult::Botton1)
		{
			const auto& ge = EDITOR_CORE.TryGetEditEntity();
			if (!ge.IsNull())
			{
				for (int i = 0; i < sCloneCount; ++i) { SCENE_MANAGER.TryGetCurrentScene()->CloneGameEntity(ge); }
			}
		}
	}
}

inline void SceneHierarchyPanel::DrawSceneSelector() const
{
	ImGui::TextUnformatted("Scene :");
	ImGui::SameLine();

	auto [sceneList, sceneListSize] = SCENE_MANAGER.GetSceneNameList();

	if (sceneListSize > 0)
	{
		Scene* editScene = nullptr;
		static int sceneListIndex = -1;

		if (SCENE_MANAGER.TryGetCurrentScene() && SCENE_MANAGER.TryGetCurrentScene() != editScene)
		{
			editScene = SCENE_MANAGER.TryGetCurrentScene();
			const char* name = SCENE_MANAGER.TryGetCurrentScene()->GetName();
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
}

void SceneHierarchyPanel::HandleSceneSerialize()
{
	if (ImModal modal = { "Save Scene" })
	{
		Scene* curScene = SCENE_MANAGER.TryGetCurrentScene();
		if (curScene)
		{
			enum { BUFFER_SIZE = 64 };
			static char sBuffer[BUFFER_SIZE] = {};

			ImGui::TextUnformatted("Input name to save");
			ImGui::InputText("##Scene name", sBuffer, BUFFER_SIZE);
			if (ImGui::Button("Load current scene name")) 
			{
				::strcpy_s(sBuffer, curScene->GetName());
			}

			eImPopupResult ret = modal.DrawOnlyButton("Save", "Cancel");

			if (ret == eImPopupResult::Botton1)
			{
				SceneSerializer{}.SerializeSceneToFile(curScene);
				modal.CloseAndOpenPopup(mSignal);
				mAlertMsg = "Save done";
			}
		}
		else
		{
			modal.CloseAndOpenPopup(mSignal);
			mAlertMsg = "current scene is not selected.";
		}
	}
}

void SceneHierarchyPanel::HandleSceneDeserialize()
{
	enum { BUFFER_SIZE = 64 };
	static char sBuffer[BUFFER_SIZE] = {};

	if (ImModal modal = { "Load Scene" })
	{
		ImGui::TextUnformatted("Load Scene");
		ImGui::InputText("##SaveScene", sBuffer, BUFFER_SIZE);

		eImPopupResult ret = modal.DrawOnlyButton("Load", "Cancel");

		if (ret == eImPopupResult::Botton1)
		{
			std::filesystem::path name = sBuffer;
			if (SCENE_MANAGER.IsExistScene(name.stem().string()))
			{
				modal.CloseAndOpenPopup("Overwrite");
			}
			else
			{
				if (SceneSerializer{}.DeserializeSceneFromFile(sBuffer))
				{
					modal.CloseAndOpenPopup(mSignal);
					mAlertMsg = "Scene Load Done.";
				}
				else
				{
					modal.CloseAndOpenPopup(mSignal);
					mAlertMsg = "Scene Load Fail.\nInvalid path.";
				}
			}
		}
	}

	if (ImModal modal = { "Overwrite" })
	{
		eImPopupResult ret = modal.DrawWithMessage("{} is already exist scene\nWould you like to overwrite the scene?", "Yes", "No");

		if (ret == eImPopupResult::Botton1)
		{
			SceneSerializer{}.DeserializeSceneFromFile(sBuffer);
		}
	}
}
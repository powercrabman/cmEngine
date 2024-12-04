#include "0. cmEditor/cmEditor.h"
#include "EntityInspectorPanel.h"

EntityInspectorPanel::EntityInspectorPanel()
{
	if (JSON_SERIALIZER.DeserializerFromFileWithTag(mConfig, Config::gEditorPanelConfigFileName, sClassName))
	{
		SetVisible(mConfig.visible);
	}
}

EntityInspectorPanel::~EntityInspectorPanel()
{
	mConfig.visible = IsVisible();
	JSON_SERIALIZER.SerializeToFileWithTag(mConfig, Config::gEditorPanelConfigFileName, sClassName);
}

void EntityInspectorPanel::RenderGui()
{
	ImWindow window = { "Entity Inspector", GetVisiblePtr() };

	mEntity = EDITOR_CORE.TryGetEditEntity();

	if (mEntity.IsValid())
	{
		ImGui::Text("Entity ID: %d", mEntity.GetID());

		ImGui::Separator();

		// Component Menu
		ImGui::Button("Add Component");
		if (ImPopupItem popup{ nullptr , ImGuiPopupFlags_MouseButtonLeft }) { DrawCreateComponentMenu(); }

		ImGui::SameLine();
		if (ImGui::Button("Remove Component")) { ImGui::OpenPopup("RemoveComponentPopup"); }
		if (ImPopupItem popup{ nullptr , ImGuiPopupFlags_MouseButtonLeft }) { DrawRemoveComponentMenu(); }

		// Context Window
		if (ImPopupWindow window = {})
		{
			if (ImMenu menu = { "Add Component" }) { DrawCreateComponentMenu(); }
			if (ImMenu menu = { "Remove Component" }) { DrawRemoveComponentMenu(); }
		}

		ImGui::Spacing();

		// Draw Component Panel
		DrawComponentPanel<Name>("Name", &EntityInspectorPanel::DrawNamePanel);
		DrawComponentPanel<Transform>("Transform", &EntityInspectorPanel::DrawTransformPanel);
		DrawComponentPanel<Camera>("Camera", &EntityInspectorPanel::DrawCameraPanel);
		DrawComponentPanel<SpriteRender>("Sprite Render", &EntityInspectorPanel::DrawSpriteRenderPanel);
		DrawComponentPanel<FlipbookRender>("Flipbook Render", &EntityInspectorPanel::DrawFlipbookRenderPanel);
		DrawComponentPanel<RenderProfile>("Render Profile", &EntityInspectorPanel::DrawRenderProfilePanel);
	}
	else
	{
		mEntity = GameEntity::NullEntity;
		ImTextAlign(ToImVec4(Colors::Gray), "Game entity is not selected.", eImTextAlignHorizon::Center, eImTextAlignVertical::Center);
	}
}

void EntityInspectorPanel::DrawNamePanel(Name* inName)
{
	static bool sEdit = false;
	enum { BUFFER_SIZE = 64 };
	static char buffer[BUFFER_SIZE] = {};

	ImGui::BulletText("Name");
	if (sEdit)
	{
		ImGui::InputText("##Name", buffer, BUFFER_SIZE);
		ImGui::SameLine();
		if (ImGui::Button("Set"))
		{
			inName->name = buffer;
			sEdit = false;
		}
	}
	else
	{
		ImGui::InputText("##Name", inName->name.data(), inName->name.size(), ImGuiInputTextFlags_ReadOnly);
		ImGui::SameLine();
		if (ImGui::Button("Edit"))
		{
			sEdit = true;
			::strcpy_s(buffer, inName->name.c_str());
		}

	}
}

void EntityInspectorPanel::DrawTransformPanel(Transform* inTransform)
{
	// 조절옵션
	ImGui::Button("Value Speed");
	if (ImPopupItem item = { "Value Speed" , ImGuiPopupFlags_MouseButtonLeft })
	{
		ImGui::TextUnformatted("Position Adj Speed");
		ImGui::DragFloat(
			"##PositionDrag",
			&mConfig.positionDragSpeed,
			0.0001f,
			0.0001f,
			10.f,
			"%.4f"
		);
		ImGui::TextUnformatted("Rotation Adj Speed");
		ImGui::DragFloat(
			"##RotationDrag",
			&mConfig.rotationDragSpeed,
			0.0001f,
			0.0001f,
			10.f,
			"%.4f"
		);

		ImGui::TextUnformatted("Scale Adj Speed");
		ImGui::DragFloat(
			"##ScaleDrag",
			&mConfig.scaleDragSpeed,
			0.0001f,
			0.0001f,
			10.f,
			"%.4f"
		);
	}

	// Position
	{
		ImGui::BulletText("Position");
		ImGui::DragFloat("X##Pos", &inTransform->position.x, mConfig.positionDragSpeed, -10000, 10000, "%.3f");
		ImGui::DragFloat("Y##Pos", &inTransform->position.y, mConfig.positionDragSpeed, -10000, 10000, "%.3f");
		ImGui::DragFloat("Z##Pos", &inTransform->position.z, mConfig.positionDragSpeed, -10000, 10000, "%.3f");

		if (ImGui::Button("Reset##Pos")) { inTransform->position = Vector3::Zero; }
	}

	// Rotation
	{
		ImGui::BulletText("Rotation");

		static float pitch, yaw, roll;
		pitch = Math::RadToDeg(inTransform->rotation.x);
		yaw = Math::RadToDeg(inTransform->rotation.y);
		roll = Math::RadToDeg(inTransform->rotation.z);

		if (ImGui::DragFloat("Pitch##Rot", &pitch, mConfig.rotationDragSpeed, 0.f, 360.f, "%.3f", ImGuiSliderFlags_WrapAround)) { inTransform->rotation.x = Math::DegToRad(pitch); }
		if (ImGui::DragFloat("Yaw##Rot", &yaw, mConfig.rotationDragSpeed, 0.f, 360.f, "%.3f", ImGuiSliderFlags_WrapAround)) { inTransform->rotation.y = Math::DegToRad(yaw); }
		if (ImGui::DragFloat("Roll##Rot", &roll, mConfig.rotationDragSpeed, 0.f, 360.f, "%.3f", ImGuiSliderFlags_WrapAround)) { inTransform->rotation.z = Math::DegToRad(roll); }

		if (ImGui::Button("Reset##Rot")) { inTransform->rotation = Vector3::Zero; }
	}

	// Scale
	{
		ImGui::BulletText("Scale");

		Vector3 previousScaling = inTransform->scaling;
		bool updated = false;

		updated |= ImGui::DragFloat("X##Sc", &inTransform->scaling.x, mConfig.scaleDragSpeed, -10000, 10000, "%.3f");
		updated |= ImGui::DragFloat("Y##Sc", &inTransform->scaling.y, mConfig.scaleDragSpeed, -10000, 10000, "%.3f");
		updated |= ImGui::DragFloat("Z##Sc", &inTransform->scaling.z, mConfig.scaleDragSpeed, -10000, 10000, "%.3f");

		ImGui::Checkbox("Fix Ratio##Trans", &mConfig.scaleFixRatio);
		if (ImGui::Button("Reset##Sc")) { inTransform->scaling = Vector3::One; }

		if (mConfig.scaleFixRatio && updated)
		{
			float scaleFactor = 1.0f;
			if (fabs(previousScaling.x) > Math::SMALL_NUM &&
				fabs(inTransform->scaling.x - previousScaling.x) > fabs(inTransform->scaling.y - previousScaling.y) &&
				fabs(inTransform->scaling.x - previousScaling.x) > fabs(inTransform->scaling.z - previousScaling.z))
			{
				scaleFactor = inTransform->scaling.x / previousScaling.x;
			}
			else if (fabs(previousScaling.y) > Math::SMALL_NUM &&
				fabs(inTransform->scaling.y - previousScaling.y) > fabs(inTransform->scaling.z - previousScaling.z))
			{
				scaleFactor = inTransform->scaling.y / previousScaling.y;
			}
			else if (fabs(previousScaling.z) > Math::SMALL_NUM)
			{
				scaleFactor = inTransform->scaling.z / previousScaling.z;
			}

			if (fabs(scaleFactor) < Math::SMALL_NUM)
			{
				scaleFactor = 1.0f;
			}

			inTransform->scaling.x = previousScaling.x * scaleFactor;
			inTransform->scaling.y = previousScaling.y * scaleFactor;
			inTransform->scaling.z = previousScaling.z * scaleFactor;
		}
	}
}

void EntityInspectorPanel::DrawCameraPanel(Camera* inCamera)
{
	if (ImGui::Button("Main Camera"))
	{
		SCENE_MANAGER.TryGetCurrentScene()->SetSceneCamera(mEntity);
	}

	ImGui::BulletText("Camera Mode");
	static const char* sCameraMode[] = { "Orthographic", "Perspective" };
	int mode = static_cast<int>(inCamera->mode);
	if (ImGui::Combo("##Mode", &mode, sCameraMode, std::size(sCameraMode)))
	{
		inCamera->mode = static_cast<eCameraProjectionMode>(mode);
	}

	ImGui::BulletText("Frustum");
	ImGui::DragFloat("Near Plane", &inCamera->nearPlane, 0.001f, 0.001f, 10000.f);
	ImGui::DragFloat("Far Plane", &inCamera->farPlane, 0.001f, 0.001f, 10000.f);
	inCamera->nearPlane = max(0.001f, inCamera->nearPlane);
	inCamera->farPlane = max(inCamera->nearPlane + 0.001f, inCamera->farPlane);

	ImGui::BulletText(sCameraMode[static_cast<uint32>(inCamera->mode)]);

	if (inCamera->mode == eCameraProjectionMode::Orthographic)
	{
		bool fixRatio = mConfig.cameraFixRatio;
		float aspectRatio = (fixRatio) ? inCamera->width / inCamera->height : 0.0f;

		ImGui::Checkbox("Fix Ratio##Cmr", &mConfig.cameraFixRatio);

		bool updated = false;
		float previousWidth = inCamera->width;
		float previousHeight = inCamera->height;

		updated |= ImGui::DragFloat("Camera Width", &inCamera->width, 0.001f, 0.001f, 100.f);
		updated |= ImGui::DragFloat("Camera Height", &inCamera->height, 0.001f, 0.001f, 100.f);

		if (fixRatio && updated)
		{
			if (fabs(inCamera->width - previousWidth) > fabs(inCamera->height - previousHeight))
			{
				inCamera->height = inCamera->width / aspectRatio;
			}
			else
			{
				inCamera->width = inCamera->height * aspectRatio;
			}
		}
	}

	else if (inCamera->mode == eCameraProjectionMode::Perspective)
	{
		static float fov = 0;
		fov = ::cmEngine::Math::RadToDeg(inCamera->fov);
		if (ImGui::DragFloat("Field of View", &fov, 0.1f, 0.1f, 180.f, "%.3f", ImGuiSliderFlags_AlwaysClamp))
		{
			inCamera->fov = Math::DegToRad(fov);
		}
	}
}

void EntityInspectorPanel::DrawFlipbookRenderPanel(FlipbookRender* inFlipbookRender)
{
	ImGui::Button("Load Flipbook");
	ImItemTooltip("Drop here");

	if (ImDragDropTarget target = {})
	{
		if (const auto* data = ImGui::AcceptDragDropPayload(ImPayload::GetResourcePayload(eResourceType::Flipbook)))
		{
			const char* name = static_cast<const char*>(data->Data);
			inFlipbookRender->flipbook = RESOURCE_MANAGER.TryFindResource<Flipbook>(name);
		}
	}

	if (inFlipbookRender->flipbook)
	{
		const FlipbookData& fbData = inFlipbookRender->flipbook->GetFlipbookData();

		ImGui::BulletText("Resource Data");
		ImGui::Text(std::format(
			"Flipbook Name : {}\n"
			"Source Texture : {}\n"
			"Width : {}\n"
			"Height : {}\n"
			"Pivot Row : {}\n"
			"Pivot Col : {}\n"
			"Total Frame : {}\n"
			"Flip Speed : {} sec\n"
			"Loop : {}",
			inFlipbookRender->flipbook->GetName(),
			fbData.texture->GetName(),
			fbData.width,
			fbData.height,
			fbData.pivotRow,
			fbData.pivotCol,
			fbData.frameCount,
			fbData.frameDuration,
			fbData.loop ? "On" : "Off"
		).c_str());

		ImGui::Spacing();
		ImGui::BulletText("Component Data");

		ImGui::Text("Current Frame : %d", inFlipbookRender->curFrame);
		if (ImGui::Button("Prev"))
		{
			inFlipbookRender->play = false;
			inFlipbookRender->curFrame = (inFlipbookRender->curFrame - 1 + fbData.frameCount) % fbData.frameCount;
		}
		ImGui::SameLine();
		if (ImGui::Button("Next"))
		{
			inFlipbookRender->play = false;
			inFlipbookRender->curFrame = (inFlipbookRender->curFrame + 1) % fbData.frameCount;
		}
		static float step = 0.01f;
		ImGui::TextUnformatted("Playback Speed");
		ImGui::InputScalar("##Playback Speed", ImGuiDataType_Float, (void*)&inFlipbookRender->playbackSpeed, (void*)&step, NULL);
		ImGui::Text(std::format(
			"Finish : {}\n"
			"Play : {}",
			inFlipbookRender->finish ? "Yes" : "No",
			inFlipbookRender->play ? "Yes" : "No"
		).c_str());

		if (ImGui::Button("Reset"))
		{
			inFlipbookRender->finish = false;
			inFlipbookRender->curFrame = 0;
		}
		ImGui::SameLine();
		if (ImGui::Button(inFlipbookRender->play ? "Stop" : "Play"))
		{
			inFlipbookRender->play = !inFlipbookRender->play;
		}
	}
}

void EntityInspectorPanel::DrawSpriteRenderPanel(SpriteRender* inSpriteRender)
{

	ImGui::Button("Load Sprite");
	ImItemTooltip("Drag here");

	if(ImDragDropTarget target = {})
	{
		if (const auto* data = ImGui::AcceptDragDropPayload(ImPayload::GetResourcePayload(eResourceType::Sprite)))
		{
			const char* name = static_cast<const char*>(data->Data);
			inSpriteRender->sprite = RESOURCE_MANAGER.TryFindResource<Sprite>(name);
		}
	}

	if (inSpriteRender->sprite)
	{
		const SpriteData& spd = inSpriteRender->sprite->GetSpriteData();
		ImGui::Text(std::format(
			"Sprite Name : {}\n"
			"Source Texture : {}\n"
			"Width : {}\n"
			"Height : {}\n"
			"Pivot Row : {}\n"
			"Pivot Col : {}",
			inSpriteRender->sprite->GetName(),
			spd.texture->GetName(),
			spd.width,
			spd.height,
			spd.pivotCol,
			spd.pivotRow
		).c_str());
	}
}

void EntityInspectorPanel::DrawRenderProfilePanel(RenderProfile* inRenderProfile)
{
	ImGui::BulletText("Shader set");

	ImGui::Button("Load Shader set");
	ImItemTooltip("Drag here");

	if(ImDragDropTarget target = {})
	{
		if (const auto* data = ImGui::AcceptDragDropPayload(ImPayload::GetResourcePayload(eResourceType::ShaderSet)))
		{
			const char* name = static_cast<const char*>(data->Data);
			inRenderProfile->shaders = RESOURCE_MANAGER.TryFindResource<ShaderSet>(name);
		}
	}

	if (inRenderProfile->shaders)
	{
		ImGui::Text("Shader Name : %s", inRenderProfile->shaders->GetName());
	}

	ImGui::Spacing();
	ImGui::BulletText("Render State");

	RenderState& state = inRenderProfile->renderState;

	ImGui::Combo("Blend State", (int*)&state.blendState, RenderStatePool::sBlendStateString.data(), RenderStatePool::sBlendStateString.size());
	ImGui::Combo("Sampler State", (int*)&state.samplerState, RenderStatePool::sSamplerStateString.data(), RenderStatePool::sSamplerStateString.size());
	ImGui::Combo("Depth Stencil State", (int*)&state.depthStencilState, RenderStatePool::sDepthStencilStateString.data(), RenderStatePool::sDepthStencilStateString.size());
	ImGui::Combo("Rasterizer State", (int*)&state.rasterizerState, RenderStatePool::sRasterizerStateString.data(), RenderStatePool::sRasterizerStateString.size());
}

void EntityInspectorPanel::DrawCreateComponentMenu()
{
	if (!mEntity.IsNull())
	{
		if (!mEntity.HasComponent<Name>()) { if (ImGui::MenuItem("Name")) { mEntity.TryCreateComponent<Name>(); } }
		if (!mEntity.HasComponent<Transform>()) { if (ImGui::MenuItem("Transform")) { mEntity.TryCreateComponent<Transform>(); } }
		if (!mEntity.HasComponent<Camera>()) { if (ImGui::MenuItem("Camera")) { mEntity.TryCreateComponent<Camera>(); } }
		if (!mEntity.HasComponent<SpriteRender>()) { if (ImGui::MenuItem("SpriteRender")) { mEntity.TryCreateComponent<SpriteRender>(); } }
		if (!mEntity.HasComponent<FlipbookRender>()) { if (ImGui::MenuItem("FlipbookRender")) { mEntity.TryCreateComponent<FlipbookRender>(); } }
		if (!mEntity.HasComponent<RenderProfile>()) { if (ImGui::MenuItem("RenderProfile")) { mEntity.TryCreateComponent<RenderProfile>(); } }
	}
}

void EntityInspectorPanel::DrawRemoveComponentMenu()
{
	if (!mEntity.IsNull())
	{
		if (mEntity.HasComponent<Name>()) { if (ImGui::MenuItem("Name")) { mEntity.TryRemoveComponent<Name>(); } }
		if (mEntity.HasComponent<Transform>()) { if (ImGui::MenuItem("Transform")) { mEntity.TryRemoveComponent<Transform>(); } }
		if (mEntity.HasComponent<Camera>()) { if (ImGui::MenuItem("Camera")) { mEntity.TryRemoveComponent<Camera>(); } }
		if (mEntity.HasComponent<SpriteRender>()) { if (ImGui::MenuItem("SpriteRender")) { mEntity.TryRemoveComponent<SpriteRender>(); } }
		if (mEntity.HasComponent<FlipbookRender>()) { if (ImGui::MenuItem("FlipbookRender")) { mEntity.TryRemoveComponent<FlipbookRender>(); } }
		if (mEntity.HasComponent<RenderProfile>()) { if (ImGui::MenuItem("RenderProfile")) { mEntity.TryRemoveComponent<RenderProfile>(); } }
	}
}

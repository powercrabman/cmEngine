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
	ImGui::Begin("EntityInspectorPanel");

	mEntity = EDITOR_CORE.TryGetEditEntity();

	if (mEntity.IsValid())
	{
		DrawDefaultPanel();
		PanelLayout<Name>(&EntityInspectorPanel::DrawNamePanel);
		PanelLayout<Transform>(&EntityInspectorPanel::DrawTransformPanel);
		PanelLayout<Camera>(&EntityInspectorPanel::DrawCameraPanel);
		PanelLayout<FlipbookRender>(&EntityInspectorPanel::DrawFlipbookRenderPanel);
		PanelLayout<SpriteRender>(&EntityInspectorPanel::DrawSpriteRenderPanel);
	}
	else
	{
		mEntity = GameEntity::NullEntity;
		ImTextAlign(ToImVec4(Colors::Gray), "Game entity is not selected.",eImTextAlignHorizon::Center, eImTextAlignVertical::Center);
	}

	ImGui::End();
}

void EntityInspectorPanel::DrawDefaultPanel()
{
	Name* name = mEntity.TryFindComponent<Name>();
	ImGui::Text("Entity ID : %d", mEntity.GetID());

	ImGui::Separator();
	if (ImGui::Button("Create Component")) { ImGui::OpenPopup("CreateComp"); }
	ImGui::SameLine();
	if (ImGui::Button("Delete Component")) { ImGui::OpenPopup("DeleteComp"); }

	if (ImGui::BeginPopup("CreateComp"))
	{
		CreateComponentMenuItem<Name>("Name");
		CreateComponentMenuItem<Transform>("Transform");
		CreateComponentMenuItem<Camera>("Camera");
		CreateComponentMenuItem<FlipbookRender>("FlipbookRender");
		CreateComponentMenuItem<SpriteRender>("SpriteRender");
		CreateComponentMenuItem<RenderProfile>("RenderProfile");

		ImGui::EndPopup();
	}

	if (ImGui::BeginPopup("DeleteComp"))
	{
		DeleteComponentMenuItem<Name>("Name");
		DeleteComponentMenuItem<Transform>("Transform");
		DeleteComponentMenuItem<Camera>("Camera");
		DeleteComponentMenuItem<FlipbookRender>("FlipbookRender");
		DeleteComponentMenuItem<SpriteRender>("SpriteRender");
		DeleteComponentMenuItem<RenderProfile>("RenderProfile");

		ImGui::EndPopup();
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
	if (ImGui::Button("Value Speed")) { ImGui::OpenPopup("Value Speed"); }
	if (ImGui::BeginPopup("Value Speed"))
	{
		ImGui::TextUnformatted("Position Adj Speed");
		ImGui::DragFloat(
			"##PositionDrag",
			&mConfig.PositionDragSpeed,
			0.0001f,
			0.0001f,
			10.f,
			"%.4f"
		);
		ImGui::TextUnformatted("Rotation Adj Speed");
		ImGui::DragFloat(
			"##RotationDrag",
			&mConfig.RotateDragSpeed,
			0.0001f,
			0.0001f,
			10.f,
			"%.4f"
		);

		ImGui::TextUnformatted("Scale Adj Speed");
		ImGui::DragFloat(
			"##ScaleDrag",
			&mConfig.ScaleDragSpeed,
			0.0001f,
			0.0001f,
			10.f,
			"%.4f"
		);
		ImGui::EndPopup();
	}

	// Position
	{
		ImGui::BulletText("Position");
		ImGui::DragFloat("X##Pos", &inTransform->position.x, mConfig.PositionDragSpeed, -10000, 10000, "%.3f");
		ImGui::DragFloat("Y##Pos", &inTransform->position.y, mConfig.PositionDragSpeed, -10000, 10000, "%.3f");
		ImGui::DragFloat("Z##Pos", &inTransform->position.z, mConfig.PositionDragSpeed, -10000, 10000, "%.3f");

		if (ImGui::Button("Reset##Pos")) { inTransform->position = Vector3::Zero; }
	}

	// Rotation
	{
		ImGui::BulletText("Rotation");

		static float pitch, yaw, roll;
		pitch = Math::RadToDeg(inTransform->rotation.x);
		yaw = Math::RadToDeg(inTransform->rotation.y);
		roll = Math::RadToDeg(inTransform->rotation.z);

		if (ImGui::DragFloat("Pitch##Rot", &pitch, mConfig.RotateDragSpeed, 0.f, 360.f, "%.3f", ImGuiSliderFlags_WrapAround)) { inTransform->rotation.x = Math::DegToRad(pitch); }
		if (ImGui::DragFloat("Yaw##Rot", &yaw, mConfig.RotateDragSpeed, 0.f, 360.f, "%.3f", ImGuiSliderFlags_WrapAround)) { inTransform->rotation.y = Math::DegToRad(yaw); }
		if (ImGui::DragFloat("Roll##Rot", &roll, mConfig.RotateDragSpeed, 0.f, 360.f, "%.3f", ImGuiSliderFlags_WrapAround)) { inTransform->rotation.z = Math::DegToRad(roll); }

		if (ImGui::Button("Reset##Rot")) { inTransform->rotation = Vector3::Zero; }
	}

	// Scale
	{
		ImGui::BulletText("Scale");

		Vector3 previousScaling = inTransform->scaling;
		bool updated = false;

		updated |= ImGui::DragFloat("X##Sc", &inTransform->scaling.x, mConfig.ScaleDragSpeed, -10000, 10000, "%.3f");
		updated |= ImGui::DragFloat("Y##Sc", &inTransform->scaling.y, mConfig.ScaleDragSpeed, -10000, 10000, "%.3f");
		updated |= ImGui::DragFloat("Z##Sc", &inTransform->scaling.z, mConfig.ScaleDragSpeed, -10000, 10000, "%.3f");

		ImGui::Checkbox("Fix Ratio#Trans", &mConfig.ScaleFixRatio);
		if (ImGui::Button("Reset##Sc")) { inTransform->scaling = Vector3::One; }

		if (mConfig.ScaleFixRatio && updated)
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
		bool fixRatio = mConfig.CameraFixRatio;
		float aspectRatio = (fixRatio) ? inCamera->width / inCamera->height : 0.0f;

		ImGui::Checkbox("Fix Ratio#Cmr", &mConfig.CameraFixRatio);

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
	if (ImGui::BeginItemTooltip())
	{
		ImGui::TextUnformatted("Drop here");
		ImGui::EndTooltip();
	}

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
	if (ImGui::Button(inFlipbookRender->play ?"Stop" : "Play"))
	{
		inFlipbookRender->play = !inFlipbookRender->play;
	}
}

void EntityInspectorPanel::DrawSpriteRenderPanel(SpriteRender* inSpriteRender)
{
	ImGui::Button("Load Sprite");
	if (ImGui::BeginItemTooltip())
	{
		ImGui::TextUnformatted("Drop here");
		ImGui::EndTooltip();
	}

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
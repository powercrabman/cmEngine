#pragma once

struct EntityInspectorPanelJson
{
	bool visible = false;

	// Transform
	float PositionDragSpeed = 0.1f;
	float RotateDragSpeed = 0.1f;
	float ScaleDragSpeed = 0.1;
	bool ScaleFixRatio = false;

	// Camera
	bool CameraFixRatio = false;

	JSON_STRUCT_BODY(
		EntityInspectorPanelJson,
		visible,
		PositionDragSpeed, RotateDragSpeed, ScaleDragSpeed,
		CameraFixRatio
	);
};

class EntityInspectorPanel : public Gui
{
public:
	EntityInspectorPanel();
	~EntityInspectorPanel() override;
	void RenderGui() override;

	void DrawDefaultPanel();
	void DrawNamePanel(Name* inName);
	void DrawTransformPanel(Transform* inTransform);
	void DrawCameraPanel(Camera* inCamera);
	void DrawFlipbookRenderPanel(FlipbookRender* inFlipbookRender);
	void DrawSpriteRenderPanel(SpriteRender* inSpriteRender);

	template <typename CompType, typename Callback>
	void PanelLayout(Callback callback)
	{
		CompType* comp = mEntity.TryFindComponent<CompType>();
		if (comp)
		{
			if (ImGui::CollapsingHeader(CompType::sComponentName, ImGuiTreeNodeFlags_DefaultOpen))
			{
				(this->*callback)(comp);
			}
		}
	}

	template <typename Ty>
	void CreateComponentMenuItem(std::string_view str)
	{
		if (ImGui::Selectable(str.data()))
		{
			if (!mEntity.IsNull())
			{
				mEntity.TryCreateComponent<Ty>();
			}
		}
	}

	template <typename Ty>
	void DeleteComponentMenuItem(std::string_view str)
	{
		if (ImGui::Selectable(str.data()))
		{
			if (!mEntity.IsNull())
			{
				mEntity.TryRemoveComponent<Ty>();
			}
		}
	}

	TO_STRING(EntityInspectorPanel);

private:
	EntityInspectorPanelJson mConfig = {};
	GameEntity mEntity               = GameEntity::NullEntity;
};


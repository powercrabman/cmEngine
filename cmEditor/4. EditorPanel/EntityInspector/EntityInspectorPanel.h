#pragma once

struct EntityInspectorPanelJson
{
	bool visible = false;

	// Transform
	float positionDragSpeed = 0.1f;
	float rotationDragSpeed = 0.1f;
	float scaleDragSpeed = 0.1f;
	bool scaleFixRatio = false;

	// Camera
	bool cameraFixRatio = false;

	JSON_STRUCT_BODY(
		EntityInspectorPanelJson,
		visible,
		positionDragSpeed, rotationDragSpeed, scaleDragSpeed,
		scaleFixRatio,
		cameraFixRatio
	);
};

class EntityInspectorPanel : public Gui
{
public:
	EntityInspectorPanel();
	~EntityInspectorPanel() override;
	void RenderGui() override;

private:
	void DrawNamePanel(Name* name);
	void DrawTransformPanel(Transform* transform);
	void DrawCameraPanel(Camera* camera);
	void DrawFlipbookRenderPanel(FlipbookRender* flipbookRender);
	void DrawSpriteRenderPanel(SpriteRender* spriteRender);
	void DrawRenderProfilePanel(RenderProfile* inRenderProfile);

	template <typename ComponentType>
	void DrawComponentPanel(const char* panelName, void (EntityInspectorPanel::* drawFunc)(ComponentType*));

	void DrawCreateComponentMenu();
	void DrawRemoveComponentMenu();

	TO_STRING(EntityInspectorPanel);

private:
	EntityInspectorPanelJson mConfig = {};
	GameEntity mEntity = GameEntity::NullEntity;
};

template <typename ComponentType>
void EntityInspectorPanel::DrawComponentPanel(const char* panelName, void (EntityInspectorPanel::* drawFunc)(ComponentType*))
{
	if (ComponentType* component = mEntity.TryFindComponent<ComponentType>())
	{
		if (ImGui::CollapsingHeader(panelName, ImGuiTreeNodeFlags_DefaultOpen))
		{
			(this->*drawFunc)(component);
		}
	}
}

#pragma once

struct SceneHierarchyPanelJson
{
	bool visible;

	JSON_STRUCT_BODY(SceneHierarchyPanelJson, visible);
};

class SceneHierarchyPanel : public Gui
{
public:
	SceneHierarchyPanel();
	~SceneHierarchyPanel() override;

	void RenderGui() override;
	void HandleCreateScenePopup();
	void HandleDeleteScenePopup();
	void DrawSceneHierarchy() const;

	void HandleSceneSerialize();
	void HandleSceneDeserialize();

	TO_STRING(SceneHierarchyPanel);
private:
	SceneHierarchyPanelJson		mConfig = {};
	ImModalOK					mModal{"Alert"};
	ImModalYesOrNo				mModalYN{"YesOrNo"};
};


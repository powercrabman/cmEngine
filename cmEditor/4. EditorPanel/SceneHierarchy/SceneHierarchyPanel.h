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
	void DrawSceneSelector() const;

	void HandleSceneSerialize();
	void HandleSceneDeserialize();

	TO_STRING(SceneHierarchyPanel);
private:
	SceneHierarchyPanelJson		mConfig   = {};

	std::string					mAlertMsg = {};
	inline static const const char*	const mSignal = "Alert";
};


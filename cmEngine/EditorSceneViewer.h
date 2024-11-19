#pragma once

namespace cmEngine
{
	struct EditorScecneViwerConfig : public JsonMetaData
	{
		bool visible        = false;
		bool entityEditView = false;

		JSON_STRUCT_BODY(
			EditorScecneViwerConfig,
			L"EditorConfig.json",
			visible,
			entityEditView
		);
	};

	//===================================================
	
	class EditorSceneViewer : public Gui
	{
	public:
		EditorSceneViewer();
		~EditorSceneViewer() override;

		void RenderGui() override;

		void DrawEntityEditor();

	private:
		EditorScecneViwerConfig mConfig       = {};
		GameEntity				mTargetEntity = GameEntity::NullEntity;
	};
}

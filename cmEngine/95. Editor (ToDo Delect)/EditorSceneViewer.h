#pragma once

namespace cmEngine
{
	struct EditorScecneViwerConfig : public JsonStructBase
	{
		bool visible        = false;
		bool entityEditView = false;

		JSON_STRUCT_BODY(
			EditorScecneViwerConfig,
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
		EditorScecneViwerConfig mConfig          = {};
		GameEntity				mTargetEntity    = GameEntity::NullEntity;
		bool					mEntityEditorBit = false;
	};
}

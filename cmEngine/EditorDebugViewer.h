#pragma once

namespace cmEngine
{
	struct EngineDebugViwerConfig : public JsonMetaData
	{
		bool visible;

		JSON_STRUCT_BODY(
			EngineDebugViwerConfig,
			L"EditorConfig.json",
			visible
		);
	};


	//===================================================

	class EditorDebugViewer : public Gui
	{
	public:
		EditorDebugViewer();
		~EditorDebugViewer() override;

		void RenderGui() override;

		void DrawPerformenceView();
		void DrawInputView();
	private:
		EngineDebugViwerConfig	mConfig     = {};
	};

	
}

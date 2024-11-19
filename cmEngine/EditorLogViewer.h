#pragma once

namespace cmEngine
{
	struct EngineLogViewerConfig : public JsonMetaData
		{
			bool visible;
			bool autoScrollBit;

			JSON_STRUCT_BODY(
				EngineLogViewerConfig,
				L"EditorConfig.json",
				visible,
				autoScrollBit
		);
	};

	//===================================================

	class EditorLogViewer : public Gui
	{
	public:
		EditorLogViewer();
		~EditorLogViewer() override;

		void RenderGui() override;

	private:
		EngineLogViewerConfig	mConfig  = {};
		size_t					mLogSize = 0;
	};

	
}

#pragma once

namespace cmEngine
{
	struct EngineLogViewerConfig : public JsonMetaData
		{
			bool visible;
			bool autoScrollBit;

			std::array<ImVec4, static_cast<uint32>(eLogLevel::Count)> textColor =
			{
				ImVec4{1.f,1.f,1.f,1.f},	// Trace
				ImVec4{1.f,1.f,1.f,1.f},	// Debug
				ImVec4{1.f,1.f,1.f,1.f},	// Info
				ImVec4{1.f,1.f,1.f,1.f},	// Warn
				ImVec4{1.f,1.f,1.f,1.f},	// Error
				ImVec4{1.f,1.f,1.f,1.f},	// Fatal
			};

			JSON_STRUCT_BODY(
				EngineLogViewerConfig,
				visible,
				autoScrollBit,
				textColor
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
		uint32					mPrevLogSize = {};
	};

	
}

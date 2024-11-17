#pragma once
#include "GuiFrame.h"

namespace cmEngine
{
	struct EngineDebugViwerConfig : public ConfigBase
	{
		bool Visible;
		bool OverlayBit;
		CONFIG_BODY(
			EngineDebugViwerConfig, 
			L"SystemConfig.json", 
			Visible,
			OverlayBit
		);
	};

	class EngineDebugViewer : public GuiFrame
	{
	public:
		EngineDebugViewer() { ConfigEngine::Load(mConfig); }
		virtual ~EngineDebugViewer();

		void Initialize() override;
		void GuiLayout() override;

		void DrawPerformenceView();
		void DrawInputView();

	private:
		EngineDebugViwerConfig mConfig = {};
	};
}

#pragma once
#include "GuiFrame.h"
#include "ConfigSystem.h"

namespace cmEngine
{
	struct EngineDebugViwerConfig : public ConfigBase
	{
		bool OverlayBit = false;
		CONFIG_BODY(EngineDebugViwerConfig, L"SystemConfig.json", OverlayBit);
	};

	class EngineDebugViewer : public GuiFrame
	{
	public:
		EngineDebugViewer() {}
		virtual ~EngineDebugViewer();

		void Initialize() override;
		void GuiLayout() override;

		void DrawPerformenceView();
		void DrawInputView();

	private:
	};
}

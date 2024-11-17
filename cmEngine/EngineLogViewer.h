#pragma once
#include "GuiFrame.h"

namespace cmEngine
{
	struct EngineLogViewerConfig : public ConfigBase
	{
		bool Visible;
		bool AutoScrollBit;
		CONFIG_BODY(
			EngineLogViewerConfig, 
			L"SystemConfig.json", 
			Visible,
			AutoScrollBit
		);
	};

	class EngineLogViewer : public GuiFrame
	{
	public:
		EngineLogViewer() { ConfigEngine::Load(mConfig); }
		virtual ~EngineLogViewer() 
		{
			EngineLogViewerConfig cf = {};
			cf.Visible = GetGui()->GetVisible();
			ConfigEngine::Save(cf);
		}

		void Initialize() override;
		void GuiLayout() override;

	private:
		EngineLogViewerConfig	mConfig = {};
		size_t					mLogSize = 0;
	};
}


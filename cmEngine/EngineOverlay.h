#pragma once
#include "GuiFrame.h"

namespace cmEngine
{
	struct EngineOverlayConfig : public ConfigBase
	{
		float	Transparency  = 0.5f;
		bool	NoMoveBit     = false;
		bool	FrameViewBit  = true;
		bool	MemoryViewBit = true;
		bool	Visible       = true;

		CONFIG_BODY(
			EngineOverlayConfig,
			L"SystemConfig.json",
			Transparency,
			NoMoveBit,
			FrameViewBit,
			MemoryViewBit,
			Visible
		);
	};

	class EngineOverlay : public GuiFrame
	{
	public:
		EngineOverlay() { ConfigEngine::Load(mConfig); }
		virtual ~EngineOverlay()
		{
			EngineOverlayConfig cf = {};
			cf.Visible = GetGui()->GetVisible();
			ConfigEngine::Save(cf);
		}

		void Initialize() override;
		void GuiLayout() override;

	private:
		EngineOverlayConfig mConfig = {};
	};
}

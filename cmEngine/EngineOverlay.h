#pragma once
#include "GuiFrame.h"

namespace cmEngine
{
	class EngineOverlay : public GuiFrame
	{
	public:
		void Initialize() override;
		void GuiLayout() override;

	private:
		float	mTransparency = 0.5f;
		bool	mNoMoveBit = false;
	};
}

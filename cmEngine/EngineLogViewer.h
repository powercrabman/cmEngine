#pragma once
#include "GuiFrame.h"

namespace cmEngine
{
	class EngineLogViewer : public GuiFrame
	{
	public:
		void Initialize() override;
		void GuiLayout() override;

	private:
		bool	mAutoScrollBit = true;
		size_t	mLogSize = 0;
	};
}


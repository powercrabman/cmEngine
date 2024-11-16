#pragma once
#include "GuiFrame.h"

namespace cmEngine
{
	class EngineVoidPopup : public GuiFrame
	{
	public:
		EngineVoidPopup() {}
		~EngineVoidPopup() {}

		void Initialize() override;
		void GuiLayout() override;

		void DrawClearColor();

	private:
		bool mClearColorBit = false;
	};
}

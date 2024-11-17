#pragma once
#include "GuiFrame.h"
#include "ConfigBase.h"

namespace cmEngine
{
	class EngineVoidPopup : public GuiFrame
	{
	public:
		EngineVoidPopup();
		~EngineVoidPopup();

		void Initialize() override;
		void GuiLayout() override;

		void DrawClearColor();

	private:
		bool mClearColorBit = false;

		Gui* logView = nullptr;
		Gui* debugView = nullptr;
		Gui* sceneView = nullptr;
	};
}

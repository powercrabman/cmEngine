#pragma once

namespace cmEngine
{
	class Gui;

	class GuiFrame
	{
		friend class GuiRenderer;
	public:
		GuiFrame() = default;
		virtual ~GuiFrame() = default;

		virtual void Initialize() abstract;
		virtual void GuiLayout() abstract;

		const char* GetName() const { return mName.c_str(); }
		Gui*		GetGui() const { return mGui; }
		bool*		GetGuiVisibleAddr() { return mGui->GetVisibleAddr(); }

	private:
		void		SetGui(Gui* inGui) { mGui = inGui; }
		void		SetName(std::string_view inName) { mName = inName; }

		std::string mName = {};
		Gui*		mGui  = nullptr;
	};
}

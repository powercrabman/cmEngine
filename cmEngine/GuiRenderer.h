#pragma once

class Gui;

namespace cmEngine
{
	class GuiRenderer
	{
	public:
		static Gui* CreateGui(std::string_view inGuiName);
		static Gui* FindOrNull(std::string_view inGuiName);
		static bool RemoveGui(std::string_view inGuiName);

		static void Render();
	
	private:
		static void Initialize();
		static void Destroy();

	private:
		static std::unordered_map<std::string, std::unique_ptr<Gui>>	mGuiRepo;
		static BatchSystem<Gui>											mGuiBatch;
	};
}


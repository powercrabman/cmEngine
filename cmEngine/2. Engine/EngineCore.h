#pragma once
#include "10. Scene/SceneManager.h"
#include "7. Gui/GuiRenderer.h"

namespace cmEngine
{
	class EngineCore
	{
		friend class Application;
		SINGLETON(EngineCore);
	public:
		void CloseGame() { mRunning = false; }
		bool IsRunning() const { return mRunning; }
		
	private:
		EngineCore() = default;
		~EngineCore() = default;

		void	Init(const ApplicationProp& inWindowProp);
		int		Run() const;

		bool mRunning = false;
	};
}

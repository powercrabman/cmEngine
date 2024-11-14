#pragma once
#include "Component.h"


namespace cmEngine
{
	class GuiComponent : public Component
	{
	public:
		COMPONENT_BODY(GuiComponent);

		GuiComponent(const std::function<void()>& inCallback);
		virtual ~GuiComponent() = default;

		void OnStart() override;
		void OnFinish() override;

		void SetLayoutCallback(const std::function<void()>& inCallback)
		{
			mLayoutCallback = inCallback;
		}

		Gui* GetGUI()  const { return mGui; }

	private:
		Gui* mGui = nullptr;
		std::function<void()> mLayoutCallback = nullptr;
	};
}
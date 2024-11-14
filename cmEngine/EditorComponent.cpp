#include "EnginePch.h"
#include "EditorComponent.h"

namespace cmEngine
{
	GuiComponent::GuiComponent(const std::function<void()>& inCallback)
		: mLayoutCallback(inCallback)
	{
	}

	void GuiComponent::OnStart()
	{
		GuiRenderer::CreateGui(std::to_string(GetComponentID()));

		if (mLayoutCallback)
		{
			mGui->SetLayoutCallback(mLayoutCallback);
		}
		else
		{
			ASSERT(false, "GUI Layout Callback is nullptr!");
			LOG_ERROR("GUI Layout Callback is nullptr");
		}
	}

	void GuiComponent::OnFinish()
	{
		GuiRenderer::RemoveGui(std::to_string(GetComponentID()));
		mGui = nullptr;
	}
}

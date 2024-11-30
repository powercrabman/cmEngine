#include "EnginePch.h"
#include "Gui.h"

namespace cmEngine
{
	void Gui::RenderGui()
	{
		if (mLayoutCallback)
		{
			mLayoutCallback();
		}
	}
}


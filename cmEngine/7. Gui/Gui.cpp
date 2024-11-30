#include "0. cmEngine/cmEngine.h"
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


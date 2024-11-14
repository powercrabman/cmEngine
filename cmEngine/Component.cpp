#include "EnginePch.h"
#include "Component.h"

namespace cmEngine
{
	Component::Component()
	{
		mComponentID = sComponentIDCounter++;
	}

	Component::~Component() {}

}

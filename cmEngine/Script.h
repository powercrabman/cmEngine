#pragma once
#include "Component.h"
#include "IUpdateable.h"
#include "IFinalUpdateable.h"
#include "ISetupable.h"

namespace cmEngine
{
	class Script
		: public		Component
		, IMPLEMENTS	IUpdateable
		, IMPLEMENTS	IFinalUpdateable
		, IMPLEMENTS	ISetupable
	{
	public:
		COMPONENT_BODY(Script);

		Script() = default;
		virtual ~Script() = default;
	};
}


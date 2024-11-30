#pragma once
#include "Factory/ComponentSerializer.h"

namespace cmEngine
{
	//===================================================
	//			            Name
	//===================================================

	struct Name
	{
		bool operator==(const Name& other) const
		{
			return name == other.name;
		}

		std::string name = "Undefined";

		SERIALIZABLE_COMPONENT_BODY(Name, name);
	};
}

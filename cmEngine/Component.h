#pragma once

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

		std::string name;
	};
}


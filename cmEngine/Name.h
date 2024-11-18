#pragma once

namespace cmEngine
{
	struct Name
	{
		bool operator==(const Name& other)
		{
			return name == other.name;
		}

		std::string name;
	};
}
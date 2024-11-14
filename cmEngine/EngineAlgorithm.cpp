#include "EnginePch.h"
#include "EngineAlgorithm.h"

namespace cmEngine
{
	namespace
	{
		 std::wstring_convert<std::codecvt_utf8<wchar_t>> wstringConv;
	}

	std::string String::ConvertToString(std::wstring_view inString)
	{
		return wstringConv.to_bytes(inString.data());
	}

	std::wstring String::ConvertToWString(std::string_view inString)
	{
		return wstringConv.from_bytes(inString.data());
	}
}


#include "EnginePch.h"
#include "ResourceManager.h"

namespace cmEngine
{
	void ResourceManager::Initialize()
	{
		mClientResourcePath = std::filesystem::current_path() / "Resources\\";
		mCommonResourcePath = std::filesystem::current_path().parent_path() / "CommonResource\\";
		LOG_INFO("Resource Manager Initialize Done.");
	}

	std::wstring ResourceManager::GetClientResourcePath(std::wstring_view inPath) 
	{
		std::wstring retVal = {};
		retVal = mClientResourcePath.wstring() + std::wstring(inPath);
		return retVal;
	}

	std::wstring ResourceManager::GetCommonResourcePath(std::wstring_view inPath) 
	{
		std::wstring retVal = {};
		retVal = mCommonResourcePath.wstring() + std::wstring(inPath);
		return retVal;
	}
}

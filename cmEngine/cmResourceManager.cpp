#include "pch.h"
#include "cmResourceManager.h"

cmResourceManager::cmResourceManager() {}

void cmResourceManager::Initialize()
{
	mClientResourcePath = std::filesystem::current_path() / "Resources\\";
	mCommonResourcePath = std::filesystem::current_path().parent_path() / "CommonResource\\";
	LOG_INFO("Resource Manager Initialize Done.");
}

 std::wstring cmResourceManager::GetClientResourcePath(std::wstring_view inPath) const
{
	std::wstring retVal = {};
	retVal = mClientResourcePath.wstring() + std::wstring(inPath);
	return retVal;
}

 std::wstring cmResourceManager::GetCommonResourcePath(std::wstring_view inPath) const
{
	std::wstring retVal = {};
	retVal = mCommonResourcePath.wstring() + std::wstring(inPath);
	return retVal;
}


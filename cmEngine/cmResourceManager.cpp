#include "pch.h"
#include "cmResourceManager.h"

cmResourceManager::cmResourceManager() {}

void cmResourceManager::Initialize()
{
	mClientResourcePath = std::filesystem::current_path() / "Resources\\";
	mCommonResourcePath = std::filesystem::current_path().parent_path() / "CommonResource\\";
	LOG_INFO("Resource Manager Initialize Done.");
}


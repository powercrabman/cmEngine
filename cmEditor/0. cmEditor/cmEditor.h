#pragma once
#include "0. cmEngine/cmEngine.h"
#pragma comment(lib, "cmEngine/Debug/cmEngine.lib")
using namespace cmEngine;

#include "6. EditorResource/EditorResourceManager.h"
#include "2. Editor/EditorCore.h"
#include "1. EditorApp/EditorAppConfig.h"
#include "5. GuiHelper/ImHelper.h"


#define EDITOR_CORE EditorCore::Ref()
#define EDITOR_RESOURCE_MANAGER EditorResourceManager::Ref()
#include "pch.h"
#include "cmGUI.h"
#include "cmRenderer.h"
#include "cmGUIRenderer.h"

cmGUI::cmGUI() = default;
cmGUI::~cmGUI() = default;

void cmGUI::KeyHandler()
{
	//����Ű
	if (mUseHotKey && ImGui::IsKeyPressed(mHotKey))
	{
		ToggleVisible();
	}
}

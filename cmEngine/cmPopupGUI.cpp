#include "pch.h"
#include "cmPopupGUI.h"
#include "cmLoggerGUI.h"
#include "cmDebugGUI.h"
#include "cmConsoleGUI.h"

void cmPopupGUI::Initialize()
{
	mLog = Engine->GetRenderer()->GetGUIRenderer()->FindGUIOrNull<cmLoggerGUI>();
	mDebug = Engine->GetRenderer()->GetGUIRenderer()->FindGUIOrNull<cmDebugGUI>();
	mConsole = Engine->GetRenderer()->GetGUIRenderer()->FindGUIOrNull<cmConsoleGUI>();

	ASSERT(mLog, "nullptr error");
	ASSERT(mDebug, "nullptr error");
	ASSERT(mConsole, "nullptr error");
}

void cmPopupGUI::RenderGUI()
{
	// View
	if (ImGui::BeginPopupContextVoid())
	{
		if (ImGui::Button("TestButton"))
		{
			// 테스트용 코드
		}

		if (ImGui::BeginMenu("View"))
		{
			ImGui::MenuItem("Console", mConsole->GetHotKeyToString(), mConsole->GetVisiblePtr());
			ImGui::MenuItem("Log", mLog->GetHotKeyToString(), mLog->GetVisiblePtr());
			ImGui::MenuItem("Debug", mDebug->GetHotKeyToString(), mDebug->GetVisiblePtr());

			ImGui::EndMenu();
		}

		ImGui::Separator();
			if (ImGui::Selectable("Close Game")) { Engine->CloseGame(); }

		ImGui::EndPopup();
	}
}

#include "pch.h"
#include "cmConsoleGUI.h"
#include "cmConsole.h"

cmConsoleGUI::cmConsoleGUI()
{
	mHistory.reserve(1000);
}

void cmConsoleGUI::Initialize()
{
	SetHotKey(ImGuiKey_F5);
	SetVisible(false);
}

void cmConsoleGUI::RenderGUI()
{
	const std::vector<cmConsoleData>& consoleDatas = Engine->GetConsole()->GetConsoleDatas();

	ImGui::SetNextWindowSize({ 400, 400 }, ImGuiCond_FirstUseEver);
	ImGui::Begin("Console", GetVisiblePtr(), ImGuiWindowFlags_NoFocusOnAppearing);
	ImGui::SeparatorText("Command-Line");

	// 히스토리
	{
		static ImGuiChildFlags cFlag = ImGuiChildFlags_Borders;
		ImGui::BeginChild("CommandLine", { 0, -ImGui::GetFrameHeightWithSpacing() }, cFlag, 0);

		// 메시지 표시
		for (const cmConsoleData& item : consoleDatas)
		{
			ImGui::Helper::TextColoredWrap(cmConsoleData::TextColor[(uint64)item.TextType], item.Text.c_str());
		}

		// 오토 스크롤
		if (mAutoScroll && mNeedScroll)
		{
			ImGui::SetScrollHereY(1.0f);
			mNeedScroll = false;
		}

		// 팝업
		if (ImGui::BeginPopupContextWindow())
		{
			if (ImGui::Selectable("Clear")) { Engine->GetConsole()->ClearConsoleDatas(); } /* Clear */
			if (ImGui::Selectable("Help")) { Engine->GetConsole()->ExecuteCommand("help", {}); } /* Help */

			/* 로그 색상 설정 */
			if (ImGui::BeginMenu("Set Log Text Color"))
			{
				ImGui::Text("Set Console Text Color");

				ImGui::ColorEdit3("Normal Text", (float*)&cmConsoleData::TextColor[0]);
				ImGui::ColorEdit3("Command Text", (float*)&cmConsoleData::TextColor[1]);
				ImGui::ColorEdit3("Error Text", (float*)&cmConsoleData::TextColor[2]);

				ImGui::EndMenu();
			}

			ImGui::Checkbox("Auto Scroll", &mAutoScroll); /* 오토 스크롤 */

			ImGui::Separator();
			if (ImGui::Selectable("Close")) { SetVisible(false); }

			ImGui::EndPopup();
		}


		ImGui::EndChild();
	}

	// Enter 입력시 자동 포커스
	if (ImGui::IsWindowFocused(ImGuiFocusedFlags_RootAndChildWindows) && ImGui::IsKeyPressed(ImGuiKey_Enter))
	{
		ImGui::SetKeyboardFocusHere();
	}

	// Input
	{
		static bool sSend = false;

		// History Callback
		static auto callback = [](ImGuiInputTextCallbackData* data) {
			cmConsoleGUI* gui = static_cast<cmConsoleGUI*>(data->UserData);
			if (data->EventFlag == ImGuiInputTextFlags_CallbackHistory)
			{
				if (data->EventKey == ImGuiKey_UpArrow)
				{
					gui->mHistroyIndex = max(gui->mHistroyIndex - 1, 0);
				}
				else if (data->EventKey == ImGuiKey_DownArrow)
				{
					gui->mHistroyIndex = min(gui->mHistroyIndex + 1, gui->mHistory.size() - 1);
				}

				if (gui->mHistroyIndex >= 0 && gui->mHistroyIndex < gui->mHistory.size())
				{
					data->DeleteChars(0, data->BufTextLen);
					data->InsertChars(0, gui->mHistory[gui->mHistroyIndex].c_str());
				}
			}
			return 0;
			};


		static ImGuiInputTextFlags flags = ImGuiInputTextFlags_EscapeClearsAll | ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_CallbackHistory;

		// 입력
		if (ImGui::InputText("##Input", mInputBuffer.data(), mInputBuffer.capacity(), flags, callback, this))
		{
			sSend = true;
		};

		// 전송 버튼
		ImGui::SameLine();
		if (ImGui::Button("send")) { sSend = true; };

		// 커맨드 핸들러
		if (sSend)
		{
			CommandHandler();
			sSend = false;
		}
	}

	ImGui::End();
}

void cmConsoleGUI::SendConsoleData(std::string_view inMsg, eConsoleDataType inDataType)
{
	Engine->GetConsole()->PushConsoleData(inMsg.data(), inDataType);
	if (inDataType == eConsoleDataType::Command) { mHistory.push_back(inMsg.data()); } // 만약 CommandMsg면 히스토리에 추가
	mNeedScroll = true;
}

void cmConsoleGUI::CommandHandler()
{
	// 커맨드 버퍼 예외처리
	size_t len = mInputBuffer.Length();
	if (len <= 0 || mInputBuffer[0] == '\0' || mInputBuffer[0] == ' ')
	{
		return;
	}

	// 핑퐁 메시지 (사용자가 입력한 메시지 그대로 출력)
	SendConsoleData(mInputBuffer.c_str(), eConsoleDataType::Command);

	// 커맨드와 매개변수 분리
	size_t idx;
	for (idx = 0; idx < len; ++idx)
	{
		if (mInputBuffer[idx] == ' ') { break; }
	}

	std::string cmd{ mInputBuffer.data(), mInputBuffer.data() + idx };
	std::vector<std::string> arg;

	// 매개변수가 있으면 추가
	if (idx < len)
	{
		arg = cmString::Split({ mInputBuffer.data() + idx + 1, mInputBuffer.data() + len });
	}

	// 실행 
	Engine->GetConsole()->ExecuteCommand(cmd, arg);

	// 입력문자 초기화
	mInputBuffer[0] = '\0';

	// 히스토리 인덱스 수정
	mHistroyIndex = mHistory.size();
}


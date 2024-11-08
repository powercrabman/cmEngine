#include "pch.h"
#include "cmLoggerGUI.h"

void cmLoggerGUI::Initialize()
{
	SetHotKey(ImGuiKey_F6);
	SetVisible(false);
}

void cmLoggerGUI::RenderGUI()
{
	ImGui::SetNextWindowSize({ 400, 500 }, ImGuiCond_FirstUseEver);

	// �α� ������
	const std::vector<cmLogData>& logData = Engine->GetLogger()->GetLogData();

	// GUI ����
	ImGui::Begin("Logger", GetVisiblePtr(), ImGuiWindowFlags_NoFocusOnAppearing);

	// �ɼ�
	ImGui::SeparatorText("Option");
	{
		// ��� �����
		if (ImGui::Button("Clear")) { Engine->GetLogger()->ClearLog(); }
		ImGui::Helper::Tooltip("Clear Log History.");

		ImGui::SameLine();

		// ����
		if (ImGui::Button("Copy"))
		{
			// TEMP
			ImGui::LogToClipboard();
			//ImGui::LogText(logDataVector.c_str());
			ImGui::LogFinish();
		}
		ImGui::Helper::Tooltip("Copy to clipboard.");

		ImGui::SameLine();

		// Level ����
		if (ImGui::Button("Level Filter")) { ImGui::OpenPopup("Level Popup"); }
		if (ImGui::BeginPopup("Level Popup"))
		{
			ImGui::Text("Enable level flag to show.");
			ImGui::Separator();
			ImGui::CheckboxFlags("All", &mShowFlags, LOGGER_SHOW_FLAGS_ALL);
			ImGui::CheckboxFlags("Trace", &mShowFlags, LOGGER_SHOW_FLAGS_TRACE);
			ImGui::CheckboxFlags("Debug", &mShowFlags, LOGGER_SHOW_FLAGS_DEBUG);
			ImGui::CheckboxFlags("Info", &mShowFlags, LOGGER_SHOW_FLAGS_INFO);
			ImGui::CheckboxFlags("Warn", &mShowFlags, LOGGER_SHOW_FLAGS_WARN);
			ImGui::CheckboxFlags("Error", &mShowFlags, LOGGER_SHOW_FLAGS_ERROR);
			ImGui::CheckboxFlags("Fatal", &mShowFlags, LOGGER_SHOW_FLAGS_FATAL);

			ImGui::EndPopup();
		}

		// �޽��� ����
		{
			mFilter.Draw("Search");
		}
		ImGui::Helper::Tooltip("Only active in history!");
	}

	// �α� ������
	{
		ImGui::SeparatorText("Log History");

		// �α� ���
		static ImGuiTableFlags flags = ImGuiTableFlags_BordersOuterV | ImGuiTableFlags_BordersOuterH | ImGuiTableFlags_BordersInnerV | ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_ScrollX | ImGuiTableFlags_ScrollY;
		if (ImGui::BeginTable("Test", 3, flags))
		{
			ImGui::TableSetupScrollFreeze(0, 1);
			ImGui::TableSetupColumn("Time", ImGuiTableColumnFlags_WidthFixed);
			ImGui::TableSetupColumn("Level", ImGuiTableColumnFlags_WidthFixed);
			ImGui::TableSetupColumn("Message", ImGuiTableColumnFlags_WidthStretch);
			ImGui::TableHeadersRow();

			for (const cmLogData& log : logData)
			{
				// ���͸�
				if (mFilter.IsActive() && !mFilter.PassFilter(log.Text.c_str()))
				{
					continue;
				}

				// �α� level ���͸�
				if (!(mShowFlags & (1 << static_cast<uint32>(log.Level))))
				{
					continue;
				}

				ImGui::TableNextRow();
				uint32 idx = (uint32)log.Level;
				const ImVec4& color = cmLogData::sLogLevelColor[idx];

				ImGui::TableSetColumnIndex(0);
				ImGui::TextColored(color, "%.2f sec", log.TimeStamp);

				ImGui::TableSetColumnIndex(1);
				ImGui::TextColored(color, cmLogData::sLogLevelString[idx]);

				ImGui::TableSetColumnIndex(2);
				ImGui::TextColored(color, log.Text.c_str());
			}

			//���ο� �αװ� �߰��ƴٸ� �ڵ����� ���� �Ʒ��� (AUto-Scroll �� true ������)
			if (mAutoScroll && mNeedScroll)
			{
				ImGui::SetScrollHereY(1.0f);
				mNeedScroll = false;
			}

			// ������ �˾�
			{
				if (ImGui::BeginPopupContextWindow())
				{
					// Clear
					if (ImGui::Selectable("Clear")) { Engine->GetLogger()->ClearLog(); }

					// ����� ���� ������ ����
					if (ImGui::BeginMenu("Create Dummy Log"))
					{
						static int slider_i = 0;
						ImGui::Text("How many insert?");
						ImGui::SliderInt("##", &slider_i, 0, 100, "%d");

						if (ImGui::Button("Apply"))
						{
							for (int i = 0; i < slider_i; i++)
							{
								int idx = cmRandom::GetInt(0, static_cast<int>(eLogLevel::Count) - 1);
								eLogLevel level = static_cast<eLogLevel>(idx);
								Engine->GetLogger()->Logging(level, "Hello, World : %.1lf, Random Number : %d", ImGui::GetTime(), cmRandom::GetInt(0, 100));
							}
						}
						ImGui::EndMenu();
					}

					// �ؽ��� ���� ����
					if (ImGui::BeginMenu("Set Log Text Color"))
					{
						static ImGuiColorEditFlags flags = ImGuiColorEditFlags_Uint8;

						ImGui::Text("Color Format");

						ImGui::RadioButton("uint8", &flags, ImGuiColorEditFlags_Uint8);
						ImGui::RadioButton("float", &flags, ImGuiColorEditFlags_Float);

						ImGui::Separator();

						const char* sLogText[] = { "Trace", "Debug","Info", "Warn", "Error", "Fatal" };

						// ���� ������
						for (int i = 0; i < (uint32)eLogLevel::Count; ++i)
						{
							ImGui::Text(sLogText[i]);
							ImGui::ColorEdit3(sLogText[i], (float*)&cmLogData::sLogLevelColor[i], flags);
						}

						ImGui::EndMenu();
					}

					// Auto Scroll
					ImGui::Checkbox("Auto Scroll", &mAutoScroll);

					ImGui::Separator();
					if (ImGui::Selectable("Close")) { SetVisible(false); }

					ImGui::EndPopup();
				}
			}

			ImGui::EndTable();
		}
	}

	ImGui::End();
}

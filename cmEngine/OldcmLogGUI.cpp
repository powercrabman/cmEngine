#include "pch.h"
#include "OldcmLogGUI.h"
#include <fstream>
#include <filesystem>

OldcmLogGUI::OldcmLogGUI()
{
	mLogBuffer.reserve(100000);
	mLogDatas.reserve(1000);
}

void OldcmLogGUI::Initialize()
{
	SetHotKey(ImGuiKey::ImGuiKey_F6);
	DisableVisible();
}

void OldcmLogGUI::SetupGUILayout()
{
	ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiCond_FirstUseEver);

	ImGui::Begin("Log Viewer", &mVisible);

	ImGui::SeparatorText("Option");

	//�α� �ʱ�ȭ
	if (ImGui::Button("Clear"))
	{
		mLogDatas.clear();
		mLogBuffer.clear();
	}

	//�α� ����
	{
		ImGui::SameLine();
		if (ImGui::Button("Copy"))
		{
			ImGui::LogToClipboard();
			ImGui::LogText(mLogBuffer.c_str());
			ImGui::LogFinish();
		}

		//����
		ImGui::TooltipHelper("Copy to clipboard.");
	}


	//���Ϸ� ����
	{

		ImGui::SameLine();
		if (ImGui::Button("Save"))
		{
			mShowSaveDlg = !mShowSaveDlg;
		}

		//����
		ImGui::TooltipHelper("Save to file.");

		//���ϰ�����
		if (IsVisible() && mShowSaveDlg)
		{
			ShowSaveDlg();
		}
	}

	//����
	static ImGuiTextFilter logFilter;
	logFilter.Draw("Filter", 200);


	//�α� ���
	ImGui::SeparatorText("Log");

	{
		ImGui::BeginChild("LogViewer", { 0, 0 }, true, ImGuiWindowFlags_AlwaysVerticalScrollbar);

		// �޴�
		if (ImGui::BeginPopupContextWindow("LogViewerPopup", 1))
		{
			// ���� ������ �߰� (����� ��)
			if (ImGui::BeginMenu("Create Dummy Log"))
			{
				static int slider_i = 0;
				ImGui::Text("How many insert?");
				ImGui::SliderInt("##", &slider_i, 0, 100, "%d");

				if (ImGui::Button("Apply"))
				{
					for (int i = 0; i < slider_i; i++)
					{
						int idx = cmRandom::GetInt(0, static_cast<int>(eLogType::Count) - 1);
						eLogType type = static_cast<eLogType>(idx);
						Logging(type, "Hello, World : %.1lf, Random Number : %d", ImGui::GetTime(), cmRandom::GetInt(0, 100));
					}
				}

				ImGui::EndMenu();
			}

			// �α� �ؽ�Ʈ ���� ���� ��
			if (ImGui::BeginMenu("Set Log Text Color"))
			{
				static ImGuiColorEditFlags flags = ImGuiColorEditFlags_Uint8;

				ImGui::Text("Color Format");

				ImGui::RadioButton("uint8", &flags, ImGuiColorEditFlags_Uint8);
				ImGui::RadioButton("float", &flags, ImGuiColorEditFlags_Float);

				ImGui::Separator();

				ImGui::Text("None");
				ImGui::ColorEdit3("##1", (float*)&sLogTextColor[0], flags);

				ImGui::Text("Info");
				ImGui::ColorEdit3("##2", (float*)&sLogTextColor[1], flags);

				ImGui::Text("Warning");
				ImGui::ColorEdit3("##3", (float*)&sLogTextColor[2], flags);

				ImGui::Text("Error");
				ImGui::ColorEdit3("##4", (float*)&sLogTextColor[3], flags);

				ImGui::EndMenu();
			}

			// Auto Scroll
			ImGui::MenuItem("Auto Scroll", NULL, &mAutoScroll, true);

			ImGui::EndPopup();
		}

		//�α� ���
		for (const LogData& ld : mLogDatas)
		{
			std::string logText = mLogBuffer.substr(ld.Index, ld.Length);
			if (logFilter.IsActive())
			{
				if (logFilter.PassFilter(logText.c_str()))
				{
					ImGui::TextColored(GetTextColor(ld.Type), logText.c_str());
				}
			}
			else
			{
				ImGui::TextColored(GetTextColor(ld.Type), logText.c_str());
			}
		}

		//���ο� �αװ� �߰��ƴٸ� �ڵ����� ���� �Ʒ���
		if (mAutoScroll && mNeedScroll)
		{
			ImGui::SetScrollHereY(1.0f);
			mNeedScroll = false;
		}

		ImGui::EndChild();
	}

	ImGui::End();
}

void OldcmLogGUI::ShowSaveDlg()
{
	static ImGui::FileDialogHelper fd;
	static bool show = true;
	static cmStaticTextBuffer<256> buf = {};
	fd.Show("File Sexer", &show, (cmStaticTextBufferBase*)&buf);

	////���� Ž����
	//ImGui::SetNextWindowPos(ImGui::GetWindowPos(), ImGuiCond_Appearing);
	//
	//static char* fileDlgBuffer = nullptr;
	//static char path[500] = "";
	//
	////���� Ž���� �ھ�
	//{
	//	ImGui::SeparatorText("Choose folder to save");
	//
	//	ImGui::TextUnformatted("Path: ");
	//	ImGui::InputText("##path", path, sizeof(path));
	//	ImGui::SameLine();
	//
	//	if (ImGui::Button("Browse##path"))
	//	{
	//		fileDlgBuffer = path;
	//		FileDialog::file_dialog_open = true;
	//		FileDialog::file_dialog_open_type = FileDialog::FileDialogType::OpenFile;
	//	}
	//
	//	if (FileDialog::file_dialog_open)
	//	{
	//		FileDialog::ShowFileDialog(&FileDialog::file_dialog_open, fileDlgBuffer, sizeof(fileDlgBuffer), FileDialog::file_dialog_open_type);
	//	}
	//}
	//
	//static char saveFileName[64] = "";
	//
	////���� ����
	//{
	//	ImGui::Separator();
	//
	//	ImGui::BulletText("file name (with format)");
	//	ImGui::InputText("##Save", saveFileName, sizeof(saveFileName));
	//}
	//
	////���� ���� ��ư
	//{
	//	ImGui::Spacing();
	//
	//	static bool clicked = false;
	//	static std::string msg = {};
	//
	//	if (ImGui::Button("Save"))
	//	{
	//		//���� ���� �ھ�
	//		if (SaveFile(fileDlgBuffer, saveFileName))
	//		{
	//			msg = "Save Successful";
	//		}
	//		else
	//		{
	//			msg = "Save Fail.";
	//		}
	//
	//		clicked = true;
	//	}
	//
	//	ImGui::SameLine();
	//
	//	//���� ��� ��ư 
	//	if (ImGui::Button("Cancel"))
	//	{
	//		mShowSaveDlg = false;
	//	}
	//
	//	//���� ��ư Ŭ���� ������ �޽���
	//	ImGui::SimpleMessageBoxHelper(&clicked, msg.c_str());
	//}
}

bool OldcmLogGUI::SaveFile(std::string_view inFilePath, std::string_view inFileName) const
{
	std::fstream fs = {};

	std::filesystem::path realPath = inFilePath;
	realPath /= inFileName;

	fs.open(realPath, std::ios_base::out | std::ios_base::trunc);

	// ���� ���� ����
	if (fs.is_open() == false)
	{
		return false;
	}

	fs << mLogBuffer;

	return true;
}

void OldcmLogGUI::Logging(eLogType inType, const char* format, const va_list& args)
{
	if (inType == eLogType::None)
	{
		mTempBuffer.Print(format, args);
	}
	else
	{
		mTempBuffer.Print("[%.2lf sec][%s]", ImGui::GetTime(), GetTextString(inType));
		mTempBuffer.Append(format, args);
	}

	LogData ld = {};
	ld.Index = mLogBuffer.size();
	ld.Type = inType;

	mLogBuffer.append(mTempBuffer.c_str());
	mLogBuffer.append("\n");

	ld.Length = mTempBuffer.size();
	mLogDatas.push_back(ld);

	if (mAutoScroll)
	{
		mNeedScroll = true;
	}
}

// [Internal]
void OldcmLogGUI::Logging(const char* format, ...)
{
	va_list args;
	va_start(args, format);
	Logging(format, args);
	va_end(args);
}

void OldcmLogGUI::Logging(eLogType inType, const char* format, ...)
{
	va_list args;
	va_start(args, format);
	Logging(inType, format, args);
	va_end(args);
}


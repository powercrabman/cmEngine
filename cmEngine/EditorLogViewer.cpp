#include "EnginePch.h"
#include "EditorLogViewer.h"

namespace cmEngine
{
	EditorLogViewer::EditorLogViewer()
	{
		JsonSerializer::Deserialize(mConfig);
		SetVisible(mConfig.visible);
	}

	EditorLogViewer::~EditorLogViewer()
	{
		mConfig.visible = IsVisible();
		JsonSerializer::Serialize(mConfig);
	}

	void EditorLogViewer::RenderGui()
	{
		ImGui::SetNextWindowSize({ 300,400 }, ImGuiCond_FirstUseEver);
		ImGui::Begin("Log History", GetVisiblePtr());

		ImGui::SeparatorText("Log");
		ImGui::Text("Log count : %d", mLogSize);
		ImGui::BeginChild("Log History", { 0,0 }, ImGuiChildFlags_Border, ImGuiWindowFlags_HorizontalScrollbar);

		for (auto iter = Log::GetLogDataConstBegin(); iter != Log::GetLogDataConstEnd(); ++iter)
		{
			ImGui::TextColored(
				LogData::LogLevelColor[(uint32)iter->LogLevel],
				"[%.2f sec] %s | %s | %s",
				iter->LogTime,
				ToString(iter->LogCaller),
				ToString(iter->LogLevel),
				iter->LogMessage.c_str()
			);
		}

		if (mLogSize != Log::GetLogListSize() && mConfig.autoScrollBit) { ImGui::SetScrollHereY(1.f); }
		mLogSize = Log::GetLogListSize();

		if (ImGui::BeginPopupContextWindow())
		{
			if (ImGui::BeginMenu("Set log level color"))
			{
				ImGui::ColorEdit4("Trace", (float*)&LogData::LogLevelColor[(uint32)eLogLevel::Trace]);
				ImGui::ColorEdit4("Debug", (float*)&LogData::LogLevelColor[(uint32)eLogLevel::Debug]);
				ImGui::ColorEdit4("Info", (float*)&LogData::LogLevelColor[(uint32)eLogLevel::Info]);
				ImGui::ColorEdit4("Warn", (float*)&LogData::LogLevelColor[(uint32)eLogLevel::Warn]);
				ImGui::ColorEdit4("Error", (float*)&LogData::LogLevelColor[(uint32)eLogLevel::Error]);
				ImGui::ColorEdit4("Fatal", (float*)&LogData::LogLevelColor[(uint32)eLogLevel::Fatal]);

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Create debug message"))
			{
				static int messageCount = 0;

				ImGui::Text("how many make message?");
				ImGui::SliderInt("##meesageCount", &messageCount, 1, 1000);

				if (ImGui::SmallButton("create"))
				{
					for (int i = 0; i < messageCount; i++)
					{
						int loglevel = Random::GetInt(0, (uint32)eLogLevel::Count - 1);
						if (rand() & 1) { Log::LogEngine((eLogLevel)loglevel, "Hello!! I am debug message!"); }
						else { Log::LogClient((eLogLevel)loglevel, "Hello!! I am debug message!"); }
					}
				}

				ImGui::EndMenu();
			}

			if (ImGui::MenuItem("Clear")) { Log::ClearLogList(); }
			ImGui::Checkbox("Auto scroll", &mConfig.autoScrollBit);

			ImGui::Separator();
			if (ImGui::MenuItem("Close")) { SetVisible(false); }

			ImGui::EndPopup();
		}

		ImGui::EndChild();
		ImGui::End();
	}
}

#include "EnginePch.h"
#include "EditorLogViewer.h"

namespace cmEngine
{
	EditorLogViewer::EditorLogViewer()
	{
		JsonSerializer::DeserializeFromSection(
			mConfig,
			Editor::sEditorConfigPath,
			"EditorLogViewer"
		);

		SetVisible(mConfig.visible);
		SetHotKey(eKeyCode::F6);
	}

	EditorLogViewer::~EditorLogViewer()
	{
		mConfig.visible = IsVisible();
		JsonSerializer::SerializeToSection(
			mConfig,
			Editor::sEditorConfigPath,
			"EditorLogViewer"
		);
	}

	void EditorLogViewer::RenderGui()
	{
		ImGui::SetNextWindowSize({ 300,400 }, ImGuiCond_FirstUseEver);
		ImGui::Begin("Log History", GetVisiblePtr());

		ImGui::SeparatorText("Log");
		ImGui::Text("Log count : %d", Log::GetLogListSize());
		ImGui::BeginChild("Log History", { 0,0 }, ImGuiChildFlags_Border);

		size_t		lineOffsetSize = Log::GetLogListSize();
		const char* buf = Log::GetLogTextBegin();
		const char* buf_end = Log::GetLogTextEnd();
		LogInfo* LineOffsets = Log::GetLogListData();

		ImGuiListClipper clipper;
		clipper.Begin(lineOffsetSize);
		while (clipper.Step())
		{
			for (int line_no = clipper.DisplayStart; line_no < clipper.DisplayEnd; line_no++)
			{
				const char* line_start = buf + LineOffsets[line_no].lineOffset;
				const char* line_end = (line_no + 1 < lineOffsetSize) ? (buf + LineOffsets[line_no + 1].lineOffset - 1) : buf_end;
				ImGui::PushStyleColor(ImGuiCol_Text, mConfig.textColor[static_cast<uint32>(LineOffsets[line_no].logLevel)]);
				ImGui::TextUnformatted(line_start, line_end);
				ImGui::PopStyleColor();
			}
		}
		clipper.End();

		// Auto-Scroll
		if (mConfig.autoScrollBit && mPrevLogSize != lineOffsetSize)
		{
			mPrevLogSize = lineOffsetSize;
			ImGui::SetScrollHereY(1.f);
		}

		if (ImGui::BeginPopupContextWindow())
		{
			if (ImGui::BeginMenu("Set log level color"))
			{
				ImGui::ColorEdit4("Trace", reinterpret_cast<float*>(&mConfig.textColor[static_cast<uint32>(eLogLevel::Trace)]));
				ImGui::ColorEdit4("Debug", reinterpret_cast<float*>(&mConfig.textColor[static_cast<uint32>(eLogLevel::Debug)]));
				ImGui::ColorEdit4("Info", reinterpret_cast<float*>(&mConfig.textColor[static_cast<uint32>(eLogLevel::Info)]));
				ImGui::ColorEdit4("Warn", reinterpret_cast<float*>(&mConfig.textColor[static_cast<uint32>(eLogLevel::Warn)]));
				ImGui::ColorEdit4("Error", reinterpret_cast<float*>(&mConfig.textColor[static_cast<uint32>(eLogLevel::Error)]));
				ImGui::ColorEdit4("Fatal", reinterpret_cast<float*>(&mConfig.textColor[static_cast<uint32>(eLogLevel::Fatal)]));

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
						int loglevel = Random::GetInt(0, static_cast<uint32>(eLogLevel::Count) - 1);
						if (rand() & 1) { Log::LogEngine(static_cast<eLogLevel>(loglevel), "Hello!! I am debug message!"); }
						else { Log::LogClient(static_cast<eLogLevel>(loglevel), "Hello!! I am debug message!"); }
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

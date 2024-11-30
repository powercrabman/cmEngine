#pragma once

class ImFileDialog
{
public:
	ImFileDialog()
		: mVisible(false)
		, mCurrentPath(std::filesystem::current_path())
	{
	}

	void Draw()
	{
		if (!mVisible) { return; }

		ImGui::SetNextWindowSize(ImVec2{ 600, 400 }, ImGuiCond_FirstUseEver);
		ImGui::Begin("File Dialog", &mVisible, ImGuiWindowFlags_NoCollapse);

		if (ImGui::ArrowButton("cd", ImGuiDir_Left))
		{
			mCurrentPath = mCurrentPath.parent_path();
		}
		ImGui::SameLine();

		std::string curPath = mCurrentPath.string();
		ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
		ImGui::InputText("##CurPath", curPath.data(), curPath.size(), ImGuiInputTextFlags_ReadOnly);
		ImGui::Separator();

		static float directoryTreeWidthRatio = 0.3f;
		static float directoryTreeHeightRatio = 0.78f;

		ImVec2 avail = ImGui::GetContentRegionAvail();
		float directoryTreeHeight = avail.y * directoryTreeHeightRatio;
		float directoryTreeWidth = avail.x * directoryTreeWidthRatio;
		float currentDirectoryWidth = avail.x - directoryTreeWidth;

		ImGui::BeginGroup();
		ImGui::TextUnformatted("Directory View");
		if (ImGui::BeginChild("Directory View", { directoryTreeWidth, directoryTreeHeight }, ImGuiChildFlags_Border))
		{
			size_t dirCount = 0;

			if (ImGui::Selectable("..")) { mCurrentPath = mCurrentPath.parent_path(); }
			ImGui::Separator();

			for (const auto& entry : std::filesystem::directory_iterator(mCurrentPath))
			{
				if (entry.is_directory())
				{
					if (ImGui::Selectable(entry.path().filename().string().c_str(), false, ImGuiSelectableFlags_AllowDoubleClick))
					{
						mCurrentPath = entry;
					}
					ImGui::Separator();
				}
			}

			ImGui::EndChild();
		}
		ImGui::EndGroup();

		ImGui::SameLine();

		ImGui::BeginGroup();
		ImGui::TextUnformatted("Current Directory");
		if (ImGui::BeginChild("Current Directory", { currentDirectoryWidth, directoryTreeHeight }, ImGuiChildFlags_Border))
		{
			if (ImGui::BeginTable("FileTable", 3, ImGuiTableFlags_Resizable | ImGuiTableFlags_BordersInnerV))
			{
				ImGui::TableSetupColumn("File Name", ImGuiTableColumnFlags_WidthStretch);
				ImGui::TableSetupColumn("File Size", ImGuiTableColumnFlags_WidthFixed, 80.0f);
				ImGui::TableSetupColumn("Date Modified", ImGuiTableColumnFlags_WidthFixed, 150.0f);
				ImGui::TableHeadersRow();

				for (const auto& entry : std::filesystem::directory_iterator(mCurrentPath))
				{
					if (entry.is_regular_file())
					{
						ImGui::TableNextRow();
						ImGui::TableNextColumn();

						const auto& fileName = entry.path().filename().string();
						if (ImGui::Selectable(fileName.c_str(), false, ImGuiSelectableFlags_SpanAllColumns))
						{
							mSelectedFile = entry.path();
						}

						ImGui::TableNextColumn();
						auto fileSize = std::filesystem::file_size(entry);
						ImGui::Text("%lld bytes", fileSize);

						ImGui::TableNextColumn();
						auto ftime = entry.last_write_time();
						auto sctp = std::chrono::time_point_cast<std::chrono::system_clock::duration>(
							ftime - std::filesystem::file_time_type::clock::now() + std::chrono::system_clock::now()
						);
						std::time_t cftime = std::chrono::system_clock::to_time_t(sctp);

						std::tm timeInfo = {};
						localtime_s(&timeInfo, &cftime);

						static char timeStr[100];
						std::strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", &timeInfo);
						ImGui::TextUnformatted(timeStr);
					}
				}

				ImGui::EndTable();
			}
			ImGui::EndChild();
		}
		ImGui::EndGroup();

		ImGui::TextUnformatted("Selected File : ");
		std::string selectedFile = mSelectedFile.string();
		ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
		ImGui::InputText("##selected", selectedFile.data(), selectedFile.size(), ImGuiInputTextFlags_ReadOnly);

		ImGui::Spacing();
		if (ImGui::Button("OK")) { mVisible = false; }
		ImGui::SameLine();
		if (ImGui::Button("Cancel")) { mSelectedFile.clear(); mVisible = false; }

		ImGui::End();
	}

	void	SetVisible(bool inVisible) { mVisible = inVisible; }
	bool	IsVisible() const { return mVisible; }
	bool*	GetVisibleRef() { return &mVisible; }

	const std::filesystem::path& GetSelectedFile() const { return mSelectedFile; }

private:
	std::filesystem::path mCurrentPath = {};
	std::filesystem::path mSelectedFile = {};
	bool mVisible;
};

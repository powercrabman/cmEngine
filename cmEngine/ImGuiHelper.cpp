#include "pch.h"
#include "ImGuiHelper.h"
#include <filesystem>
#include <chrono>
#include <ctime>
#include "cmWindow.h"
#include "cmWindowsManager.h"

#include <string>

void ImGui::Helper::FileDialogHelper::Show(const char* inDlgTitle, bool* open, cmStaticTextBufferBase* outBuffer)
{
	static std::string currentPath = std::filesystem::current_path().string();
	// ���� ���� ����
	static std::filesystem::directory_entry selectedFolder; // ���õ� ���� ��θ� ������ ����
	static std::string renameFolderName;  // ���� �̸� ���� �� ����� �̸�
	static bool showRenamePopup = false;  // ���� �̸� ���� �˾��� �������� ����

	if (*open)
	{
		// ���� Ž���� â ����
		ImGui::Begin(inDlgTitle, open, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);

		// ���� ���丮�� ���ϰ� ���� ��� ����
		std::vector<std::filesystem::directory_entry> files;
		std::vector<std::filesystem::directory_entry> folders;

		// ���� ����� ���丮 �� ���ϵ��� �з�
		for (const auto& p : std::filesystem::directory_iterator(currentPath))
		{
			if (p.is_directory())
				folders.push_back(p);
			else
				files.push_back(p);
		}

		// ���� ���丮 �̵��� ���� ".." �߰�
		ImGui::Text("Current Path: %s", currentPath.c_str());

		ImGui::Separator();

		// ���丮 ��� (����)
		ImGui::BeginChild("Directories##1", ImVec2(200, 400), true, ImGuiWindowFlags_HorizontalScrollbar);

		if (ImGui::Selectable("..", false))
		{
			currentPath = std::filesystem::path(currentPath).parent_path().string();
		}

		for (const auto& folder : folders)
		{
			if (ImGui::Selectable(folder.path().filename().string().c_str(), false))
			{
				currentPath = folder.path().string();
				outBuffer->Print(currentPath.c_str());
			}
		}
		ImGui::EndChild();

		ImGui::SameLine();

		// ���� ��� (ǥ ����)
		ImGui::BeginChild("Files##2", ImVec2(600, 400), true, ImGuiWindowFlags_HorizontalScrollbar);

		// ��� ������ ��ü �ʺ� ��������
		float totalWidth = ImGui::GetContentRegionAvail().x;

		// �� ���� �Ҵ��� �ʺ� ���� ����
		float fileColumnWidth = totalWidth * 0.4f;    // ���� �̸� ���� ��ü �ʺ��� 40% �Ҵ�
		float sizeColumnWidth = totalWidth * 0.2f;    // ���� ũ�� ���� ��ü �ʺ��� 20% �Ҵ�
		float typeColumnWidth = totalWidth * 0.2f;    // ���� Ÿ�� ���� ��ü �ʺ��� 20% �Ҵ�
		float dateColumnWidth = totalWidth * 0.2f;    // ���� ��¥ ���� ��ü �ʺ��� 20% �Ҵ�

		// �� ���� �� �ʺ� ����
		ImGui::Columns(4, "file_columns");
		ImGui::SetColumnWidth(0, fileColumnWidth);
		ImGui::SetColumnWidth(1, sizeColumnWidth);
		ImGui::SetColumnWidth(2, typeColumnWidth);
		ImGui::SetColumnWidth(3, dateColumnWidth);

		// �� ���� ǥ��
		ImGui::Text("File"); ImGui::NextColumn();
		ImGui::Text("Size (bytes)"); ImGui::NextColumn();
		ImGui::Text("Type"); ImGui::NextColumn();
		ImGui::Text("Date Modified"); ImGui::NextColumn();
		ImGui::Separator();

		for (const auto& file : files)
		{
			// ���� �̸�
			ImGui::Text(file.path().filename().string().c_str());
			ImGui::NextColumn();

			// ���� ũ��
			ImGui::Text("%lld", file.file_size());
			ImGui::NextColumn();

			// ���� Ȯ����
			ImGui::Text("%s", file.path().extension().string().c_str());
			ImGui::NextColumn();

			// ���� ���� ��¥
			auto ftime = file.last_write_time();
			auto sctp = decltype(ftime)::clock::now() - (decltype(ftime)::clock::now() - ftime);

			// std::filesystem�� ���� �ð��� time_t�� ��ȯ
			auto system_time = std::chrono::time_point_cast<std::chrono::system_clock::duration>(
				sctp - decltype(sctp)::clock::now() + std::chrono::system_clock::now());

			std::time_t tt = std::chrono::system_clock::to_time_t(system_time);
			struct tm timeInfo;
			localtime_s(&timeInfo, &tt);  // localtime_s�� ����Ͽ� �����ϰ� ��ȯ

			char timeStr[64];
			std::strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M", &timeInfo);
			ImGui::Text("%s", timeStr);
			ImGui::NextColumn();
		}

		ImGui::EndChild();

		// ���� �̸� �Է� �ʵ� �� "Ȯ��" ��ư
		ImGui::Separator();
		ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
		ImGui::InputText("##File Name", outBuffer->data(), outBuffer->capacity(), ImGuiInputTextFlags_AutoSelectAll);

		if (ImGui::Button("New Folder"))
		{
			std::string newFolderPath = currentPath + "/NewFolder";
			int folderCount = 1;
			while (std::filesystem::exists(newFolderPath))
			{
				newFolderPath = currentPath + "/NewFolder" + std::to_string(folderCount++);
			}
			std::filesystem::create_directory(newFolderPath);
		}

		ImGui::SameLine();

		if (ImGui::Button("Rename Folder"))
		{
			if (!selectedFolder.path().empty())
			{
				renameFolderName = selectedFolder.path().filename().string();
				showRenamePopup = true;
			}
		}

		if (showRenamePopup)
		{
			ImGui::OpenPopup("Rename Folder");
		}

		if (ImGui::BeginPopupModal("Rename Folder", NULL, ImGuiWindowFlags_AlwaysAutoResize))
		{
			ImGui::InputText("New Name", renameFolderName.data(), renameFolderName.size());

			if (ImGui::Button("OK"))
			{
				std::filesystem::rename(selectedFolder.path(), selectedFolder.path().parent_path() / renameFolderName);
				showRenamePopup = false;
				ImGui::CloseCurrentPopup();
			}

			ImGui::SameLine();

			if (ImGui::Button("Cancel"))
			{
				showRenamePopup = false;
				ImGui::CloseCurrentPopup();
			}

			ImGui::EndPopup();
		}

		ImGui::SameLine();

		if (ImGui::Button("Delete Folder"))
		{
			if (std::filesystem::is_empty(currentPath))
			{
				std::filesystem::remove_all(currentPath);
			}
			else
			{
				ImGui::OpenPopup("Warning");
			}
		}

		if (ImGui::BeginPopupModal("Warning", NULL, ImGuiWindowFlags_AlwaysAutoResize))
		{
			ImGui::Text("The folder is not empty. Are you sure you want to delete it?");
			ImGui::Separator();

			if (ImGui::Button("OK"))
			{
				std::filesystem::remove_all(currentPath);
				ImGui::CloseCurrentPopup();
			}

			ImGui::SameLine();

			if (ImGui::Button("Cancel"))
			{
				ImGui::CloseCurrentPopup();
			}

			ImGui::EndPopup();
		}

		ImGui::SameLine();

		ImGui::SetCursorPosX(ImGui::GetWindowWidth() - 120);
		if (ImGui::Button("OK", { 50,0 }))
		{
			*open = false;  // ���̾�α� �ݱ�
		}

		ImGui::SameLine();

		if (ImGui::Button("Cancel", { 50,0 }))
		{
			*open = false;  // ���̾�α� �ݱ�
		}

		ImGui::End();
	}
}


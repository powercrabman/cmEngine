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
	// 전역 변수 선언
	static std::filesystem::directory_entry selectedFolder; // 선택된 폴더 경로를 저장할 변수
	static std::string renameFolderName;  // 폴더 이름 변경 시 사용할 이름
	static bool showRenamePopup = false;  // 폴더 이름 변경 팝업을 보여줄지 여부

	if (*open)
	{
		// 파일 탐색기 창 시작
		ImGui::Begin(inDlgTitle, open, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);

		// 현재 디렉토리의 파일과 폴더 목록 저장
		std::vector<std::filesystem::directory_entry> files;
		std::vector<std::filesystem::directory_entry> folders;

		// 현재 경로의 디렉토리 및 파일들을 분류
		for (const auto& p : std::filesystem::directory_iterator(currentPath))
		{
			if (p.is_directory())
				folders.push_back(p);
			else
				files.push_back(p);
		}

		// 상위 디렉토리 이동을 위한 ".." 추가
		ImGui::Text("Current Path: %s", currentPath.c_str());

		ImGui::Separator();

		// 디렉토리 목록 (왼쪽)
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

		// 파일 목록 (표 형식)
		ImGui::BeginChild("Files##2", ImVec2(600, 400), true, ImGuiWindowFlags_HorizontalScrollbar);

		// 사용 가능한 전체 너비 가져오기
		float totalWidth = ImGui::GetContentRegionAvail().x;

		// 각 열에 할당할 너비 비율 설정
		float fileColumnWidth = totalWidth * 0.4f;    // 파일 이름 열에 전체 너비의 40% 할당
		float sizeColumnWidth = totalWidth * 0.2f;    // 파일 크기 열에 전체 너비의 20% 할당
		float typeColumnWidth = totalWidth * 0.2f;    // 파일 타입 열에 전체 너비의 20% 할당
		float dateColumnWidth = totalWidth * 0.2f;    // 수정 날짜 열에 전체 너비의 20% 할당

		// 열 생성 및 너비 설정
		ImGui::Columns(4, "file_columns");
		ImGui::SetColumnWidth(0, fileColumnWidth);
		ImGui::SetColumnWidth(1, sizeColumnWidth);
		ImGui::SetColumnWidth(2, typeColumnWidth);
		ImGui::SetColumnWidth(3, dateColumnWidth);

		// 열 제목 표시
		ImGui::Text("File"); ImGui::NextColumn();
		ImGui::Text("Size (bytes)"); ImGui::NextColumn();
		ImGui::Text("Type"); ImGui::NextColumn();
		ImGui::Text("Date Modified"); ImGui::NextColumn();
		ImGui::Separator();

		for (const auto& file : files)
		{
			// 파일 이름
			ImGui::Text(file.path().filename().string().c_str());
			ImGui::NextColumn();

			// 파일 크기
			ImGui::Text("%lld", file.file_size());
			ImGui::NextColumn();

			// 파일 확장자
			ImGui::Text("%s", file.path().extension().string().c_str());
			ImGui::NextColumn();

			// 파일 수정 날짜
			auto ftime = file.last_write_time();
			auto sctp = decltype(ftime)::clock::now() - (decltype(ftime)::clock::now() - ftime);

			// std::filesystem의 파일 시간을 time_t로 변환
			auto system_time = std::chrono::time_point_cast<std::chrono::system_clock::duration>(
				sctp - decltype(sctp)::clock::now() + std::chrono::system_clock::now());

			std::time_t tt = std::chrono::system_clock::to_time_t(system_time);
			struct tm timeInfo;
			localtime_s(&timeInfo, &tt);  // localtime_s를 사용하여 안전하게 변환

			char timeStr[64];
			std::strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M", &timeInfo);
			ImGui::Text("%s", timeStr);
			ImGui::NextColumn();
		}

		ImGui::EndChild();

		// 파일 이름 입력 필드 및 "확인" 버튼
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
			*open = false;  // 다이얼로그 닫기
		}

		ImGui::SameLine();

		if (ImGui::Button("Cancel", { 50,0 }))
		{
			*open = false;  // 다이얼로그 닫기
		}

		ImGui::End();
	}
}


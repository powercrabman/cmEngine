#include "0. cmEngine/cmEngine.h"
#include "FileDialog.h"

namespace cmEngine
{
	namespace fs = std::filesystem;

	FileDialog::FileDialog()
	{
		currentPath = fs::current_path();
	}

	void FileDialog::DrawFileButton(eAssetType inType, const char* inName, bool needLineBreak)
	{
		static Texture* sDirectoryTexture = ResourceManager::Ref().TryFindResource<Texture>(EngineResource::sFileTextureName);
		static Texture* sTextTexture      = ResourceManager::Ref().TryFindResource<Texture>(EngineResource::sTextTextureName);
		static Texture* sImageTexture     = ResourceManager::Ref().TryFindResource<Texture>(EngineResource::sImageTextureName);

		static ImTextureID sDirectoryIcon = reinterpret_cast<ImTextureID>(sDirectoryTexture->GetShaderResourceView().Get());
		static ImTextureID sTextIcon      = reinterpret_cast<ImTextureID>(sTextTexture->GetShaderResourceView().Get());
		static ImTextureID sImageIcon     = reinterpret_cast<ImTextureID>(sImageTexture->GetShaderResourceView().Get());

		ImTextureID icon = {};

		switch (inType)
		{
		case eAssetType::Text:
			icon = sTextIcon;
			break;
		case eAssetType::Image:
			icon = sImageIcon;
			break;
		case eAssetType::Directory:
			icon = sDirectoryIcon;
			break;
		default:
			assert(false);
		}

		// �̹��� ��ư (������)
		if (ImGui::ImageButton(inName, icon, ImVec2{ assetSize, assetSize }))
		{
			if (inType == eAssetType::Directory)
			{
				currentPath /= inName;
			}
		}

		if (needLineBreak)
		{
			ImGui::NewLine();  // ���� �ٷ� �̵�
		}
		else
		{
			ImGui::SameLine();  // ���� �ٿ� ��� �׸���
		}
	}

	void FileDialog::Draw()
	{
		ImGui::SetNextWindowSize({ 600, 400 }, ImGuiCond_Appearing);
		ImGui::Begin("File Dialog");

		// ���� ���丮 ǥ��
		ImGui::Text("Current path: %ls", currentPath.c_str());

		// ���� ���丮�� �̵� ��ư
		if (currentPath != currentPath.root_path())
		{
			ImGui::SameLine();
			if (ImGui::Button(".."))
			{
				currentPath = currentPath.parent_path();
			}
		}

		ImGui::Separator();
		float width = ImGui::GetContentRegionAvail().x;

		// ���� ��ư�� ũ��� ������ �������� ���
		float totalItemWidth = assetSize + ImGui::GetStyle().ItemSpacing.x;
		uint32 assetsPerRow = static_cast<uint32>(width / totalItemWidth);
		if (assetsPerRow == 0) assetsPerRow = 1;  // �ּ� 1�� ����

		// �� �׸� ���� ���� ������ ���� �е� ���
		float padding = (width - (assetsPerRow * assetSize)) / (assetsPerRow + 1);

		uint32 idx = 0;

		if (ImGui::BeginChild("Directory Search", ImVec2{ width, 0 }, true))
		{
			for (const auto& entry : fs::directory_iterator(currentPath))
			{
				eAssetType type = DetermineAssetType(entry);

				// �� �������� ���� ��ġ�� �е��� �°� ����
				ImGui::SetCursorPosX(ImGui::GetCursorPosX() + padding);

				bool needLineBreak = (idx % assetsPerRow) == (assetsPerRow - 1);
				DrawFileButton(type, entry.path().filename().string().c_str(), needLineBreak);

				idx++;
			}
			ImGui::EndChild();
		}

		ImGui::End();
	}

	eAssetType FileDialog::DetermineAssetType(const std::filesystem::directory_entry& entry)
	{
		if (entry.is_directory())
		{
			return eAssetType::Directory;
		}
		else if (entry.is_regular_file())
		{
			auto ext = entry.path().extension().wstring();
			if (ext == L".png" || ext == L".jpg" || ext == L".jpeg")
			{
				return eAssetType::Image;
			}
			else if (ext == L".txt" || ext == L".md")
			{
				return eAssetType::Text;
			}
		}
		return eAssetType::Text; // �⺻������ �ؽ�Ʈ�� ����
	}
}

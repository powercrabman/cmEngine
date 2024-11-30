#pragma once

namespace cmEngine
{
	enum class eAssetType
	{
		Text,
		Image,
		Directory,

		Count
	};

	struct FileDialog
	{
		FileDialog();

		eAssetType DetermineAssetType(const std::filesystem::directory_entry& entry);
		void DrawFileButton(eAssetType inType, const char* inName, bool needLineBreak);
		void Draw();

		std::filesystem::path	currentPath;
		float					assetSize = 100.f;
	};
}


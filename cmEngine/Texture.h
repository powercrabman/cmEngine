#pragma once
#include "ResourceBase.h"

namespace cmEngine
{
	enum class eTextureFormat
	{
		BMP = 1,
		JPEG,
		PNG,
		TIFF,
		GIF,
		WMP,
		ICO,
		HEIF
	};

	struct TextureJson : JsonMetaData
	{
		std::string		textureName;
		eResourceType	resourceType;
		std::string		imagePath;

		JSON_STRUCT_BODY(
			TextureJson,
			textureName,
			resourceType,
			imagePath
		);
	};

	class Texture : public ResourceBase
	{
	public:
		RESOURCE_BODY(Texture);
		~Texture() override = default;

		void LoadTextureImage(std::wstring_view inFilePath);
		void SaveTextureImage(std::wstring_view inFilePath, eTextureFormat inFormat) const;

		auto  GetSize() const;
		float GetAspectRatio() const { return mMetaData.width / static_cast<float>(mMetaData.height); }

		::ComPtr<ID3D11ShaderResourceView> GetShaderResourceView() const { return mSRV; }

		const wchar_t* GetTextureImagePath() const { return mImagePath.c_str(); }

	private:
		Texture() = default;
		void Create();

		bool LoadJsonFromFile(std::wstring_view inFilePath) override;
		void SaveJsonToFile(std::wstring_view inFilePath) override;
		bool LoadJsonFromSection(std::wstring_view inFilePath,std::string_view inSectionName) override;
		void SaveJsonToSection(std::wstring_view inFilePath, std::string_view inSectionName) override;

		::ComPtr<ID3D11ShaderResourceView>	mSRV         = nullptr;
		::ComPtr<ID3D11Texture2D>			mTex         = nullptr;
		TexMetadata							mMetaData    = {};
		ScratchImage						mImage       = {};
		std::wstring						mImagePath = {};
	};

	//===================================================
	//                      Inline
	//===================================================

	inline auto Texture::GetSize() const
	{
		return std::make_pair(mMetaData.width, mMetaData.height);
	}
}

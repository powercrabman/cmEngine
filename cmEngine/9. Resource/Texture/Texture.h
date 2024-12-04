#pragma once


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

	struct TextureJson
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

		Texture() = default;
		Texture(std::string_view inName) { mName = inName; }
		~Texture() override = default;

		void LoadTextureImage(std::wstring_view inFilePath);
		void SaveTextureImage(std::wstring_view inFilePath, eTextureFormat inFormat) const;

		auto  GetSize() const;
		float GetAspectRatio() const { return mMetaData.width / static_cast<float>(mMetaData.height); }

		::ComPtr<ID3D11ShaderResourceView> GetShaderResourceView() const { return mSRV; }

		const wchar_t* GetTextureImagePath() const { return mImagePath.c_str(); }

	private:
		void Create();

		void SaveJsonToFile(const std::filesystem::path& inFileName, const std::filesystem::path& inDirectory = "") override;
		bool LoadJsonFromFile(const std::filesystem::path& inFilePath,const std::filesystem::path& inDirectory = "") override;

		::ComPtr<ID3D11ShaderResourceView>	mSRV         = nullptr;
		::ComPtr<ID3D11Texture2D>			mTex         = nullptr;
		TexMetadata							mMetaData    = {};
		ScratchImage						mImage       = {};
		std::wstring						mImagePath   = {};
	};

	//===================================================
	//                      Inline
	//===================================================

	inline auto Texture::GetSize() const
	{
		return std::make_pair(mMetaData.width, mMetaData.height);
	}
}

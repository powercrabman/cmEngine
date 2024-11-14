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

	class Texture : public ResourceBase
	{
	public:
		RESOURCE_BODY(Texture);

		Texture() = default;
		virtual ~Texture() = default;

		void Load(std::wstring_view inFilePath);
		void Save(std::wstring_view inFilePath, eTextureFormat inFormat);

		void Create();
		auto GetSize() const;

		::ComPtr<ID3D11ShaderResourceView> GetShaderResourceView() const { return mSRV; }

	private:
		::ComPtr<ID3D11ShaderResourceView> mSRV = nullptr;
		::ComPtr<ID3D11Texture2D> mTex          = nullptr;
		TexMetadata mMetaData                   = {};
		ScratchImage mImage                     = {};
	};

	//===================================================
	//                      Inline
	//===================================================

	inline auto Texture::GetSize() const
	{
		return std::make_pair(mMetaData.width, mMetaData.height);
	}
}

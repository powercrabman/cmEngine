#pragma once
#include "cmResourceBase.h"

class cmTexture : public cmResourceBase
{
public:
	cmTexture() = default;
	virtual ~cmTexture() = default;

	void Load(std::wstring_view inFilePath);
	void Save(std::wstring_view inFilePath, eTextureFormat inFormat);

	void Create();
	auto GetSize() const;
	
	ID3D11ShaderResourceView*			GetShaderResource() const { return mSRV.Get(); }
	ID3D11ShaderResourceView* const*	GetShaderResourcePtr() { return mSRV.GetAddressOf(); }
	ID3D11Texture2D*					GetTexture() const { return mTex.Get(); }

private:
	UComPtr<ID3D11ShaderResourceView> mSRV = nullptr;
	UComPtr<ID3D11Texture2D> mTex = nullptr;
	TexMetadata mMetaData = {};
	ScratchImage mImage = {};
};

inline auto cmTexture::GetSize() const
{
	return std::make_pair(mMetaData.width, mMetaData.height);
}
